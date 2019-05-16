#pragma once

#include "common.h"
#include "platform.h"
#include "traits.h"
#include "nodelistview.h"

namespace ch {
namespace internal {

class lnode;
class node_list;
class lnodeimpl;
class proxyimpl;
class opimpl;
class litimpl;
class cdimpl;
class ioimpl;
class memimpl;
class regimpl;
class ioportimpl;
class inputimpl;
class outputimpl;
class bindimpl;
class selectimpl;
class tapimpl;
class assertimpl;
class timeimpl;
class udfimpl;
class udf_base;
class udf_obj;
class udf_iface;
class clock_event;
class source_location;
struct cond_br_t;
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

typedef std::unordered_map<uint32_t, cond_block_t*> cond_inits_t;

typedef const char* (*enum_string_cb)(uint32_t value);

typedef std::unordered_map<uint32_t, enum_string_cb> enum_strings_t;

typedef std::stack<std::pair<cdimpl*, lnodeimpl*>> cd_stack_t;

class context : public refcounted {
public:

  context(const std::string& name, context* parent = nullptr);

  ~context();

  uint32_t id() const {
    return id_;
  }

  auto& name() const {
    return name_;
  }

  auto parent() const {
    return parent_;
  }

  auto& nodes() const {
    return nodes_;
  }

  auto& nodes() {
    return nodes_;
  }

  auto& proxies() const {
    return proxies_;
  }

  auto& ops() const {
    return ops_;
  }

  auto& sels() const {
    return sels_;
  }

  auto& inputs() const {
    return inputs_;
  }

  auto& outputs() const {
    return outputs_;
  }

  auto& mems() const {
    return mems_;
  }

  auto& taps() const {
    return taps_;
  }

  auto& gtaps() const {
    return gtaps_;
  }

  auto& udfs() const {
    return udfs_;
  }

  auto& literals() const {
    return literals_;
  }

  auto& snodes() const {
    return snodes_;
  }

  auto sys_clk() const {
    return sys_clk_;
  }

  auto sys_reset() const {
    return sys_reset_;
  }

  auto sys_time() const {
    return sys_time_;
  }

  auto& bindings() const {
    return bindings_;
  }

  auto& cdomains() const {
    return cdomains_;
  }

  void set_managed(bool value) {
    is_managed_ = value;
  }

  bool is_managed() const {
    return is_managed_;
  }

  size_t hash() const;

  //--

  uint32_t node_id();

  template <typename T, typename... Args>
  T* create_node(Args&&... args) {
    auto node = new T(this, std::forward<Args>(args)...);
    this->add_node(node);
    return node;
  }

  node_list_view::iterator delete_node(const node_list_view::iterator& it);

  void delete_node(lnodeimpl* node);

  //--

  void create_binding(context* ctx, const source_location& sloc);

  inputimpl* create_input(uint32_t size,
                          const std::string& name,
                          const source_location& sloc);

  outputimpl* create_output(uint32_t size,
                            const std::string& name,
                            const source_location& sloc);

  outputimpl* get_output(const lnode& src);

  //--

  litimpl* create_literal(const sdata_type& value);

  //--

  timeimpl* create_time(const source_location& sloc);

  //--

  lnodeimpl* current_clock(const source_location& sloc);

  lnodeimpl* current_reset(const source_location& sloc);

  cdimpl* current_cd(const source_location& sloc);

  cdimpl* create_cd(const lnode& clk,
                    bool pos_edge,
                    const source_location& sloc);

  void push_cd(const lnode& clk,
               const lnode& reset,
               bool pos_edge,
               const source_location& sloc);

  void pop_cd();

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

  bindimpl* current_binding();

  //--

  void register_tap(const lnode& lnode,
                    const std::string& name,
                    const source_location& sloc);

  //--

  udfimpl* create_udf_node(udf_obj* udf,
                           const std::vector<lnode>& inputs,
                           const source_location& sloc);

  lnodeimpl* create_udf_input(uint32_t size,
                              const std::string& name,
                              const source_location& sloc);

  lnodeimpl* create_udf_output(uint32_t size,
                               const std::string& name,
                               const source_location& sloc);

  //--
  
  void dump_ast(std::ostream& out);

  void dump_cfg(lnodeimpl* target, std::ostream& out);

  void dump_stats(std::ostream& out);

  //--

  void register_enum_string(uint32_t id, enum_string_cb callback);

  enum_string_cb enum_to_string(uint32_t id);

  context* clone() const;
  
protected:

  void add_node(lnodeimpl* node);

  lnodeimpl* emit_conditionals(lnodeimpl* dst,
                               const cond_range_t& range,
                               const cond_defs_t& defs,
                               const cond_br_t* branch);

  uint32_t    id_;
  std::string name_;
  context*    parent_;
  bool        is_managed_;

  inputimpl* sys_clk_;
  inputimpl* sys_reset_;
  timeimpl*  sys_time_;
  
  node_list literals_;
  node_list proxies_;
  node_list inputs_;
  node_list outputs_;
  node_list sels_;
  node_list ops_;
  node_list cdomains_;
  node_list regs_;
  node_list mems_;
  node_list marports_;
  node_list msrports_;
  node_list mwports_;
  node_list bindings_;
  node_list bindports_;
  node_list taps_;
  node_list gtaps_;
  node_list udfseqs_;
  node_list udfcombs_;

  node_list_view nodes_;
  node_list_view snodes_;
  node_list_view udfs_;

  enum_strings_t enum_strings_;

  cd_stack_t              cd_stack_;
  dup_tracker<std::string> dup_tap_names_;
  uint32_t                cond_blk_idx_;
  std::stack<cond_br_t*>  cond_branches_;
  cond_vars_t             cond_vars_;
  cond_inits_t            cond_inits_;  
};

context* ctx_create(const std::type_index& signature,
                    bool has_args,
                    const std::string& name);

context* ctx_swap(context* ctx);

context* ctx_curr();

context* ctx_find(context* ctx);

void destroyUDF(uint32_t id);

}
}
