#pragma once

#include <cash.h>
#include <math.h>

namespace ch {
namespace htl {

using namespace logic;
using namespace extension;

#define ALTFP_SP_ADD_SUB 7
#define ALTFP_SP_MULT    5
#define ALTFP_SP_DIV     6

class ch_float32;

class ch_sfloat32 : public ch_snumber_base<ch_sfloat32> {
public:
  using traits = system_traits<32, true, ch_sfloat32, ch_float32>;
  using base = ch_snumber_base<ch_sfloat32>;

  ch_sfloat32(const system_buffer_ptr& buffer
              = make_system_buffer(32, ch::internal::idname<ch_sfloat32>()))
    : buffer_(buffer)
  {}

  template <typename U,
            CH_REQUIRE(ch_width_v<U> <= 32)>
  explicit ch_sfloat32(const ch_sbit_base<U>& other)
    : ch_sfloat32(make_system_buffer(32, ch::internal::idname<ch_sfloat32>())) {
    base::operator=(reinterpret_cast<const U&>(other));
  }

  ch_sfloat32(float other)
    : ch_sfloat32(make_system_buffer(32, ch::internal::idname<ch_sfloat32>())) {
    this->operator=(other);
  }

  ch_sfloat32(const ch_sfloat32& other)
    : ch_sfloat32(make_system_buffer(32, ch::internal::idname<ch_sfloat32>())) {
    this->operator=(other);
  }

  ch_sfloat32(ch_sfloat32&& other) : buffer_(std::move(other.buffer_)) {}

  ch_sfloat32& operator=(const ch_sfloat32& other) {
    this->as_bit().operator=(other.as_bit());
    return *this;
  }

  ch_sfloat32& operator=(ch_sfloat32&& other) {
    this->as_bit().operator=(std::move(other.as_bit()));
    return *this;
  }

  ch_sfloat32& operator=(float other) {
    base::operator=(bit_cast<int32_t>(other));
    return *this;
  }

  explicit operator float() const {
    return bit_cast<float>(static_cast<int32_t>(*this));
  }  

protected:

  template <typename R>
  auto do_neg() const {
    static_assert(std::is_same_v<R, ch_sfloat32>, "invalid type");
    auto value = static_cast<float>(*this);
    return ch_sfloat32(0.0f - value);
  }

  template <typename R, typename U>
  auto do_add(const U& other) const {
    static_assert(std::is_same_v<R, ch_sfloat32>, "invalid type");
    auto lhs_value = static_cast<float>(*this);
    auto rhs_value = static_cast<float>(other);
    return ch_sfloat32(lhs_value + rhs_value);
  }

  template <typename R, typename U>
  auto do_sub(const U& other) const {
    static_assert(std::is_same_v<R, ch_sfloat32>, "invalid type");
    auto lhs_value = static_cast<float>(*this);
    auto rhs_value = static_cast<float>(other);
    return ch_sfloat32(lhs_value - rhs_value);
  }

  template <typename R, typename U>
  auto do_mul(const U& other) const {
    static_assert(std::is_same_v<R, ch_sfloat32>, "invalid type");
    auto lhs_value = static_cast<float>(*this);
    auto rhs_value = static_cast<float>(other);
    return ch_sfloat32(lhs_value * rhs_value);
  }

  template <typename R, typename U>
  auto do_div(const U& other) const {
    static_assert(std::is_same_v<R, ch_sfloat32>, "invalid type");
    auto lhs_value = static_cast<float>(*this);
    auto rhs_value = static_cast<float>(other);
    return ch_sfloat32(lhs_value / rhs_value);
  }

  template <typename R, typename U>
  auto do_mod(const U& other) const {
    static_assert(std::is_same_v<R, ch_sfloat32>, "invalid type");
    auto lhs_value = static_cast<float>(*this);
    auto rhs_value = static_cast<float>(other);
    return ch_sfloat32(fmod(lhs_value, rhs_value));
  }

  const system_buffer_ptr& __buffer() const {
    return buffer_;
  }

  system_buffer_ptr buffer_;

  friend class ch::extension::system_accessor;
};

///////////////////////////////////////////////////////////////////////////////

class ch_float32 : public ch_number_base<ch_float32> {
public:
  using traits = logic_traits<32, true, ch_float32, ch_sfloat32>;
  using base = ch_number_base<ch_float32>;

