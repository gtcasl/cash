#include "common.h"

template <typename T>
__inout(FiFoIO, (
  (ch_in<ch_bit1>)  ready,
  (ch_out<ch_bit1>) valid,
  (ch_out<T>)       data
));

template <typename T, unsigned A>
struct Fifo {
  __io (
    (ch_flip_t<FiFoIO<T>>) enq,
    (FiFoIO<T>) deq
  );
  void describe() {
    ch_seq<ch_bit<A+1>> rd_ptr, wr_ptr;

    auto rd_A = ch_slice<A>(rd_ptr);
    auto wr_A = ch_slice<A>(wr_ptr);

    auto reading = io.deq.ready && io.deq.valid;
    auto writing = io.enq.ready && io.enq.valid;

    rd_ptr.next = ch_select(reading, rd_ptr + 1, rd_ptr);
    wr_ptr.next = ch_select(writing, wr_ptr + 1, wr_ptr);

    ch_ram<T::bitcount, A> mem;
    __if (writing) (
      mem[wr_A] = io.end.data;
    );

    io.deq.data  = mem[rd_A];
    io.deq.valid = (wr_ptr != rd_ptr);
    io.enq.ready = (wr_A != rd_A) || (wr_ptr[A] == rd_ptr[A]);
  }
};

struct FifoWrapper {
  __io (
    (ch_flip_t<FiFoIO<ch_bit4>>) enq,
    (FiFoIO<ch_bit4>) deq
  );
  void describe() {
    f1_.io.enq() % io.enq();
    f1_.io.deq() % io.deq();
  }
  ch_module<Fifo<ch_bit4, 2>> f1_;
};

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
    io.y.ready  = io.x.ready;
    io.y.parity = ~io.x.parity;
  }
};

struct FilterBlock {
  FilterIO<ch_bit8> io;
  void describe() {
    f1_.io.x() % io.x();
    f1_.io.y() % f2_.io.x();
    f2_.io.y() % io.y();
  }
  ch_module<Filter> f1_, f2_;
};

struct FilterBlock2 {
  FilterIO<ch_bit8> io;
  void describe() {
    f1_.io.x(io.x);
    f1_.io.y(f2_.io.x);
    f2_.io.y(io.y);
  }
  ch_module<Filter> f1_, f2_;
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
    adder.io.in1(2);
    adder.io.out(out);
    io = (3 == out);
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
  }
}
