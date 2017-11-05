#pragma once

#include <cash.h>
#include <../htl/mux.h>

namespace ch {
namespace htl {

using namespace ch::core;

template <typename T, unsigned I, unsigned O>
struct ch_hxbar {
  __io(
    __in(ch_bit<I * O>) sel,
    __in(ch_vec<T, I>)  in,
    __out(ch_vec<T, O>) out
  );
  void describe() {
    for (int i = 0; i < O; ++i) {
      io.out[i] = ch_hmux(ch_slice<I>(io.sel, i * I), io.in);
    }
  }
};

}
}
