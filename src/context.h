#pragma once

namespace cash {
namespace detail {

class lnode;
class lnodeimpl;
class undefimpl;
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

  void push_clk(const lnode& clk);
  void pop_clk();
  lnodeimpl* get_clk();

  void push_reset(const lnode& reset);
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
  void conditional_split(lnode& dst, uint32_t offset, uint32_t length);
  void conditional_assign(lnode& dst, const lnode& src, uint32_t offset, uint32_t length);  
  void erase_block_local(lnodeimpl* src, lnodeimpl* dst);
  
  lnodeimpl* create_literal(const bitvector& value);
  
  cdomain* create_cdomain(const std::vector<clock_event>& sensitivity_list);
  void remove_cdomain(cdomain* cd);
    
  //-- 

  lnodeimpl* bind_input(const snode& bus);
  snodeimpl* bind_output(const lnode& output);
  
  void register_tap(const std::string& name, const lnode& lnode);
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
    cond_upd_t(selectimpl* p_sel, uint32_t p_block_id)
      : sel(p_sel)
      , block_id(p_block_id)
    {}
    selectimpl* sel;
    uint32_t block_id;
  };
  
  struct cond_var_t {
    cond_var_t(selectimpl* p_sel, uint32_t p_block_id) {
      updates.emplace_front(p_sel, p_block_id);
    }
    std::list<cond_upd_t> updates;
  };

  struct cond_block_t {
    cond_block_t(uint32_t p_id, lnodeimpl* p_cond)
      : id(p_id)
      , cond(p_cond)
    {}
    uint32_t id;
    lnodeimpl* cond;
    std::set<lnodeimpl*> locals;
  };

  struct cond_branch_t {
    std::vector<lnodeimpl*> conds;
  };

  typedef std::map<uint32_t, std::list<cond_var_t>> cond_vars_t;

  typedef std::list<cond_block_t> cond_blocks_t;

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
  std::stack<lnode>       user_clks_;
  std::stack<lnode>       user_resets_;

  uint32_t    node_ids_;
  uint32_t    block_ids_;
  inputimpl*  clk_;
  inputimpl*  reset_;
  
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
