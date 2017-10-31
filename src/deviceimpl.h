#pragma once

#include "common.h"

namespace ch {
namespace internal {

class context;
class lnodeimpl;

class deviceimpl : public refcounted {
public:
  deviceimpl(size_t signature, const std::string& name);
  ~deviceimpl();

  void begin_context();

  void end_context();

  void compile();

  context* get_ctx() const {
    return ctx_;
  }

protected:
  context* ctx_;
  context* old_ctx_;
};

}
}
