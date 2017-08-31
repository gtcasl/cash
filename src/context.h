#pragma once

namespace cash {
namespace internal {

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

  void begin_block(lnodeimpl* pred = nullptr);
  void end_block();

  bool conditional_enabled(lnodeimpl* node = nullptr) const;
  void conditional_assign(lnode& dst, const lnode& src, uint32_t offset, uint32_t length);
  void remove_from_locals(lnodeimpl* node);
  
  lnodeimpl* createLiteralNode(const bitvector& value);

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
  
  void get_live_nodes(std::unordered_set<lnodeimpl*>& live_nodes);
  
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

  struct cond_range_t {
    uint32_t nodeid;
    uint32_t offset;
    uint32_t length;

    bool operator==(const cond_range_t& range) const {
      return this->nodeid == range.nodeid
          && this->offset == range.offset
          && this->length == range.length;
    }

    bool operator!=(const cond_range_t& range) const {
      return !(*this == range);
    }

    bool operator<(const cond_range_t& range) const {
      if (this->nodeid != range.nodeid)
        return (this->nodeid < range.nodeid);
      if (this->offset != range.offset)
        return (this->offset < range.offset);
      if (this->length != range.length)
        return (this->length < range.length);
      return false;
    }
  };

  struct cond_branch_t {
    lnodeimpl* else_pred;
  };

  typedef std::list<cond_branch_t> cond_branches_t;

  struct cond_block_t {
    cond_block_t(uint32_t p_id, lnodeimpl* p_pred, cond_branches_t::iterator p_branch)
      : id(p_id)
      , pred(p_pred)
      , branch(p_branch)
    {}
    uint32_t id;
    lnodeimpl* pred;
    cond_branches_t::iterator branch;
    std::unordered_map<uint32_t, lnodeimpl*> agg_preds;
    std::unordered_set<lnodeimpl*> locals;
  };

  typedef std::list<cond_block_t> cond_blocks_t;

  typedef std::map<cond_range_t, std::list<cond_upd_t>> cond_upds_t;

  lnodeimpl* build_aggregate_predicate(
      cond_blocks_t::iterator def_block,
      cond_blocks_t::iterator use_block);

  void clone_conditional_assignment(
      lnode& dst,
      const cond_range_t& range,
      uint32_t offset,
      uint32_t length);
  
  std::list<lnodeimpl*>   nodes_;
  std::list<undefimpl*>   undefs_;
  std::list<proxyimpl*>   proxies_;
  std::list<inputimpl*>   inputs_;
  std::list<outputimpl*>  outputs_;
  std::list<tapimpl*>     taps_;
  std::list<ioimpl*>      gtaps_;
  std::list<litimpl*>     literals_;
  std::list<cdomain*>     cdomains_;  
  cond_upds_t             cond_upds_;
  cond_blocks_t           cond_blocks_;
  cond_branches_t         cond_branches_;
  std::stack<lnode>       user_clks_;
  std::stack<lnode>       user_resets_;

  uint32_t    node_ids_;
  uint32_t    block_ids_;
  inputimpl*  clk_;
  inputimpl*  reset_;
  
  std::unordered_map<std::string, unsigned> dup_taps_;
  
  friend class ch_compiler;
  friend class ch_simulator;
  friend class ch_tracer;
};

context* ctx_begin();
context* ctx_curr();
void ctx_end();

}
}
