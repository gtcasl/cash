#pragma once

#include "common.h"

namespace ch {
namespace internal {

class context;
class lnodeimpl;
struct sloc_ctx_t;

class deviceimpl : public refcounted {
public:

  deviceimpl(const std::type_index& signature,
             bool is_pod,
             const std::string& name);

  ~deviceimpl();

  bool begin();

  void build();

  void end();

  context* ctx() const {
    return ctx_;
  }

protected:

  context* ctx_;
  context* old_ctx_;
  sloc_ctx_t* sloc_ctx_;
  bool is_new_ctx_;
  bool is_opened_;
};

}
}
