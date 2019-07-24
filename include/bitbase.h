#pragma once

#include "logic.h"
#include "system.h"

namespace ch {
namespace internal {

CH_SYSTEM_FUNCTION2B_DECL(ch_sbitbase, ch_eq)
CH_SYSTEM_FUNCTION2B_DECL(ch_sbitbase, ch_ne)

CH_SYSTEM_FUNCTION1B_DECL(ch_sbitbase, ch_not)
CH_SYSTEM_FUNCTION2B_DECL(ch_sbitbase, ch_andl)
CH_SYSTEM_FUNCTION2B_DECL(ch_sbitbase, ch_orl)

CH_SYSTEM_FUNCTION1X_DECL(ch_sbitbase, ch_inv)
CH_SYSTEM_FUNCTION2X_DECL(ch_sbitbase, ch_and)
CH_SYSTEM_FUNCTION2X_DECL(ch_sbitbase, ch_or)
CH_SYSTEM_FUNCTION2X_DECL(ch_sbitbase, ch_xor)

CH_SYSTEM_FUNCTION2B_DECL(ch_sbitbase, ch_andr)
CH_SYSTEM_FUNCTION2B_DECL(ch_sbitbase, ch_orr)
CH_SYSTEM_FUNCTION2B_DECL(ch_sbitbase, ch_xorr)

CH_SYSTEM_FUNCTION2X_DECL(ch_sbitbase, ch_shl)
CH_SYSTEM_FUNCTION2X_DECL(ch_sbitbase, ch_shr)

template <typename T>
class ch_sbitbase {
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
  T& operator=(const ch_sbitbase<U>& other) {
    static_assert((ch_width_v<U>) <= (ch_width_v<T>), "invalid type");
    auto self = reinterpret_cast<T*>(this);
    if constexpr (ch_width_v<U> < ch_width_v<T>) {
      sdata_type tmp(ch_width_v<T>);
      bv_pad<is_signed_v<U>>(tmp.words(),
                             ch_width_v<T>,
                             system_accessor::data(reinterpret_cast<const U&>(other)).words(),
                             ch_width_v<U>);
      system_accessor::assign(*self, tmp);
    } else {
      system_accessor::assign(*self, reinterpret_cast<const U&>(other));
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

  CH_SYSTEM_OPERATOR2B_IMPL(ch_sbitbase, operator==, do_eq)
  CH_SYSTEM_OPERATOR2B_IMPL(ch_sbitbase, operator!=, do_ne)

  CH_SYSTEM_OPERATOR1B_IMPL(ch_sbitbase, operator!, do_not)
  CH_SYSTEM_OPERATOR2B_IMPL(ch_sbitbase, operator&&, do_andl)
  CH_SYSTEM_OPERATOR2B_IMPL(ch_sbitbase, operator||, do_orl)

  CH_SYSTEM_OPERATOR1X_IMPL(ch_sbitbase, operator~, do_inv)
  CH_SYSTEM_OPERATOR2X_IMPL(ch_sbitbase, operator&, do_and)
  CH_SYSTEM_OPERATOR2X_IMPL(ch_sbitbase, operator|, do_or)
  CH_SYSTEM_OPERATOR2X_IMPL(ch_sbitbase, operator^, do_xor)

  CH_SYSTEM_OPERATOR2Y_IMPL(ch_sbitbase, operator<<, do_shl)
  CH_SYSTEM_OPERATOR2Y_IMPL(ch_sbitbase, operator>>, do_shr)

  CH_SYSTEM_OPERATOR2Z_IMPL(ch_sbitbase, operator&=, do_and)
  CH_SYSTEM_OPERATOR2Z_IMPL(ch_sbitbase, operator|=, do_or)
  CH_SYSTEM_OPERATOR2Z_IMPL(ch_sbitbase, operator^=, do_xor)

  CH_SYSTEM_OPERATOR2Z_IMPL(ch_sbitbase, operator<<=, do_shl)
  CH_SYSTEM_OPERATOR2Z_IMPL(ch_sbitbase, operator>>=, do_shr)

  CH_SYSTEM_FUNCTION2B_IMPL(ch_sbitbase, ch_eq, do_eq)
  CH_SYSTEM_FUNCTION2B_IMPL(ch_sbitbase, ch_ne, do_ne)

  CH_SYSTEM_FUNCTION1B_IMPL(ch_sbitbase, ch_not, do_not)
  CH_SYSTEM_FUNCTION2B_IMPL(ch_sbitbase, ch_andl, do_andl)
  CH_SYSTEM_FUNCTION2B_IMPL(ch_sbitbase, ch_orl, do_orl)

  CH_SYSTEM_FUNCTION1X_IMPL(ch_sbitbase, ch_inv, do_inv)
  CH_SYSTEM_FUNCTION2X_IMPL(ch_sbitbase, ch_and, do_and)
  CH_SYSTEM_FUNCTION2X_IMPL(ch_sbitbase, ch_or, do_or)
  CH_SYSTEM_FUNCTION2X_IMPL(ch_sbitbase, ch_xor, do_xor)

  CH_SYSTEM_FUNCTION2Y_IMPL(ch_sbitbase, ch_shl, do_shl)
  CH_SYSTEM_FUNCTION2Y_IMPL(ch_sbitbase, ch_shr, do_shr)

  CH_SYSTEM_FUNCTION1B_IMPL(ch_sbitbase, ch_andr, do_andr)
  CH_SYSTEM_FUNCTION1B_IMPL(ch_sbitbase, ch_orr, do_orr)
  CH_SYSTEM_FUNCTION1B_IMPL(ch_sbitbase, ch_xorr, do_xorr)

protected:

  friend std::ostream& operator<<(std::ostream& out, const T& in) {
    return system_accessor::do_print(in, out);
  }

  template <typename U>
  auto do_eq(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_system_op<ch_op::eq>(*self, other);
  }

  template <typename U>
  auto do_ne(const U& other) const {
    return !this->do_eq(other);
  }

  auto do_not() const {
    auto self = reinterpret_cast<const T*>(this);
    return make_system_op<ch_op::notl>(*self);
  }

  template <typename U>
  auto do_andl(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_system_op<ch_op::andl>(*self, other);
  }

  template <typename U>
  auto do_orl(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_system_op<ch_op::orl>(*self, other);
  }

  template <typename R>
  auto do_inv() const {
    auto self = reinterpret_cast<const T*>(this);
    return make_system_op<R, ch_op::inv>(*self);
  }

  template <typename R, typename U>
  auto do_and(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_system_op<R, ch_op::andb>(*self, other);
  }

  template <typename R, typename U>
  auto do_or(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_system_op<R, ch_op::orb>(*self, other);
  }

  template <typename R, typename U>
  auto do_xor(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_system_op<R, ch_op::xorb>(*self, other);
  }

  template <typename R, typename U>
  auto do_shl(const U& other) const {
    static_assert(ch_width_v<U> <= 32, "invalid size");
    auto self = reinterpret_cast<const T*>(this);
    return make_system_op<R, ch_op::shl>(*self, other);
  }

  template <typename R, typename U>
  auto do_shr(const U& other) const {
    static_assert(ch_width_v<U> <= 32, "invalid size");
    auto self = reinterpret_cast<const T*>(this);
    return make_system_op<R, ch_op::shr>(*self, other);
  }

  auto do_andr() const {
    auto self = reinterpret_cast<const T*>(this);
    return make_system_op<ch_op::andr>(*self);
  }

  auto do_orr() const {
    auto self = reinterpret_cast<const T*>(this);
    return make_system_op<ch_op::orr>(*self);
  }

  auto do_xorr() const {
    auto self = reinterpret_cast<const T*>(this);
    return make_system_op<ch_op::xorr>(*self);
  }

  std::ostream& do_print(std::ostream& out) const {
    auto self = reinterpret_cast<const T*>(this);
    return out << system_accessor::data(*self);
  }

  friend class system_accessor;
};

///////////////////////////////////////////////////////////////////////////////

CH_LOGIC_FUNCTION2B_DECL(ch_bitbase, ch_eq)
CH_LOGIC_FUNCTION2B_DECL(ch_bitbase, ch_ne)

CH_LOGIC_FUNCTION1B_DECL(ch_bitbase, ch_not)
CH_LOGIC_FUNCTION2B_DECL(ch_bitbase, ch_andl)
CH_LOGIC_FUNCTION2B_DECL(ch_bitbase, ch_orl)

CH_LOGIC_FUNCTION1X_DECL(ch_bitbase, ch_inv)
CH_LOGIC_FUNCTION2X_DECL(ch_bitbase, ch_and)
CH_LOGIC_FUNCTION2X_DECL(ch_bitbase, ch_or)
CH_LOGIC_FUNCTION2X_DECL(ch_bitbase, ch_xor)

CH_LOGIC_FUNCTION2B_DECL(ch_bitbase, ch_andr)
CH_LOGIC_FUNCTION2B_DECL(ch_bitbase, ch_orr)
CH_LOGIC_FUNCTION2B_DECL(ch_bitbase, ch_xorr)

CH_LOGIC_FUNCTION2X_DECL(ch_bitbase, ch_shl)
CH_LOGIC_FUNCTION2X_DECL(ch_bitbase, ch_shr)

template <typename T>
class ch_bitbase {
public:

  // assignment operators

  template <typename U,
            CH_REQUIRE(std::is_integral_v<U>)>
  T& operator=(const U& other) {
    CH_API_ENTRY(1);
    auto self = reinterpret_cast<T*>(this);
    logic_accessor::assign(*self, sdata_type(ch_width_v<T>, other));
    return *self;
  }

  template <typename U>
  T& operator=(const ch_sbitbase<U>& other) {
    CH_API_ENTRY(1);
    static_assert(ch_width_v<U> <= ch_width_v<T>, "invalid size");
    auto self = reinterpret_cast<T*>(this);
    if constexpr (ch_width_v<U> < ch_width_v<T>) {
      ch_sbit<ch_width_v<T>> tmp(reinterpret_cast<const U&>(other));
      logic_accessor::assign(*self, system_accessor::data(tmp));
    } else {
      logic_accessor::assign(*self,
                             system_accessor::data(reinterpret_cast<const U&>(other)));
    }
    return *self;
  }

  template <typename U>
  T& operator=(const ch_bitbase<U>& other) {
    CH_API_ENTRY(1);
    static_assert(ch_width_v<U> <= ch_width_v<T>, "invalid size");
    auto self = reinterpret_cast<T*>(this);
    if constexpr (ch_width_v<U> < ch_width_v<T>) {
      ch_bit<ch_width_v<T>> tmp(make_logic_buffer(
          createOpNode(ch_op::pad,
                       ch_width_v<T>,
                       is_signed_v<U>,
                       get_lnode(reinterpret_cast<const U&>(other)))));
      logic_accessor::assign(*self, tmp);
    } else {
      logic_accessor::assign(*self, reinterpret_cast<const U&>(other));
    }
    return *self;
  }

  // subscript operators

  auto operator[](size_t index) const {
    CH_API_ENTRY(1);
    assert(index < ch_width_v<T>);
    auto self = reinterpret_cast<const T*>(this);
    return logic_accessor::slice<ch_bool>(*self, index);
  }

  auto operator[](size_t index) {
    CH_API_ENTRY(1);
    assert(index < ch_width_v<T>);
    auto self = reinterpret_cast<T*>(this);
    return logic_accessor::sliceref<ch_bool>(*self, index);
  }

  CH_LOGIC_INTERFACE(T)

  CH_LOGIC_OPERATOR2B_IMPL(ch_bitbase, operator==, do_eq)
  CH_LOGIC_OPERATOR2B_IMPL(ch_bitbase, operator!=, do_ne)

  CH_LOGIC_OPERATOR1B_IMPL(ch_bitbase, operator!, do_not)
  CH_LOGIC_OPERATOR2B_IMPL(ch_bitbase, operator&&, do_andl)
  CH_LOGIC_OPERATOR2B_IMPL(ch_bitbase, operator||, do_orl)

  CH_LOGIC_OPERATOR1X_IMPL(ch_bitbase, operator~, do_inv)
  CH_LOGIC_OPERATOR2X_IMPL(ch_bitbase, operator&, do_and)
  CH_LOGIC_OPERATOR2X_IMPL(ch_bitbase, operator|, do_or)
  CH_LOGIC_OPERATOR2X_IMPL(ch_bitbase, operator^, do_xor)

  CH_LOGIC_OPERATOR2Y_IMPL(ch_bitbase, operator<<, do_shl)
  CH_LOGIC_OPERATOR2Y_IMPL(ch_bitbase, operator>>, do_shr)

  CH_LOGIC_OPERATOR2Z_IMPL(ch_bitbase, operator&=, do_and)
  CH_LOGIC_OPERATOR2Z_IMPL(ch_bitbase, operator|=, do_or)
  CH_LOGIC_OPERATOR2Z_IMPL(ch_bitbase, operator^=, do_xor)

  CH_LOGIC_OPERATOR2Z_IMPL(ch_bitbase, operator<<=, do_shl)
  CH_LOGIC_OPERATOR2Z_IMPL(ch_bitbase, operator>>=, do_shr)

  CH_LOGIC_FUNCTION2B_IMPL(ch_bitbase, ch_eq, do_eq)
  CH_LOGIC_FUNCTION2B_IMPL(ch_bitbase, ch_ne, do_ne)

  CH_LOGIC_FUNCTION1B_IMPL(ch_bitbase, ch_not, do_not)
  CH_LOGIC_FUNCTION2B_IMPL(ch_bitbase, ch_andl, do_andl)
  CH_LOGIC_FUNCTION2B_IMPL(ch_bitbase, ch_orl, do_orl)

  CH_LOGIC_FUNCTION1X_IMPL(ch_bitbase, ch_inv, do_inv)
  CH_LOGIC_FUNCTION2X_IMPL(ch_bitbase, ch_and, do_and)
  CH_LOGIC_FUNCTION2X_IMPL(ch_bitbase, ch_or, do_or)
  CH_LOGIC_FUNCTION2X_IMPL(ch_bitbase, ch_xor, do_xor)

  CH_LOGIC_FUNCTION2Y_IMPL(ch_bitbase, ch_shl, do_shl)
  CH_LOGIC_FUNCTION2Y_IMPL(ch_bitbase, ch_shr, do_shr)

  CH_LOGIC_FUNCTION1B_IMPL(ch_bitbase, ch_andr, do_andr)
  CH_LOGIC_FUNCTION1B_IMPL(ch_bitbase, ch_orr, do_orr)
  CH_LOGIC_FUNCTION1B_IMPL(ch_bitbase, ch_xorr, do_xorr)

protected:

  template <typename U>
  auto do_eq(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<ch_op::eq>(*self, other);
  }

  template <typename U>
  auto do_ne(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<ch_op::ne>(*self, other);
  }

  auto do_not() const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<ch_op::notl>(*self);
  }

  template <typename U>
  auto do_andl(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<ch_op::andl>(*self, other);
  }

  template <typename U>
  auto do_orl(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<ch_op::orl>(*self, other);
  }

  template <typename R>
  auto do_inv() const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<R, ch_op::inv>(*self);
  }

  template <typename R, typename U>
  auto do_and(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<R, ch_op::andb>(*self, other);
  }

  template <typename R, typename U>
  auto do_or(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<R, ch_op::orb>(*self, other);
  }

  template <typename R, typename U>
  auto do_xor(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<R, ch_op::xorb>(*self, other);
  }

  template <typename R, typename U>
  auto do_shl(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    static_assert(ch_width_v<U> <= 32, "invalid size");
    return make_logic_op<R, ch_op::shl>(*self, other);
  }

  template <typename R, typename U>
  auto do_shr(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    static_assert(ch_width_v<U> <= 32, "invalid size");
    return make_logic_op<R, ch_op::shr>(*self, other);
  }

  auto do_andr() const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<ch_op::andr>(*self);
  }

  auto do_orr() const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<ch_op::orr>(*self);
  }

  auto do_xorr() const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<ch_op::xorr>(*self);
  }

  friend class logic_accessor;
};

}
}
