#pragma once

#include "logic.h"
#include "system.h"

namespace ch {
namespace internal {

template <typename T>
class ch_sbit_base {
public:

  // assignment operators

  template <typename U,
            CH_REQUIRE(std::is_integral_v<U>)>
  T& operator=(const U& other) {
    auto self = reinterpret_cast<T*>(this);
    system_accessor::assign(*self, sdata_type(ch_width_v<T>, other));
    return *self;
  }

  template <typename U>
  T& operator=(const ch_sbit_base<U>& other) {
    static_assert((ch_width_v<U>) <= (ch_width_v<T>), "invalid type");
    auto self = reinterpret_cast<T*>(this);
    if constexpr (ch_width_v<U> < ch_width_v<T>) {
      sdata_type tmp(ch_width_v<T>);
      bv_pad<ch_signed_v<U>>(tmp.words(), ch_width_v<T>, system_accessor::data((const U&)other).words(), ch_width_v<U>);
      system_accessor::assign(*self, tmp);
    } else {
      system_accessor::assign(*self, (const U&)other);
    }
    return *self;
  }

  // subscript operators

  auto operator[](size_t index) const {
    assert(index < ch_width_v<T>);
    auto self = reinterpret_cast<const T*>(this);
    return system_accessor::slice<ch_sbool>(*self, index);
  }

  auto operator[](size_t index) {
    assert(index < ch_width_v<T>);
    auto self = reinterpret_cast<T*>(this);
    return system_accessor::sliceref<ch_sbool>(*self, index);
  }

  CH_SYSTEM_INTERFACE(T)
  CH_SYSTEM_OP_CAST(T)

  CH_SYSTEM_OPERATOR2B_IMPL(ch_sbit_base, operator==, do_eq)
  CH_SYSTEM_OPERATOR2B_IMPL(ch_sbit_base, operator!=, do_ne)

  CH_SYSTEM_OPERATOR1B_IMPL(ch_sbit_base, operator!, do_not)
  CH_SYSTEM_OPERATOR2B_IMPL(ch_sbit_base, operator&&, do_andl)
  CH_SYSTEM_OPERATOR2B_IMPL(ch_sbit_base, operator||, do_orl)

  CH_SYSTEM_OPERATOR1X_IMPL(ch_sbit_base, operator~, do_inv)
  CH_SYSTEM_OPERATOR2X_IMPL(ch_sbit_base, operator&, do_and)
  CH_SYSTEM_OPERATOR2X_IMPL(ch_sbit_base, operator|, do_or)
  CH_SYSTEM_OPERATOR2X_IMPL(ch_sbit_base, operator^, do_xor)

  CH_SYSTEM_OPERATOR2X_IMPL(ch_sbit_base, operator<<, do_shl)
  CH_SYSTEM_OPERATOR2X_IMPL(ch_sbit_base, operator>>, do_shr)

  CH_SYSTEM_FUNCTION2B_IMPL(ch_sbit_base, ch_eq, do_eq)
  CH_SYSTEM_FUNCTION2B_IMPL(ch_sbit_base, ch_ne, do_ne)

  CH_SYSTEM_FUNCTION1B_IMPL(ch_sbit_base, ch_not, do_not)
  CH_SYSTEM_FUNCTION2B_IMPL(ch_sbit_base, ch_andl, do_andl)
  CH_SYSTEM_FUNCTION2B_IMPL(ch_sbit_base, ch_orl, do_orl)

  CH_SYSTEM_FUNCTION1X_IMPL(ch_sbit_base, ch_inv, do_inv)
  CH_SYSTEM_FUNCTION2X_IMPL(ch_sbit_base, ch_and, do_and)
  CH_SYSTEM_FUNCTION2X_IMPL(ch_sbit_base, ch_or, do_or)
  CH_SYSTEM_FUNCTION2X_IMPL(ch_sbit_base, ch_xor, do_xor)

  CH_SYSTEM_FUNCTION2X_IMPL(ch_sbit_base, ch_shl, do_shl)
  CH_SYSTEM_FUNCTION2X_IMPL(ch_sbit_base, ch_shr, do_shr)

