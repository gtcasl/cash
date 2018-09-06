#include "common.h"

using namespace ch::extension;

namespace {

  struct CombAdd : public udf_comb<ch_int32, ch_int32, ch_int32> {
    
    void initialize() {
      //--
    }    

    void reset(udf_output&, const udf_inputs&) {
      //--
    }

    void eval(udf_output& dst, const udf_inputs& srcs) override {
      auto lhs = static_cast<int32_t>(srcs[0]);
      auto rhs = static_cast<int32_t>(srcs[1]);
      dst = *(int32_t*)&lhs + *(int32_t*)&rhs;
    }

    void init_verilog(std::ostream& out) override {
      out << "// comment";
    }

    void to_verilog(std::ostream& out) override {
      out << "assign $dst = $signed($src0) + $signed($src1);";
    }
  };

  template <unsigned Delay = 1>
  struct SeqAdd : public udf_seq<Delay, true, ch_int32, ch_int32, ch_int32> {

    void initialize() {
      //--
    }

    void reset(udf_output& dst, const udf_inputs&) {
      dst = 0;
    }

    void eval(udf_output& dst, const udf_inputs& srcs) override {
      auto lhs = static_cast<int32_t>(srcs[0]);
      auto rhs = static_cast<int32_t>(srcs[1]);
      dst = *(int32_t*)&lhs + *(int32_t*)&rhs;
    }

    void init_verilog(std::ostream& out) override {
      out << "// comment";
    }

    void to_verilog(std::ostream& out) override {
      out << "assign $dst = $signed($src0) + $signed($src1);";
    }
  };
}

TEST_CASE("udf", "[udf]") {
  SECTION("udf_comb", "[udf_comb]") {
    TEST([]()->ch_bool {
      ch_int32 a(1), b(2);
      auto c = ch_udf<CombAdd>(a, b);
      return (c == 3);
    });
  }

  SECTION("udf_seq", "[udf_seq]") {
    TEST([]()->ch_bool {
       ch_int32 a(1), b(2);
       auto c = ch_udf<SeqAdd<1>>(a, b);
       return (c == 3);
    }, 1);
  }
}
