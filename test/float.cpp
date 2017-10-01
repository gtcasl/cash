#include "common.h"

TEST_CASE("floats", "[floats]") {
  SECTION("basic", "[basic]") {
    TEST([]()->ch_bit1 {
      ch_float x(0.0f);
      ch_bit32 y(0);
      return x == y;
    });
    TEST([]()->ch_bit1 {
      ch_bit32 x(0);
      ch_float y = x;
      return y == 0;
    });
    
    TEST([]()->ch_bit1 {
      ch_float x(0.5f);
      return x == 0x3f000000;
    });
    
    TEST([]()->ch_bit1 {
      ch_float x(1.0f);
      return x == 0x3f800000;
    });
    
    TEST([]()->ch_bit1 {
      ch_float x(2.0f);
      return x == 0x40000000;
    });
  }
  
  SECTION("arithmetic test", "[math]") {
    TEST([]()->ch_bit1 {
      ch_float x(0.5f), y(0.0f), z;
      z = x * y;
      return z == 0;
    });
    
    TEST([]()->ch_bit1 {
      ch_float x(0.5f), y(0.5f), z;
      z = x * y;
      return z == 0x3e800000;
    });
    
    TEST([]()->ch_bit1 {
      ch_float x(0.5f), y(1.0f), z;
      z = x * y;
      return z == 0x3f000000;
    });
    
    TEST([]()->ch_bit1 {
      ch_float x(0.5f), y(2.0f), z;
      z = x * y;
      return z == 0x3f800000;
    });
    
    TEST([]()->ch_bit1 {
      ch_float x(0.5f), y(1.5f), z;
      z = x + y;
      return z == 0x40000000;
    });
    
    TEST([]()->ch_bit1 {
      ch_float x(2.5f), y(0.5f), z;
      z = x - y;
      return z == 0x40000000;
    });
  }
}
