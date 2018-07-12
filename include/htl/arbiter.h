#pragma once

#include <cash.h>
#include <htl/decoupled.h>
#include <htl/counter.h>

namespace ch {
namespace htl {

using namespace ch::core;

template <unsigned N>
struct ch_rrArbiter {
  __io (
    __in(ch_vec<ch_bool, N>) in,
    __out(ch_bit<N>) grant
  );

  void describe() {
    ch_reg<ch_bit<N*N>> state(0);
    ch_bit<N> dis[N], grant;
    for (unsigned i = 0; i < N; ++i) {
      for (unsigned j = 0; j < i; ++j) {
        dis[j][i] = io.in[i] && ~state[j*N+i];
      }
      dis[i][i] = 0;
      for (unsigned j = i + 1; j < N; ++j) {
        dis[j][i] = io.in[i] && state[i*N+j];
      }
      grant[i] = io.in[i] && ~ch_orr(dis[i]);
      for (unsigned j = i + 1; j < N; ++j) {
        state->next[i*N+j] = (state[i*N+j] || grant[j]) && ~grant[i];
      }
    }
    io.grant = grant;
  }
};

template <typename T, unsigned I, typename Arbiter = ch_rrArbiter<I>>
struct ch_xbar_switch {
  using value_type = T;
  using arbiter_type = Arbiter;
  using in_io = ch_vec<ch_enq_io<T>, I>;
  __inout (out_io, ch_deq_io<T>, (
    __out(ch_bit<I>) grant
  ));
  __io (
    (in_io)  in,
    (out_io) out
  );
  void describe() {
    auto grant = ch_bit<I>(1) << ch_counter<I>(io.out.ready);
    for (unsigned i = 0; i < I; ++i) {
      xbar_.io.in[i].data  = io.in[i].data;
      xbar_.io.in[i].valid = io.in[i].valid;
      arb_.io.in[i]        = io.in[i].valid;
    }
    io.out.data  = xbar_.io.out[0].data;
    io.out.valid = xbar_.io.out[0].valid;
    xbar_.io.sel = arb_.io.grant;
    for (unsigned i = 0; i < I; ++i) {
      io.in[i].ready = io.out.ready && (arb_.io.grant == (1 << i));
    }
    io.out.grant = arb_.io.grant;
  }
private:
  __struct (xb_data_t, (
    (T) data,
    (ch_bool) valid
  ));
  ch_module<ch_hxbar<xb_data_t, I, 1>> xbar_;
  ch_module<Arbiter> arb_;
};

}
}
