#include "cash.h"

using namespace ch::core;
using namespace ch::sim;
using namespace ch::literals;

void foo() {
  {
    ch_scbit<4> a = 3;
    auto b = a & 1;
    auto c = 3 & a;
  }
  {
    ch_scbit<4> a = 1;
    ch_scbit<6> b = 2;
    auto c = b & a;
    auto d = a & b;
  }
  {
    ch_scint<4> a = 7;
    ch_scint<6> b = 8;
    auto c = b + a;
    auto d = a + b;
  }
  {
    ch_scuint<4> a = 7;
    ch_scuint<6> b = 8;
    auto c = b + a;
    auto d = a + b;
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
    ch_scuint<4> c(a), d = b;
  }
  {
    ch_scbit<4> a(a);
    ch_scint<2> b(-1);
    ch_scuint<2> c(1);
    auto q0 = a << 1;
    auto q1 = b << 1;
    auto q2 = 1 << b;
    auto q3 = c << 1;
    auto q4 = b << b;
    auto q5 = c << c;
    auto q6 = 1 << c;
    auto q7 = a << c;
    auto q8 = a << b;
  }
  {
    ch_bit4 a(0);
    ch_bit4 b(1);
    auto c = a & b;
  }
  {
    ch_bit4 a(0);
    ch_bit2 b(1);
    auto c = a & b;
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
    auto q2 = 1 << b;
    auto q3 = c << 1;
    auto q4 = b << b;
    auto q5 = c << c;
    auto q6 = 1 << c;
    auto q7 = a << c;
    auto q8 = a << b;
  }
}
