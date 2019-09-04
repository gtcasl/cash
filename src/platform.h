#pragma once

#include "common.h"

namespace ch {
namespace internal {

enum class cflags {
  debug_cfg       = (1 << 0),
  dump_cfg        = (1 << 1),
  dump_ast        = (1 << 2),
  dump_asm        = (1 << 3),
  codegen_sloc    = (1 << 4),
  codegen_merged  = (1 << 5),
  check_reg_init  = (1 << 6),
  force_reg_init  = (1 << 7),
  disable_jit     = (1 << 8),
  disable_pip     = (1 << 9),
  disable_cfo     = (1 << 10),
  disable_cse     = (1 << 11),
  disable_bro     = (1 << 12),
  disable_rpo     = (1 << 13),
  disable_pcx     = (1 << 14),
  disable_swo     = (1 << 15),
  disable_sro     = (1 << 16),
  disable_snc     = (1 << 17),
  disable_cpb     = (1 << 18),
  disable_smo     = (1 << 19),
  verbose_tracing = (1 << 20)
};

inline constexpr auto operator|(cflags lsh, cflags rhs) {
  return static_cast<int>(lsh) | static_cast<int>(rhs);
}

inline constexpr auto operator|(int lsh, cflags rhs) {
  return lsh | static_cast<int>(rhs);
}

inline constexpr auto operator|(cflags lsh, int rhs) {
  return static_cast<int>(lsh) | rhs;
}

inline constexpr auto operator&(cflags lsh, cflags rhs) {
  return static_cast<int>(lsh) & static_cast<int>(rhs);
}

inline constexpr auto operator&(int lsh, cflags rhs) {
  return lsh & static_cast<int>(rhs);
}

inline constexpr auto operator&(cflags lsh, int rhs) {
  return static_cast<int>(lsh) & rhs;
}

class platform {
public:

  platform();

  ~platform();

  static platform& self();
  
  int dbg_level() const;

  int dbg_node() const;

  ch::internal::cflags cflags() const;

  void set_cflags(ch::internal::cflags value);
  
protected:
  class Impl;
  Impl* impl_;
};

}
}
