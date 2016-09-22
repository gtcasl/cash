#pragma once

#include "nodeimpl.h"

namespace chdl_internal {

class iobridge;
class busimpl;

class ioimpl : public nodeimpl {
public:
  ioimpl(context* ctx, uint32_t size, const std::string name);
  virtual ~ioimpl();
  
  const std::string get_name() const {
    return m_name;
  }
  
  void bind(iobridge* bridge);
  
  void print(std::ostream& out) const override {}
  void print_vl(std::ostream& out) const override {}
  
protected:

  std::string m_name;
  iobridge* m_bridge;
  
  friend class context;
};

class inputimpl : public ioimpl {
public:
  inputimpl(context* ctx, uint32_t size, const std::string name);
  ~inputimpl() {}

  bool ready() const override;
  bool valid() const override;  
  const bitvector& eval(ch_cycle t) override;
};

class outputimpl : public ioimpl {
public:
  outputimpl(const ch_node& src, const std::string name);
  ~outputimpl() {}
  
  const bitvector& eval(ch_cycle t);
};

class iobridge : public refcounted {
public:
  iobridge() {}
  ~iobridge() {}
  
  virtual bool ready() const = 0;
  virtual bool valid() const = 0;  

  virtual void detach() = 0;
  virtual const bitvector& eval(ch_cycle t) = 0;
};

class ibridge : public iobridge {
public:
  ibridge(busimpl* impl) : m_impl(impl) {}
  ~ibridge() {}
  
  bool ready() const override;
  bool valid() const override;

  void detach() override;
  const bitvector& eval(ch_cycle t) override;

private:

  busimpl* m_impl;
};

class obridge : public iobridge {
public:
  obridge(ioimpl* impl) : m_impl(impl) {}
  ~obridge() {}
  
  bool ready() const override;
  bool valid() const override;
  
  void detach() override;
  const bitvector& eval(ch_cycle t) override;
  
private:

  ioimpl* m_impl;
};

}
