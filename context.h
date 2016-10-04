#pragma once

#include "common.h"

namespace chdl_internal {

class lnode;
class snode;
class lnodeimpl;
class snodeimpl;
class memimpl;
class cdomain;
class ioimpl;
class inputimpl;
class outputimpl;
class tapimpl;
class assertimpl;
class litimpl;
class clock_event;

class context {
private:

  std::map<std::string, unsigned> m_dup_taps;

public:
  //--
  std::list<lnodeimpl*> undefs;
  std::list<lnodeimpl*> nodes;
  std::list<cdomain*> cdomains;
  std::stack<lnode> clk_stack;
  std::stack<lnode> reset_stack;
  std::vector<ioimpl*> ioports;
  std::vector<tapimpl*> taps;
  std::list<assertimpl*> gtaps;
  std::list<litimpl*> literals;

  //--
  uint64_t nodeids;
  inputimpl* g_clk;
  inputimpl* g_reset;

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
  cdomain* create_cdomain(const std::vector<clock_event>& sensitivity_list);
  void create_assertion(const lnode& lnode, const std::string& msg);
  
  //-- 

  void register_input(unsigned index, const lnode& node);
  void register_output(unsigned index, const lnode& node);
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

context* ctx_begin();
context* ctx_curr();
void ctx_end();

}
