#pragma once

#include <cash.h>

namespace ch {
namespace htl {

using namespace ch::logic;

template <typename T = void>
__struct (ch_valid_t, (
  (T) data,
  (ch_bool) valid
));

namespace detail {
  __struct (ch_valid_void, (
    (ch_bool) valid
  ));
}

template <>
struct ch_valid_t<void> : public detail::ch_valid_void {
  using base = detail::ch_valid_void;
  using base::ch_valid_void;
  using base::operator=;

  ch_valid_t(const ch_valid_t& other) : base(other) {}
  
  ch_valid_t(ch_valid_t&& other) : base(std::move(other)) {}

  ch_valid_t& operator=(const ch_valid_t& other)  { 
    base::operator=(other);
    return *this;
  }

  ch_valid_t& operator=(ch_valid_t&& other)  {
    base::operator=(std::move(other));
    return *this;
  }
};

template <typename T = void>
using ch_valid_in = ch_in<ch_valid_t<T>>;

template <typename T = void>
__inout (ch_enq_io, ch_valid_in<T>, (
  __out (ch_bool) ready
));

template <typename T = void> using ch_valid_out = ch_flip_io<ch_valid_in<T>>;

template <typename T = void> using ch_deq_io = ch_flip_io<ch_enq_io<T>>;

}
}
