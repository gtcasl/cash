#pragma once

#include "logic.h"
#include "select.h"

namespace ch {
namespace internal {

lnodeimpl* createRegNode(const lnode& next, const lnode& init);

lnodeimpl* createRegNode(const lnode& next);

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class ch_reg final : public const_type_t<T> {
public:
  using base = const_type_t<T>;
  using traits = logic_traits<width_v<T>, ch_reg, const_type_t<T>, T, scalar_type_t<T>>;

  T next;

  ch_reg(const source_location& sloc = CH_SRC_LOCATION)
    : base(logic_buffer(width_v<T>, sloc)) {
    auto reg = createRegNode(get_lnode(next));
    logic_accessor::set_data(*this, reg);
    next = *this;
  }

  template <typename U, CH_REQUIRE_0(is_cast_convertible<T, U>::value)>
  explicit ch_reg(const U& init,
                  const source_location& sloc = CH_SRC_LOCATION)
    : base(logic_buffer(width_v<T>, sloc)) {
    auto reg = createRegNode(get_lnode(next), get_lnode<U, T>(init));
    logic_accessor::set_data(*this, reg);
    next = *this;
  }

  ch_reg(ch_reg&& rhs) : base(std::move(rhs)) {}

  ch_reg& operator=(ch_reg&& rhs) {
    base::operator=(std::move(rhs));
    return *this;
  }

protected:

  ch_reg(ch_reg&) = delete;

  ch_reg& operator=(const ch_reg&) = delete;
};

///////////////////////////////////////////////////////////////////////////////

void ch_pushcd(const ch_bit<1>& clock, const ch_bit<1>& reset, bool posedge);

void ch_popcd();

ch_bit<1> ch_clock();

ch_bit<1> ch_reset();

///////////////////////////////////////////////////////////////////////////////

template <typename R, typename T,
          CH_REQUIRE_0(is_cast_convertible<R, T>::value)>
auto ch_delay(const T& rhs, unsigned delay = 1) {
  R ret(rhs);
  for (unsigned i = 0; i < delay; ++i) {
    ret = make_type<R>(createRegNode(get_lnode(ch_clone(ret))));
  }
  return ret;
}

template <typename T,
          CH_REQUIRE_0(is_bit_convertible<T>::value)>
auto ch_delay(const T& rhs, unsigned delay = 1) {
  return ch_delay<logic_value_t<T>, T>(rhs, delay);
}

}
}
