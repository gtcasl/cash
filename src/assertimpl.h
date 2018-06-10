#pragma once

#include "ioimpl.h"

namespace ch {
namespace internal {

class assertimpl : public ioimpl {
public:

  void initialize() override;

  void eval() override;

protected:

  assertimpl(context* ctx,
             const lnode& cond,
             const std::string& msg,
             const source_location& sloc);

  ~assertimpl() {}

  std::string msg_;
  bool predicated_;
  ch_tick tick_;

  friend class context;
};

}
}
