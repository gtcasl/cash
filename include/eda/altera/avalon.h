#pragma once

#include "../../core.h"
#include "../../htl/queue.h"
#include "../../htl/decoupled.h"

namespace eda {
namespace altera {
namespace avalon {

using namespace ch::logic;
using namespace ch::literals;
using namespace ch::htl;

template <unsigned D, unsigned A, unsigned B>
struct avm_properties {
  static constexpr unsigned DataW  = D;
  static constexpr unsigned AddrW  = A;
  static constexpr unsigned BurstW = B;
  static_assert(ispow2(D), "invalid data width");
  static_assert(ispow2(A), "invalid address width");
};

using avm_v0 = avm_properties<512, 64, 5>;

__interface (avalon_st_io, (
  __in  (ch_bool) valid_in,  // inputs available
  __out (ch_bool) ready_out, // can receive inputs
  __out (ch_bool) valid_out, // outputs available
  __in  (ch_bool) ready_in   // can receive outputs
));

template <typename T = avm_v0>
__interface (avalon_mm_io, (
  __in  (ch_bit<T::DataW>)   readdata,
  __in  (ch_bool)            readdatavalid,
  __in  (ch_bool)            waitrequest,
  __out (ch_bit<T::AddrW>)   address,
  __out (ch_bool)            read,
  __out (ch_bool)            write,
  __in  (ch_bool)            writeack,
  __out (ch_bit<T::DataW>)   writedata,
  __out (ch_bit<T::DataW/8>) byteenable,
  __out (ch_bit<T::BurstW>)  burstcount
));

///////////////////////////////////////////////////////////////////////////////

template <typename T,
          unsigned Qsize = (1 << (avm_v0::BurstW - 1)),
          typename AVM = avm_v0>
class avm_reader {
public:
  using data_type = T;

  static constexpr unsigned LMaxBurst = AVM::BurstW - 1;
  static constexpr unsigned MaxBurst = 1 << LMaxBurst;
  static_assert(Qsize >= MaxBurst, "invalid size");
  static_assert(ispow2(Qsize), "invalid size");

  static constexpr unsigned DataW  = AVM::DataW;
  static constexpr unsigned AddrW  = AVM::AddrW;
  static constexpr unsigned BurstW = AVM::BurstW;

  static constexpr unsigned LDataW = log2floor(DataW);
  static constexpr unsigned DataB  = DataW/8;
  static constexpr unsigned LDataB = log2floor(DataB);

  static constexpr unsigned DataPerBlk = DataW / ch_width_v<data_type>;
  static_assert(ch_width_v<data_type> <= DataW, "invalid size");
  static_assert(DataW == DataPerBlk * ch_width_v<data_type>, "invalid size");
  static_assert(ispow2(DataPerBlk), "invalid size");

  using burst_t = ch_uint<AVM::BurstW>;

  __io (
    __in  (ch_uint<AddrW>) base_addr,
    __in  (ch_uint32)      count,
    __in  (ch_bool)        start,
    __out (ch_bool)        busy,
    (ch_deq_io<data_type>) deq,
    (avalon_mm_io<AVM>)    avm,
    __out (ch_uint64)      req_stalls,
    __out (ch_uint64)      mem_stalls
  );

