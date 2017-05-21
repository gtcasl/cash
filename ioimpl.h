#pragma once

#include "lnodeimpl.h"

namespace cash {
namespace detail {

class snodeimpl;

class ioimpl : public lnodeimpl {
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
  
  void print_vl(std::ostream& out) const override {
    CH_UNREFERENCED_PARAMETER(out);
  }
  
protected:
  snodeimpl* bus_;
};

class outputimpl : public ioimpl {
public:
  outputimpl(ch_operator op, lnodeimpl* src);
  outputimpl(lnodeimpl* src) : outputimpl(op_output, src) {}
  ~outputimpl();
  
  const bitvector& eval(ch_cycle t) override;
  
  snodeimpl* get_bus();
  
  void print(std::ostream& out) const override;
  
  void print_vl(std::ostream& out) const override {
    CH_UNREFERENCED_PARAMETER(out);
  }
  
private:
  snodeimpl* bus_;
};

class tapimpl : public outputimpl {
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
  
  void print_vl(std::ostream& out) const override {
    CH_UNREFERENCED_PARAMETER(out);
  }
  
protected:
  std::string  tapName_;
};

}
}
