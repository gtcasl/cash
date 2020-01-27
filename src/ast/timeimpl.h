#pragma once

#include "ioimpl.h"

namespace ch {
namespace internal {

class timeimpl : public ioimpl {
public:

  lnodeimpl* clone(context* ctx, const clone_map& cloned_nodes) const override;

protected:

  timeimpl(context* ctx, const source_info& srcinfo);

  friend class context;
};

}
}
