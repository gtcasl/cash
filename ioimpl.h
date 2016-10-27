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
  inputimpl(const std::string& name, context* ctx, uint32_t size);
  ~inputimpl();
  
  void bind(snodeimpl* bus);

  const bitvector& eval(ch_cycle t) override;
  
  void print(std::ostream& out) const override;
  
  void print_vl(std::ostream& out) const override {}
  
protected:
  snodeimpl* m_bus;
};

class outputimpl : public ioimpl {
public:
  outputimpl(const std::string& name, lnodeimpl* src);
  ~outputimpl();
  
  const bitvector& eval(ch_cycle t);
  
  snodeimpl* get_bus();
  
  void print(std::ostream& out) const override;
  
  void print_vl(std::ostream& out) const override {}
  
private:
  snodeimpl* m_bus;
};

class tapimpl : public outputimpl {
public:
  tapimpl(const std::string& name, lnodeimpl* src);
  ~tapimpl() {}
  
  const std::string& get_tapName() const {
    return m_tapName;
  }
  
  void print(std::ostream& out) const override;
  
  void print_vl(std::ostream& out) const override {}
  
protected:
  std::string  m_tapName;
};

}
