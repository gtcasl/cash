#include <cash.h>

using namespace ch::core;
using namespace ch::literals;
using namespace ch::sim;

__enum (e2_t, 2, (
  (idle, 0),
  execute,
  stats,
  done
));

__enum(E, 2, (
  a,
  b,
  c,
  d
));

__union (u4_t, (
  (ch_bit4) a
  ));

__union (u2_4_t, (
  (ch_bit2) a,
  (ch_bit4) b
  ));

__struct (s4_t, (
  (ch_bit4) a
  ));

__struct (s2_4_t, (
  (ch_bit2) a,
  (ch_bit4) b
));

__union (ux_t, (
  (u2_4_t) a,
  (s2_4_t) b
));

__struct (sd1_t, s4_t, (
  (ch_bit4) b
));

__struct (sd2_t, sd1_t, (
  (ch_bit4) c
));

__struct (sd3_t, (
  (sd1_t)   c,
  (ch_bit4) d
));

using v2_1_t = ch_vec<ch_bit2, 1>;
using v2_2_t = ch_vec<ch_bit2, 2>;
using v2_3_t = ch_vec<ch_bit2, 3>;

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

    ch_ram<ch_bitwidth_v<T>, A> mem;
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
  __flip(PLink<T>) x,
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
    adder.io.in2(2);
    adder.io.out(out);
    io = (3 == out);
  }
};

struct Dogfood {
  __io (
    (ch_out<ch_bit1>) out
  );
  void describe() {
    //io.out = 1_b;
    ch_float32 x(0.5f);
    io.out = (x == 0x3f000000_h);
    /*ch_bit4 a(1100_b), b(0011_b);
    b[3] = a[3];
    io.out = (b == 1011_b);*/
    /*v2_2_t a(1, 1), b(0);
    b[0][0] = a[0][0];
    io.out = (b.asBits() == 0001_b);*/
    /*v2_2_t a(0, 0);
    a[0][1] = 1;
    io.out = (a.asBits() == 0010_b);*/
    /*ch_bit4 a;
    a.slice<3>(0) = '0';
    a[3] = '1';
    io.out = (a == 1000_b);*/
    /*ch_bit4 a(1100_b), b(0011_b), c(3);
    auto t = ch_orr(a[0] & b[3]);
    c[0] = t;
    ch_print("t={0}, c={1}", t, c);
    io.out = (c == 2);*/
    /*ch_bit4 a;
    ch_bit1 x, y;
    a[3] = x;
    a[1] = y;
    x = 1_b;
    y = 0_b;
    io.out = (a[3] == 1_b && a[1] == 0_b);*/
    /*auto x = ch_reg(E::c, E::a);
    auto e = ch_case<E>(ch_getTick(), 3, E::c)(x);
    io.out = (x == e);*/
    /*v2_2_t a = ch_reg(v2_2_t{3, 1});
    auto e = ch_case(ch_getTick(), 3, 1101_b)(a);
    ch_print("t={0}, a={1}, e={2}", ch_getTick(), a, e);
    io.out = (a.asBits() == e);*/
  }
};

int main(int argc, char **argv) {

  ch_module<Dogfood> dogfood;
  ch_simulator sim(dogfood);
  sim.run(1);
  assert(ch_peek<bool>(dogfood.io.out));

  {
    ch_scalar<4> a(0), b(1), c(1);
    assert(a != b);
    assert(b == c);
    assert(a == (b - c));
  }

  {
    auto force_move_assignment = []() {
      return 4_h + 3_h;
    };
    ch_scalar<4> x;
    x = force_move_assignment();
    assert(x == 7);
  }

  {
    ch_scalar<4> a(e2_t::done), b(1);

    assert(a == 3);
    assert((a + b) == 4);
    assert((a - 1) == 2);
    assert((a & b) == 1);
    assert((a | 1) == 3);
    assert(~a == 1100_b);
    assert(~b == 1110_b);
    assert((a >> 1) == 1);
    assert((b << 1) == 2);
  }

  {
    ch_scalar_t<u2_4_t> u2(0101_b);
    assert(u2.a == 1);
    assert(u2.b == 5);
    u2.b = 7;
    assert(u2.a == 3);
    u2.a = 0;
    assert(u2.b == 4);
  }

  {
    ch_scalar_t<s2_4_t> s2(0101_b, 01_b);
    assert(s2.a == 1);
    assert(s2.b == 5);
    s2.b = 7;
    assert(s2.a == 1);
    s2.a = 0;
    assert(s2.b == 7);
  }

  {
    auto force_move_assignment = []() {
      return 4_h + 3_h;
    };
    ch_scalar_t<s2_4_t> s2(0101_b, 01_b);
    s2.b = force_move_assignment();
    assert(s2.b == 7);
    assert(s2.asScalar() == 011101_b);
  }

  {
    ch_scalar_t<u2_4_t> a(0101_b), b(a);
    assert((ch_scalar<4>)a == (ch_scalar<4>)b);
  }

  {
    ch_scalar_t<u2_4_t> a(0101_b), b;
    b = a;
    assert((ch_scalar<4>)a == (ch_scalar<4>)b);
  }

  {
    ch_scalar_t<s2_4_t> a(010101_b), b(0101_b, 01_b);
    assert((ch_scalar<6>)a == (ch_scalar<6>)b);
  }

  {
    ch_scalar_t<s2_4_t> a(010101_b), b(a);
    assert((ch_scalar<6>)a == (ch_scalar<6>)b);
  }

  {
    ch_scalar_t<s2_4_t> a(010101_b), b;
    b = a;
    assert((ch_scalar<6>)a == (ch_scalar<6>)b);
  }

  {
    ch_scalar_t<sd3_t> s3(321_h);
    ch_scalar_t<sd1_t> x(54_h);

    assert(s3.c.a == 1);
    assert(s3.c.b == 2);
    assert(s3.d == 3);
    s3.c = x;
    assert(s3.c.a == 4);
    assert(s3.c.b == 5);
    assert(s3.d == 3);
  }

  {
    ch_scalar_t<sd1_t> a(21_h), b(2_h, 1_h);
    assert((ch_scalar<8>)a == (ch_scalar<8>)b);
  }

  {
    ch_scalar_t<sd3_t> a(321_h), b(3_h, 21_h);
    assert((ch_scalar<12>)a == (ch_scalar<12>)b);
  }

  {
    ch_scalar_t<sd3_t> a(321_h), b(a);
    assert(b.d == 3);
  }

  /*ch_module<Dogfood> dogfood;
  ch_simulator sim(dogfood);
  sim.run(1);
  assert(ch_peek<bool>(dogfood.io.out));*/

  /*{
    ch_module<Foo1> foo;
    ch_poke(foo.io.in1, 1);
    ch_poke(foo.io.in2, 2);
    ch_simulator sim(foo);
    sim.run(1);
    assert(3 == ch_peek<int>(foo.io.out));
    ch_toVerilog("foo.v", foo);
  }*/

  /*ch_module<Foo2> foo;
  ch_simulator sim(foo);
  sim.run(1);
  assert(ch_peek<bool>(foo.io));*/

  return 0;
}
