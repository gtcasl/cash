#include "common.h"

using namespace cash::sim_literals;

__struct (s2_t,(
  (ch_bit2) a,
  (ch_bit2) b
));

__struct (s32_t,(
  (ch_bit1)  a,
  (ch_bit2)  b,
  (ch_bit4)  c,
  (ch_bit8)  d,
  (ch_bit1)  e,
  (ch_bit16) f
));
 
 __union (u2_t,(
   (ch_bit2) a,
   (ch_bit2) b
 ));

__enum (my_enum, 4,(
  idle = 0,
  execute,
  stats,
  done
)); 

TEST_CASE("simulation", "[sim]") {
  SECTION("bus", "[bus]") {
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
      a.read(0, &x, sizeof(x), 0, 4);
      return (x == 4);
    });
    TESTX([]()->bool {          
      ch_bus4 a(4);
      uint32_t x;
      a.read(0, &x, sizeof(x), 0, 4);
      return (x == 4);
    });
    TESTX([]()->bool {          
      ch_bus4 a;
      uint8_t x = 4;
      a.write(0, &x, sizeof(x), 0, 4);
      return (a == 4);
    });
    TESTX([]()->bool {          
      ch_bus4 a;
      uint32_t x = 4;
      a.write(0, &x, sizeof(x), 0, 4);
      return (a == 4);
    });
    TESTX([]()->bool {
      ch_bus4 in, out;
      auto foo = [](const ch_bit4& x)->ch_bit4 {
        return x + 1;
      };
      auto func = ch_function(foo);
      out = func(in);
      ch_simulator sim(func);
      in = 7;
      sim.run(1);
      return (out == 8);
    });
    TESTX([]()->bool {      
      ch_bus4 in, out;
      auto foo = [](const ch_bit4& x)->ch_bit4 {
        return x + 1;
      };
      auto func = ch_function(foo);
      out = func(in);
      ch_simulator sim(func);
      in = 0x7_h4;
      sim.run(1);
      return (out == 8);
    });
  }
  SECTION("structs", "[struct]") {
    TESTX([]()->bool {          
      s2_t::bus_t s2;
      s2.a = 01_b;
      s2.b = 10_b;
      return (s2 == 1001_b);
    });    
    TESTX([]()->bool {          
      s2_t::bus_t s2;
      s2 = 1001_b;
      return (s2 == 1001_b);
    });
    TESTX([]()->bool {          
      s2_t::bus_t s1, s2;
      s1 = 0;
      s2 = s1;      
      s2 = 1001_b;
      return (s2 == 1001_b);
    });
    TESTX([]()->bool {
      s32_t::bus_t a(0);
      uint32_t v = 0xABCD71E3;
      a.write(0, &v, sizeof(v));
      return (a == 0xABCD71E3);
    });
    TESTX([]()->bool {
      s32_t::bus_t a(0);
      uint32_t v = 0xABCD71E3;
      a.write(0, &v, sizeof(v), 4, 28);
      return (a == (0xABCD71E3 >> 4));
    });
    TESTX([]()->bool {
      s32_t::bus_t a(0);
      uint32_t v = 0xABCD71E3;
      a.write(4, &v, sizeof(v), 0, 28);
      return (a == (0xABCD71E3 << 4));
    });
    TESTX([]()->bool {
      s32_t::bus_t a(0xABCD71E3);
      uint32_t v = 0;
      a.read(0, &v, sizeof(v));
      return (v == 0xABCD71E3);
    });
    TESTX([]()->bool {
      s32_t::bus_t a;
      a = 0xABCD71E3;
      uint32_t v = 0;
      a.read(0, &v, sizeof(v), 4, 28);
      return (v == (0xABCD71E3 >> 4));
    });
    TESTX([]()->bool {
      s32_t::bus_t a(0xABCD71E3);
      uint32_t v = 0;
      a.read(4, &v, sizeof(v), 0, 28);
      return (v == (0xABCD71E3 << 4));
    });
  }  
  SECTION("unions", "[union]") {
    TESTX([]()->bool {          
      u2_t::bus_t u2;
      u2.a = 01_b;
      u2.b = 10_b;
      return (u2 == 10_b);
    });
  }  
  SECTION("enums", "[enum]") {
    TESTX([]()->bool {          
      my_enum::bus_t a(my_enum::idle);
      return (0 == a);
    });
    TESTX([]()->bool {
      my_enum::bus_t a;
      a = my_enum::execute;
      return (a == 1);
    });
  }  
}
