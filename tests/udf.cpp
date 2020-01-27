#include "common.h"

using namespace ch::extension;

namespace {

  struct Add {
    __sio (
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

    TEST([]()->ch_bool {
      ch_vec<ch_udf_comb<Add>, 2> udfs;
      for (int i = 0; i < 2; ++i) {
        udfs[i].io.lhs = 1;
        udfs[i].io.rhs = 2;
      }
      return (3 == udfs[0].io.dst && 3 == udfs[1].io.dst);
    });
  }

  SECTION("udf_seq", "[udf_seq]") {
    TEST([]()->ch_bool {
      ch_udf_seq<Add> udf;
      udf.io.lhs = 1;
      udf.io.rhs = 2;
      return (3 == udf.io.dst);
    }, 1);

    TEST([]()->ch_bool {
      ch_vec<ch_udf_seq<Add>, 2> udfs;
      for (int i = 0; i < 2; ++i) {
        udfs[i].io.lhs = 1;
        udfs[i].io.rhs = 2;
      }
      return (3 == udfs[0].io.dst && 3 == udfs[1].io.dst);
    }, 1);
  }
}
