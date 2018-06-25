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
struct fAdd : public udf_seq<Delay, false, ch_float32, ch_float32, ch_float32, ch_float32> {

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
struct fSub : public udf_seq<Delay, false, ch_float32, ch_float32, ch_float32, ch_float32> {

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
struct fMult : public udf_seq<Delay, false, ch_float32, ch_float32, ch_float32, ch_float32> {

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
struct fDiv : public udf_seq<Delay, false, ch_float32, ch_float32, ch_float32, ch_float32> {

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

template <unsigned Delay>
ch_float32 ch_fadd(const ch_float32& lhs, const ch_float32& rhs, const ch_bool& enable, const source_location&);

template <unsigned Delay>
ch_float32 ch_fsub(const ch_float32& lhs, const ch_float32& rhs, const ch_bool& enable, const source_location&);

template <unsigned Delay>
ch_float32 ch_fmult(const ch_float32& lhs, const ch_float32& rhs, const ch_bool& enable, const source_location&);

template <unsigned Delay>
ch_float32 ch_fdiv(const ch_float32& lhs, const ch_float32& rhs, const ch_bool& enable, const source_location&);

class ch_float32 : public logic_op_compare<ch_float32,
                            logic_op_relational<ch_float32, ch_bit32>> {
public:
  using traits = logic_traits<32, true, ch_float32, ch_scbit<32>>;
  using base = logic_op_compare<ch_float32,
                 logic_op_relational<ch_float32, ch_bit32>>;

  explicit ch_float32(const logic_buffer_ptr& buffer = make_logic_buffer(32, CH_CUR_SLOC))
    : base(buffer)
  {}

  ch_float32(float rhs, CH_SLOC) : base(*(uint32_t*)&rhs, sloc) {}

  ch_float32(const ch_float32& rhs, CH_SLOC) : base(rhs, sloc) {}

  ch_float32(ch_float32&& rhs) : base(std::move(rhs)) {}

  explicit ch_float32(const ch_bit<32>& rhs, CH_SLOC) : base(rhs, sloc) {}

  explicit ch_float32(const ch_scbit<32>& rhs, CH_SLOC) : base(rhs, sloc) {}

  ch_float32& operator=(const ch_float32& rhs) {
    base::operator=(rhs);
    return *this;
  }

  ch_float32& operator=(ch_float32&& rhs) {
    base::operator=(std::move(rhs));
    return *this;
  }

  template <unsigned Delay>
  friend auto ch_fadd(const ch_float32& lhs, const ch_float32& rhs, const ch_bool& enable = true, __sloc) {
    return ch_udf<fAdd<Delay>>(lhs, rhs, enable, sloc);
  }

  template <unsigned Delay>
  friend auto ch_fsub(const ch_float32& lhs, const ch_float32& rhs, const ch_bool& enable = true, __sloc) {
    return ch_udf<fSub<Delay>>(lhs, rhs, enable, sloc);
  }

  template <unsigned Delay>
  friend auto ch_fmult(const ch_float32& lhs, const ch_float32& rhs, const ch_bool& enable = true, __sloc) {
    return ch_udf<fMult<Delay>>(lhs, rhs, enable, sloc);
  }

  template <unsigned Delay>
  friend auto ch_fdiv(const ch_float32& lhs, const ch_float32& rhs, const ch_bool& enable = true, __sloc) {
    return ch_udf<fDiv<Delay>>(lhs, rhs, enable, sloc);
  }

  CH_LOGIC_INTERFACE(ch_float32)
};

}
}
