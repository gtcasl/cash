#include <htl/pipe.h>
#include "common.h"

using namespace ch::htl;
namespace {

template <typename T>
struct inverter {
  __io (
    __in (T)  in,
    __out (T) out
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
      auto device = ch_device<inverter<ch_bit2>>();
      device.io.in = 2;
      ch_device<> d1 = device;
      ch_device<> d2(d1), d3;
      d3 = d2;
      ch_simulator s1, s2;
      s1 = ch_simulator(d3);
      s2 = s1;
      ch_simulator s3(s2);
      ch_simulator s4(std::move(s3));
      s4.eval();
      return (1 == device.io.out);
    });
  }

  SECTION("tracer", "[tracer]") {
    TESTX([]()->bool {
      ch_device<inverter<ch_bit2>> device;
      device.io.in = 2;
      ch_tracer t1, t2;
      t1 = ch_tracer(device);
      t2 = t1;
      ch_tracer t3(t2);
      ch_tracer t4(std::move(t3));
      auto y = device.io.out ^ 3_h;
      t4.run();
      t4.toText("trace.log");
      return (1 == device.io.out);
    });
    TESTX([]()->bool {
      ch_device<inverter<ch_bit2>> device1;
      ch_device<inverter<ch_int2>> device2;
      device1.io.in = 2;
      device2.io.in = 2;
      ch_tracer t1, t2;
      t1 = ch_tracer(device1, device2);
      t2 = t1;
      ch_tracer t3(t2);
      ch_tracer t4(std::move(t3));
      t4.run();
      t4.toVCD("trace.vcd");
      return (1 == device1.io.out && 1 == device2.io.out);
    });
  }

  SECTION("stats", "[stats]") {
    TESTX([]()->bool {
      ch_device<GenericModule<ch_bit2, ch_bit2>> device(
        [](ch_bit2 in)->ch_bit2 { return ~in; }
      );
      ch_stats(std::cout, device);
      return true;
    });

    TESTX([]()->bool {
      ch_device<GenericModule2<ch_int2, ch_int2, ch_int2>> device(
        [](ch_int2 lhs, ch_int2 rhs)->ch_int2 { 
          ch_module<ch_pipe<ch_int2, 4>> pipe;
          pipe.io.enq.data = lhs + rhs;
          pipe.io.enq.valid = true;
          pipe.io.deq.ready = true;
          return pipe.io.deq.data; 
        }
      );
      ch_stats(std::cout, device);
      return true;
    });
  }
}