  void describe() {
    //--
    ch_reg<ch_uint<AddrW>> address(0);
    ch_reg<ch_uint<log2ceil(Qsize+1)>> pending_size(0);
    ch_reg<ch_uint<32-LMaxBurst>> remain_reqs(0);
    ch_reg<ch_bool> read_enabled(false);
    ch_reg<burst_t> burst_count(0);
    ch_reg<ch_bool> busy(false);

    // total blocks to fetch
    auto num_blocks = (io.count * ch_width_v<data_type> + (DataW - 1)) >> LDataW;

    // the read request was granted
    auto read_granted = read_enabled && !io.avm.waitrequest;

    // the output queue was popped
    auto fifo_dequeued = out_fifo_.io.deq.valid && out_fifo_.io.deq.ready;

    // track the request burst size
    __if (io.start) {
      burst_count->next = (ch_slice<burst_t>(num_blocks - 1) & (MaxBurst - 1)) + 1;
    }__elif (read_granted) {
      burst_count->next = MaxBurst;
    };

    // assert a read request when the queue has enough space for the next burst
    __if (io.start) {
      read_enabled->next = (num_blocks != 0);
    }__elif (read_granted && (1 == remain_reqs)) {
      read_enabled->next = false;
    }__else {
      read_enabled->next = (remain_reqs != 0) && (pending_size->next <= (Qsize - MaxBurst));
    };

    // track the pending queue size
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

    // track remaining burst requests
    __if (io.start) {
      remain_reqs->next = ch_shr<32-LMaxBurst>(num_blocks + MaxBurst - 1, LMaxBurst);
    }__elif (read_granted) {
      remain_reqs->next = remain_reqs - 1;
    };

    // advance the address when a read is granted
    __if (io.start) {
      address->next = io.base_addr;
    }__elif (read_granted) {
      address->next = address + (ch_resize<AddrW>(burst_count) << LDataB);
    };

    // the device is busy until all requests are submitted
    __if (io.start) {
      busy->next = (num_blocks != 0);
    }__elif (read_granted && (1 == remain_reqs)) {
      busy->next = false;
    };

    // we have a request stall when we have pending requests with the Avalon bus ready but the request deasserted
    ch_reg<ch_uint64> req_stalls(0);
    __if ((remain_reqs != 0) && !io.avm.waitrequest && !io.avm.read) {
      req_stalls->next = req_stalls + 1;
    };

    // we have a memory stall when we a request is asserted but he Avalon bus is busy
    ch_reg<ch_uint64> mem_stalls(0);
    __if (io.avm.read && io.avm.waitrequest) {
      mem_stalls->next = mem_stalls + 1;
    };

    //--
    out_fifo_.io.enq.data  = io.avm.readdata;
    out_fifo_.io.enq.valid = io.avm.readdatavalid;

    //--
    if constexpr ((ch_width_v<data_type>) < DataW) {
      ch_reg<ch_bit<DataW>> tmp_buf;
      ch_reg<ch_bool> tmp_buf_valid(false);

      auto tmp_buf_pop = tmp_buf_valid && io.deq.ready;
      ch_counter<DataPerBlk> counter(tmp_buf_pop);
      auto tmp_buf_going_empty = (counter.value() == (DataPerBlk-1)) && io.deq.ready;
      auto tmp_buf_ready = !tmp_buf_valid || tmp_buf_going_empty;
      auto tmp_buf_fill = out_fifo_.io.deq.valid && tmp_buf_ready;

      __if (tmp_buf_fill) {
        tmp_buf->next = out_fifo_.io.deq.data;
      }__elif (tmp_buf_pop) {
        tmp_buf->next = tmp_buf >> ch_width_v<data_type>;
      };

      __if (tmp_buf_fill) {
        tmp_buf_valid->next = true;
      }__elif (tmp_buf_going_empty) {
        tmp_buf_valid->next = false;
      };

      io.deq.data  = ch_slice<data_type>(tmp_buf);
      io.deq.valid = tmp_buf_valid;
      out_fifo_.io.deq.ready = tmp_buf_ready;
    } else {
      out_fifo_.io.deq(io.deq);
    }

    //--
    io.avm.address    = address;
    io.avm.read       = read_enabled;
    io.avm.write      = false;
    io.avm.writedata  = 0;
    io.avm.byteenable = -1; // full word access
    io.avm.burstcount = burst_count;

    //--
    io.busy = busy;

    //--
    io.req_stalls = req_stalls;
    io.mem_stalls = mem_stalls;

    /*__if (ch_clock() && io.deq.valid && io.deq.ready) {
      ch_println("{}: AVMR: deq_data={}", ch_now(), io.deq.data);
    };
    __if (ch_clock()) {
      ch_println("{}: AVMR: start={}, rd={}, addr={}, burst={}, rdg={}, rmqs={}, pns={}, rsp={}, pop={}, ffs={}, busy={}",
             ch_now(), io.start, io.avm.read, io.avm.address, io.avm.burstcount,
               read_granted, remain_reqs, pending_size, io.avm.readdatavalid,
               fifo_dequeued, out_fifo_.io.size, io.busy);
    };*/
  }

private:
  ch_module<ch_queue<ch_bit<DataW>, Qsize>> out_fifo_;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned Qsize = (1 << (avm_v0::BurstW - 1)), typename AVM = avm_v0>
class avm_writer {
public:
  using data_type = T;

  static constexpr unsigned MaxBurst = 1 << (AVM::BurstW - 1);
  static_assert(Qsize >= MaxBurst, "invalid size");
  static_assert(ispow2(Qsize), "invalid size");

  static constexpr unsigned DataW  = AVM::DataW;
  static constexpr unsigned AddrW  = AVM::AddrW;
  static constexpr unsigned BurstW = AVM::BurstW;

  static constexpr unsigned LDataW = log2floor(DataW);
  static constexpr unsigned DataB  = DataW/8;
  static constexpr unsigned LDataB = log2floor(DataB);

  static constexpr unsigned DataPerBlk = DataW / ch_width_v<data_type>;
  static_assert(ch_width_v<data_type> <= DataW, "invalid size");
  static_assert(DataW == DataPerBlk * ch_width_v<data_type>, "invalid size");
  static_assert(ispow2(DataPerBlk), "invalid size");

  using burst_t = ch_uint<AVM::BurstW>;

  __io (
    __in  (ch_uint<AddrW>) base_addr,
    __in  (ch_bool)        start,
    __in  (ch_bool)        done,
    __out (ch_bool)        busy,
    (ch_enq_io<data_type>) enq,
    (avalon_mm_io<AVM>)    avm,
    __out (ch_uint64)      req_stalls,
    __out (ch_uint64)      mem_stalls
  );

