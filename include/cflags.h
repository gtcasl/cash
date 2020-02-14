#pragma once

#include "common.h"

namespace ch {
namespace internal {

enum class ch_flags {
  debug_cfg       = (1 << 0),  // 1
  dump_cfg        = (1 << 1),  // 2
  dump_ast        = (1 << 2),  // 4
  dump_asm        = (1 << 3),  // 8
  codegen_sloc    = (1 << 4),  // 16
  codegen_merged  = (1 << 5),  // 32
  check_reg_init  = (1 << 6),  // 64
  force_reg_init  = (1 << 7),  // 128
  disable_jit     = (1 << 8),  // 256
  disable_pip     = (1 << 9),  // 512
  disable_cfo     = (1 << 10), // 1024
  disable_cse     = (1 << 11), // 2048
  disable_bro     = (1 << 12), // 4096
  disable_rpo     = (1 << 13), // 8192
  disable_pcx     = (1 << 14), // 16384
  disable_swo     = (1 << 15), // 32768
  disable_sro     = (1 << 16), // 65536
  disable_snc     = (1 << 17), // 131072
  disable_cpb     = (1 << 18), // 262144
  merged_only_opt = (1 << 19), // 524288
  verbose_tracing = (1 << 20)  // 1048576
};

inline constexpr auto operator|(ch_flags lsh, ch_flags rhs) {
  return static_cast<int>(lsh) | static_cast<int>(rhs);
}

inline constexpr auto operator|(int lsh, ch_flags rhs) {
  return lsh | static_cast<int>(rhs);
}

inline constexpr auto operator|(ch_flags lsh, int rhs) {
  return static_cast<int>(lsh) | rhs;
}

inline constexpr auto operator&(ch_flags lsh, ch_flags rhs) {
  return static_cast<int>(lsh) & static_cast<int>(rhs);
}

inline constexpr auto operator&(int lsh, ch_flags rhs) {
  return lsh & static_cast<int>(rhs);
}

inline constexpr auto operator&(ch_flags lsh, int rhs) {
  return static_cast<int>(lsh) & rhs;
}

void ch_setflags(ch_flags flags);

ch_flags ch_getflags();

}
}