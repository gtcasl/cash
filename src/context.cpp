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
#include "cdomain.h"
#include "device.h"
#include "context.h"
#include "arithm.h"
#include "select.h"

using namespace std;
using namespace cash::detail;

thread_local context* tls_ctx = nullptr;

context::context()
  : node_ids_(0)
  , block_ids_(0)
  , clk_(nullptr)
  , reset_(nullptr) 
{}

context::~context() {  
  // delete all nodes
  for (auto iter = nodes_.begin(), iterEnd = nodes_.end(); iter != iterEnd;) {
    delete *iter++;
  }
  assert(undefs_.empty());
  assert(proxies_.empty());
  assert(literals_.empty());
  assert(inputs_.empty());
  assert(outputs_.empty());
  assert(taps_.empty());
  assert(gtaps_.empty());
  assert(nullptr == clk_);
  assert(nullptr == reset_);
  assert(cdomains_.empty());
  assert(cond_blocks_.empty());
}

void context::push_clk(lnodeimpl* clk) {
  clk_stack_.emplace(clk);
}

void context::pop_clk() {
  clk_stack_.pop();
}

void context::push_reset(lnodeimpl* reset) {
  reset_stack_.emplace(reset);
}

void context::pop_reset() {
  reset_stack_.pop();
}

lnodeimpl* context::get_clk() {
  if (!clk_stack_.empty())
    return clk_stack_.top().get_impl();
  if (nullptr == clk_)
    clk_ = new inputimpl(op_clk, this, 1);
  return clk_;
}

lnodeimpl* context::get_reset() {
  if (!reset_stack_.empty())
    return reset_stack_.top().get_impl();
  if (nullptr == reset_)
     reset_ = new inputimpl(op_reset, this, 1);
  return reset_;
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
    break;  
  case op_output:
    outputs_.emplace_back((outputimpl*)node);
    break; 
  case op_tap:
    taps_.emplace_back((tapimpl*)node);
    break;
  case op_assert:
  case op_print:
    gtaps_.emplace_back((ioimpl*)node);
    break;
  default:
    break;
  }
  
  // register local nodes
  if (!cond_blocks_.empty()) {
    // memory ports have global scope, skip them
    if (node->get_op() != op_memport) {
      cond_blocks_.front().locals.emplace(node);
    }
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
  default:
    break;
  }
  
  if (node == clk_) {
    clk_ = nullptr;
  } else
  if (node == reset_) {
    reset_ = nullptr;
  }
}

void context::begin_branch() {
  cond_branches_.emplace_front(cond_branch_t());
}

void context::end_branch() {
  assert(!cond_branches_.empty());
  cond_branches_.pop_front();
  if (cond_branches_.empty()) {
    cond_vars_.clear();
    block_ids_ = 0;
  }
}

void context::begin_block(lnodeimpl* cond) {
  lnodeimpl* cond_u = cond;
  cond_branch_t& branch = cond_branches_.front();
  if (nullptr == cond_u) {
    for (auto c : branch.conds) {
      if (cond_u) {
        cond_u = createAluNode(alu_op_or, 1, c, cond_u);
      } else {
        cond_u = c;
      }
    }
    cond_u = createAluNode(alu_op_inv, 1, cond_u);
  }
  branch.conds.emplace_back(cond_u);

  auto parent_iter = cond_blocks_.begin();
  if (parent_iter != cond_blocks_.end()) {
    lnodeimpl* parent_cond = parent_iter->cond;
    if (nullptr == parent_cond) {
      auto parent_branch = std::next(cond_branches_.begin());
      parent_cond = parent_branch->conds.back();
    }
    cond = createAluNode(alu_op_and, 1, parent_cond, cond_u);
  }

  cond_blocks_.emplace_front(block_ids_++, cond);
}

void context::end_block() {
  assert(!cond_blocks_.empty());
  cond_blocks_.pop_front();
}

bool context::conditional_enabled(lnodeimpl* node) const {
  // a node is conditionally assigned if it is not local to the current block
  return (!cond_blocks_.empty()
       && 0 == cond_blocks_.front().locals.count(node));
}

void context::erase_block_local(lnodeimpl* src, lnodeimpl* dst) {
  if (cond_blocks_.empty())
    return;
  cond_block_t& block = cond_blocks_.front();
  if (block.locals.count(src)
   && 0 == block.locals.count(dst)) {
    block.locals.erase(src); // remove from local scope
    if (dst) {
      for (auto& b : cond_blocks_) {
        if (b.locals.count(dst)) {
          b.locals.insert(src);
          return;
        }
      }
    }
  }
}

