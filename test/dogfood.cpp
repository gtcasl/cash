#include "common.h"

using namespace ch::core;
using namespace ch::literals;
using namespace ch::sim;
using namespace ch::stl;

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

struct Dogfood {
  __io (
    __out(ch_bit1) out
  );
  void describe() {
    io.out = 1_b;
  }
};

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
      io.x[i].b = io.y[i] + io.x[i].a;
      io.z[i] = io.x[i].b;
    }
  }
};

template <typename T, unsigned N>
struct QueueWrapper {
  __io (
    (ch_deqIO<T>) enq,
    (ch_enqIO<T>) deq
  );
  void describe() {
    queue_.io.enq(io.enq);
    queue_.io.deq(io.deq);
  }
  ch_module<ch_queue<T, N>> queue_;
};

int main(int argc, char **argv) {
  /*{
    ch_device<Dogfood> dogfood;
    ch_simulator sim(dogfood);
    sim.run(1);
    assert(dogfood.io.out);
  }*/

  /*{ch_device<Foo1> foo;
  foo.io.in1 = 1;
  foo.io.in2 = 2;
  ch_simulator sim(foo);
  sim.run(1);
  assert(3 == (int)foo.io.out);}*/

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
      ret &= (2 == (int)foo.io.z[i]);
      ret &= (2 == (int)foo.io.x[i].b);
    }
    assert(ret);
  }

  {
    ch_scalar<4> a(0101_b);
    assert(a[0]);
    assert(a[2]);
    assert(1 == a.slice<2>());
    assert(1 == a.slice<2>(2));
    assert( (a[0] == a[2]) && (a.slice<2>() == a.slice<2>(2)) );
  }

  {
    ch_device<QueueWrapper<ch_bit4, 2>> queue;
    ch_simulator sim(queue);
    ch_tick t = sim.reset(0);

    int ret = !!queue.io.enq.ready;  // !full
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

    ch_toVerilog("queue.v", queue);
    ret &= (checkVerilog("queue_tb.v"));
    assert(!!ret);
  }

  return 0;
}
