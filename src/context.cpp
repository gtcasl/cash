#include "context.h"
#include <thread>
#include "lnode.h"
#include "litimpl.h"
#include "regimpl.h"
#include "memimpl.h"
#include "ioimpl.h"
#include "snodeimpl.h"
#include "selectimpl.h"
#include "proxyimpl.h"
#include "memimpl.h"
#include "aluimpl.h"
#include "assertimpl.h"
#include "tickimpl.h"
#include "cdomain.h"
#include "device.h"
#include "arithm.h"
#include "select.h"

using namespace cash::internal;

thread_local context* tls_ctx = nullptr;

context::context()
  : node_ids_(0)
  , block_ids_(0)
  , clk_(nullptr)
  , reset_(nullptr)
  , tick_(nullptr)
{}

context::~context() {  
  // delete all nodes
  for (auto it = nodes_.begin(), end = nodes_.end(); it != end;) {
    delete *it++;
  }
  assert(undefs_.empty());
  assert(proxies_.empty());
  assert(literals_.empty());
  assert(inputs_.empty());
  assert(outputs_.empty());
  assert(taps_.empty());
  assert(gtaps_.empty());
  assert(cdomains_.empty());
  assert(cond_blocks_.empty());

  assert(nullptr == clk_);
  assert(nullptr == reset_);
  assert(nullptr == tick_);
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
  if (nullptr == clk_)
    clk_ = new inputimpl(op_clk, this, 1);
  return clk_;
}

lnodeimpl* context::get_reset() {
  if (!user_resets_.empty())
    return user_resets_.top().get_impl();
  if (nullptr == reset_)
     reset_ = new inputimpl(op_reset, this, 1);
  return reset_;
}

lnodeimpl* context::get_tick() {
  if (nullptr == tick_)
    tick_ = new tickimpl(this);
  return tick_;
}

uint32_t context::add_node(lnodeimpl* node) {
  uint32_t nodeid = ++node_ids_;
#ifndef NDEBUG
  uint32_t dbg_nodeid = platform::self().get_dbg_node();
  if (dbg_nodeid) {
    if (nodeid == dbg_nodeid) {
      CH_ABORT("debugbreak on nodeid %d hit!", nodeid);
    }
  }
#endif
  nodes_.emplace_back(node);
  
  bool is_ionode = false;

  switch (node->get_op()) {
  case op_undef:
    undefs_.emplace_back((undefimpl*)node);
    break;
  case op_proxy:
    proxies_.emplace_back((proxyimpl*)node);
    break;
  case op_lit:
    literals_.emplace_back((litimpl*)node);
    break;
  case op_input:
  case op_clk:
  case op_reset:  
    inputs_.emplace_back((inputimpl*)node);
    is_ionode = true;
    break;  
  case op_output:
    outputs_.emplace_back((outputimpl*)node);
    is_ionode = true;
    break; 
  case op_tap:
    taps_.emplace_back((tapimpl*)node);
    is_ionode = true;
    break;
  case op_assert:
  case op_print:
    gtaps_.emplace_back((ioimpl*)node);
    is_ionode = true;
    break;
  case op_mem:
  case op_memport:
  case op_tick:
    is_ionode = true;
    break;
  default:
    break;
  }

  // register local nodes
  // io objects have global scope
  if (!cond_blocks_.empty() && !is_ionode) {
    cond_blocks_.front().locals.emplace(node);
  }

  return nodeid;  
}

