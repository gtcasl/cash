#pragma once

#include <cash.h>

namespace ch {
namespace htl {

using namespace core;
using namespace extension;

#define ALTFP_SP_ADD_SUB 7
#define ALTFP_SP_MULT    5
#define ALTFP_SP_DIV     6

class ch_float32;

template <unsigned Delay = 1>
struct fAdd : public udf_seq<Delay, false, ch_float32, ch_float32, ch_float32, ch_bool> {

  void eval(udf_output& dst, const udf_inputs& srcs) override {
    uint32_t enable = srcs[2].word(0);
    if (enable) {
      uint32_t lhs = srcs[0].word(0);
      uint32_t rhs = srcs[1].word(0);
      float result = *(float*)&lhs + *(float*)&rhs;
      dst.word(0) = *(uint32_t*)&result;
    }
  }

  void to_verilog(std::ostream& out) override {
    out << "fp_add __fp_add$id(.clock($clock), .clk_en($src2), "
           ".dataa($src0), .datab($src1), .result($dst));";
  }
};

template <unsigned Delay = 1>
struct fSub : public udf_seq<Delay, false, ch_float32, ch_float32, ch_float32, ch_bool> {

  void eval(udf_output& dst, const udf_inputs& srcs) override {
    uint32_t enable = srcs[2].word(0);
    if (enable) {
      uint32_t lhs = srcs[0].word(0);
      uint32_t rhs = srcs[1].word(0);
      float result = *(float*)&lhs - *(float*)&rhs;
      dst.word(0) = *(uint32_t*)&result;
    }
  }

  void to_verilog(std::ostream& out) override {
    out << "fp_sub __fp_sub$id(.clock($clock), .clk_en($src2), "
           ".dataa($src0), .datab($src1), .result($dst));";
  }
};

template <unsigned Delay>
struct fMul : public udf_seq<Delay, false, ch_float32, ch_float32, ch_float32, ch_bool> {

  void eval(udf_output& dst, const udf_inputs& srcs) override {
    uint32_t enable = srcs[2].word(0);
    if (enable) {
      uint32_t lhs = srcs[0].word(0);
      uint32_t rhs = srcs[1].word(0);
      float result = *(float*)&lhs * *(float*)&rhs;
      dst.word(0) = *(uint32_t*)&result;
    }
  }

  void to_verilog(std::ostream& out) override {
    out << "fp_mult __fp_mult$id(.clock($clock), .clk_en($src2), "
           ".dataa($src0), .datab($src1), .result($dst));";
  }
};

template <unsigned Delay>
struct fDiv : public udf_seq<Delay, false, ch_float32, ch_float32, ch_float32, ch_bool> {

  void eval(udf_output& out, const udf_inputs& srcs) override {
    uint32_t enable = srcs[2].word(0);
    if (enable) {
      uint32_t lhs = srcs[0].word(0);
      uint32_t rhs = srcs[1].word(0);
      float result = *(float*)&lhs / *(float*)&rhs;
      out.word(0) = *(uint32_t*)&result;
    }
  }

  void to_verilog(std::ostream& out) override {
    out << "fp_div __fp_div$id(.clock($clock), .clk_en($src2), "
           ".dataa($src0), .datab($src1), .result($dst));";
  }
};

class ch_float32;

class ch_scfloat32 : public ch_scbit<32> {
public:
  using traits = scalar_traits<32, true, ch_scfloat32, ch_float32>;
  using base = ch_scbit<32>;

  explicit ch_scfloat32(const scalar_buffer_ptr& buffer = make_scalar_buffer(32))
    : base(buffer)
  {}

  ch_scfloat32(float other) : base(bitcast<uint32_t>(other)) {}

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

  CH_SCALAR_INTERFACE(ch_scfloat32)

  friend bool operator==(const ch_scfloat32& lhs, const ch_scfloat32& rhs) {
    return (lhs.as_scint() == rhs.as_scint());
  }

