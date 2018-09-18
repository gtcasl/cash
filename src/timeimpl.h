#pragma once

#include "ioimpl.h"

namespace ch {
namespace internal {

class timeimpl : public ioimpl {
protected:

  timeimpl(context* ctx, const source_location& sloc);

  friend class context;
};

}
}
