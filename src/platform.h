#pragma once

#include "common.h"

namespace ch {
namespace internal {

enum class cflags {
  dump_ast    = (1 << 0),
  dump_cfg    = (1 << 1),
  dump_jit    = (1 << 2),
  dump_asm    = (1 << 3),
  show_sloc   = (1 << 4),
  reg_init    = (1 << 5),
  check_reg   = (1 << 6),
  disable_jit = (1 << 8),
  disable_cfo = (1 << 9),
  disable_cse = (1 << 10),
  disable_pip = (1 << 11),
  disable_pcx = (1 << 12),
  disable_bro = (1 << 13),
};

inline constexpr auto operator|(cflags lsh, cflags rhs) {
  return ((int)lsh | (int)rhs);
}

inline constexpr auto operator|(int lsh, cflags rhs) {
  return (lsh | (int)rhs);
}

inline constexpr auto operator|(cflags lsh, int rhs) {
  return ((int)lsh | rhs);
}

inline constexpr auto operator&(cflags lsh, cflags rhs) {
  return ((int)lsh & (int)rhs);
}

inline constexpr auto operator&(int lsh, cflags rhs) {
  return (lsh & (int)rhs);
}

inline constexpr auto operator&(cflags lsh, int rhs) {
  return ((int)lsh & rhs);
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
