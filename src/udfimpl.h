#pragma once

#include "lnodeimpl.h"
#include "udf.h"

namespace ch {
namespace internal {

class udfimpl : public lnodeimpl {
public:

  udf_iface* udf() const {
    return udf_;
  }

protected:

  udfimpl(context* ctx,
          lnodetype type,
          udf_iface* udf,
          const std::initializer_list<lnode>& srcs,
          const source_location& sloc);

  ~udfimpl();

  udf_iface* udf_;

  friend class context;
};

///////////////////////////////////////////////////////////////////////////////

class udfcimpl : public udfimpl {
protected:

  udfcimpl(context* ctx,
          udf_iface* udf,
          const std::initializer_list<lnode>& srcs,
          const source_location& sloc);

  friend class context;
};

///////////////////////////////////////////////////////////////////////////////

class udfsimpl : public udfimpl {
public:

  const lnode& cd() const {
    return srcs_[cd_idx_];
  }

  bool has_initdata() const {
    return (reset_idx_ != -1);
  }

  const lnode& reset() const {
    return srcs_[reset_idx_];
  }

protected:

  udfsimpl(context* ctx,
           udf_iface* udf,
           const std::initializer_list<lnode>& srcs,
           const source_location& sloc);

  int cd_idx_;
  int reset_idx_;

  friend class context;
};

}}
