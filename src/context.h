#pragma once

#include "common.h"
#include "platform.h"

namespace ch {
namespace internal {

class bitvector;
class lnode;
class nodelist;
class lnodeimpl;
class undefimpl;
class proxyimpl;
class aluimpl;
class litimpl;
class ioimpl;
class inputimpl;
class outputimpl;
class bindimpl;
class selectimpl;
class tapimpl;
class assertimpl;
class timeimpl;
class cdimpl;
class udf_iface;
class clock_event;

struct cond_block_t;

struct cond_range_t {
  uint32_t offset;
  uint32_t length;

  bool operator==(const cond_range_t& var) const {
    return this->offset == var.offset
        && this->length == var.length;
  }

  bool operator!=(const cond_range_t& var) const {
    return !(*this == var);
  }

  bool operator<(const cond_range_t& var) const {
    if (this->offset != var.offset)
      return (this->offset < var.offset);
    return (this->length < var.length);
  }
};

typedef std::unordered_map<uint32_t, lnodeimpl*> cond_defs_t;

typedef std::map<cond_range_t, cond_defs_t> cond_slices_t;

typedef std::unordered_map<lnodeimpl*, cond_slices_t> cond_vars_t;

typedef std::list<lnodeimpl*> node_list_t;

struct cond_block_t;

struct cond_br_t {
  cond_br_t(lnodeimpl* p_key, cond_block_t* p_parent, const source_location& p_sloc)
    : key(p_key)
    , parent(p_parent)
    , sloc(p_sloc)
  {}

  ~cond_br_t();

  lnodeimpl* key;
  cond_block_t* parent;
  const source_location sloc;
  std::list<cond_block_t*> blocks;
};

struct cond_block_t {
  cond_block_t(uint32_t p_id, lnodeimpl* p_pred, cond_br_t* p_branch)
    : id(p_id)
    , pred(p_pred)
    , branch(p_branch)
  {}

  uint32_t id;
  lnodeimpl* pred;
  cond_br_t* branch;
  std::list<cond_br_t*> branches;
};

inline cond_br_t::~cond_br_t() {
  for (auto block : blocks) {
    delete block;
  }
}

typedef std::unordered_map<uint32_t, cond_block_t*> cond_inits_t;

typedef const char* (*enum_string_cb)(uint32_t value);

typedef std::unordered_map<uint32_t, enum_string_cb> enum_strings_t;

typedef std::stack<std::pair<cdimpl*, lnode>> cd_stack_t;

class context : public refcounted {
public:

  uint32_t id() const {
    return id_;
  }

  const std::string& name() const {
    return name_;
  }

  const auto& nodes() const {
    return nodes_;
  }

  auto& nodes() {
    return nodes_;
  }

  const auto& undefs() const {
    return undefs_;
  }

  const auto& proxies() const {
    return proxies_;
  }

  const auto& inputs() const {
    return inputs_;
  }

  const auto& outputs() const {
    return outputs_;
  }

  const auto& taps() const {
    return taps_;
  }

  const auto& gtaps() const {
    return gtaps_;
  }

  const auto& literals() const {
    return literals_;
  }

  const auto& snodes() const {
    return snodes_;
  }

  auto default_clk() const {
    return default_clk_;
  }

  auto default_reset() const {
    return default_reset_;
  }

  const auto& bindings() const {
    return bindings_;
  }

  const auto& cdomains() const {
    return cdomains_;
  }

  //--

  void push_cd(const lnode& clk,
               const lnode& reset,
               bool posedge,
               const source_location& sloc);

  void pop_cd();

  cdimpl* current_cd(const source_location& sloc);

  lnode current_reset(const source_location& sloc);

  //--

  lnodeimpl* time(const source_location& sloc);

  //--

  uint32_t node_id();

  template <typename T, typename... Ts>
  T* create_node(Ts&&... args) {
    auto node = new T(this, std::forward<Ts>(args)...);
    this->add_node(node);
    return node;
  }

  cdimpl* create_cd(const lnode& clk,
                    bool posedge,
                    const source_location& sloc);

  node_list_t::iterator delete_node(const node_list_t::iterator& it);
  
  //--

  void begin_branch(lnodeimpl* key, const source_location& sloc);

  void end_branch();

  void begin_block(lnodeimpl* pred);

  void end_block();

  bool conditional_enabled(lnodeimpl* node = nullptr) const;

  void conditional_assign(lnodeimpl* dst,
                          uint32_t offset,
                          uint32_t length,
                          lnodeimpl* src,
                          const source_location& sloc);

  lnodeimpl* create_predicate(const source_location& sloc);

  void remove_local_variable(lnodeimpl* src, lnodeimpl* dst);

  //--
  
  lnodeimpl* literal(const bitvector& value);

  //--

  bindimpl* find_binding(context* module, const source_location& sloc);

  //--

  void register_tap(const lnode& lnode,
                    const std::string& name,
                    const source_location& sloc);

  //--
  
  void syntax_check();
    
  //--

  void build_run_list(std::vector<lnodeimpl*>& runlist);

  //--

  lnodeimpl* create_udf_node(udf_iface* udf,
                             const std::initializer_list<lnode>& inputs,
                             const source_location& sloc);

  //--
  
  void dump_ast(std::ostream& out, uint32_t level);

  void dump_cfg(lnodeimpl* node, std::ostream& out, uint32_t level);  

  void dump_stats(std::ostream& out);

  //--

  void register_enum_string(const lnode& node, enum_string_cb callback);

  const char* enum_to_string(const lnode& node);
  
protected:

  context(const std::string& name);

  ~context();

  void add_node(lnodeimpl* node);

  lnodeimpl* emit_conditionals(lnodeimpl* dst,
                               const cond_range_t& range,
                               const cond_defs_t& defs,
                               const cond_br_t* branch);

  uint32_t    id_;
  std::string name_;

  uint32_t    block_idx_;
  inputimpl*  default_clk_;
  inputimpl*  default_reset_;
  timeimpl*   time_;
  
  node_list_t             nodes_;
  std::list<undefimpl*>   undefs_;
  std::list<proxyimpl*>   proxies_;
  std::list<lnodeimpl*>   snodes_;
  std::list<inputimpl*>   inputs_;
  std::list<outputimpl*>  outputs_;  
  std::list<tapimpl*>     taps_;
  std::list<ioimpl*>      gtaps_;
  std::list<litimpl*>     literals_;
  std::list<cdimpl*>      cdomains_;
  std::list<bindimpl*>    bindings_;

  std::stack<cond_br_t*>  cond_branches_;
  cond_vars_t             cond_vars_;
  cond_inits_t            cond_inits_;

  cd_stack_t              cd_stack_;

  unique_names            unique_tap_names_;

  enum_strings_t          enum_strings_;

  friend class context_manager;
};

context* ctx_create(const std::type_index& signature, const std::string& name);

context* ctx_swap(context* ctx);

context* ctx_curr();

}
}
