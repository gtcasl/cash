#include <cash.h>
#include <htl/fixed.h>
#include <eda/altera/avalon.h>
#include <eda/altera/avalon_sim.h>
#include "common.h"

using namespace ch::core;
using namespace ch::htl;
using namespace eda::altera::avalon;

template <typename T>
class vectoradd {
public:
  __io (
    __in (ch_uint<avm_v0::AddrW>) dst,
    __in (ch_uint<avm_v0::AddrW>) src0,
    __in (ch_uint<avm_v0::AddrW>) src1,
    __in (ch_uint32)       count,
      (avalon_st_io)       avs,
    (avalon_mm_io<avm_v0>) avm_dst,
    (avalon_mm_io<avm_v0>) avm_src0,
    (avalon_mm_io<avm_v0>) avm_src1
  );

  __enum (ctrl_state, (idle, running, done));

  vectoradd(int delay) : delay_(delay) {}

  void describe() {
    ch_reg<ctrl_state> state(ctrl_state::idle);
    ch_reg<ch_uint32> remaining(0);

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

    auto start  = io.avs.valid_in && (state == ctrl_state::idle);
    __if (start) {
      remaining->next = io.count;
    }__elif (avm_writer_.io.enq.ready && avm_writer_.io.enq.valid) {
      remaining->next = remaining - 1;
    };

    auto enable = avm_writer_.io.enq.ready || !avm_writer_.io.enq.valid;

    auto sum = ch_delayEn(avm_reader0_.io.deq.data + avm_reader1_.io.deq.data, enable, delay_);

    auto src0_ready = enable && !(avm_reader0_.io.deq.valid && !avm_reader1_.io.deq.valid);
    auto src1_ready = enable && !(avm_reader1_.io.deq.valid && !avm_reader0_.io.deq.valid);
    auto dst_valid  = ch_delayEn(avm_reader0_.io.deq.valid & avm_reader1_.io.deq.valid, enable, delay_, false);

    avm_reader0_.io.deq.ready = src0_ready;
    avm_reader0_.io.base_addr = io.src0;
    avm_reader0_.io.count = io.count;
    avm_reader0_.io.start = start;
    avm_reader0_.io.avm(io.avm_src0);

    avm_reader1_.io.deq.ready = src1_ready;
    avm_reader1_.io.base_addr = io.src1;
    avm_reader1_.io.start = start;
    avm_reader1_.io.count = io.count;    
    avm_reader1_.io.avm(io.avm_src1);

    avm_writer_.io.enq.data   = sum;
    avm_writer_.io.enq.valid  = dst_valid;
    avm_writer_.io.base_addr = io.dst;
    avm_writer_.io.start = start;
    avm_writer_.io.done = (state == ctrl_state::done);
    avm_writer_.io.avm(io.avm_dst);

    io.avs.ready_out = (state == ctrl_state::idle);
    io.avs.valid_out = (state == ctrl_state::done) && !avm_writer_.io.busy;
  }

private:

  ch_module<avm_reader<T>> avm_reader0_;
  ch_module<avm_reader<T>> avm_reader1_;
  ch_module<avm_writer<T>> avm_writer_;
  int delay_;
};

using data_type = ch::htl::ch_fixed<32, 16>;

static bool verify(const std::vector<ch_system_t<data_type>>& output) {
  int errors = 0;

  for (unsigned i = 0; i < output.size(); ++i) {
    auto value = static_cast<float>(output[i]);
    auto refvalue = static_cast<float>(2*(i & 0xff));
    bool test = (value != refvalue);
    if (test) {
      std::cout << "error: value[" << i << "]=" << value << ", gold " << refvalue << std::endl;
    }
    errors += test;
  }

  if (errors != 0) {
    std::cout << "\tFound " << errors << " errors: FAILED!" << std::endl;
  }

  return (0 == errors);
}

int main() {
  unsigned count = 256;

  // create FFT device
  ch_device<vectoradd<data_type>> device(2);

  std::cout << "hardware stats:" << std::endl;
  ch_stats(std::cout, device);

  // allocate test buffer
  auto alloc_size = 64 * ceildiv<uint32_t>(count * (ch_width_v<data_type>/8), 64);
  std::vector<uint8_t> buffer_in0(alloc_size);
  std::vector<uint8_t> buffer_in1(alloc_size);
  std::vector<uint8_t> buffer_out(alloc_size + 64);

  // setup Avalon salve driver
  avm_slave_driver<avm_v0> avm_driver(128, 84);
  avm_driver.connect(device.io.avm_src0);
  avm_driver.connect(device.io.avm_src1);
  avm_driver.connect(device.io.avm_dst);
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

  std::cout << "Simulation run time: " << std::dec << ticks/2 << " cycles" << std::endl;

  // flush pending requests
  avm_driver.flush();

  // copy output data
  std::vector<ch_system_t<data_type>> test_result(count);
  for (unsigned i = 0; i < count; ++i) {
    auto& value = test_result[i];
    ch_write(value, 0, buffer_out.data(), i * ch_width_v<data_type>, ch_width_v<data_type>);
  }

  ch_toVerilog("vectoradd.v", device);

  // verify output
  CHECK(verify(test_result));

  ch_toFIRRTL("vectoradd.fir", device);

  tracer.toText("vectoradd.log");
  tracer.toVCD("vectoradd.vcd");
  tracer.toTestBench("vectoradd_tb.v", "vectoradd.v");
  int ret = !system("iverilog vectoradd_tb.v -o vectoradd_tb.iv")
          & !system("! vvp vectoradd_tb.iv | grep 'ERROR' || false");

  return (0 == ret);
}
