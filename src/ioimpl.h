#pragma once

#include "lnodeimpl.h"

namespace ch {
namespace internal {

class ioimpl : public lnodeimpl {
protected:  

  ioimpl(context* ctx, lnodetype type, uint32_t size)
    : lnodeimpl(ctx, type, size)
  {}

  ioimpl(context* ctx, lnodetype type, uint32_t size, const std::string& name)
    : lnodeimpl(ctx, type, size, 0, name)
  {}

  ~ioimpl() {}

  friend class context;
};

class inputimpl : public ioimpl {
public:

  const lnode& input() const {
    return input_;
  }

  void bind(const lnode& input);

  void initialize() override;

  void eval() override;
  
  void print(std::ostream& out, uint32_t level) const override;
  
protected:

  inputimpl(context* ctx, uint32_t size, const std::string& name);

  ~inputimpl();

  lnode input_;

  uint32_t* words_;

  friend class context;
};

class outputimpl : public ioimpl {
public:

  void initialize() override;

  void eval() override;
  
  void print(std::ostream& out, uint32_t level) const override;
  
protected:

  outputimpl(context* ctx, const lnode& src, const std::string& name);

  ~outputimpl();

  uint32_t* words_;

  friend class context;
};

class tapimpl : public ioimpl {
public:

  const lnode& target() const {
    return srcs_[0];
  }

  void initialize() override;

  void eval() override;
  
  void print(std::ostream& out, uint32_t level) const override;

protected:

  tapimpl(context* ctx, const lnode& src, const std::string& name);

  ~tapimpl();

  uint32_t* words_;

  friend class context;
};

}
}
