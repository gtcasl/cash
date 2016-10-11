#include <thread>
#include "lnode.h"
#include "litimpl.h"
#include "regimpl.h"
#include "memimpl.h"
#include "ioimpl.h"
#include "snodeimpl.h"
#include "assertimpl.h"
#include "cdomain.h"
#include "device.h"
#include "context.h"

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
}

std::list<lnodeimpl*>::iterator
context::erase_node(const std::list<lnodeimpl*>::iterator& iter) {
  lnodeimpl* node = *iter;
  if (node == m_clk) {
    m_clk = nullptr;
  } else
  if (node == m_reset) {
    m_reset = nullptr;
  }
  node->release();
  return m_nodes.erase(iter);
}

void context::push_clk(const lnode& clk) {
  m_clk_stack.push(clk);
}

void context::pop_clk() {
  m_clk_stack.pop();
}

void context::push_reset(const lnode& reset) {
  m_reset_stack.push(reset);
}

void context::pop_reset() {
  m_reset_stack.pop();
}

lnode context::get_clk() {
  if (!m_clk_stack.empty())
    return m_clk_stack.top();
  if (m_clk == nullptr)
    m_clk = new inputimpl("clk", this, 1);
  return lnode(m_clk);
}

lnode context::get_reset() {
  if (!m_reset_stack.empty())
    return m_reset_stack.top();
  if (m_reset == nullptr)
     m_reset = new inputimpl("reset", this, 1);
  return lnode(m_reset);
}

uint32_t context::add_node(lnodeimpl* node) {
  if (node->m_name == "undef") {
    m_undefs.emplace_back(node);
  } else {
    m_nodes.emplace_back(node);
  }  
  node->acquire();
  return ++m_nodeids;
}

void context::remove_node(undefimpl* node) {
  assert(m_undefs.size() > 0);
  m_undefs.remove(node);
}

litimpl* context::create_literal(const std::initializer_list<uint32_t>& value, uint32_t size) {
  bitvector tmp(value, size);
  for (litimpl* lit : m_literals) {
    if (lit->get_value() == tmp) {
      return lit;
    }
  }
  litimpl* lit = new litimpl(this, tmp);
  m_literals.emplace_back(lit);
  return lit;
}

litimpl* context::create_literal(const std::string& value) {
  bitvector tmp(value);
  for (litimpl* lit : m_literals) {
    if (lit->get_value() == tmp) {
      return lit;
    }
  }
  litimpl* lit = new litimpl(this, tmp);
  m_literals.emplace_back(lit);
  return lit;
}

void context::create_assertion(const lnode& node, const std::string& msg) {
  m_gtaps.emplace_back(new assertimpl(node, msg));  
}

cdomain* context::create_cdomain(const std::vector<clock_event>& sensitivity_list) {
  // return existing cdomain 
  for (cdomain* cd : m_cdomains) {
    if (*cd == sensitivity_list)
      return cd;
  }  
  // allocate new cdomain
  cdomain* cd = new cdomain(this, sensitivity_list);
  m_cdomains.emplace_back(cd);
  return cd;
}

void context::remove_cdomain(cdomain* cd) {
  m_cdomains.remove(cd);
}

void context::bind_input(const lnode& input, const snode& bus) {
  inputimpl* impl = new inputimpl("input", this, bus.m_impl->get_size());
  impl->bind(bus.m_impl);
  input.assign(impl);
  m_inputs.emplace_back(impl);
}

snode context::bind_output(const lnode& output) {
  outputimpl* impl = new outputimpl("output", output);
  m_outputs.emplace_back(impl);
  return snode(impl->get_bus());
}

void context::register_tap(const std::string& name, const lnode& node) {
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

snode context::get_tap(std::string& name, uint32_t size) {
  for (tapimpl* tap : m_taps) {
    if (tap->get_tapName() == name) {
      CHDL_REQUIRED(tap->get_size() == size, "tap bus size mismatch: received %u, expected %u", size, tap->get_size());
      return snode(tap->get_bus());
    }
  } 
  CHDL_ABORT("couldn't find tab '%s'", name.c_str());
}

void context::syntax_check() {
  // check for un-initialized nodes
  if (m_undefs.size()) {
    this->dumpNodes(cout);    
    for (auto node : m_undefs) {
      fprintf(stderr, "error: un-initialized node #%d!\n", node->get_id());
    }
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

void context::dumpNodes(std::ostream& out) {
  for (lnodeimpl* node : m_nodes) {
    node->print(out);
  }
}

///////////////////////////////////////////////////////////////////////////////

context* chdl_internal::ctx_begin() {
  context* ctx = new context();
  tls_ctx = ctx;
  return ctx;
}

void chdl_internal::ctx_end() {
  tls_ctx = nullptr;
}

context* chdl_internal::ctx_curr() {
  CHDL_REQUIRED(tls_ctx, "invalid CHDL context!");
  return tls_ctx;
}
