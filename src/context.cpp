#include "context.h"
#include <thread>
#include "lnode.h"
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
#include "ioport.h"
#include "traits.h"
#include "select.h"
#include "enum.h"
#include "udf.h"
#include "udfimpl.h"

#ifdef CALLTRACE
#include "slocmgr.h"
#endif

using namespace ch::internal;

class context_manager {
public:
  context_manager() : ctx_(nullptr), ctx_ids_(0), node_ids_(0) {}

  ~context_manager() {
    assert(ctx_ == nullptr);
    assert(pod_contexts_.empty());
    assert(pod_udfs_.empty());
  }

  context* create_context(const std::type_index& signature,
                          bool has_args,
                          const std::string& name) {
    context* ctx;
    if (!has_args) {
      auto it = ctx_signatures_.find(signature);
      if (it != ctx_signatures_.end()) {
        auto it2 = pod_contexts_.find(it->second);
        if (it2 != pod_contexts_.end()) {
          return it2->second;
        }
        ctx_signatures_.erase(it);
      }
    }
    auto unique_name = name;
    auto instances = dup_ctx_names_.insert(unique_name);
    if (instances) {
       unique_name = stringf("%s_%ld", unique_name.c_str(), instances);
    }
    ctx = new context(unique_name, ctx_);
    if (!has_args) {
      pod_contexts_.emplace(ctx->id(), ctx);
      [[maybe_unused]] auto status = ctx_signatures_.emplace(signature, ctx->id());
      assert(status.second);
      ctx->set_managed(true);
    }
    return ctx;
  }

  void destroy_context(uint32_t id) {
    auto it = pod_contexts_.find(id);
    assert(it != pod_contexts_.end());
    pod_contexts_.erase(it);
  }

  context* current() const {
    CH_CHECK(ctx_ != nullptr, "invalid context!");
    return ctx_;
  }

  context* swap(context* ctx) {
    std::swap(ctx_, ctx);
    return ctx;
  }

  udf_iface* lookup_udf(const std::type_index& signature, bool has_args) {
    udf_iface* udf = nullptr;
    if (!has_args) {
      auto it = udf_signatures_.find(signature);
      if (it != udf_signatures_.end()) {
        auto it2 = pod_udfs_.find(it->second);
        if (it2 != pod_udfs_.end()) {
          return it2->second;
        }
        udf_signatures_.erase(it);
      }
    }
    return udf;
  }

  udf_iface* create_udf(const std::type_index& signature,
                        bool has_args,
                        const std::string& name,
                        bool is_seq,
                        uint32_t output_size,
                        const std::initializer_list<uint32_t>& inputs_size,
                        udf_base* udf) {
    uint32_t id = this->udf_id();
    auto iface = new udf_iface(id, name, is_seq, output_size, inputs_size, udf);
    if (!has_args) {
      pod_udfs_.emplace(id, iface);
      [[maybe_unused]] auto status = udf_signatures_.emplace(signature, id);
      assert(status.second);
      iface->set_managed(true);
    }
    return iface;
  }

  void destroy_udf(uint32_t id) {
    auto it = pod_udfs_.find(id);
    assert(it != pod_udfs_.end());
    pod_udfs_.erase(it);
  }

#ifdef CALLTRACE
  bool register_source_location(uint32_t level) {
    return src_loc_manager_.register_source_location(level+1);
  }
  void release_source_location() {
    src_loc_manager_.release_source_location();
  }
  const source_location& get_source_location() {
    return src_loc_manager_.get_source_location();
  }
#endif

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

  uint32_t udf_id() const {
    return ++udf_ids_;
  }

protected:

  mutable context* ctx_;
  mutable uint32_t ctx_ids_;
  mutable uint32_t node_ids_;  
  mutable uint32_t udf_ids_;
  std::unordered_map<std::type_index, uint32_t> ctx_signatures_;
  std::unordered_map<uint32_t, context*> pod_contexts_;
  dup_tracker<std::string> dup_ctx_names_;
  std::unordered_map<std::type_index, uint32_t> udf_signatures_;
  std::unordered_map<uint32_t, udf_iface*> pod_udfs_;
  sloc_manager src_loc_manager_;
};

context* ch::internal::ctx_create(const std::type_index& signature,
                                  bool has_args,
                                  const std::string& name) {
  return context_manager::instance().create_context(signature, has_args, name);
}

