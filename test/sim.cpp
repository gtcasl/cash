#include "common.h"

using namespace chdl::sim_literals;

__ch_enum(my_enum, 4)(
  idle = 0,
  execute,
  stats,
  done
); 

TEST_CASE("simulation tests", "[sim]") {  
  SECTION("test buses", "[bus][signal]") {
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
    TESTX([]()->bool {          
      ch_bus8 a(10), b(1), c(99), d(5), e(50);
      return (a == 10 && b > 0 && c < 100 && d >= 5 && e <= 50);
    });
  }
  SECTION("test bus enums", "[enum]") {    
    TESTX([]()->bool {          
      my_enum::bus_type a(my_enum::idle);
      return (a == 0);
    });
    TEST([]()->bool {
      my_enum::bus_type a;
      a = my_enum::execute;
      return (a == 1);
    });
  }  
}
