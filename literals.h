#pragma once

#include "bitv.h"
#include "bus.h"

namespace chdl_internal {

//
// CHDL literal formats: XXX...[e0-9]_(b|o|d|h)
//

template <bool S, typename F, unsigned N, unsigned M, char... Chars>
struct lit_size;

template <typename F, unsigned N, unsigned M, char... Chars>
struct lit_size<false, F, N, M, Chars...> {
  static const unsigned value = N * F::logbase;
};

template <typename F, unsigned N, unsigned M, char Char, char... Chars>
struct lit_size<false, F, N, M, Char, Chars...> {
  static_assert(F::valid(Char) || Char == 'e' || Char == 'E', "invalid binary number");
  static const unsigned value = lit_size<(Char == 'e' || Char == 'E'), F, N, M, Chars...>::value;
};

template <typename F, unsigned N, unsigned M, char... Chars>
struct lit_size<true, F, N, M, Chars...> {
  static const unsigned value = M;
};

template <typename F, unsigned N, unsigned M, char Char, char... Chars>
struct lit_size<true, F, N, M, Char, Chars...> {
  static_assert(isdigit(Char), "invalid binary size value");
  static const unsigned value = lit_size<true, F, N, (M * 10 + Char - '0'), Chars...>::value;
};

struct lit_bin {
  enum { logbase = 1 };
  static constexpr bool valid(char c) {
    return c == '0' || c == '1';
  }     
};

struct lit_oct {
  enum { logbase = 3 };
  static constexpr bool valid(char c) {
    return c >= '0' && c <= '7';
  }     
};

struct lit_dec {
  enum { logbase = 4 };
  static constexpr bool valid(char c) {
    return c >= '0' && c <= '9';
  }     
};

struct lit_hex {
  enum { logbase = 4 };
  static constexpr bool valid(char c) {
    return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f');
  }     
};

template <char... Chars>
struct lit_bin_size {
  static const unsigned value = lit_size<false, lit_bin, sizeof...(Chars), 0, Chars...>::value;
};

template <char... Chars>
struct lit_oct_size {
  static const unsigned value = lit_size<false, lit_oct, sizeof...(Chars), 0, Chars...>::value;
};

template <char... Chars>
struct lit_dec_size {
  static const unsigned value = lit_size<false, lit_dec, sizeof...(Chars), 0, Chars...>::value;
};

template <char... Chars>
struct lit_hex_size {
  static const unsigned value = lit_size<false, lit_hex, sizeof...(Chars), 0, Chars...>::value;
};
  
namespace core_literals {

template< char... Chars>
constexpr ch_bitv<lit_bin_size<Chars...>::value> operator "" _b() {
  constexpr const char str[] = {Chars..., 'b', '\0'};
  return ch_bitv<lit_bin_size<Chars...>::value>(bitvector(str));
}

template< char... Chars>
constexpr ch_bitv<lit_oct_size<Chars...>::value> operator "" _o() {
  constexpr const char str[] = {Chars..., 'o', '\0'};
  return ch_bitv<lit_oct_size<Chars...>::value>(bitvector(str));
}

template< char... Chars>
constexpr ch_bitv<lit_dec_size<Chars...>::value> operator "" _d() {
  constexpr const char str[] = {Chars..., 'd', '\0'};
  return ch_bitv<lit_dec_size<Chars...>::value>(bitvector(str));
}

template< char... Chars>
constexpr ch_bitv<lit_hex_size<Chars...>::value> operator "" _h() {
  constexpr const char str[] = {Chars..., 'h', '\0'};
  return ch_bitv<lit_hex_size<Chars...>::value>(bitvector(str));
}

}

namespace sim_literals {

template< char... Chars>
constexpr ch_bus<lit_bin_size<Chars...>::value> operator "" _b() {
  constexpr const char str[] = {Chars..., 'b', '\0'};
  return ch_bus<lit_bin_size<Chars...>::value>(bitvector(str));
}

template< char... Chars>
constexpr ch_bus<lit_oct_size<Chars...>::value> operator "" _o() {
  constexpr const char str[] = {Chars..., 'o', '\0'};
  return ch_bus<lit_oct_size<Chars...>::value>(bitvector(str));
}

template< char... Chars>
constexpr ch_bus<lit_dec_size<Chars...>::value> operator "" _d() {
  constexpr const char str[] = {Chars..., 'd', '\0'};
  return ch_bus<lit_dec_size<Chars...>::value>(bitvector(str));
}

template< char... Chars>
constexpr ch_bus<lit_hex_size<Chars...>::value> operator "" _h() {
  constexpr const char str[] = {Chars..., 'h', '\0'};
  return ch_bus<lit_hex_size<Chars...>::value>(bitvector(str));
}

}

}
