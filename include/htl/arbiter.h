#pragma once

#include <cash.h>
#include <htl/decoupled.h>
#include <htl/counter.h>
#include <htl/xbar.h>
#include <htl/onehot.h>

namespace ch {
namespace htl {

using namespace ch::logic;

template <unsigned N>
struct ch_matArbiter {
  __io (
    __in (ch_bit<N>)  in,
    __out (ch_bit<N>) grant
  );

  void describe() {
    ch_bit<N*N> state(0);
    ch_bit<N> dis[N], grant;
    for (unsigned i = 0; i < N; ++i) {
      for (unsigned j = 0; j < i; ++j) {
        dis[j][i] = io.in[i] & ~state[j*N+i];
      }
      dis[i][i] = 0;
      for (unsigned j = i + 1; j < N; ++j) {
        dis[j][i] = io.in[i] & state[i*N+j];
      }
      grant[i] = io.in[i] & ~ch_orr(dis[i]);
      for (unsigned j = i + 1; j < N; ++j) {
        state[i*N+j] = ch_next((state[i*N+j] | grant[j]) & ~grant[i]);
      }
    }
    io.grant = grant;
  }
};

template <unsigned N>
struct ch_ctrArbiter {
  __io (
    __in (ch_bit<N>)  in,
    __out (ch_bit<N>) grant
  );

  void describe() {
    ch_counter<N> ctr(0);
    io.grant = ch_bit<N>(1) << ctr.value();
  }
};

template <typename T, unsigned I, typename Arbiter = ch_matArbiter<I>>
struct ch_xbar_switch {
  using value_type   = T;
  using arbiter_type = Arbiter;
  using in_io  = ch_vec<ch_enq_io<T>, I>;
  using out_io = ch_deq_io<T>;
    
  __io (
    (in_io)  in,
    (out_io) out,
    __out (ch_bit<I>) grant
  );

  void describe() {
    ch_module<ch_hxbar<ch_valid_t<T>, I, 1>> xbar;
    ch_module<Arbiter> arb;

    for (unsigned i = 0; i < I; ++i) {
      xbar.io.in[i].data  = io.in[i].data;
      xbar.io.in[i].valid = io.in[i].valid;
      arb.io.in[i]        = io.in[i].valid && io.out.ready;
    }

    io.out.data  = xbar.io.out[0].data;
    io.out.valid = xbar.io.out[0].valid;
    xbar.io.sel  = arb.io.grant;

    for (unsigned i = 0; i < I; ++i) {
      io.in[i].ready = io.out.ready && (arb.io.grant == (1 << i));
    }

    io.grant = arb.io.grant;
  }  
};

}
}
