#pragma once

namespace chdl_internal {

class lnode;
class snode;
class lnodeimpl;
class snodeimpl;
class undefimpl;
class litimpl;
class ioimpl;
class inputimpl;
class outputimpl;
class tapimpl;
class assertimpl;
class clock_event;
class cdomain;

class context : public refcounted {
public:
  context();
  ~context();

  //--

  std::list<lnodeimpl*>::iterator erase_node(const std::list<lnodeimpl*>::iterator& iter);

  //--

  void push_clk(lnodeimpl* clk);
  void pop_clk();
  lnodeimpl* get_clk();

  void push_reset(lnodeimpl* reset);
  void pop_reset();
  lnodeimpl* get_reset();

  //--
  
  uint32_t add_node(lnodeimpl* node);  
  void remove_node(undefimpl* node);
  
  void push_cond(lnodeimpl* cond);
  void pop_cond();
  lnodeimpl* resolve(lnodeimpl* dst, lnodeimpl* src);
  
  litimpl* create_literal(const std::initializer_list<uint32_t>& value, uint32_t size);
  litimpl* create_literal(const std::string& value);
  
  cdomain* create_cdomain(const std::vector<clock_event>& sensitivity_list);
  void remove_cdomain(cdomain* cd);
  
  void create_assertion(lnodeimpl* node, const std::string& msg);
  
  //-- 

  lnodeimpl* bind_input(snodeimpl* bus);  
  snodeimpl* bind_output(lnodeimpl* output);
  
  void register_tap(const std::string& name, lnodeimpl* lnode);
  snode get_tap(std::string& name, uint32_t size);
  
  void bind(unsigned index, const snode& node);
  
  //--
  
  void syntax_check();
    
  //--
  
  void get_live_nodes(std::set<lnodeimpl*>& live_nodes);
  
  //--
  
  void tick(ch_cycle t);  
  void tick_next(ch_cycle t);
  void eval(ch_cycle t);
  
  //--
  
  void toVerilog(const std::string& module_name, std::ostream& out);
  
  void dumpAST(std::ostream& out, uint32_t level);
  
protected:
  
  struct cond_t {
    lnodeimpl* cond;
    std::set<lnodeimpl*> locals;
    cond_t(lnodeimpl* cond_) : cond(cond_) {}
  };

  std::list<lnodeimpl*>   m_undefs;
  std::list<lnodeimpl*>   m_nodes;
  std::list<cdomain*>     m_cdomains;
  std::vector<ioimpl*>    m_inputs;
  std::vector<ioimpl*>    m_outputs;
  std::vector<tapimpl*>   m_taps;
  std::list<assertimpl*>  m_gtaps;
  std::list<litimpl*>     m_literals;
  std::list<cond_t>       m_conds;    
  std::stack<lnode>       m_clk_stack;
  std::stack<lnode>       m_reset_stack;

  uint32_t   m_nodeids;
  inputimpl* m_clk;
  inputimpl* m_reset;
  
  std::map<std::string, unsigned> m_dup_taps;
  
  friend class optimizer;
  friend class ch_simulator;
  friend class ch_tracer;
};

context* ctx_begin();
context* ctx_curr();
void ctx_end();

}
