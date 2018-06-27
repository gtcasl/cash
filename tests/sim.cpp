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
      auto d = std::move(device);
      d.io.in = 2;
      ch_tracer tracer(std::cout, d);
      auto t = tracer;
      auto y = d.io.out ^ 3_h;
      t.add_trace("y", y);
      t.run();
      return (1 == d.io.out);
    });
  }

  SECTION("vcdtracer", "[vcdtracer]") {
    TESTX([]()->bool {
      ch_device<inverter<ch_bit2>> device1;
      ch_device<inverter<ch_int2>> device2;
      device1.io.in = 2;
      device2.io.in = 2;
      ch_vcdtracer tracer(std::cout, device1, device2);
      auto t = tracer;
      auto y = device1.io.out ^ 3_h;
      auto z = device2.io.out ^ 3_h;
      t.add_trace("y", y);
      t.add_trace("y", z); // dup name!
      t.run();
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
