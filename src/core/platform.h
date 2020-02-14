#pragma once

#include "cflags.h"

namespace ch {
namespace internal {

class platform {
public:

  platform();

  ~platform();

  static platform& self();
  
  int dbg_level() const;

  int dbg_node() const;

  ch::internal::ch_flags cflags() const;

  void set_cflags(ch::internal::ch_flags value);
  
protected:
  class Impl;
  Impl* impl_;
};

}
}
