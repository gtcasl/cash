#include "common.h"

namespace {

template <typename T>
struct inverter {
  __io (
    __in(T)  in,
    __out(T) out
  );
  void describe() {
    auto x = ~io.in;
    __tap(x);
    io.out = x;
  }
};

}

TEST_CASE("simulation", "[sim]") {
  SECTION("tracer", "[tracer]") {
    TESTX([]()->bool {
      ch_device<inverter<ch_bit2>> device;
      device.io.in = 2;
      ch_tracer tracer(std::cout, device);
      auto y = device.io.out ^ 3_h;
      tracer.add_trace("y", y);
      tracer.run();
      return (1 == device.io.out);
    });
  }

  SECTION("vcdtracer", "[vcdtracer]") {
    TESTX([]()->bool {
      ch_device<inverter<ch_bit2>> device1;
      ch_device<inverter<ch_int2>> device2;
      device1.io.in = 2;
      device2.io.in = 2;
      ch_vcdtracer tracer(std::cout, device1, device2);
      auto y = device1.io.out ^ 3_h;
      auto z = device2.io.out ^ 3_h;
      tracer.add_trace("y", y);
      tracer.add_trace("y", z); // dup name!
      tracer.run();
      return (1 == device1.io.out && 1 == device2.io.out);
    });
  }

  SECTION("stats", "[stats]") {
    TESTX([]()->bool {
      ch_device<inverter<ch_bit2>> device;
      ch_stats(std::cout, device);
      return true;
    });
  }
}
