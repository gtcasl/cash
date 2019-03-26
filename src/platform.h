#pragma once

#include "common.h"

namespace ch {
namespace internal {

enum class cflags {
  show_sloc   = (1 << 0),
  dump_ast    = (1 << 1),
  dump_cfg    = (1 << 2),
  check_reg   = (1 << 3),
  dump_jit    = (1 << 4),
  dump_asm    = (1 << 5),
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

inline constexpr auto operator&(cflags lsh, cflags rhs) {
  return ((int)lsh & (int)rhs);
}

class platform {
public:

  platform();

  ~platform();

  static const platform& self();
  
  int dbg_level() const;

  int dbg_node() const;

  ch::internal::cflags cflags() const;
  
protected:
  class Impl;
  Impl* impl_;
};

}
}
