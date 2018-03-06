#include "common.h"

struct inverter {
  __io (
    __in(ch_bit2)  in,
    __out(ch_bit2) out
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
      ch_device<inverter> device;
      device.io.in = 2;
      ch_tracer tracer(std::cout, device);
      tracer.run();
      return (1 == (int)device.io.out);
    });
  }

  SECTION("vcdtracer", "[vcdtracer]") {
    TESTX([]()->bool {
      ch_device<inverter> device;
      device.io.in = 2;
      ch_vcdtracer tracer(std::cout, device);
      tracer.run();
      return (1 == (int)device.io.out);
    });
  }

  SECTION("stats", "[stats]") {
    TESTX([]()->bool {
      ch_device<inverter> device;
      ch_dumpStats(std::cout, device);
      return true;
    });
  }
}