  ch_float32(const logic_buffer& buffer = logic_buffer(32, ch::internal::idname<ch_float32>()))
    : buffer_(buffer)
  {}

  template <typename U,
            CH_REQUIRE(ch_width_v<U> <= 32)>
  explicit ch_float32(const ch_sbit_base<U>& other)
    : ch_float32(logic_buffer(32, ch::internal::idname<ch_float32>())) {
    __source_location(1);
    base::operator=(reinterpret_cast<const U&>(other));
  }

  template <typename U,
            CH_REQUIRE(ch_width_v<U> <= 32)>
  explicit ch_float32(const ch_bit_base<U>& other)
    : ch_float32(logic_buffer(32, ch::internal::idname<ch_float32>())) {
    __source_location(1);
    base::operator=(reinterpret_cast<const U&>(other));
  }

  ch_float32(float other)
    : ch_float32(logic_buffer(32, ch::internal::idname<ch_float32>())) {
    __source_location(1);
    this->operator=(other);
  }

  ch_float32(const ch_sfloat32& other)
    : ch_float32(logic_buffer(32, ch::internal::idname<ch_float32>())) {
    __source_location(1);
    base::operator=(other);
  }

  ch_float32(const ch_float32& other)
    : ch_float32(logic_buffer(32, ch::internal::idname<ch_float32>())) {
    __source_location(1);
    this->operator=(other);
  }

  ch_float32(ch_float32&& other) : buffer_(std::move(other.buffer_)) {}

  ch_float32& operator=(float other) {
    __source_location(1);
    base::operator=(bit_cast<int32_t>(other));
    return *this;
  }

  ch_float32& operator=(const ch_float32& other) {
    __source_location(1);
    this->as_bit().operator=(other.as_bit());
    return *this;
  }

  ch_float32& operator=(ch_float32&& other) {
    __source_location(1);
    this->as_bit().operator=(std::move(other.as_bit()));
    return *this;
  }

protected:

  template <typename R>
  auto do_neg() const;

  template <typename R, typename U>
  auto do_add(const U& other) const;

  template <typename R, typename U>
  auto do_sub(const U& other) const;

  template <typename R, typename U>
  auto do_mul(const U& other) const;

  template <typename R, typename U>
  auto do_div(const U& other) const;

  template <typename R, typename U>
  auto do_mod(const U& other) const;

  const logic_buffer& __buffer() const {
    return buffer_;
  }

  logic_buffer buffer_;

  friend class ch::extension::logic_accessor;
};

///////////////////////////////////////////////////////////////////////////////

namespace detail {
template <typename T>
class sc_pipereg {
public:
  sc_pipereg(unsigned depth) : buffer_(depth), index_(0) {}

  T eval(const T& obj, bool enable) {
    if (enable) {
      buffer_[index_] = obj;
      if (++index_ == buffer_.size())
        index_ = 0;
    }
    return buffer_[index_];
  }

  void reset() {
    index_ = 0;
  }

private:
  std::vector<T> buffer_;
  unsigned index_;
};
}

class sfAdd {
public:
  __sio (
    __in (ch_bool)     en,
    __in (ch_float32)  lhs,
    __in (ch_float32)  rhs,
    __out (ch_float32) dst
  );

  sfAdd(unsigned delay) : pipe_(delay) {}

  void eval() {
    auto lhs = static_cast<float>(io.lhs);
    auto rhs = static_cast<float>(io.rhs);
    io.dst = pipe_.eval(lhs + rhs, !!io.en);
  }

  void reset() {
    pipe_.reset();
  }

  bool to_verilog(udf_vostream& out, udf_verilog mode) {
    if (mode != udf_verilog::body)
      return false;
    out << "fp_add __fp_add$id(.clock($clk), .clk_en($io.en), "
           ".dataa($io.lhs), .datab($io.rhs), .result($io.dst));";
    return true;
  }

private:
  detail::sc_pipereg<float> pipe_;
};

class sfSub {
public:
  __sio (
    __in (ch_bool)     en,
    __in (ch_float32)  lhs,
    __in (ch_float32)  rhs,
    __out (ch_float32) dst
  );

