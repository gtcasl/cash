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
  SECTION("simulator", "[simulator]") {
    TESTX([]()->bool {
      ch_device<inverter<ch_bit2>> device;
      device.io.in = 2;
      ch_simulator s1, s2;
      s1 = ch_simulator(device);
      s2 = s1;
      ch_simulator s3(s2);
      ch_simulator s4(std::move(s3));
      s4.run();
      return (1 == device.io.out);
    });
  }

  SECTION("tracer", "[tracer]") {
    TESTX([]()->bool {
      ch_device<inverter<ch_bit2>> device;
      device.io.in = 2;
      ch_tracer t1, t2;
      t1 = ch_tracer(std::cout, device);
      t2 = t1;
      ch_tracer t3(t2);
      ch_tracer t4(std::move(t3));
      auto y = device.io.out ^ 3_h;
      t4.add_trace("y", y);
      t4.run();
      return (1 == device.io.out);
    });
  }

  SECTION("vcdtracer", "[vcdtracer]") {
    TESTX([]()->bool {
      ch_device<inverter<ch_bit2>> device1;
      ch_device<inverter<ch_int2>> device2;
      device1.io.in = 2;
      device2.io.in = 2;
      ch_vcdtracer t1, t2;
      t1 = ch_vcdtracer(std::cout, device1, device2);
      t2 = t1;
      ch_vcdtracer t3(t2);
      ch_vcdtracer t4(std::move(t3));
      auto y = device1.io.out ^ 3_h;
      auto z = device2.io.out ^ 3_h;
      t4.add_trace("y_0", y);
      t4.add_trace("y", y);
      t4.add_trace("y", z); // dup name!
      t4.run();
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
