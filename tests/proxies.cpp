#include "common.h"

TEST_CASE("proxies", "[proxies]") {  
  SECTION("subscript", "[subscript]") {
    TEST([]()->ch_bool {
      ch_bit4 a(1010_b);
      return (a[0] == a[2] && a[1] == a[3]);
    });
    TEST([]()->ch_bool {
      ch_bit4 a(1010_b);
      return (a[0] == a[2] && a[1] == a[3]);
    });
    TEST([]()->ch_bool {
       ch_bit4 a(0110_b);
       return (a[0] == a[3] && a[1] == a[2]);
    });
    TEST([]()->ch_bool {
      ch_bit4 a;
      ch_bit1 x, y;
      a[3] = x;
      a[1] = y;
      x = 1_b;
      y = 0_b;
      return (a[3] == 1_b && a[1] == 0_b);
    });    
    TEST([]()->ch_bool {
      ch_bit4 a(1100_b), b(0011_b), c(3);
      c[0] = ch_orr(a[0] & b[3]);
      return (c == 2);
    });
    TEST([]()->ch_bool {
      ch_bit4 a(1100_b), b(0011_b);
      b[3] = a[3];
      return (b == 1011_b);
    });
  }
  
  SECTION("slice", "[slice]") {
    TEST([]()->ch_bool {
      ch_bit4 a(1100_b);
      auto c = a.slice<2>(1) ^ 01_b;
      return (c == 11_b);
    });
    TEST([]()->ch_bool {
      ch_bit4 a(1100_b);
      auto c = ch_slice<2>(a, 1) ^ 01_b;
      return (c == 11_b);
    });
    TEST([]()->ch_bool {
      ch_bit4 a(1100_b);
      auto c = a.slice<2>(2) ^ 01_b;
      return (c == 10_b);
    });
    TEST([]()->ch_bool {
      ch_bit4 a(1100_b);
      auto c = a.aslice<2>(1) ^ 01_b;
      return (c == 10_b);
    });
    TEST([]()->ch_bool {
      ch_bit4 a(1100_b);
      auto c = ch_slice<2>(a, 2) ^ 01_b;
      return (c == 10_b);
    });
    TEST([]()->ch_bool {
      ch_bit4 a(1100_b);
      auto c = ch_aslice<2>(a, 1) ^ 01_b;
      return (c == 10_b);
    });
    TEST([]()->ch_bool {
      ch_bit4 a;
      ch_sliceref<3>(a, 0) = 0;
      a[3] = 1;
      return a == 1000_b;
    });
    TEST([]()->ch_bool {
      ch_bit4 a;
      ch_bit4 b(a);
      a.sliceref<3>(0) = 0;
      a[3] = 1;
      return a == 1000_b;
    });
    TEST([]()->ch_bool {
      ch_bit4 a;
      ch_bit4 b(a);
      a.asliceref<3>(0) = 0;
      a[3] = 1;
      return a == 1000_b;
    });
    TEST([]()->ch_bool {
      ch_bit4 a;
      ch_bit4 b(a);
      a.sliceref<3>(0) = 0;
      ch_bit1 x;
      a[3] = x;
      x = 1;
      return a == 1000_b;
    });
    TEST([]()->ch_bool {
      ch_bit4 a;
      a[0] = 0;
      a[1] = 1;
      a[2] = 1;
      a[3] = 0;
      a[0] = 1;
      a[3] = 1;
      ch_sliceref<2>(a, 1) = 0;
      return a == 1001_b;
    });
    TEST([]()->ch_bool {
      ch_bit4 a(0);
      ch_bit2 x, y;
      a.sliceref<2>(0) = x;
      a.sliceref<2>(2) = y;
      x = 1;
      y = 1;
      return a == 0101_b;
    });
    TEST([]()->ch_bool {
      ch_bit4 a(0);
      ch_bit2 x, y;
      a.asliceref<2>(0) = x;
      a.asliceref<2>(1) = y;
      x = 1;
      y = 1;
      return a == 0101_b;
    });
    TEST([]()->ch_bool {
      ch_uint4 a, b(1);
      auto c = a + b;
      a.sliceref<2>(0) = 1; // a = 0001
      a.sliceref<2>(1) = 1; // a = 0011
      a.sliceref<2>(2) = 1; // a = 0111
      //ch_print("c={0}", c);
      return (c == 1000_b);
    });
    TEST([]()->ch_bool {
      ch_bit4 a;
      ch_bit1 x;
      ch_bit2 y;
      ch_bit2 z;

      a[0] = x;
      a.sliceref<2>(1) = y;
      a[3] = x;
      y = z;

      x = 1_b;
      z = 10_b;
      return (a == 1101_b);
    });
    TEST([]()->ch_bool {
     ch_bit4 a;
     ch_bit1 x, y;
     ch_bit<3> z;
     ch_bit1 w;

     a[0] = x;
     a[1] = y;
     a.sliceref<3>(0) = z;
     a[3] = w;

     x = 0_b;
     y = 1_b;     
     z = 001_b;
     w = 1_b;
     return (a == 1001_b);
    });
    TEST([]()->ch_bool {
      ch_bit4 x(0x0);
      x.sliceref<3>(1).sliceref<2>() = 11_b;
      return (x == 0110_b);
    });
    TEST([]()->ch_bool {
      ch_bit4 a(1100_b), b(0011_b);
      b.sliceref<2>(2) = a.slice<2>(2);
      return (b == 1111_b);
    });
    TEST([]()->ch_bool {
      ch_bit128 a(0xd0000000'c0000000'b0000000'a0000000_h128);
      ch_bit8 b(0x01);
      b.asliceref<4>(1) = a.aslice<4>(8*3-1);
      return (b == 0xc1_h);
    });
    TEST([]()->ch_bool {
      ch_bit8 a(0xBA), b(0xDC);
      ch_bit128 c(0x0);
      c.sliceref<8>(60) = a;
      c.sliceref<8>(68) = b;
      auto w = c | 0x1;
      auto y = w.slice<16>(60);
      //ch_print("c={0}, w={1}, y={2}", c, w, y);
      return (y == 0xDCBA);
    });
    TEST([]()->ch_bool {
      ch_bit64 a(0x3333'2222'1111'0000_h64);
      ch_bit128 c(0x0);
      c.sliceref<64>(4) = a;
      auto w = c | 0x1;
      auto y = w.slice<64>(4);
      //ch_print("c={0}, w={1}, y={2}", c, w, y);
      return (y == a);
    });
  }

  SECTION("pad", "[pad]") {
    TEST([]()->ch_bool {
      ch_bit4 a(1100_b);
      auto c = ch_pad<1>(a) << 1;
      return (c == 11000_b);
    });
    TEST([]()->ch_bool {
      ch_uint4 a(1100_b);
      auto c = ch_pad<1>(a) << 1;
      return (c == 11000_b);
    });
    TEST([]()->ch_bool {
      ch_int4 a(1100_b);
      auto c = ch_pad<1>(a);
      return (c == 11100_b);
    });
  }

  SECTION("resize", "[resize]") {
    TEST([]()->ch_bool {
      ch_bit4 a(1100_b);
      auto c = ch_resize<3>(a);
      return (c == 100_b);
    });
    TEST([]()->ch_bool {
      ch_uint4 a(1100_b);
      auto c = ch_resize<5>(a);
      return (c == 01100_b);
    });
    TEST([]()->ch_bool {
      ch_int4 a(1100_b);
      auto c = ch_resize<5>(a);
      return (c == 11100_b);
    });
  }
  
  SECTION("concat", "[concat]") {
    TEST([]()->ch_bool {
      ch_bit4 a(1100_b);
      auto c = ch_cat(a, 1_b);
      return (c == 11001_b);
    });
    TEST([]()->ch_bool {
      ch_bit4 a(1100_b);
      auto c = ch_cat(1_b, a);
      return (c == 11100_b);
    });
    TEST([]()->ch_bool {
      auto c = ch_cat(011_b, 011_b);
      return (c == 011011_b);
    });
    TEST([]()->ch_bool {
      auto c = ch_cat(10_b, 1011_b);
      return (c == 101011_b);
    });
    TEST([]()->ch_bool {
      ch_bit4 a(1100_b);
      auto c = ch_cat(a[3], a[2], a[1], a[0]);
      return (c == 1100_b && ch_cat(a[3], a[0]) == 10_b);
    });
    TEST([]()->ch_bool {
       ch_bit4 a(1100_b);
       auto c = ch_cat(a[3], a[0], a[0], a[0]);
       return (c == 1000_b);
    });
    TEST([]()->ch_bool {
      ch_bit2 x(0), y(0);
      ch_bind(y, x) = 0101_b;
      //ch_print("x={0}", x);
      return (x == 01_b && y == 01_b);
    });
    TEST([]()->ch_bool {
      ch_bit2 x(0), y(0), z(0);
      ch_bind(z, y, x) = 010101_b;
      //ch_print("x={0}, y={1}, z={2}", x, y, z);
      return (x == 01_b && y == 01_b && z == 01_b);
    });
    TEST([]()->ch_bool {
      ch_bit2 x, y;
      ch_bind(x, y) = ch_cat(01_b, 00_b);
      //ch_print("x={0}, y={1}", x, y);
      return (x == 1 && y == 0);
    });
    TEST([]()->ch_bool {
      ch_bit2 x(01_b), y(10_b);
      auto w = ch_cat(y, x).slice<2>(1);
      return (w == 0);
    });
    TEST([]()->ch_bool {
      ch_bit16 a(0xabcd_h);
      auto b = a.slice<12>().slice<8>().slice<4>(4);
      //ch_print("{0}: b={1}", ch_now(), b);
      return b == 0xc_h;
    });
    TEST([]()->ch_bool {
      ch_uint16 x(0xabcd_h);
      auto a = (x + 0).slice<12>();
      auto b = a.slice<8>().slice<4>(4);
      auto c = a.slice<8>(4).slice<4>(4);
      return (b == 0xC_h && c == 0xB_h);
    });
    TEST([]()->ch_bool {
      ch_uint4 x, y;
      ch_uint8 z, w;
      ch_bind(w, y, z, x) = 0xfa2eb1_h;
      auto k = ch_cat(y, x).as_uint() + z + w;
      return (0x06 == k);
    });

    TEST([]()->ch_bool {
      ch_bit32 k(0x00fa2eb1_h);
      ch_bit4 x, y;
      ch_bit8 z, w;
      auto a = ch_cat(ch_slice<4>(k, 4), ch_slice<4>(k, 0));
      auto b = ch_cat(ch_slice<8>(k, 16), ch_slice<8>(k, 8));
      ch_bind(y, x) = a;
      ch_bind(w, z) = b;
      return (x == 0x1 && y == 0xb && z == 0x2e && w == 0xfa);
    });
  }
  SECTION("shuffle", "[shuffle]") {
    TEST([]()->ch_bool {
      ch_bit8 a(10111001_b);
      auto b = ch_shuffle<4>(a, {0, 1, 2, 3});
      return (b == 01101110_b);
    });

    TEST([]()->ch_bool {
      ch_bit8 a(10111001_b);
      auto b = ch_shuffle<4>(a, {0, 0, 0, 0});
      return (b == 01010101_b);
    });

    TEST([]()->ch_bool {
      ch_bit8 a(10111001_b);
      auto b = ch_shuffle<4>(a, {2, 0, 2, 0});
      return (b == 11011101_b);
    });
  }
}
