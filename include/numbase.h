#pragma once

#include "bitbase.h"

namespace ch {
namespace internal {

CH_SYSTEM_FUNCTION2B_DECL(ch_snumbase, ch_lt)
CH_SYSTEM_FUNCTION2B_DECL(ch_snumbase, ch_le)
CH_SYSTEM_FUNCTION2B_DECL(ch_snumbase, ch_gt)
CH_SYSTEM_FUNCTION2B_DECL(ch_snumbase, ch_ge)

CH_SYSTEM_FUNCTION1X_DECL(ch_snumbase, ch_neg)
CH_SYSTEM_FUNCTION2X_DECL(ch_snumbase, ch_add)
CH_SYSTEM_FUNCTION2X_DECL(ch_snumbase, ch_sub)
CH_SYSTEM_FUNCTION2X_DECL(ch_snumbase, ch_mul)
CH_SYSTEM_FUNCTION2X_DECL(ch_snumbase, ch_div)
CH_SYSTEM_FUNCTION2X_DECL(ch_snumbase, ch_mod)

CH_SYSTEM_FUNCTION2X_DECL(ch_snumbase, ch_min)
CH_SYSTEM_FUNCTION2X_DECL(ch_snumbase, ch_max)
CH_SYSTEM_FUNCTION1X_DECL(ch_snumbase, ch_abs)

template <typename T>
class ch_snumbase : public ch_sbitbase<T> {
public:
  using base = ch_sbitbase<T>;
  using base::operator=;

  CH_SYSTEM_OPERATOR2B_IMPL(ch_snumbase, operator<, do_lt)
  CH_SYSTEM_OPERATOR2B_IMPL(ch_snumbase, operator<=, do_le)
  CH_SYSTEM_OPERATOR2B_IMPL(ch_snumbase, operator>, do_gt)
  CH_SYSTEM_OPERATOR2B_IMPL(ch_snumbase, operator>=, do_ge)

  CH_SYSTEM_OPERATOR1X_IMPL(ch_snumbase, operator-, do_neg)
  CH_SYSTEM_OPERATOR2X_IMPL(ch_snumbase, operator+, do_add)
  CH_SYSTEM_OPERATOR2X_IMPL(ch_snumbase, operator-, do_sub)
  CH_SYSTEM_OPERATOR2X_IMPL(ch_snumbase, operator*, do_mul)
  CH_SYSTEM_OPERATOR2X_IMPL(ch_snumbase, operator/, do_div)
  CH_SYSTEM_OPERATOR2X_IMPL(ch_snumbase, operator%, do_mod)

  CH_SYSTEM_OPERATOR2Z_IMPL(ch_snumbase, operator+=, do_add)
  CH_SYSTEM_OPERATOR2Z_IMPL(ch_snumbase, operator-=, do_sub)
  CH_SYSTEM_OPERATOR2Z_IMPL(ch_snumbase, operator*=, do_mul)
  CH_SYSTEM_OPERATOR2Z_IMPL(ch_snumbase, operator/=, do_div)
  CH_SYSTEM_OPERATOR2Z_IMPL(ch_snumbase, operator%=, do_mod)

  CH_SYSTEM_FUNCTION2B_IMPL(ch_snumbase, ch_lt, do_lt)
  CH_SYSTEM_FUNCTION2B_IMPL(ch_snumbase, ch_le, do_le)
  CH_SYSTEM_FUNCTION2B_IMPL(ch_snumbase, ch_gt, do_gt)
  CH_SYSTEM_FUNCTION2B_IMPL(ch_snumbase, ch_ge, do_ge)

  CH_SYSTEM_FUNCTION1X_IMPL(ch_snumbase, ch_neg, do_neg)
  CH_SYSTEM_FUNCTION2X_IMPL(ch_snumbase, ch_add, do_add)
  CH_SYSTEM_FUNCTION2X_IMPL(ch_snumbase, ch_sub, do_sub)
  CH_SYSTEM_FUNCTION2X_IMPL(ch_snumbase, ch_mul, do_mul)
  CH_SYSTEM_FUNCTION2X_IMPL(ch_snumbase, ch_div, do_div)
  CH_SYSTEM_FUNCTION2X_IMPL(ch_snumbase, ch_mod, do_mod)

  CH_SYSTEM_FUNCTION2X_IMPL(ch_snumbase, ch_min, do_min)
  CH_SYSTEM_FUNCTION2X_IMPL(ch_snumbase, ch_max, do_max)
  CH_SYSTEM_FUNCTION1X_IMPL(ch_snumbase, ch_abs, do_abs)

protected:

