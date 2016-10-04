#pragma once

#include "bus.h"

namespace chdl_internal {

template<char ...Chars>
constexpr ch_bitv<sizeof...(Chars)> operator "" _b() {
  return ch_bitv<sizeof...(Chars)>(0x0);
}

/*template<char ...Chars>
constexpr ch_bus<sizeof...(Chars)> operator "" _b() {
  return ch_bus<sizeof...(Chars)>(0x0);
}*/

/*template<char... Chars>
struct conv2bin;

template <char MSB>
struct binary_literal_size {
  static size_t size;
};
 
template <char MSB, char... REST>
struct binary_literal_size {
  static size_t size;
};

template<char ... Chars>
constexpr ch_bus< binary_literal_size<Chars...> > operator "" _b() {
  return ch_bus<sizeof...(Chars)>(0x0);
} 

template<char ... Chars>
constexpr ch_bitv< binary_literal_size<Chars...> > operator "" _b() {
  return ch_bitv<sizeof...(Chars)>(0x0);
}*/

}
