#pragma once

#include "bit.h"

namespace ch {
namespace internal {

template <typename T>
class ch_number_base : public ch_bit_base<T> {
public:
  using base = ch_bit_base<T>;
  using base::operator=;

  CH_LOGIC_OPERATOR2_IMPL(T, ch_op::lt, operator<, do_lt)
  CH_LOGIC_OPERATOR2_IMPL(T, ch_op::le, operator<=, do_le)
  CH_LOGIC_OPERATOR2_IMPL(T, ch_op::gt, operator>, do_gt)
  CH_LOGIC_OPERATOR2_IMPL(T, ch_op::ge, operator>=, do_ge)

  CH_LOGIC_OPERATOR1_IMPL(T, ch_op::neg, operator-, do_neg)
  CH_LOGIC_OPERATOR2_IMPL(T, ch_op::add, operator+, do_add)
  CH_LOGIC_OPERATOR2_IMPL(T, ch_op::sub, operator-, do_sub)
  CH_LOGIC_OPERATOR2_IMPL(T, ch_op::mul, operator*, do_mul)
  CH_LOGIC_OPERATOR2_IMPL(T, ch_op::div, operator/, do_div)
  CH_LOGIC_OPERATOR2_IMPL(T, ch_op::mod, operator%, do_mod)

  CH_LOGIC_FUNCTION2_IMPL(T, ch_op::lt, ch_lt, do_lt)
  CH_LOGIC_FUNCTION2_IMPL(T, ch_op::le, ch_le, do_le)
  CH_LOGIC_FUNCTION2_IMPL(T, ch_op::gt, ch_gt, do_gt)
  CH_LOGIC_FUNCTION2_IMPL(T, ch_op::ge, ch_ge, do_ge)

  CH_LOGIC_FUNCTION1_IMPL(T, ch_op::neg, ch_neg, do_neg)
  CH_LOGIC_FUNCTION2_IMPL(T, ch_op::add, ch_add, do_add)
  CH_LOGIC_FUNCTION2_IMPL(T, ch_op::sub, ch_sub, do_sub)
  CH_LOGIC_FUNCTION2_IMPL(T, ch_op::mul, ch_mul, do_mul)
  CH_LOGIC_FUNCTION2_IMPL(T, ch_op::div, ch_div, do_div)
  CH_LOGIC_FUNCTION2_IMPL(T, ch_op::mod, ch_mod, do_mod)

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

CH_LOGIC_FUNCTION2_DECL(ch_lt)
CH_LOGIC_FUNCTION2_DECL(ch_le)
CH_LOGIC_FUNCTION2_DECL(ch_gt)
CH_LOGIC_FUNCTION2_DECL(ch_ge)

CH_LOGIC_FUNCTION1_DECL(ch_neg)
CH_LOGIC_FUNCTION2_DECL(ch_add)
CH_LOGIC_FUNCTION2_DECL(ch_sub)
CH_LOGIC_FUNCTION2_DECL(ch_mul)
CH_LOGIC_FUNCTION2_DECL(ch_div)
CH_LOGIC_FUNCTION2_DECL(ch_mod)

///////////////////////////////////////////////////////////////////////////////

template <unsigned N = 32>
class ch_uint : public ch_number_base<ch_uint<N>> {
public:  
  static_assert(N != 0, "invalid size");
  using traits = logic_traits<N, false, ch_uint, ch_scuint<N>>;
  template <unsigned M> using size_cast = ch_uint<M>;
  using base = ch_number_base<ch_uint<N>>;
  using base::operator=;

  ch_uint(const logic_buffer& buffer =
      logic_buffer(N, idname<ch_uint>()))
    : buffer_(buffer) {
    assert(N == buffer.size());
  }

  template <typename U,
            CH_REQUIRE(std::is_integral_v<U>)>
  ch_uint(const U& other)
    : ch_uint(logic_buffer(N, idname<ch_uint>())) {
    CH_SOURCE_LOCATION(1);
    base::operator=(other);
  }

  template <typename U,
            CH_REQUIRE(is_scbit_base_v<U>),
            CH_REQUIRE(ch_width_v<U> <= N)>
  ch_uint(const U& other)
    : ch_uint(logic_buffer(N, idname<ch_uint>())) {
    CH_SOURCE_LOCATION(1);
    base::operator=(other);
  }

  template <typename U,
            CH_REQUIRE(is_bit_base_v<U>),
            CH_REQUIRE(ch_width_v<U> <= N)>
  ch_uint(const U& other)
    : ch_uint(logic_buffer(N, idname<ch_uint>())) {
    CH_SOURCE_LOCATION(1);
    base::operator=(other);
  }

  ch_uint(const ch_uint& other)
    : ch_uint(logic_buffer(N, idname<ch_uint>())) {
    CH_SOURCE_LOCATION(1);
    base::operator=(other);
  }

  ch_uint(ch_uint&& other) : buffer_(std::move(other.buffer_)) {}

  ch_uint& operator=(const ch_uint& other) {
    CH_SOURCE_LOCATION(1);
    logic_accessor::assign(*this, other);
    return *this;
  }

  ch_uint& operator=(ch_uint&& other) {
    CH_SOURCE_LOCATION(1);
    logic_accessor::move(*this, std::move(other));
    return *this;
  }

protected:

  const logic_buffer& __buffer() const {
    return buffer_;
  }

  logic_buffer buffer_;

  friend class logic_accessor;
  template <unsigned M> friend class ch_uint;
};

template <unsigned M, unsigned N>
auto ch_pad(const ch_uint<N>& obj) {
  CH_SOURCE_LOCATION(1);
  return ch_uint<M+N>(obj);
}

/*CH_LOGIC_FUNCTION_EQUALITY(ch_uint, ch_eq, ch_op::eq)
CH_LOGIC_FUNCTION_EQUALITY(ch_uint, ch_ne, ch_op::ne)

CH_LOGIC_FUNCTION_RELATIONAL(ch_uint, ch_lt, ch_op::lt)
CH_LOGIC_FUNCTION_RELATIONAL(ch_uint, ch_le, ch_op::le)
CH_LOGIC_FUNCTION_RELATIONAL(ch_uint, ch_gt, ch_op::gt)
CH_LOGIC_FUNCTION_RELATIONAL(ch_uint, ch_ge, ch_op::ge)

CH_LOGIC_FUNCTION_BITWISE1(ch_uint, ch_inv, ch_op::inv)
CH_LOGIC_FUNCTION_BITWISE2(ch_uint, ch_and, ch_op::andb)
CH_LOGIC_FUNCTION_BITWISE2(ch_uint, ch_or, ch_op::orb)
CH_LOGIC_FUNCTION_BITWISE2(ch_uint, ch_xor, ch_op::xorb)

CH_LOGIC_FUNCTION_SHIFT(ch_uint, ch_shl, ch_op::shl)
CH_LOGIC_FUNCTION_SHIFT(ch_uint, ch_shr, ch_op::shr)

CH_LOGIC_FUNCTION_ARITHMETIC1(ch_uint, ch_neg, ch_op::neg)
CH_LOGIC_FUNCTION_ARITHMETIC2(ch_uint, ch_add, ch_op::add)
CH_LOGIC_FUNCTION_ARITHMETIC2(ch_uint, ch_sub, ch_op::sub)
CH_LOGIC_FUNCTION_ARITHMETIC3(ch_uint, ch_mul, ch_op::mul)
CH_LOGIC_FUNCTION_ARITHMETIC3(ch_uint, ch_div, ch_op::div)
CH_LOGIC_FUNCTION_ARITHMETIC3(ch_uint, ch_mod, ch_op::mod)*/

}}
