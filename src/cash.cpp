/*#include "cash.h"
#include <htl/float32.h>

using namespace ch::core;
using namespace ch::sim;
using namespace ch::literals;
using namespace ch::htl;

__enum (e2_t, 2, (
  (idle, 0),
  execute,
  stats,
  done
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
  (ch_bit2) b
));

__struct (sd2_t, sd1_t, (
  (ch_bit4) c
));

__struct (sd3_t, (
  (sd1_t)   c,
  (ch_bit4) d
));


void foo() {
  {
    ch_float32 a, b;
    auto c = ch_fmul<1>(a, b);
    auto d = ch_fmul<1>(0.1f, b);
    auto e = ch_fmul<1>(a, 0.1f);
  }
  {
    ch_scbit<4> a(0);
    ch_scbit<8> b(a);
  }
  {
    ch_scbit<4> a = 3;
    auto b = a & 1;
    auto c = 3 & a;
    c = a;
  }
  {
    ch_scbit<4> a = 1, k;
    ch_scbit<6> b = 2;
    auto c = b & a;
    auto d = a & b;
  }
  {
    ch_scint<4> a = 7;
    ch_scint<4> b = 8;
    auto c = b + a;
    auto d = a + b;
    b = a;
  }

  {
    ch_scint<4> a = 7, k;
    ch_scint<9> b = 8;
    auto c = b + a;
    auto d = a + b;
  }
  {
    ch_scuint<4> a = 7, k;
    ch_scuint<6> b = 8;
    auto c = b + a;
    auto d = a + b;
    d = c;
  }
  {
    ch_scint<2> a(0);
    ch_scint<4> b(1);
    auto c = a + b;
  }
  {
    ch_scint<4> a(0);
    ch_scint<2> b(1);
    auto c = a + b;
  }
  {
    ch_scint<4> a(-1);
    ch_scbit<4> b(a);
    ch_scuint<4> c(a), d(b);
  }
  {
    ch_scbit<4> a(a);
    ch_scint<2> b(-1);
    ch_scuint<2> c(1);
    auto q0 = a << 1;
    auto q1 = b << 1;
    auto q3 = c << 1;
    auto q4 = b << b;
    auto q5 = c << c;
    auto q7 = a << c;
    auto q8 = a << b;
  }  
  {
    ch_bit4 a = 0, b = 0_b4;
    ch_bit8 d(b);
  }
  {
    ch_bit4 a(0);
    ch_bit4 b(1);
    auto c = a & b;
    b = a;
  }
  {
    ch_bit4 a(0);
    ch_bit2 b(1);
    auto c = a & b;
  }
  {
    ch_int4 a(0);
    ch_int4 b(1);
    auto c = a + b;
    b = a;
  }
  {
    ch_int2 a(0);
    ch_int4 b(1);
    auto c = a + b;
  }

  {
    ch_bit<4> a = 3;
    auto b = a & 1;
    auto c = 3 & a;
  }
  {
    ch_bit<4> a = 1;
    ch_bit<6> b = 2;
    auto c = b & a;
    auto d = a & b;
  }
  {
    ch_int<4> a = 7;
    ch_int<6> b = 8;
    auto c = b + a;
    auto d = a + b;
  }
  {
    ch_uint<4> a = 7;
    ch_uint<6> b = 8;
    auto c = b + a;
    auto d = a + b;
  }
  {
    ch_int<2> a(0);
    ch_int<4> b(1);
    auto c = a + b;
  }
  {
    ch_int<4> a(0);
    ch_int<2> b(1);
    auto c = a + b;
  }
  {
    ch_int4 a(0);
    ch_int2 b(1);
    auto c = a + b;
  }
  {
    ch_int2 a(0);
    ch_int4 b(1);
    auto c = a + b;
  }
  {
    ch_int<4> a(-1);
    ch_bit<4> b(a);
    ch_bit<4> c = b;
    ch_int<4> d(c);
  }
  {
    ch_bit<4> a(a);
    ch_int<2> b(-1);
    ch_uint<2> c(1);
    auto q0 = a << 1;
    auto q1 = b << 1;
    auto q3 = c << 1;
    auto q4 = b << b;
    auto q5 = c << c;
    auto q7 = a << c;
    auto q8 = a << b;
  }
}

void bar() {
  ch_scalar_t<s4_t> a(0101_b);
  ch_scalar_t<s2_4_t> b(0101_b, 01_b);
  ch_scalar_t<s2_4_t> c(0101_b, 01_b);
  ch_scalar_t<u2_4_t> d(0101_b);
  ch_scalar_t<sd1_t> e{1_b2, 2_h};
  ch_scalar_t<sd2_t> f{2_h, {1_b2, 2_h}};
  ch_scalar_t<sd3_t> g{1_h, {1_b2, 2_h}};

  ch_reg<s2_4_t> h{0101_b, 01_b};
  ch_reg<u2_4_t> i{0101_b};
}*/