lnodeimpl* context::resolve_conditional(lnodeimpl* src, lnodeimpl* dst) {
  assert(dst && src);
  // check if node conditionally assigned
  if (!this->conditional_enabled(dst))
    return src;

  // get the current conditional value
  cond_block_t& block = cond_blocks_.front();

  // lookup for last conditional assignment to dst
  auto var_iter = std::find_if(cond_vars_.begin(), cond_vars_.end(),
    [dst](const cond_var_t& v)->bool { return v.updates.front().sel == dst; });
  if (var_iter != cond_vars_.end()) {
    // check if last assignment took place in nested blocks
    auto upd_iter = var_iter->updates.begin();
    if (block.id < upd_iter->block_id) {
      // erase all nested assignments
      auto upd_iterEnd = var_iter->updates.end();
      for (; upd_iter != upd_iterEnd;) {
        if (upd_iter->block_id <= block.id)
          break;
        upd_iter = var_iter->updates.erase(upd_iter);
      }
      // remove variable if no more assignment exist
      if (upd_iter != upd_iterEnd) {
        cond_vars_.erase(var_iter);
        var_iter = cond_vars_.end();
      }
    }
  }

  if (var_iter != cond_vars_.end()) {
    cond_upd_t& last_upd = var_iter->updates.front();
    if (block.id > last_upd.block_id) {
      // last assignment took place in parent or sibling blocks
      if (block.cond) {
        // new conditional assignment
        selectimpl* sel = dynamic_cast<selectimpl*>(
            createSelectNode(block.cond, src, last_upd.sel)
          );
        var_iter->updates.emplace_front(sel, block.id);
      } else {
        // last 'default' assignment
        var_iter->updates.back().sel->set_false(src);
      }
    } else {
      // last assignment happened in current block
      assert(block.id == last_upd.block_id && block.cond);
      last_upd.sel->set_true(src);
    }
    dst = var_iter->updates.front().sel;
  } else {
    // new variable conditional assignment
    lnodeimpl* cond = block.cond;
    if (nullptr == cond) {
      cond_branch_t& branch = cond_branches_.front();
      cond = branch.conds.back();
    }
    selectimpl* sel = dynamic_cast<selectimpl*>(
        createSelectNode(cond, src, dst)
      );
    cond_vars_.emplace_back(sel, block.id);
    dst = sel;
  }

  return dst;
}

lnodeimpl* context::create_literal(const bitvector& value) {
  for (litimpl* lit : literals_) {
    if (lit->get_value() == value) {
      return lit;
    }
  }
  return new litimpl(this, value);
}

cdomain* context::create_cdomain(const std::vector<clock_event>& sensitivity_list) {
  // return existing cdomain 
  for (cdomain* cd : cdomains_) {
    if (*cd == sensitivity_list)
      return cd;
  }  
  // allocate new cdomain
  cdomain* const cd = new cdomain(this, sensitivity_list);
  cdomains_.emplace_back(cd);
  return cd;
}

void context::remove_cdomain(cdomain* cd) {
  cdomains_.remove(cd);
}

lnodeimpl* context::bind_input(snodeimpl* bus) {
  inputimpl* const impl = new inputimpl(this, bus->get_size());
  impl->bind(bus);
  return impl;
}

snodeimpl* context::bind_output(lnodeimpl* output) {
  outputimpl* const impl = new outputimpl(output);
  return impl->get_bus();
}

void context::register_tap(const std::string& name, lnodeimpl* node) {
  // resolve duplicate names
  string full_name(name);
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

void context::get_live_nodes(std::set<lnodeimpl*>& live_nodes) {
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

void context::tick(ch_cycle t) {
  for (auto cd : cdomains_) {
    cd->tick(t);
  }  
}

void context::tick_next(ch_cycle t) {
  for (auto cd : cdomains_) {
    cd->tick_next(t);
  }  
}

void context::eval(ch_cycle t) {
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

static void dump_cfg_impl(lnodeimpl* node, std::ostream& out, uint32_t level, std::vector<bool>& visits, const std::map<uint32_t, tapimpl*>& taps) {
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
  std::map<uint32_t, tapimpl*> taps;
  
  for (tapimpl* tap : taps_) {
    taps[tap->get_target().get_id()] = tap;
  }
  
  visits[node->get_id()] = true;
  
  tapimpl* const tap = dynamic_cast<tapimpl*>(node);
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
    memimpl* mem = dynamic_cast<memimpl*>(node);
    if (mem) {
      ++num_memories;
      memory_bits += mem->get_total_size();      
      continue;
    }
    regimpl* reg = dynamic_cast<regimpl*>(node);
    if (reg) {
      ++num_registers;
      register_bits += reg->get_size();      
      continue;
    }
    selectimpl* sel = dynamic_cast<selectimpl*>(node);
    if (sel) {
      ++num_muxes;
      continue;
    }
    aluimpl* alu = dynamic_cast<aluimpl*>(node);
    if (alu) {
      ++num_alus;
      continue;
    }
    litimpl* lit = dynamic_cast<litimpl*>(node);
    if (lit) {
      ++num_lits;
      continue;
    }
    proxyimpl* proxy = dynamic_cast<proxyimpl*>(node);
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

context* cash::detail::ctx_begin() {
  context* const ctx = new context();
  tls_ctx = ctx;
  ctx->acquire();
  return ctx;
}

void cash::detail::ctx_end() {
  tls_ctx = nullptr;
}

context* cash::detail::ctx_curr() {
  CH_CHECK(tls_ctx, "invalid CASH context!");
  return tls_ctx;
}
