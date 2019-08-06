#include "context.h"
#include "brconv.h"
#include "litimpl.h"
#include "regimpl.h"
#include "memimpl.h"
#include "ioimpl.h"
#include "bindimpl.h"
#include "selectimpl.h"
#include "proxyimpl.h"
#include "memimpl.h"
#include "opimpl.h"
#include "timeimpl.h"
#include "assertimpl.h"
#include "cdimpl.h"
#include "udfimpl.h"
#include "ioport.h"
#include "traits.h"
#include "select.h"
#include "enum.h"
#include "udf.h"
#include "debug.h"

using namespace ch::internal;

class context_manager {
public:
  context_manager() : curr_ctx_(nullptr), ctx_ids_(0), node_ids_(0) {}

  ~context_manager() {
    assert(curr_ctx_ == nullptr);
    assert(pod_ctx_map_.empty());
  }

  std::pair<context*, uint32_t> create_context(const std::type_index& signature,
                                               bool is_pod,
                                               const std::string& name) {
    context* ctx;
    if (is_pod) {
      auto it = pod_ctx_map_.find(signature);
      if (it != pod_ctx_map_.end()) {
        auto ctx = it->second.first;
        auto instance = ++it->second.second;
        return std::make_pair(ctx, instance);
      }
    }

    auto unique_name = name;
    auto instance = dup_ctx_names_.insert(unique_name);
    if (instance) {
       unique_name = stringf("%s_%ld", unique_name.c_str(), instance);
    }

    ctx = new context(unique_name, curr_ctx_);
    if (is_pod) {
      ctx->set_managed(true);
      pod_ctx_map_.emplace(signature, std::pair<context*, uint32_t>{ctx, 0});
    }

    return std::make_pair(ctx, 0);
  }

  void destroy_context(uint32_t id) {
    for (auto it = pod_ctx_map_.begin(), end = pod_ctx_map_.end(); it != end; ++it) {
      if (it->second.first->id() == id) {
        pod_ctx_map_.erase(it);
        break;
      }
    }
  }

  context* current() const {
    CH_CHECK(curr_ctx_ != nullptr, "invalid context!");
    return curr_ctx_;
  }

  context* swap(context* ctx) {
    std::swap(curr_ctx_, ctx);
    return ctx;
  }

  static context_manager& instance(){
    static context_manager inst;
    return inst;
  }

  uint32_t ctx_id() const {
    return ++ctx_ids_;
  }

  uint32_t node_id() const {
    return ++node_ids_;
  }

protected:

  std::unordered_map<std::type_index, std::pair<context*, uint32_t>> pod_ctx_map_;
  dup_tracker<std::string> dup_ctx_names_;
  mutable context* curr_ctx_;
  mutable uint32_t ctx_ids_;
  mutable uint32_t node_ids_;
};

///////////////////////////////////////////////////////////////////////////////

std::pair<context*, bool> ch::internal::ctx_create(const std::type_index& signature,
                                                   bool is_pod,
                                                   const std::string& name) {
  return context_manager::instance().create_context(signature, is_pod, name);
}

context* ch::internal::ctx_swap(context* ctx) {
  return context_manager::instance().swap(ctx);
}

context* ch::internal::ctx_curr() {
  return context_manager::instance().current();
}

///////////////////////////////////////////////////////////////////////////////

context::context(const std::string& name, context* parent)
  : id_(context_manager::instance().ctx_id())
  , name_(name)
  , parent_(parent)
  , is_managed_(false)
  , is_initialized_(nullptr == parent)
  , sys_clk_(nullptr)
  , sys_reset_(nullptr)
  , sys_time_(nullptr)
  , curr_udf_(nullptr)
  , branchconv_(nullptr)
  , nodes_(&mems_, &marports_, &msrports_, &mwports_, &regs_,
           &proxies_, &sels_, &ops_,
           &inputs_, &outputs_, &cdomains_, &bindings_, &bindports_,
           &udfseqs_, &udfcombs_, &udfports_, &gtaps_, &btaps_, &taps_, &literals_)
  , snodes_(&regs_, &msrports_, &mwports_, &udfseqs_)
  , udfs_(&udfcombs_, &udfseqs_) {
  branchconv_ = new branchconverter(this);
}

