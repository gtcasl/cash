#include "common.h"
#include <htl/complex.h>
#include <htl/queue.h>
#include <htl/fixed.h>

using namespace ch::htl;
using namespace ch::extension;

namespace {

  __enum (my_enum, 4, (
    (idle, 0),
    execute,
    stats,
    done
  ));

  template <typename T>
  auto sbind(const T& a, const T& b) {
    return std::tuple(a + b, a - b);
  }

  template <typename T>
  struct SubPrint {
    __io (
      __in (T)  in,
      __out (T) out
    );

    void describe() {
      io.out = io.in;
      __if (io.in[0]) {
        ch_println("io.in={0}", io.in);
      };
    }
  };

  template <typename T>
  struct Print {
    __io (
      __in (T)  in,
      __out (T) out
    );

    void describe() {
      ch_module<SubPrint<T>> m;      
      m.io.in = io.in;
      io.out = m.io.out;
      ch_println("io.in={0}", io.in);
    }
  };

  template <typename T>
  struct Bypass2 {
    __io (
      __in (T)  in,
      __out (T) out
    );

    void describe() {
      tap_ = (io.in << 1);
      io.out = (tap_ >> 1);
    }

    T tap_;
  };

  template <typename T>
  struct Bypass {
    __io (
      __in (T)  in,
      __out (T) out
    );

    void describe() {
      bypass_.io.in = io.in;
      io.out = bypass_.io.out;
    }
    ch_module<Bypass2<T>> bypass_;
  };
}