  CH_SYSTEM_FUNCTION1B_IMPL(ch_sbit_base, ch_andr, do_andr)
  CH_SYSTEM_FUNCTION1B_IMPL(ch_sbit_base, ch_orr, do_orr)
  CH_SYSTEM_FUNCTION1B_IMPL(ch_sbit_base, ch_xorr, do_xorr)

protected:

  friend std::ostream& operator<<(std::ostream& out, const T& in) {
    return system_accessor::do_print(in, out);
  }

  template <typename U>
  auto do_eq(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    /*auto lhs_w = system_accessor::data(*self).words();
    auto rhs_w = system_accessor::data(other).words();
    return bv_eq<ch_signed_v<T>, block_type, ClearBitAccessor<block_type>>(
                                      lhs_w, ch_width_v<T>, rhs_w, ch_width_v<T>);*/
    return false;
  }

  template <typename U>
  auto do_ne(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    /*auto lhs_w = system_accessor::data(*self).words();
    auto rhs_w = system_accessor::data(other).words();
    return !bv_eq<ch_signed_v<T>, block_type, ClearBitAccessor<block_type>>(
                                      lhs_w, ch_width_v<T>, rhs_w, ch_width_v<T>);*/
    return false;
  }

  auto do_not() const {
    auto self = reinterpret_cast<const T*>(this);
    //return make_logic_op<ch_op::notl, false, ch_bool>(*self);
    return false;
  }

  template <typename U>
  auto do_andl(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    //return make_logic_op<ch_op::andl, ch_signed_v<T>, ch_bool>(*self, other);
    return false;
  }

  template <typename U>
  auto do_orl(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    //return make_logic_op<ch_op::orl, ch_signed_v<T>, ch_bool>(*self, other);
    return false;
  }

  template <typename R>
  auto do_inv() const {
    auto self = reinterpret_cast<const T*>(this);
    //return make_logic_op<ch_op::inv, false, R>(*self);
    return R();
  }

  template <typename R, typename U>
  auto do_and(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    //return make_logic_op<ch_op::andb, ch_signed_v<R>, R>(*self, other);
    return R();
  }

  template <typename R, typename U>
  auto do_or(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    //return make_logic_op<ch_op::orb, ch_signed_v<R>, R>(*self, other);
    return R();
  }

  template <typename R, typename U>
  auto do_xor(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    //return make_logic_op<ch_op::xorb, ch_signed_v<R>, R>(*self, other);
    return R();
  }

  template <typename R, typename U>
  auto do_shl(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    static_assert(ch_width_v<U> <= 32, "invalid size");
    //return make_logic_op<ch_op::shl, ch_signed_v<R>, R>(*self, other);
    return R();
  }

  template <typename R, typename U>
  auto do_shr(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    static_assert(ch_width_v<U> <= 32, "invalid size");
    //return make_logic_op<ch_op::shr, ch_signed_v<R>, R>(*self, other);
    return R();
  }

  auto do_andr() const {
    auto self = reinterpret_cast<const T*>(this);
    //return make_logic_op<ch_op::andr, false, ch_bool>(*self);
    return false;
  }

  auto do_orr() const {
    auto self = reinterpret_cast<const T*>(this);
    //return make_logic_op<ch_op::orr, false, ch_bool>(*self);
    return false;
  }

  auto do_xorr() const {
    auto self = reinterpret_cast<const T*>(this);
    //return make_logic_op<ch_op::xorr, false, ch_bool>(*self);
    return false;
  }

  std::ostream& do_print(std::ostream& out) const {
    auto self = reinterpret_cast<const T*>(this);
    return out << system_accessor::data(*self);
  }

