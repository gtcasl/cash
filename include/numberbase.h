#pragma once

#include "bitbase.h"

namespace ch {
namespace internal {

template <typename T>
class ch_snumber_base : public ch_sbit_base<T> {
public:
  using base = ch_sbit_base<T>;
  using base::operator=;

  CH_SYSTEM_OPERATOR2B_IMPL(ch_snumber_base, operator<, do_lt)
  CH_SYSTEM_OPERATOR2B_IMPL(ch_snumber_base, operator<=, do_le)
  CH_SYSTEM_OPERATOR2B_IMPL(ch_snumber_base, operator>, do_gt)
  CH_SYSTEM_OPERATOR2B_IMPL(ch_snumber_base, operator>=, do_ge)

  CH_SYSTEM_OPERATOR1X_IMPL(ch_snumber_base, operator-, do_neg)
  CH_SYSTEM_OPERATOR2X_IMPL(ch_snumber_base, operator+, do_add)
  CH_SYSTEM_OPERATOR2X_IMPL(ch_snumber_base, operator-, do_sub)
  CH_SYSTEM_OPERATOR2X_IMPL(ch_snumber_base, operator*, do_mul)
  CH_SYSTEM_OPERATOR2X_IMPL(ch_snumber_base, operator/, do_div)
  CH_SYSTEM_OPERATOR2X_IMPL(ch_snumber_base, operator%, do_mod)

  CH_SYSTEM_FUNCTION2B_IMPL(ch_snumber_base, ch_lt, do_lt)
  CH_SYSTEM_FUNCTION2B_IMPL(ch_snumber_base, ch_le, do_le)
  CH_SYSTEM_FUNCTION2B_IMPL(ch_snumber_base, ch_gt, do_gt)
  CH_SYSTEM_FUNCTION2B_IMPL(ch_snumber_base, ch_ge, do_ge)

  CH_SYSTEM_FUNCTION1X_IMPL(ch_snumber_base, ch_neg, do_neg)
  CH_SYSTEM_FUNCTION2X_IMPL(ch_snumber_base, ch_add, do_add)
  CH_SYSTEM_FUNCTION2X_IMPL(ch_snumber_base, ch_sub, do_sub)
  CH_SYSTEM_FUNCTION2X_IMPL(ch_snumber_base, ch_mul, do_mul)
  CH_SYSTEM_FUNCTION2X_IMPL(ch_snumber_base, ch_div, do_div)
  CH_SYSTEM_FUNCTION2X_IMPL(ch_snumber_base, ch_mod, do_mod)

protected:

  template <typename U>
  auto do_lt(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    //return make_logic_op<ch_op::lt, ch_signed_v<T>, ch_bool>(*self, other);
    return false;
  }

  template <typename U>
  auto do_le(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    //return make_logic_op<ch_op::le, ch_signed_v<T>, ch_bool>(*self, other);
    return false;
  }

  template <typename U>
  auto do_gt(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    //return make_logic_op<ch_op::gt, ch_signed_v<T>, ch_bool>(*self, other);
    return false;
  }

  template <typename U>
  auto do_ge(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    //return make_logic_op<ch_op::ge, ch_signed_v<T>, ch_bool>(*self, other);
    return false;
  }

  template <typename R>
  auto do_neg() const {
    auto self = reinterpret_cast<const T*>(this);
    //return make_logic_op<ch_op::neg, ch_signed_v<R>, R>(*self);
    return R();
  }

  template <typename R, typename U>
  auto do_add(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    //return make_logic_op<ch_op::add, ch_signed_v<R>, R>(*self, other);
    return R();
  }

  template <typename R, typename U>
  auto do_sub(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    //return make_logic_op<ch_op::sub, ch_signed_v<R>, R>(*self, other);
    return R();
  }

  template <typename R, typename U>
  auto do_mul(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    //return make_logic_op<ch_op::mul, ch_signed_v<R>, R>(*self, other);
    return R();
  }

  template <typename R, typename U>
  auto do_div(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    //return make_logic_op<ch_op::div, ch_signed_v<R>, R>(*self, other);
    return R();
  }

  template <typename R, typename U>
  auto do_mod(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    //return make_logic_op<ch_op::mod, ch_signed_v<R>, R>(*self, other);
    return R();
  }

