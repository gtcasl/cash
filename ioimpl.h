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
  
  bool ready() const override;
  bool valid() const override;  
  const bitvector& eval(ch_cycle t);
};

class iobridge : public refcounted {
public:
  iobridge() {}
  ~iobridge() {}

  virtual void detach() = 0;
  virtual const bitvector& eval(ch_cycle t) = 0;
};

class ibridge : public iobridge {
public:
  explicit ibridge(busimpl* impl) : m_impl(impl) {}
  ~ibridge() {}

  void detach();
  const bitvector& eval(ch_cycle t) override;

private:

  busimpl* m_impl;
};

class obridge : public iobridge {
public:
  explicit obridge(ioimpl* impl) : m_impl(impl) {}
  ~obridge() {}
  
  void detach();
  const bitvector& eval(ch_cycle t);
  
private:

  ioimpl* m_impl;
};

}