context::~context() {
  // delete allocated nodes
  for (auto it = nodes_.begin(), end = nodes_.end(); it != end;) {
    auto node = *it++;
    node->release();
  }
  if (is_managed_) {
    context_manager::instance().destroy_context(id_);
  }
  if (branchconv_) {
    delete branchconv_;
  }
}

uint32_t context::node_id() {
  auto nodeid = context_manager::instance().node_id();
#ifndef NDEBUG
  uint32_t dbg_nodeid = platform::self().dbg_node();
  if (dbg_nodeid) {
    if (nodeid == dbg_nodeid) {
      CH_ABORT("debugbreak on nodeid %d hit!", nodeid);
    }
  }
#endif
  return nodeid;
}

void context::add_node(lnodeimpl* node) {
  //--
  node->acquire();

  //--
  auto type = node->type();
  switch (type) {
  default:
    assert(false);
  case type_lit:
    literals_.push_back(node);
    break;
  case type_proxy:
    proxies_.push_back(node);
    if (!is_initialized_) {
      ext_nodes_.push_back(node);
    }
    break;
  case type_input:
    inputs_.push_back(node);
    break;
  case type_output:
    outputs_.push_back(node);
    break;
  case type_sel:
    sels_.push_back(node);
    break;
  case type_op:
    ops_.push_back(node);
    break;
  case type_cd:
    cdomains_.push_back(node);
    break;
  case type_reg:
    regs_.push_back(node);
    break;
  case type_mem:
    mems_.push_back(node);
    break;
  case type_marport:
    marports_.push_back(node);
    break;
  case type_msrport:
    msrports_.push_back(node);
    break;
  case type_mwport:
    mwports_.push_back(node);
    break;
  case type_bind:
    bindings_.push_back(node);
    break;
  case type_bindin:
  case type_bindout:
    bindports_.push_back(node);
    break;
  case type_tap:
    taps_.push_back(node);
    break;
  case type_bypass:
    btaps_.push_back(node);
    break;
  case type_assert:
  case type_print:
  case type_time:
    gtaps_.push_back(node);
    break;
  case type_udfc:
    udfcombs_.push_back(node);
    break;
  case type_udfs:
    udfseqs_.push_back(node);
    break;
  case type_udfin:
  case type_udfout:
    udfports_.push_back(node);
    break;
  }

  // register local nodes, io objects & literals have global scope
  if (branchconv_->enabled()
   && nullptr == dynamic_cast<ioimpl*>(node)
   && nullptr == dynamic_cast<litimpl*>(node)) {
    branchconv_->add_definition(node);
  }
}

void context::delete_node(lnodeimpl* node) {
  CH_DBG(3, "*** deleting node: %s%d(#%d)\n", to_string(node->type()), node->size(), node->id());

  // clear system node
  this->reset_system_node(node);

  // remove from list
  auto type = node->type();
  switch (type) {
  default:
    assert(false);
  case type_lit:
    literals_.remove(node);
    break;
  case type_proxy:
    proxies_.remove(node);
    ext_nodes_.remove(node);
    break;
  case type_input:
    inputs_.remove(node);
    break;
  case type_output:
    outputs_.remove(node);
    break;
  case type_sel:
    sels_.remove(node);
    break;
  case type_op:
    ops_.remove(node);
    break;
  case type_cd:
    cdomains_.remove(node);
    break;
  case type_reg:
    regs_.remove(node);
    break;
  case type_mem:
    mems_.remove(node);
    break;
  case type_marport:
    marports_.remove(node);
    break;
  case type_msrport:
    msrports_.remove(node);
    break;
  case type_mwport:
    mwports_.remove(node);
    break;
  case type_bind:
    bindings_.remove(node);
    break;
  case type_bindin:
  case type_bindout:
    bindports_.remove(node);
    break;
  case type_tap:
    taps_.remove(node);
    break;
  case type_bypass:
    btaps_.remove(node);
    break;
  case type_time:
  case type_assert:
  case type_print:
    gtaps_.remove(node);
    break;
  case type_udfc:
    udfcombs_.remove(node);
    break;
  case type_udfs:
    udfseqs_.remove(node);
    break;
  case type_udfin:
  case type_udfout:
    udfports_.remove(node);
    break;
  }

  // destroy object
  node->release();
}