  template <typename U> friend class ch_snumber_base;
};

CH_SYSTEM_FUNCTION2B_DECL(ch_snumber_base, ch_lt)
CH_SYSTEM_FUNCTION2B_DECL(ch_snumber_base, ch_le)
CH_SYSTEM_FUNCTION2B_DECL(ch_snumber_base, ch_gt)
CH_SYSTEM_FUNCTION2B_DECL(ch_snumber_base, ch_ge)

CH_SYSTEM_FUNCTION1X_DECL(ch_snumber_base, ch_neg)
CH_SYSTEM_FUNCTION2X_DECL(ch_snumber_base, ch_add)
CH_SYSTEM_FUNCTION2X_DECL(ch_snumber_base, ch_sub)
CH_SYSTEM_FUNCTION2X_DECL(ch_snumber_base, ch_mul)
CH_SYSTEM_FUNCTION2X_DECL(ch_snumber_base, ch_div)
CH_SYSTEM_FUNCTION2X_DECL(ch_snumber_base, ch_mod)

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class ch_number_base : public ch_bit_base<T> {
public:
  using base = ch_bit_base<T>;
  using base::operator=;

  CH_LOGIC_OPERATOR2B_IMPL(T, operator<, do_lt)
  CH_LOGIC_OPERATOR2B_IMPL(T, operator<=, do_le)
  CH_LOGIC_OPERATOR2B_IMPL(T, operator>, do_gt)
  CH_LOGIC_OPERATOR2B_IMPL(T, operator>=, do_ge)

  CH_LOGIC_OPERATOR1X_IMPL(T, operator-, do_neg)
  CH_LOGIC_OPERATOR2X_IMPL(T, operator+, do_add)
  CH_LOGIC_OPERATOR2X_IMPL(T, operator-, do_sub)
  CH_LOGIC_OPERATOR2X_IMPL(T, operator*, do_mul)
  CH_LOGIC_OPERATOR2X_IMPL(T, operator/, do_div)
  CH_LOGIC_OPERATOR2X_IMPL(T, operator%, do_mod)

  CH_LOGIC_FUNCTION2B_IMPL(T, ch_lt, do_lt)
  CH_LOGIC_FUNCTION2B_IMPL(T, ch_le, do_le)
  CH_LOGIC_FUNCTION2B_IMPL(T, ch_gt, do_gt)
  CH_LOGIC_FUNCTION2B_IMPL(T, ch_ge, do_ge)

  CH_LOGIC_FUNCTION1X_IMPL(T, ch_neg, do_neg)
  CH_LOGIC_FUNCTION2X_IMPL(T, ch_add, do_add)
  CH_LOGIC_FUNCTION2X_IMPL(T, ch_sub, do_sub)
  CH_LOGIC_FUNCTION2X_IMPL(T, ch_mul, do_mul)
  CH_LOGIC_FUNCTION2X_IMPL(T, ch_div, do_div)
  CH_LOGIC_FUNCTION2X_IMPL(T, ch_mod, do_mod)

protected:

  template <typename U>
  auto do_lt(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<ch_op::lt, ch_signed_v<T>, ch_bool>(*self, other);
  }

  template <typename U>
  auto do_le(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<ch_op::le, ch_signed_v<T>, ch_bool>(*self, other);
  }

  template <typename U>
  auto do_gt(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<ch_op::gt, ch_signed_v<T>, ch_bool>(*self, other);
  }

  template <typename U>
  auto do_ge(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<ch_op::ge, ch_signed_v<T>, ch_bool>(*self, other);
  }

  template <typename R>
  auto do_neg() const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<ch_op::neg, ch_signed_v<R>, R>(*self);
  }

  template <typename R, typename U>
  auto do_add(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<ch_op::add, ch_signed_v<R>, R>(*self, other);
  }

  template <typename R, typename U>
  auto do_sub(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<ch_op::sub, ch_signed_v<R>, R>(*self, other);
  }

  template <typename R, typename U>
  auto do_mul(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<ch_op::mul, ch_signed_v<R>, R>(*self, other);
  }

  template <typename R, typename U>
  auto do_div(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<ch_op::div, ch_signed_v<R>, R>(*self, other);
  }

  template <typename R, typename U>
  auto do_mod(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<ch_op::mod, ch_signed_v<R>, R>(*self, other);
  }

  template <typename U> friend class ch_number_base;
};

CH_LOGIC_FUNCTION2B_DECL(ch_lt)
CH_LOGIC_FUNCTION2B_DECL(ch_le)
CH_LOGIC_FUNCTION2B_DECL(ch_gt)
CH_LOGIC_FUNCTION2B_DECL(ch_ge)

CH_LOGIC_FUNCTION1X_DECL(ch_neg)
CH_LOGIC_FUNCTION2X_DECL(ch_add)
CH_LOGIC_FUNCTION2X_DECL(ch_sub)
CH_LOGIC_FUNCTION2X_DECL(ch_mul)
CH_LOGIC_FUNCTION2X_DECL(ch_div)
CH_LOGIC_FUNCTION2X_DECL(ch_mod)

}}
