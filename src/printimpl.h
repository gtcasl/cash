#pragma once

#include "ioimpl.h"

namespace ch {
namespace internal {

class printimpl : public ioimpl {
public:

  void eval() override;

  void print(std::ostream& out, uint32_t level) const override;

protected:

  printimpl(context* ctx,
            const std::string& format,
            const std::initializer_list<lnode>& args);

  ~printimpl();

  std::string format_;  
  std::stringstream strbuf_;  
  bool predicated_;

  friend class context;
};

}
}
