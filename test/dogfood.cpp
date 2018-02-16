#include "common.h"
#include <htl/queue.h>
#include <htl/onehot.h>
#include <htl/mux.h>
#include <htl/xbar.h>
#include <htl/arbiter.h>
#include <htl/pipe.h>

using namespace ch::core;
using namespace ch::literals;
using namespace ch::sim;
using namespace ch::htl;

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

struct Adder {
  __io (
    __in(ch_bit2)  in1,
    __in(ch_bit2)  in2,
    __out(ch_bit2) out
  );
  void describe() {
    io.out = io.in1 + io.in2;
  }
};

struct Foo1 {
  __io (
    __in(ch_bit2)  in1,
    __in(ch_bit2)  in2,
    __out(ch_bit2) out
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
    __in(ch_bit2) a,
    __out(ch_bit2) b
  ));

  __io(
    (ch_vec<io_ab_t, 2>) x,
    (ch_vec<ch_in<ch_bit2>, 2>) y,
    (ch_vec<ch_out<ch_bit2>, 2>) z
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

struct Dogfood {
  __io (
    __in(ch_bit4) in,
    __out(ch_bit1) out
  );
  void describe() {
    /*ch_bit2 a(0);
    auto b = a + 1;
    a = 1;
    io.out = (b == 2);*/
    //io.out = (io.in == 0xA);
    ch_bit4 a(0), b(0);
    __if (a == 1) {
      b = 1;
    } __elif (a == 0) {
      b[1] = 1;
    } __else {
      b = 1000_b;
    };
    //ch_print("b={0}", b);
    io.out = (b == 0010_b);
  }
};

int main() {
  {
    ch_device<Dogfood> device;
    ch_simulator sim(device);
    device.io.in = 0xA;
    sim.run(4);
    assert(device.io.out);
  }

  /*{
    ch_device<Foo1> foo;
    foo.io.in1 = 1;
    foo.io.in2 = 2;
    ch_simulator sim(foo);
    sim.run(1);
    assert(3 == (int)foo.io.out);
  }*/

  /*{
    ch_device<Foo2> foo;
    ch_simulator sim(foo);
    sim.run(1);
    assert(foo.io);
  }*/

  /*{
    ch_device<Foo3> foo;
    ch_simulator sim(foo);
    for (int i = 0; i < 2; ++i) {
      foo.io.y[i] = i;
      foo.io.x[i].a = 2-i;
    }
    sim.run(1);
    int ret = 1;
    for (int i = 0; i < 2; ++i) {
      ret &= (2 == (int)foo.io.z[i]);
      ret &= (2 == (int)foo.io.x[i].b);
    }
    assert(ret);
  }*/

  /*{
    ch_scalar<4> a(0101_b);
    assert(a[0]);
    assert(a[2]);
    assert(1 == a.slice<2>());
    assert(1 == a.slice<2>(2));
    assert( (a[0] == a[2]) && (a.slice<2>() == a.slice<2>(2)) );
  }*/

  return 0;
}
