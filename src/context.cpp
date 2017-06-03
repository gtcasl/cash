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
  : nodeids_(0)
  , clk_(nullptr)
  , reset_(nullptr) 
{}

context::~context() {  
  // delete all nodes
  for (auto iter = nodes_.begin(), iterEnd = nodes_.end(); iter != iterEnd;) {
    delete *iter++;
  }
  assert(undefs_.empty());
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
  uint32_t nodeid = ++nodeids_;  
#ifndef NDEBUG
  uint32_t dbg_node = platform::self().get_dbg_node();
  if (dbg_node) {
    if (nodeid == dbg_node) {
      CH_ABORT("debugbreak on nodeid %d hit!", nodeid);
    }
  }
#endif
  nodes_.emplace_back(node);
  
  switch (node->get_op()) {
  case op_undef:
    undefs_.emplace_back((undefimpl*)node);
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
  
  if (!cond_blocks_.empty()
   && !cond_blocks_.front().cases.empty()) {
    // memory ports have global scope
    if (node->get_op() != op_memport) {
      cond_blocks_.front().cases.front().locals.emplace(node);
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
  cond_blocks_.push_front(cond_block_t());
}

void context::end_branch() {
  assert(!cond_blocks_.empty());
  cond_blocks_.pop_front();
  if (cond_blocks_.empty()) {
    cond_vals_.clear();
  }
}

void context::begin_case(lnodeimpl* cond) {
  assert(!cond_blocks_.empty());
  cond_blocks_.front().cases.emplace_front(cond);
}

void context::end_case() {
  assert(!cond_blocks_.empty() && !cond_blocks_.front().cases.empty());
  const cond_case_t& cc = cond_blocks_.front().cases.front();
  for (uint32_t v : cc.assignments) {
    if (cond_vals_[v].owner == cc.cond) {
      cond_vals_[v].owner = nullptr;
    }
  }
}

bool context::conditional_enabled(lnodeimpl* node) const {
  if (cond_blocks_.empty())
    return false;
  return (nullptr == node)
      || (0 == cond_blocks_.front().cases.front().locals.count(node));
}

lnodeimpl* context::get_current_conditional(const cond_blocks_t::iterator& iterBlock, lnodeimpl* dst) const {
  lnodeimpl* cond = nullptr;
  if (0 == iterBlock->cases.front().locals.count(dst)) {      
    // recursively compute nested conditional value
    lnodeimpl* parent_cond = nullptr;
    auto iterParentBlock = std::next(iterBlock);
    if (iterParentBlock != cond_blocks_.end()) {
      parent_cond = this->get_current_conditional(iterParentBlock, dst);
    }

    auto iterCase = iterBlock->cases.begin();    
    cond = iterCase->cond;        
  
    // check if nested conditional
    if (parent_cond) {
      // check if fallback condition
      if (nullptr == cond) {
        // a default case with parent conditional requires a precise fallback test
        // default condition = !(cond1 & cond2 ... & condN)
        for (auto iter = ++iterCase, iterEnd = iterBlock->cases.end(); iter != iterEnd; ++iter) {
          if (cond) {
            cond = createAluNode(alu_op_or, 1, cond, iter->cond);
          } else {
            cond = iter->cond;
          }
        }  
        if (cond) {
          cond = createAluNode(alu_op_inv, 1, cond);
        }
      }      
      if (cond) {
        cond = createAluNode(alu_op_and, 1, parent_cond, cond);    
      } else {
        cond = parent_cond;
      }
    }
  }
  return cond;
}

lnodeimpl* context::resolve_conditional(lnodeimpl* dst, lnodeimpl* src) {
  // check if inside conditionall block and the node is not local
  if (!cond_blocks_.empty()
   && !cond_blocks_.front().cases.empty()
   && (0 == cond_blocks_.front().cases.front().locals.count(dst))) {
    // get the current conditional value
    auto iterBlock = cond_blocks_.begin();
    cond_case_t& cc = iterBlock->cases.front();
    lnodeimpl* const cond = this->get_current_conditional(iterBlock, dst);    
    // lookup dst value if already defined
    auto iter = std::find_if(cond_vals_.begin(), cond_vals_.end(),
      [dst](const cond_val_t& v)->bool { return v.dst == dst; });
    if (iter != cond_vals_.end()) {
      selectimpl* const sel = dynamic_cast<selectimpl*>(iter->sel);
      if (iter->owner) {
        sel->get_true().set_impl(src);
      } else {
        if (cond) {
          lnodeimpl* const false_val = sel->get_false().get_impl();
          src = createSelectNode(cond, src, false_val);
          sel->get_false().set_impl(src);
        } else {
          sel->get_false().assign(src, true);
        }
        cc.assignments.push_back(iter - cond_vals_.begin()); // save the index        
        iter->sel = src;              
      }     
      src = dst; // return original value
    } else {
      if (cond) {
        if (nullptr == dst) {
          dst = new undefimpl(this, src->get_size());
          src = createSelectNode(cond, src, dst);                                   
          cc.locals.erase(src); // ensure global scope                       
        } else {             
          src = createSelectNode(cond, src, dst);                         
        } 
        cc.assignments.push_back(cond_vals_.size());  // save the index       
        cond_vals_.push_back({src, src, cond});     
      }
    }
  }
  return src;
}

litimpl* context::create_literal(const bitvector& value) {
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
  CH_UNUSED(level);
  for (lnodeimpl* node : nodes_) {
    node->print(out);
    out << std::endl;
  }
}

static void dump_cfg_impl(lnodeimpl* node, std::ostream& out, uint32_t level, std::vector<bool>& visits, const std::map<uint32_t, tapimpl*>& taps) {
  visits[node->get_id()] = true;
  node->print(out);
  
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
  std::vector<bool> visits(nodeids_ + 1);
  std::map<uint32_t, tapimpl*> taps;
  
  for (tapimpl* tap : taps_) {
    taps[tap->get_target().get_id()] = tap;
  }
  
  visits[node->get_id()] = true;
  
  tapimpl* const tap = dynamic_cast<tapimpl*>(node);
  if (tap) {
    node = tap->get_target().get_impl();
    node->print(out);
    out << " // " << tap->get_tapName();        
  } else {  
    node->print(out);
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
