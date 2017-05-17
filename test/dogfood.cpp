#include "common.h"

using namespace cash::core_literals;

int g_debugbreak = 0;

static void debugbreak() {
  g_debugbreak = 1;
}

TEST_CASE("dogfood", "[debug]") { 
  /*TEST([]()->ch_logic {
    ch_bit<512> a(2);
    auto b = a >> 1;  
    return (b[0] == 1);
  });*/
}
