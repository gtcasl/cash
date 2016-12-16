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
using namespace chdl_internal;

thread_local context* tls_ctx = nullptr;

context::context()
  : m_nodeids(0)
  , m_clk(nullptr)
  , m_reset(nullptr) 
{}

context::~context() {  
  // delete all nodes
  for (auto iter = m_nodes.begin(), iterEnd = m_nodes.end(); iter != iterEnd;) {
    delete *iter++;
  }
  assert(m_undefs.empty());
  assert(m_literals.empty());
  assert(m_inputs.empty());
  assert(m_outputs.empty());
  assert(m_taps.empty());
  assert(m_gtaps.empty());
  assert(m_clk == nullptr);
  assert(m_reset == nullptr);
  assert(m_cdomains.empty());
  assert(m_cond_blocks.empty());
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
    m_clk = new inputimpl(op_clk, this, 1);
  return m_clk;
}

lnodeimpl* context::get_reset() {
  if (!m_reset_stack.empty())
    return m_reset_stack.top().get_impl();
  if (m_reset == nullptr)
     m_reset = new inputimpl(op_reset, this, 1);
  return m_reset;
}

uint32_t context::add_node(lnodeimpl* node) {
  uint32_t nodeid = ++m_nodeids;  
#ifndef NDEBUG
  uint32_t dbg_node = platform::self().get_dbg_node();
  if (dbg_node) {
    if (nodeid == dbg_node) {
      CHDL_ABORT("debugbreak on nodeid %d hit!", nodeid);
    }
  }
#endif
  m_nodes.emplace_back(node);
  
  switch (node->get_op()) {
  case op_undef:
    m_undefs.emplace_back((undefimpl*)node);
    break;
  case op_lit:
    m_literals.emplace_back((litimpl*)node);
    break;
  case op_input:
  case op_clk:
  case op_reset:  
    m_inputs.emplace_back((inputimpl*)node);
    break;  
  case op_output:
    m_outputs.emplace_back((outputimpl*)node);
    break; 
  case op_tap:
    m_taps.emplace_back((tapimpl*)node);
    break;
  case op_assert:
  case op_print:
    m_gtaps.emplace_back((ioimpl*)node);
    break;
  }
  
  if (!m_cond_blocks.empty()
   && !m_cond_blocks.front().cases.empty()) {
    // memory ports have global scope
    if (node->get_op() != op_memport) {
      m_cond_blocks.front().cases.front().locals.emplace(node);
    }
  }
  return nodeid;  
}

void context::remove_node(lnodeimpl* node) {
  DBG(3, "*** deleting node: %s%d(#%d)!\n", node->get_name(), node->get_size(), node->get_id());
  
  assert(!m_nodes.empty());
  m_nodes.remove(node);
  
  switch (node->get_op()) {
  case op_undef:
    m_undefs.remove((undefimpl*)node);
    break;
  case op_lit:
    m_literals.remove((litimpl*)node);
    break;
  case op_input:
  case op_clk:
  case op_reset:  
    m_inputs.remove((inputimpl*)node);
    break;  
  case op_output:
    m_outputs.remove((outputimpl*)node);
    break; 
  case op_tap:
    m_taps.remove((tapimpl*)node);
    break;
  case op_assert:
  case op_print:
    m_gtaps.remove((ioimpl*)node);
    break;
  }
  
  if (node == m_clk) {
    m_clk = nullptr;
  } else
  if (node == m_reset) {
    m_reset = nullptr;
  }
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
  for (uint32_t v : cc.assignments) {
    if (m_cond_vals[v].owner = cc.cond) {
      m_cond_vals[v].owner = nullptr;
    }
  }
}

