#pragma once

#include "bus.h"

namespace chdl_internal {

//
// CHDL literal formats: XXX...[e0-9]_(b|o|d|h)
//

template <bool S, typename F, unsigned N, unsigned M, char... Chars>
struct bin_literal_size;

template <typename F, unsigned N, unsigned M, char... Chars>
struct bin_literal_size<false, F, N, M, Chars...> {
  static constexpr unsigned eval() {
    return N * F::logbase;
  }
};

template <typename F, unsigned N, unsigned M, char Char, char... Chars>
struct bin_literal_size<false, F, N, M, Char, Chars...> {
  static constexpr unsigned eval() {
    static_assert(F::valid(Char) || Char == 'e' || Char == 'E', "invalid binary number"); 
    return bin_literal_size<(Char == 'e' || Char == 'E'), F, N, M, Chars...>::eval();
  }
};

template <typename F, unsigned N, unsigned M, char... Chars>
struct bin_literal_size<true, F, N, M, Chars...> {
  static constexpr unsigned eval() {
    return M;
  }
};

template <typename F, unsigned N, unsigned M, char Char, char... Chars>
struct bin_literal_size<true, F, N, M, Char, Chars...> {
  static constexpr unsigned eval() {
    static_assert(isdigit(Char), "invalid binary size value"); 
    return bin_literal_size<true, F, N, (M * 10 + Char - '0'), Chars...>::eval();
  } 
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
  
template< char... Chars>
constexpr ch_bitv<bin_literal_size<false, lit_bin, sizeof...(Chars), 0, Chars...>::eval()> operator "" _b() {
  constexpr const char str[] = {Chars..., 'b', '\0'};
  return ch_bitv<bin_literal_size<false, lit_bin, sizeof...(Chars), 0, Chars...>::eval()>(str);
}

template< char... Chars>
constexpr ch_bitv<bin_literal_size<false, lit_oct, sizeof...(Chars), 0, Chars...>::eval()> operator "" _o() {
  constexpr const char str[] = {Chars..., 'o', '\0'};
  return ch_bitv<bin_literal_size<false, lit_oct, sizeof...(Chars), 0, Chars...>::eval()>(str);
}

template< char... Chars>
constexpr ch_bitv<bin_literal_size<false, lit_dec, sizeof...(Chars), 0, Chars...>::eval()> operator "" _d() {
  constexpr const char str[] = {Chars..., 'd', '\0'};
  return ch_bitv<bin_literal_size<false, lit_dec, sizeof...(Chars), 0, Chars...>::eval()>(str);
}

template< char... Chars>
constexpr ch_bitv<bin_literal_size<false, lit_hex, sizeof...(Chars), 0, Chars...>::eval()> operator "" _h() {
  constexpr const char str[] = {Chars..., 'h', '\0'};
  return ch_bitv<bin_literal_size<false, lit_hex, sizeof...(Chars), 0, Chars...>::eval()>(str);
}

}
