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
          const std::initializer_list<lnode>& srcs);

  ~udfimpl();

  udf_iface* udf_;
  std::vector<const bitvector*> udf_srcs_;

  friend class context;
};

///////////////////////////////////////////////////////////////////////////////

class udfcimpl : public udfimpl {
public:

  void initialize() override;

  void eval() override;

protected:

  udfcimpl(context* ctx,
          udf_iface* udf,
          const std::initializer_list<lnode>& srcs);

  ~udfcimpl();

  friend class context;
};

///////////////////////////////////////////////////////////////////////////////

class udfsimpl : public udfimpl {
public:

  const lnode& cd() const {
    return srcs_[cd_idx_];
  }

  bool has_enable() const {
    return (enable_idx_ != -1);
  }

  const lnode& enable() const {
    return srcs_[enable_idx_];
  }

  void initialize() override;

  void eval() override;

protected:

  udfsimpl(context* ctx,
           udf_iface* udf,
           const std::initializer_list<lnode>& srcs);

  ~udfsimpl();

  int cd_idx_;
  int enable_idx_;
  std::vector<bitvector> pipe_;

  friend class context;
};

}}
