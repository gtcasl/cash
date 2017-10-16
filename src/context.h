#pragma once

#include "common.h"

namespace ch {
namespace internal {

class bitvector;
class lnode;
class nodelist;
class lnodeimpl;
class undefimpl;
class proxyimpl;
class litimpl;
class ioimpl;
class inputimpl;
class outputimpl;
class callimpl;
class callportimpl;
class selectimpl;
class tapimpl;
class assertimpl;
class tickimpl;
class clock_event;
class cdomain;

using ch_tick = uint64_t;

using node_map_t = std::unordered_map<uint32_t, std::vector<const lnode*>>;

using live_nodes_t = std::unordered_set<lnodeimpl*>;

class context : public refcounted {
public:
  uint32_t get_id() const {
    return id_;
  }

  const std::string& get_name() const {
    return name_;
  }

  const auto& get_nodes() const {
    return nodes_;
  }

  const auto& get_undefs() const {
    return undefs_;
  }

  const auto& get_proxies() const {
    return proxies_;
  }

  const auto& get_inputs() const {
    return inputs_;
  }

  const auto& get_outputs() const {
    return outputs_;
  }

  const auto& get_taps() const {
    return taps_;
  }

  const auto& get_gtaps() const {
    return gtaps_;
  }

  const auto& get_literals() const {
    return literals_;
  }

  auto get_default_clk() const {
    return default_clk_;
  }

  auto get_default_reset() const {
    return default_reset_;
  }

  const auto& get_calls() const {
    return calls_;
  }

  const auto& get_callports() const {
    return callports_;
  }

  //--

  void push_clk(const lnode& clk);
  void pop_clk();
  lnodeimpl* get_clk();

  void push_reset(const lnode& reset);
  void pop_reset();
  lnodeimpl* get_reset();

  //--

  lnodeimpl* get_tick();

  //--

  uint32_t node_id();

  template <typename T, typename... Ts>
  T* createNode(Ts&&... args) {
    auto node = new T(this, std::forward<Ts>(args)...);
    this->add_node(node);
    return node;
  }

  void destroyNode(lnodeimpl* node);

  void add_node(lnodeimpl* node);
  void remove_node(lnodeimpl* node);
  
  //--

  void begin_branch();
  void end_branch();

  void begin_block(lnodeimpl* pred = nullptr);
  void end_block();

  bool conditional_enabled(lnodeimpl* node = nullptr) const;
  void conditional_assign(lnode& dst, const lnode& src, uint32_t offset, uint32_t length);
  lnodeimpl* get_predicate(lnodeimpl* node, uint32_t offset, uint32_t length);
  void remove_from_locals(lnodeimpl* node);

  //--
  
  lnodeimpl* get_literal(const bitvector& value);

  cdomain* create_cdomain(const std::vector<clock_event>& sensitivity_list);
  void remove_cdomain(cdomain* cd);

  void register_tap(const std::string& name, const lnode& lnode);

  //--
  
  void syntax_check();
    
  //--
  
  live_nodes_t compute_live_nodes() const;
  
  //--
  
  void tick(ch_tick t);  
  void tick_next(ch_tick t);
  void eval(ch_tick t);
  
  //--
  
  void dump_ast(std::ostream& out, uint32_t level);
  
  void dump_cfg(lnodeimpl* node, std::ostream& out, uint32_t level);
  
  void dump_stats(std::ostream& out);

  //--

  void bind_input(const lnode& input, const lnode& src);

  void bind_output(const lnode& dst, const lnode& output);
  
protected:

  context(const std::string& name);
  ~context();

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
    cond_block_t(uint32_t p_id,
                 lnodeimpl* p_pred,
                 cond_branches_t::iterator p_branch)
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

  callimpl* find_call(context* module_ctx);

  uint32_t    id_;
  std::string name_;

  uint32_t    node_ids_;
  uint32_t    block_ids_;
  inputimpl*  default_clk_;
  inputimpl*  default_reset_;
  tickimpl*   tick_;
  
  std::list<lnodeimpl*>  nodes_;
  std::list<undefimpl*>  undefs_;
  std::list<proxyimpl*>  proxies_;
  std::list<inputimpl*>  inputs_;
  std::list<outputimpl*> outputs_;
  std::list<tapimpl*>    taps_;
  std::list<ioimpl*>     gtaps_;
  std::list<litimpl*>    literals_;
  std::list<cdomain*>    cdomains_;
  std::list<callimpl*>   calls_;
  std::list<callportimpl*> callports_;

  cond_upds_t            cond_upds_;
  cond_blocks_t          cond_blocks_;
  cond_branches_t        cond_branches_;

  std::stack<lnode>      user_clks_;
  std::stack<lnode>      user_resets_;

  unique_name            unique_tap_names_;

  friend class context_manager;
};

context* ctx_create(size_t signature, const std::string& name);
context* ctx_swap(context* ctx);
context* ctx_curr();

}
}
