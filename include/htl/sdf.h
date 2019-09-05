#pragma once

#include <cash.h>
#include <htl/queue.h>

namespace ch {
namespace htl {

using namespace ch::logic;

template <typename T, unsigned I=2, unsigned O=2>
struct ch_sdf {
  __io (
    (ch_enq_io<T>) in,
    (ch_deq_io<T>) out,
    (ch_deq_io<T>) deq,
    (ch_enq_io<T>) enq
  );

  void describe() {
    ch_module<ch_llqueue<T, I>> q_in;
    ch_module<ch_llqueue<T, O>> q_out;

    //--
    auto enq_stalled = !io.deq.ready && !q_in.io.deq.valid;
    auto deq_stalled = q_out.io.enq.valid && !q_out.io.enq.ready;

    //--
    q_in.io.enq(io.in);
    q_in.io.deq.ready = !deq_stalled;
    q_out.io.deq(io.out);
    q_out.io.enq.data  = io.enq.data;
    q_out.io.enq.valid = io.enq.valid && !enq_stalled;

    //--
    io.enq.ready = !enq_stalled && !deq_stalled;
    io.deq.data  = q_in.io.deq.data;
    io.deq.valid = q_in.io.deq.ready && q_in.io.deq.valid;
  }
};

}
}
