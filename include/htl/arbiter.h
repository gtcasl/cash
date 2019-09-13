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
    ch_vec<ch_vec<ch_bool, N>, N> fill_ones(ch_vec<ch_bool, N>(true));
    ch_reg<ch_vec<ch_vec<ch_bool, N>, N>> priority(fill_ones);

    for (unsigned i = 0; i < N; ++i) {
      ch_bit<N> dis;
      for (unsigned j = 0; j < N; ++j) {
        if (j > i) {
          dis[j] = io.in[j] & priority[j][i];
        } else if (j < i) {
          dis[j] = io.in[j] & ~priority[i][j];
        } else {
          dis[j] = false;
        }
      }
      auto g = io.in[i] & ~ch_orr(dis);
      __if (g) {
        for (unsigned j = 0; j < N; ++j) {
          if (j > i) {
            priority->next[j][i] = true;
          } else if (j < i) {
            priority->next[i][j] = false;
          }
        }
      };
      io.grant[i] = g;
    }
  }
};

template <unsigned N>
struct ch_ctrArbiter {
  __io (
    __in (ch_bit<N>)  in,
    __out (ch_bit<N>) grant
  );

  void describe() {
    ch_counter<N> ctr;
    io.grant = io.in & (ch_bit<N>(1) << ctr.value());
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
      arb.io.in[i]        = io.in[i].valid;
    }

    io.out.data  = xbar.io.out[0].data;
    io.out.valid = xbar.io.out[0].valid;
    xbar.io.sel  = arb.io.grant;

    for (unsigned i = 0; i < I; ++i) {
      io.in[i].ready = io.out.ready && arb.io.grant[i];
    }

    io.grant = arb.io.grant;
  }  
};

}
}
