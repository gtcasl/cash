#include "common.h"
#include <htl/decoupled.h>

using namespace ch::logic;
using namespace ch::system;
using namespace ch::literals;
using namespace ch::htl;

__union (u4_t, (
  (ch_bit4) a
));

__struct (s4_t, (
  (ch_bit4) a
));

__union (u2_4_t, (
  (ch_bit2) a,
  (ch_bit4) b
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

__enum (e2_t, 2, (
  (idle, 0),
  execute,
  stats,
  done
));

__struct (qw2_t, (
  (ch_bool) a,
  (ch_bool) b,
  (e2_t) c
));

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

struct TestModule2 {
  __io (
    __in (ch_bit4)  in,
    __out (ch_bit4) out
  );

  TestModule2(float v) : v_(v) {}
  
  void describe() {
    io.out = io.in;
  }

  float v_;
};

struct QQ {
  __io (
    __in (ch_bool) w,
    (ch_enq_io<>) x,
    (ch_deq_io<>) y,
    __out (ch_bool) r
  );

  void describe() {
    io.y(io.x);
  }
};

struct PP {
  __interface (io_ab_t, (
    __in (ch_uint2) a,
    __out (ch_uint2) b
  ));

  __io (
    (ch_vec<io_ab_t, 2>) x,
    (ch_vec<ch_in<ch_uint2>, 2>) y,
    (ch_vec<ch_out<ch_uint2>, 2>) z
  );

  void describe() {
    for (int i = 0; i < 2; ++i) {
      io.x[i].b = io.y[i] + io.x[i].a;
      io.z[i] = io.x[i].b;
    }
  }
};

void foo() {
  {
    ch_module<QQ> q;
    auto q2(q);
    auto a = q2.io.y.ready;
    auto b = q2.io.x.valid;        
    q2.io.x.valid = true;
    q2.io.y.ready = true;
  }
  {
    ch_module<PP> p;
  }
  {
    ch_device<QQ> q;
    auto q2(q);
    auto a = q2.io.x.ready;
    auto b = q2.io.y.valid;        
    q2.io.x.valid = true;
    q2.io.y.ready = true;
  }

  {
    qw_t qw{false, false, 1};
    qw2_t qw2{e2_t::done, false, false};
  }
  {
    auto d1 = ch_device<TestModule>();
    auto d2(d1);
  }
  {
    ch_sbit<4> x("5h");
    ch_sint<4> y("5h");
    ch_suint<4> z("5h");
  }
  {
    ch_sbit<4> a = 3;
    auto b = a & 1;
    auto c = 3 & a;
    c = a;
  }
  {
    ch_sint<4> a = 3;
    auto b = a + 1;
    auto c = 3 + a;
  }
  {
    ch_sbit<4> a = 1;
    ch_sbit<6> b = 2;
    auto c = b & a;
    auto d = a & b;
  }
  {
    ch_sint<4> a = 7;
    ch_sint<4> b = 8;
    auto c = b + a;
    auto d = a + b;
    b = a;
  }
  {
    ch_sint<4> a = 7;
    ch_sint<9> b = 8;
    auto c = b + a;
    auto d = a + b;
  }
  {
    ch_suint<4> a = 7;
    ch_suint<6> b = 8;
    auto c = b + a;
    auto d = a + b;
    d = c;
  }
  {
    ch_sint<2> a(0);
    ch_sint<4> b(1);
    auto c = a + b;
  }
  {
    ch_sint<4> a(0);
    ch_sint<2> b(1);
    auto c = a + b;
  }
  {
    ch_sint<4> a(-1);
    ch_sbit<4> b(a);
    ch_suint<4> c(a), d(b);
  }
  {
    ch_sbit<4> a(0);
    ch_sint<2> b(-1);
    ch_suint<2> c(1);
    auto q0 = a << 1;
    auto q1 = b << 1_b;
    auto q3 = c << 1;
    auto q4 = b << b;
    auto q5 = c << c;
    auto q7 = a << c;
    auto q8 = a << b;
  }
  {
    ch_sbit4 a(0);
    ch_sbit8 b(0);
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
    ch_sint4 a(0);
    ch_sint8 b(0);
    auto c1 = ch_eq(a, a);
    auto c2 = ch_ne(a, a);
    auto c3 = ch_lt(a, b);
    auto c4 = ch_le(b, a);
    auto c5 = ch_gt(a, b);
    auto c6 = ch_ge(a, 1_b);
    auto c7 = ch_eq(1_b, a);
    auto c8 = ch_eq(a, 1);
    auto c9 = ch_eq(1, a);
  }
  {
    ch_sint4 a(0);
    ch_sint8 b(0);
    auto c1 = ch_shr(a, a);
    auto c2 = ch_shr<10>(a, a);
    auto c3 = ch_shr(a, b);
    auto c4 = ch_shr<10>(a, b);
    auto c5 = ch_shr<10>(a, 1_b);
    auto c6 = ch_shr<10>(a, 1);
  }
  {
    ch_sint4 a(0);
    ch_sint8 b(0);
    auto c1 = ch_add(a, a);
    auto c2 = ch_add<10>(a, a);
    auto c3 = ch_add(a, b);
    auto c4 = ch_add(b, a);
    auto c5 = ch_add<10>(a, b);
    auto c6 = ch_add<10>(a, 1_b);
    auto c7 = ch_add<10>(1_b, a);
    auto c8 = ch_add<10>(a, 1);
    auto c9 = ch_add<10>(1, a);
  }
  {
    ch_sint4 a(0);
    ch_sint8 b(0);
    auto c1 = ch_mul(a, a);
    auto c2 = ch_mul<10>(a, a);
    auto c3 = ch_mul(a, b);
    auto c4 = ch_mul(b, a);
    auto c5 = ch_mul<10>(a, b);
    auto c6 = ch_mul<10>(a, 1_b);
    auto c7 = ch_mul<10>(1_b, a);
    auto c8 = ch_mul<10>(a, 1);
    auto c9 = ch_mul<10>(1, a);
  }
  {
    auto dev = ch_device<TestModule>();
    auto a = dev.io.lhs ^ 3_h4;
    auto b = dev.io.lhs ^ 3_h8;
    auto c = dev.io.in ^ 3_h4;
    auto d = dev.io.in ^ 3_h8;
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
    ch_bit<4> a(0);
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
    ch_bit4 a(0);
    ch_bit8 b(0);
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
    ch_int4 a(0);
    ch_int8 b(0);
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
    ch_int4 a(0);
    ch_int8 b(0);
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
    ch_int4 a(0);
    ch_int8 b(0);
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
    ch_int4 a(0);
    ch_int8 b(0);
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
    ch_sbit<4> sone(1);
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
    ch_int4 a(0);
    ch_bit4 b(0);
    auto c = a + b;
  }
  {
    ch_int4 a(0);
    ch_uint2 b(0);
    auto c = a + b;
  }
  {
    ch_int4 a(0);
    ch_bit2 b(0);
    auto c = a + b;
  }

  {
    ch_uint4 a(0x1);
    ch_bit4 b(0x2);
    auto c = a + b;
    auto d = a | b;
  }

  {
    ch_uint4 a(0);
    ch_int2 b(0);
    auto c = a + b;
  }
  {
    ch_int4 a(0);
    ch_uint2 b(0);
    auto c = a | b;
  }
  {
    ch_int2 a(1);
    auto c = a & 1010_b;
    auto d = 1010_b | a;
    auto e = ch_and(a, 1010_b);
    auto f = ch_add<3>(1010_b, a);
  }
  {
    ch_int2 a(1);
    auto c = (a != 1010_b);
    auto d = (1010_b > a);
    auto e = ch_shr<3>(a, 1010_b);
    auto f = ch_eq(1010_b, a);
  }

  {
    ch_reg<ch_uint2> a(0);
    ch_uint2 b(1);
    auto c = a & b;
  }

  {
    ch_reg<ch_uint2> a(0);
    ch_reg<ch_uint2> b(1);
    auto c = a & b;
  }

  {
    ch_reg<ch_uint4> a(0);
    ch_uint2 b(1);
    auto c = a & b;
  }

  {
    ch_reg<ch_uint2> a(0);
    ch_uint4 b(1);
    auto c = a & b;
  }

  {
    ch_reg<ch_uint4> a(0);
    ch_reg<ch_uint2> b(1);
    auto c = a & b;
  }

  {
    ch_reg<ch_int2> a(0);
    ch_uint2 b(1);
    auto c = a & b;
  }

  {
    ch_reg<ch_int2> a(0);
    ch_reg<ch_uint2> b(1);
    auto c = a & b;
  }

  {
    ch_reg<ch_int2> a(0);
    ch_uint4 b(1);
    auto c = a & b;
  }

  {
    ch_in<ch_suint4> a;
    ch_sint2 b(1);
    auto c = a & b;
  }

  {
    ch_in<ch_sint2> a;
    ch_in<ch_suint4> b;
    auto c = a & b;
  }

  {
    ch_uint4 a(0);
    ch_int2 b(1);
    auto c = a & b;
  }

  {
    ch_in<ch_uint4> a;
    ch_int2 b(1);
    auto c = a & b;
  }

  {
    ch_in<ch_int2> a;
    ch_in<ch_uint4> b;
    auto c = a & b;
  }

  {
    s2_4_t a{0101_b, 01_b};
    ch_reg<s2_4_t> b{0101_b, 01_b};
  }

  {
    std::array<ch_sbit2, 2> a{11_b, 00_b};
    std::array<std::array<ch_sbit2, 2>, 2> b{{ {0, 1}, {1, 0} }};
    std::array<std::array<std::array<ch_sbit2, 3>, 2>, 2> c{{ {{ {11_b, 00_b, 0}, {10_b, 00_b, 0} }}, {{ {11_b, 0, 00_b}, {0, 10_b, 00_b} }} }};
  }

  {
    ch_vec<ch_sbit2, 2> a{11_b, 00_b};
    ch_vec<ch_vec<ch_sbit2, 2>, 2> b{{ {0, 1}, {1, 0} }};
    ch_vec<ch_vec<ch_vec<ch_sbit2, 3>, 2>, 2> c{{ {{ {11_b, 00_b, 0}, {10_b, 00_b, 0} }}, {{ {11_b, 0, 00_b}, {0, 10_b, 00_b} }} }};
  }

  {
    ch_vec<ch_int2, 2> a{11_b, 00_b};
    ch_vec<ch_vec<ch_int2, 2>, 2> b{{ {0, 1}, {1, 0} }};
    ch_vec<ch_vec<ch_vec<ch_int2, 3>, 2>, 2> c{{ {{ {11_b, 00_b, 0}, {10_b, 00_b, 0} }}, {{ {11_b, 0, 00_b}, {0, 10_b, 00_b} }} }};
  }

  {
    ch_vec<ch_bit2, 2> a{11_b, 00_b};
    ch_reg<ch_vec<ch_bit2, 2>> b{11_b, 00_b};
    ch_vec<ch_vec<ch_bit2, 2>, 2> c{{11_b, 00_b}, {11_b, 00_b}};
    auto x = c[0][1];
    auto y = (x == 11_b);
  }

  {
    std::array<ch_reg<ch_bit2>, 2> a{11_b, 00_b};
  }

  {
    ch_reg<ch_bit2> a(0), b(0);
    auto test = (a == b);
  }

  {
    auto dev = ch_device<TestModule>();
    auto test = (dev.io.lhs == dev.io.rhs);
  }

  {
    ch_system_t<ch_vec<ch_bit2, 2>> a{11_b, 00_b};
    ch_system_t<ch_vec<ch_vec<ch_bit2, 2>, 2>> b{{11_b, 00_b}, {11_b, 00_b}};
    auto x = b[0][1];
    auto y = (x == 11_b);
  }
}

void bar() {
  {
    ch_system_t<s4_t> a{0101_b};
    ch_system_t<s2_4_t> b{0101_b, 01_b};
    ch_system_t<s2_4_t> c{010_b, 01_b};
    ch_system_t<u2_4_t> d{0101_b};
    ch_system_t<u2_4_t> e{010_b};
    ch_system_t<sd1_t> f{1_b2, {2_h}};
    ch_system_t<sd1_t> g{1_b2, {2_h4}};
    ch_system_t<sd2_t> h{2_h, {1_b2, {2_h}}};
    ch_system_t<sd3_t> i{1_h, {1_b2, {2_h4}}};
  }
  {
    s4_t a{0101_b};
    s2_4_t b{0101_b, 01_b};
    s2_4_t c{010_b, 01_b};
    u2_4_t d{0101_b};
    u2_4_t e{010_b};
    sd1_t f{1_b2, {2_h}};
    sd1_t g{1_b2, {2_h4}};
    sd2_t h{2_h, {1_b2, {2_h}}};
    sd3_t i{1_h, {1_b2, {2_h4}}};
  }
  
  {
    ch_reg<s2_4_t> h{0101_b, 01_b};
    ch_reg<u2_4_t> i{0101_b};
  }

  {
    std::array<ch_reg<ch_bit4>, 2> a;
    std::array<ch_reg<ch_bit4>, 2> b{0, 0};
  }

  {
    std::array<ch_mem<ch_bit4, 4>, 2> a;
    std::array<ch_mem<ch_bit4, 4>, 2> b{0, 0};
  }

  {
    ch_vec<ch_reg<ch_bit4>, 2> a;
    ch_vec<ch_reg<ch_bit4>, 2> b{0, 0};
  }

  {
    ch_vec<ch_mem<ch_bit4, 4>, 2> a;
    ch_vec<ch_mem<ch_bit4, 4>, 2> b{0, 0};
  }

  {
    std::array<ch_module<TestModule>, 2> a;
    std::array<ch_module<TestModule2>, 2> b{0.1f, 0.8f};
  }

  {
    ch_vec<ch_module<TestModule>, 2> a;
    ch_vec<ch_module<TestModule2>, 2> b{0.1f, 0.8f};
  }
}