#pragma once

#include "nodeimpl.h"

namespace chdl_internal {

class litimpl : public nodeimpl {
public:
  litimpl(context* ctx, uint32_t size, const std::initializer_list<uint32_t>& value);
  virtual ~litimpl() {}

  const bitvector& eval(ch_cycle t) override;
  void print(std::ostream& out) const override;
  void print_vl(std::ostream& out) const override;
};

}
