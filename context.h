#pragma once

#include "common.h"

namespace chdl_internal {

class ch_node;
class nodeimpl;
class memimpl;
class cdomain;
class ioimpl;
class inputimpl;
class outputimpl;
class tapimpl;
class assertimpl;
class litimpl;
class busimpl;
class clock_event;

class context {
private:

  std::map<std::string, unsigned> m_dup_taps;

public:
  //--
  std::list<nodeimpl*> undefs;
  std::list<nodeimpl*> nodes;
  std::list<cdomain*> cdomains;
  std::stack<ch_node> clk_stack;
  std::stack<ch_node> reset_stack;
  std::vector<ioimpl*> ioports;
  std::vector<tapimpl*> taps;
  std::list<assertimpl*> gtaps;

  //--
  uint64_t nodeids;
  inputimpl* g_clk;
  inputimpl* g_reset;

  context();
  ~context();

  //--

  std::list<nodeimpl*>::iterator erase_node(const std::list<nodeimpl*>::iterator& iter);

  //--

  void push_clk(const ch_node& clk);
  void pop_clk();
  ch_node get_clk();

  void push_reset(const ch_node& reset);
  void pop_reset();
  ch_node get_reset();

  //--

  cdomain* create_cdomain(const std::vector<clock_event>& sensitivity_list);
  void create_assertion(const ch_node& ch_node, const std::string& msg);
  
  //-- 

  void register_io(unsigned index, ch_node& node);
  void register_tap(const std::string& name, const ch_node& ch_node);
  
  void bind(unsigned index, busimpl* bus);
  
  //--
  
  void syntax_check();
    
  //--
  
  void get_live_nodes(std::set<nodeimpl*>& live_nodes);
  
  //--
  
  void tick(ch_cycle t);  
  void tick_next(ch_cycle t);
  
  //--
  
  void toVerilog(const std::string& module_name, std::ostream& out);
  
  void print(std::ostream& out);
};

context* ctx_enter();
context* ctx_curr();
void ctx_exit();

}
