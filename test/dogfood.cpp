#include "common.h"
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/punctuation/remove_parens.hpp>

using namespace chdl::core_literals;

int g_debugbreak = 0;

static void debugbreak() {
  g_debugbreak = 1;
}

TEST_CASE("dogfood", "[debug]") {        
  //-- 
}
