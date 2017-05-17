#pragma once

#include "lnodeimpl.h"

namespace cash_internal {

class snodeimpl;

class ioimpl : public lnodeimpl { // LCOV_EXCL_LINE
public:
  ioimpl(ch_operator op, context* ctx, uint32_t size) : lnodeimpl(op, ctx, size)  {}
};

class inputimpl : public ioimpl {
public:
  inputimpl(ch_operator op, context* ctx, uint32_t size);
  inputimpl(context* ctx, uint32_t size) : inputimpl(op_input, ctx, size) {}
  ~inputimpl();
  
  void bind(snodeimpl* bus);

  const bitvector& eval(ch_cycle t) override;
  
  void print(std::ostream& out) const override;
  
  void print_vl(std::ostream& out) const override {} // LCOV_EXCL_LINE
  
protected:
  snodeimpl* bus_;
};

class outputimpl : public ioimpl {
public:
  outputimpl(ch_operator op, lnodeimpl* src);
  outputimpl(lnodeimpl* src) : outputimpl(op_output, src) {}
  ~outputimpl();
  
  const bitvector& eval(ch_cycle t);
  
  snodeimpl* get_bus();
  
  void print(std::ostream& out) const override;
  
  void print_vl(std::ostream& out) const override {} // LCOV_EXCL_LINE
  
private:
  snodeimpl* bus_;
};

class tapimpl : public outputimpl { // LCOV_EXCL_LINE
public:
  tapimpl(const std::string& name, lnodeimpl* src);
  
  const lnode& get_target() const {
    return srcs_[0];
  }
  
  void set_tagName(const std::string& tagName) {
    tapName_ = tagName;
  }
  
  const std::string& get_tapName() const {
    return tapName_;
  }
  
  void print(std::ostream& out) const override;
  
  void print_vl(std::ostream& out) const override {} // LCOV_EXCL_LINE 
  
protected:
  std::string  tapName_;
};

}
