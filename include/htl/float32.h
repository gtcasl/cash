#pragma once

#include <cash.h>

namespace ch {
namespace htl {

using namespace logic;
using namespace extension;

#define ALTFP_SP_ADD_SUB 7
#define ALTFP_SP_MULT    5
#define ALTFP_SP_DIV     6

class ch_float32;

struct sfAdd : public udf_seq<ch_float32, ch_float32, ch_float32> {

  void eval(udf_output& dst, const udf_inputs& srcs) override {
    auto lhs = bit_cast<float>(static_cast<int32_t>(srcs[0]));
    auto rhs = bit_cast<float>(static_cast<int32_t>(srcs[1]));
    dst = bit_cast<int32_t>(lhs + rhs);
  }

  void to_verilog(std::ostream& out) override {
    out << "fp_add __fp_add$id(.clock($clock), .clk_en($src2), "
           ".dataa($src0), .datab($src1), .result($dst));";
  }
};

struct sfSub : public udf_seq<ch_float32, ch_float32, ch_float32> {

  void eval(udf_output& dst, const udf_inputs& srcs) override {
    auto lhs = bit_cast<float>(static_cast<int32_t>(srcs[0]));
    auto rhs = bit_cast<float>(static_cast<int32_t>(srcs[1]));
    dst = bit_cast<int32_t>(lhs - rhs);
  }

  void to_verilog(std::ostream& out) override {
    out << "fp_sub __fp_sub$id(.clock($clock), .clk_en($src2), "
           ".dataa($src0), .datab($src1), .result($dst));";
  }
};

struct sfMul : public udf_seq<ch_float32, ch_float32, ch_float32> {

  void eval(udf_output& dst, const udf_inputs& srcs) override {
    auto lhs = bit_cast<float>(static_cast<int32_t>(srcs[0]));
    auto rhs = bit_cast<float>(static_cast<int32_t>(srcs[1]));
    dst = bit_cast<int32_t>(lhs * rhs);
  }

  void to_verilog(std::ostream& out) override {
    out << "fp_mul __fp_mul$id(.clock($clock), .clk_en($src2), "
           ".dataa($src0), .datab($src1), .result($dst));";
  }
};

struct sfDiv : public udf_seq<ch_float32, ch_float32, ch_float32> {

  void eval(udf_output& dst, const udf_inputs& srcs) override {
    auto enable = static_cast<bool>(srcs[2]);
    if (enable) {
      auto lhs = bit_cast<float>(static_cast<int32_t>(srcs[0]));
      auto rhs = bit_cast<float>(static_cast<int32_t>(srcs[1]));
      dst = bit_cast<int32_t>(lhs / rhs);
    }
  }

  void to_verilog(std::ostream& out) override {
    out << "fp_div __fp_div$id(.clock($clock), .clk_en($src2), "
           ".dataa($src0), .datab($src1), .result($dst));";
  }
};

struct cfAdd : public udf_comb<ch_float32, ch_float32, ch_float32> {
  void eval(udf_output& dst, const udf_inputs& srcs) override {
    auto lhs = bit_cast<float>(static_cast<int32_t>(srcs[0]));
    auto rhs = bit_cast<float>(static_cast<int32_t>(srcs[1]));
    dst = bit_cast<int32_t>(lhs + rhs);
  }
};

struct cfSub : public udf_comb<ch_float32, ch_float32, ch_float32> {
  void eval(udf_output& dst, const udf_inputs& srcs) override {
    auto lhs = bit_cast<float>(static_cast<int32_t>(srcs[0]));
    auto rhs = bit_cast<float>(static_cast<int32_t>(srcs[1]));
    dst = bit_cast<int32_t>(lhs - rhs);
  }
};

struct cfMul : public udf_comb<ch_float32, ch_float32, ch_float32> {
  void eval(udf_output& dst, const udf_inputs& srcs) override {
    auto lhs = bit_cast<float>(static_cast<int32_t>(srcs[0]));
    auto rhs = bit_cast<float>(static_cast<int32_t>(srcs[1]));
    dst = bit_cast<int32_t>(lhs * rhs);
  }
};

struct cfDiv : public udf_comb<ch_float32, ch_float32, ch_float32> {
  void eval(udf_output& dst, const udf_inputs& srcs) override {
    auto lhs = bit_cast<float>(static_cast<int32_t>(srcs[0]));
    auto rhs = bit_cast<float>(static_cast<int32_t>(srcs[1]));
    dst = bit_cast<int32_t>(lhs / rhs);
  }
};

class ch_float32;

class ch_scfloat32 : public ch_scbit<32> {
public:
  using traits = system_traits<32, true, ch_scfloat32, ch_float32>;
  using base = ch_scbit<32>;

