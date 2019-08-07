#pragma once

#include "lnodeimpl.h"

namespace ch {
namespace internal {

class proxyimpl;

class branchconverter {
protected:

  struct cond_br_t;

  struct cond_block_t {
    cond_block_t(uint32_t p_id, lnodeimpl* p_cond, cond_br_t* p_branch)
      : id(p_id)
      , cond(p_cond)
      , branch(p_branch)
      , pred(nullptr)
    {}

    uint32_t id;
    lnodeimpl* cond;
    cond_br_t* branch;
    std::list<cond_br_t*> branches;
    proxyimpl* pred;
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
  typedef std::unordered_map<proxyimpl*, cond_slices_t> cond_vars_t;
  typedef std::unordered_map<uint32_t, cond_block_t*> cond_inits_t;

  lnodeimpl* emit(proxyimpl* dst,
                  const cond_range_t& range,
                  const cond_defs_t& defs,
                  const cond_br_t* branch);

  context*                ctx_;
  uint32_t                cond_blk_idx_;
  std::stack<cond_br_t*>  cond_branches_;
  cond_vars_t             cond_vars_;
  cond_inits_t            cond_inits_;

public:

  branchconverter(context* ctx);

  bool enabled() const {
    return !cond_branches_.empty();
  }

  void add_definition(lnodeimpl* node);

  void begin_branch(lnodeimpl* key, const source_location& sloc);

  void end_branch();

  void begin_block(lnodeimpl* pred);

  void end_block();

  bool is_local(lnodeimpl* node) const;

  void write(proxyimpl* dst,
             uint32_t offset,
             uint32_t length,
             lnodeimpl* src,
             const source_location& sloc);

  lnodeimpl* get_predicate(const source_location& sloc);
};

}}
