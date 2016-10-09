#pragma once

#include "bus.h"

namespace chdl_internal {

template <bool Scale, unsigned N, unsigned M, char... Chars>
struct binary_literal_size;

template <unsigned N, unsigned M, char... Chars>
struct binary_literal_size<false, N, M, Chars...> {
  static constexpr unsigned eval() {
    return N;
  }
};

template <unsigned N, unsigned M, char Char, char... Chars>
struct binary_literal_size<false, N, M, Char, Chars...> {
  static constexpr unsigned eval() {
    static_assert(Char == '0' || Char == '1' || Char == 'e' || Char == 'E', "invalid binary number"); 
    return binary_literal_size<(Char == 'e' || Char == 'E'), N, M, Chars...>::eval();
  }
};

template <unsigned N, unsigned M, char... Chars>
struct binary_literal_size<true, N, M, Chars...> {
  static constexpr unsigned eval() {
    return M;
  }
};

template <unsigned N, unsigned M, char Char, char... Chars>
struct binary_literal_size<true, N, M, Char, Chars...> {
  static constexpr unsigned eval() {
    static_assert(Char >= '0' && Char <= '9', "invalid binary number"); 
    return binary_literal_size<true, N, (M * 10 + Char - '0'), Chars...>::eval();
  } 
};
  
template< char... Chars>
constexpr ch_bitv<binary_literal_size<false, sizeof...(Chars), 0, Chars...>::eval()> operator "" _b() {
  constexpr const char str[] = {Chars..., '\0'};
  return ch_bitv<binary_literal_size<false, sizeof...(Chars), 0, Chars...>::eval()>(str);
}

}
