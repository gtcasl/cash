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

  bool begin();

  void begin_build();

  void end_build();

  void end(const std::string& name, const source_location& sloc);

  context* ctx() const {
    return ctx_;
  }

  std::string name() const;

protected:

  context* ctx_;
  context* old_ctx_;
  uint32_t instance_;
};

}
}
