#include "common.h"

struct inverter {
  __io (
    (ch_in<ch_bit2>) in,
    (ch_out<ch_bit2>) out
  );
  void describe() {
    auto x = ~io.in;
    __tap(x);
    io.out = x;
  }
};

TEST_CASE("simulation", "[sim]") {
  SECTION("tracer", "[tracer]") {
    TESTX([]()->bool {
      ch_module<inverter> module;
      ch_poke(module.io.in, 2);
      ch_tracer tracer(std::cout, module);
      tracer.run();
      return (1 == ch_peek<int>(module.io.out));
    });
  }

  SECTION("vcdtracer", "[vcdtracer]") {
    TESTX([]()->bool {
      ch_module<inverter> module;
      ch_poke(module.io.in, 2);
      ch_vcdtracer tracer(std::cout, module);
      tracer.run();
      return (1 == ch_peek<int>(module.io.out));
    });
  }

  SECTION("stats", "[stats]") {
    TESTX([]()->bool {
      ch_module<inverter> module;
      ch_dumpStats(std::cout, module);
      return true;
    });
  }
}
