#pragma once

#include "bit.h"

namespace ch {
namespace internal {

class reg_buffer : public logic_buffer {
public:
  using logic_buffer::value_;

  explicit reg_buffer(uint32_t size,
                      const source_location& sloc);

  explicit reg_buffer(const lnode& data,
                      const source_location& sloc);

  void write(uint32_t dst_offset,
             const lnode& data,
             uint32_t src_offset,
             uint32_t length,
             const source_location& sloc) override;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class ch_reg_impl final : public T {
public:  
  using traits = logic_traits<width_v<T>, signed_v<T>, ch_reg<T>, scalar_type_t<T>>;
  using base = T;

  ch_reg_impl(CH_SLOC)
    : base(std::make_shared<reg_buffer>(width_v<T>, sloc))
  {}

  ch_reg_impl(const ch_reg_impl& rhs, CH_SLOC)
    : base(std::make_shared<reg_buffer>(logic_accessor::data(rhs), sloc))
  {}

  ch_reg_impl(ch_reg_impl&& rhs) : base(std::move(rhs.buffer_)) {}

  template <typename... Args,
            CH_REQUIRE_0(std::is_constructible_v<T, Args...>)>
  ch_reg_impl(const Args&... args)
    : base(std::make_shared<reg_buffer>(logic_accessor::data(T(args...)),
                                        source_location()))
  {}

  template <typename U>
  void operator <<=(const U& rhs) const {
    static_assert(std::is_constructible_v<T, U>, "invalid type");
    this->buffer()->write(0, to_lnode<T>(rhs, source_location()), 0, width_v<T>,
                          source_location());
  }  
};

///////////////////////////////////////////////////////////////////////////////

ch_bit<1> ch_clock(CH_SLOC);

ch_bit<1> ch_reset(CH_SLOC);

void ch_pushcd(const ch_bit<1>& clk,
               const ch_bit<1>& reset = ch_reset(),
               bool posedge = true,
               CH_SLOC);

void ch_popcd();

///////////////////////////////////////////////////////////////////////////////

template <typename R, typename T>
auto ch_delay(const T& rhs, uint32_t delay = 1, CH_SLOC) {
  static_assert(is_logic_type_v<R>, "invalid type");
  static_assert(std::is_constructible_v<R, T>, "invalid type");
  R ret(rhs, sloc);
  for (unsigned i = 0; i < delay; ++i) {
    ch_reg<R> reg(sloc);
    reg <<= ch_clone(ret, sloc);
    ret = reg;
  }
  return ret;
}

template <typename T>
auto ch_delay(const T& rhs, uint32_t delay = 1, CH_SLOC) {
  static_assert(is_object_type_v<T>, "invalid type");
  return ch_delay<logic_type_t<T>, T>(rhs, delay, sloc);
}

}
}
