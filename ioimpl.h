#pragma once

#include "lnodeimpl.h"

namespace chdl_internal {

class snodeimpl;

class ioimpl : public lnodeimpl { // LCOV_EXCL_LINE
public:
  // LCOV_EXCL_START
  ioimpl(ch_operator op, context* ctx, uint32_t size) : lnodeimpl(op, ctx, size)  {}
  // LCOV_EXCL_END
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
  snodeimpl* m_bus;
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
  snodeimpl* m_bus;
};

class tapimpl : public outputimpl { // LCOV_EXCL_LINE
public:
  tapimpl(const std::string& name, lnodeimpl* src);
  
  const lnode& get_target() const {
    return m_srcs[0];
  }
  
  void set_tagName(const std::string& tagName) {
    m_tapName = tagName;
  }
  
  const std::string& get_tapName() const {
    return m_tapName;
  }
  
  void print(std::ostream& out) const override;
  
  void print_vl(std::ostream& out) const override {} // LCOV_EXCL_LINE 
  
protected:
  std::string  m_tapName;
};

}
