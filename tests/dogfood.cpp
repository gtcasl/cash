#include <htl/queue.h>
#include <htl/onehot.h>
#include <htl/mux.h>
#include <htl/xbar.h>
#include <htl/arbiter.h>
#include <htl/pipe.h>
#include <htl/fixed.h>
#include <htl/complex.h>
#include "common.h"

using namespace ch::core;
using namespace ch::literals;
using namespace ch::sim;
using namespace ch::htl;

namespace {

__struct (Q_t, (
  (ch_bit2) a,
  (ch_bit2) b
));

__enum (e2_t, 2, (
  a, b, c, d
));

__struct (s4_2_t, (
  (ch_bit4) a,
  (ch_bit2) b
));

__struct (u4_2_t, (
  (ch_bit4) a,
  (ch_bit2) b
));

__inout(bundle4_io, (
  __in(e2_t) x,
  __in(s4_2_t) y,
  __out(u4_2_t) z,
  __out(ch_vec<ch_bool, 2>) w,
  (ch_enq_io<s4_2_t>) eq,
  (ch_deq_io<s4_2_t>) dq
));

__struct (s2_t, (
  (ch_bit4) a,
  (ch_bit4) b
));

__struct (s4_t, (
  (ch_bit4) a
  ));

__struct (sd1_t, s4_t, (
  (ch_bit4) b
));

__struct (sd3_t, (
  (sd1_t)   c,
  (ch_bit4) d
));

__struct (s2_4_t, (
  (ch_bit2) a,
  (ch_bit4) b
));

struct Adder {
  __io (
    __in(ch_uint2)  in1,
    __in(ch_uint2)  in2,
    __out(ch_uint2) out
  );
  void describe() {
    io.out = io.in1 + io.in2;
  }
};

struct Foo1 {
  __io (
    __in(ch_uint2)  in1,
    __in(ch_uint2)  in2,
    __out(ch_uint2) out
  );
  void describe() {
    adder_.io.in1(io.in1);
    adder_.io.in2(io.in2);
    adder_.io.out(io.out);
  }
  ch_module<Adder> adder_;
};

struct Foo2 {
  ch_out<ch_bool> io;
  void describe() {
    ch_module<Adder> adder;
    adder.io.in1 = 1;
    adder.io.in2 = 2;
    io = (3 == adder.io.out);
  }
};

struct Foo3 {
  __inout(io_ab_t, (
    __in(ch_uint2) a,
    __out(ch_uint2) b
  ));

  __io(
    (ch_vec<io_ab_t, 2>) x,
    (ch_vec<ch_in<ch_uint2>, 2>) y,
    (ch_vec<ch_out<ch_uint2>, 2>) z
  );

  void describe() {
    for (int i = 0; i < 2; ++i) {
      auto x = io.y[i] + io.x[i].a;
      io.x[i].b = x;
      io.z[i] = x;
    }
  }
};

template <typename T, unsigned N>
struct QueueWrapper {
  __io (
    (ch_deq_io<T>) enq,
    (ch_enq_io<T>) deq
  );
  void describe() {
    queue_.io.enq(io.enq);
    queue_.io.deq(io.deq);
  }
  ch_module<ch_queue<T, N>> queue_;
};

template <typename T>
__inout(link_io, (
  __out(T) data,
  __out(ch_bool) valid
));

template <typename T>
__inout(plink_io, link_io<T>, (
  __out(ch_bool) parity
));

template <typename T>
__inout(filter_io, (
  (ch_flip_t<plink_io<T>>) x,
  (plink_io<T>) y
));

template <typename T>
struct Filter {
  filter_io<T> io;
  void describe() {
    auto tmp = (ch_pad<ch_width_v<T>+1>(io.x.data) << 1)
              | ch_pad<ch_width_v<T>+1>(io.x.parity);
    io.y.data   = ch_delay(ch_slice<T>(tmp));
    io.y.parity = tmp[ch_width_v<T>];
    auto q = ch_delay(io.x.valid);
    io.y.valid = q;
    //ch_print("{0}: clk={1}, rst={2}, y.val={3}, x.val={4}", ch_time(), ch_clock(), ch_reset(), q, io.x.valid);
  }
};

template <typename T>
struct FilterBlock {
  filter_io<T> io;
  void describe() {
    f1_.io.x(io.x);
    f1_.io.y(f2_.io.x);
    f2_.io.y(io.y);
    //ch_print("{0}: clk={1}, rst={2}, y={3}", ch_time(), ch_clock(), ch_reset(), io.y.valid);
  }
  ch_module<Filter<T>> f1_, f2_;
};

__union(U_t, (
  (ch_bit1) q,
  (ch_bit2) p
));

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

struct TestAssign {
  __io (
    __in(ch_bit4) in,
    __out(ch_bool) out
  );
  void describe() {
    ch_bit4 w(io.in);
    w = 0xB;
    io.out = (io.in == 0xA);
  }
};

struct Dogfood {
  __io (
    __in(ch_uint4) in,
    __out(ch_bool) out
  );
  void describe() {
    ch_bit2 a;
    a = ch_delay(10_b, 4);
    ch_bit2 e = ch_case(ch_time(), 7, 10_b)(a);
    //ch_print("t={0}, a={1}, e={2}", ch_time(), a, e);
    io.out = true; //(a == e);
    //io.out = true;
  }
};

}

