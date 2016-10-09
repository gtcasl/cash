#pragma once

#include "lnode.h"
#include "snode.h"

namespace chdl_internal {

class cdomain;
class ioimpl;
class inputimpl;
class outputimpl;
class tapimpl;
class assertimpl;
class litimpl;
class clock_event;

typedef refcounted_ptr<ioimpl>     ioimpl_ptr;
typedef refcounted_ptr<inputimpl>  inputimpl_ptr;
typedef refcounted_ptr<outputimpl> outputimpl_ptr;
typedef refcounted_ptr<tapimpl>    tapimpl_ptr;
typedef refcounted_ptr<assertimpl> assertimpl_ptr;
typedef refcounted_ptr<litimpl>    litimpl_ptr;

typedef refcounted_ptr<cdomain>    cdomain_ptr;

class context : refcounted {
private:

  std::map<std::string, unsigned> m_dup_taps;

public:
  //--
  std::list<lnodeimpl_ptr> undefs;
  std::list<lnodeimpl_ptr> nodes;
  std::list<cdomain_ptr> cdomains;
  std::stack<lnode> clk_stack;
  std::stack<lnode> reset_stack;
  std::vector<ioimpl_ptr> ioports;
  std::vector<tapimpl_ptr> taps;
  std::list<assertimpl_ptr> gtaps;
  std::list<litimpl_ptr> literals;

  //--
  uint32_t      nodeids;
  inputimpl_ptr g_clk;
  inputimpl_ptr g_reset;

  context();
  ~context();

  //--

  std::list<lnodeimpl*>::iterator erase_node(const std::list<lnodeimpl*>::iterator& iter);

  //--

  void push_clk(const lnode& clk);
  void pop_clk();
  lnode get_clk();

  void push_reset(const lnode& reset);
  void pop_reset();
  lnode get_reset();

  //--

  litimpl* create_literal(const std::initializer_list<uint32_t>& value, uint32_t size);
  litimpl* create_literal(const std::string& value);
  cdomain* create_cdomain(const std::vector<clock_event>& sensitivity_list);
  void create_assertion(const lnode& lnode, const std::string& msg);
  
  //-- 

  void bind_input(unsigned index, const lnode& input, const snode& bus);  
  snode bind_output(unsigned index, const lnode& output);
  void register_tap(const std::string& name, const lnode& lnode);
  
  void bind(unsigned index, const snode& node);
  
  //--
  
  void syntax_check();
    
  //--
  
  void get_live_nodes(std::set<lnodeimpl*>& live_nodes);
  
  //--
  
  void tick(ch_cycle t);  
  void tick_next(ch_cycle t);
  
  //--
  
  void toVerilog(const std::string& module_name, std::ostream& out);
  
  void dumpNodes(std::ostream& out);
};

context_ptr ctx_begin();
context_ptr ctx_curr();
void ctx_end();

}
