#include "context.h"
#include <thread>
#include "lnode.h"
#include "litimpl.h"
#include "regimpl.h"
#include "memimpl.h"
#include "ioimpl.h"
#include "bindimpl.h"
#include "selectimpl.h"
#include "proxyimpl.h"
#include "memimpl.h"
#include "aluimpl.h"
#include "assertimpl.h"
#include "tickimpl.h"
#include "cdomain.h"
#include "arithm.h"
#include "select.h"
#include "misc.h"

namespace ch {
namespace internal {

class context_manager {
public:
  context_manager() : ctx_(nullptr) {}
  ~context_manager() {
    if (ctx_)
      ctx_->release();
  }

  context* create(size_t signature, const std::string& name) {
    std::string unique_name(name);
    auto it = module_names_.find(signature);
    if (it != module_names_.end()) {
      CH_CHECK(it->second == unique_name, "Multiple names assigned to same module: new=%s, old=%s", unique_name.c_str(), it->second.c_str());
    } else {
      unique_name = unique_name_.get(unique_name.c_str());
      module_names_[signature] = unique_name;
    }
    return new context(unique_name.c_str());
  }

  context* get_ctx() const {
    CH_CHECK(ctx_ != nullptr, "invalid context!");
    return ctx_;
  }

  context* swap(context* ctx) {
    std::swap(ctx_, ctx);
    return ctx;
  }

protected:
  mutable context* ctx_;
  std::map<size_t, std::string> module_names_;
  unique_name unique_name_;
};

}
}

using namespace ch::internal;

thread_local context_manager tls_ctx;

context* ch::internal::ctx_create(size_t signature, const std::string& name) {
  return tls_ctx.create(signature, name);
}

context* ch::internal::ctx_swap(context* ctx) {
  return tls_ctx.swap(ctx);
}

context* ch::internal::ctx_curr() {
  return tls_ctx.get_ctx();
}

///////////////////////////////////////////////////////////////////////////////

static uint32_t make_id() {
  static uint32_t s_id(0);
  return s_id++;
}

context::context(const std::string& name)
  : id_(make_id())
  , name_(name)
  , node_ids_(0)
  , block_ids_(0)
  , default_clk_(nullptr)
  , default_reset_(nullptr)
  , tick_(nullptr)
{}

context::~context() {
  // delete allocated nodes
  for (auto it = nodes_.begin(), end = nodes_.end(); it != end;) {
    delete *it++;
  }
}

void context::push_clk(const lnode& clk) {  
  user_clks_.emplace(clk);
}

void context::pop_clk() {
  user_clks_.pop();
}

void context::push_reset(const lnode& reset) {
  user_resets_.emplace(reset);
}

void context::pop_reset() {
  user_resets_.pop();
}

lnodeimpl* context::get_clk() {
  if (!user_clks_.empty())
    return user_clks_.top().get_impl();
  if (nullptr == default_clk_) {
    default_clk_ = this->createNode<inputimpl>(1, "clk");
  }
  return default_clk_;
}

lnodeimpl* context::get_reset() {
  if (!user_resets_.empty())
    return user_resets_.top().get_impl();
  if (nullptr == default_reset_) {
     default_reset_ = this->createNode<inputimpl>(1, "reset");
  }
  return default_reset_;
}

lnodeimpl* context::get_tick() {
  if (nullptr == tick_) {
    tick_ = this->createNode<tickimpl>();
  }
  return tick_;
}

uint32_t context::node_id() {
  uint32_t nodeid = ++node_ids_;
#ifndef NDEBUG
  uint32_t dbg_nodeid = platform::self().get_dbg_node();
  if (dbg_nodeid) {
    if (nodeid == dbg_nodeid) {
      CH_ABORT("debugbreak on nodeid %d hit!", nodeid);
    }
  }
#endif
  return nodeid;
}

void context::destroyNode(lnodeimpl* node) {
  this->remove_node(node);
  delete node;
}

