#include "branchconv.h"
#include "context.h"
#include "litimpl.h"
#include "proxyimpl.h"
#include "selectimpl.h"

using namespace ch::internal;

branchconverter::branchconverter(context* ctx)
  : ctx_(ctx)
  , cond_blk_idx_(0)
{}

void branchconverter::add_definition(lnodeimpl *node) {
  auto curr_branch = cond_branches_.top();
  auto curr_block = curr_branch->blocks.back();
  cond_inits_[node->id()] = curr_block;
}

void branchconverter::begin_branch(lnodeimpl* key, const source_location& sloc) {
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

void branchconverter::end_branch() {
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
        auto value = this->emit(dst, slice.first, slice.second, curr_branch);
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

void branchconverter::begin_block(lnodeimpl* pred) {
  // insert new conditional block
  auto curr_branch = cond_branches_.top();
  auto new_block = new cond_block_t(++cond_blk_idx_, pred, curr_branch);
  curr_branch->blocks.push_back(new_block);
}

void branchconverter::end_block() {
  //--
}

bool branchconverter::is_local(lnodeimpl* node) const {
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

void branchconverter::write(
    proxyimpl* dst,
    uint32_t offset,
    uint32_t length,
    lnodeimpl* src,
    const source_location& sloc) {
  assert(this->is_local(dst));
  auto& defs       = cond_vars_[dst];
  auto curr_branch = cond_branches_.top();
  auto curr_block  = curr_branch->blocks.back();

  //--
  auto add_definition = [&](cond_slices_t& slices,
                            const cond_range_t& range,
                            uint32_t loc,
                            lnodeimpl* src,
                            uint32_t src_offset) {
    if (src->size() != range.length) {
      src = ctx_->create_node<proxyimpl>(src, src_offset, range.length, "slice", sloc);
    }
    slices[range][loc] = src;
  };

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
  auto create_split_definitions = [&](cond_slices_t& split_list,
                                      const cond_range_t& range,
                                      uint32_t offset,
                                      uint32_t length) {
    cond_range_t new_range{offset, length};
    for (auto def : defs[range]) {
      add_definition(split_list, new_range, def.first, def.second, offset - range.offset);
    }
  };

  //--
  auto add_new_definition = [&](uint32_t var_offset, uint32_t offset, uint32_t length) {
    cond_range_t new_range{offset, length};

    // delete all existing definitions within current block
    delete_definitions(defs[new_range], curr_block);

    // add new definition
    add_definition(defs, new_range, curr_block->id, src, offset - var_offset);
  };

  {
    //--
    cond_slices_t split_list;

    // create split list for partially overlapping definitions
    for (auto it = defs.begin(), end = defs.end(); it != end;) {
      auto& curr = it->first;
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
          create_split_definitions(split_list, curr, curr.offset, var_end - curr.offset);
          create_split_definitions(split_list, curr, var_end, curr_end - var_end);
        } else if (var_end > curr_end) {
          // variable overlaps on the right
          create_split_definitions(split_list, curr, curr.offset, offset - curr.offset);
          create_split_definitions(split_list, curr, offset, curr_end - offset);
        } else {
          // variable fully included
          if (offset != curr.offset) {
            create_split_definitions(split_list, curr, curr.offset, offset - curr.offset);
          }
          create_split_definitions(split_list, curr, offset, var_end - offset);
          if (var_end != curr_end) {
            create_split_definitions(split_list, curr, var_end, curr_end - var_end);
          }
        }
        // remove entry
        it = defs.erase(it);
      } else {
        ++it;
      }
    }

    // insert split entries
    if (!split_list.empty()) {
      for (auto& item : split_list) {
        defs[item.first] = item.second;
      }
    }
  }

  //--
  uint32_t var_offset = offset;

  // add new definitions to current block
  for (auto it = defs.begin(), end = defs.end();
       length != 0 && it != end; ++it) {
    auto& curr = it->first;
    uint32_t curr_end = curr.offset + curr.length;
    uint32_t var_end  = offset + length;

    // does variable overlap existing definition?
    if (offset < curr_end && var_end > curr.offset) {
      if (offset == curr.offset
       && var_end == curr_end) {
        // variable strictly overlaps current definition
        add_new_definition(var_offset, offset, length);
        length = 0; // no need to continue
      } else if (offset < curr.offset) {
        // variable overlaps current definition on the left
        add_new_definition(var_offset, offset, curr.offset - offset);
        add_new_definition(var_offset, curr.offset, curr.length);
        uint32_t delta = (curr.offset - offset) + curr.length;
        offset += delta;
        length -= delta;
      } else if (var_end > curr_end) {
        // variable overlaps current definition on the right
        add_new_definition(var_offset, curr.offset, curr.length);
        offset += curr.length;
        length -= curr.length;
      } else {
        // splitting should have eliminated this case
        assert(false);
      }
    } else if (std::next(it) == end
            || var_end <= curr.offset) {
      // no overlap with current and next
      add_new_definition(var_offset, offset, length);
      length = 0; // no need to continue
    } else {
      // definitions no not overlap
      continue;
    }
  }

  if (length != 0) {
    add_new_definition(var_offset, offset, length);
  }
}

lnodeimpl*
branchconverter::emit(proxyimpl* dst,
                      const cond_range_t& range,
                      const cond_defs_t& defs,
                      const cond_br_t* branch) {
  //--
  std::function<lnodeimpl*(const cond_br_t* branch,
                           lnodeimpl* current)> emit_conditional_branch;

  //--
  typedef std::list<std::pair<lnodeimpl*, lnodeimpl*>> branch_info_t;

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

    // get definitions
    for (auto block : branch->blocks) {
      auto value = emit_conditional_block(block, current);
      values.emplace_back(block->pred, value);
      changed |= (value != current);
    }

    if (!changed)
      return current;

    // add default value if not provided
    if (values.back().first) {
      values.emplace_back(nullptr, current);
    }

    // return single assignment as default value
    if (1 ==  values.size()) {
      assert(nullptr == values.front().first);
      return values.front().second;
    }

    // create select node
    auto sel = ctx_->create_node<selectimpl>(
                        range.length, branch->key, branch->sloc);
    if (branch->key && (branch->key->size() <= 64)) {
      // insert switch cases in ascending order
      for (auto& value : values) {
        auto pred = value.first;
        if (pred) {
          // the case predicate should be a literal value
          assert(!branch->key || type_lit == pred->type());
          auto ipred = static_cast<int64_t>(reinterpret_cast<litimpl*>(pred)->value());
          uint32_t i = 1;
          for (; i < sel->num_srcs(); i += 2) {
            auto sel_ipred = static_cast<int64_t>(reinterpret_cast<litimpl*>(sel->src(i).impl())->value());
            CH_CHECK(sel_ipred != ipred, "duplicate switch case predicate");
            if (sel_ipred > ipred) {
              sel->insert_src(i, value.second);
              sel->insert_src(i, pred);
              break;
            }
          }
          if (i == sel->num_srcs()) {
            sel->add_src(pred);
            sel->add_src(value.second);
          }
        } else {
          sel->add_src(value.second);
        }
      }
    } else {
      for (auto& value : values) {
        auto pred = value.first;
        if (pred) {
          sel->add_src(pred);
        }
        sel->add_src(value.second);
      }
    }
    // check sources
    for (auto& src : sel->srcs()) {
      if (src.empty()) {
        fprintf(stderr, "error: not-fully initialized conditional variable: %s\n", sel->debug_info().c_str());
        std::abort();
      }
    }
    return sel;
  };

  // get current variable value
  auto current = dst->source(range.offset, range.length, branch->sloc);

  // emit conditional variable
  auto it = cond_inits_.find(dst->id());
  if (it != cond_inits_.end()) {
    current = emit_conditional_block(it->second, current);
  } else {
    current = emit_conditional_branch(branch, current);
  }

  return current;
}

lnodeimpl* branchconverter::create_predicate(const source_location& sloc) {
  auto zero = ctx_->create_literal(sdata_type(1, 0));
  auto one = ctx_->create_literal(sdata_type(1, 1));

  // create predicate variable
  auto predicate = ctx_->create_node<proxyimpl>(zero, 0, 1, "predicate", sloc);

  // remove from source init block
  auto it = cond_inits_.find(predicate->id());
  if (it != cond_inits_.end()) {
    cond_inits_.erase(it);
  }

  // assign predicate
  this->write(predicate, 0, 1, one, sloc);

  return predicate;
}
