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
          const std::vector<lnode>& srcs,
          const source_location& sloc);

  ~udfimpl();

  udf_iface* udf_;

  friend class context;
};

///////////////////////////////////////////////////////////////////////////////

class udfcimpl : public udfimpl {
public:

  virtual lnodeimpl* clone(context* ctx, const clone_map& cloned_nodes) override;

protected:

  udfcimpl(context* ctx,
          udf_iface* udf,
          const std::vector<lnode>& srcs,
          const source_location& sloc);

  friend class context;
};

///////////////////////////////////////////////////////////////////////////////

class udfsimpl : public udfimpl {
public:

  const lnode& cd() const {
    return srcs_[cd_idx_];
  }

  virtual lnodeimpl* clone(context* ctx, const clone_map& cloned_nodes) override;

protected:

  udfsimpl(context* ctx,
           udf_iface* udf,
           lnodeimpl* cd,
           const std::vector<lnode>& srcs,
           const source_location& sloc);

  int cd_idx_;

  friend class context;
};

}}