void context::add_node(lnodeimpl* node) {
  nodes_.emplace_back(node);

  switch (node->get_type()) {
  case type_undef:
    undefs_.emplace_back((undefimpl*)node);
    break;
  case type_proxy:
    proxies_.emplace_back((proxyimpl*)node);
    break;
  case type_lit:
    literals_.emplace_back((litimpl*)node);
    break;
  case type_input:
    {
      // ensure clock and reset signals are ordered first
      auto input = dynamic_cast<inputimpl*>(node);
      if (input->get_name() == "clk") {
        inputs_.emplace_front(input);
      } else if (input->get_name() == "reset") {
        if (default_clk_) {
          inputs_.emplace(std::next(inputs_.begin()), input);
        } else {
          inputs_.emplace_front(input);
        }
      } else {
        inputs_.emplace_back(input);
      }
    }
    break;  
  case type_output:
    outputs_.emplace_back((outputimpl*)node);
    break; 
  case type_bind:
    bindings_.emplace_back((bindimpl*)node);
    break;
  case type_tap:
    taps_.emplace_back((tapimpl*)node);
    break;
  case type_assert:
  case type_print:
    gtaps_.emplace_back((ioimpl*)node);
    break;
  default:
    break;
  }

  // register local nodes, io objects have global scope
  if (!cond_blocks_.empty()
   && nullptr == dynamic_cast<ioimpl*>(node)) {
    cond_blocks_.front().locals.emplace(node);
  }
}

void context::remove_node(lnodeimpl* node) {
  DBG(3, "*** deleting node: %s%d(#%d)!\n",
      to_string(node->get_type()), node->get_size(), node->get_id());
  
  assert(!nodes_.empty());
  nodes_.remove(node);
  
  switch (node->get_type()) {
  case type_undef:
    undefs_.remove((undefimpl*)node);
    break;
  case type_proxy:
    proxies_.remove((proxyimpl*)node);
    break;
  case type_lit:
    literals_.remove((litimpl*)node);
    break;
  case type_input:
    if (node == default_clk_) {
      default_clk_ = nullptr;
    } else
    if (node == default_reset_) {
      default_reset_ = nullptr;
    }
    inputs_.remove((inputimpl*)node);
    break;
  case type_output:
    outputs_.remove((outputimpl*)node);
    break;
  case type_bind:
    bindings_.remove((bindimpl*)node);
    break;
  case type_tap:
    taps_.remove((tapimpl*)node);
    break;
  case type_assert:
  case type_print:
    gtaps_.remove((ioimpl*)node);
    break;
  case type_tick:
    if (node == tick_)
      tick_ = nullptr;
    break;
  default:
    break;
  }
}

void context::begin_branch() {
  cond_branches_.emplace_front(cond_branch_t());
}

void context::end_branch() {
  assert(!cond_branches_.empty());
  cond_branches_.pop_front();
  if (cond_branches_.empty()) {
    cond_upds_.clear();
    block_ids_ = 0;
  }
}

void context::begin_block(lnodeimpl* pred) {
  // compute 'else' predicate
  auto branch = cond_branches_.begin();
  if (nullptr == branch->else_pred) {
    branch->else_pred = pred;
  } else {
    if (pred) {
      branch->else_pred = createAluNode(alu_or, branch->else_pred, pred);
    } else {
      branch->else_pred = createAluNode(alu_inv, branch->else_pred);
    }
  }
  // insert new conditional block
  cond_blocks_.emplace_front(++block_ids_, pred, branch);
}

void context::end_block() {
  assert(!cond_blocks_.empty());
  cond_blocks_.pop_front();
}

lnodeimpl* context::build_aggregate_predicate(
    cond_blocks_t::iterator def_block,
    cond_blocks_t::iterator use_block) {
  // try use precomputed value from cache
  uint32_t def_block_id = (def_block != cond_blocks_.end()) ? def_block->id : 0;
  if (use_block->agg_preds.count(def_block_id) != 0) {
    return use_block->agg_preds.at(def_block_id);
  }

  auto pred = use_block->pred;

  // add parent predicate
  auto parent_block = std::next(use_block);
  if (parent_block != def_block) {
    if (nullptr == pred) {
      pred = use_block->branch->else_pred;
    }
    auto parent_pred = this->build_aggregate_predicate(def_block, parent_block);
    if (nullptr == parent_pred) {
      parent_pred = parent_block->branch->else_pred;
    }
    pred = createAluNode(alu_and, parent_pred, pred);
  }
  use_block->agg_preds[def_block_id] = pred;

  return pred;
}

lnodeimpl* context::get_predicate(lnodeimpl* node, uint32_t offset, uint32_t length) {
  // get variable decl block
  auto def_block = std::find_if(cond_blocks_.begin(), cond_blocks_.end(),
    [&](const cond_block_t& cond_block)->bool {
      return cond_block.locals.count(node) != 0;
    });

  auto pred = this->build_aggregate_predicate(def_block, cond_blocks_.begin());
  if (nullptr == pred) {
    // use the 'else' aggregate predicate if first assignment
    cond_range_t range{node->get_id(), offset, length};
    if (cond_upds_.find(range) == cond_upds_.end()) {
      cond_branch_t& branch = cond_branches_.front();
      pred = branch.else_pred;
    }
  }

  return pred;
}

