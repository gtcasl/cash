#pragma once

#include "ioimpl.h"

namespace ch {
namespace internal {

class timeimpl : public ioimpl {
public:

  virtual lnodeimpl* clone(context* ctx, const clone_map& cloned_nodes) override;

protected:

  timeimpl(context* ctx, const source_location& sloc);

  friend class context;
};

}
}