  template <typename U>
  auto do_lt(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_system_op<ch_op::lt>(*self, other);
  }

  template <typename U>
  auto do_le(const U& other) const {    
    return !this->do_gt(other);
  }

  template <typename U>
  auto do_gt(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_system_op<ch_op::lt>(other, *self);
  }

  template <typename U>
  auto do_ge(const U& other) const {
    return !this->do_le(other);
  }

  template <typename R>
  auto do_neg() const {
    auto self = reinterpret_cast<const T*>(this);
    return make_system_op<R, ch_op::neg>(*self);
  }

  template <typename R, typename U>
  auto do_add(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_system_op<R, ch_op::add>(*self, other);
  }

  template <typename R, typename U>
  auto do_sub(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_system_op<R, ch_op::sub>(*self, other);
  }

  template <typename R, typename U>
  auto do_mul(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_system_op<R, ch_op::mul>(*self, other);
  }

  template <typename R, typename U>
  auto do_div(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_system_op<R, ch_op::div>(*self, other);
  }

  template <typename R, typename U>
  auto do_mod(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_system_op<R, ch_op::mod>(*self, other);
  }

  template <typename R, typename U>
  auto do_min(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    auto res = (*self < other) ? *self : other;
    if constexpr (ch_width_v<T> == ch_width_v<R>) {
      return res.template as<R>();
    } else {
      return  R(res);
    }
  }

  template <typename R, typename U>
  auto do_max(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    auto res = (*self > other) ? *self : other;
    if constexpr (ch_width_v<T> == ch_width_v<R>) {
      return res.template as<R>();
    } else {
      return  R(res);
    }
  }

  template <typename R>
  auto do_abs() const {
    auto& self = *reinterpret_cast<const T*>(this);
    T res;
    if constexpr (is_signed_v<T>) {
      res = self[ch_width_v<T>-1] ? -self : self;
    } else {
      res = self;
    }
    if constexpr (ch_width_v<T> == ch_width_v<R>) {
      return res.template as<R>();
    } else {
      return R(res);
    }
  }

  friend class system_accessor;
};

///////////////////////////////////////////////////////////////////////////////

CH_LOGIC_FUNCTION2B_DECL(ch_numbase, ch_lt)
CH_LOGIC_FUNCTION2B_DECL(ch_numbase, ch_le)
CH_LOGIC_FUNCTION2B_DECL(ch_numbase, ch_gt)
CH_LOGIC_FUNCTION2B_DECL(ch_numbase, ch_ge)

CH_LOGIC_FUNCTION1X_DECL(ch_numbase, ch_neg)
CH_LOGIC_FUNCTION2X_DECL(ch_numbase, ch_add)
CH_LOGIC_FUNCTION2X_DECL(ch_numbase, ch_sub)
CH_LOGIC_FUNCTION2X_DECL(ch_numbase, ch_mul)
CH_LOGIC_FUNCTION2X_DECL(ch_numbase, ch_div)
CH_LOGIC_FUNCTION2X_DECL(ch_numbase, ch_mod)

CH_LOGIC_FUNCTION2X_DECL(ch_numbase, ch_min)
CH_LOGIC_FUNCTION2X_DECL(ch_numbase, ch_max)
CH_LOGIC_FUNCTION1X_DECL(ch_numbase, ch_abs)

template <typename T>
class ch_numbase : public ch_bitbase<T> {
public:
  using base = ch_bitbase<T>;
  using base::operator=;

  CH_LOGIC_OPERATOR2B_IMPL(ch_numbase, operator<, do_lt)
  CH_LOGIC_OPERATOR2B_IMPL(ch_numbase, operator<=, do_le)
  CH_LOGIC_OPERATOR2B_IMPL(ch_numbase, operator>, do_gt)
  CH_LOGIC_OPERATOR2B_IMPL(ch_numbase, operator>=, do_ge)

  CH_LOGIC_OPERATOR1X_IMPL(ch_numbase, operator-, do_neg)
  CH_LOGIC_OPERATOR2X_IMPL(ch_numbase, operator+, do_add)
  CH_LOGIC_OPERATOR2X_IMPL(ch_numbase, operator-, do_sub)
  CH_LOGIC_OPERATOR2X_IMPL(ch_numbase, operator*, do_mul)
  CH_LOGIC_OPERATOR2X_IMPL(ch_numbase, operator/, do_div)
  CH_LOGIC_OPERATOR2X_IMPL(ch_numbase, operator%, do_mod)