bool context::conditional_enabled(lnodeimpl* node) const {
  // a node is conditionally assigned if it is not local to the current block
  return (!cond_blocks_.empty()
       && 0 == cond_blocks_.front().locals.count(node));
}

void context::conditional_assign(
    lnode& dst,
    const lnode& src,
    uint32_t offset,
    uint32_t length) {
  assert(this->conditional_enabled(dst.get_impl()));
  cond_range_t range{dst.get_id(), offset, length};

  // split overlapping assignment to same node
  auto it_upds = std::find_if(cond_upds_.begin(), cond_upds_.end(),
    [&](const cond_upds_t::value_type& v)->bool {
      const auto& curr = v.first;
      uint32_t curr_end = curr.offset + curr.length;
      uint32_t src_end = offset + length;
      return (curr != range)
          && (curr.nodeid == range.nodeid)
          && (offset < curr_end && src_end > curr.offset);
    });
  if (it_upds != cond_upds_.end()) {
    const auto& curr = it_upds->first;
    uint32_t curr_end = curr.offset + curr.length;
    uint32_t src_end = offset + length;
    // overlaps exist?
    if (offset < curr_end && src_end > curr.offset) {
      if (offset <= curr.offset && src_end >= curr_end) {
        // source fully overlaps
        assert(false);
      } else if (offset < curr.offset) {
        // source overlaps on the left
        this->clone_conditional_assignment(dst, curr, curr.offset, src_end - curr.offset);
        this->clone_conditional_assignment(dst, curr, src_end, curr_end - src_end);
      } else if (src_end > curr_end) {
        // source overlaps on the right
        this->clone_conditional_assignment(dst, curr, curr.offset, offset - curr.offset);
        this->clone_conditional_assignment(dst, curr, offset, curr_end - offset);
      } else {
        // source fully included
        if (offset != curr.offset) {
          this->clone_conditional_assignment(dst, curr, curr.offset, offset - curr.offset);
        }
        this->clone_conditional_assignment(dst, curr, offset, src_end - offset);
        if (src_end != curr_end) {
          this->clone_conditional_assignment(dst, curr, src_end, curr_end - src_end);
        }
      }
      // remove entry
      cond_upds_.erase(it_upds);
    }
  }

  // get the current conditional block
  cond_block_t& block = cond_blocks_.front();

  // lookup for dst assignment history  
  it_upds = cond_upds_.find(range);
  if (it_upds != cond_upds_.end()) {
    // check if last assignment took place in nested blocks
    auto it_upd = it_upds->second.begin();
    if (block.id < it_upd->block_id) {
      // erase all nested assignments
      auto it_upd_end = it_upds->second.end();
      for (;it_upd != it_upd_end;) {
        if (it_upd->block_id <= block.id)
          break;
        it_upd = it_upds->second.erase(it_upd);
      }
      // remove variable if no more assignment exist
      if (it_upd != it_upd_end) {
        cond_upds_.erase(it_upds);
        it_upds = cond_upds_.end();
      }
    }
  }

  selectimpl* sel;
  selectimpl* sel_old = nullptr;

  lnodeimpl* pred = this->get_predicate(dst.get_impl(), offset, length);

  if (it_upds != cond_upds_.end()) {
    sel_old = it_upds->second.front().sel;
    sel = sel_old;
    cond_upd_t& last_upd = it_upds->second.front();
    if (block.id > last_upd.block_id) {
      // last assignment took place in parent or sibling blocks
      if (pred) {
        // new conditional assignment
        sel = dynamic_cast<selectimpl*>(createSelectNode(pred, src, last_upd.sel));
        it_upds->second.emplace_front(sel, block.id);
      } else {
        // 'default' last assignment
        it_upds->second.back().sel->set_false(src);
      }
    } else {
      // reassignment in current block
      assert(block.id == last_upd.block_id);
      last_upd.sel->set_true(src);
    }
  } else {
    // new variable conditional assignment
    assert(pred);
    lnode _false(dst.get_impl()->get_slice(offset, length));
    sel = dynamic_cast<selectimpl*>(createSelectNode(pred, src, _false));
    cond_upds_[range].emplace_front(sel, block.id);
  }

  if (sel != sel_old) {
    auto proxy = dynamic_cast<proxyimpl*>(dst.get_impl());
    if (proxy) {
      proxy->add_source(offset, sel, 0, length);
    } else {
      dst.set_impl(sel);
    }
  }
}