context* ch::internal::ctx_swap(context* ctx) {
  return context_manager::instance().swap(ctx);
}

context* ch::internal::ctx_curr() {
  return context_manager::instance().current();
}

refcounted* ch::internal::lookupUDF(const std::type_index& signature, bool has_args) {
  return context_manager::instance().lookup_udf(signature, has_args);
}

refcounted* ch::internal::createUDF(const std::type_index& signature,
                                    bool has_args,
                                    const std::string& name,
                                    bool is_seq,
                                    uint32_t output_size,
                                    const std::initializer_list<uint32_t>& inputs_size,
                                    udf_base* udf) {
  return context_manager::instance().create_udf(
        signature, has_args, name, is_seq, output_size, inputs_size, udf);
}

void ch::internal::destroyUDF(uint32_t id) {
  context_manager::instance().destroy_udf(id);
}

bool ch::internal::register_source_location(uint32_t level) {
#ifdef CALLTRACE
  return context_manager::instance().register_source_location(level+1);
#else
  CH_UNUSED(level);
  return false;
#endif
}

void ch::internal::release_source_location() {
#ifdef CALLTRACE
  context_manager::instance().release_source_location();
#endif
}

source_location ch::internal::get_source_location() {
#ifdef CALLTRACE
  return context_manager::instance().get_source_location();
#else
  return source_location();
#endif
}

///////////////////////////////////////////////////////////////////////////////

namespace ch::internal {

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

struct cond_br_t {
  cond_br_t(lnodeimpl* p_key, cond_block_t* p_parent, const source_location& p_sloc)
    : key(p_key)
    , parent(p_parent)
    , sloc(p_sloc)
  {}

  ~cond_br_t() {
    for (auto block : blocks) {
      delete block;
    }
  }

  lnodeimpl* key;
  cond_block_t* parent;
  const source_location sloc;
  std::list<cond_block_t*> blocks;
};

}

///////////////////////////////////////////////////////////////////////////////

context::context(const std::string& name, context* parent)
  : id_(context_manager::instance().ctx_id())
  , name_(name)
  , parent_(parent)
  , is_managed_(false)
  , sys_clk_(nullptr)
  , sys_reset_(nullptr)
  , sys_time_(nullptr)
  , nodes_(&literals_, &proxies_, &inputs_, &outputs_, &alus_,
           &cdomains_, &regs_, &mems_, &marports_, &msrports_, &mwports_,
           &bindings_, &bindports_, &taps_, &gtaps_, &udfseqs_, &udfcombs_)
  , snodes_(&regs_, &msrports_, &mwports_, &udfseqs_)
  , udfs_(&udfcombs_, &udfseqs_)
  , cond_blk_idx_(0)    
{}

context::~context() {
  // delete allocated nodes
  for (auto it = nodes_.begin(), end = nodes_.end(); it != end;) {
    auto node = *it++;
    node->release();
  }
  if (is_managed_) {
    context_manager::instance().destroy_context(id_);
  }
}

context* context::clone() const {
  clone_map cloned_nodes;
  auto ctx = new context(name_, parent_);
  for (auto node : nodes_) {
    node->clone(ctx, cloned_nodes);
  }
  return ctx;
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
  case type_lit:
    literals_.push_back(node);
    break;
  case type_proxy:
    proxies_.push_back(node);
    break;
  case type_input:
    inputs_.push_back(node);
    break;
  case type_output:
    outputs_.push_back(node);
    break;
  case type_op:
  case type_sel:
    alus_.push_back(node);
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
  default:
    assert(false);
  }

  // register local nodes, io objects & literals have global scope
  if (!cond_branches_.empty()
   && nullptr == dynamic_cast<ioimpl*>(node)
   && nullptr == dynamic_cast<litimpl*>(node)) {
    auto curr_branch = cond_branches_.top();
    auto curr_block = curr_branch->blocks.back();
    cond_inits_[node->id()] = curr_block;
  }  
}

