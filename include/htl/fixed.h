#pragma once

#include <cash.h>

namespace ch {
namespace htl {

using namespace core;
using namespace extension;

// |1|<- N-F-1 bits ->|<--- F bits -->|
// |S|IIIIIIIIIIIIIIII|FFFFFFFFFFFFFFF|

template <unsigned N, unsigned F>
class ch_fixed;

template <unsigned N, unsigned F>
class ch_scfixed : public ch_scbit<N> {
public:  
  static_assert(N >= (F+1), "invalid size");
  using traits = scalar_traits<N, true, ch_scfixed, ch_fixed<N, F>>;
  using base = ch_scbit<N>;
  static constexpr unsigned I = N-F;

  explicit ch_scfixed(const scalar_buffer_ptr& buffer = make_scalar_buffer(N))
    : base(buffer)
  {}

  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  ch_scfixed(const U& other) : base(other) {}

  ch_scfixed(const ch_scbit<N>& other) : base(other) {}

  template <typename U,
            CH_REQUIRE_0(is_bitvector_extended_type_v<U>)>
  explicit ch_scfixed(const U& other) : base(other) {}

  explicit ch_scfixed(const ch_bit<N>& other) : base(other) {}

  ch_scfixed(const ch_scfixed& other) : base(other) {}

  ch_scfixed(ch_scfixed&& other) : base(std::move(other)) {}

  ch_scfixed& operator=(const ch_scfixed& other) {
    base::operator=(other);
    return *this;
  }

  ch_scfixed& operator=(ch_scfixed&& other) {
    base::operator=(std::move(other));
    return *this;
  }

  CH_SCALAR_INTERFACE(ch_scfixed)

  friend auto operator==(const ch_scfixed& lhs, const ch_scfixed& rhs) {
    return (lhs.as_scint() == rhs.as_scint());
  }

  friend auto operator!=(const ch_scfixed& lhs, const ch_scfixed& rhs) {
    return (lhs.as_scint() != rhs.as_scint());
  }

  friend auto operator<(const ch_scfixed& lhs, const ch_scfixed& rhs) {
    return (lhs.as_scint() < rhs.as_scint());
  }

  friend auto operator<=(const ch_scfixed& lhs, const ch_scfixed& rhs) {
    return (lhs.as_scint() <= rhs.as_scint());
  }

  friend auto operator>(const ch_scfixed& lhs, const ch_scfixed& rhs) {
    return (lhs.as_scint() >= rhs.as_scint());
  }

  friend auto operator>=(const ch_scfixed& lhs, const ch_scfixed& rhs) {
    return (lhs.as_scint() >= rhs.as_scint());
  }

  friend auto operator-(const ch_scfixed& self) {
    return (-self.as_scint()).template as<ch_scfixed>();
  }

  friend auto operator+(const ch_scfixed& lhs, const ch_scfixed& rhs) {
    return (lhs.as_scint() + rhs.as_scint()).template as<ch_scfixed>();
  }

  friend auto operator-(const ch_scfixed& lhs, const ch_scfixed& rhs) {
    return (lhs.as_scint() - rhs.as_scint()).template as<ch_scfixed>();
  }

  friend auto operator*(const ch_scfixed& lhs, const ch_scfixed& rhs) {
    auto ret = ((lhs.as_scint().template pad<N+F>() * rhs.as_scint()) >> F).template slice<N>();
    return ret.template as<ch_scfixed>();
  }

  friend auto operator/(const ch_scfixed& lhs, const ch_scfixed& rhs) {
    auto ret = ((lhs.as_scint().template pad<N+F>() << F) / rhs.as_scint()).template slice<N>();
    return ret.template as<ch_scfixed>();
  }

  static auto fromInt(const ch_scint<I>& in) {
    return ch_scfixed((in.template pad<N>() << F));
  }

  static auto fromReal(double in) {
    static_assert(N <= 64, "invalid size");
    auto value = (int64_t)(double(in) * (int64_t(1) << F));
    return ch_scfixed(value);
  }
};

template <unsigned N, unsigned F>
class ch_fixed : public ch_bit<N> {
public:  
  static_assert(N >= (F+1), "invalid size");
  using traits = logic_traits<N, true, ch_fixed, ch_scfixed<N, F>>;
  using base = ch_bit<N>;
  static constexpr unsigned I = N-F;

  explicit ch_fixed(const logic_buffer_ptr& buffer = make_logic_buffer(N, CH_CUR_SLOC))
    : base(buffer)
  {}

  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  ch_fixed(const U& other, CH_SLOC) : base(other, sloc) {}

  ch_fixed(const ch_scbit<N>& other, CH_SLOC) : base(other, sloc) {}

  template <typename U,
            CH_REQUIRE_0(is_bitvector_extended_type_v<U>)>
  explicit ch_fixed(const U& other, CH_SLOC) : base(other, sloc) {}

  explicit ch_fixed(const ch_bit<N>& other, CH_SLOC) : base(other, sloc) {}

  ch_fixed(const ch_fixed& other, CH_SLOC) : base(other, sloc) {}

  ch_fixed(ch_fixed&& other) : base(std::move(other)) {}

  ch_fixed& operator=(const ch_fixed& other) {
    base::operator=(other);
    return *this;
  }

  ch_fixed& operator=(ch_fixed&& other) {
    base::operator=(std::move(other));
    return *this;
  }

  CH_LOGIC_INTERFACE(ch_fixed)

  friend auto operator==(ch_fixed lhs, const ch_fixed& rhs) {
    return (lhs.as_int() == rhs.as_int());
  }

  friend auto operator!=(ch_fixed lhs, const ch_fixed& rhs) {
    return (lhs.as_int() != rhs.as_int());
  }

  friend auto operator<(ch_fixed lhs, const ch_fixed& rhs) {
    return (lhs.as_int() < rhs.as_int());
  }

  friend auto operator<=(ch_fixed lhs, const ch_fixed& rhs) {
    return (lhs.as_int() <= rhs.as_int());
  }

  friend auto operator>(ch_fixed lhs, const ch_fixed& rhs) {
    return (lhs.as_int() >= rhs.as_int());
  }

  friend auto operator>=(ch_fixed lhs, const ch_fixed& rhs) {
    return (lhs.as_int() >= rhs.as_int());
  }

  friend auto operator-(ch_fixed self) {
    return (-self.as_int()).template as<ch_fixed>();
  }

  friend auto operator+(ch_fixed lhs, const ch_fixed& rhs) {
    return (lhs.as_int() + rhs.as_int()).template as<ch_fixed>();
  }

  friend auto operator-(ch_fixed lhs, const ch_fixed& rhs) {
    return (lhs.as_int() - rhs.as_int()).template as<ch_fixed>();
  }

  friend auto operator*(ch_fixed lhs, const ch_fixed& rhs) {
    auto ret = ((lhs.as_int().template pad<N+F>() * rhs.as_int()) >> F).template slice<N>();
    return ret.template as<ch_fixed>();
  }

  friend auto operator/(ch_fixed lhs, const ch_fixed& rhs) {
    auto ret = ((lhs.as_int().template pad<N+F>() << F) / rhs.as_int()).template slice<N>();
    return ret.template as<ch_fixed>();
  }

  static auto fromInt(const ch_int<I>& in, CH_SLOC) {
    return ch_fixed((in.template pad<N>() << F), sloc);
  }

  static auto fromReal(double in, CH_SLOC) {
    static_assert(N <= 64, "invalid size");
    auto value = (int64_t)(double(in) * (int64_t(1) << F));
    return ch_fixed(value, sloc);
  }
};

}
}
