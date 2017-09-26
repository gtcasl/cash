#pragma once

#include "lnodeimpl.h"
#include "snode.h"

namespace cash {
namespace internal {

class ioimpl : public lnodeimpl {
public:
  ioimpl(ch_operator op, context* ctx, uint32_t size)
    : lnodeimpl(op, ctx, size)
  {}
};

class inputimpl : public ioimpl {
public:
  inputimpl(ch_operator op, context* ctx, uint32_t size);

  inputimpl(context* ctx, const snode& node);
  
  const snode& get_bus() const {
    return bus_;
  }

  void bind(const snode& node);

  void unbind();

  const bitvector& eval(ch_tick t) override;
  
  void print(std::ostream& out, uint32_t level) const override;
  
protected:
  snode bus_;
  ch_tick tick_;
};

class outputimpl : public ioimpl {
public:
  outputimpl(ch_operator op, const lnode& src);

  outputimpl(const lnode& src)
    : outputimpl(op_output, src)
  {}
  
  const snode& get_bus() const {
    return bus_;
  }

  const bitvector& eval(ch_tick t) override;
  
  void print(std::ostream& out, uint32_t level) const override;
  
private:
  snode bus_;
  ch_tick tick_;
};

class tapimpl : public outputimpl {
public:
  tapimpl(const std::string& name, const lnode& src);
  
  const lnode& get_target() const {
    return srcs_[0];
  }
  
  void set_tagName(const std::string& tagName) {
    tapName_ = tagName;
  }
  
  const std::string& get_tapName() const {
    return tapName_;
  }
  
  void print(std::ostream& out, uint32_t level) const override;
  
protected:
  std::string  tapName_;
};

}
}