void context::delete_node(lnodeimpl* node) {
  CH_DBG(3, "*** deleting node: %s%d(#%d)\n", to_string(node->type()), node->size(), node->id());

  // remove from list
  auto type = node->type();
  switch (type) {
  case type_lit:
    literals_.remove(node);
    break;
  case type_proxy:
    proxies_.remove(node);
    break;
  case type_input:
    if (node == sys_clk_) {
      sys_clk_ = nullptr;
    } else
    if (node == sys_reset_) {
      sys_reset_ = nullptr;
    }
    inputs_.remove(node);
    break;
  case type_output:
    outputs_.remove(node);
    break;
  case type_op:
  case type_sel:
    alus_.remove(node);
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
  case type_time:
    if (node == sys_time_) {
      sys_time_ = nullptr;
    }
    [[fallthrough]];
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
  default:
    assert(false);
  }

  // destroy object
  node->release();
}

node_list_view::iterator context::delete_node(const node_list_view::iterator& it) {
  auto node = *it;
  CH_DBG(3, "*** deleting node: %s%d(#%d)\n", to_string(node->type()), node->size(), node->id());
  
  auto type = node->type();
  switch (type) {
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

  // remove node from list
  auto next = nodes_.erase(it);

  // destroy object
  node->release();

  return next;
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

outputimpl* context::create_output(uint32_t size,
                                   const std::string& name,
                                   const source_location& sloc) {
  for (auto node : outputs_) {
    auto output = reinterpret_cast<outputimpl*>(node);
    if (output->name() == name) {
      return output;
    }
  }
  auto src = this->create_node<proxyimpl>(size, sloc, name);
  auto value = smart_ptr<sdata_type>::make(size);
  return this->create_node<outputimpl>(src, value, name, sloc);
}

outputimpl* context::get_output(const lnode& src) {
  for (auto node : outputs_) {
    auto output = reinterpret_cast<outputimpl*>(node);
    if (output->src(0).id() == src.id()) {
      return output;
    }
  }
  std::abort();
  return nullptr;
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
  // create new conditional branch
  // add to current block and push on the stack
  cond_br_t* new_branch;
  if (!cond_branches_.empty()) {
    auto curr_branch = cond_branches_.top();
    auto curr_block = curr_branch->blocks.back();
    new_branch = new cond_br_t(key, curr_block, sloc);
    curr_block->branches.push_back(new_branch);
  } else {
    new_branch = new cond_br_t(key, nullptr, sloc);
  }
  cond_branches_.push(new_branch);
}

void context::end_branch() {
  // branch delete visitor
  std::function<void(cond_br_t*)> delete_branch = [&](cond_br_t* branch) {
    for (auto bk : branch->blocks) {
      for (auto br : bk->branches) {
        delete_branch(br);
      }
    }
    delete branch;
  };

  // remove current conditional branch from stack
  // process top parent branch on exit
  assert(!cond_branches_.empty());
  auto curr_branch = cond_branches_.top();
  cond_branches_.pop();
  if (cond_branches_.empty()) {
    // emit conditional statements
    for (auto& var : cond_vars_) {      
      auto dst = var.first;
      assert(type_proxy == dst->type());
      for (auto& slice : var.second) {
        auto value  = this->emit_conditionals(dst, slice.first, slice.second, curr_branch);
        reinterpret_cast<proxyimpl*>(dst)->add_source(slice.first.offset, value, 0, slice.first.length);
      }
    }
    // cleanup
    delete_branch(curr_branch);
    cond_vars_.clear();
    cond_inits_.clear();
    cond_blk_idx_ = 0;
  }
}

void context::begin_block(lnodeimpl* pred) {
  // insert new conditional block  
  auto curr_branch = cond_branches_.top();
  auto new_block = new cond_block_t(++cond_blk_idx_, pred, curr_branch);
  curr_branch->blocks.push_back(new_block);
}

void context::end_block() {
  //--
}

void context::remove_local_variable(lnodeimpl* src, lnodeimpl* dst) {
  // remove from source init block
  auto it = cond_inits_.find(src->id());
  if (it != cond_inits_.end()) {
    cond_inits_.erase(it);
    if (dst) {
      // add to destination's init block
      auto it = cond_inits_.find(dst->id());
      if (it != cond_inits_.end()) {
        cond_inits_[src->id()] = it->second;
      }
    }
  }
}

bool context::conditional_enabled(lnodeimpl* node) const {
  // a node is conditionally assigned if it is not local to the current block
  if (cond_branches_.empty())
    return false;
  if (node) {
    auto it = cond_inits_.find(node->id());
    if (it != cond_inits_.end()) {
      auto curr_branch = cond_branches_.top();
      auto curr_block  = curr_branch->blocks.back();
      if (it->second == curr_block)
        return false;
    }
  }
  return true;
}

void context::conditional_assign(
    lnodeimpl* dst,
    uint32_t offset,
    uint32_t length,
    lnodeimpl* src,
    const source_location& sloc) {
  assert(this->conditional_enabled(dst));
  auto& slices     = cond_vars_[dst];
  auto curr_branch = cond_branches_.top();
  auto curr_block  = curr_branch->blocks.back();

  //--
  auto add_definition = [&](cond_slices_t& slices,
                            const cond_range_t& range,
                            uint32_t loc,
                            lnodeimpl* src,
                            uint32_t src_offset) {
    if (src->size() != range.length) {
      src = this->create_node<proxyimpl>(src, src_offset, range.length, sloc, "slice");
    }
    slices[range][loc] = src;
  };

  {
    //--
    cond_slices_t split_list;

    //--
    auto create_split_definitions = [&](const cond_range_t& range,
                                     uint32_t offset,
                                     uint32_t length) {
      cond_range_t new_range{offset, length};
      for (auto def : slices[range]) {
        add_definition(split_list, new_range, def.first, def.second, offset - range.offset);
      }
    };

    // create split list for partially overlapping definitions
    for (auto it = slices.begin(), end = slices.end(); it != end;) {
      auto& curr  = it->first;
      uint32_t curr_end = curr.offset + curr.length;
      uint32_t var_end  = offset + length;

      // does variable overlap existing definition?
      if (offset < curr_end && var_end > curr.offset) {
        if (offset <= curr.offset && var_end >= curr_end) {
          // variable fully overlaps current
          ++it;
          continue;
        } else if (offset < curr.offset) {
          // variable overlaps on the left
          create_split_definitions(curr, curr.offset, var_end - curr.offset);
          create_split_definitions(curr, var_end, curr_end - var_end);
        } else if (var_end > curr_end) {
          // variable overlaps on the right
          create_split_definitions(curr, curr.offset, offset - curr.offset);
          create_split_definitions(curr, offset, curr_end - offset);
        } else {
          // variable fully included
          if (offset != curr.offset) {
            create_split_definitions(curr, curr.offset, offset - curr.offset);
          }
          create_split_definitions(curr, offset, var_end - offset);
          if (var_end != curr_end) {
            create_split_definitions(curr, var_end, curr_end - var_end);
          }
        }
        // remove entry
        it = slices.erase(it);
      } else {
        ++it;
      }
    }

    // insert split entries
    if (!split_list.empty()) {
      for (auto& item : split_list) {
        slices[item.first] = item.second;
      }
    }
  }

  //--
  std::function<void (cond_defs_t&, const cond_block_t*)>
      delete_definitions = [&](cond_defs_t& defs, const cond_block_t* block) {
    // delete definition in current block
    auto it = defs.find(block->id);
    if (it != defs.end()) {
      defs.erase(it);
    }
    if(defs.empty())
      return;
    // recurse delete definitions in nested blocks
    for (auto branch : block->branches) {
      for (auto block : branch->blocks) {
        delete_definitions(defs, block);
      }
    }
  };

  //--
  uint32_t var_offset = offset;

  //--
  auto add_new_definition = [&](uint32_t offset, uint32_t length) {
    cond_range_t new_range{offset, length};

    // delete all existing definitions within current block
    delete_definitions(slices[new_range], curr_block);

    // add new definition
    add_definition(slices, new_range, curr_block->id, src, offset - var_offset);
  };

  // add new definitions to current block
  for (auto it = slices.begin(), end = slices.end();
       length != 0 && it != end; ++it) {
    auto& curr = it->first;
    uint32_t curr_end = curr.offset + curr.length;
    uint32_t var_end  = offset + length;

    // does variable overlap existing definition?
    if (offset < curr_end && var_end > curr.offset) {
      if (offset == curr.offset
       && var_end == curr_end) {
        // variable strictly overlaps current definition
        add_new_definition(offset, length);
        length = 0; // no need to continue
      } else if (offset < curr.offset) {
        // variable overlaps current definition on the left
        add_new_definition(offset, curr.offset - offset);
        add_new_definition(curr.offset, curr.length);
        uint32_t delta = (curr.offset - offset) + curr.length;
        offset += delta;
        length -= delta;
      } else if (var_end > curr_end) {
        // variable overlaps current definition on the right
        add_new_definition(curr.offset, curr.length);
        offset += curr.length;
        length -= curr.length;
      } else {
        // splitting should have eliminated this case
        assert(false);
      }
    } else if (std::next(it) == end
            || var_end <= curr.offset) {
      // no overlap with current and next
      add_new_definition(offset, length);
      length = 0; // no need to continue
    } else {
      // definitions no not overlap
      continue;
    }
  }

  if (length != 0) {
    add_new_definition(offset, length);
  }
}

lnodeimpl*
context::emit_conditionals(lnodeimpl* dst,
                           const cond_range_t& range,
                           const cond_defs_t& defs,
                           const cond_br_t* branch) {
  //--
  std::function<lnodeimpl*(const cond_br_t* branch,
                           lnodeimpl* current)> emit_conditional_branch;

  //--
  typedef std::list<std::pair<lnodeimpl*, lnodeimpl*>> branch_info_t;

  //--
  auto branch_optimizer = [&](lnodeimpl* key, branch_info_t& values)->lnodeimpl* {
    // ensure default value exist
    assert(nullptr == values.back().first && values.back().second);

    {
      // skip paths with value equal to default value
      auto df_value = values.back().second;
      lnodeimpl* skip_pred = nullptr;
      for (auto it = values.begin(), end = values.end(); it != end;) {
        if (it->first && it->second == df_value) {
          if (nullptr == key) {
            if (skip_pred) {
              skip_pred = this->create_node<opimpl>(ch_op::orb, 1, false, skip_pred, it->first, branch->sloc);
            } else {
              skip_pred = it->first;
            }
          }
          it = values.erase(it);
        } else {
          if (skip_pred && it->first) {
            auto not_skip_pred = this->create_node<opimpl>(ch_op::inv, 1, false, skip_pred, branch->sloc);
            it->first = this->create_node<opimpl>(ch_op::andb, 1, false, it->first, not_skip_pred, branch->sloc);
          }
          ++it;
        }
      }
    }

    // return single assignment as default value
    if (1 ==  values.size()) {
      assert(nullptr == values.front().first);
      return values.front().second;
    }

    // coallesce cascading ternary branches sharing the same default value
    // p2 ? (p1 ? t1 : f1) : f1 => (p1 & p2) ? t1 : f1;
    if (2 == values.size()) {
      auto _true = dynamic_cast<selectimpl*>(values.front().second);
      if (_true) {
        uint32_t num_srcs = _true->has_key() ? 4 : 3;
        if (_true->num_srcs() == num_srcs
         && _true->src(num_srcs-1) == values.back().second) {
          // combine predicates
          auto pred0 = values.front().first;
          if (key) {
            pred0 = this->create_node<opimpl>(ch_op::eq, 1, false, key, pred0, branch->sloc);
          }
          auto pred1 = _true->src(0).impl();
          if (_true->has_key()) {
            // create predicate
            pred1 = this->create_node<opimpl>(ch_op::eq, 1, false, pred1, _true->src(1).impl(), branch->sloc);
            // remove key from src list
            _true->remove_key();
          }
          auto pred = this->create_node<opimpl>(ch_op::andb, 1, false, pred0, pred1, branch->sloc);
          _true->src(0) = pred;
          return _true;
        }
      }
    }

    return nullptr;
  };

  //--
  auto emit_conditional_block = [&](const cond_block_t* block,
                                    lnodeimpl* current)->lnodeimpl* {
    // get existing definition in current block
    auto it = defs.find(block->id);
    if (it != defs.end()) {
      current = it->second;
    }
    // recurse emit conditionals from nested blocks
    for (auto br : block->branches) {
      current = emit_conditional_branch(br, current);
    }
    return current;
  };

  //--
  emit_conditional_branch = [&](const cond_br_t* branch,
                                lnodeimpl* current)->lnodeimpl* {
    uint32_t changed = 0;
    branch_info_t values;

    for (auto block : branch->blocks) {
      // get definition
      auto value = emit_conditional_block(block, current);
      values.emplace_back(block->pred, value);
      changed |= (value != current);
    }

    if (changed) {
      // add default value if not provided
      if (values.back().first) {
         values.emplace_back(nullptr, current);
      }

      // optimize the branch
      auto ret = branch_optimizer(branch->key, values);
      if (ret)
        return ret;

      // create select node
      auto sel = this->create_node<selectimpl>(
                          current->size(), branch->key, branch->sloc);
      for (auto& value : values) {
        auto pred = value.first;
        if (pred) {
          // the case predicate should be a literal value
          assert(!branch->key || type_lit == pred->type());
          sel->srcs().push_back(pred);
        }
        sel->srcs().push_back(value.second);
      }

      return sel;
    }

    return current;
  };

  // get current variable value
  auto current = dst->slice(range.offset, range.length, branch->sloc);

  // emit conditional variable
  auto it = cond_inits_.find(dst->id());
  if (it != cond_inits_.end()) {
    current = emit_conditional_block(it->second, current);
  } else {    
    current = emit_conditional_branch(branch, current);
  }

  return current;
}

lnodeimpl* context::create_predicate(const source_location& sloc) {
  auto zero = this->create_literal(sdata_type(1, false));
  auto one = this->create_literal(sdata_type(1, true));

  // create predicate variable
  auto predicate = this->create_node<proxyimpl>(zero, 0, 1, sloc, "predicate");
  this->remove_local_variable(predicate, nullptr);

  // assign predicate
  this->conditional_assign(predicate, 0, 1, one, sloc);

  return predicate;
}

bindimpl* context::current_binding() {
  return reinterpret_cast<bindimpl*>(bindings_.back());
}

void context::register_tap(const lnode& node,
                           const std::string& name,
                           const source_location& sloc) {
  auto sid = identifier_from_string(name);  
  auto num_dups = dup_tap_names_.insert(sid);
  if (num_dups) {
    sid = stringf("tap_%s_%ld", sid.c_str(), num_dups);
  } else {
    sid = stringf("tap_%s", sid.c_str());
  }
  this->create_node<tapimpl>(node, sid, sloc);
}

udfimpl* context::create_udf_node(udf_iface* udf,
                                  const std::vector<lnode>& inputs,
                                  const source_location& sloc) {
  if (udf->is_seq()) {
    auto cd = this->current_cd(sloc);
    return this->create_node<udfsimpl>(udf, cd, inputs, sloc);
  } else {
    return this->create_node<udfcimpl>(udf, inputs, sloc);
  }
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

  uint64_t input_bits = 0;
  uint64_t output_bits = 0;
  uint64_t register_bits = 0;
  uint64_t memory_bits = 0;
  uint64_t literal_bits = 0;

  std::function<void(context*)> calc_stats = [&](context* ctx) {
    for (lnodeimpl* node : ctx->nodes()) {
      switch (node->type()) {
      case type_input:
        if (nullptr == ctx->parent()) {
          input_bits += node->size();
          ++num_inputs;
        }
        break;
      case type_output:
        if (nullptr == ctx->parent()) {
          output_bits += node->size();
          ++num_outputs;
        }
        break;
      case type_reg:
        register_bits += node->size();
        ++num_registers;
        break;
      case type_mem:
        memory_bits += node->size();
        ++num_memories;
        break;
      case type_lit:
        literal_bits += node->size();
        ++num_literals;
        break;
      case type_op:
        ++num_ops;
        break;
      case type_sel:
        ++num_muxes;
        break;
      case type_bind:
        calc_stats(reinterpret_cast<bindimpl*>(node)->module());
        break;
      default:
        break;
      }
    }
  };

  calc_stats(this);

  out << "ch-stats: total inputs = " << num_inputs << " (" << input_bits << " bits)" << std::endl;
  out << "ch-stats: total outputs = " << num_outputs << " (" << output_bits << " bits)" << std::endl;
  out << "ch-stats: total registers = " << num_registers << " (" << register_bits << " bits)" << std::endl;
  out << "ch-stats: total memories = " << num_memories << " (" << memory_bits << " bits)" << std::endl;
  out << "ch-stats: total literals = " << num_literals << " (" << literal_bits << " bits)" << std::endl;
  out << "ch-stats: total ops = " << num_ops << std::endl;
  out << "ch-stats: total muxes = " << num_muxes << std::endl;
}

///////////////////////////////////////////////////////////////////////////////

void ch::internal::registerTap(const lnode& node, const std::string& name) {
  auto sloc = get_source_location();
  node.impl()->ctx()->register_tap(node, name, sloc);
}

void ch::internal::registerEnumString(const lnode& node, void* callback) {
  node.impl()->ctx()->register_enum_string(node.id(), (enum_string_cb)callback);
}
