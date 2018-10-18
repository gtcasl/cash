#pragma once

#include <cash.h>
#include <htl/queue.h>
#include <htl/decoupled.h>

namespace eda {
namespace altera {
namespace avalon {

using namespace ch::logic;
using namespace ch::literals;
using namespace ch::htl;

template <unsigned Bitwidth, bool Signed, typename SystemType, typename LogicType>
struct my_traits {
  static constexpr int type = ch::internal::traits_system;
  static constexpr unsigned bitwidth  = Bitwidth;
  static constexpr unsigned is_signed = Signed;
  using system_type = SystemType;
  using logic_type  = LogicType;
};

__inout (avalon_st_io, (
  __in(ch_bool)  valid_in,  // inputs available
  __out(ch_bool) ready_out, // can receive inputs
  __out(ch_bool) valid_out, // outputs available
  __in(ch_bool)  ready_in   // can receive outputs
));

template <typename T>
__inout (avalon_mm_io, (
  __in(ch_bit<T::DataW>)    readdata,
  __in(ch_bool)             readdatavalid,
  __in(ch_bool)             waitrequest,
  __out(ch_bit<T::AddrW>)   address,
  __out(ch_bool)            read,
  __out(ch_bool)            write,
  __in(ch_bool)             writeack,
  __out(ch_bit<T::DataW>)   writedata,
  __out(ch_bit<T::DataW/8>) byteenable,
  __out(ch_bit<T::BurstW>)  burstcount
));

template <unsigned D, unsigned A, unsigned B>
struct avm_properties {
  static constexpr unsigned DataW  = D;
  static constexpr unsigned AddrW  = A;
  static constexpr unsigned BurstW = B;
  static_assert(ispow2(D), "invalid data width");
  static_assert(ispow2(A), "invalid address width");
};

using avm_v0 = avm_properties<512, 64, 5>;

///////////////////////////////////////////////////////////////////////////////

template <typename AVM, unsigned Latency = 0>
class avm_reader {
public:
  static constexpr unsigned LMaxBurst = AVM::BurstW - 1;
  static constexpr unsigned MaxBurst = 1 << LMaxBurst;
  static constexpr unsigned Qsize = 1 << log2ceil(MaxBurst + Latency);

  static constexpr unsigned DataW  = AVM::DataW;
  static constexpr unsigned AddrW  = AVM::AddrW;
  static constexpr unsigned BurstW = AVM::BurstW;

  static constexpr unsigned LDataW = log2floor(DataW);
  static constexpr unsigned DataB  = DataW/8;
  static constexpr unsigned LDataB = log2floor(DataB);

  using burst_t = ch_uint<AVM::BurstW>;

  __io(
    __in(ch_uint<AddrW>)  base_addr,
    __in(ch_uint32)       num_blocks,
    __in(ch_bool)         start,
    __out(ch_bool)        done,
    (ch_deq_io<ch_bit<DataW>>) deq,
    (avalon_mm_io<AVM>)   avm,
    __out(ch_uint64)      req_stalls,
    __out(ch_uint64)      mem_stalls
  );

  void describe() {
    //--
    ch_reg<ch_uint<AddrW>> address(0);
    ch_reg<ch_uint<log2ceil(Qsize+1)>> pending_size(0);
    ch_reg<ch_uint<32-LMaxBurst>> remain_reqs(0);
    ch_reg<ch_bool> read_enabled(false);
    ch_reg<burst_t> burst_count(0);
    ch_reg<ch_bool> done(false);

    //--
    auto read_granted = read_enabled && !io.avm.waitrequest;
    auto fifo_dequeued = out_fifo_.io.deq.valid && out_fifo_.io.deq.ready;

    //--
    __if (io.start) {
      burst_count->next = (ch_slice<burst_t>(io.num_blocks - 1) & (MaxBurst - 1)) + 1;
    }__elif (read_granted) {
      burst_count->next = MaxBurst;
    };

    //--
    __if (io.start) {
      read_enabled->next = (io.num_blocks != 0);
    }__elif (read_granted && (1 == remain_reqs)) {
      read_enabled->next = false;
    }__else {
      read_enabled->next = (remain_reqs != 0) && (pending_size->next <= (Qsize - MaxBurst));
    };

    //--
    __if (io.start) {
      pending_size->next = 0;
    }__elif (read_granted) {
      __if (fifo_dequeued) {
        pending_size->next = pending_size + burst_count - 1;
      }__else {
        pending_size->next = pending_size + burst_count;
      };
    }__else {
      __if (fifo_dequeued) {
        pending_size->next = pending_size - 1;
      }__else {
        pending_size->next = pending_size;
      };
    };

    //--
    __if (io.start) {
      remain_reqs->next = ch_shr<32-LMaxBurst>(io.num_blocks + MaxBurst - 1, LMaxBurst);
    }__elif (read_granted) {
      remain_reqs->next = remain_reqs - 1;
    };

    //--
    __if (io.start) {
      address->next = io.base_addr;
    }__elif (read_granted) {
      address->next = address + (ch_resize<AddrW>(burst_count) << LDataB);
    };

    //--
    __if (io.start) {
      done->next = (0 == io.num_blocks);
    }__elif (read_granted && (1 == remain_reqs)) {
      done->next = true;
    };

    //--
    ch_reg<ch_uint64> req_stalls(0);
    __if ((remain_reqs != 0) && !io.avm.read && !io.avm.waitrequest) {
      req_stalls->next = req_stalls + 1;
    };

    //--
    ch_reg<ch_uint64> mem_stalls(0);
    __if (io.avm.read && io.avm.waitrequest) {
      mem_stalls->next = mem_stalls + 1;
    };

    //--
    out_fifo_.io.enq.data  = io.avm.readdata;
    out_fifo_.io.enq.valid = io.avm.readdatavalid;
    out_fifo_.io.deq(io.deq);

    //--
    io.avm.address    = address;
    io.avm.read       = read_enabled;
    io.avm.write      = false;
    io.avm.writedata  = 0;
    io.avm.byteenable = -1; // full word access
    io.avm.burstcount = burst_count;

    //--
    io.done = done;

    //--
    io.req_stalls = req_stalls;
    io.mem_stalls = mem_stalls;

    /*__if (ch_clock()) {
      ch_print("{0}: AVMR: start={1}, rd={2}, addr={3}, burst={4}, rdg={5}, rmqs={6}, pns={7}, rsp={8}, pop={9}, ffs={10}, done={11}",
             ch_now(), io.start, io.avm.read, io.avm.address, io.avm.burstcount,
               read_granted, remain_reqs, pending_size, io.avm.readdatavalid,
               out_fifo_.io.deq.ready, out_fifo_.io.size, io.done);
    };*/
  }

private:
  ch_module<ch_queue<ch_bit<DataW>, Qsize>> out_fifo_;
};

///////////////////////////////////////////////////////////////////////////////

template <typename AVM, unsigned Latency = 0>
class avm_writer {
public:
  static constexpr unsigned MaxBurst = 1 << (AVM::BurstW - 1);
  static constexpr unsigned Qsize = 1 << log2ceil(MaxBurst + Latency);

