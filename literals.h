#pragma once

#include "bit.h"
#include "bus.h"

namespace cash_internal {

//
// CASH literals format: XXXXXX_(b|o|h)[size] using ' as separator
//

template <bool X, typename T, unsigned N, char... Chars>
struct lit_size;

template <typename T, unsigned N, char... Chars>
struct lit_size<false, T, N, Chars...> {
  static_assert(N > 0, "invalid literal size");
  static const unsigned value = N;
};

template <typename T, unsigned N, char Char, char... Chars>
struct lit_size<false, T, N, Char, Chars...> {  
  static_assert(T::is_digit(Char) || T::is_escape(Char), "invalid literal value");
  static const unsigned value = lit_size<false, T, T::size(Char, N), Chars...>::value;
};

template <typename T, unsigned N, char... Chars>
struct lit_size<true, T, N, Chars...> {
  static const unsigned value = N;
};

template <typename T, unsigned N, char Char, char... Chars>
struct lit_size<true, T, N, Char, Chars...> {  
  static_assert(T::is_digit(Char) || T::is_escape(Char), "invalid literal value");
  static const unsigned value = lit_size<true, T, T::sizex(Char, N), Chars...>::value;
};

struct lit_bin {
  static constexpr bool is_digit(char c) {
    return c == '0' || c == '1';
  }
  static constexpr bool is_escape(char c) {
    return (c == '\'');
  }
  static constexpr unsigned size(char c, unsigned N) {
    return is_escape(c) ? N : (N + 1);
  }
  static constexpr unsigned chr2int(char c) {
    return (c - '0');
  }
  static constexpr unsigned sizex(char c, unsigned N) {
    return is_escape(c) ? N : (N ? (N + 1) : chr2int(c));
  }
};

struct lit_oct {
  static constexpr bool is_digit(char c) {
    return c >= '0' && c <= '7';
  }  
  static constexpr bool is_escape(char c) {
    return (c == '\'');
  }
  static constexpr unsigned size(char c, unsigned N) {
    return is_escape(c) ? N : (N + 3);
  }
  static constexpr unsigned chr2int(char c) {
    return (c - '0');
  }
  static constexpr unsigned sizex(char c, unsigned N) {
    return is_escape(c) ? N : (N ? (N + 3) : (chr2int(c) ? (ilog2(chr2int(c)) + 1) : 0));
  }   
};

struct lit_hex {
  static constexpr bool is_digit(char c) {
    return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f');
  }    
  static constexpr bool is_escape(char c) {
    return (c == '\'' || c == 'x' || c == 'X');
  }
  static constexpr unsigned size(char c, unsigned N) {
    return (c == 'x' || c == 'X') ? 0 : (is_escape(c) ? N : (N + 4));
  }
  static constexpr unsigned chr2int(char c) {
    return (c >= '0' && c <= '9') ? (c - '0') :
          ((c >= 'A' && c <= 'F') ? (c - 'A' + 10) : 
          ((c >= 'a' && c <= 'f') ? (c - 'a' + 10) : 0));
  }
  static constexpr unsigned sizex(char c, unsigned N) {
    return (c == 'x' || c == 'X') ? 0 : (is_escape(c) ? N : (N ? (N + 4) : (chr2int(c) ? (ilog2(chr2int(c)) + 1) : 0)));
  }
};

template <char... Chars>
struct lit_bin_size {
  static const unsigned value = lit_size<false, lit_bin, 0, Chars...>::value;
};

template <char... Chars>
struct lit_oct_size {
  static const unsigned value = lit_size<false, lit_oct, 0, Chars...>::value;
};

template <char... Chars>
struct lit_hex_size {
  static const unsigned value = lit_size<false, lit_hex, 0, Chars...>::value;
};

template <char... Chars>
struct lit_bin_sizex {
  static const unsigned value = lit_size<true, lit_bin, 0, Chars...>::value;
};

template <char... Chars>
struct lit_oct_sizex {
  static const unsigned value = lit_size<true, lit_oct, 0, Chars...>::value;
};

template <char... Chars>
struct lit_hex_sizex {
  static const unsigned value = lit_size<true, lit_hex, 0, Chars...>::value;
};

#define CH_DEF_LITERALS_IMPL(x, ...) \
  CH_FOR_EACH(x, CH_SEP_SPACE, __VA_ARGS__)

#define CH_DEF_LITERALS(x) \
  CH_DEF_LITERALS_IMPL(x, 2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,29,30,31,32) \
  CH_DEF_LITERALS_IMPL(x, 33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64) \
  CH_DEF_LITERALS_IMPL(x, 65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92) \
  CH_DEF_LITERALS_IMPL(x, 93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128)
  
namespace core_literals {