void context::remove_node(lnodeimpl* node) {
  DBG(3, "*** deleting node: %s%d(#%d)!\n", node->get_name(), node->get_size(), node->get_id());
  
  assert(!nodes_.empty());
  nodes_.remove(node);
  
  switch (node->get_op()) {
  case op_undef:
    undefs_.remove((undefimpl*)node);
    break;
  case op_proxy:
    proxies_.remove((proxyimpl*)node);
    break;
  case op_lit:
    literals_.remove((litimpl*)node);
    break;
  case op_input:
  case op_clk:
  case op_reset:
    if (node == clk_) {
      clk_ = nullptr;
    } else
    if (node == reset_) {
      reset_ = nullptr;
    }
    inputs_.remove((inputimpl*)node);
    break;  
  case op_output:
    outputs_.remove((outputimpl*)node);
    break; 
  case op_tap:
    taps_.remove((tapimpl*)node);
    break;
  case op_assert:
  case op_print:
    gtaps_.remove((ioimpl*)node);
    break;
  case op_tick:
    if (node == tick_) {
      tick_ = nullptr;
    }
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
      branch->else_pred = createAluNode(alu_op_or, branch->else_pred, pred);
    } else {
      branch->else_pred = createAluNode(alu_op_inv, branch->else_pred);
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
    pred = createAluNode(alu_op_and, parent_pred, pred);
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
    auto _false = dst.get_impl()->get_slice(offset, length);
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
    auto _true = (sel_old->get_true().get_impl() == prev_sel_old) ?
          prev_sel_new : new proxyimpl(sel_old->get_true(), offset - range.offset, length);
    auto _false = (sel_old->get_false().get_impl() == prev_sel_old) ?
          prev_sel_new : new proxyimpl(sel_old->get_false(), offset - range.offset, length);
    auto sel_new = dynamic_cast<selectimpl*>(createSelectNode(sel_old->get_pred(), _true, _false));
    cond_upds_[new_range].emplace_front(sel_new, it_upd->block_id);
    prev_sel_old = sel_old;
    prev_sel_new = sel_new;
  }
  auto proxy = dynamic_cast<proxyimpl*>(dst.get_impl());
  proxy->add_source(offset, prev_sel_new, 0, length);
}

void context::remove_from_locals(lnodeimpl* node) {
  if (cond_blocks_.empty())
    return;
  // remove from local scope
  cond_block_t& block = cond_blocks_.front();
  block.locals.erase(node);
}

lnodeimpl* context::createLiteralNode(const bitvector& value) {
  for (litimpl* lit : literals_) {
    if (lit->get_value() == value)
      return lit;
  }
  return new litimpl(this, value);
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

lnodeimpl* context::bind_input(const snode& bus) {
  inputimpl* impl = new inputimpl(this, bus.get_size());
  impl->bind(bus);
  return impl;
}

snodeimpl* context::bind_output(const lnode& output) {
  outputimpl* impl = new outputimpl(output);
  return impl->get_bus();
}

void context::register_tap(const std::string& name, const lnode& node) {
  // resolve duplicate names
  std::string full_name(name);
  unsigned instances = dup_taps_[name]++;
  if (instances > 0) {
    if (instances == 1) {
      // rename first instance
      auto iter = std::find_if(taps_.begin(), taps_.end(),
        [name](tapimpl* t)->bool { return t->get_tapName() == name; });
      assert(iter != taps_.end());
      (*iter)->set_tagName(fstring("%s_%d", name.c_str(), 0));
    }
    full_name = fstring("%s_%d", name.c_str(), instances);
  }
  // create tap node
  new tapimpl(full_name, node);
}

snodeimpl* context::get_tap(const std::string& name, uint32_t size) {
  for (tapimpl* tap : taps_) {
    if (tap->get_tapName() == name) {
      CH_CHECK(tap->get_size() == size, "tap bus size mismatch: received %u, expected %u", size, tap->get_size());
      return tap->get_bus();
    }
  } 
  CH_ABORT("couldn't find tab '%s'", name.c_str());
}

void context::get_live_nodes(std::unordered_set<lnodeimpl*>& live_nodes) {
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
}

void context::tick(ch_tick t) {
  for (auto cd : cdomains_) {
    cd->tick(t);
  }  
}

void context::tick_next(ch_tick t) {
  for (auto cd : cdomains_) {
    cd->tick_next(t);
  }  
}

void context::eval(ch_tick t) {
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

void context::to_verilog(const std::string& module_name, std::ostream& out) {
  CH_UNUSED(module_name, out);
  CH_TODO();
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
    out << " // " << iter->second->get_tapName();
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
    out << " // " << tap->get_tapName();        
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
  
  out << "cash-stats: total memories = " << num_memories << std::endl;
  out << "cash-stats: total memory bits = " << memory_bits << std::endl;
  out << "cash-stats: total registers = " << num_registers << std::endl;
  out << "cash-stats: total regiters bits = " << register_bits << std::endl;
  out << "cash-stats: total muxes = " << num_muxes << std::endl;
  out << "cash-stats: total alus = " << num_alus << std::endl;
  out << "cash-stats: total literals = " << num_lits << std::endl;
  out << "cash-stats: total proxies = " << num_proxies << std::endl;
}

///////////////////////////////////////////////////////////////////////////////

context* cash::internal::ctx_create() {
  auto ctx = new context();  
  ctx->acquire();  
  return ctx;
}

void cash::internal::ctx_set(context* ctx) {
  tls_ctx = ctx;
}

context* cash::internal::ctx_curr() {
  CH_CHECK(tls_ctx, "unitialized context!");
  return tls_ctx;
}