int main() {
  ch_device<Dogfood> device;
  //ch_verilog("test.v", device);
  ch_simulator sim(device);
  device.io.in = 0xA;
  sim.run([&](ch_tick t)->bool {
    std::cout << "t" << t << ": out="  << device.io.out << std::endl;
    //assert(!!device.io.out);
    return (t != 8);
  });

  /*{
    ch_device<inverter> device;
    device.io.in = 2;
    //auto s = ch_simulator(device);
    //s.run();
    ch_simulator s1; //, s2;
    s1 = ch_simulator(device);
    //s2 = s1;
    s1.run();
  }
  {
    ch_scbit<4> a(1), b;
    b = std::move(a);
    assert(b == 1);
  }
  {
    ch_scalar_t<s2_t> a{1, 0}, b;
    b = std::move(a);
    assert(b.b == 1);
  }*/

  /*{
    ch_device<inverter> device;
    device.io.in = 2;
    ch_vcdtracer tracer(std::cout, device);
    auto y = device.io.out ^ 3_h;
    tracer.add_trace("y", y);
    tracer.run();
    return (1 == device.io.out);
  }*/

  /*{
    ch_device<FilterBlock<ch_uint16>> filter;
    ch_simulator sim(filter);
    ch_tick t = sim.reset(0);

    filter.io.x.data   = 3;
    filter.io.x.valid  = 1;
    filter.io.x.parity = 0;
    t = sim.step(t, 2);

    int ret(!!filter.io.y.valid);
    ret &= (12 == filter.io.y.data);
    ret &= !filter.io.y.parity;

    assert(!!ret);
  }*/

  /*{
    ch_device<FilterBlock<ch_uint16>> filter;
    ch_simulator sim(filter);
    ch_tick t = sim.reset(0);

    filter.io.x.data   = 3;
    filter.io.x.valid  = 1;
    filter.io.x.parity = 0;
    t = sim.step(t, 3);

    int ret(!!filter.io.y.valid);
    ret &= (12 == filter.io.y.data);
    ret &= !filter.io.y.parity;

    assert(!!ret);
  }*/

  /*{
    ch_device<QueueWrapper<ch_bit4, 2>> queue;
    ch_simulator sim(queue);
    ch_tick t = sim.reset(0);

    int ret(!!queue.io.enq.ready);  // !full
    ret &= !queue.io.deq.valid; // empty
    queue.io.deq.ready = 0;
    queue.io.enq.data = 0xA;
    queue.io.enq.valid = 1; // push
    t = sim.step(t);

    ret &= !!queue.io.deq.valid;  // !empty
    queue.io.enq.data = 0xB;
    t = sim.step(t);

    ret &= !queue.io.enq.ready; // full
    ret &= !!queue.io.deq.valid;
    ret &= (0xA == queue.io.deq.data);
    queue.io.enq.valid = 0; // !push
    queue.io.deq.ready = 1; // pop
    t = sim.step(t);

    ret &= !!queue.io.enq.ready;  // !full
    ret &= (0xB == queue.io.deq.data);
    queue.io.deq.ready = 1; // pop
    t = sim.step(t, 4);

    ret &= !queue.io.deq.valid; // empty
    ch_verilog("queue.v", queue);
    ret &= (checkVerilog("queue_tb.v"));
    ch_firrtl("queue.fir", queue);

    assert(!!ret);
  }

  {
    ch_device<QueueWrapper<ch_bit4, 2>> queue;
    ch_verilog("queue.v", queue);
  }

  {
    ch_device<Foo1> foo;
    foo.io.in1 = 1;
    foo.io.in2 = 2;
    ch_simulator sim(foo);
    sim.run(1);
    ch_verilog("foo.v", foo);
    std::cout << "foo.io.out=" << foo.io.out << std::endl;
    assert(3 == foo.io.out);
  }

  {
    ch_device<Foo2> foo;
    ch_simulator sim(foo);
    sim.run(1);
    assert(foo.io);
  }

  {
    ch_device<Foo3> foo;
    ch_simulator sim(foo);
    for (int i = 0; i < 2; ++i) {
      foo.io.y[i] = i;
      foo.io.x[i].a = 2-i;
    }
    sim.run(1);
    int ret = 1;
    for (int i = 0; i < 2; ++i) {
      ret &= (2 == foo.io.z[i]);
      ret &= (2 == foo.io.x[i].b);
    }
    assert(!!ret);
  }

  {
    ch_scbit<4> a(0101_b);
    assert(a[0]);
    assert(a[2]);
    assert(1 == a.slice<2>());
    assert(1 == a.slice<2>(2));
    assert((a[0] == a[2]) && (a.slice<2>() == a.slice<2>(2)));
  }*/

  return 0;
}