  template< char... Chars>
  constexpr ch_bit<lit_bin_size<Chars...>::value> operator "" _b() {
    constexpr const char str[] = {Chars..., 'b', '\0'};
    return ch_bit<lit_bin_size<Chars...>::value>(bitvector(str, lit_bin_size<Chars...>::value));
  }
  
  template< char... Chars>
  constexpr ch_bit<lit_oct_size<Chars...>::value> operator "" _o() {
    constexpr const char str[] = {Chars..., 'o', '\0'};
    return ch_bit<lit_oct_size<Chars...>::value>(bitvector(str, lit_oct_size<Chars...>::value));
  }
  
  template< char... Chars>
  constexpr ch_bit<lit_hex_size<Chars...>::value> operator "" _h() {
    constexpr const char str[] = {Chars..., 'h', '\0'};
    return ch_bit<lit_hex_size<Chars...>::value>(bitvector(str, lit_hex_size<Chars...>::value));
  }


#define CH_CORE_LITERALS(i, x) \
  template< char... Chars> \
  constexpr ch_bit<x> operator "" _b##x() { \
    static_assert(x >= lit_bin_sizex<Chars...>::value, "literal value overflow"); \
    constexpr const char str[] = {Chars..., 'b', '\0'}; \
    return ch_bit<x>(bitvector(str, x)); \
  } \
  template< char... Chars> \
  constexpr ch_bit<x> operator "" _o##x() { \
    static_assert(x >= lit_oct_sizex<Chars...>::value, "literal value overflow"); \
    constexpr const char str[] = {Chars..., 'o', '\0'}; \
    return ch_bit<x>(bitvector(str, x)); \
  } \
  template< char... Chars> \
  constexpr ch_bit<x> operator "" _h##x() { \
    static_assert(x >= lit_hex_sizex<Chars...>::value, "literal value overflow"); \
    constexpr const char str[] = {Chars..., 'h', '\0'}; \
    return ch_bit<x>(bitvector(str, x)); \
  }
  
  CH_DEF_LITERALS(CH_CORE_LITERALS)
#undef CH_CORE_LITERALs
}

namespace sim_literals {

  template< char... Chars>
  constexpr ch_bus<lit_bin_size<Chars...>::value> operator "" _b() {
    constexpr const char str[] = {Chars..., 'b', '\0'};
    return ch_bus<lit_bin_size<Chars...>::value>(bitvector(str, lit_bin_size<Chars...>::value));
  }
  
  template< char... Chars>
  constexpr ch_bus<lit_oct_size<Chars...>::value> operator "" _o() {
    constexpr const char str[] = {Chars..., 'o', '\0'};
    return ch_bus<lit_oct_size<Chars...>::value>(bitvector(str, lit_oct_size<Chars...>::value));
  }
  
  template< char... Chars>
  constexpr ch_bus<lit_hex_size<Chars...>::value> operator "" _h() {
    constexpr const char str[] = {Chars..., 'h', '\0'};
    return ch_bus<lit_hex_size<Chars...>::value>(bitvector(str, lit_hex_size<Chars...>::value));
  }

#define CH_SIM_LITERALS(i, x) \
  template< char... Chars> \
  constexpr ch_bus<x> operator "" _b##x() { \
    static_assert(x >= lit_bin_sizex<Chars...>::value, "literal value overflow"); \
    constexpr const char str[] = {Chars..., 'b', '\0'}; \
    return ch_bus<x>(bitvector(str, x)); \
  } \
  template< char... Chars> \
  constexpr ch_bus<x> operator "" _o##x() { \
    static_assert(x >= lit_oct_sizex<Chars...>::value, "literal value overflow"); \
    constexpr const char str[] = {Chars..., 'o', '\0'}; \
    return ch_bus<x>(bitvector(str, x)); \
  } \
  template< char... Chars> \
  constexpr ch_bus<x> operator "" _h##x() { \
    static_assert(x >= lit_hex_sizex<Chars...>::value, "literal value overflow"); \
    constexpr const char str[] = {Chars..., 'h', '\0'}; \
    return ch_bus<x>(bitvector(str, x)); \
  }
  
  CH_DEF_LITERALS(CH_SIM_LITERALS)
#undef CH_SIM_LITERALs
}

#undef CH_DEF_LITERALS_IMPL
#undef CH_SIM_LITERALs

}
