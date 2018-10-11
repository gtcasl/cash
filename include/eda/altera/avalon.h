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

template <typename AVM, unsigned Qsize = 32>
class avm_reader {
public:
  static constexpr unsigned MaxBurst = 1 << (AVM::BurstW - 1);
  static_assert(Qsize >= 2*MaxBurst, "invalid Qsize");

  static constexpr unsigned DataW  = AVM::DataW;
  static constexpr unsigned AddrW  = AVM::AddrW;
  static constexpr unsigned BurstW = AVM::BurstW;

  static constexpr unsigned LDataW = log2floor(DataW);
  static constexpr unsigned DataB  = DataW/8;
  static constexpr unsigned LDataB = log2floor(DataB);

  using burst_t = ch_uint<log2ceil(MaxBurst+1)>;

  __io(
    __in(ch_uint<AddrW>)  base_addr,
    __in(ch_uint32)       num_blocks,
    __in(ch_bool)         start,
    __out(ch_bool)        done,
    (ch_deq_io<ch_bit<DataW>>) deq,
    (avalon_mm_io<AVM>)   avm,
    __out(ch_uint64)      stalls
  );

  void describe() {
    //--
    ch_reg<ch_uint<AddrW>> address(0);
    ch_reg<ch_uint<log2ceil(Qsize+1)>> pending_reqs(0);
    ch_reg<ch_uint32> remain_reqs(0);
    ch_reg<ch_bool> done(false);

    // determine if we can request the next data
    auto fifo_almost_full = (ch_pad<1>(fifo_.io.size) + pending_reqs) > (Qsize - 2*MaxBurst); // assume inflight burst from previous cycle
    auto cur_remain_reqs = ch_sel(io.start, io.num_blocks, remain_reqs);
    auto read_enabled_next = (cur_remain_reqs != 0) && !fifo_almost_full;
    auto read_enabled = ch_delay(read_enabled_next, 1, false) && (remain_reqs != 0); // ensure no an extra request to be issued
    auto read_complete = read_enabled && !io.avm.waitrequest;

    // compute the burst size
    auto last_burst_enable = (cur_remain_reqs < MaxBurst);
    auto last_burst_count = ch_slice<burst_t>(cur_remain_reqs);
    auto burst_count = ch_delay(ch_sel(last_burst_enable, last_burst_count, MaxBurst));

    //--
    __if (io.start) {
      remain_reqs->next = io.num_blocks;
    }__elif (read_complete) {
      remain_reqs->next = remain_reqs - burst_count;
    };

    //--
    __if (io.start) {
      address->next = io.base_addr;
    }__elif (read_complete) {
      address->next = address + (ch_resize<AddrW>(burst_count) << LDataB);
    };

    //--
    __if (io.start) {
      pending_reqs->next = 0;
    }__elif (read_complete) {
      __if (io.avm.readdatavalid) {
        // a burst request is submitted while a block is returned
        pending_reqs->next = pending_reqs + burst_count - 1;
      }__else {
        // a burst request is submitted but no block is returned
        pending_reqs->next = pending_reqs + burst_count;
      };
    }__else {
      __if (io.avm.readdatavalid) {
        // no request submitted but a block is returned
        pending_reqs->next = pending_reqs - 1;
      }__else {
        // no request submitted and no block returned
        pending_reqs->next = pending_reqs;
      };
    };

    //--
    __if (io.start) {
      done->next = (0 == io.num_blocks);
    }__elif ((0 == remain_reqs) || (burst_count == remain_reqs && read_complete)) {
      done->next = true;
    };

    //--
    ch_reg<ch_uint64> stalls(0);
    __if (read_enabled && io.avm.waitrequest) {
      stalls->next = stalls + 1;
    };

    //--
    fifo_.io.enq.data  = io.avm.readdata;
    fifo_.io.enq.valid = io.avm.readdatavalid;
    fifo_.io.deq(io.deq);

    //--
    io.avm.address    = address;
    io.avm.read       = read_enabled;
    io.avm.write      = false;
    io.avm.writedata  = 0;
    io.avm.byteenable = -1; // full word access
    io.avm.burstcount = ch_resize<BurstW>(burst_count);

    //--
    io.done = done;

    //--
    io.stalls = stalls;

    /*__if (ch_clock()) {
      ch_print("{0}: AVMR: rd={1}, rdn={2}, wtrq={3}, rmq={4}, pnq={5}, ffs={6}, rsp={7}, addr={8}, burst={9}, done={10}",
             ch_now(), io.avm.read, read_complete, io.avm.waitrequest, remain_reqs, pending_reqs, fifo_.io.size, io.avm.readdatavalid, io.avm.address, io.avm.burstcount, io.done);
    };*/
  }

private:
  ch_module<ch_queue<ch_bit<DataW>, Qsize>> fifo_;
};