  CH_LOGIC_OPERATOR2Z_IMPL(ch_numbase, operator+=, do_add)
  CH_LOGIC_OPERATOR2Z_IMPL(ch_numbase, operator-=, do_sub)
  CH_LOGIC_OPERATOR2Z_IMPL(ch_numbase, operator*=, do_mul)
  CH_LOGIC_OPERATOR2Z_IMPL(ch_numbase, operator/=, do_div)
  CH_LOGIC_OPERATOR2Z_IMPL(ch_numbase, operator%=, do_mod)

  CH_LOGIC_FUNCTION2B_IMPL(ch_numbase, ch_lt, do_lt)
  CH_LOGIC_FUNCTION2B_IMPL(ch_numbase, ch_le, do_le)
  CH_LOGIC_FUNCTION2B_IMPL(ch_numbase, ch_gt, do_gt)
  CH_LOGIC_FUNCTION2B_IMPL(ch_numbase, ch_ge, do_ge)

  CH_LOGIC_FUNCTION1X_IMPL(ch_numbase, ch_neg, do_neg)
  CH_LOGIC_FUNCTION2X_IMPL(ch_numbase, ch_add, do_add)
  CH_LOGIC_FUNCTION2X_IMPL(ch_numbase, ch_sub, do_sub)
  CH_LOGIC_FUNCTION2X_IMPL(ch_numbase, ch_mul, do_mul)
  CH_LOGIC_FUNCTION2X_IMPL(ch_numbase, ch_div, do_div)
  CH_LOGIC_FUNCTION2X_IMPL(ch_numbase, ch_mod, do_mod)

  CH_LOGIC_FUNCTION2X_IMPL(ch_numbase, ch_min, do_min)
  CH_LOGIC_FUNCTION2X_IMPL(ch_numbase, ch_max, do_max)
  CH_LOGIC_FUNCTION1X_IMPL(ch_numbase, ch_abs, do_abs)

protected:

  template <typename U>
  auto do_lt(const U& other, const source_info& sloc) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<ch_op::lt>(*self, other, sloc);
  }

  template <typename U>
  auto do_le(const U& other, const source_info& sloc) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<ch_op::le>(*self, other, sloc);
  }

  template <typename U>
  auto do_gt(const U& other, const source_info& sloc) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<ch_op::gt>(*self, other, sloc);
  }

  template <typename U>
  auto do_ge(const U& other, const source_info& sloc) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<ch_op::ge>(*self, other, sloc);
  }

  template <typename R>
  auto do_neg(const source_info& sloc) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<R, ch_op::neg>(*self, sloc);
  }

  template <typename R, typename U>
  auto do_add(const U& other, const source_info& sloc) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<R, ch_op::add>(*self, other, sloc);
  }

  template <typename R, typename U>
  auto do_sub(const U& other, const source_info& sloc) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<R, ch_op::sub>(*self, other, sloc);
  }

  template <typename R, typename U>
  auto do_mul(const U& other, const source_info& sloc) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<R, ch_op::mul>(*self, other, sloc);
  }

  template <typename R, typename U>
  auto do_div(const U& other, const source_info& sloc) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<R, ch_op::div>(*self, other, sloc);
  }

  template <typename R, typename U>
  auto do_mod(const U& other, const source_info& sloc) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<R, ch_op::mod>(*self, other, sloc);
  }

  template <typename R, typename U>
  auto do_min(const U& other, const source_info& sloc) const {
    auto self = reinterpret_cast<const T*>(this);
    auto res = ch_sel(*self < other, *self, other, sloc);
    if constexpr (ch_width_v<T> == ch_width_v<R>) {
      return res.template as<R>();
    } else {
      return R(res, sloc);
    }
  }

  template <typename R, typename U>
  auto do_max(const U& other, const source_info& sloc) const {
    auto self = reinterpret_cast<const T*>(this);
    auto res = ch_sel(*self > other, *self, other, sloc);
    if constexpr (ch_width_v<T> == ch_width_v<R>) {
      return res.template as<R>();
    } else {
      return R(res, sloc);
    }
  }

  template <typename R>
  auto do_abs(const source_info& sloc) const {
    auto& self = *reinterpret_cast<const T*>(this);
    T res;
    if constexpr (is_signed_v<T>) {
      res = ch_sel(self[ch_width_v<T>-1], -self, self, sloc);
    } else {
      res = self;
    }
    if constexpr (ch_width_v<T> == ch_width_v<R>) {
      return res.template as<R>();
    } else {
      return R(res, sloc);
    }
  }

  friend class logic_accessor;
};

}}
