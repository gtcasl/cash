#include "common.h"

using namespace chdl::core_literals;

int g_debugbreak = 0;

static void debugbreak() {
  g_debugbreak = 1;
}

TEST_CASE("dogfood", "[debug]") {  
  TEST([]()->ch_logic {
    ch_bit8 a(0x1'0_h);
    return (a == 16 && a[4] == 1);
  });
}
