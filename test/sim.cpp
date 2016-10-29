#include "common.h"

using namespace chdl::sim_literals;

TEST_CASE("simulation", "[sim]") {  
  TESTX([]()->bool {          
    ch_bus4 a(1), b(2), c;
    c.write<uint8_t>(a.read<uint8_t>() + b.read<uint8_t>());
    return (c == 3);
  });
  TESTX([]()->bool {          
    ch_bus4 a(1), b(2), c;
    c = a;
    c = b;
    return (c == 2);
  });
  TESTX([]()->bool {          
    ch_bus4 a(1), b, c;
    b = a;
    c = b;
    return (c == 1);
  });
  TESTX([]()->bool {          
    ch_bus4 a(1), b, c;
    b = a;
    c = b;
    b = 2;
    return (b == 2 && c == 1);
  });
}
