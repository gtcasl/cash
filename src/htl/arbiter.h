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
    ch_seq<ch_bool> state[N][N];
    ch_bit<N> dis[N];
    ch_bit<N> grant;

    for (int i = 0; i < N; ++i) {
      for (int j = i + 1; j < N; ++j) {
        dis[j][i] = state[i][j] && io.in[i];
      }
      dis[i][i] = 0;
      for(int j = 0; j < i; ++j) {
        dis[j][i] = (~state[j][i]) && io.in[i];
      }
      grant[i] = io.in[i] && ~ch_orr(dis[i]);
      for (int j = i + 1; j < N; ++j) {
        state[i][j].next = (state[i][j] || grant[j]) && ~grant[i];
      }
    }
    io.grant = grant;
  }
};

template <typename T, unsigned I, typename Arbiter = ch_rrArbiter<I>>
struct ch_arbiter {
  using in_io = ch_vec<ch_deq_io<T>, I>;
  __inout (out_io, ch_enq_io<T>, (
    __out(ch_bit<I>) grant
  ));
  __io (
    (in_io)  in,
    (out_io) out
  );
  void describe() {
    auto grant = ch_bit<I>(1) << (ch_counter<I>(io.out.ready));
    for (int i = 0; i < I; ++i) {
      xbar_.io.in[i].data  = io.in[i].data;
      xbar_.io.in[i].valid = io.in[i].valid;
      arb_.io.in[i]        = io.in[i].valid;
    }
    io.out.data  = xbar_.io.out[0].data;
    io.out.valid = xbar_.io.out[0].valid;
    xbar_.io.sel = arb_.io.grant;
    for (int i = 0; i < I; ++i) {
      io.in[i].ready = io.out.ready && (arb_.io.grant == (1 << i));
    }
    io.out.grant = arb_.io.grant;
  }
  ch_module<ch_hxbar<ch_logic_t<ch_valid_io<T>>, I, 1>> xbar_;
  ch_module<Arbiter> arb_;
};

}
}