void context::clone_conditional_assignment(
    lnode& dst,
    const cond_range_t& range,
    uint32_t offset,
    uint32_t length) {
  lnodeimpl* prev_sel_old = nullptr;
  lnodeimpl* prev_sel_new = nullptr;
  cond_range_t new_range{dst.get_id(), offset, length};
  // traverse assignment history in reverse order, from oldest to latest
  const auto& cond_upds = cond_upds_.at(range);  
  for (auto it_upd = cond_upds.rbegin(), it_upd_end = cond_upds.rend();
       it_upd != it_upd_end; ++it_upd) {
    auto sel_old = it_upd->sel;
    lnode _true((sel_old->get_true().get_impl() == prev_sel_old) ?
          prev_sel_new : this->createNode<proxyimpl>(sel_old->get_true(), offset - range.offset, length));
    lnode _false((sel_old->get_false().get_impl() == prev_sel_old) ?
          prev_sel_new : this->createNode<proxyimpl>(sel_old->get_false(), offset - range.offset, length));
    auto sel_new = dynamic_cast<selectimpl*>(createSelectNode(sel_old->get_pred(), _true, _false));
    cond_upds_[new_range].emplace_front(sel_new, it_upd->block_id);
    prev_sel_old = sel_old;
    prev_sel_new = sel_new;
  }
  auto proxy = dynamic_cast<proxyimpl*>(dst.get_impl());
  proxy->add_source(offset, prev_sel_new, 0, length);
}

void context::relocate_locals(lnodeimpl* dst, lnodeimpl* src) {
  if (cond_blocks_.empty())
    return;
  // remove from local scope
  cond_block_t& block = cond_blocks_.front();
  auto ret = block.locals.erase(src);
  if (ret > 0 && dst) {
    for (auto& block : cond_blocks_) {
      if (block.locals.count(dst) != 0) {
        block.locals.insert(src);
        break;
      }
    }
  }
}

lnodeimpl* context::get_literal(const bitvector& value) {
  for (litimpl* lit : literals_) {
    if (lit->get_value() == value)
      return lit;
  }
  return this->createNode<litimpl>(value);
}

cdomain* context::create_cdomain(
    const std::vector<clock_event>& sensitivity_list) {
  // return existing cdomain 
  for (cdomain* cd : cdomains_) {
    if (*cd == sensitivity_list)
      return cd;
  }  
  // allocate new cdomain
  cdomain* cd = new cdomain(this, sensitivity_list);
  cdomains_.emplace_back(cd);
  return cd;
}

void context::remove_cdomain(cdomain* cd) {
  cdomains_.remove(cd);
}

void context::register_tap(const std::string& name, const lnode& node) {
  this->createNode<tapimpl>(node, unique_tap_names_.get(name).c_str());
}

bindimpl* context::get_binding(context* module) {
  for (auto binding : bindings_) {
    if (binding->get_module() == module)
      return binding;
  }
  return this->createNode<bindimpl>(module);
}

void context::bind_input(const lnode& src, const lnode& input) {
  auto binding = this->get_binding(input.get_ctx());
  binding->bind_input(src, input);
}

void context::bind_output(const lnode& dst, const lnode& output) {
  auto binding = this->get_binding(output.get_ctx());
  binding->bind_output(dst, output);
}

live_nodes_t context::compute_live_nodes() const {
  live_nodes_t live_nodes;

  // default signals
  if (default_clk_) {
    live_nodes.emplace(default_clk_);
  }
  if (default_reset_) {
    live_nodes.emplace(default_reset_);
  }

  // get inputs
  for (auto node : inputs_) {
    live_nodes.emplace(node);
  }

  // get outputs
  for (auto node : outputs_) {
    live_nodes.emplace(node);
  }  
  
  // get debug taps
  for (auto node : taps_) {
    live_nodes.emplace(node);
  }

  // get assert taps
  for (auto node : gtaps_) {
    live_nodes.emplace(node);
  }

  return live_nodes;
}

void context::tick(ch_tick t) {
  for (auto node : bindings_) {
    node->tick(t);
  }
  for (auto cd : cdomains_) {
    cd->tick(t);
  }  
}

void context::tick_next(ch_tick t) {
  for (auto node : bindings_) {
    node->tick_next(t);
  }
  for (auto cd : cdomains_) {
    cd->tick_next(t);
  }  
}

