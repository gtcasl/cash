#pragma once

namespace cash {
namespace detail {

class lnode;
class lnodeimpl;
class proxyimpl;
class litimpl;
class ioimpl;
class inputimpl;
class outputimpl;
class selectimpl;
class tapimpl;
class assertimpl;
class snode;
class snodeimpl;
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
  void begin_block(lnodeimpl* cond);
  void end_block();
  bool conditional_enabled(lnodeimpl* node = nullptr) const;
  lnodeimpl* resolve_conditional(lnodeimpl* dst, lnodeimpl* src);
  void move_block_local(lnodeimpl* dst, lnodeimpl* src);
  
  lnodeimpl* create_literal(const bitvector& value);
  
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

  struct cond_upd_t {
    cond_upd_t(selectimpl* sel_, uint32_t block_id_)
      : sel(sel_)
      , block_id(block_id_)
    {}
    selectimpl* sel;
    uint32_t block_id;
  };
  
  struct cond_var_t {
    cond_var_t(selectimpl* sel, uint32_t block_id) {
      updates.emplace_front(sel, block_id);
    }
    std::list<cond_upd_t> updates;
  };

  typedef std::vector<cond_var_t> cond_vars_t;

  struct cond_block_t {
    cond_block_t(uint32_t id_, lnodeimpl* cond_)
      : id(id_)
      , cond(cond_)
    {}
    uint32_t id;
    lnodeimpl* cond;
    std::set<lnodeimpl*> locals;
  };

  typedef std::list<cond_block_t> cond_blocks_t;

  struct cond_branch_t {
    std::vector<lnodeimpl*> conds;
  };

  typedef std::list<cond_branch_t> cond_branches_t;
  
  std::list<lnodeimpl*>   nodes_;
  std::list<undefimpl*>   undefs_;
  std::list<proxyimpl*>   proxies_;
  std::list<inputimpl*>   inputs_;
  std::list<outputimpl*>  outputs_;
  std::list<tapimpl*>     taps_;
  std::list<ioimpl*>      gtaps_;
  std::list<litimpl*>     literals_;
  std::list<cdomain*>     cdomains_;  
  cond_vars_t             cond_vars_;
  cond_blocks_t           cond_blocks_;
  cond_branches_t         cond_branches_;
  std::stack<lnode>       clk_stack_;
  std::stack<lnode>       reset_stack_;

  uint32_t   node_ids_;
  uint32_t   block_ids_;
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
