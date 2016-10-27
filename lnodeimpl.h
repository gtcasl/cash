#pragma once

#include "lnode.h"

namespace chdl_internal {

class lnodeimpl : public refcounted {
public:
  lnodeimpl(const std::string& name, context* ctx, uint32_t size);
  virtual ~lnodeimpl();
  
  uint32_t get_id() const {
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

  virtual void remove_ref(const lnode* curr_owner, lnodeimpl* new_owner) {
    m_refs.erase(curr_owner);
  }

  void replace_refs(lnodeimpl* impl);
  
  virtual void update_refs(uint32_t start, lnodeimpl* new_owner, uint32_t offset, uint32_t length) {}
  
  lnodeimpl* resolve(lnodeimpl* impl);
  
  const std::vector<lnode>& get_srcs() const {
    return m_srcs;
  }
  
  std::vector<lnode>& get_srcs() {
    return m_srcs;
  }
  
  lnodeimpl* get_src(unsigned i) const {
    return m_srcs[i];
  }
  
  lnodeimpl* get_src(unsigned i) {
    return m_srcs[i];
  }
  
  uint32_t get_size() const {
    return m_value.get_size();
  }
  
  const bitvector& get_value() const { 
    return m_value;
  }
  
  bitvector& get_value() { 
    return m_value;
  }
  
  virtual bool ready() const;
  virtual bool valid() const;  
  virtual const bitvector& eval(ch_cycle t) = 0;
  
  virtual void print(std::ostream& out) const;
  virtual void print_vl(std::ostream& out) const = 0;

protected:

  uint32_t m_id;
  std::string m_name;
  context* m_ctx;
  std::set<const lnode*> m_refs;
  std::vector<lnode> m_srcs;  
  bitvector m_value; 
  
  friend class context;
};

class undefimpl : public lnodeimpl {
public:
  undefimpl(context* ctx, uint32_t size);
  virtual ~undefimpl();
  
  void remove_ref(const lnode* curr_owner, lnodeimpl* new_owner) override;
  void update_refs(uint32_t start, lnodeimpl* new_owner, uint32_t offset, uint32_t length) override;

  const bitvector& eval(ch_cycle t) override;  
  void print_vl(std::ostream& out) const override;
};

}