node_list_view::iterator context::delete_node(const node_list_view::iterator& it) {
  auto node = *it;
  CH_DBG(3, "*** deleting node: %s%d(#%d)\n", to_string(node->type()), node->size(), node->id());

  // clear system node
  this->reset_system_node(node);

  // remove node from list
  auto next = nodes_.erase(it);

  // destroy object
  node->release();

  return next;
}

void context::reset_system_node(lnodeimpl* node) {
  switch (node->type()) {
  case type_input:
    if (node == sys_clk_) {
      sys_clk_ = nullptr;
    } else
    if (node == sys_reset_) {
      sys_reset_ = nullptr;
    }
    break;
  case type_time:
    if (node == sys_time_) {
      sys_time_ = nullptr;
    }
    break;
  default:
    break;
  }
}

void context::create_binding(context* ctx, const source_location& sloc) {
  this->create_node<bindimpl>(ctx, sloc);
}

inputimpl* context::create_input(uint32_t size,
                                 const std::string& name,
                                 const source_location& sloc) {
  for (auto node : inputs_) {
    auto input = reinterpret_cast<inputimpl*>(node);
    if (input->name() == name) {
      return input;
    }
  }
  auto value = smart_ptr<sdata_type>::make(size);
  return this->create_node<inputimpl>(size, value, name, sloc);
}

outputimpl* context::get_output(const std::string& name) {
  for (auto node : outputs_) {
    auto output = reinterpret_cast<outputimpl*>(node);
    if (output->name() == name) {
      return output;
    }
  }
  return nullptr;
}

outputimpl* context::create_output(uint32_t size,
                                   const std::string& name,
                                   const source_location& sloc) {
  auto output = this->get_output(name);
  if (output)
    return output;
  auto src = this->create_node<proxyimpl>(size, name, sloc);
  auto value = smart_ptr<sdata_type>::make(size);
  return this->create_node<outputimpl>(size, src, value, name, sloc);
}

litimpl* context::create_literal(const sdata_type& value) {
  // first lookup literals cache
  for (auto node : literals_) {
    auto lit = reinterpret_cast<litimpl*>(node);
    if (lit->value() == value)
      return lit;
  }
  // create new literal
  return this->create_node<litimpl>(value);
}

timeimpl* context::create_time(const source_location& sloc) {
  if (nullptr == sys_time_) {
    sys_time_ = this->create_node<timeimpl>(sloc);
  }
  return sys_time_;
}

cdimpl* context::create_cd(const lnode& clk,
                           bool pos_edge,
                           const source_location& sloc) {
  // return existing match
  for (auto node : cdomains_) {
    auto cd = reinterpret_cast<cdimpl*>(node);
    if (cd->clk() == clk && cd->pos_edge() == pos_edge)
      return cd;
  }
  // allocate new cdomain
  return this->create_node<cdimpl>(clk.impl(), pos_edge, sloc);
}

void context::push_cd(const lnode& clk,
                      const lnode& reset,
                      bool pos_edge,
                      const source_location& sloc) {
  auto cd = this->create_cd(clk, pos_edge, sloc);
  cd_stack_.emplace(cd, reset.impl());
}

void context::pop_cd() {
  cd_stack_.pop();
}

cdimpl* context::current_cd(const source_location& sloc) {
  if (!cd_stack_.empty())
    return cd_stack_.top().first;

  if (nullptr == sys_clk_) {
    auto value = smart_ptr<sdata_type>::make(1);
    sys_clk_ = this->create_node<inputimpl>(1, value, "clk", sloc);
  }
  return this->create_cd(sys_clk_, true, sloc);
}

lnodeimpl* context::current_clock(const source_location& sloc) {
  return this->current_cd(sloc)->clk().impl();
}

lnodeimpl* context::current_reset(const source_location& sloc) {
  if (!cd_stack_.empty())
    return cd_stack_.top().second;

  if (nullptr == sys_reset_) {
    auto value = smart_ptr<sdata_type>::make(1);
    sys_reset_ = this->create_node<inputimpl>(1, value, "reset", sloc);
  }
  return sys_reset_;
}