bool context::conditional_enabled(lnodeimpl* node) const {
  if (m_cond_blocks.empty())
    return false;
  return (node == nullptr) 
      || (0 == m_cond_blocks.front().cases.front().locals.count(node));
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
          for (auto v : iter->assignments) {
            if (m_cond_vals[v].dst == dst) {
              lnodeimpl* true_val = dynamic_cast<selectimpl*>(m_cond_vals[v].sel)->get_true().get_impl();
              proxyimpl* true_proxy = dynamic_cast<proxyimpl*>(true_val);
              if (true_proxy == nullptr || !true_proxy->has_undefs())
                assigned = true;
              break;
            }
          }
          if (!assigned) {
            if (cond) {
              cond = createAluNode(alu_op_or, 1, cond, iter->cond);
            } else {
              cond = iter->cond;
            }
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
  // check if insize conditionall block and the node is not local
  if (!m_cond_blocks.empty()
   && !m_cond_blocks.front().cases.empty()
   && (0 == m_cond_blocks.front().cases.front().locals.count(dst))) {
    // get the current conditional value
    auto iterBlock = m_cond_blocks.begin();
    cond_case_t& cc = iterBlock->cases.front();
    lnodeimpl* const cond = this->get_current_conditional(iterBlock, dst);
    proxyimpl* const proxy = dynamic_cast<proxyimpl*>(src);
    
    // lookup dst value if already defined
    auto iter = std::find_if(m_cond_vals.begin(), m_cond_vals.end(),
      [dst](const cond_val_t& v)->bool { return v.dst == dst; });
    if (iter != m_cond_vals.end()) {
      CHDL_CHECK((proxy && proxy->is_slice()) || iter->owner == nullptr, "redundant assignment to node %s%d(#%d)!\n", dst->get_name(), dst->get_size(), dst->get_id());
      selectimpl* const sel = dynamic_cast<selectimpl*>(iter->sel);
      if (iter->owner) {
        assert(proxy && proxy->is_slice());
        // merge existing select value and make sure their undefined regions point to dst
        lnodeimpl* const true_val = sel->get_true().get_impl();
        proxy->ensureInitialized();
        proxy->replace_undefs(0, true_val, 0, true_val->get_size());
        sel->get_true().reset(src);
      } else {
        if (cond) {
          lnodeimpl* const false_val = sel->get_false().get_impl();
          if (proxy && proxy->is_slice()) {
            // resolve partial proxy object and make sure their undefined regions point to dst                     
            proxy->ensureInitialized();
            proxy->replace_undefs(0, false_val, 0, false_val->get_size());
          }
          src = createSelectNode(cond, src, false_val);
          sel->get_false().reset(src);
        } else {
          sel->get_false().assign(src, true);
        }
        cc.assignments.push_back(iter - m_cond_vals.begin()); // save the index        
        iter->sel = src;              
      }     
      src = dst; // return original value
    } else {
      if (cond) {
        if (dst == nullptr) {
          dst = new undefimpl(this, src->get_size());
          // resolve partial proxy object
          // make sure their undefined regions point to dst           
          if (proxy && proxy->is_slice()) {
            proxy->ensureInitialized();
            proxy->replace_undefs(0, dst, 0, dst->get_size());
          }
          src = createSelectNode(cond, src, dst);                                   
          cc.locals.erase(src); // ensure global scope                       
        } else {             
          src = createSelectNode(cond, src, dst);                         
        } 
        cc.assignments.push_back(m_cond_vals.size());  // save the index       
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
  return new litimpl(this, value);
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
  unsigned instances = m_dup_taps[name]++;
  if (instances > 0) {
    if (instances == 1) {
      // rename first instance
      auto iter = std::find_if(m_taps.begin(), m_taps.end(),
        [name](tapimpl* t)->bool { return t->get_tapName() == name; });
      assert(iter != m_taps.end());
      (*iter)->set_tagName(fstring("%s_%d", name.c_str(), 0));
    }
    full_name = fstring("%s_%d", name.c_str(), instances);
  }
  // create tap node
  new tapimpl(full_name, node);
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

static void dumpCFG_r(lnodeimpl* node, std::ostream& out, uint32_t level, std::vector<bool>& visits, const std::map<uint32_t, tapimpl*>& taps) {
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
  
  for (tapimpl* tap : m_taps) {
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
      dumpCFG_r(src.get_impl(), out, level, visits, taps);
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
  
  for (lnodeimpl* node : m_nodes) {
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
  
  out << "chdl-stats: total memories = " << num_memories << std::endl;
  out << "chdl-stats: total memory bits = " << memory_bits << std::endl;
  out << "chdl-stats: total registers = " << num_registers << std::endl;
  out << "chdl-stats: total regiters bits = " << register_bits << std::endl;
  out << "chdl-stats: total muxes = " << num_muxes << std::endl;
  out << "chdl-stats: total alus = " << num_alus << std::endl;
  out << "chdl-stats: total literals = " << num_lits << std::endl;
  out << "chdl-stats: total proxies = " << num_proxies << std::endl;  
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