  ch_scfloat32(const system_buffer_ptr& buffer = make_system_buffer(32))
    : base(buffer)
  {}

  ch_scfloat32(float other) : base(bit_cast<uint32_t>(other)) {}

  explicit ch_scfloat32(const ch_scbit<32>& other) : base(other) {}

  ch_scfloat32(const ch_scfloat32& other) : base(other) {}

  ch_scfloat32(ch_scfloat32&& other) : base(std::move(other)) {}

  ch_scfloat32& operator=(const ch_scfloat32& other) {
    base::operator=(other);
    return *this;
  }

  ch_scfloat32& operator=(ch_scfloat32&& other) {
    base::operator=(std::move(other));
    return *this;
  }

  CH_SYSTEM_INTERFACE(ch_scfloat32)

  friend auto operator==(const ch_scfloat32& lhs, const ch_scfloat32& rhs) {
    return (lhs.as_scint() == rhs.as_scint());
  }

  friend auto operator!=(const ch_scfloat32& lhs, const ch_scfloat32& rhs) {
    return (lhs.as_scint() != rhs.as_scint());
  }

  friend auto operator<(const ch_scfloat32& lhs, const ch_scfloat32& rhs) {
    return (lhs.as_scint() < rhs.as_scint());
  }

  friend auto operator<=(const ch_scfloat32& lhs, const ch_scfloat32& rhs) {
    return (lhs.as_scint() <= rhs.as_scint());
  }

  friend auto operator>(const ch_scfloat32& lhs, const ch_scfloat32& rhs) {
    return (lhs.as_scint() >= rhs.as_scint());
  }

  friend auto operator>=(const ch_scfloat32& lhs, const ch_scfloat32& rhs) {
    return (lhs.as_scint() >= rhs.as_scint());
  }

  friend auto operator-(const ch_scfloat32& self) {
    auto f_self = bit_cast<float>(static_cast<int32_t>(system_accessor::data(self)));
    return ch_scfloat32(0.0f - f_self);
  }

  friend auto operator+(const ch_scfloat32& lhs, const ch_scfloat32& rhs) {
    auto f_lhs = bit_cast<float>(static_cast<int32_t>(system_accessor::data(lhs)));
    auto f_rhs = bit_cast<float>(static_cast<int32_t>(system_accessor::data(rhs)));
    return ch_scfloat32(f_lhs + f_rhs);
  }

  friend auto operator-(const ch_scfloat32& lhs, const ch_scfloat32& rhs) {
    auto f_lhs = bit_cast<float>(static_cast<int32_t>(system_accessor::data(lhs)));
    auto f_rhs = bit_cast<float>(static_cast<int32_t>(system_accessor::data(rhs)));
    return ch_scfloat32(f_lhs - f_rhs);
  }

  friend auto operator*(const ch_scfloat32& lhs, const ch_scfloat32& rhs) {
    auto f_lhs = bit_cast<float>(static_cast<int32_t>(system_accessor::data(lhs)));
    auto f_rhs = bit_cast<float>(static_cast<int32_t>(system_accessor::data(rhs)));
    return ch_scfloat32(f_lhs * f_rhs);
  }

  friend auto operator/(const ch_scfloat32& lhs, const ch_scfloat32& rhs) {
    auto f_lhs = bit_cast<float>(static_cast<int32_t>(system_accessor::data(lhs)));
    auto f_rhs = bit_cast<float>(static_cast<int32_t>(system_accessor::data(rhs)));
    return ch_scfloat32(f_lhs / f_rhs);
  }

  explicit operator float() const {
    return bit_cast<float>(static_cast<uint32_t>(*this));
  }  
};

class ch_float32 : public ch_bit32 {
public:
  using traits = logic_traits<32, true, ch_float32, ch_scfloat32>;
  using base = ch_bit32;

  ch_float32(const logic_buffer& buffer = logic_buffer(32, "ch_float32"))
    : base(buffer)
  {}