TEST_CASE("misc", "[misc]") {
  SECTION("sbind", "[sbind]") {
    TEST([]()->ch_bool {
      ch_int4 a(0_h), b(1_h);
      auto q = sbind(a, b);
      auto [x, y] = q;
      return (x == 1 && y == -1);
    });
    
    TEST([]()->ch_bool {
      ch_fixed<8, 4> a(00_h), b(10_h);
      auto q = sbind(a, b);
      auto [x, y] = q;
      return (x == 10_h && y == -16);
    });

    TEST([]()->ch_bool {
      ch_complex<ch_int4> a(0, 0), b(1, 1);
      auto q = sbind(a, b);
      auto [x, y] = q;
      return (x == ch_complex<ch_int4>(1, 1)
           && y == ch_complex<ch_int4>(-1, -1));
    });
  }
  SECTION("utils", "[utils]") {
    TESTX([]()->bool {
      char bigs[258];
      memset(bigs, ' ', sizeof(bigs));
      bigs[255] = '%';
      bigs[256] = 'd';
      bigs[257] = '\0';
      std::string s = stringf(bigs, 7);
      std::cout << s << " " << s.size() << std::endl;
      return (s.size() == 256 && s[255] == '7');
    });

    TESTX([]()->bool {
      std::string tmp(1028, 'X');
      std::string s = stringf(tmp.c_str());
      return true;
    });
  }
  
  SECTION("assert", "[assert]") {
    TEST([]()->ch_bool {
      ch_bit4 a(1100_b);
      auto c = ch_slice<2>(a, 1) ^ 01_b;
      ch_assert(c == 11_b, "assertion failed!");
      return (c == 11_b);
    });

    TEST([]()->ch_bool {
      ch_bit4 a(1100_b), b(1);
      auto c = ch_slice<2>(a, 1) ^ 01_b;
      __if (b == 1) {
        ch_assert(c == 11_b, "assertion failed!");
      } __else {
        ch_assert(c != 11_b, "assertion failed!");
      };
      return (c == 11_b);
    });
  }
  
  SECTION("taps", "[tap]") {
    TESTX([]()->bool {
      auto_cflags_enable dump_enable(cflags::dump_ast | cflags::dump_cfg);
      ch_device<GenericModule2<ch_uint4, ch_uint4, ch_uint4>> device("taps",
        [](auto lhs, auto rhs) {
          auto ret = (lhs + rhs) / 2;
          __tap(ret);
          return ret;
        }
      );
      ch_toVerilog("taps.v", device);
      device.io.lhs = 5;
      device.io.rhs = 3;
      ch_tracer trace(device);
      trace.run();
      RetCheck ret;
      ret &= (device.io.out == 4);
      trace.toText("taps.log");
      trace.toVCD("taps.vcd");
      trace.toTestBench("taps_tb.v", "taps.v");
      ret &= (checkVerilog("taps_tb.v"));
      return ret;
    });

    TESTX([]()->bool {
      auto_cflags_enable dump_enable(cflags::dump_ast | cflags::dump_cfg);
      ch_device<GenericModule2<ch_uint4, ch_uint4, ch_uint4>> device("taps2",
        [](auto lhs, auto rhs) {
          auto f = [](auto in) {
                  auto ret = (in << 1) / 2;
                  __tap(ret);
                  return ret;
                };
          std::array<ch_module<GenericModule<ch_uint4, ch_uint4>>, 2> m{f, f};
          m[0].io.in = lhs;
          m[1].io.in = rhs;
          auto ret = (m[0].io.out + m[1].io.out) / 2;
          return ret;
        }
      );
      ch_toVerilog("taps2.v", device);
      device.io.lhs = 5;
      device.io.rhs = 3;
      ch_tracer trace(device);
      trace.run();
      RetCheck ret;
      ret &= (device.io.out == 4);
      trace.toText("taps2.log");
      trace.toVCD("taps2.vcd");
      trace.toTestBench("taps2_tb.v", "taps2.v");
      ret &= (checkVerilog("taps2_tb.v"));
      return ret;
    });
  }
  
  SECTION("tick", "[tick]") {
    TEST([]()->ch_bool {
      return (0 == ch_now());
    });
  }
  
  SECTION("print", "[print]") {
    TEST([]()->ch_bool {
      ch_println("hello world");
      return ch_true;
    });
    
    TEST([]()->ch_bool {
      ch_bit128 a(0x5555);
      ch_println("a={0}", a);
      return ch_true;
    });
    
    TEST([]()->ch_bool {
      ch_bit8 a(255);
      ch_println("a={0}", a);
      return ch_true;
    });

    TESTX([]()->bool {
      ch_device<Print<ch_bit128>> device;
      device.io.in = 0x5555;
      ch_simulator sim(device);
      sim.run();
      return (device.io.out == 0x5555);
    });
    
    TEST([]()->ch_bool {
      ch_bit8 a(255), b(0);
      ch_println("a={0}, b={1}", a, b);
      return ch_true;
    });  
    
    TEST([]()->ch_bool {
      ch_bit8 a(255);
      ch_bool b(1);
      __if (b) {
        ch_println("a={0}", a);
      };
      return ch_true;
    });
    
    TEST([]()->ch_bool {
      ch_int4 a(-1);
      ch_println("a={0:i}", a);
      return ch_true;
    });
    
    TEST([]()->ch_bool {
      ch_int32 a(0x3e800000_h);
      ch_println("a={0:f}", a);
      return ch_true;
    });

    TEST([]()->ch_bool {
      my_enum a(my_enum::done);
      ch_println("a={0:e}", a);
      return ch_true;
    });
  }

  SECTION("bitvector", "[bitvector]") {
    TESTX([]()->bool {
      sdata_type x(12, 0x707);
      auto y = static_cast<int32_t>(x);
      return (0x707 == y);
    });
    
    TESTX([]()->bool {
      sdata_type x(12, "707_h");
      auto y = static_cast<int32_t>(x);
      return (0x707 == y);
    });
    
    TESTX([]()->bool {
      std::vector<uint16_t> tmp({0x707});
      sdata_type x(12, tmp);
      auto y = static_cast<int32_t>(x);
      return (0x707 == y);
    });

    TESTX([]()->bool {
      std::vector<uint8_t> tmp({0x7, 0x7});
      sdata_type x(12, tmp);
      auto y = static_cast<int32_t>(x);
      return (0x707 == y);
    });

    TESTX([]()->bool {
      std::array<uint16_t, 1> tmp{0x707};
      sdata_type x(12, tmp);
      auto q = x;
      auto y = static_cast<int32_t>(q);
      return (0x707 == y);
    });
    
    TESTX([]()->bool {
      std::array<uint8_t, 2> tmp{0x7, 0x7};
      sdata_type x(12, tmp);
      auto q = x;
      auto y = static_cast<int32_t>(q);
      return (0x707 == y);
    });
  }

  SECTION("sign_ext", "[sign_ext]") {
    CHECK(sign_ext<uint32_t>(0x0555, 16) == 0x00000555);
    CHECK(sign_ext<uint32_t>(0xf555, 16) == 0xfffff555);
    CHECK(sign_ext<uint32_t>(0x05555555, 32) == 0x05555555);
    CHECK(sign_ext<uint32_t>(0xf5555555, 32) == 0xf5555555);
  }

  SECTION("log2", "[log2]") {
    CHECK(log2floor(1) == 0);
    CHECK(log2floor(2) == 1);
    CHECK(log2floor(3) == 1);
    CHECK(log2floor(4) == 2);
    CHECK(log2ceil(1) == 0);
    CHECK(log2ceil(2) == 1);
    CHECK(log2ceil(3) == 2);
    CHECK(log2ceil(4) == 2);
    CHECK(log2up(1) == 1);
    CHECK(log2up(2) == 1);
    CHECK(log2up(3) == 2);
    CHECK(log2up(4) == 2);
    CHECK(roundup(7, 3) == 9);
  }

  SECTION("unused", "unused") {
    TESTX([]()->bool {
      ch_device<GenericModule2<ch_int4, ch_int4, ch_int4>> device(
        [](auto lhs, auto rhs) { 
          ch_module<ch_queue<ch_int4, 4>> queue;
          queue.io.enq.data = lhs + rhs;
          queue.io.enq.valid = true;
          queue.io.deq.ready = true;
          return lhs * rhs; 
        }
      );      
      device.io.lhs = 2;
      device.io.rhs = 3;
      ch_simulator sim(device);
      sim.run();
      return (device.io.out == 6);
    });
    
    TESTX([]()->bool {
      ch_device<GenericModule2<ch_int4, ch_int4, ch_int4>> device(
        [](auto lhs, auto rhs) { 
          ch_module<ch_queue<ch_int4, 4>> queue;
          queue.io.enq.data = lhs + rhs;
          return lhs * rhs; 
        }
      );      
      device.io.lhs = 2;
      device.io.rhs = 3;
      ch_simulator sim(device);
      sim.run();
      return (device.io.out == 6);
    });

    TESTX([]()->bool {
      auto_cflags_disable cg_merge(cflags::codegen_merged);
      ch_device<GenericModule2<ch_int4, ch_int4, ch_int4>> device("merged",
        [](auto lhs, auto rhs) {
          std::array<ch_module<Bypass<ch_int4>>, 2> bypass;
          bypass[0].io.in = lhs;
          bypass[1].io.in = rhs;
          return bypass[0].io.out * bypass[1].io.out;
        }
      );
      ch_toVerilog("merged.v", device);
      device.io.lhs = 2;
      device.io.rhs = 3;
      ch_tracer trace(device);
      trace.run();
      RetCheck ret;
      ret &= (device.io.out == 6);
      trace.toText("merged.log");
      trace.toVCD("merged.vcd");
      trace.toTestBench("merged_tb.v", "merged.v");
      ret &= (checkVerilog("merged_tb.v"));
      return ret;
    });

    TESTX([]()->bool {
      auto_cflags_disable cg_merge(cflags::codegen_merged);
      ch_device<GenericModule2<ch_int4, ch_int4, ch_int4>> device("merged2",
        [](auto lhs, auto rhs) {
          std::array<ch_module<Bypass<ch_int4>>, 2> bypass;
          bypass[1].io.in = rhs;
          return lhs * bypass[1].io.out;
        }
      );
      ch_toVerilog("merged2.v", device);
      device.io.lhs = 2;
      device.io.rhs = 3;
      ch_tracer trace(device);
      trace.run();
      RetCheck ret;
      ret &= (device.io.out == 6);
      trace.toText("merged2.log");
      trace.toVCD("merged2.vcd");
      trace.toTestBench("merged2_tb.v", "merged2.v");
      ret &= (checkVerilog("merged2_tb.v"));
      return ret;
    });

    TESTX([]()->bool {
      auto_cflags_disable cfo_off(cflags::disable_cfo);
      ch_device<GenericModule2<ch_int4, ch_int4, ch_int4>> device("bypass",
        [](auto lhs, auto rhs) {
          std::array<ch_module<Bypass<ch_int4>>, 2> bypass;
          bypass[0].io.in = lhs;
          bypass[1].io.in = rhs;
          auto x = bypass[0].io.out + bypass[1].io.out;
          auto y = bypass[1]->bypass_->tap_ - bypass[0]->bypass_->tap_;
          ch_print("y={0}", y);
          return x * y;
        }
      );
      ch_toVerilog("bypass.v", device);
      device.io.lhs = 2;
      device.io.rhs = 3;
      ch_tracer trace(device);
      trace.run();
      RetCheck ret;
      ret &= (device.io.out == 10);
      trace.toText("bypass.log");
      trace.toVCD("bypass.vcd");
      trace.toTestBench("bypass_tb.v", "bypass.v");
      ret &= (checkVerilog("bypass_tb.v"));
      return ret;
    });
  }
}
