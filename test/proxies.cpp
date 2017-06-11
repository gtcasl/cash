#include "common.h"

using namespace cash::core_literals;

TEST_CASE("proxies tests", "[proxies]") {   
  SECTION("test subscript", "[subscript]") {
    TEST([]()->ch_logic {
      ch_bit4 a(1010_b);
      return (a[0] == a[2] && a[1] == a[3]);
    });
    TEST([]()->ch_logic {
      ch_bit4 a(1010_b);
      return (a[0] == a[2] && a[1] == a[3]);
    });
    TEST([]()->ch_logic {
       ch_bit4 a(0110_b);
       return (a[0] == a[3] && a[1] == a[2]);
    });    
    TEST([]()->ch_logic {
      ch_bit4 a;
      ch_logic x = a[3];
      ch_logic y = a[2];
      x = 1_b;
      y = 0_b;
      return (a[2] == 0_b && a[3] == 1_b);
    });
  }
  
  SECTION("test slice", "[slice]") {
    TEST([]()->ch_logic {
      ch_bit4 a(1100_b);
      ch_bit2 c = a.slice<2>(1) ^ 01_b;
      return (c == 11_b);
    });
    TEST([]()->ch_logic {
      ch_bit4 a(1100_b);
      ch_bit2 c = a.aslice<2>(1) ^ 01_b;
      return (c == 10_b);
    });
    TEST([]()->ch_logic {
      ch_bit4 a;
      a.slice<3>(0) = '0';
      a[3] = '1';
      return a == 1000_b;
    });
    TEST([]()->ch_logic {
      ch_bit4 a;
      ch_bit4 b = a;     
      a.slice<3>(0) = '0';
      a[3] = '1';
      return a == 1000_b;
    });
    TEST([]()->ch_logic {
      ch_bit4 a;
      ch_bit4 b = a;
      a.slice<3>(0) = '0';
      ch_logic x = a[3];
      x = '1';
      return a == 1000_b;
    });
    TEST([]()->ch_logic {
      ch_bit4 a;
      a[0] = '0';
      a[1] = '1';
      a[2] = '1';
      a[3] = '0';
      a[0] = '1';
      a[3] = '1';
      a.slice<2>(1) = '0';     
      return a == 1001_b;
    });
    TEST([]()->ch_logic {
      ch_bit4 a;
      ch_bit2 x = a.slice<2>(0);
      ch_bit2 y = a.slice<2>(2);
      a.slice<2>(1) = '0';     
      x = '1';
      y = '1';
      return a == 0101_b;
    });
    TEST([]()->ch_logic {         
      ch_bit4 a, b(1);
      ch_bit4 c = a + b;
      ch_bit2 x = a.slice<2>(0);
      ch_bit2 y = a.slice<2>(1);
      ch_bit2 z = a.slice<2>(2);
      x[1] = 1; // x[1] and a[1] should change
      x = 0;    // x[0] and a[0] should change    
      z = 1;    // z and a[3] should change
      y = 0;    // y only should change
      return (c == 0111_b);
    });
    TEST([]()->ch_logic {
     ch_bit4 a;
     ch_logic x = a[3];
     ch_logic x2 = a[3];
     ch_bit2  y = a.slice<2>(2);
     ch_logic z = y[0];
     x = 1_b;
     z = 0_b;
     return (a[2] == 0_b && a[3] == 1_b);
    });
    TEST([]()->ch_logic {
     ch_bit4 a;
     ch_logic x = a[0];
     ch_logic y = a[1];     
     ch_bit<3> z = a.slice<3>(0);
     ch_logic w = a[3];
     x = 0_b;
     y = 1_b;     
     z = 001_b;
     w = 1_b;
     return (a == 1010_b && a.slice<2>(1) == 01_b);
    });
  }
  
  SECTION("test concat", "[concat]") {
    TEST([]()->ch_logic {          
    {
      ch_bit4 x;
      x.slice<3>().slice<2>() = 0x1_h2;    
    }
    
    {
      const ch_bit4 x(0x0);
      auto q = x.slice<3>();
      auto q2 = x.slice<3>().slice<2>();
      //x.slice<3>() = 0x1_h3;
      //x.slice<3>().slice<2>() = 0x1_h2;    
    }
    
    {
      ch_bit2 x(0x0);
      ch_bit2 y(0x0);
      (x, y) = 0x1_h4;    
      (y, x) = 0x1_h4;
      (y, x).slice<2>() = 0x1_h2;
    }
    
    {
      const ch_bit2 x(0x0);
      ch_bit2 y(0x0);
      ch_bit2 z(0x0);
      ch_bit2 w(0x0);
      (y, z, w) = 0x1_h6;
      auto q = (0_b, 1_b, 0_b);
      auto q2 = (0_b, y, 0_b);
      auto q3 = (x, y).template slice<2>();
      auto q4 = (y, x).template slice<2>();
      auto q5 = (x, y, z).template slice<2>();
      //(x, y) = 0x1_h4;    
      //(y, x) = 0x1_h4;
      //(x, y, z) = 0x1_h6;
      //(y, x, z) = 0x1_h6;
    }
      ch_bit4 a(1100_b);
      ch_bit<5> c = (a, 1_b);
      return (c == 11001_b);
    });
    TEST([]()->ch_logic {
      ch_bit4 a(1100_b);
      ch_bit<5> c = (1_b, a);
      return (c == 11100_b);
    });
    TEST([]()->ch_logic {
      ch_bit<6> c = (011_b, 011_b);
      return (c == 011011_b);
    });
    TEST([]()->ch_logic {
      ch_bit<6> c = (10_b, 1011_b);
      return (c == 101011_b);
    });
    TEST([]()->ch_logic {
      ch_bit4 a(1100_b);
      ch_bit4 c = (a[3], a[2], a[1], a[0]);
      return (c == 1100_b && (a[3], a[0]) == 10_b);
    });
    TEST([]()->ch_logic {
       ch_bit4 a(1100_b);
       ch_bit4 c = (a[3], a[0], a[0], a[0]);
       return (c == 1000_b);
    });
  }
}
