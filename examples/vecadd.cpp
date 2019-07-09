#include <cash.h>
#include <eda/altera/avalon.h>

using namespace eda::altera::avalon;

template <typename T,
          typename AVM,
          unsigned RQsize,
          unsigned WQsize>
class vecadd {
public:
  static constexpr unsigned DataW  = AVM::DataW;
  static constexpr unsigned AddrW  = AVM::AddrW;
  static constexpr unsigned LDataW = log2floor(DataW);

  __io (
    __in (ch_uint<AddrW>) dst,
    __in (ch_uint<AddrW>) src0,
    __in (ch_uint<AddrW>) src1,
    __in (ch_uint32)      count,
    (avalon_st_io)        avs,
    (avalon_mm_io<AVM>)   avm_dst,
    (avalon_mm_io<AVM>)   avm_src0,
    (avalon_mm_io<AVM>)   avm_src1
  );

  __enum (ctrl_state, (idle, running, done));

  void describe() {
    ch_reg<ctrl_state> state(ctrl_state::idle);
    ch_reg<ch_uint32> remaining(0);

    auto num_blocks = (io.count * ch_width_v<T> + (DataW - 1)) >> LDataW;
    auto start = io.avs.valid_in && (state == ctrl_state::idle);

    avm_reader0_.io.base_addr = io.src0;
    avm_reader0_.io.num_blocks = num_blocks;
    avm_reader0_.io.start = start;
    avm_reader0_.io.avm(io.src0_avm);

    avm_reader1_.io.base_addr = io.src1;
    avm_reader1_.io.num_blocks = num_blocks;
    avm_reader1_.io.start = start;
    avm_reader1_.io.avm(io.src1_avm);

    avm_writer_.io.base_addr = io.dst;
    avm_writer_.io.start = start;
    avm_writer_.io.flush = true; //(state == ctrl_state::done);
    avm_writer_.io.avm(io.dst_avm);

    __switch (state)
    __case (ctrl_state::idle) {
      __if (io.avs.valid_in) {
        state->next = ctrl_state::running;
      };
    }
    __case (ctrl_state::running) {
      __if (0 == remaining) {
        state->next = ctrl_state::done;
      };
    }
    __case (ctrl_state::done) {
      __if (!avm_writer_.io.busy && io.avs.ready_in) {
        state->next = ctrl_state::idle;
      };
    };

    __if (start) {
      remaining->next = num_blocks;
    }__elif (avm_writer_.io.enq.ready && avm_writer_.io.enq.valid) {
      remaining->next = remaining - 1;
    };

    ch_reg<ch_uint64> run_time(0);
    __if (state != ctrl_state::idle) {
      run_time->next = run_time + 1;
    };

    auto [k_data, k_valid, k_ready0, k_ready1] = k_vectoradd(avm_reader0_.io.deq.data,
                                                             avm_reader0_.io.deq.valid,
                                                             avm_reader1_.io.deq.data,
                                                             avm_reader1_.io.deq.valid,
                                                             writer_xbar_.io.in[1].ready);
    avm_writer_.io.enq(writer_xbar_.io.out);
    writer_xbar_.io.sel = (state == ctrl_state::running);
    writer_xbar_.io.in[0].data  = ch_resize<DataW>(perf_cntrs.as_bit());
    writer_xbar_.io.in[0].valid = (state == ctrl_state::write_cntrs);
    writer_xbar_.io.in[1].data  = k_data;
    writer_xbar_.io.in[1].valid = k_valid;
    avm_reader0_.io.deq.ready   = k_ready0;
    avm_reader1_.io.deq.ready   = k_ready1;

    io.avs.ready_out = (state == ctrl_state::idle);
    io.avs.valid_out = (state == ctrl_state::done) && !avm_writer_.io.busy;
  }

private:

  auto k_vectoradd(const ch_bit<DataW>& data_in0, const ch_bool valid_in0,
                   const ch_bit<DataW>& data_in1, const ch_bool valud_in1,
                   const ch_bool ready_out) {
    ch_bool pipeline_enable;
    auto d_in0_data = ch_delayEn(data_in0, pipeline_enable, 2);
    auto d_in1_data = ch_delayEn(data_in1, pipeline_enable, 2);

    ch_bit<DataW> data_out;
    for (uint i = 0; i < (DataW/ch_width_v<T>); ++i) {
      auto sum = ch_aslice<T>(d_in0_data, i) + ch_aslice<T>(d_in1_data, i);
      ch_asliceref<T>(data_out, i) = ch_delayEn(sum, pipeline_enable, 1);
    }

    auto valid_out = ch_delayEn(valid_in0 & valud_in1, pipeline_enable, 3, false);
    pipeline_enable = !valid_out || ready_out;

    auto ready_in0 = pipeline_enable && !(valid_in0 && !valud_in1);
    auto ready_in1 = pipeline_enable && !(valud_in1 && !valid_in0);

    return std::make_tuple(data_out, valid_out, ready_in0, ready_in1);
  }

