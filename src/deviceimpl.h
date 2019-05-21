#pragma once

#include "common.h"

namespace ch {
namespace internal {

class context;
class lnodeimpl;

class deviceimpl : public refcounted {
public:

  deviceimpl(const std::type_index& signature,
             bool is_pod,
             const std::string& name);

  ~deviceimpl();

  void begin_context();

  void end_context();

  bool begin_build() const;

  void end_build();

  context* ctx() const {
    return ctx_;
  }

protected:

  context* ctx_;
  context* old_ctx_;
  bool is_new_ctx_;
};

}
}
