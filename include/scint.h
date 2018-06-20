#pragma once

#include "scalar.h"

namespace ch {
namespace internal {

template <typename Derived>
class ch_scalar_integer : public ch_scalar_base<Derived> {
public:
  using base = ch_scalar_base<Derived>;
  using base::buffer_;
  using base::base;

  // relational operators

  friend auto operator<(const Derived& lhs, const Derived& rhs) {
    return (lhs.buffer_->data() < rhs.buffer_->data());
  }

  friend auto operator>=(const Derived& lhs, const Derived& rhs) {
    return (lhs.buffer_->data() >= rhs.buffer_->data());
  }

  friend auto operator>(const Derived& lhs, const Derived& rhs) {
    return (lhs.buffer_->data() > rhs.buffer_->data());
  }

  friend auto operator<=(const Derived& lhs, const Derived& rhs) {
    return (lhs.buffer_->data() <= rhs.buffer_->data());
  }

  // arithmetic operators

  auto operator-() const {
    return make_scalar_op(*this, Neg);
  }

  friend auto operator+(const Derived& lhs, const Derived& rhs) {
    return make_scalar_op(lhs, rhs, Add);
  }

  friend auto operator-(const Derived& lhs, const Derived& rhs) {
    return make_scalar_op(lhs, rhs, Sub);
  }

  friend auto operator*(const Derived& lhs, const Derived& rhs) {
    return make_scalar_op(lhs, rhs, Mult);
  }

  friend auto operator/(const Derived& lhs, const Derived& rhs) {
    return make_scalar_op(lhs, rhs, Div);
  }

  friend auto operator%(const Derived& lhs, const Derived& rhs) {
    return make_scalar_op(lhs, rhs, Mod);
  }
};

template <unsigned N>
class ch_scint : public ch_scalar_integer<ch_scint<N>> {
public:
  using traits = scalar_traits<N, true, ch_scint, ch_int<N>>;
  using base = ch_scalar_integer<ch_scint>;

  ch_scint(const scalar_buffer_ptr& buffer = make_scalar_buffer(N))
    : base(buffer)
  {}

  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  ch_scint(const U& rhs) : base(rhs) {}

  ch_scint(const ch_scbit<N>& rhs) : base(rhs) {}

  template <unsigned M,
            CH_REQUIRE_0(M < N)>
  ch_scint(const ch_scint<M>& rhs) : base(rhs.template pad<N>()) {}

  template <typename T>
  explicit ch_scint(const ch_scalar_base<T>& rhs) : base(rhs) {}

  ch_scint(const ch_scint& rhs) : base(rhs) {}

  ch_scint(ch_scint&& rhs) : base(std::move(rhs)) {}

  ch_scint& operator=(const ch_scint& rhs) {
    base::operator=(rhs);
    return *this;
  }

  ch_scint& operator=(ch_scint&& rhs) {
    base::operator=(std::move(rhs));
    return *this;
  }
};

}
}
