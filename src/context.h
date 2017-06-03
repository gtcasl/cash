#pragma once

namespace cash {
namespace detail {

class lnode;
class snode;
class lnodeimpl;
class snodeimpl;
class undefimpl;
class litimpl;
class ioimpl;
class inputimpl;
class outputimpl;
class tapimpl;
class assertimpl;
class clock_event;
class cdomain;

class context : public refcounted {
public:
  context();
  ~context();

  //--

  void push_clk(lnodeimpl* clk);
  void pop_clk();
  lnodeimpl* get_clk();

  void push_reset(lnodeimpl* reset);
  void pop_reset();
  lnodeimpl* get_reset();

  //--
  
  uint32_t add_node(lnodeimpl* node);  
  void remove_node(lnodeimpl* node);
  
  void begin_branch();
  void end_branch();
  
  void begin_case(lnodeimpl* cond);
  void end_case();
  bool conditional_enabled(lnodeimpl* node = nullptr) const;
  lnodeimpl* resolve_conditional(lnodeimpl* dst, lnodeimpl* src);
  
  litimpl* create_literal(const bitvector& value);
  
  cdomain* create_cdomain(const std::vector<clock_event>& sensitivity_list);
  void remove_cdomain(cdomain* cd);
    
  //-- 

  lnodeimpl* bind_input(snodeimpl* bus);  
  snodeimpl* bind_output(lnodeimpl* output);
  
  void register_tap(const std::string& name, lnodeimpl* lnode);
  snodeimpl* get_tap(const std::string& name, uint32_t size);
  
  //--
  
  void syntax_check();
    
  //--
  
  void get_live_nodes(std::set<lnodeimpl*>& live_nodes);
  
  //--
  
  void tick(ch_cycle t);  
  void tick_next(ch_cycle t);
  void eval(ch_cycle t);
  
  //--
  
  void to_verilog(const std::string& module_name, std::ostream& out);
  
  void dump_ast(std::ostream& out, uint32_t level);
  
  void dump_cfg(lnodeimpl* node, std::ostream& out, uint32_t level);
  
  void dump_stats(std::ostream& out);
  
protected:
  
  struct cond_val_t {
    lnodeimpl* dst;
    lnodeimpl* sel;
    lnodeimpl* owner;
  };
  
  struct cond_case_t {
    lnodeimpl* cond;
    std::set<lnodeimpl*> locals;
    std::vector<uint32_t> assignments; 
    cond_case_t(lnodeimpl* cond_) : cond(cond_) {}
  };
  
  struct cond_block_t {
    std::list<cond_case_t> cases;
  };
  
  typedef std::vector<cond_val_t> cond_vals_t;
  typedef std::list<cond_block_t> cond_blocks_t;
  
  lnodeimpl* get_current_conditional(const cond_blocks_t::iterator& iterBlock, lnodeimpl* dst) const;
  
  std::list<lnodeimpl*>   nodes_;
  std::list<undefimpl*>   undefs_;  
  std::list<inputimpl*>   inputs_;
  std::list<outputimpl*>  outputs_;
  std::list<tapimpl*>     taps_;
  std::list<ioimpl*>      gtaps_;
  std::list<litimpl*>     literals_;
  std::list<cdomain*>     cdomains_;
  cond_blocks_t           cond_blocks_;   
  cond_vals_t             cond_vals_;
  std::stack<lnode>       clk_stack_;
  std::stack<lnode>       reset_stack_;

  uint32_t   nodeids_;
  inputimpl* clk_;
  inputimpl* reset_;
  
  std::map<std::string, unsigned> dup_taps_;
  
  friend class ch_compiler;
  friend class ch_simulator;
  friend class ch_tracer;
};

context* ctx_begin();
context* ctx_curr();
void ctx_end();

}
}
