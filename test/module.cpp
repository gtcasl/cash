#include "common.h"

static_assert(ch_direction_v<ch_in<ch_bool>> == ch_direction::in, "invalid direction");
static_assert(ch_direction_v<ch_out<ch_bool>> == ch_direction::out, "invalid direction");

__inout(io_bundle2_t, (
  (ch_in<ch_bool>) x,
  (ch_in<ch_bool>) y
));
static_assert(ch_direction_v<io_bundle2_t> == ch_direction::in, "invalid direction");

__inout(io_bundle1_t, (
  (ch_out<ch_bool>) x,
  (ch_out<ch_bool>) y
));
static_assert(ch_direction_v<io_bundle1_t> == ch_direction::out, "invalid direction");

__inout(io_bundle3_t, (
  (ch_in<ch_bool>) x,
  (ch_out<ch_bool>) y
));
static_assert(ch_direction_v<io_bundle3_t> == ch_direction::inout, "invalid direction");

template <typename T>
__inout(SimpleLink, (
  (ch_out<T>) data,
  (ch_out<ch_bit1>) ready
));

template <typename T>
__inout(PLink, SimpleLink<T>, (
  (ch_out<ch_bit1>) parity
));

template <typename T>
__inout(FilterIO, (
  (ch_flip_t<PLink<T>>) x,
  (PLink<T>) y
));

struct Filter {
  FilterIO<ch_bit8> io;
  void describe() {
    io.y.data   = ~io.x.data;
    io.y.ready  =  io.x.ready;
    io.y.parity = ~io.x.parity;
  }
};

struct FilterBlock {
  FilterIO<ch_bit8> io;
  void describe() {
    f1_.io.x(io.x);
    f1_.io.y(f2_.io.x);
    f2_.io.y(io.y);
  }
  ch_module<Filter> f1_, f2_;
};

template <typename T, unsigned N>
struct FifoWrapper {
  __io (
    (ch_deqIO<T>) enq,
    (ch_enqIO<T>) deq
  );
  void describe() {
    f1_.io.enq(io.enq);
    f1_.io.deq(io.deq);
  }
  ch_module<ch_fifo<T, log2ceil(N)>> f1_;
};

struct Adder {
  __io (
    (ch_in<ch_bit2>)  in1,
    (ch_in<ch_bit2>)  in2,
    (ch_out<ch_bit2>) out
  );
  void describe() {
    io.out = io.in1 + io.in2;
  }
};

struct Foo1 {
  __io (
    (ch_in<ch_bit2>)  in1,
    (ch_in<ch_bit2>)  in2,
    (ch_out<ch_bit2>) out
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
    ch_bit2 out;
    ch_module<Adder> adder;
    adder.io.in1(1);
    adder.io.in2(2);
    adder.io.out(out);
    io = (3 == out);
  }
};

struct Foo3 {
  __inout(io_ab_t, (
    (ch_in<ch_bit2>) a,
    (ch_out<ch_bit2>) b
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
      ch_module<Adder> adder;
      ch_poke(adder.io.in1, 1);
      ch_poke(adder.io.in2, 2);
      ch_simulator sim(adder);
      sim.run(1);
      return (3 == ch_peek<int>(adder.io.out));
    });

    TESTX([]()->bool {
      ch_module<Foo3> foo;
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
      ch_module<Foo1> foo;
      ch_poke(foo.io.in1, 1);
      ch_poke(foo.io.in2, 2);
      ch_simulator sim(foo);
      sim.run(1);
      return (3 == ch_peek<int>(foo.io.out));
    });
    TESTX([]()->bool {
      ch_module<Foo2> foo;
      ch_simulator sim(foo);
      sim.run(1);
      return ch_peek<bool>(foo.io);
    });
    TESTX([]()->bool {
      ch_module<FifoWrapper<ch_bit4, 2>> fifo;
      ch_simulator sim(fifo);
      ch_tick t = sim.reset(0);

      int ret = (ch_peek<bool>(fifo.io.enq.ready));  // !full
      ret &= (!ch_peek<bool>(fifo.io.deq.valid)); // empty
      ch_poke(fifo.io.deq.ready, 0);
      ch_poke(fifo.io.enq.data, 0xA);
      ch_poke(fifo.io.enq.valid, 1); // push
      t = sim.step(t);

      ret &= (ch_peek<bool>(fifo.io.deq.valid));  // !empty
      ch_poke(fifo.io.enq.data, 0xB);
      t = sim.step(t);

      ret &= (!ch_peek<bool>(fifo.io.enq.ready)); // full
      ret &= (ch_peek<bool>(fifo.io.deq.valid));
      ret &= (0xA == ch_peek<int>(fifo.io.deq.data));
      ch_poke(fifo.io.enq.valid, 0); // !push
      ch_poke(fifo.io.deq.ready, 1); // pop
      t = sim.step(t);

      ret &= (ch_peek<bool>(fifo.io.enq.ready));  // !full
      ret &= (0xB == ch_peek<int>(fifo.io.deq.data));
      ch_poke(fifo.io.deq.ready, 1); // pop
      t = sim.step(t, 4);

      ret &= (!ch_peek<bool>(fifo.io.deq.valid)); // empty

      ch_toVerilog("fifowrapper.v", fifo);
      ret &= (checkVerilog("fifowrapper_tb.v"));
      return !!ret;
    });
  }
}