  template <typename U> friend class ch_sbit_base;
};

CH_SYSTEM_FUNCTION2B_DECL(ch_sbit_base, ch_eq)
CH_SYSTEM_FUNCTION2B_DECL(ch_sbit_base, ch_ne)

CH_SYSTEM_FUNCTION1B_DECL(ch_sbit_base, ch_not)
CH_SYSTEM_FUNCTION2B_DECL(ch_sbit_base, ch_andl)
CH_SYSTEM_FUNCTION2B_DECL(ch_sbit_base, ch_orl)

CH_SYSTEM_FUNCTION1X_DECL(ch_sbit_base, ch_inv)
CH_SYSTEM_FUNCTION2X_DECL(ch_sbit_base, ch_and)
CH_SYSTEM_FUNCTION2X_DECL(ch_sbit_base, ch_or)
CH_SYSTEM_FUNCTION2X_DECL(ch_sbit_base, ch_xor)

CH_SYSTEM_FUNCTION2B_DECL(ch_sbit_base, ch_andr)
CH_SYSTEM_FUNCTION2B_DECL(ch_sbit_base, ch_orr)
CH_SYSTEM_FUNCTION2B_DECL(ch_sbit_base, ch_xorr)

CH_SYSTEM_FUNCTION2X_DECL(ch_sbit_base, ch_shl)
CH_SYSTEM_FUNCTION2X_DECL(ch_sbit_base, ch_shr)

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class ch_bit_base {
public:

  // assignment operators

  template <typename U,
            CH_REQUIRE(std::is_integral_v<U>)>
  T& operator=(const U& other) {
    CH_SOURCE_LOCATION(1);
    auto self = reinterpret_cast<T*>(this);
    logic_accessor::assign(*self, sdata_type(ch_width_v<T>, other));
    return *self;
  }

  template <typename U>
  T& operator=(const ch_sbit_base<U>& other) {
    CH_SOURCE_LOCATION(1);
    static_assert(ch_width_v<U> <= ch_width_v<T>, "invalid size");
    auto self = reinterpret_cast<T*>(this);
    if constexpr (ch_width_v<U> < ch_width_v<T>) {
      ch_sbit<ch_width_v<T>> tmp((const U&)other);
      logic_accessor::assign(*self, system_accessor::data(tmp));
    } else {
      logic_accessor::assign(*self, system_accessor::data((const U&)other));
    }
    return *self;
  }

  template <typename U>
  T& operator=(const ch_bit_base<U>& other) {
    CH_SOURCE_LOCATION(1);
    static_assert(ch_width_v<U> <= ch_width_v<T>, "invalid size");
    auto self = reinterpret_cast<T*>(this);
    if constexpr (ch_width_v<U> < ch_width_v<T>) {
      ch_bit<ch_width_v<T>> tmp(logic_buffer(
          createOpNode(ch_op::pad, ch_width_v<T>, ch_signed_v<U>, get_lnode((const U&)other))));
      logic_accessor::assign(*self, tmp);
    } else {
      logic_accessor::assign(*self,(const U&)other);
    }
    return *self;
  }

  // subscript operators

  auto operator[](size_t index) const {
    assert(index < ch_width_v<T>);
    CH_SOURCE_LOCATION(1);
    auto self = reinterpret_cast<const T*>(this);
    return logic_accessor::slice<ch_bool>(*self, index);
  }

  auto operator[](size_t index) {
    assert(index < ch_width_v<T>);
    CH_SOURCE_LOCATION(1);
    auto self = reinterpret_cast<T*>(this);
    return logic_accessor::sliceref<ch_bool>(*self, index);
  }

  CH_LOGIC_INTERFACE(T)

  CH_LOGIC_OPERATOR2B_IMPL(T, operator==, do_eq)
  CH_LOGIC_OPERATOR2B_IMPL(T, operator!=, do_ne)

  CH_LOGIC_OPERATOR1B_IMPL(T, operator!, do_not)
  CH_LOGIC_OPERATOR2B_IMPL(T, operator&&, do_andl)
  CH_LOGIC_OPERATOR2B_IMPL(T, operator||, do_orl)

  CH_LOGIC_OPERATOR1X_IMPL(T, operator~, do_inv)
  CH_LOGIC_OPERATOR2X_IMPL(T, operator&, do_and)
  CH_LOGIC_OPERATOR2X_IMPL(T, operator|, do_or)
  CH_LOGIC_OPERATOR2X_IMPL(T, operator^, do_xor)

  CH_LOGIC_OPERATOR2X_IMPL(T, operator<<, do_shl)
  CH_LOGIC_OPERATOR2X_IMPL(T, operator>>, do_shr)

  CH_LOGIC_FUNCTION2B_IMPL(T, ch_eq, do_eq)
  CH_LOGIC_FUNCTION2B_IMPL(T, ch_ne, do_ne)

  CH_LOGIC_FUNCTION1B_IMPL(T, ch_not, do_not)
  CH_LOGIC_FUNCTION2B_IMPL(T, ch_andl, do_andl)
  CH_LOGIC_FUNCTION2B_IMPL(T, ch_orl, do_orl)

  CH_LOGIC_FUNCTION1X_IMPL(T, ch_inv, do_inv)
  CH_LOGIC_FUNCTION2X_IMPL(T, ch_and, do_and)
  CH_LOGIC_FUNCTION2X_IMPL(T, ch_or, do_or)
  CH_LOGIC_FUNCTION2X_IMPL(T, ch_xor, do_xor)

  CH_LOGIC_FUNCTION2X_IMPL(T, ch_shl, do_shl)
  CH_LOGIC_FUNCTION2X_IMPL(T, ch_shr, do_shr)

  CH_LOGIC_FUNCTION1B_IMPL(T, ch_andr, do_andr)
  CH_LOGIC_FUNCTION1B_IMPL(T, ch_orr, do_orr)
  CH_LOGIC_FUNCTION1B_IMPL(T, ch_xorr, do_xorr)

protected:

  template <typename U>
  auto do_eq(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<ch_op::eq, ch_signed_v<T>, ch_bool>(*self, other);
  }

  template <typename U>
  auto do_ne(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<ch_op::ne, ch_signed_v<T>, ch_bool>(*self, other);
  }

  auto do_not() const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<ch_op::notl, false, ch_bool>(*self);
  }

