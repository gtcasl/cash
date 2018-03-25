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
#include "aluimpl.h"
#include "assertimpl.h"
#include "tickimpl.h"
#include "cdomain.h"
#include "arithm.h"
#include "select.h"
#include "enum.h"
#include "misc.h"

namespace ch {
namespace internal {

class context_manager {
public:
  context_manager() : ctx_(nullptr) {}
  ~context_manager() {
    if (ctx_)
      ctx_->release();
  }

  context* create(size_t signature, const std::string& name) {
    std::string unique_name(name);
    auto it = module_names_.find(signature);
    if (it != module_names_.end()) {
      unique_name = it->second;
    } else {
      unique_name = unique_name_.get(unique_name.c_str());
      module_names_[signature] = unique_name;
    }
    return new context(unique_name.c_str());
  }

  context* get_ctx() const {
    CH_CHECK(ctx_ != nullptr, "invalid context!");
    return ctx_;
  }

  context* swap(context* ctx) {
    std::swap(ctx_, ctx);
    return ctx;
  }

protected:
  mutable context* ctx_;
  std::unordered_map<size_t, std::string> module_names_;
  unique_name unique_name_;
};

}
}

using namespace ch::internal;

thread_local context_manager tls_ctx;

context* ch::internal::ctx_create(size_t signature, const std::string& name) {
  return tls_ctx.create(signature, name);
}

context* ch::internal::ctx_swap(context* ctx) {
  return tls_ctx.swap(ctx);
}

context* ch::internal::ctx_curr() {
  return tls_ctx.get_ctx();
}

///////////////////////////////////////////////////////////////////////////////

static uint32_t make_id() {
  static uint32_t s_id(0);
  return s_id++;
}

context::context(const std::string& name)
  : id_(make_id())
  , name_(name)
  , node_ids_(0)
  , block_idx_(0)
  , default_clk_(nullptr)
  , default_reset_(nullptr)
  , tick_(nullptr)
{}

context::~context() {
  // delete allocated nodes
  for (auto it = nodes_.begin(), end = nodes_.end(); it != end;) {
    delete *it++;
  }
}

void context::push_clk(const lnode& clk) {  
  user_clks_.emplace(clk);
}

void context::pop_clk() {
  user_clks_.pop();
}

void context::push_reset(const lnode& reset) {
  user_resets_.emplace(reset);
}

void context::pop_reset() {
  user_resets_.pop();
}

lnodeimpl* context::get_clk() {
  if (!user_clks_.empty())
    return user_clks_.top().get_impl();
  if (nullptr == default_clk_) {
    default_clk_ = this->createNode<inputimpl>(1, "clk");
  }
  return default_clk_;
}

lnodeimpl* context::get_reset() {
  if (!user_resets_.empty())
    return user_resets_.top().get_impl();
  if (nullptr == default_reset_) {
     default_reset_ = this->createNode<inputimpl>(1, "reset");
  }
  return default_reset_;
}

lnodeimpl* context::get_tick() {
  if (nullptr == tick_) {
    tick_ = this->createNode<tickimpl>();
  }
  return tick_;
}

uint32_t context::node_id() {
  uint32_t nodeid = ++node_ids_;
#ifndef NDEBUG
  uint32_t dbg_nodeid = platform::self().get_dbg_node();
  if (dbg_nodeid) {
    if (nodeid == dbg_nodeid) {
      CH_ABORT("debugbreak on nodeid %d hit!", nodeid);
    }
  }
#endif
  return nodeid;
}

aluimpl* context::createAluNode(uint32_t op, const lnode& in) {
  aluimpl* node;
  alu_key_t hk{op, in.get_id(), 0};
  auto it = alu_cache_.find(hk);
  if (it == alu_cache_.end()) {
    node = this->createNode<aluimpl>((ch_alu_op)op, in);
    alu_cache_[hk] = node;
  } else {
    node = it->second;
  }
  return node;
}

aluimpl* context::createAluNode(uint32_t op, const lnode& lhs, const lnode& rhs) {
  aluimpl* node;
  alu_key_t hk{op, lhs.get_id(), rhs.get_id()};
  if (alu_symmetric((ch_alu_op)hk.op)
   && hk.arg0 > hk.arg1) {
    // adjust ordering for symmetrix operators
    std::swap(hk.arg0, hk.arg1);
  }
  auto it = alu_cache_.find(hk);
  if (it == alu_cache_.end()) {
    node = this->createNode<aluimpl>((ch_alu_op)op, lhs, rhs);
    alu_cache_[hk] = node;
  } else {
    node = it->second;
  }
  return node;
}

node_list_t::iterator context::destroyNode(const node_list_t::iterator& it) {
  auto node = *it;
  auto next = this->remove_node(it);
  delete node;
  return next;
}

