#include <cash.h>

using namespace cash::core;
using namespace cash::core_literals;
using namespace cash::sim;

class X {
public:
  X(int x) {}
  ~X() {}

  void operator()(const ch_bit1& w) const {
    //--
  }
};

int main(int argc, char **argv) {
  //--

  auto f = ch_function<X>(2);

  ch_bus<1> w(0);
  f(w);

  return 0;
}
