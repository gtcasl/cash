#pragma once

#include <cash.h>

namespace ch {
namespace htl {

using namespace extension;

#define ALTFP_SP_ADD_SUB 7
#define ALTFP_SP_MULT    5
#define ALTFP_SP_DIV     6

class ch_float32;

template <unsigned Delay = 1>
struct fAdd : public udf_seq<Delay, true, ch_float32, ch_float32, ch_float32> {

  void eval(bitvector& out, const std::vector<bitvector>& srcs) override {
    assert(out.size() == 32 && srcs.size() == 2);
    uint32_t a(srcs[0].word(0));
    uint32_t b(srcs[1].word(0));
    float c(*(float*)&a + *(float*)&b);
    out.word(0) = *(uint32_t*)&c;
  }

  void to_verilog(std::ostream& out) override {
    out << "fp_add __fp_add$id__(.clock($clock), .clk_en($enable), "
           ".dataa($src0), .datab($src1), .result($dst));";
  }
};

template <unsigned Delay = 1>
struct fSub : public udf_seq<Delay, true, ch_float32, ch_float32, ch_float32> {

  void eval(bitvector& out, const std::vector<bitvector>& srcs) override {
    assert(out.size() == 32 && srcs.size() == 2);
    uint32_t a(srcs[0].word(0));
    uint32_t b(srcs[1].word(0));
    float c(*(float*)&a - *(float*)&b);
    out.word(0) = *(uint32_t*)&c;
  }

  void to_verilog(std::ostream& out) override {
    out << "fp_sub __fp_sub$id__(.clock($clock), .clk_en($enable), "
           ".dataa($src0), .datab($src1), .result($dst));";
  }
};

template <unsigned Delay>
struct fMult : public udf_seq<Delay, true, ch_float32, ch_float32, ch_float32> {

  void eval(bitvector& out, const std::vector<bitvector>& srcs) override {
    assert(out.size() == 32 && srcs.size() == 2);
    uint32_t a(srcs[0].word(0));
    uint32_t b(srcs[1].word(0));
    float c(*(float*)&a * *(float*)&b);
    out.word(0) = *(uint32_t*)&c;
  }

  void to_verilog(std::ostream& out) override {
    out << "fp_mult __fp_mult$id __(.clock($clock), .clk_en($enable), "
           ".dataa($src0), .datab($src1), .result($dst));";
  }
};

template <unsigned Delay>
struct fDiv : public udf_seq<Delay, true, ch_float32, ch_float32, ch_float32> {

  void eval(bitvector& out, const std::vector<bitvector>& srcs) override {
    assert(out.size() == 32 && srcs.size() == 2);
    uint32_t a(srcs[0].word(0));
    uint32_t b(srcs[1].word(0));
    float c(*(float*)&a / *(float*)&b);
    out.word(0) = *(uint32_t*)&c;
  }

  void to_verilog(std::ostream& out) override {
    out << "fp_div __fp_div$id __(.clock($clock), .clk_en($enable), "
           ".dataa($src0), .datab($src1), .result($dst));";
  }
};

class ch_float32 : public ch_int<32> {
public:
  using traits = logic_traits<32, true, ch_float32, ch_int<32>>;
  using base = ch_int<32>;

  ch_float32(const logic_buffer_ptr& buffer = make_logic_buffer(32, CH_SRC_LOCATION))
    : base(buffer)
  {}

  ch_float32(const ch_float32& rhs,
             const source_location& sloc = CH_SRC_LOCATION)
    : base(rhs, sloc)
  {}

  ch_float32(ch_float32&& rhs) : base(std::move(rhs)) {}

  explicit ch_float32(const ch_logic<32>& rhs,
                      const source_location& sloc = CH_SRC_LOCATION)
    : base(rhs, sloc)
  {}

  explicit ch_float32(const ch_scalar<32>& rhs,
                      const source_location& sloc = CH_SRC_LOCATION)
    : base(rhs, sloc)
  {}

  explicit ch_float32(float rhs,
                      const source_location& sloc = CH_SRC_LOCATION)
    : base(*(uint32_t*)&rhs, sloc)
  {}

  ch_float32& operator=(const ch_float32& rhs) {
    base::operator=(rhs);
    return *this;
  }

  ch_float32& operator=(ch_float32&& rhs) {
    base::operator=(std::move(rhs));
    return *this;
  }

  ch_float32& operator=(float rhs) {
    base::operator=(*(uint32_t*)&rhs);
    return *this;
  }

  // compare operators

  auto operator<(const ch_float32& rhs) const {
    return base::operator<(rhs);
  }

  auto operator<=(const ch_float32& rhs) const {
    return base::operator<=(rhs);
  }

  auto operator>(const ch_float32& rhs) const {
    return base::operator>(rhs);
  }

  auto operator>=(const ch_float32& rhs) const {
    return base::operator>=(rhs);
  }

  // arithmetic operators

  auto operator+(const ch_float32& rhs) const {
    return ch_udf<fAdd<1>>(*this, rhs);
  }

  auto operator-(const ch_float32& rhs) const {
    return ch_udf<fSub<1>>(*this, rhs);
  }

  auto operator*(const ch_float32& rhs) const {
    return ch_udf<fMult<1>>(*this, rhs);
  }

  auto operator/(const ch_float32& rhs) const {    
    return ch_udf<fDiv<1>>(*this, rhs);
  }

protected:

  CH_FRIEND_OP1((), ==, const ch_float32&, float)
  CH_FRIEND_OP1((), !=, const ch_float32&, float)
  CH_FRIEND_OP1((), <, const ch_float32&, float)
  CH_FRIEND_OP1((), <=, const ch_float32&, float)
  CH_FRIEND_OP1((), >, const ch_float32&, float)
  CH_FRIEND_OP1((), >=, const ch_float32&, float)

  CH_FRIEND_OP1((), +, const ch_float32&, float)
  CH_FRIEND_OP1((), -, const ch_float32&, float)
  CH_FRIEND_OP1((), *, const ch_float32&, float)
  CH_FRIEND_OP1((), /, const ch_float32&, float)
};

}
}