  friend bool operator!=(const ch_scfloat32& lhs, const ch_scfloat32& rhs) {
    return (lhs.as_scint() != rhs.as_scint());
  }

  friend bool operator<(const ch_scfloat32& lhs, const ch_scfloat32& rhs) {
    return (lhs.as_scint() < rhs.as_scint());
  }

  friend bool operator<=(const ch_scfloat32& lhs, const ch_scfloat32& rhs) {
    return (lhs.as_scint() <= rhs.as_scint());
  }

  friend bool operator>(const ch_scfloat32& lhs, const ch_scfloat32& rhs) {
    return (lhs.as_scint() >= rhs.as_scint());
  }

  friend bool operator>=(const ch_scfloat32& lhs, const ch_scfloat32& rhs) {
    return (lhs.as_scint() >= rhs.as_scint());
  }

  explicit operator float() const {
    return bitcast<float>(static_cast<uint32_t>(*this));
  }  
};

class ch_float32 : public ch_bit32 {
public:
  using traits = logic_traits<32, true, ch_float32, ch_scfloat32>;
  using base = ch_bit32;

  explicit ch_float32(const logic_buffer_ptr& buffer = make_logic_buffer(32, CH_CUR_SLOC))
    : base(buffer)
  {}

  ch_float32(float other, CH_SLOC) : base(bitcast<uint32_t>(other), sloc) {}

  explicit ch_float32(const ch_scbit<32>& other, CH_SLOC) : base(other, sloc) {}

  explicit ch_float32(const ch_bit<32>& other, CH_SLOC) : base(other, sloc) {}

  ch_float32(const ch_float32& other, CH_SLOC) : base(other, sloc) {}

  ch_float32(ch_float32&& other) : base(std::move(other)) {}

  ch_float32& operator=(const ch_float32& other) {
    base::operator=(other);
    return *this;
  }

  ch_float32& operator=(ch_float32&& other) {
    base::operator=(std::move(other));
    return *this;
  }

  CH_LOGIC_INTERFACE(ch_float32)

  friend auto operator==(ch_float32 lhs, const ch_float32& rhs) {
    return (lhs.as_int() == rhs.as_int());
  }

  friend auto operator!=(ch_float32 lhs, const ch_float32& rhs) {
    return (lhs.as_int() != rhs.as_int());
  }

  friend auto operator<(ch_float32 lhs, const ch_float32& rhs) {
    return (lhs.as_int() < rhs.as_int());
  }

  friend auto operator<=(ch_float32 lhs, const ch_float32& rhs) {
    return (lhs.as_int() <= rhs.as_int());
  }

  friend auto operator>(ch_float32 lhs, const ch_float32& rhs) {
    return (lhs.as_int() >= rhs.as_int());
  }

  friend auto operator>=(ch_float32 lhs, const ch_float32& rhs) {
    return (lhs.as_int() >= rhs.as_int());
  }
};

template <unsigned Delay>
auto ch_fadd(const ch_float32& lhs, const ch_float32& rhs, const ch_bool& enable = true, __sloc) {
  return ch_udf<fAdd<Delay>>(lhs, rhs, enable, sloc);
}

template <unsigned Delay>
auto ch_fsub(const ch_float32& lhs, const ch_float32& rhs, const ch_bool& enable = true, __sloc) {
  return ch_udf<fSub<Delay>>(lhs, rhs, enable, sloc);
}

template <unsigned Delay>
auto ch_fmul(const ch_float32& lhs, const ch_float32& rhs, const ch_bool& enable = true, __sloc) {
  return ch_udf<fMul<Delay>>(lhs, rhs, enable, sloc);
}

template <unsigned Delay>
auto ch_fdiv(const ch_float32& lhs, const ch_float32& rhs, const ch_bool& enable = true, __sloc) {
  return ch_udf<fDiv<Delay>>(lhs, rhs, enable, sloc);
}

}
}