///////////////////////////////////////////////////////////////////////////////

template <typename AVM, unsigned Qsize = 32>
class avm_writer {
public:
  static constexpr unsigned MaxBurst = 1 << (AVM::BurstW - 1);
  static_assert(Qsize >= MaxBurst, "invalid Qsize");

  static constexpr unsigned DataW  = AVM::DataW;
  static constexpr unsigned AddrW  = AVM::AddrW;
  static constexpr unsigned BurstW = AVM::BurstW;

  static constexpr unsigned LDataW = log2floor(DataW);
  static constexpr unsigned DataB  = DataW/8;
  static constexpr unsigned LDataB = log2floor(DataB);

  using burst_t = ch_uint<log2ceil(MaxBurst+1)>;

  __io(
    __in(ch_uint<AddrW>)  base_addr,
    __in(ch_uint32)       num_blocks,
    __in(ch_bool)         start,
    __out(ch_bool)        done,
    (ch_enq_io<ch_bit<DataW>>) enq,
    (avalon_mm_io<AVM>)   avm,
    __out(ch_uint64)      stalls
  );

  void describe() {
    ch_reg<ch_uint<AddrW>> address(0);
    ch_reg<ch_uint32> remain_reqs(0);
    ch_reg<burst_t> burst_counter(0);
    ch_reg<ch_bool> write_enabled(false);
    ch_reg<ch_bool> done(false);

    // determine if we can submit the next data
    auto write_complete = write_enabled && !io.avm.waitrequest;

    // determine when to start the next burst transaction
    auto full_burst_ready = (fifo_.io.size > MaxBurst)
                        ||	((fifo_.io.size == MaxBurst) && (0 == burst_counter));
    auto last_burst_enable = (remain_reqs < MaxBurst);
    auto last_burst_count  = ch_slice<burst_t>(remain_reqs);
    auto last_burst_ready  = (fifo_.io.size > last_burst_count)
                           || ((fifo_.io.size == last_burst_count) && (0 == burst_counter));
    auto burst_begin = (remain_reqs != 0)
                    && ((last_burst_enable && last_burst_ready) || full_burst_ready)
                    && ((0 == burst_counter) || ((1 == burst_counter) && !io.avm.waitrequest));

    // compute the burst size
    auto burst_count_val = ch_sel(last_burst_enable, last_burst_count, MaxBurst);

    //--
    auto burst_count = ch_delay(burst_count_val);

    //--
    __if (io.start) {
      address->next = io.base_addr;
    }__elif (write_complete) {
      address->next = address + DataB;
    };

    //--
    __if (io.start) {
      remain_reqs->next = io.num_blocks;
    }__elif (write_complete) {
      remain_reqs->next = remain_reqs - 1;
    };

    //--
    __if (io.start) {
      burst_counter->next = 0;
    }__elif(burst_begin) {
      burst_counter->next = burst_count_val;
    }__elif(write_complete) {
      burst_counter->next = burst_counter - 1;
    };

    //--
    __if (burst_begin) {
      write_enabled->next = true;
    }__elif (1 == burst_counter && write_complete) {
      write_enabled->next = false;
    };

    //--
    __if (io.start) {
      done->next = (0 == io.num_blocks);
    }__elif ((0 == remain_reqs) || (1 == remain_reqs && write_complete)) {
      done->next = true;
    };

    //--
    ch_reg<ch_uint64> stalls(0);
    __if (write_enabled && io.avm.waitrequest) {
      stalls->next = stalls + 1;
    };

    //--
    io.avm.address    = address;
    io.avm.read       = false;
    io.avm.write      = write_enabled;
    io.avm.writedata  = fifo_.io.deq.data;
    io.avm.byteenable = -1; // full word access
    io.avm.burstcount = ch_resize<BurstW>(burst_count);

    //--
    fifo_.io.deq.ready = write_complete;
    fifo_.io.enq(io.enq);

    //--
    io.done = done;

    //--
    io.stalls = stalls;

    /*__if (ch_clock()) {
      ch_print("{0}: AVMW: wr0={1}, wr={2}, wrn={3}, wtrq={4}, rmq={5}, ffs={6}, addr={7}, burst={8}, burstv={9}, wdata={10}, done={11}",
             ch_now(), burst_begin, io.avm.write, write_complete, io.avm.waitrequest, remain_reqs, fifo_.io.size, io.avm.address, io.avm.burstcount, burst_count_val, io.avm.writedata, io.done);
    };*/
  }

private:
  ch_module<ch_queue<ch_bit<DataW>, Qsize>> fifo_;
};

}
}
}
