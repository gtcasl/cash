#pragma once

#include <cash.h>

namespace ch {
namespace htl {

using namespace ch::core;

template <typename T>
__inout (ch_valid_io, (      
  __out(T) data,
  __out(ch_bool) valid
));

template <typename T>
__inout (ch_decoupled_io, ch_valid_io<T>, (
  __in(ch_bool) ready
));

// producer driven input stream
template <typename T> using ch_enq_io = ch_decoupled_io<T>;

// producer driven output stream
template <typename T> using ch_deq_io = ch_flip_t<ch_decoupled_io<T>>;

}
}
