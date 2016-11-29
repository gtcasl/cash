#include <thread>
#include "lnode.h"
#include "litimpl.h"
#include "regimpl.h"
#include "memimpl.h"
#include "ioimpl.h"
#include "snodeimpl.h"
#include "selectimpl.h"
#include "proxyimpl.h"
#include "assertimpl.h"
#include "cdomain.h"
#include "device.h"
#include "context.h"
#include "arithm.h"
#include "select.h"

using namespace std;
using namespace chdl_internal;

thread_local context* tls_ctx = nullptr;

context::context()
  : m_nodeids(0)
  , m_clk(nullptr)
  , m_reset(nullptr) 
{}

context::~context() { 
  //
  // cleanup allocated resources
  //
  
  for (lnodeimpl* node : m_nodes) {
    node->release();
  }

  assert(m_cdomains.empty());
  assert(m_cond_blocks.empty());
}

std::list<lnodeimpl*>::iterator
context::erase_node(const std::list<lnodeimpl*>::iterator& iter) {
  lnodeimpl* const node = *iter;
  if (node == m_clk) {
    m_clk = nullptr;
  } else
  if (node == m_reset) {
    m_reset = nullptr;
  }
  node->release();
  return m_nodes.erase(iter);
}

void context::push_clk(lnodeimpl* clk) {
  m_clk_stack.emplace(clk);
}

void context::pop_clk() {
  m_clk_stack.pop();
}

void context::push_reset(lnodeimpl* reset) {
  m_reset_stack.emplace(reset);
}

void context::pop_reset() {
  m_reset_stack.pop();
}

lnodeimpl* context::get_clk() {
  if (!m_clk_stack.empty())
    return m_clk_stack.top().get_impl();
  if (m_clk == nullptr)
    m_clk = new inputimpl("clk", this, 1);
  return m_clk;
}

lnodeimpl* context::get_reset() {
  if (!m_reset_stack.empty())
    return m_reset_stack.top().get_impl();
  if (m_reset == nullptr)
     m_reset = new inputimpl("reset", this, 1);
  return m_reset;
}

uint32_t context::add_node(lnodeimpl* node) {
  uint32_t nodeid = ++m_nodeids;  
#ifndef NDEBUG
  uint32_t dbg_node = platform::self().get_dbg_node();
  if (dbg_node) {
    CHDL_CHECK(nodeid != dbg_node, "debugbreak on nodeid %d hit!", nodeid);
  }
#endif
  if (node->m_name == "undef") {
    m_undefs.emplace_back(node);
  } else {
    m_nodes.emplace_back(node);
  }  
  node->acquire();
  if (!m_cond_blocks.empty()
   && !m_cond_blocks.front().cases.empty()) {
    // memory ports have global scope
    if (node->get_name() != "memport") {
      m_cond_blocks.front().cases.front().locals.emplace(node);
    }
  }
  return nodeid;  
}

void context::remove_node(undefimpl* node) {
  assert(!m_undefs.empty());
  m_undefs.remove(node);
}

void context::begin_branch() {
  m_cond_blocks.push_front(cond_block_t());
}

void context::end_branch() {
  assert(!m_cond_blocks.empty());
  m_cond_blocks.pop_front();
  if (m_cond_blocks.empty()) {
    m_cond_vals.clear();
  }
}

void context::begin_case(lnodeimpl* cond) {
  assert(!m_cond_blocks.empty());
  m_cond_blocks.front().cases.emplace_front(cond);
}

void context::end_case() {
  assert(!m_cond_blocks.empty() && !m_cond_blocks.front().cases.empty());
  const cond_case_t& cc = m_cond_blocks.front().cases.front();
  for (uint32_t v : cc.defs) {
    if (m_cond_vals[v].owner = cc.cond) {
      m_cond_vals[v].owner = nullptr;
    }
  }
}

