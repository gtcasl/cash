#pragma once

#include "logic.h"

namespace ch {
namespace internal {

class reg_buffer : public logic_buffer {
public:
  using logic_buffer::value_;

  explicit reg_buffer(uint32_t size,
                      const source_location& sloc = source_location(),
                      const std::string& name = "");

  explicit reg_buffer(const lnode& data,
                      const source_location& sloc = source_location(),
                      const std::string& name = "");

  void write(uint32_t dst_offset,
             const lnode& data,
             uint32_t src_offset,
             uint32_t length) override;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class ch_reg_impl final : public T {
public:  
  using traits = logic_traits<width_v<T>, signed_v<T>, ch_reg<T>, scalar_type_t<T>>;
  using base = T;

  ch_reg_impl(const source_location& sloc = CH_SRC_LOCATION)
    : base(std::make_shared<reg_buffer>(width_v<T>, sloc))
  {}

  ch_reg_impl(const ch_reg_impl& rhs, const source_location& sloc = CH_SRC_LOCATION)
    : base(std::make_shared<reg_buffer>(logic_accessor::data(rhs), sloc))
  {}

  ch_reg_impl(ch_reg_impl&& rhs) : base(std::move(rhs.buffer_)) {}

  template <typename U,
            CH_REQUIRE_0(std::is_constructible_v<T, U>)>
  explicit ch_reg_impl(const U& init, const source_location& sloc = CH_SRC_LOCATION)
    : base(std::make_shared<reg_buffer>(get_lnode<U, T>(init), sloc))
  {}

  template <typename U,
            CH_REQUIRE_0(std::is_constructible_v<T, U>)>
  void operator <<=(const U& rhs) const {
    logic_accessor::buffer(*this)->write(get_lnode<U, T>(rhs));
  }
};

///////////////////////////////////////////////////////////////////////////////

ch_logic<1> ch_clock(const source_location& sloc = CH_SRC_LOCATION);

ch_logic<1> ch_reset(const source_location& sloc = CH_SRC_LOCATION);

void ch_pushcd(const ch_logic<1>& clk,
               const ch_logic<1>& rst = ch_reset(),
               bool posedge = true,
               const source_location& sloc = CH_SRC_LOCATION);

void ch_popcd();

///////////////////////////////////////////////////////////////////////////////

template <typename R, typename T,
          CH_REQUIRE_0(std::is_constructible_v<R, T>)>
auto ch_delay(const T& rhs, uint32_t delay = 1, const source_location& sloc = CH_SRC_LOCATION) {
  R ret(rhs, sloc);
  for (unsigned i = 0; i < delay; ++i) {
    ch_reg<R> reg(sloc);
    reg <<= ch_clone(ret, sloc);
    ret = reg;
  }
  return ret;
}

template <typename T,
          CH_REQUIRE_0(is_logic_convertible_v<T>)>
auto ch_delay(const T& rhs, uint32_t delay = 1, const source_location& sloc = CH_SRC_LOCATION) {
  return ch_delay<logic_type_t<T>, T>(rhs, delay, sloc);
}

}
}