void context::add_node(lnodeimpl* node) {
  nodes_.emplace_back(node);

  switch (node->get_type()) {
  case type_undef:
    undefs_.emplace_back((undefimpl*)node);
    break;
  case type_proxy:
    proxies_.emplace_back((proxyimpl*)node);
    break;
  case type_lit:
    literals_.emplace_back((litimpl*)node);
    break;
  case type_input:
    {
      // ensure clock and reset signals are ordered first
      auto input = dynamic_cast<inputimpl*>(node);
      if (input->get_name() == "clk") {
        inputs_.emplace_front(input);
      } else if (input->get_name() == "reset") {
        if (default_clk_) {
          inputs_.emplace(std::next(inputs_.begin()), input);
        } else {
          inputs_.emplace_front(input);
        }
      } else {
        inputs_.emplace_back(input);
      }
    }
    break;  
  case type_output:
    outputs_.emplace_back((outputimpl*)node);
    break; 
  case type_bind:
    bindings_.emplace_back((bindimpl*)node);
    break;
  case type_tap:
    taps_.emplace_back((tapimpl*)node);
    break;
  case type_assert:
  case type_print:
    gtaps_.emplace_back((ioimpl*)node);
    break;
  default:
    break;
  }

  // register local nodes, io objects & literals have global scope
  if (!cond_branches_.empty()
   && nullptr == dynamic_cast<ioimpl*>(node)
   && nullptr == dynamic_cast<litimpl*>(node)) {
    auto curr_branch = cond_branches_.top();
    auto curr_block = curr_branch->blocks.back();
    cond_inits_[node->get_id()] = curr_block;
  }
}

node_list_t::iterator context::remove_node(const node_list_t::iterator& it) {
  auto node = *it;
  DBG(3, "*** deleting node: %s%d(#%d)\n",
      to_string(node->get_type()), node->get_size(), node->get_id());
  
  assert(!nodes_.empty());
  auto next = nodes_.erase(it);
  
  switch (node->get_type()) {
  case type_undef:
    undefs_.remove((undefimpl*)node);
    break;
  case type_proxy:
    proxies_.remove((proxyimpl*)node);
    break;
  case type_lit:
    literals_.remove((litimpl*)node);
    break;
  case type_input:
    if (node == default_clk_) {
      default_clk_ = nullptr;
    } else
    if (node == default_reset_) {
      default_reset_ = nullptr;
    }
    inputs_.remove((inputimpl*)node);
    break;
  case type_output:
    outputs_.remove((outputimpl*)node);
    break;
  case type_bind:
    bindings_.remove((bindimpl*)node);
    break;
  case type_tap:
    taps_.remove((tapimpl*)node);
    break;
  case type_assert:
  case type_print:
    gtaps_.remove((ioimpl*)node);
    break;
  case type_tick:
    if (node == tick_)
      tick_ = nullptr;
    break;
  default:
    break;
  }
  return next;
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
  std::function<void(cond_br_t* branch)> delete_branch = [&](cond_br_t* branch) {
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
      auto proxy  = dynamic_cast<proxyimpl*>(dst);
      assert(proxy);
      for (auto& slice : var.second) {
        auto value  = this->emit_conditionals(dst, slice.first, slice.second, curr_branch);
        proxy->add_source(slice.first.offset, value, 0, slice.first.length);
      }
    }
    // cleanup
    delete_branch(curr_branch);
    cond_vars_.clear();
    cond_inits_.clear();
    block_idx_ = 0;
  }
}

void context::begin_block(lnodeimpl* pred) {
  // insert new conditional block  
  auto curr_branch = cond_branches_.top();
  auto new_block = new cond_block_t(++block_idx_, pred, curr_branch);
  curr_branch->blocks.push_back(new_block);
}

void context::end_block() {
  //--
}

void context::remove_local_variable(lnodeimpl* src, lnodeimpl* dst) {
  // remove from source init block
  auto it = cond_inits_.find(src->get_id());
  if (it != cond_inits_.end()) {
    cond_inits_.erase(it);
    if (dst) {
      // add to destination's init block
      auto it = cond_inits_.find(dst->get_id());
      if (it != cond_inits_.end()) {
        cond_inits_[src->get_id()] = it->second;
      }
    }
  }
}

