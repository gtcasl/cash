#include "common.h"

using namespace chdl::sim_literals;

 __ch_struct(s2_t,(
  (ch_bit2) a,
  (ch_bit2) b
));
 
 __ch_union(u2_t,(
   (ch_bit2) a,
   (ch_bit2) b
 ));

__ch_enum(my_enum, 4,(
  idle = 0,
  execute,
  stats,
  done
)); 

TEST_CASE("simulation tests", "[sim]") {  
  SECTION("test buses", "[bus][signal]") {
    TESTX([]()->bool {          
      ch_bus4 a(1), b(2), c;
      c = (uint8_t)a + (uint8_t)b;
      return (c == 3);
    });
    TESTX([]()->bool {          
      ch_bus64 a(1), b(2), c;
      c = (uint64_t)a + (uint64_t)b;
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
      ch_bus64 a(1), b;
      b = a;
      return (b == 1);
    });
    TESTX([]()->bool {          
      ch_bus64 a(1), b;
      b = a;
      b = 4;
      return (b == 4);
    });
    TESTX([]()->bool {          
      ch_bus64 a(1);
      a = 10;
      return (a == 10);
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
    TESTX([]()->bool {          
      ch_bus4 a(4);
      uint8_t x;
      a.read(&x, sizeof(x));
      return (x == 4);
    });
    TESTX([]()->bool {          
      ch_bus4 a(4);
      uint32_t x;
      a.read(&x, sizeof(x));
      return (x == 4);
    });
    TESTX([]()->bool {          
      ch_bus4 a;
      uint8_t x = 4;
      a.write(&x, sizeof(x));
      return (a == 4);
    });
    TESTX([]()->bool {          
      ch_bus4 a;
      uint32_t x = 4;
      a.write(&x, sizeof(x));
      return (a == 4);
    });
  }
  SECTION("test bus structs", "[struct]") {    
    TESTX([]()->bool {          
      s2_t::bus_type s2;
      s2.a = 01_b;
      s2.b = 10_b;
      return (s2 == 1001_b);
    });    
    TESTX([]()->bool {          
      s2_t::bus_type s2;
      s2 = 1001_b;
      return (s2 == 1001_b);
    });
    TESTX([]()->bool {          
      s2_t::bus_type s1, s2;
      s1 = 0;
      s2 = s1;      
      s2 = 1001_b;
      return (s2 == 1001_b);
    });
  }  
  SECTION("test bus unions", "[union]") {    
    TESTX([]()->bool {          
      u2_t::bus_type u2;
      u2.a = 01_b;
      u2.b = 10_b;
      return (u2 == 10_b);
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