void context::begin_branch(lnodeimpl* key, const source_location& sloc) {
  branchconv_->begin_branch(key, sloc);
}

void context::end_branch() {
  branchconv_->end_branch();
}

void context::begin_block(lnodeimpl* pred) {
  branchconv_->begin_block(pred);
}

void context::end_block() {
  branchconv_->end_block();
}

bool context::conditional_enabled(lnodeimpl* node) const {
  if (!branchconv_->enabled())
    return false;
  if (node) {
    return branchconv_->is_local(node);
  }
  return true;
}

void context::conditional_write(
    proxyimpl* dst,
    uint32_t offset,
    uint32_t length,
    lnodeimpl* src,
    const source_location& sloc) {
  return branchconv_->write(dst, offset, length, src, sloc);
}

lnodeimpl* context::create_predicate(const source_location& sloc) {
  return branchconv_->create_predicate(sloc);
}

bindimpl* context::current_binding() {
  return reinterpret_cast<bindimpl*>(bindings_.back());
}

void context::register_tap(const lnode& target,
                           const std::string& name,
                           const source_location& sloc) {
  auto sid = identifier_from_string(name);
  auto num_dups = dup_tap_names_.insert(sid);
  if (num_dups) {
    sid = stringf("%s%ld", sid.c_str(), num_dups);
  } else {
    sid = stringf("%s", sid.c_str());
  }
  this->create_node<tapimpl>(target.impl(), sid, sloc);
}

lnodeimpl* context::create_bypass(lnodeimpl* target) {
  assert(target->ctx() != this);
  for (auto node : btaps_) {
    auto bypass = reinterpret_cast<bypassimpl*>(node);
    if (bypass->target() == target)
      return bypass;
  }
  return this->create_node<bypassimpl>(target);
}

void context::create_udf_node(udf_iface* udf,
                              bool is_seq,
                              const std::string& name,
                              const source_location& sloc) {
  if (is_seq) {
    auto cd = this->current_cd(sloc);
    auto reset = this->current_reset(sloc);
    curr_udf_ = this->create_node<udfsimpl>(udf, cd, reset, name, sloc);
  } else {
    curr_udf_ = this->create_node<udfcimpl>(udf, name, sloc);
  }
}

udfimpl* context::current_udf() {
  return curr_udf_;
}

void context::register_enum_string(uint32_t id, enum_string_cb callback) {
  enum_strings_[id] = callback;
}

enum_string_cb context::enum_to_string(uint32_t id) {
  auto iter = enum_strings_.find(id);
  if (iter == enum_strings_.end())
    return nullptr;
  return iter->second;
}

void context::dump_ast(std::ostream& out) {
  for (auto node : nodes_) {
    node->print(out);
    out << std::endl;
  }
  std::cout << "total nodes: " << nodes_.size() << std::endl;
}

void context::dump_cfg(lnodeimpl* target, std::ostream& out) {
  std::unordered_set<uint32_t> visited_nodes;
  std::unordered_map<uint32_t, tapimpl*> taps;

  std::function<void(lnodeimpl*)> dfs_visit = [&](lnodeimpl* node) {
    visited_nodes.insert(node->id());
    node->print(out);

    auto iter = taps.find(node->id());
    if (iter != taps.end()) {
      out << " // " << iter->second->name();
      out << std::endl;
      return;
    }
    out << std::endl;

    for (auto& src : node->srcs()) {
      if (!visited_nodes.count(src.id())) {
        dfs_visit(src.impl());
      }
    }
  };

  for (auto node : taps_) {
    auto tap = reinterpret_cast<tapimpl*>(node);
    taps[tap->target().id()] = tap;
  }

  visited_nodes.insert(target->id());

  if (type_tap == target->type()) {
    auto tap = reinterpret_cast<tapimpl*>(target);
    target = tap->target().impl();
    target->print(out);
    out << " // " << tap->name();
  } else {
    target->print(out);
  }

  out << std::endl;

  for (auto& src : target->srcs()) {
    if (!visited_nodes.count(src.id())) {
      dfs_visit(src.impl());
    }
  }
}

