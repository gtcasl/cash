#pragma once

#include "logic.h"

namespace ch {
namespace internal {

template <typename Derived>
class ch_logic_integer : public ch_logic_base<Derived> {
public:
  using base = ch_logic_base<Derived>;
  using base::buffer_;
  using base::base;

  // compare operators

  friend auto operator<(Derived lhs, const Derived& rhs) {
    auto sloc = logic_accessor::sloc(lhs);
    return make_logic_op<op_lt, ch_bit<1>>(lhs, rhs, sloc);
  }

  friend auto operator<=(Derived lhs, const Derived& rhs) {
    auto sloc = logic_accessor::sloc(lhs);
    return make_logic_op<op_le, ch_bit<1>>(lhs, rhs, sloc);
  }

  friend auto operator>(Derived lhs, const Derived& rhs) {
    auto sloc = logic_accessor::sloc(lhs);
    return make_logic_op<op_gt, ch_bit<1>>(lhs, rhs, sloc);
  }

  friend auto operator>=(Derived lhs, const Derived& rhs) {
    auto sloc = logic_accessor::sloc(lhs);
    return make_logic_op<op_ge, ch_bit<1>>(lhs, rhs, sloc);
  }

  // arithmetic operators

  auto operator-() const {
    return make_logic_op<op_neg>(*this);
  }

  friend auto operator+(Derived lhs, const Derived& rhs) {
    auto sloc = logic_accessor::sloc(lhs);
    return make_logic_op<op_add>(lhs, rhs, sloc);
  }

  friend auto operator-(Derived lhs, const Derived& rhs) {
    auto sloc = logic_accessor::sloc(lhs);
    return make_logic_op<op_sub>(lhs, rhs, sloc);
  }

  friend auto operator*(Derived lhs, const Derived& rhs) {
    auto sloc = logic_accessor::sloc(lhs);
    return make_logic_op<op_mult>(lhs, rhs, sloc);
  }

  friend auto operator/(Derived lhs, const Derived& rhs) {
    auto sloc = logic_accessor::sloc(lhs);
    return make_logic_op<op_div>(lhs, rhs, sloc);
  }

  friend auto operator%(Derived lhs, const Derived& rhs) {
    auto sloc = logic_accessor::sloc(lhs);
    return make_logic_op<op_mod>(lhs, rhs, sloc);
  }
};

template <unsigned N>
class ch_int : public ch_logic_integer<ch_int<N>> {
public:
  using traits = logic_traits<N, true, ch_int, ch_scint<N>>;
  using base = ch_logic_integer<ch_int>;

  ch_int(const logic_buffer_ptr& buffer = make_logic_buffer(N, CH_CUR_SLOC))
    : base(buffer)
  {}

  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  ch_int(const U& rhs, CH_SLOC) : base(rhs, sloc) {}

  template <typename U>
  ch_int(const ch_scalar_base<U>& rhs, CH_SLOC) : base(rhs, sloc) {}

  template <unsigned M,
            CH_REQUIRE_0(M < N)>
  ch_int(const ch_int<M>& rhs, CH_SLOC) : base(rhs.template pad<N>(), sloc) {}

  template <typename U>
  explicit ch_int(const ch_logic_base<U>& rhs, CH_SLOC) : base(rhs, sloc) {}

  ch_int(const ch_int& rhs, CH_SLOC) : base(rhs, sloc) {}

  ch_int(ch_int&& rhs) : base(std::move(rhs)) {}

  ch_int& operator=(const ch_int& rhs) {
    base::operator=(rhs);
    return *this;
  }

  ch_int& operator=(ch_int&& rhs) {
    base::operator=(std::move(rhs));
    return *this;
  }
};

// compare operators

template <typename T>
inline auto ch_lt(const ch_logic_integer<T>& lhs, const ch_logic_integer<T>& rhs, CH_SLOC) {
  return make_logic_op<op_lt, ch_bit<1>>(lhs, rhs, sloc);
}

template <typename T>
inline auto ch_le(const ch_logic_integer<T>& lhs, const ch_logic_integer<T>& rhs, CH_SLOC) {
  return make_logic_op<op_le, ch_bit<1>>(lhs, rhs, sloc);
}

template <typename T>
inline auto ch_gt(const ch_logic_integer<T>& lhs, const ch_logic_integer<T>& rhs, CH_SLOC) {
  return make_logic_op<op_gt, ch_bit<1>>(lhs, rhs, sloc);
}

template <typename T>
inline auto ch_ge(const ch_logic_integer<T>& lhs, const ch_logic_integer<T>& rhs, CH_SLOC) {
  return make_logic_op<op_ge, ch_bit<1>>(lhs, rhs, sloc);
}

// arithmetic operators

template <typename T>
auto ch_neg(const ch_logic_integer<T>& in, CH_SLOC) {
  return make_logic_op<op_neg, T>(in, sloc);
}

template <typename T>
inline auto ch_add(const ch_logic_integer<T>& lhs, const ch_logic_integer<T>& rhs, CH_SLOC) {
  return make_logic_op<op_add, T>(lhs, rhs, sloc);
}

template <typename T>
inline auto ch_sub(const ch_logic_integer<T>& lhs, const ch_logic_integer<T>& rhs, CH_SLOC) {
  return make_logic_op<op_sub, T>(lhs, rhs, sloc);
}

template <typename T>
inline auto ch_mult(const ch_logic_integer<T>& lhs, const ch_logic_integer<T>& rhs, CH_SLOC) {
  return make_logic_op<op_mult, T>(lhs, rhs, sloc);
}

template <typename T>
inline auto ch_div(const ch_logic_integer<T>& lhs, const ch_logic_integer<T>& rhs, CH_SLOC) {
  return make_logic_op<op_div, T>(lhs, rhs, sloc);
}

}}
