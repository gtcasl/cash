#include <thread>
#include "node.h"
#include "litimpl.h"
#include "regimpl.h"
#include "memimpl.h"
#include "ioimpl.h"
#include "busimpl.h"
#include "assertimpl.h"
#include "cdomain.h"
#include "device.h"
#include "context.h"

using namespace std;
using namespace chdl_internal;

thread_local context* tls_ctx = nullptr;

context::context()
  : nodeids(0)
  , undefcount(0)
  , g_clk(nullptr)
  , g_reset(nullptr)
{}

context::~context() { 
  //
  // cleanup allocated resources
  //

  for (auto assertion : assertions) {
    delete assertion;
  }
  
  for (auto node : nodes) {
    delete node;
  }

  assert(cdomains.empty());
}

std::list<nodeimpl*>::iterator
context::erase_node(const std::list<nodeimpl*>::iterator& iter) {
  nodeimpl* node = *iter;
  if (node == g_clk) {
    g_clk = nullptr;
  } else
  if (node == g_reset) {
    g_reset = nullptr;
  }
  delete node;
  return nodes.erase(iter);
}

void context::push_clk(const ch_node& clk) {
  clk_stack.push(clk);
}

void context::pop_clk() {
  clk_stack.pop();
}

void context::push_reset(const ch_node& reset) {
  reset_stack.push(reset);
}

void context::pop_reset() {
  reset_stack.pop();
}

ch_node context::get_clk() {
  if (!clk_stack.empty())
    return clk_stack.top();
  if (g_clk == nullptr)
    g_clk = new inputimpl(this, 1, "clk");
  return ch_node(g_clk);
}

ch_node context::get_reset() {
  if (!reset_stack.empty())
    return reset_stack.top();
  if (g_reset == nullptr)
     g_reset = new inputimpl(this, 1, "reset");
  return ch_node(g_reset);
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

void context::create_assertion(const ch_node& node, const std::string& msg) {
  node.ensureInitialized(this, 1);
  assertions.emplace_back(new assertion(this, node, msg));
}

void context::register_io(unsigned index, ch_node& node) {
  ioimpl* impl;
  string name(fstring("arg%d", index));
  if (node.m_impl == nullptr
   || dynamic_cast<undefimpl*>(node.m_impl)) {
    impl = new inputimpl(this, node.get_size(), name);
    node.assign(impl, true);
  } else {
    impl = new outputimpl(node, name);
  }  
  // add to list
  ioports.emplace_back(impl);
}

void context::register_tap(const std::string& name, const ch_node& node) {
  // resolve duplicate names
  string full_name(name);
  unsigned instances = m_dup_taps[name]++;
  if (instances > 0) {
    if (instances == 1) {
      // rename first instance
      auto iter = std::find_if(taps.begin(), taps.end(),
        [name](outputimpl* p)->bool { return p->get_name() == name; });
      assert(iter != taps.end());
      (*iter)->m_name = fstring("%s_%d", name.c_str(), 0);
    }
    full_name = fstring("%s_%d", name.c_str(), instances);
  }
  // add to list
  taps.emplace_back(new outputimpl(node, full_name));
}

void context::bind(unsigned index, busimpl* bus) {
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

void context::get_live_nodes(std::set<nodeimpl*>& live_nodes) {
  // get io ports
  for (auto node : ioports) {
    live_nodes.emplace(node);
  }  
  
  // get debug taps
  for (auto node : taps) {
    live_nodes.emplace(node);
  }

  // get assert taps
  for (auto node : gtaps) {
    live_nodes.emplace(node);
  }
}

void context::tick(ch_cycle t) {
  for (auto a : assertions) {
    a->eval(t);
  }
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

///////////////////////////////////////////////////////////////////////////////

context* chdl_internal::ctx_enter() {
  context* ctx = new context();
  tls_ctx = ctx;
  return ctx;
}

void chdl_internal::ctx_exit() {
  tls_ctx = nullptr;
}

context* chdl_internal::ctx_curr() {
  if (!tls_ctx)
    CHDL_ABORT("invalid CHDL context!");
  return tls_ctx;
}