void context::eval(ch_tick t) {
  // evaluate bindings
  for (auto node : bindings_) {
    node->eval(t);
  }

  // evaluate outputs
  for (auto node : outputs_) {
    node->eval(t);
  }

  // evaluate taps
  for (auto node : taps_) {
    node->eval(t);
  }

  // evaluate asserts
  for (auto node : gtaps_) {
    node->eval(t);
  }
}

void context::dump_ast(std::ostream& out, uint32_t level) {
  for (lnodeimpl* node : nodes_) {
    node->print(out, level);
    out << std::endl;
  }
}

static void dump_cfg_impl(
    lnodeimpl* node,
    std::ostream& out,
    uint32_t level,
    std::vector<bool>& visits,
    const std::unordered_map<uint32_t, tapimpl*>& taps) {
  visits[node->get_id()] = true;
  node->print(out, level);
  
  auto iter = taps.find(node->get_id());
  if (iter != taps.end()) {
    out << " // " << iter->second->get_name();
    out << std::endl;
    return;
  }  
  out << std::endl;
  
  for (const lnode& src : node->get_srcs()) {
    if (!visits[src.get_id()]) {
      dump_cfg_impl(src.get_impl(), out, level, visits, taps);
    }
  }  
}

void context::dump_cfg(lnodeimpl* node, std::ostream& out, uint32_t level) {
  std::vector<bool> visits(node_ids_ + 1);
  std::unordered_map<uint32_t, tapimpl*> taps;
  
  for (tapimpl* tap : taps_) {
    taps[tap->get_target().get_id()] = tap;
  }
  
  visits[node->get_id()] = true;
  
  auto tap = dynamic_cast<tapimpl*>(node);
  if (tap) {
    node = tap->get_target().get_impl();
    node->print(out, level);
    out << " // " << tap->get_name();
  } else {  
    node->print(out, level);
  }
  out << std::endl;    
  for (const lnode& src : node->get_srcs()) {
    if (!visits[src.get_id()]) {
      dump_cfg_impl(src.get_impl(), out, level, visits, taps);
    }
  }
}

void context::dump_stats(std::ostream& out) {
  uint32_t memory_bits = 0;
  uint32_t register_bits = 0;
  uint32_t num_memories = 0;
  uint32_t num_registers = 0;
  uint32_t num_muxes = 0;
  uint32_t num_alus = 0;
  uint32_t num_lits = 0;
  uint32_t num_proxies = 0;
  
  for (lnodeimpl* node : nodes_) {
    auto* mem = dynamic_cast<memimpl*>(node);
    if (mem) {
      ++num_memories;
      memory_bits += mem->get_total_size();      
      continue;
    }
    auto* reg = dynamic_cast<regimpl*>(node);
    if (reg) {
      ++num_registers;
      register_bits += reg->get_size();      
      continue;
    }
    auto* sel = dynamic_cast<selectimpl*>(node);
    if (sel) {
      ++num_muxes;
      continue;
    }
    auto* alu = dynamic_cast<aluimpl*>(node);
    if (alu) {
      ++num_alus;
      continue;
    }
    auto* lit = dynamic_cast<litimpl*>(node);
    if (lit) {
      ++num_lits;
      continue;
    }
    auto* proxy = dynamic_cast<proxyimpl*>(node);
    if (proxy) {
      ++num_proxies;
      continue;
    }
  }
  
  out << "ch-stats: total memories = " << num_memories << std::endl;
  out << "ch-stats: total memory bits = " << memory_bits << std::endl;
  out << "ch-stats: total registers = " << num_registers << std::endl;
  out << "ch-stats: total regiters bits = " << register_bits << std::endl;
  out << "ch-stats: total muxes = " << num_muxes << std::endl;
  out << "ch-stats: total alus = " << num_alus << std::endl;
  out << "ch-stats: total literals = " << num_lits << std::endl;
  out << "ch-stats: total proxies = " << num_proxies << std::endl;
}

///////////////////////////////////////////////////////////////////////////////

void ch::internal::registerTap(const std::string& name, const lnode& node) {
  node.get_ctx()->register_tap(name, node);
}

void ch::internal::ch_dumpStats(std::ostream& out, const device& device) {
  get_ctx(device)->dump_stats(out);
}

void ch::internal::bindInput(const lnode& src, const lnode& input) {
  src.get_ctx()->bind_input(src, input);
}

void ch::internal::bindOutput(const lnode& dst, const lnode& output) {
  dst.get_ctx()->bind_output(dst, output);
}