  static constexpr unsigned DataW  = AVM::DataW;
  static constexpr unsigned AddrW  = AVM::AddrW;
  static constexpr unsigned BurstW = AVM::BurstW;

  static constexpr unsigned LDataW = log2floor(DataW);
  static constexpr unsigned DataB  = DataW/8;
  static constexpr unsigned LDataB = log2floor(DataB);

  using burst_t = ch_uint<AVM::BurstW>;

  __io(
    __in(ch_uint<AddrW>)  base_addr,
    __in(ch_bool)         start,
    __out(ch_bool)        done,
    (ch_enq_io<ch_bit<DataW>>) enq,
    (avalon_mm_io<AVM>)   avm,
    __out(ch_uint64)      req_stalls,
    __out(ch_uint64)      mem_stalls
  );

  void describe() {
    ch_reg<ch_uint<AddrW>> address(0);
    ch_reg<burst_t> burst_counter(0);
    ch_reg<ch_bool> write_enabled(false);
    ch_reg<ch_bool> done(false);

    // determine if we can submit the next data
    auto write_granted = write_enabled && !io.avm.waitrequest;

    // determine when to start the next burst transaction
    auto burst_begin = ((0 == burst_counter) && in_fifo_.io.deq.valid)
                    || ((1 == burst_counter) && !io.avm.waitrequest && (in_fifo_.io.size > 1));

    // compute the burst size
    auto full_burst_enable = (in_fifo_.io.size > MaxBurst)
                          || ((in_fifo_.io.size == MaxBurst) && (0 == burst_counter));
    auto partial_burst_value = ch_slice<burst_t>(in_fifo_.io.size) -  (burst_counter != 0).as_uint();
    auto burst_count_val = ch_sel(full_burst_enable, MaxBurst, partial_burst_value);
    auto burst_count = ch_delayEn(burst_count_val, burst_begin);

    //--
    __if (io.start) {
      address->next = io.base_addr;
    }__elif (write_granted) {
      address->next = address + DataB;
    };

    //--
    __if (burst_begin) {
      burst_counter->next = burst_count_val;
    }__elif (write_granted) {
      burst_counter->next = burst_counter - 1;
    };

    //--
    __if (burst_begin) {
      write_enabled->next = true;
    }__elif (write_granted && (1 == burst_counter)) {
      write_enabled->next = false;
    };

    //--
    __if (in_fifo_.io.enq.ready && in_fifo_.io.enq.valid) {
      done->next = false;
    }__elif (write_granted && (1 == in_fifo_.io.size)) {
      done->next = true;
    };

    //--
    ch_reg<ch_uint64> req_stalls(0);
    __if (!in_fifo_.io.enq.ready) {
      req_stalls->next = req_stalls + 1;
    };

    //--
    ch_reg<ch_uint64> mem_stalls(0);
    __if (io.avm.write && io.avm.waitrequest) {
      mem_stalls->next = mem_stalls + 1;
    };

    //--
    io.avm.address    = address;
    io.avm.read       = false;
    io.avm.write      = write_enabled;
    io.avm.writedata  = in_fifo_.io.deq.data;
    io.avm.byteenable = -1; // full word access
    io.avm.burstcount = burst_count;

    //--
    in_fifo_.io.deq.ready = write_granted;
    in_fifo_.io.enq(io.enq);

    //--
    io.done = done;

    //--
    io.req_stalls = req_stalls;
    io.mem_stalls = mem_stalls;

    /*__if (ch_clock()) {
      ch_print("{0}: AVMW: bbg={1}, wr={2}, wrg={3}, wtrq={4}, ffs={5}, addr={6}, burst={7}, burstctr={8}, wdata={9}, done={10}",
             ch_now(), burst_begin, io.avm.write, write_granted, io.avm.waitrequest, in_fifo_.io.size,
               io.avm.address, io.avm.burstcount, burst_counter, io.avm.writedata, io.done);
    };*/
  }

private:
  ch_module<ch_queue<ch_bit<DataW>, Qsize>> in_fifo_;
};

}
}
}