void context::dump_stats(std::ostream& out) {
  uint64_t num_inputs = 0;
  uint64_t num_outputs = 0;
  uint64_t num_registers = 0;
  uint64_t num_memories = 0;
  uint64_t num_literals = 0;
  uint64_t num_ops = 0;
  uint64_t num_muxes = 0;
  uint64_t num_proxies = 0;
  uint64_t num_other = 0;

  uint64_t inputs_bits = 0;
  uint64_t outputs_bits = 0;
  uint64_t registers_bits = 0;
  uint64_t memories_bits = 0;
  uint64_t literals_bits = 0;
  uint64_t ops_bits = 0;
  uint64_t muxes_bits = 0;
  uint64_t proxies_bits = 0;
  uint64_t other_bits = 0;

  std::function<void(context*)> calc_stats = [&](context* ctx) {
    for (lnodeimpl* node : ctx->nodes()) {
      switch (node->type()) {
      case type_input:
        if (nullptr == ctx->parent()) {
          inputs_bits += node->size();
          ++num_inputs;
        }
        break;
      case type_output:
        if (nullptr == ctx->parent()) {
          outputs_bits += node->size();
          ++num_outputs;
        }
        break;
      case type_reg:
        registers_bits += node->size();
        ++num_registers;
        break;
      case type_mem:
        memories_bits += node->size();
        ++num_memories;
        break;
      case type_lit:
        literals_bits += node->size();
        ++num_literals;
        break;
      case type_op:
        ops_bits += node->size();
        ++num_ops;
        break;
      case type_sel:
        muxes_bits += node->size();
        ++num_muxes;        
        break;
      case type_proxy:
        proxies_bits += node->size();
        ++num_proxies;
        break;
      case type_bind:
        calc_stats(reinterpret_cast<bindimpl*>(node)->module());
        break;
      default:
        other_bits += node->size();
        ++num_other;
        break;
      }
    }
  };

  calc_stats(this);

  auto num_nodes = num_inputs + num_outputs + num_registers + num_memories
                 + num_literals + num_ops + num_muxes + num_proxies + num_other;

  auto nodes_bits = inputs_bits + outputs_bits + registers_bits + memories_bits
                  + literals_bits + ops_bits + muxes_bits + proxies_bits + other_bits;

  out << "ch-stats: total nodes = " << num_nodes << " (" << nodes_bits << " bits)" << std::endl;
  out << "ch-stats: total inputs = " << num_inputs << " (" << inputs_bits << " bits, " << ((inputs_bits * 100)/nodes_bits) << "%)" << std::endl;
  out << "ch-stats: total outputs = " << num_outputs << " (" << outputs_bits << " bits, " << ((outputs_bits * 100)/nodes_bits) << "%)" << std::endl;
  out << "ch-stats: total registers = " << num_registers << " (" << registers_bits << " bits, " << ((registers_bits * 100)/nodes_bits) << "%)" << std::endl;
  out << "ch-stats: total memories = " << num_memories << " (" << memories_bits << " bits, " << ((memories_bits * 100)/nodes_bits) << "%)" << std::endl;
  out << "ch-stats: total literals = " << num_literals << " (" << literals_bits << " bits, " << ((literals_bits * 100)/nodes_bits) << "%)" << std::endl;
  out << "ch-stats: total ops = " << num_ops << " (" << ops_bits << " bits, " << ((ops_bits * 100)/nodes_bits) << "%)" << std::endl;
  out << "ch-stats: total muxes = " << num_muxes << " (" << muxes_bits << " bits, " << ((muxes_bits * 100)/nodes_bits) << "%)" << std::endl;
  out << "ch-stats: total proxies = " << num_proxies << " (" << proxies_bits << " bits, " << ((proxies_bits * 100)/nodes_bits) << "%)" << std::endl;
  out << "ch-stats: total other = " << num_other << " (" << other_bits << " bits, " << ((other_bits * 100)/nodes_bits) << "%)" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////

void ch::internal::registerTap(const lnode& node, const std::string& name) {
  auto sloc = get_source_location();
  ctx_curr()->register_tap(node, name, sloc);
}

void ch::internal::registerEnumString(const lnode& node, void* callback) {
  ctx_curr()->register_enum_string(node.id(), (enum_string_cb)callback);
}
