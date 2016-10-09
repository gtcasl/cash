#pragma once

#include "lnodeimpl.h"

namespace chdl_internal {

class snodeimpl;

class ioimpl : public lnodeimpl {
public:
  ioimpl(const std::string& name, context* ctx, uint32_t size)
    : lnodeimpl(name, ctx, size)  {}
  
  virtual ~ioimpl() {}
};

class inputimpl : public ioimpl {
public:
  inputimpl(const std::string& name, uint32_t index, context* ctx, uint32_t size);
  ~inputimpl();
  
  void bind(snodeimpl* bus);

  const bitvector& eval(ch_cycle t) override;
  
  void print(std::ostream& out) const override;
  
  void print_vl(std::ostream& out) const override {}
  
protected:
  snodeimpl* m_bus;
  uint32_t m_index;
};

class outputimpl : public ioimpl {
public:
  outputimpl(const std::string& name, uint32_t index, const lnode& src);
  ~outputimpl() {}
  
  const bitvector& eval(ch_cycle t);
  
  void print(std::ostream& out) const override;
  
  void print_vl(std::ostream& out) const override {}

protected:
  uint32_t  m_index;
};

class tapimpl : public ioimpl {
public:
  tapimpl(const std::string& name, const lnode& src);
  ~tapimpl() {}
  
  const std::string& get_tapName() const {
    return m_tapName;
  }
  
  const bitvector& eval(ch_cycle t);
  
  void print(std::ostream& out) const override;
  
  void print_vl(std::ostream& out) const override {}
  
protected:
  std::string  m_tapName;
};

}