  void describe() {
    ch_reg<ch_uint<AddrW>> address(0);
    ch_reg<burst_t> burst_counter(0);
    ch_reg<ch_bool> write_enabled(false);
    ch_reg<ch_bool> busy(false);
    ch_bool flush;

    // the write request was granted
    auto write_granted = write_enabled && !io.avm.waitrequest;

    // determine when to begin the next write transaction
    auto fifo_valid = (in_fifo_.io.deq.valid && flush)
                   || (in_fifo_.io.size >= MaxBurst);
    auto fifo_valid_next = (in_fifo_.io.size > 1 && flush)
                        || (in_fifo_.io.size > MaxBurst);
    auto write_begin = (0 == burst_counter && fifo_valid)
                    || (1 == burst_counter && !io.avm.waitrequest && fifo_valid_next);

    // compute the burst size
    auto full_burst_enable = (in_fifo_.io.size > MaxBurst)
                          || ((in_fifo_.io.size == MaxBurst) && (0 == burst_counter));
    auto partial_burst_value = ch_slice<burst_t>(in_fifo_.io.size) - (burst_counter != 0).as_uint();
    auto burst_count_val = ch_sel(full_burst_enable, MaxBurst, partial_burst_value);
    auto burst_count = ch_delayEn(burst_count_val, write_begin);

    // assert the write request until active transaction complete
    __if (write_begin) {
      write_enabled->next = true;
    }__elif (write_granted && (1 == burst_counter)) {
      write_enabled->next = false;
    };

    // track remaining blocks in active write transaction
    __if (write_begin) {
      burst_counter->next = burst_count_val;
    }__elif (write_granted) {
      burst_counter->next = burst_counter - 1;
    };

    // advance the address when a write is granted
    __if (io.start) {
      address->next = io.base_addr;
    }__elif (write_granted) {
      address->next = address + DataB;
    };

    // the device is busy until all requests are submitted
    __if (in_fifo_.io.enq.ready && in_fifo_.io.enq.valid) {
      busy->next = true;
    }__elif (write_granted && (1 == in_fifo_.io.size)) {
      busy->next = false;
    };

    // we have a requet stall when the input queue is full
    ch_reg<ch_uint64> req_stalls(0);
    __if (!in_fifo_.io.enq.ready) {
      req_stalls->next = req_stalls + 1;
    };

    // we have a memory stall when a write is asserted but the Avalon bus is busy
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

    //--
    if constexpr ((ch_width_v<data_type>) < DataW) {
      ch_reg<ch_bit<DataW>> tmp_buf;
      ch_reg<ch_bool> tmp_buf_full(false);

      auto tmp_buf_push = io.enq.valid && io.enq.ready;
      ch_counter<DataPerBlk> counter(tmp_buf_push);
      auto is_last_entry = counter.value() && io.done;
      counter.reset(is_last_entry);

      auto tmp_buf_going_full = (counter.value() == (DataPerBlk-1)) && io.enq.valid;
      auto tmp_buf_flush = (tmp_buf_full || is_last_entry) && in_fifo_.io.enq.ready;

      __if (tmp_buf_going_full) {
        tmp_buf_full->next = true;
      }__elif (tmp_buf_flush) {
        tmp_buf_full->next = false;
      };

      __if (tmp_buf_push) {
        auto value  = ch_resize<DataW>(io.enq.data.as_bit());
        auto offset = ch_resize<LDataW>(counter.value()) * ch_width_v<data_type>;
        tmp_buf->next = ch_sel(0 == counter.value(), value, (value << offset) | tmp_buf);
      };

      io.enq.ready = !tmp_buf_full || in_fifo_.io.enq.ready;
      in_fifo_.io.enq.valid = tmp_buf_flush;
      in_fifo_.io.enq.data = tmp_buf;
      flush = ch_delay(io.done, 1, false);
    } else {
      in_fifo_.io.enq(io.enq);
      flush = io.done;
    }

    //--
    io.busy = busy;

    //--
    io.req_stalls = req_stalls;
    io.mem_stalls = mem_stalls;

    /*__if (ch_clock() && io.enq.valid && io.enq.ready) {
      ch_println("{}: AVMW: enq_data={}", ch_now(), io.enq.data);
    };
    __if (ch_clock()) {
      ch_println("{}: AVMW: wbg={}, wr={}, wrg={}, wtrq={}, ffs={}, addr={}, burst={}, burstctr={}, wdata={}, busy={}",
             ch_now(), write_begin, io.avm.write, write_granted, io.avm.waitrequest, in_fifo_.io.size,
               io.avm.address, io.avm.burstcount, burst_counter, io.avm.writedata, io.busy);
    };*/
  }

private:
  ch_module<ch_queue<ch_bit<DataW>, Qsize>> in_fifo_;
};

}
}
}
