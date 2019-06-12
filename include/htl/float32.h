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

class ch_scfloat32 : public ch_scbit<32> {
public:
  using traits = system_traits<32, true, ch_scfloat32, ch_float32>;
  using base = ch_scbit<32>;

  ch_scfloat32(const system_buffer_ptr& buffer = make_system_buffer(32, "ch_scfloat32"))
    : base(buffer)
  {}

  ch_scfloat32(float other) : base(bit_cast<int32_t>(other)) {}

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
    return bit_cast<float>(static_cast<int32_t>(*this));
  }  
};

///////////////////////////////////////////////////////////////////////////////

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
    base::operator=(bit_cast<int32_t>(other));
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

  friend auto operator-(ch_float32& self);

  friend auto operator+(ch_float32& lhs, const ch_float32& rhs);

  friend auto operator-(ch_float32& lhs, const ch_float32& rhs);

  friend auto operator*(ch_float32& lhs, const ch_float32& rhs);

  friend auto operator/(ch_float32& lhs, const ch_float32& rhs);
};

///////////////////////////////////////////////////////////////////////////////

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

class sfAdd {
public:
  __scio (
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
  sc_pipereg<float> pipe_;
};

class sfSub {
public:
  __scio (
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
  sc_pipereg<float> pipe_;
};

class sfMul {
public:
  __scio (
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
  sc_pipereg<float> pipe_;
};

class sfDiv {
public:
  __scio (
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
  sc_pipereg<float> pipe_;
};

///////////////////////////////////////////////////////////////////////////////

struct cfAdd {
  __scio (
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
  __scio (
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
  __scio (
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
  __scio (
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

///////////////////////////////////////////////////////////////////////////////

inline auto operator-(ch_float32& self) {
  __source_location(1);
  ch_udf_comb<cfSub> udf;
  udf.io.lhs = 0.0f;
  udf.io.rhs = self;
  return udf.io.dst;
}

inline auto operator+(ch_float32& lhs, const ch_float32& rhs) {
  __source_location(1);
  ch_udf_comb<cfAdd> udf;
  udf.io.lhs = lhs;
  udf.io.rhs = rhs;
  return udf.io.dst;
}

inline auto operator-(ch_float32& lhs, const ch_float32& rhs) {
  __source_location(1);
  ch_udf_comb<cfSub> udf;
  udf.io.lhs = lhs;
  udf.io.rhs = rhs;
  return udf.io.dst;
}

inline auto operator*(ch_float32& lhs, const ch_float32& rhs) {
  __source_location(1);
  ch_udf_comb<cfMul> udf;
  udf.io.lhs = lhs;
  udf.io.rhs = rhs;
  return udf.io.dst;
}

inline auto operator/(ch_float32& lhs, const ch_float32& rhs) {
  __source_location(1);
  ch_udf_comb<cfDiv> udf;
  udf.io.lhs = lhs;
  udf.io.rhs = rhs;
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
