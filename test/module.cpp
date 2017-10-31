#include "common.h"

static_assert(ch_direction_v<ch_in<ch_bool>> == ch_direction::in, "invalid direction");
static_assert(ch_direction_v<ch_out<ch_bool>> == ch_direction::out, "invalid direction");

__inout(io_bundle2_t, (
  __in(ch_bool) x,
  __in(ch_bool) y
));
static_assert(ch_direction_v<io_bundle2_t> == ch_direction::in, "invalid direction");

__inout(io_bundle1_t, (
  __out(ch_bool) x,
  __out(ch_bool) y
));
static_assert(ch_direction_v<io_bundle1_t> == ch_direction::out, "invalid direction");

__inout(io_bundle3_t, (
  __in(ch_bool) x,
  __out(ch_bool) y
));
static_assert(ch_direction_v<io_bundle3_t> == ch_direction::inout, "invalid direction");

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

__inout(io_bundle4_t, (
  __in(e2_t) x,
  __in(s4_2_t) y,
  __out(u4_2_t) z,
  __out(ch_vec<ch_bool, 2>) w
));

template <typename T>
__inout(SimpleLink, (
  __out(T) data,
  __out(ch_bool) valid
));

template <typename T>
__inout(PLink, SimpleLink<T>, (
  __out(ch_bool) parity
));

template <typename T>
__inout(FilterIO, (
  (ch_flip_t<PLink<T>>) x,
  (PLink<T>) y
));

template <typename T>
struct Filter {
  FilterIO<T> io;
  void describe() {
    io.y.data   = ch_reg(io.x.data << 1);
    io.y.parity = io.x.data[0];
    io.y.valid  = ch_reg(io.x.valid);
  }
};

template <typename T>
struct FilterBlock {
  FilterIO<T> io;
  void describe() {
    f1_.io.x(io.x);
    f1_.io.y(f2_.io.x);
    f2_.io.y(io.y);
  }
  ch_module<Filter<T>> f1_, f2_;
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
  ch_out<ch_bit1> io;
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

TEST_CASE("module", "[module]") {
  SECTION("sim", "[sim]") {
    TESTX([]()->bool {
      ch_device<Adder> adder;
      ch_poke(adder.io.in1, 1);
      ch_poke(adder.io.in2, 2);
      ch_simulator sim(adder);
      sim.run(1);
      return (3 == ch_peek<int>(adder.io.out));
    });

    TESTX([]()->bool {
      ch_device<Foo3> foo;
      ch_simulator sim(foo);
      for (int i = 0; i < 2; ++i) {
        ch_poke(foo.io.y[i], i);
        ch_poke(foo.io.x[i].a, 2-i);
      }
      sim.run(1);
      int ret = 1;
      for (int i = 0; i < 2; ++i) {
        ret &= (2 == ch_peek<int>(foo.io.z[i]));
        ret &= (2 == ch_peek<int>(foo.io.x[i].b));
      }
      return !!ret;
    });
  }
  SECTION("emplace", "[emplace]") {
    TESTX([]()->bool {
      ch_device<Foo1> foo;
      ch_poke(foo.io.in1, 1);
      ch_poke(foo.io.in2, 2);
      ch_simulator sim(foo);
      sim.run(1);
      return (3 == ch_peek<int>(foo.io.out));
    });
    TESTX([]()->bool {
      ch_device<Foo2> foo;
      ch_simulator sim(foo);
      sim.run(1);
      return ch_peek<bool>(foo.io);
    });
    TESTX([]()->bool {
      ch_device<FilterBlock<ch_bit16>> filter;
      ch_simulator sim(filter);
      ch_tick t = sim.reset(0);

      ch_poke(filter.io.x.data, 3);
      ch_poke(filter.io.x.valid, 1);
      t = sim.step(t, 2);

      int ret = (ch_peek<bool>(filter.io.y.valid));
      ret &= (12 == ch_peek<int>(filter.io.y.data));

      ch_toVerilog("filter.v", filter);

      return !!ret;
    });
    TESTX([]()->bool {
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

      return !!ret;
    });
  }
}
