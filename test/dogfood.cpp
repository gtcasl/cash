#include "common.h"

int g_debugbreak = 0;

static void debugbreak() {
  g_debugbreak = 1;
}


TEST_CASE("dogfood", "[debug]") {  
  //--    
}
