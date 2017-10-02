#pragma once

#include "lnodeimpl.h"

namespace ch {
namespace internal {

class ioimpl : public lnodeimpl {
public:
  ioimpl(ch_operator op, context* ctx, uint32_t size)
    : lnodeimpl(op, ctx, size)
  {}

  ioimpl(ch_operator op, context* ctx, uint32_t size, const std::string& name)
    : lnodeimpl(op, ctx, size)
    , name_(name)
  {}

  void set_name(const std::string& name) {
    name_ = name;
  }

  const std::string& get_name() const {
    return name_;
  }

protected:
  std::string name_;
};

class inputimpl : public ioimpl {
public:
  inputimpl(ch_operator op, context* ctx, uint32_t size, const std::string& name);

  inputimpl(context* ctx, uint32_t size, const std::string& name)
    : inputimpl(op_input, ctx, size, name)
  {}

  void set_input(const lnode& input) {
    assert(ctx_ != srcs_[0].get_ctx());
    srcs_[0] = input;
  }
  
  const lnode& get_input() const {
    return srcs_[0];
  }

  const bitvector& eval(ch_tick t) override;
  
  void print(std::ostream& out, uint32_t level) const override;
  
protected:
  ch_tick tick_;
};

class outputimpl : public ioimpl {
public:
  outputimpl(const lnode& src, const std::string& name);
  
  const bitvector& eval(ch_tick t) override;
  
  void print(std::ostream& out, uint32_t level) const override;
  
protected:
  ch_tick tick_;
};

class tapimpl : public ioimpl {
public:
  tapimpl(const lnode& src, const std::string& name);

  const lnode& get_target() const {
    return srcs_[0];
  }

  const bitvector& eval(ch_tick t) override;
  
  void print(std::ostream& out, uint32_t level) const override;

protected:
  ch_tick tick_;
};

}
}
