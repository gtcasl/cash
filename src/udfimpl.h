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

  auto& udf_srcs() const {
    return udf_srcs_;
  }

protected:

  udfimpl(context* ctx,
          lnodetype type,
          udf_iface* udf,
          const std::initializer_list<lnode>& srcs,
          const source_location& sloc);

  ~udfimpl();

  udf_iface* udf_;
  udf_inputs udf_srcs_;

  friend class context;
};

///////////////////////////////////////////////////////////////////////////////

class udfcimpl : public udfimpl {
public:

  void eval() override;

protected:

  udfcimpl(context* ctx,
          udf_iface* udf,
          const std::initializer_list<lnode>& srcs,
          const source_location& sloc);

  ~udfcimpl();

  friend class context;
};

///////////////////////////////////////////////////////////////////////////////

class udfsimpl : public udfimpl {
public:

  const lnode& cd() const {
    return srcs_[cd_idx_];
  }

  void eval() override;

protected:

  udfsimpl(context* ctx,
           udf_iface* udf,
           const std::initializer_list<lnode>& srcs,
           const source_location& sloc);

  ~udfsimpl();

  int cd_idx_;
  std::vector<bitvector> pipe_;

  friend class context;
};

}}