  ch_module<avm_reader<AVM, RQsize>> avm_reader0_;
  ch_module<avm_reader<AVM, RQsize>> avm_reader1_;
  ch_module<avm_writer<AVM, WQsize>> avm_writer_;
};

int main() {
  // create FFT device
  ch_device<vectoradd_aocl<data_type, avm_v0, AVM_READ_QSIZE, AVM_WRITE_QSIZE>> device;

  std::cout << "hardware stats:" << std::endl;
  ch_stats(std::cout, device);

  ch_toVerilog("vectoradd.v", device);
  ch_toFIRRTL("vectoradd.fir", device);

  // allocate test buffer
  auto alloc_size = 64 * ceildiv<uint32_t>(count * (ch_width_v<data_type>/8), 64);
  std::vector<uint8_t> buffer_in0(alloc_size);
  std::vector<uint8_t> buffer_in1(alloc_size);
  std::vector<uint8_t> buffer_out(alloc_size + 64);

  // setup Avalon salve driver
  avm_slave_driver<avm_v0> avm_driver(128, 84);
  avm_driver.connect(device.io.src0_avm);
  avm_driver.connect(device.io.src1_avm);
  avm_driver.connect(device.io.dst_avm);
  avm_driver.bind(0, buffer_in0.data(), buffer_in0.size());
  avm_driver.bind(1, buffer_in1.data(), buffer_in1.size());
  avm_driver.bind(2, buffer_out.data(), buffer_out.size());

  // copy input data
  for (unsigned i = 0; i < count; ++i) {
    ch_system_t<data_type> value((float)(i & 0xff));
    ch_read(value, 0, buffer_in0.data(), i * ch_width_v<data_type>, ch_width_v<data_type>);
    ch_read(value, 0, buffer_in1.data(), i * ch_width_v<data_type>, ch_width_v<data_type>);
  }

  // run simulation
  ch_tracer tracer(device);
  device.io.avs.valid_in = false;
  device.io.avs.ready_in = false;
  auto ticks = tracer.run([&](ch_tick t)->bool {
    if (2 == t) {
      // start simulation
      device.io.dst   = 0;
      device.io.src0  = 0;
      device.io.src1  = 0;
      device.io.count = count;
      device.io.avs.valid_in = true;
      device.io.avs.ready_in = true;
    }
    // tick avm driver
    avm_driver.tick();

    // stop when device done
    return (!device.io.avs.valid_out && (t < MAX_TICKS));
  });

  // flush pending requests
  avm_driver.flush();

  // copy output data
  std::vector<ch_system_t<data_type>> test_result(count);
  for (unsigned i = 0; i < count; ++i) {
    auto& value = test_result[i];
    ch_write(value, 0, buffer_out.data(), i * ch_width_v<data_type>, ch_width_v<data_type>);
  }

  // get perf_counters
  ch_system_t<perf_counters> perf_cntrs;
  ch_write(perf_cntrs, 0, buffer_out.data(), buffer_out.size() * 8 - 512, ch_width_v<perf_counters>);
  std::cout << std::dec
            << "Simulation run time: "      << ticks/2 << " cycles" << std::endl
            << "Kernel run time: "     << (uint64_t)perf_cntrs.run_time << " cycles" << std::endl
            << "Read0 queue stalls: " << (uint64_t)perf_cntrs.r0q_stalls << " cycles" << std::endl
            << "Read0 memory stalls: " << (uint64_t)perf_cntrs.r0m_stalls << " cycles" << std::endl
            << "Read1 queue stalls: " << (uint64_t)perf_cntrs.r1q_stalls << " cycles" << std::endl
            << "Read1 memory stalls: " << (uint64_t)perf_cntrs.r1m_stalls << " cycles" << std::endl
            << "Write queue stalls: " << (uint64_t)perf_cntrs.wq_stalls << " cycles" << std::endl
            << "Write memory stalls: " << (uint64_t)perf_cntrs.wm_stalls << " cycles" << std::endl;


  tracer.toVCD("vectoradd.vcd");

  // verify output
  int ret = VerifyOutput(test_result);

  // verify testbench
  tracer.toTestBench("vectoradd_tb.v", "vectoradd.v");
  ret &= !system("iverilog vectoradd_tb.v -o vectoradd_tb.iv");
  ret &= !system("! vvp vectoradd_tb.iv | grep 'ERROR' || false");

  return ret;
}
