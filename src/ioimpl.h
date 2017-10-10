#pragma once

#include "lnodeimpl.h"

namespace ch {
namespace internal {

class ioimpl : public lnodeimpl {
public:
  ioimpl(lnodetype type, context* ctx, uint32_t size)
    : lnodeimpl(type, ctx, size)
  {}

  ioimpl(lnodetype type, context* ctx, uint32_t size, const char* name)
    : lnodeimpl(type, ctx, size)
    , name_(name)
  {}

  void set_name(const char* name) {
    name_ = name;
  }

  const char* get_name() const {
    return name_.c_str();
  }

protected:
  std::string name_;
};

class inputimpl : public ioimpl {
public:
  inputimpl(lnodetype type, context* ctx, uint32_t size, const char* name);

  inputimpl(context* ctx, uint32_t size, const char* name)
    : inputimpl(type_input, ctx, size, name)
  {}

  void bind(const lnode& input);

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
  outputimpl(const lnode& src, const char* name);

  void bind(const lnode& output) {
    output_ = output;
  }

  const lnode& get_output() const {
    return output_;
  }
  
  const bitvector& eval(ch_tick t) override;
  
  void print(std::ostream& out, uint32_t level) const override;
  
protected:
  lnode output_;
  ch_tick tick_;
};

class tapimpl : public ioimpl {
public:
  tapimpl(const lnode& src, const char* name);

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
