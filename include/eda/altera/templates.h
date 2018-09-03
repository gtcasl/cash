#pragma once

#include <cash.h>
#include <htl/queue.h>
#include <htl/decoupled.h>

namespace eda {
namespace altera {

struct half_cplx_mult {
__io (
    __in(ch_bool)    en,
    __in(ch_int<18>) a0,
    __in(ch_int<18>) b0,
    __in(ch_int<18>) a1,
    __in(ch_int<18>) b1,
    __in(ch_int<36>) rout,
    __in(ch_int<36>) iout
);

  void describe() {

  }
};



}
}
