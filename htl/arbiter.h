#pragma once

#include <cash.h>

namespace ch {
namespace htl {

using namespace ch::core;

template <unsigned N>
struct ch_rrArbiter {
  __io (
    __in(ch_vec<ch_bool, N>) in,
    __out(ch_bit<N>) out
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
    io.out = grant;
  }
};

}
}
