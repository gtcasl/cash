#pragma once

#include "lnodeimpl.h"
#include "tickable.h"
#include "udf.h"

namespace ch {
namespace internal {

class udfimpl : public lnodeimpl {
public:

  void initialize() override;

  void reset() override;

  void eval() override;

protected:

  udfimpl(context* ctx,
          udf_iface* udf,
          const std::initializer_list<lnode>& srcs);

  ~udfimpl();

  udf_iface* udf_;
  bool initialized_;

  friend class context;
};

class delayed_udfimpl : public tickable, public udfimpl {
public:

  const lnode& cd() const {
    return srcs_[cd_idx_];
  }

  bool has_wenable() const {
    return (wenable_idx_ != -1);
  }

  const lnode& wenable() const {
    return srcs_[wenable_idx_];
  }

  void tick() override;

  void eval() override;

protected:

  delayed_udfimpl(context* ctx,
                  udf_iface* udf,
                  const std::initializer_list<lnode>& srcs);

  ~delayed_udfimpl();

  std::vector<bitvector> values_;
  bitvector q_next_;
  int cd_idx_;
  int wenable_idx_;

  friend class context;
};

}}