  ch_float32(float other)
    : ch_float32(logic_buffer(32, "ch_float32")) {
    __source_location(1);
    this->operator=(other);
  }

  explicit ch_float32(const ch_scbit<32>& other)
    : ch_float32(logic_buffer(32, "ch_float32")) {
    __source_location(1);
    this->operator=(other);
  }

  explicit ch_float32(const ch_bit<32>& other)
    : ch_float32(logic_buffer(32, "ch_float32")) {
    __source_location(1);
    this->operator=(other);
  }

  ch_float32(const ch_float32& other)
    : ch_float32(logic_buffer(32, "ch_float32")) {
    __source_location(1);
    this->operator=(other);
  }

  ch_float32(ch_float32&& other) : base(std::move(other)) {}

  ch_float32& operator=(float other) {
    __source_location(1);
    base::operator=(bit_cast<uint32_t>(other));
    return *this;
  }

  ch_float32& operator=(const ch_scbit<32>& other) {
    __source_location(1);
    base::operator=(other);
    return *this;
  }

  ch_float32& operator=(const ch_bit<32>& other) {
    __source_location(1);
    base::operator=(other);
    return *this;
  }

  ch_float32& operator=(const ch_float32& other) {
    __source_location(1);
    base::operator=(other);
    return *this;
  }

  ch_float32& operator=(ch_float32&& other) {
    __source_location(1);
    base::operator=(std::move(other));
    return *this;
  }

  CH_LOGIC_INTERFACE(ch_float32)

  friend auto operator==(ch_float32& lhs, const ch_float32& rhs) {
    __source_location(1);
    return (lhs.as_int() == rhs.as_int());
  }

  friend auto operator!=(ch_float32& lhs, const ch_float32& rhs) {
    __source_location(1);
    return (lhs.as_int() != rhs.as_int());
  }

  friend auto operator<(ch_float32& lhs, const ch_float32& rhs) {
    __source_location(1);
    return (lhs.as_int() < rhs.as_int());
  }

  friend auto operator<=(ch_float32& lhs, const ch_float32& rhs) {
    __source_location(1);
    return (lhs.as_int() <= rhs.as_int());
  }

  friend auto operator>(ch_float32& lhs, const ch_float32& rhs) {
    __source_location(1);
    return (lhs.as_int() >= rhs.as_int());
  }

  friend auto operator>=(ch_float32& lhs, const ch_float32& rhs) {
    __source_location(1);
    return (lhs.as_int() >= rhs.as_int());
  }

  friend auto operator-(ch_float32& self) {
    __source_location(1);
    return ch_udf<cfSub>()(0.0f, self);
  }

  friend auto operator+(ch_float32& lhs, const ch_float32& rhs) {
    __source_location(1);
    return ch_udf<cfAdd>()(lhs, rhs);
  }

  friend auto operator-(ch_float32& lhs, const ch_float32& rhs) {
    __source_location(1);
    return ch_udf<cfSub>()(lhs, rhs);
  }

  friend auto operator*(ch_float32& lhs, const ch_float32& rhs) {
    __source_location(1);
    return ch_udf<cfMul>()(lhs, rhs);
  }

  friend auto operator/(ch_float32& lhs, const ch_float32& rhs) {
    __source_location(1);
    return ch_udf<cfDiv>()(lhs, rhs);
  }
};

template <unsigned Delay>
auto ch_fadd(const ch_float32& lhs, const ch_float32& rhs, const ch_bool& enable = true) {
  __source_location(1);
  return ch_delayEn(ch_udf<sfAdd>()(lhs, rhs), enable, Delay - 1);
}

template <unsigned Delay>
auto ch_fsub(const ch_float32& lhs, const ch_float32& rhs, const ch_bool& enable = true) {
  __source_location(1);
  return ch_delayEn(ch_udf<sfSub>()(lhs, rhs), enable, Delay - 1);
}

template <unsigned Delay>
auto ch_fmul(const ch_float32& lhs, const ch_float32& rhs, const ch_bool& enable = true) {
  __source_location(1);
  return ch_delayEn(ch_udf<sfMul>()(lhs, rhs), enable, Delay - 1);
}

template <unsigned Delay>
auto ch_fdiv(const ch_float32& lhs, const ch_float32& rhs, const ch_bool& enable = true) {
  __source_location(1);
  return ch_delayEn(ch_udf<sfDiv>()(lhs, rhs), enable, Delay - 1);
}

}
}