  sfSub(unsigned delay) : pipe_(delay) {}

  void eval() {
    auto lhs = static_cast<float>(io.lhs);
    auto rhs = static_cast<float>(io.rhs);
    io.dst = pipe_.eval(lhs - rhs, !!io.en);
  }

  void reset() {
    pipe_.reset();
  }

  bool to_verilog(udf_vostream& out, udf_verilog mode) {
    if (mode != udf_verilog::body)
      return false;
    out << "fp_sub __fp_sub$id(.clock($clk), .clk_en($io.en), "
           ".dataa($io.lhs), .datab($io.rhs), .result($io.dst));";
    return true;
  }

private:
  detail::sc_pipereg<float> pipe_;
};

class sfMul {
public:
  __sio (
    __in (ch_bool)     en,
    __in (ch_float32)  lhs,
    __in (ch_float32)  rhs,
    __out (ch_float32) dst
  );

  sfMul(unsigned delay) : pipe_(delay) {}

  void eval() {
    auto lhs = static_cast<float>(io.lhs);
    auto rhs = static_cast<float>(io.rhs);
    io.dst = pipe_.eval(lhs * rhs, !!io.en);
  }

  void reset() {
    pipe_.reset();
  }

  bool to_verilog(udf_vostream& out, udf_verilog mode) {
    if (mode != udf_verilog::body)
      return false;
    out << "fp_mul __fp_mul$id("
        << ".clock($clk), "
        << ".clk_en(" << io.en << "), "
        << ".dataa(" << io.lhs << "), "
        << ".datab(" << io.rhs << "), "
        << ".result(" << io.dst << "));";
    return true;
  }

private:
  detail::sc_pipereg<float> pipe_;
};

class sfDiv {
public:
  __sio (
    __in (ch_bool)     en,
    __in (ch_float32)  lhs,
    __in (ch_float32)  rhs,
    __out (ch_float32) dst
  );

  sfDiv(unsigned delay) : pipe_(delay) {}

  void eval() {
    auto lhs = static_cast<float>(io.lhs);
    auto rhs = static_cast<float>(io.rhs);
    io.dst = pipe_.eval(lhs / rhs, !!io.en);
  }

  void reset() {
    pipe_.reset();
  }

  bool to_verilog(udf_vostream& out, udf_verilog mode) {
    if (mode != udf_verilog::body)
      return false;
    out << "fp_div __fp_div$id("
        << ".clock($clk), "
        << ".clk_en(" << io.en << "), "
        << ".dataa(" << io.lhs << "), "
        << ".datab(" << io.rhs << "), "
        << ".result(" << io.dst << "));";
    return true;
  }

private:
  detail::sc_pipereg<float> pipe_;
};

///////////////////////////////////////////////////////////////////////////////

struct cfAdd {
  __sio (
    __in (ch_float32)  lhs,
    __in (ch_float32)  rhs,
    __out (ch_float32) dst
  );

  void eval() {
    auto lhs = bit_cast<float>(static_cast<int32_t>(io.lhs));
    auto rhs = bit_cast<float>(static_cast<int32_t>(io.rhs));
    io.dst = bit_cast<int32_t>(lhs + rhs);
  }
};

struct cfSub {
  __sio (
    __in (ch_float32)  lhs,
    __in (ch_float32)  rhs,
    __out (ch_float32) dst
  );

  void eval() {
    auto lhs = bit_cast<float>(static_cast<int32_t>(io.lhs));
    auto rhs = bit_cast<float>(static_cast<int32_t>(io.rhs));
    io.dst = bit_cast<int32_t>(lhs - rhs);
  }
};

struct cfMul {
  __sio (
    __in (ch_float32)  lhs,
    __in (ch_float32)  rhs,
    __out (ch_float32) dst
  );

  void eval() {
    auto lhs = bit_cast<float>(static_cast<int32_t>(io.lhs));
    auto rhs = bit_cast<float>(static_cast<int32_t>(io.rhs));
    io.dst = bit_cast<int32_t>(lhs * rhs);
  }
};

struct cfDiv {
  __sio (
    __in (ch_float32)  lhs,
    __in (ch_float32)  rhs,
    __out (ch_float32) dst
  );

