#pragma once

#include "lnode.h"

namespace chdl_internal {

class context;

class lnodeimpl {
public:
  lnodeimpl(const std::string& name, context* ctx, uint32_t size, bool undefined = false);
  virtual ~lnodeimpl();
  
  uint64_t get_id() const {
    return m_id;
  }
  
  const std::string get_name() const {
    return m_name;
  }
  
  context* get_ctx() const {
    return m_ctx;
  }

  bool unreferenced() const {
    return m_refs.empty();
  }

  void add_ref(const lnode* node) {
    m_refs.emplace(node);
  }

  void remove_ref(const lnode* node) {
    m_refs.erase(node);
  }

  void replace_ref(lnodeimpl* impl);
  
  const std::vector<lnode>& get_srcs() const {
    return m_srcs;
  }
  
  std::vector<lnode>& get_srcs() {
    return m_srcs;
  }
  
  const lnode& get_src(unsigned i) const {
    return m_srcs[i];
  }
  
  lnode& get_src(unsigned i) {
    return m_srcs[i];
  }
  
  uint32_t get_size() const {
    return m_value.get_size();
  }
  
  const bitvector& get_value() const { 
    return m_value;
  }
  
  virtual bool ready() const;
  virtual bool valid() const;  
  virtual const bitvector& eval(ch_cycle t) = 0;
  
  virtual void print(std::ostream& out) const;
  virtual void print_vl(std::ostream& out) const = 0;

protected:

  std::string m_name;
  std::set<const lnode*> m_refs;
  std::vector<lnode> m_srcs;
  context* m_ctx;
  uint64_t m_id;
  bitvector m_value;
  
  friend class context;
};

class undefimpl : public lnodeimpl {
public:
  undefimpl(const std::string& name, context* ctx, uint32_t size);
  undefimpl(context* ctx, uint32_t size) : undefimpl("undef", ctx, size) {}
  virtual ~undefimpl();

  const bitvector& eval(ch_cycle t) override;  
  void print_vl(std::ostream& out) const override;
};

class nullimpl : public undefimpl {
public:
  nullimpl(context* ctx, uint32_t size) : undefimpl("null", ctx, size) {}
  ~nullimpl() {}
};

}
