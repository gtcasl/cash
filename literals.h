#pragma once

#include "bitv.h"
#include "bus.h"

namespace chdl_internal {

//
// CHDL literal formats: XXX...[e0-9]_(b|o|d|h) using ' as separator
//

template <bool S, typename T, unsigned N, unsigned M, char... Chars>
struct lit_size;

template <typename T, unsigned N, unsigned M, char... Chars>
struct lit_size<false, T, N, M, Chars...> {
  static_assert(N > 0, "invalid literal size");
  static const unsigned value = N * T::logbase;
};

template <typename T, unsigned N, unsigned M, char Char, char... Chars>
struct lit_size<false, T, N, M, Char, Chars...> {  
  static_assert(T::is_digit(Char) || T::is_escape(Char) || T::is_extend(Char), "invalid literal value");
  static const unsigned value = lit_size<T::is_extend(Char), T, T::size(Char, N), M, Chars...>::value;
};

template <typename T, unsigned N, unsigned M, char... Chars>
struct lit_size<true, T, N, M, Chars...> {
  static_assert(M > 0 && M >= ((N-1) * T::logbase), "invalid literal size");
  static const unsigned value = M;
};

template <typename T, unsigned N, unsigned M, char Char, char... Chars>
struct lit_size<true, T, N, M, Char, Chars...> {
  static_assert(isdigit(Char), "invalid literal size");
  static const unsigned value = lit_size<true, T, N, (M * 10 + Char - '0'), Chars...>::value;
};

struct lit_bin {
  enum { logbase = 1 };
  static constexpr bool is_digit(char c) {
    return c == '0' || c == '1';
  }
  static constexpr bool is_extend(char c) {
    return (c == 'e' || c == 'E');
  }
  static constexpr bool is_escape(char c) {
    return (c == '\'');
  }
  static constexpr unsigned size(char c, unsigned N) {
    return (is_escape(c) || is_extend(c)) ? N : (N + 1);
  }
};

struct lit_oct {
  enum { logbase = 3 }; 
  static constexpr bool is_digit(char c) {
    return c >= '0' && c <= '7';
  }  
  static constexpr bool is_extend(char c) {
    return (c == 'e' || c == 'E');
  }
  static constexpr bool is_escape(char c) {
    return (c == '\'');
  } 
  static constexpr unsigned size(char c, unsigned N) {
    return (is_escape(c) || is_extend(c)) ? N : (N + 1);
  }   
};

struct lit_dec {
  enum { logbase = 4 };
  static constexpr bool is_digit(char c) {
    return c >= '0' && c <= '9';
  }     
  static constexpr bool is_extend(char c) {
    return (c == 'e' || c == 'E');
  }
  static constexpr bool is_escape(char c) {
    return (c == '\'');
  }
  static constexpr unsigned size(char c, unsigned N) {
    return (is_escape(c) || is_extend(c)) ? N : (N + 1);
  }
};

struct lit_hex {
  enum { logbase = 4 };
  static constexpr bool is_digit(char c) {
    return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f');
  }     
  static constexpr bool is_extend(char c) {
    return (c == 'p' || c == 'P');
  }
  static constexpr bool is_escape(char c) {
    return (c == '\'' || c == 'x' || c == 'X');
  }
  static constexpr unsigned size(char c, unsigned N) {
    return (c == 'x' || c == 'X') ? (N-1) : ((is_escape(c) || is_extend(c)) ? N : (N + 1));
  }
};

template <char... Chars>
struct lit_bin_size {
  static const unsigned value = lit_size<false, lit_bin, 0, 0, Chars...>::value;
};

template <char... Chars>
struct lit_oct_size {
  static const unsigned value = lit_size<false, lit_oct, 0, 0, Chars...>::value;
};

template <char... Chars>
struct lit_dec_size {
  static const unsigned value = lit_size<false, lit_dec, 0, 0, Chars...>::value;
};

template <char... Chars>
struct lit_hex_size {
  static const unsigned value = lit_size<false, lit_hex, 0, 0, Chars...>::value;
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
