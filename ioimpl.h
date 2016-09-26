#pragma once

#include "nodeimpl.h"

namespace chdl_internal {

class iobridge;
class busimpl;

class ioimpl : public nodeimpl {
public:
  ioimpl(const std::string& name, context* ctx, uint32_t size);
  virtual ~ioimpl();
  
  void bind(iobridge* bridge);
  
  void print_vl(std::ostream& out) const override {}
  
protected:

  iobridge* m_bridge;
    
  friend class context;
};

class inputimpl : public ioimpl {
public:
  inputimpl(const std::string& name, uint32_t index, context* ctx, uint32_t size);
  ~inputimpl() {}

  bool ready() const override;
  bool valid() const override;  
  const bitvector& eval(ch_cycle t) override;
  
  virtual void print(std::ostream& out) const;
  
protected:
  uint32_t  m_index;
};

class outputimpl : public ioimpl {
public:
  outputimpl(const std::string& name, uint32_t index, const ch_node& src);
  ~outputimpl() {}
  
  const bitvector& eval(ch_cycle t);
  
  virtual void print(std::ostream& out) const;

protected:
  uint32_t  m_index;
};

class tapimpl : public ioimpl {
public:
  tapimpl(const std::string& name, const ch_node& src);
  ~tapimpl() {}
  
  const std::string& get_tapName() const {
    return m_tapName;
  }
  
  const bitvector& eval(ch_cycle t);
  
protected:
  std::string  m_tapName;
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
