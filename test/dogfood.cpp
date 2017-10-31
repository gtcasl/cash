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
    //io.out = 1_b;

    auto force_move_a = []() {
      return ch_bit4{1};
    };
    auto force_move_b = []() {
      return ch_bit4{2};
    };
    s2_t s{0};
    s.a = force_move_a();
    s.b = force_move_b();
    io.out = (s.asBits() == 21_h);
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
    assert(ch_peek<bool>(dogfood.io.out));
  }*/

  /*{ch_device<Foo1> foo;
  ch_poke(foo.io.in1, 1);
  ch_poke(foo.io.in2, 2);
  ch_simulator sim(foo);
  sim.run(1);
  assert(3 == ch_peek<int>(foo.io.out));}*/

  {
    ch_device<QueueWrapper<ch_bit4, 2>> queue;
    ch_simulator sim(queue);
    ch_tick t = sim.reset(0);

    int ret = (ch_peek<bool>(queue.io.enq.ready));  // !full
    ret &= (!ch_peek<bool>(queue.io.deq.valid)); // empty
    ch_poke(queue.io.deq.ready, 0);
    ch_poke(queue.io.enq.data, 0xA);
    ch_poke(queue.io.enq.valid, 1); // push
    t = sim.step(t);

    ret &= (ch_peek<bool>(queue.io.deq.valid));  // !empty
    ch_poke(queue.io.enq.data, 0xB);
    t = sim.step(t);

    ret &= (!ch_peek<bool>(queue.io.enq.ready)); // full
    ret &= (ch_peek<bool>(queue.io.deq.valid));
    ret &= (0xA == ch_peek<int>(queue.io.deq.data));
    ch_poke(queue.io.enq.valid, 0); // !push
    ch_poke(queue.io.deq.ready, 1); // pop
    t = sim.step(t);

    ret &= (ch_peek<bool>(queue.io.enq.ready));  // !full
    ret &= (0xB == ch_peek<int>(queue.io.deq.data));
    ch_poke(queue.io.deq.ready, 1); // pop
    t = sim.step(t, 4);

    ret &= (!ch_peek<bool>(queue.io.deq.valid)); // empty

    ch_toVerilog("queue.v", queue);
    ret &= (checkVerilog("queue_tb.v"));
    assert(!!ret);
  }

  return 0;
}