lnodeimpl* context::get_current_conditional(const cond_blocks_t::iterator& iterBlock, lnodeimpl* dst) const {
  lnodeimpl* cond = nullptr;
  if (0 == iterBlock->cases.front().locals.count(dst)) {      
    // recursively compute nested conditional value
    lnodeimpl* parent_cond = nullptr;
    auto iterParentBlock = std::next(iterBlock);
    if (iterParentBlock != m_cond_blocks.end()) {
      parent_cond = this->get_current_conditional(iterParentBlock, dst);
    }

    auto iterCase = iterBlock->cases.begin();    
    cond = iterCase->cond;        

    if (parent_cond) {
      if (cond == nullptr) {
        // a default case with parent conditional requires a precise fallback test
        for (auto iter = ++iterCase, iterEnd = iterBlock->cases.end(); iter != iterEnd; ++iter) {
          assert(iter->cond);
          // check if the case already assigned the variable
          bool assigned = false;
          for (auto v : iter->defs) {
            if (m_cond_vals[v].dst == dst) {
              assigned = true;
              break;
            }
          }
          if (!assigned) {
            if (cond) {
              cond = createAluNode(op_or, 1, cond, iter->cond);
            } else {
              cond = iter->cond;
            }
          }
        }  
        if (cond) {
          cond = createAluNode(op_inv, 1, cond);
        }
      }      
      if (cond) {
        cond = createAluNode(op_and, 1, parent_cond, cond);    
      } else {
        cond = parent_cond;
      }
    }
  }
  return cond;
}

lnodeimpl* context::resolve_conditionals(lnodeimpl* dst, lnodeimpl* src) {
  // check if insize conditionall block and the node is not local
  if (!m_cond_blocks.empty()
   && !m_cond_blocks.front().cases.empty()
   && (0 == m_cond_blocks.front().cases.front().locals.count(dst))) {
    // get the current conditional value
    auto iterBlock = m_cond_blocks.begin();
    cond_case_t& cc = iterBlock->cases.front();
    lnodeimpl* const cond = this->get_current_conditional(iterBlock, dst);
 
    // lookup dst value if already defined
    auto iter = std::find_if(m_cond_vals.begin(), m_cond_vals.end(),
      [dst](const cond_val_t& v)->bool { return v.dst == dst; });
    if (iter != m_cond_vals.end()) {
      CHDL_CHECK(iter->owner == nullptr, "redundant assignment to node %s%d(#%d)!\n", dst->get_name().c_str(), dst->get_size(), dst->get_id());   
      if (cond) {
        src = createSelectNode(cond, src, iter->sel);
      }
      dynamic_cast<selectimpl*>(iter->sel)->get_false().assign(src, true);
      iter->sel = src;
      cc.defs.push_back(iter - m_cond_vals.begin()); // save the index
      src = dst; // return original value
    } else {
      if (cond) {
        if (dst == nullptr) {
          dst = new undefimpl(this, src->get_size());
          // resolve partial proxy object
          // make sure their undefined regions point to dst 
          proxyimpl* proxy = dynamic_cast<proxyimpl*>(src);
          if (proxy) {
            proxy->ensureInitialized();
            proxy->update_undefs(0, dst, 0, dst->get_size());
          }
        }
        src = createSelectNode(cond, src, dst);        
        cc.defs.push_back(m_cond_vals.size());
        m_cond_vals.push_back({src, src, cond});      
      }
    }
  }
  return src;
}

litimpl* context::create_literal(const bitvector& value) {
  for (litimpl* lit : m_literals) {
    if (lit->get_value() == value) {
      return lit;
    }
  }
  litimpl* const lit = new litimpl(this, value);
  m_literals.emplace_back(lit);
  return lit;
}

void context::register_gtap(ioimpl* node) {
  m_gtaps.emplace_back(node);  
}

cdomain* context::create_cdomain(const std::vector<clock_event>& sensitivity_list) {
  // return existing cdomain 
  for (cdomain* cd : m_cdomains) {
    if (*cd == sensitivity_list)
      return cd;
  }  
  // allocate new cdomain
  cdomain* const cd = new cdomain(this, sensitivity_list);
  m_cdomains.emplace_back(cd);
  return cd;
}

void context::remove_cdomain(cdomain* cd) {
  m_cdomains.remove(cd);
}

lnodeimpl* context::bind_input(snodeimpl* bus) {
  inputimpl* const impl = new inputimpl("input", this, bus->get_size());
  impl->bind(bus);
  m_inputs.emplace_back(impl);
  return impl;
}

snodeimpl* context::bind_output(lnodeimpl* output) {
  outputimpl* const impl = new outputimpl("output", output);
  m_outputs.emplace_back(impl);
  return impl->get_bus();
}