bool context::conditional_enabled(lnodeimpl* node) const {
  // a node is conditionally assigned if it is not local to the current block
  if (cond_branches_.empty())
    return false;
  if (node) {
    auto it = cond_inits_.find(node->get_id());
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
    lnodeimpl* src) {
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
    if (src->get_size() != range.length) {
      src = this->createNode<proxyimpl>(src, src_offset, range.length);
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
      const auto& curr  = it->first;
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
  std::function<void (cond_defs_t& defs, const cond_block_t* block)>
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
    const auto& curr = it->first;
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
  auto branch_optimizer = [&](lnodeimpl* key,
                              branch_info_t& values,
                              lnodeimpl* current)->lnodeimpl* {
    // ensure default argument
    if (values.back().first) {
       values.emplace_back(nullptr, current);
    }

    {
      // skip paths with value equal to default value
      auto df_value = values.back().second;
      for (auto it = values.begin(), end = values.end(); it != end;) {
        if (it->first && it->second == df_value) {
          it = values.erase(it);
        } else {
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
    if (2 == values.size()) {
      auto _true = dynamic_cast<selectimpl*>(values.front().second);
      if (_true) {
        uint32_t num_srcs = _true->has_key() ? 4 : 3;
        if (_true->get_num_srcs() == num_srcs
         && _true->get_src(num_srcs-1) == values.back().second) {
          // combine predicates
          auto pred0 = values.front().first;
          if (key) {
            pred0 = this->createAluNode(alu_eq, key, pred0);
          }
          auto pred1 = _true->get_src(0);
          if (_true->has_key()) {
            // create predicate
            pred1 = this->createAluNode(alu_eq, pred1, _true->get_src(1));            
            // remove key from src list
            _true->get_srcs().erase(_true->get_srcs().begin());
            _true->set_key(false);
          }
          auto pred = this->createAluNode(alu_and, pred0, pred1);
          _true->set_src(0, pred);
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
  auto get_scalar = [&](lnodeimpl* pred)->lnodeimpl* {
    assert(type_lit == pred->get_type());
    return pred;
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
      // optimize the branch
      auto ret = branch_optimizer(branch->key, values, current);
      if (ret)
        return ret;

      // create select node
      auto sel = this->createNode<selectimpl>(current->get_size(), branch->key);
      sel->set_source_location(branch->sloc);      
      for (auto& value : values) {
        auto pred = value.first;
        if (pred) {
          if (branch->key) {
            pred = get_scalar(pred);
          }
          sel->get_srcs().push_back(pred);
        }
        sel->get_srcs().push_back(value.second);
      }

      return sel;
    }

    return current;
  };

  // get current variable value
  auto current = dst->get_slice(range.offset, range.length);

  // emit conditional variable
  auto it = cond_inits_.find(dst->get_id());
  if (it != cond_inits_.end()) {
    current = emit_conditional_block(it->second, current);
  } else {    
    current = emit_conditional_branch(branch, current);
  }

  return current;
}

lnodeimpl* context::get_predicate() {
  auto zero = this->get_literal(bitvector(1, false));
  auto one = this->get_literal(bitvector(1, true));

  // create predicate variable
  auto predicate = this->createNode<proxyimpl>(zero);
  this->remove_local_variable(predicate, nullptr);

  // assign predicate
  this->conditional_assign(predicate, 0, 1, one);

  return predicate;
}

lnodeimpl* context::get_literal(const bitvector& value) {
  // first lookup literals cache
  for (auto lit : literals_) {
    if (lit->get_value() == value)
      return lit;
  }
  // create new literal
  return this->createNode<litimpl>(value);
}

cdomain* context::create_cdomain(
    const std::vector<clock_event>& sensitivity_list) {
  // return existing cdomain 
  for (auto cd : cdomains_) {
    if (*cd == sensitivity_list)
      return cd;
  }  
  // allocate new cdomain
  auto cd = new cdomain(this, sensitivity_list);
  cdomains_.emplace_back(cd);
  return cd;
}

void context::remove_cdomain(cdomain* cd) {
  cdomains_.remove(cd);
}

void context::register_tap(const std::string& name, const lnode& node) {
  this->createNode<tapimpl>(node, unique_tap_names_.get(name).c_str());
}

bindimpl* context::get_binding(context* module) {
  for (auto binding : bindings_) {
    if (binding->get_module() == module)
      return binding;
  }
  return this->createNode<bindimpl>(module);
}

void context::bind_input(const lnode& src, const lnode& input) {
  auto binding = this->get_binding(input.get_ctx());
  binding->bind_input(src, input);
}

void context::bind_output(const lnode& dst, const lnode& output) {
  auto binding = this->get_binding(output.get_ctx());
  binding->bind_output(dst, output);
}

live_nodes_t context::compute_live_nodes() const {
  live_nodes_t live_nodes;

  // get inputs
  for (auto node : inputs_) {
    live_nodes.insert(node);
  }

  // get outputs
  for (auto node : outputs_) {
    live_nodes.insert(node);
  }  
  
  // get debug taps
  for (auto node : taps_) {
    live_nodes.insert(node);
  }

  // get assert taps
  for (auto node : gtaps_) {
    live_nodes.insert(node);
  }

  return live_nodes;
}

void context::tick(ch_tick t) {
  // tick bindings
  for (auto node : bindings_) {
    node->tick(t);
  }

  // tick local clock domains
  for (auto cd : cdomains_) {
    cd->tick(t);
  }
}

void context::tick_next(ch_tick t) {
  // tick bindings
  for (auto node : bindings_) {
    node->tick_next(t);
  }

  // tick local clock domains
  for (auto cd : cdomains_) {
    cd->tick_next(t);
  }
}

void context::eval(ch_tick t) {
  // evaluate bindings
  for (auto node : bindings_) {
    node->eval(t);
  }

  // evaluate outputs
  for (auto node : outputs_) {
    node->eval(t);
  }

  // evaluate taps
  for (auto node : taps_) {
    node->eval(t);
  }

  // evaluate asserts
  for (auto node : gtaps_) {
    node->eval(t);
  }
}

void context::register_enum_string(const lnode& node, enum_string_cb callback) {
  enum_strings_.emplace(node.get_var_id(), callback);
}

const char* context::enum_to_string(const lnode& node, ch_tick t) {
  auto iter = enum_strings_.find(node.get_var_id());
  if (iter != enum_strings_.end()) {
    return iter->second(node.eval(t).get_word(0));
  }
  return "undefined";
}

void context::dump_ast(std::ostream& out, uint32_t level) {
  for (auto node : nodes_) {
    node->print(out, level);
    out << std::endl;
  }
}

void context::dump_cfg(lnodeimpl* node, std::ostream& out, uint32_t level) {
  std::vector<bool> visits(node_ids_ + 1);
  std::unordered_map<uint32_t, tapimpl*> taps;

  std::function<void(lnodeimpl* node)> dump_cfg_impl = [&](lnodeimpl* node) {
    visits[node->get_id()] = true;
    node->print(out, level);

    auto iter = taps.find(node->get_id());
    if (iter != taps.end()) {
      out << " // " << iter->second->get_name();
      out << std::endl;
      return;
    }
    out << std::endl;

    for (const lnode& src : node->get_srcs()) {
      if (!visits[src.get_id()]) {
        dump_cfg_impl(src.get_impl());
      }
    }
  };
  
  for (tapimpl* tap : taps_) {
    taps[tap->get_target().get_id()] = tap;
  }
  
  visits[node->get_id()] = true;
  
  if (type_tap == node->get_type()) {
    auto tap = dynamic_cast<tapimpl*>(node);
    node = tap->get_target().get_impl();
    node->print(out, level);
    out << " // " << tap->get_name();
  } else {  
    node->print(out, level);
  }
  out << std::endl;    
  for (const lnode& src : node->get_srcs()) {
    if (!visits[src.get_id()]) {
      dump_cfg_impl(src.get_impl());
    }
  }
}

void context::dump_stats(std::ostream& out) {
  uint64_t num_memories = 0;
  uint64_t num_registers = 0;
  uint64_t num_muxes = 0;
  uint64_t num_alus = 0;
  uint64_t num_lits = 0;

  uint64_t memory_bits = 0;
  uint64_t register_bits = 0;

  std::function<void(context* ctx)> calc_stats = [&](context* ctx) {
    for (lnodeimpl* node : ctx->get_nodes()) {
      switch (node->get_type()) {
      case type_mem:
        memory_bits += dynamic_cast<memimpl*>(node)->get_total_size();
        ++num_memories;
        break;
      case type_reg:
        register_bits += node->get_size();
        ++num_registers;
        break;
      case type_sel:
        ++num_muxes;
        break;
      case type_alu:
        ++num_alus;
        break;
      case type_lit:
        ++num_lits;
        break;
      case type_bind:
        calc_stats(dynamic_cast<bindimpl*>(node)->get_module());
        break;
      default:
        break;
      }
    }
  };

  calc_stats(this);

  out << "ch-stats: total memory bits = " << memory_bits << std::endl;
  out << "ch-stats: total register bits = " << register_bits << std::endl;
  out << "ch-stats: total memories = " << num_memories << std::endl;
  out << "ch-stats: total registers = " << num_registers << std::endl;
  out << "ch-stats: total muxes = " << num_muxes << std::endl;
  out << "ch-stats: total alus = " << num_alus << std::endl;
  out << "ch-stats: total literals = " << num_lits << std::endl;
}

///////////////////////////////////////////////////////////////////////////////

void ch::internal::registerTap(const std::string& name, const lnode& node) {
  node.get_ctx()->register_tap(name, node);
}

void ch::internal::ch_dumpStats(std::ostream& out, const device& device) {
  get_ctx(device)->dump_stats(out);
}

void ch::internal::bindInput(const lnode& src, const lnode& input) {
  src.get_ctx()->bind_input(src, input);
}

void ch::internal::bindOutput(const lnode& dst, const lnode& output) {
  dst.get_ctx()->bind_output(dst, output);
}

void ch::internal::register_enum_string(const lnode& node, void* callback) {
  node.get_ctx()->register_enum_string(node, (enum_string_cb)callback);
}
