#pragma once

#include <cash.h>

namespace ch {
namespace htl {

using namespace ch::logic;

template <std::size_t N>
class ch_counter {
public:

  ch_counter() {}

protected:

  ch_uint<log2up(N)> value;
};

}
}


int main() {
  ch::htl::ch_counter<4> qq;
  return 0;
}
