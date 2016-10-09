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
  
  for (lnodeimpl_ptr node : nodes) {
    node->release();
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
  node->release();
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
  bitvector tmp(value, size);
  for (litimpl* lit : literals) {
    if (lit->get_value() == tmp) {
      return lit;
    }
  }
  litimpl* lit = new litimpl(this, tmp);
  literals.emplace_back(lit);
  return lit;
}

litimpl* context::create_literal(const std::string& value) {
  bitvector tmp(value);
  for (litimpl* lit : literals) {
    if (lit->get_value() == tmp) {
      return lit;
    }
  }
  litimpl* lit = new litimpl(this, tmp);
  literals.emplace_back(lit);
  return lit;
}

cdomain* context::create_cdomain(const std::vector<clock_event>& sensitivity_list) {
  // return existing cdomain 
  for (cdomain* cd : cdomains) {
    if (*cd == sensitivity_list) {
      cd->acquire(); // increment reference for reuse
      return cd;
    }
  }  
  // allocate new cdomain
  cdomain* cd = new cdomain(this, sensitivity_list);
  this->cdomains.emplace_back(cd);
  return cd;
}

void context::bind_input(unsigned index, const lnode& input, const snode& bus) {
  inputimpl* impl = new inputimpl("input", index, this, bus.m_impl->get_size());
  impl->bind(bus.m_impl);
  input.assign(impl);
  this->ioports.emplace_back(impl);
}

snode context::bind_output(unsigned index, const lnode& output) {
  outputimpl* impl = new outputimpl("output", index, output);
  this->ioports.emplace_back(impl);
  snodeimpl* bus = new snodeimpl(impl);
  scope_exit gc([&bus]() { bus->release(); }); // call release() on exit
  return snode(bus);
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

void context::syntax_check() {
  // check for un-initialized nodes
  if (this->undefs.size()) {
    this->dumpNodes(cout);    
    for (auto node : undefs) {
      fprintf(stderr, "error: un-initialized node #%d!\n", node->get_id());
    }
    CHDL_ABORT("%zd nodes have not been initialized.", this->undefs.size());
  }
}

void context::get_live_nodes(std::set<lnodeimpl_ptr>& live_nodes) {
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
  TODO("Not yet implemented!");
}

void context::dumpNodes(std::ostream& out) {
  for (lnodeimpl_ptr node :nodes) {
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