  template <typename U>
  auto do_andl(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<ch_op::andl, ch_signed_v<T>, ch_bool>(*self, other);
  }

  template <typename U>
  auto do_orl(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<ch_op::orl, ch_signed_v<T>, ch_bool>(*self, other);
  }

  template <typename R>
  auto do_inv() const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<ch_op::inv, false, R>(*self);
  }

  template <typename R, typename U>
  auto do_and(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<ch_op::andb, ch_signed_v<R>, R>(*self, other);
  }

  template <typename R, typename U>
  auto do_or(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<ch_op::orb, ch_signed_v<R>, R>(*self, other);
  }

  template <typename R, typename U>
  auto do_xor(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<ch_op::xorb, ch_signed_v<R>, R>(*self, other);
  }

  template <typename R, typename U>
  auto do_shl(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    static_assert(ch_width_v<U> <= 32, "invalid size");
    return make_logic_op<ch_op::shl, ch_signed_v<R>, R>(*self, other);
  }

  template <typename R, typename U>
  auto do_shr(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    static_assert(ch_width_v<U> <= 32, "invalid size");
    return make_logic_op<ch_op::shr, ch_signed_v<R>, R>(*self, other);
  }

  auto do_andr() const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<ch_op::andr, false, ch_bool>(*self);
  }

  auto do_orr() const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<ch_op::orr, false, ch_bool>(*self);
  }

  auto do_xorr() const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<ch_op::xorr, false, ch_bool>(*self);
  }

  template <typename U> friend class ch_bit_base;
};

CH_LOGIC_FUNCTION2B_DECL(ch_eq)
CH_LOGIC_FUNCTION2B_DECL(ch_ne)

CH_LOGIC_FUNCTION1B_DECL(ch_not)
CH_LOGIC_FUNCTION2B_DECL(ch_andl)
CH_LOGIC_FUNCTION2B_DECL(ch_orl)

CH_LOGIC_FUNCTION1X_DECL(ch_inv)
CH_LOGIC_FUNCTION2X_DECL(ch_and)
CH_LOGIC_FUNCTION2X_DECL(ch_or)
CH_LOGIC_FUNCTION2X_DECL(ch_xor)

CH_LOGIC_FUNCTION2B_DECL(ch_andr)
CH_LOGIC_FUNCTION2B_DECL(ch_orr)
CH_LOGIC_FUNCTION2B_DECL(ch_xorr)

CH_LOGIC_FUNCTION2X_DECL(ch_shl)
CH_LOGIC_FUNCTION2X_DECL(ch_shr)

}
}
