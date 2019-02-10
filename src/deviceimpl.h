#pragma once

#include "common.h"

namespace ch {
namespace internal {

class context;
class lnodeimpl;

class deviceimpl : public refcounted {
public:

  deviceimpl(const std::type_index& signature, const std::string& name);

  ~deviceimpl();

  void begin_context();

  void end_context();

  void optimize();

  context* ctx() const {
    return ctx_;
  }

protected:

  context* ctx_;
  context* old_ctx_;
};

}
}
