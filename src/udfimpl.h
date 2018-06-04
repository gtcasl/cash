#pragma once

#include "lnodeimpl.h"
#include "udf.h"

namespace ch {
namespace internal {

class udfimpl : public lnodeimpl {
public:

  void initialize() override;

  void eval() override;

protected:

  udfimpl(context* ctx,
          udf_iface* udf,
          const std::initializer_list<lnode>& srcs);

  ~udfimpl();

  udf_iface* udf_;
  std::vector<const bitvector*> udf_srcs_;

  friend class context;
};

class delayed_udfimpl : public lnodeimpl {
public:

  const lnode& cd() const {
    return srcs_[0];
  }

  bool has_wenable() const {
    return (wenable_idx_ != -1);
  }

  const lnode& wenable() const {
    return srcs_[wenable_idx_];
  }

  void initialize() override;

  void eval() override;

protected:

  delayed_udfimpl(context* ctx,
                  udf_iface* udf,
                  const std::initializer_list<lnode>& srcs);

  ~delayed_udfimpl();

  udf_iface* udf_;  
  int wenable_idx_;
  std::vector<const bitvector*> udf_srcs_;
  std::vector<bitvector> values_;
  bitvector qnext_;

  friend class context;
};

}}
