#pragma once

#include "common.h"

namespace ch {
namespace internal {

enum class cflags {
  show_src_info  = (1 << 0),
  dump_ast =       (1 << 1),
  dump_cfg =       (1 << 2),
  check_reg_init = (1 << 3),
};

inline constexpr auto operator|(cflags lsh, cflags rhs) {
  return ((int)lsh | (int)rhs);
}

class platform {
public:

  platform();

  ~platform();

  static const platform& self();
  
  int dbg_level() const;

  int dbg_node() const;

  ch::internal::cflags cflags() const;

  const std::string& lib_path() const;
  
protected:
  class Impl;
  Impl* impl_;
};

}
}
