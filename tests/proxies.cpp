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
      //ch_println("a={}", a);
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
      auto c = ch_slice<2>(a, 1) ^ 01_b;
      return (c == 11_b);
    });    
    TEST([]()->ch_bool {
      ch_bit4 a(1100_b);
      auto c = ch_slice<2>(a, 1) ^ 01_b;
      return (c == 11_b);
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
      ch_sliceref<3>(a, 0) = 0;
      a[3] = 1;
      return a == 1000_b;
    });
    TEST([]()->ch_bool {
      ch_bit4 a;
      ch_bit4 b(a);
      ch_asliceref<3>(a, 0) = 0;
      a[3] = 1;
      return a == 1000_b;
    });
    TEST([]()->ch_bool {
      ch_bit4 a;
      ch_bit4 b(a);
      ch_sliceref<3>(a, 0) = 0;
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
      ch_sliceref<2>(a, 0) = x;
      ch_sliceref<2>(a, 2) = y;
      x = 1;
      y = 1;
      return a == 0101_b;
    });
    TEST([]()->ch_bool {
      ch_bit4 a(0);
      ch_bit2 x, y;
      ch_asliceref<2>(a, 0) = x;
      ch_asliceref<2>(a, 1) = y;
      x = 1;
      y = 1;
      return a == 0101_b;
    });
    TEST([]()->ch_bool {
      ch_uint4 a, b(1);
      auto c = a + b;
      ch_sliceref<2>(a, 0) = 1; // a = 0001
      ch_sliceref<2>(a, 1) = 1; // a = 0011
      ch_sliceref<2>(a, 2) = 1; // a = 0111
      //ch_println("c={0}", c);
      return (c == 1000_b);
    });
    TEST([]()->ch_bool {
      ch_bit4 a;
      ch_bit1 x;
      ch_bit2 y;
      ch_bit2 z;

      a[0] = x;
      ch_sliceref<2>(a, 1) = y;
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
     ch_sliceref<3>(a, 0) = z;
     a[3] = w;

     x = 0_b;
     y = 1_b;     
     z = 001_b;
     w = 1_b;
     return (a == 1001_b);
    });
    TEST([]()->ch_bool {
      ch_bit4 x(0x0);
      auto y = ch_sliceref<3>(x, 1);
      ch_sliceref<2>(y) = 11_b;
      return (x == 0110_b);
    });
    TEST([]()->ch_bool {
      ch_bit4 a(1100_b), b(0011_b);
      ch_sliceref<2>(b, 2) = ch_slice<2>(a, 2);
      return (b == 1111_b);
    });
    TEST([]()->ch_bool {
      ch_bit128 a(0xd0000000'c0000000'b0000000'a0000000_h128);
      ch_bit8 b(0x01);
      ch_asliceref<4>(b, 1) = ch_aslice<4>(a, 8*3-1);
      return (b == 0xc1_h);
    });
    TEST([]()->ch_bool {
      ch_bit8 a(0xBA), b(0xDC);
      ch_bit128 c(0x0);
      ch_sliceref<8>(c, 60) = a;
      ch_sliceref<8>(c, 68) = b;
      auto w = c | 0x1;
      auto y = ch_slice<16>(w, 60);
      //ch_println("c={0}, w={1}, y={2}", c, w, y);
      return (y == 0xDCBA);
    });
    TEST([]()->ch_bool {
      ch_bit64 a(0x3333'2222'1111'0000_h64);
      ch_bit<68> c(0x0);
      ch_sliceref<64>(c, 4) = a;
      auto w = c | 0x1;
      auto y = ch_slice<64>(w, 4);
      //ch_println("c={0}, w={1}, y={2}", c, w, y);
      return (y == a);
    });
    TEST([]()->ch_bool {
      ch_bit128 a(0xffff'f333'2222'1111'0000_h128);
      auto b = ch_slice<63>(a, 0) | 0x5555;
      ch_bit<63> e = 0x7333'2222'1111'5555_h63;
      //ch_println("b={0}, e={1}", b, e);
      return (b == e);
    });
    TEST([]()->ch_bool {
      ch_bit128 a(0xffff'f333'2222'1111'0000_h128);
      auto b = ch_slice<66>(a, 0) | 0x5555;
      ch_bit<66> e = 0x3f333'2222'1111'5555_h66;
      //ch_println("b={0}, e={1}", b, e);
      return (b == e);
    });
    TEST([]()->ch_bool {
      ch_bit128 a(0xff00'ffff'0000'ffff'0000_h128);
      auto b = ~ch_slice<66>(a, 0);
      ch_bit<66> e = 0x30000'ffff'0000'ffff_h66;
      //ch_println("b={0}, e={1}", b, e);
      return (b == e);
    });
    TEST([]()->ch_bool {
      ch_bit128 a(0x4440'3333'2222'1111'0000_h128);
      auto b = ch_slice<65>(a, 0) | 0x5555;
      ch_bit<65> e = 0x3333'2222'1111'5555_h65;
      //ch_println("b={0}, e={1}", b, e);
      return (b == e);
    });
    TEST([]()->ch_bool {
      ch_bit128 a(0xffff'3333'2222'1111'0000_h128);
      auto b = ch_slice<65>(a, 0) | 0x5555;
      ch_bit<65> e = 0x1'3333'2222'1111'5555_h65;
      //ch_println("b={0}, e={1}", b, e);
      return (b == e);
    });
    TEST([]()->ch_bool {
      ch_bit128 a(0xffff'3333'2222'1111'0000_h128);
      auto b = ch_slice<65>(a, 4) | 0x555;
      ch_bit<65> e = 0x1f'3333'2222'1111'555_h65;
      //ch_println("b={0}, e={1}", b, e);
      return (b == e);
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
      ch_int<5> e = 11100_b;
      //ch_println("c={0}, e={1}", c, e);
      return (c == e);
    });
    TEST([]()->ch_bool {
      ch_uint16 a(8000_h);
      auto c = ch_pad<52>(a);
      return (c == 0x00000000000008000_h68);
    });
    TEST([]()->ch_bool {
      ch_int16 a(8000_h);
      auto c = ch_pad<52>(a);
      return (c == 0xfffffffffffff8000_h68);
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
      auto c = ch_dup<2>(a);
      return (c == 11001100_b);
    });
    TEST([]()->ch_bool {
      ch_bit4 a(1100_b);
      auto c = ch_dup<1>(a);
      return (c == 1100_b);
    });
    TEST([]()->ch_bool {
      ch_bit4 a(1100_b);
      auto c = ch_dup<3>(a);
      return (c == 110011001100_b);
    });
    TEST([]()->ch_bool {
      ch_bit4 a(1100_b);
      auto c = ch_cat(1_b, a);
      return (c == 11100_b);
    });
    TEST([]()->ch_bool {
      ch_bit<3> a = 011_b;
      auto c = ch_cat(a, 011_b);
      return (c == 011011_b);
    });
    TEST([]()->ch_bool {
      ch_bit2 a = 10_b;
      auto c = ch_cat(a, 1011_b);
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
      ch_tie(y, x) = 0101_b;
      //ch_println("x={0}", x);
      return (x == 01_b && y == 01_b);
    });
    TEST([]()->ch_bool {
      ch_bit2 x(0), y(0), z(0);
      ch_tie(z, y, x) = 010101_b;
      //ch_println("x={0}, y={1}, z={2}", x, y, z);
      return (x == 01_b && y == 01_b && z == 01_b);
    });
    TEST([]()->ch_bool {
      ch_bit2 x, y, a(01_b);
      ch_tie(x, y) = ch_cat(a, 00_b);
      //ch_println("x={0}, y={1}", x, y);
      return (x == 1 && y == 0);
    });
    TEST([]()->ch_bool {
      ch_bit2 x(01_b), y(10_b);
      auto w = ch_slice<2>(ch_cat(y, x), 1);
      return (w == 0);
    });
    TEST([]()->ch_bool {
      ch_bit16 a(0xabcd_h);
      auto b = ch_slice<4>(ch_slice<8>(ch_slice<12>(a)), 4);
      //ch_println("{0}: b={1}", ch_now(), b);
      return b == 0xc_h;
    });
    TEST([]()->ch_bool {
      ch_uint16 x(0xabcd_h);
      auto a = ch_slice<12>(x + 0);
      auto b = ch_slice<4>(ch_slice<8>(a), 4);
      auto c = ch_slice<4>(ch_slice<8>(a, 4), 4);
      return (b == 0xC_h && c == 0xB_h);
    });
    TEST([]()->ch_bool {
      ch_uint4 x, y;
      ch_uint8 z, w;
      ch_tie(w, y, z, x) = 0xfa2eb1_h;
      auto k = ch_cat(y, x).as_uint() + z + w;
      return (0x06 == k);
    });

    TEST([]()->ch_bool {
      ch_bit32 k(0x00fa2eb1_h);
      ch_bit4 x, y;
      ch_bit8 z, w;
      auto a = ch_cat(ch_slice<4>(k, 4), ch_slice<4>(k, 0));
      auto b = ch_cat(ch_slice<8>(k, 16), ch_slice<8>(k, 8));
      ch_tie(y, x) = a;
      ch_tie(w, z) = b;
      return (x == 0x1 && y == 0xb && z == 0x2e && w == 0xfa);
    });
    TEST([]()->ch_bool {
       ch_bit<33> a(0x11112222);
       ch_bit<7> b(0x78);
       auto c = ch_cat(b, a, b, a, b, a);
       ch_bit<120> e = 0xf011112222f011112222f011112222_h120;
       //ch_println("c={0}, e={1}", c, e);
       return (c == e);
    });
    TEST([]()->ch_bool {
       ch_bit<65> a(0x1'55555555'33333333_h65);
       ch_bit<64> b(0x22222222'11111111_h64);
       auto c = ch_cat(b, a);
       ch_bit<129> e = 0x44444444222222235555555533333333_h129;
       //ch_println("c={0}, e={1}", c, e);
       return (c == e);
    });
    TEST([]()->ch_bool {
       ch_bit<65> a(0x1111222255555555);
       ch_bit<3> b(0);
       auto c = ch_cat(b, a, b, a, b, a);
       ch_bit<204> e = 0x011112222555555550111122225555555501111222255555555_h204;
       //ch_println("c={0}, e={1}", c, e);
       return (c == e);
    });
    TEST([]()->ch_bool {
       ch_bit<69> a(0x1111222255555555f_h69);
       ch_bit<5> b(0x1f);
       auto c = ch_cat(ch_slice<65>(a, 4), b);
       ch_bit<70> e = 0x22224444AAAAAAABF_h70;
       //ch_println("c={0}, e={1}", c, e);
       return (c == e);
    });
    TEST([]()->ch_bool {
       ch_bit<69> a(0x1111222255555555f_h69);
       ch_bit<5> b(0x1f);
       auto c = ch_cat(b, ch_slice<65>(a, 4));
       ch_bit<70> e = 0x3E1111222255555555_h70;
       //ch_println("c={0}, e={1}", c, e);
       return (c == e);
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
