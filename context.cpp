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
  : nodeids(0)
  , g_clk(nullptr)
  , g_reset(nullptr)
{}

context::~context() { 
  //
  // cleanup allocated resources
  //
  
  for (lnodeimpl* node : nodes) {
    delete node;
  }

  assert(cdomains.empty());
}

std::list<lnodeimpl*>::iterator
context::erase_node(const std::list<lnodeimpl*>::iterator& iter) {
  lnodeimpl* node = *iter;
  if (node == g_clk) {
    g_clk = nullptr;
  } else
  if (node == g_reset) {
    g_reset = nullptr;
  }
  delete node;
  return nodes.erase(iter);
}

void context::push_clk(const lnode& clk) {
  clk_stack.push(clk);
}

void context::pop_clk() {
  clk_stack.pop();
}

void context::push_reset(const lnode& reset) {
  reset_stack.push(reset);
}

void context::pop_reset() {
  reset_stack.pop();
}

lnode context::get_clk() {
  if (!clk_stack.empty())
    return clk_stack.top();
  if (g_clk == nullptr)
    g_clk = new inputimpl("clk", -1, this, 1);
  return lnode(g_clk);
}

lnode context::get_reset() {
  if (!reset_stack.empty())
    return reset_stack.top();
  if (g_reset == nullptr)
     g_reset = new inputimpl("reset", -1, this, 1);
  return lnode(g_reset);
}


litimpl* context::create_literal(const std::initializer_list<uint32_t>& value, uint32_t size) {
  for (litimpl* lit : literals) {
    if (lit->get_size() == size 
     && lit->get_value() == value) {
      return lit;
    }
  }
  litimpl* lit = new litimpl(this, size, value);
  literals.emplace_back(lit);
  return lit;
}

cdomain* context::create_cdomain(const std::vector<clock_event>& sensitivity_list) {
  // return existing cdomain 
  for (cdomain* cd : cdomains) {
    if (*cd == sensitivity_list) {
      cd->add_ref(); // increment reference for reuse
      return cd;
    }
  }  
  // allocate new cdomain
  cdomain* cd = new cdomain(this, sensitivity_list);
  this->cdomains.emplace_back(cd);
  return cd;
}

void context::register_input(unsigned index, const lnode& node) {
  ioimpl* impl = new inputimpl("input", index, this, node.get_size());
  node.assign(impl);
  ioports.emplace_back(impl);
}

void context::register_output(unsigned index, const lnode& node) {
  ioports.emplace_back(new outputimpl("output", index, node));
}

void context::register_tap(const std::string& name, const lnode& node) {
  // resolve duplicate names
  string full_name(name);
  unsigned instances = m_dup_taps[name]++;
  if (instances > 0) {
    if (instances == 1) {
      // rename first instance
      auto iter = std::find_if(taps.begin(), taps.end(),
        [name](tapimpl* t)->bool { return t->get_tapName() == name; });
      assert(iter != taps.end());
      (*iter)->m_name = fstring("%s_%d", name.c_str(), 0);
    }
    full_name = fstring("%s_%d", name.c_str(), instances);
  }
  // add to list
  taps.emplace_back(new tapimpl(full_name, node));
}

void context::bind(unsigned index, const snode& node) {
  snodeimpl* bus = node.m_impl;
  ioimpl* ioport = ioports[index];
  unsigned n = bus->get_size();
  if (n != ioport->get_size())
    CHDL_ABORT("bind argument %d size mismatch! (expected=%d != actual=%d)", index, ioport->get_size(), n);
  iobridge* bridge;
  if (dynamic_cast<inputimpl*>(ioport)) {
    bridge = new ibridge(bus);
  } else {
    bridge = new obridge(ioport);      
  }
  bus->bind(this, index, bridge);
  ioport->bind(bridge);    
  bridge->release();
}

void context::syntax_check() {
  // check for unitilaized nodes
  for (auto node : nodes) {
    if (dynamic_cast<undefimpl*>(node)) {
      CHDL_ABORT("undefined node #%ld!", node->get_id());
    }
  }
}

void context::get_live_nodes(std::set<lnodeimpl*>& live_nodes) {
  // get io ports
  for (lnodeimpl* node : ioports) {
    live_nodes.emplace(node);
  }  
  
  // get debug taps
  for (lnodeimpl* node : taps) {
    live_nodes.emplace(node);
  }

  // get assert taps
  for (lnodeimpl* node : gtaps) {
    live_nodes.emplace(node);
  }
}

void context::tick(ch_cycle t) {
  for (auto cd : cdomains) {
    cd->tick(t);
  }  
}

void context::tick_next(ch_cycle t) {
  for (auto cd : cdomains) {
    cd->tick_next(t);
  }  
}

void context::toVerilog(const std::string& module_name, std::ostream& out) {
  TODO();
}

void context::dumpNodes(std::ostream& out) {
  for (lnodeimpl* node :nodes) {
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
  if (!tls_ctx)
    CHDL_ABORT("invalid CHDL context!");
  return tls_ctx;
}
