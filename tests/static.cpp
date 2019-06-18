#include "cash.h"
#include <htl/float32.h>

using namespace ch::logic;
using namespace ch::system;
using namespace ch::literals;
using namespace ch::htl;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

struct TestModule {
  __io (
    __in (ch_bit4)  in,
    __in (ch_int4)  lhs,
    __in (ch_int4)  rhs,
    __out (ch_int4) out
  );
  void describe() {
    io.out = io.lhs + io.rhs;
  }
};

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

__struct (qw_t, (
  (ch_bool) a,
  (ch_bool) b,
  (ch_uint8) c
));

__struct (qw2_t, (
  (ch_bool) a,
  (ch_bool) b,
  (e2_t) c
));

void foo() {
  {
    qw_t qw{false, false, 1};
    qw2_t qw2{e2_t::done, false, false};
  }
  {
    auto d1 = ch_device<TestModule>();
    ch_device d2;
    d2 = d1;
  }
  {
    ch_scbit<4> x("5h");
    ch_scint<4> y("5h");
    ch_scuint<4> z("5h");
  }
  {
    auto dev = ch_device<TestModule>();
    auto a = dev.io.lhs ^ 3_h4;
    auto b = dev.io.lhs ^ 3_h8;
    auto c = dev.io.in ^ 3_h4;
    auto d = dev.io.in ^ 3_h8;
  }
  {
    ch_float32 a, b;
    auto c = ch_fmul<1>(a, b);
    auto d = ch_fmul<1>(0.1f, b);
    auto e = ch_fmul<1>(a, 0.1f);
  }
  {
    ch_scbit<4> a = 3;
    auto b = a & 1;
    ch_scbit<4> c = 3 & a;
    c = a;
  }
  {
    ch_scint<4> a = 3;
    auto b = a + 1;
    auto c = 3 + a;
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
    auto q1 = b << 1_b;
    auto q3 = c << 1;
    auto q4 = b << b;
    auto q5 = c << c;
    auto q7 = a << c;
    auto q8 = a << b;
  }
  /////////////////////////////////////////////////////////////////////////////
  {
    ch_bit4 a = 0, b = 0_b4, c = 0_b2;
  }
  {
    ch_bit4 a;
    ch_bit2 b(0);
    a = b;
  }
  {
    ch_bit4 a(1_h);
    a = 2_h;
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
    ch_bit2 a(0);
    ch_bit4 b(1);
    auto c = a & b;
  }
  {
    ch_int4 a(0);
    ch_int4 b(1);
    auto c = a + b + 1_b;
    b = a;
  }
  {
    ch_int2 a(0);
    ch_int4 b(1);
    ch_module<TestModule> m;
    auto c = a + b;
    auto d = m.io.lhs + a;
    auto e = m.io.lhs + m.io.rhs;
    auto f = a + m.io.rhs;
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
    ch_int<2> a = 7;
    ch_int<6> b = 8;
    ch_module<TestModule> m;
    auto c = b + a;
    auto d = a + b;
    auto e = m.io.lhs & a;
    auto f = m.io.lhs & m.io.rhs;
    auto g = a & m.io.rhs;
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
    ch_int2 a(0);
    ch_int4 b(1);
    ch_module<TestModule> m;
    auto c = a * b;
    auto d = m.io.lhs * a;
    auto e = m.io.lhs * m.io.rhs;
    auto f = a * m.io.rhs;
  }
  {
    ch_int2 a(0);
    ch_int4 b(1);
    ch_module<TestModule> m;
    auto c = a << b;
    auto d = m.io.lhs << a;
    auto e = m.io.lhs << m.io.rhs;
    auto f = a << m.io.rhs;
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
    auto q1 = b << 1_b;
    auto q3 = c << 1;
    auto q4 = b << b;
    auto q5 = c << c;
    auto q7 = a << c;
    auto q8 = a << b;
  }

  {
    ch_bit4 a;
    ch_bit8 b;
    auto c1 = ch_eq(a, a);
    auto c2 = ch_ne(a, a);
    auto c3 = ch_eq(a, b);
    auto c4 = ch_ne(b, a);
    auto c5 = ch_eq(a, b);
    auto c6 = ch_ne(a, 1_b);
    auto c7 = ch_eq(1_b, a);
    auto c8 = ch_ne(a, 1);
    auto c9 = ch_eq(1, a);
  }

  {
    ch_int4 a;
    ch_int8 b;
    ch_module<TestModule> m;
    auto c1 = ch_eq(a, a);
    auto c2 = ch_ne(a, a);
    auto c3 = ch_lt(a, b);
    auto c4 = ch_le(b, a);
    auto c5 = ch_gt(a, b);
    auto c6 = ch_ge(a, 1_b);
    auto c7 = ch_eq(1_b, a);
    auto c8 = ch_eq(a, 1);
    auto c9 = ch_eq(1, a);
    auto c10 = ch_eq(m.io.lhs, m.io.rhs);
    auto c11 = ch_eq(a, m.io.rhs);
    auto c12 = ch_eq(m.io.rhs, a);
  }

  {
    ch_int4 a;
    ch_int8 b;
    ch_module<TestModule> m;
    auto c1 = ch_shr(a, a);
    auto c2 = ch_shr<10>(a, a);
    auto c3 = ch_shr(a, b);
    auto c4 = ch_shr<10>(a, b);
    auto c5 = ch_shr<10>(a, 1_b);
    auto c6 = ch_shr<10>(a, 1);
    auto c7 = ch_shr<10>(m.io.lhs, m.io.rhs);
    auto c8 = ch_shr<10>(a, m.io.rhs);
    auto c9 = ch_shr<10>(m.io.rhs, a);
  }

  {
    ch_int4 a;
    ch_int8 b;
    ch_module<TestModule> m;
    auto c1 = ch_add(a, a);
    auto c2 = ch_add<10>(a, a);
    auto c3 = ch_add(a, b);
    auto c4 = ch_add(b, a);
    auto c5 = ch_add<10>(a, b);
    auto c6 = ch_add<10>(a, 1_b);
    auto c7 = ch_add<10>(1_b, a);
    auto c8 = ch_add<10>(a, 1);
    auto c9 = ch_add<10>(1, a);
    auto c10 = ch_add<10>(m.io.lhs, m.io.rhs);
    auto c11 = ch_add<10>(a, m.io.rhs);
    auto c12 = ch_add<10>(m.io.rhs, a);
  }

  {
    ch_int4 a;
    ch_int8 b;
    ch_module<TestModule> m;
    auto c1 = ch_mul(a, a);
    auto c2 = ch_mul<10>(a, a);
    auto c3 = ch_mul(a, b);
    auto c4 = ch_mul(b, a);
    auto c5 = ch_mul<10>(a, b);
    auto c6 = ch_mul<10>(a, 1_b);
    auto c7 = ch_mul<10>(1_b, a);
    auto c8 = ch_mul<10>(a, 1);
    auto c9 = ch_mul<10>(1, a);
    auto c10 = ch_mul<10>(m.io.lhs, m.io.rhs);
    auto c11 = ch_mul<10>(a, m.io.rhs);
    auto c12 = ch_mul<10>(m.io.rhs, a);
  }

  {
    ch_reg<ch_int4> a(0);
    ch_bit<4> lone(1);
    ch_scbit<4> sone(1);
    auto c0 = a->next + lone;
    auto c1 = a->next + sone;
    auto c2 = a->next + 1;
    auto c3 = a->next + 1_b;
    auto d0 = a + lone;
    auto d1 = a + sone;
    auto d2 = a + 1;
    auto d3 = a + 1_b;
  }

  {
    ch_int4 a;
    ch_bit4  b;
    auto c = a + b;
  }

  {
    ch_int4 a;
    ch_uint2  b;
    auto c = a + b;
  }

  {
    ch_int4 a;
    ch_bit2  b;
    auto c = a + b;
  }

  {
    ch_uint4 a;
    ch_int2  b;
    auto c = a + b;
  }

  {
    ch_int4 a;
    ch_uint2  b;
    auto c = a | b;
  }
}

void bar() {
  ch_system_t<s4_t> a(0101_b);
  ch_system_t<s2_4_t> b(0101_b, 01_b);
  ch_system_t<s2_4_t> c(0101_b, 01_b);
  ch_system_t<u2_4_t> d(0101_b);
  ch_system_t<sd1_t> e{1_b2, 2_h};
  ch_system_t<sd2_t> f{2_h, {1_b2, 2_h}};
  ch_system_t<sd3_t> g{1_h, {1_b2, 2_h}};

  ch_reg<s2_4_t> h{0101_b, 01_b};
  ch_reg<u2_4_t> i{0101_b};
}

#pragma GCC diagnostic pop
