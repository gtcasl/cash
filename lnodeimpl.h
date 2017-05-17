#pragma once

#include "lnode.h"

namespace chdl_internal {

#define CHDL_OPERATOR_TYPE(t) op_##t,
#define CHDL_OPERATOR_NAME(n) #n,
#define CHDL_OPERATOR_ENUM(m) \
  m(undef) \
  m(proxy) \
  m(lit) \
  m(input) \
  m(output) \
  m(clk) \
  m(reset) \
  m(tap) \
  m(assert) \
  m(tick) \
  m(print) \
  m(select) \
  m(reg) \
  m(latch) \
  m(mem) \
  m(memport) \
  m(inv) \
  m(and) \
  m(or) \
  m(xor) \
  m(nand) \
  m(nor) \
  m(xnor) \
  m(andr) \
  m(orr) \
  m(xorr) \
  m(shl) \
  m(shr) \
  m(rotl) \
  m(rotr) \
  m(add) \
  m(sub) \
  m(neg) \
  m(mult) \
  m(div) \
  m(mod) \
  m(eq) \
  m(ne) \
  m(lt) \
  m(gt) \
  m(le) \
  m(ge) \
  m(mux) \
  m(demux) \
  m(fadd) \
  m(fsub) \
  m(fmult) \
  m(fdiv)
  
enum ch_operator {
  CHDL_OPERATOR_ENUM(CHDL_OPERATOR_TYPE)
};

const char* to_string(ch_operator op);

class lnodeimpl {
public:
  lnodeimpl(ch_operator op, context* ctx, uint32_t size);
  virtual ~lnodeimpl();
  
  uint32_t get_id() const {
    return m_id;
  }
  
  ch_operator get_op() const {
    return m_op;
  }
  
  const char* get_name() const;
  
  context* get_ctx() const {
    return m_ctx;
  }

  void add_ref(const lnode* node, const lnode* source);

  void remove_ref(const lnode* node);

  void update_ref(const lnode* node, lnodeimpl* impl);
  
  const lnode* get_ref_owner(const lnode* node);
  
  const std::vector<lnode>& get_srcs() const {
    return m_srcs;
  }
  
  std::vector<lnode>& get_srcs() {
    return m_srcs;
  }
  
  lnodeimpl* get_src(unsigned i) const {
    return m_srcs[i].get_impl();
  }
  
  lnodeimpl* get_src(unsigned i) {
    return m_srcs[i].get_impl();
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
  
  struct ref_t {
    const lnode* node;
    const lnode* owner;
    
    ref_t(const lnode* node_ = nullptr, const lnode* owner_ = nullptr) 
      : node(node_), owner(owner_) 
    {}
    
    bool operator ==(const ref_t& rhs) const {
      return (node == rhs.node);
    }
    
    bool operator <(const ref_t& rhs) const {
      return (node < rhs.node);
    }
  };

  uint32_t m_id;
  ch_operator m_op;
  context* m_ctx;
  std::set<ref_t> m_refs;
  std::vector<lnode> m_srcs;  
  bitvector m_value; 
  
  friend class context;
};

class undefimpl : public lnodeimpl {
public:
  undefimpl(context* ctx, uint32_t size);

  const bitvector& eval(ch_cycle t) override;  
  void print_vl(std::ostream& out) const override;
};

}
