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
class moduleimpl;
class selectimpl;
class tapimpl;
class assertimpl;
class timeimpl;
class udfimpl;
class udfportimpl;
class udf_base;
class udf_obj;
class udf_iface;
class clock_event;
class source_info;
class branchconverter;
class cond_block_t;
class module_base;

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

  auto& btaps() const {
    return btaps_;
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

  auto& ext_nodes() const {
    return ext_nodes_;
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

  auto& modules() const {
    return modules_;
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

  void set_initialized() {
    is_initialized_ = true;
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

  void reset_system_node(lnodeimpl* node);

  //--

  void create_binding(context* ctx, 
                      const std::string& name, 
                      const source_location& sloc);

  inputimpl* create_input(uint32_t size, 
                          const std::string& name,
                          const source_location& sloc);

  outputimpl* create_output(uint32_t size, 
                            const std::string& name,
                            const source_location& sloc);

  outputimpl* get_output(const std::string& name);

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

  void conditional_write(proxyimpl* dst,
                          uint32_t offset,
                          uint32_t length,
                          lnodeimpl* src,
                          const source_location& sloc);

  lnodeimpl* get_predicate(const source_location& sloc);

  //--

  moduleimpl* current_module();

  //--

  void register_tap(const lnode& target, 
                    const std::string& name, 
                    const source_location& sloc);

  lnodeimpl* create_bypass(lnodeimpl* target);

  //--

  void create_udf_node(udf_iface* udf, 
                       bool is_seq, 
                       const std::string& name, 
                       const source_location& sloc);

  udfimpl* current_udf();

  //--
  
  void dump_cfg(std::ostream& out);

  void debug_cfg(lnodeimpl* target, std::ostream& out);

  void dump_stats(std::ostream& out);

  //--

  void register_enum_string(uint32_t id, enum_string_cb callback);

  enum_string_cb enum_to_string(uint32_t id);
  
protected:

  void add_node(lnodeimpl* node);  

  uint32_t     id_;
  std::string  name_;
  context*     parent_;
  bool         is_managed_;
  bool         is_initialized_;

  inputimpl* sys_clk_;
  inputimpl* sys_reset_;
  timeimpl*  sys_time_;
  udfimpl*   curr_udf_;
  branchconverter* branchconv_;

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
  node_list modules_;
  node_list modports_;
  node_list taps_;
  node_list btaps_;
  node_list gtaps_;  
  node_list udfseqs_;
  node_list udfcombs_;
  node_list udfports_;

  node_list_view nodes_;
  node_list_view snodes_;
  node_list_view udfs_;

  enum_strings_t enum_strings_;
  cd_stack_t     cd_stack_;  
  std::list<lnodeimpl*> ext_nodes_;
};

std::pair<context*, bool> ctx_create(const std::type_index& signature,
                                     bool is_pod,
                                     const std::string& name);

context* ctx_swap(context* ctx);

context* ctx_curr();

context* ctx_find(context* ctx);

void destroyUDF(uint32_t id);

}
}