void context::register_tap(const std::string& name, lnodeimpl* node) {
  // resolve duplicate names
  string full_name(name);
  unsigned instances = m_dup_taps[name]++;
  if (instances > 0) {
    if (instances == 1) {
      // rename first instance
      auto iter = std::find_if(m_taps.begin(), m_taps.end(),
        [name](tapimpl* t)->bool { return t->get_tapName() == name; });
      assert(iter != m_taps.end());
      (*iter)->m_name = fstring("%s_%d", name.c_str(), 0);
    }
    full_name = fstring("%s_%d", name.c_str(), instances);
  }
  // add to list
  m_taps.emplace_back(new tapimpl(full_name, node));
}

snodeimpl* context::get_tap(const std::string& name, uint32_t size) {
  for (tapimpl* tap : m_taps) {
    if (tap->get_tapName() == name) {
      CHDL_CHECK(tap->get_size() == size, "tap bus size mismatch: received %u, expected %u", size, tap->get_size());
      return tap->get_bus();
    }
  } 
  CHDL_ABORT("couldn't find tab '%s'", name.c_str());
}

void context::syntax_check() {
  // check for un-initialized nodes
  if (m_undefs.size()) {
    this->dumpAST(std::cerr, 1);    
    for (auto node : m_undefs) {
      fprintf(stderr, "error: un-initialized node %s%d(#%d)!\n", node->get_name().c_str(), node->get_size(), node->get_id());
    }
    if (m_undefs.size() == 1)
      CHDL_ABORT("1 node has not been initialized.");
    else
      CHDL_ABORT("%zd nodes have not been initialized.", m_undefs.size());
  }
}

void context::get_live_nodes(std::set<lnodeimpl*>& live_nodes) {
  // get inputs
  for (auto node : m_inputs) {
    live_nodes.emplace(node);
  }

  // get outputs
  for (auto node : m_outputs) {
    live_nodes.emplace(node);
  }  
  
  // get debug taps
  for (auto node : m_taps) {
    live_nodes.emplace(node);
  }

  // get assert taps
  for (auto node : m_gtaps) {
    live_nodes.emplace(node);
  }
}

void context::tick(ch_cycle t) {
  for (auto cd : m_cdomains) {
    cd->tick(t);
  }  
}

void context::tick_next(ch_cycle t) {
  for (auto cd : m_cdomains) {
    cd->tick_next(t);
  }  
}

void context::eval(ch_cycle t) {
  // evaluate outputs
  for (auto node : m_outputs) {
    node->eval(t);
  }

  // evaluate taps
  for (auto node : m_taps) {
    node->eval(t);
  }  
  
  // evaluate asserts
  for (auto node : m_gtaps) {
    node->eval(t);
  }
}

void context::toVerilog(const std::string& module_name, std::ostream& out) {
  TODO("Not yet implemented!");
}

void context::dumpAST(std::ostream& out, uint32_t level) {
  for (lnodeimpl* node : m_nodes) {
    node->print(out);
    out << std::endl;
  }
}

static void dumpCFG_r(lnodeimpl* node, std::ostream& out, uint32_t level, std::vector<bool>& visits, std::map<uint32_t, tapimpl*>& taps) {
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
      dumpCFG_r(src.get_impl(), out, level, visits, taps);
    }
  }  
}

void context::dumpCFG(lnodeimpl* node, std::ostream& out, uint32_t level) {
  std::vector<bool> visits(m_nodeids + 1);
  std::map<uint32_t, tapimpl*> taps;
  
  for (auto node : m_taps) {
    taps[node->get_target().get_id()] = node;
  }
  
  visits[node->get_id()] = true;
  
  tapimpl* tap = dynamic_cast<tapimpl*>(node);
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
      dumpCFG_r(src.get_impl(), out, level, visits, taps);
    }
  }
}

///////////////////////////////////////////////////////////////////////////////

context* chdl_internal::ctx_begin() {
  context* const ctx = new context();
  tls_ctx = ctx;
  ctx->acquire();
  return ctx;
}

void chdl_internal::ctx_end() {
  tls_ctx = nullptr;
}

context* chdl_internal::ctx_curr() {
  CHDL_CHECK(tls_ctx, "invalid CHDL context!");
  return tls_ctx;
}
