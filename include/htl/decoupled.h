#pragma once

#include <cash.h>

namespace ch {
namespace htl {

using namespace ch::logic;

template <typename T>
__struct (ch_valid_t, (
  (T) data,
  (ch_bool) valid
));

template <typename T>
__inout (ch_valid_in, (
  __in(T) data,
  __in(ch_bool) valid
));

template <typename T> using ch_valid_out = ch_flip_io<ch_valid_in<T>>;

template <typename T>
__inout (ch_enq_io, ch_valid_in<T>, (
  __out(ch_bool) ready
));

template <typename T> using ch_deq_io = ch_flip_io<ch_enq_io<T>>;

}
}
