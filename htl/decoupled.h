#pragma once

#include <cash.h>

namespace ch {
namespace htl {

using namespace ch::core;

template <typename T>
__inout (ch_validIO, (
  __out(ch_bool) valid,
  __out(T)       data
));

template <typename T>
__inout (ch_decoupledIO, (
  __in(ch_bool)  ready,
  __out(ch_bool) valid,
  __out(T)       data
));

// producer driven input stream
template <typename T> using ch_enqIO = ch_decoupledIO<T>;

// producer driven output stream
template <typename T> using ch_deqIO = ch_flip_t<ch_decoupledIO<T>>;

}
}
