#pragma once

#include "lnodeimpl.h"

namespace ch {
namespace internal {

class ioimpl : public lnodeimpl {
public:

  void set_name(const std::string& name) {
    name_ = name;
  }

  const std::string& get_name() const {
    return name_;
  }

protected:  

  ioimpl(context* ctx, lnodetype type, uint32_t size)
    : lnodeimpl(ctx, type, size)
  {}

  ioimpl(context* ctx, lnodetype type, uint32_t size, const std::string& name)
    : lnodeimpl(ctx, type, size)
    , name_(name)
  {}

  ~ioimpl() {}

  std::string name_;

  friend class context;
};

class inputimpl : public ioimpl {
public:

  void bind(const lnode& input) {
    input_ = input;
  }

  const lnode& get_input() const {
    return input_;
  }

  const bitvector& eval(ch_tick t) override;
  
  void print(std::ostream& out, uint32_t level) const override;
  
protected:

  inputimpl(context* ctx, uint32_t size, const std::string& name);
  ~inputimpl() {}

  lnode input_;
  ch_tick tick_;

  friend class context;
};

class outputimpl : public ioimpl {
public:

  const bitvector& eval(ch_tick t) override;
  
  void print(std::ostream& out, uint32_t level) const override;
  
protected:

  outputimpl(context* ctx, const lnode& src, const std::string& name);
  ~outputimpl() {}

  ch_tick tick_;

  friend class context;
};

class tapimpl : public ioimpl {
public:

  const lnode& get_target() const {
    return srcs_[0];
  }

  const bitvector& eval(ch_tick t) override;
  
  void print(std::ostream& out, uint32_t level) const override;

protected:

  tapimpl(context* ctx, const lnode& src, const std::string& name);
  ~tapimpl() {}

  ch_tick tick_;

  friend class context;
};

}
}
