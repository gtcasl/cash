#include "common.h"

using namespace ch::extension;

namespace {

  struct Add {
    __scio (
      __in (ch_int32)  lhs,
      __in (ch_int32)  rhs,
      __out (ch_int32) dst
    );

    void eval() {
      auto lhs = static_cast<int32_t>(io.lhs);
      auto rhs = static_cast<int32_t>(io.rhs);
      io.dst = lhs + rhs;
    }

    bool to_verilog(udf_vostream& out, udf_verilog mode) {
      if (mode != udf_verilog::body)
        return false;
      out << "assign $io.dst = $signed($io.lhs) + $signed($io.rhs);";
      return true;
    }
  };
}

TEST_CASE("udf", "[udf]") {
  SECTION("udf_comb", "[udf_comb]") {
    TEST([]()->ch_bool {
      ch_udf_comb<Add> udf;
      udf.io.lhs = 1;
      udf.io.rhs = 2;
      return (3 == udf.io.dst);
    });
  }

  SECTION("udf_seq", "[udf_seq]") {
    TEST([]()->ch_bool {
      ch_udf_seq<Add> udf;
      udf.io.lhs = 1;
      udf.io.rhs = 2;
      return (3 == udf.io.dst);
    }, 1);
  }
}