  void eval() {
    auto lhs = bit_cast<float>(static_cast<int32_t>(io.lhs));
    auto rhs = bit_cast<float>(static_cast<int32_t>(io.rhs));
    io.dst = bit_cast<int32_t>(lhs / rhs);
  }
};

struct cfMod {
  __sio (
    __in (ch_float32)  lhs,
    __in (ch_float32)  rhs,
    __out (ch_float32) dst
  );

  void eval() {
    auto lhs = bit_cast<float>(static_cast<int32_t>(io.lhs));
    auto rhs = bit_cast<float>(static_cast<int32_t>(io.rhs));
    io.dst = bit_cast<int32_t>(fmod(lhs, rhs));
  }
};

///////////////////////////////////////////////////////////////////////////////

template <typename R>
auto ch_float32::do_neg() const {
  static_assert(std::is_same_v<R, ch_float32>, "invalid type");
  __source_location(1);
  ch_udf_comb<cfSub> udf;
  udf.io.lhs = 0.0f;
  udf.io.rhs = *this;
  return udf.io.dst;
}

template <typename R, typename U>
auto ch_float32::do_add(const U& other) const {
  static_assert(std::is_same_v<R, ch_float32>, "invalid type");
  __source_location(1);
  ch_udf_comb<cfAdd> udf;
  udf.io.lhs = *this;
  udf.io.rhs = other;
  return udf.io.dst;
}

template <typename R, typename U>
auto ch_float32::do_sub(const U& other) const {
  static_assert(std::is_same_v<R, ch_float32>, "invalid type");
  __source_location(1);
  ch_udf_comb<cfSub> udf;
  udf.io.lhs = *this;
  udf.io.rhs = other;
  return udf.io.dst;
}

template <typename R, typename U>
auto ch_float32::do_mul(const U& other) const {
  static_assert(std::is_same_v<R, ch_float32>, "invalid type");
  __source_location(1);
  ch_udf_comb<cfMul> udf;
  udf.io.lhs = *this;
  udf.io.rhs = other;
  return udf.io.dst;
}

template <typename R, typename U>
auto ch_float32::do_div(const U& other) const {
  static_assert(std::is_same_v<R, ch_float32>, "invalid type");
  __source_location(1);
  ch_udf_comb<cfDiv> udf;
  udf.io.lhs = *this;
  udf.io.rhs = other;
  return udf.io.dst;
}

template <typename R, typename U>
auto ch_float32::do_mod(const U& other) const {
  static_assert(std::is_same_v<R, ch_float32>, "invalid type");
  __source_location(1);
  ch_udf_comb<cfMod> udf;
  udf.io.lhs = *this;
  udf.io.rhs = other;
  return udf.io.dst;
}

///////////////////////////////////////////////////////////////////////////////

template <unsigned Delay>
auto ch_fadd(const ch_float32& lhs, const ch_float32& rhs, const ch_bool& enable = true) {
  __source_location(1);
  ch_udf_seq<sfAdd> udf(Delay);
  udf.io.en  = enable;
  udf.io.lhs = lhs;
  udf.io.rhs = rhs;
  return udf.io.dst;
}

template <unsigned Delay>
auto ch_fsub(const ch_float32& lhs, const ch_float32& rhs, const ch_bool& enable = true) {
  __source_location(1);
  ch_udf_seq<sfSub> udf(Delay);
  udf.io.en  = enable;
  udf.io.lhs = lhs;
  udf.io.rhs = rhs;
  return udf.io.dst;
}

template <unsigned Delay>
auto ch_fmul(const ch_float32& lhs, const ch_float32& rhs, const ch_bool& enable = true) {
  __source_location(1);
  ch_udf_seq<sfMul> udf(Delay);
  udf.io.en  = enable;
  udf.io.lhs = lhs;
  udf.io.rhs = rhs;
  return udf.io.dst;
}

template <unsigned Delay>
auto ch_fdiv(const ch_float32& lhs, const ch_float32& rhs, const ch_bool& enable = true) {
  __source_location(1);
  ch_udf_seq<sfDiv> udf(Delay);
  udf.io.en  = enable;
  udf.io.lhs = lhs;
  udf.io.rhs = rhs;
  return udf.io.dst;
}

}
}
