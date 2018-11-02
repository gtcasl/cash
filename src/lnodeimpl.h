#pragma once

#include "lnode.h"

#define CH_LNODE_TYPE(t) type_##t,
#define CH_LNODE_NAME(n) #n,
#define CH_LNODE_INDEX(op) ((int)op)
#define CH_LNODE_ENUM(m) \
  m(undef) \
  m(lit) \
  m(proxy) \
  m(input) \
  m(output) \
  m(alu) \
  m(sel) \
  m(cd) \
  m(reg) \
  m(mem) \
  m(marport) \
  m(msrport) \
  m(mwport) \
  m(bind) \
  m(bindin) \
  m(bindout) \
  m(tap) \
  m(time) \
  m(assert) \
  m(print) \
  m(udfc) \
  m(udfs)

namespace ch {
namespace internal {
  
class context;

enum lnodetype {
  CH_LNODE_ENUM(CH_LNODE_TYPE)
};

inline bool is_snode_type(lnodetype type) {
  return type_reg == type || type_mwport == type || type_msrport == type || type_udfs == type;
}

inline bool is_output_type(lnodetype type) {
  return type_output == type || type_tap == type || type_assert == type  || type_print == type;
}

class cdimpl;
cdimpl* get_snode_cd(lnodeimpl* node);

using clone_map = std::unordered_map<uint32_t, lnodeimpl*>;

class lnodeimpl : public refcounted {
public:

  uint32_t id() const {
    return id_;
  }

  const std::string& name() const {
    return name_;
  }
  
  lnodetype type() const {
    return type_;
  }

  context* ctx() const {
    return ctx_;
  }

  const std::vector<lnode>& srcs() const {
    return srcs_;
  }
  
  std::vector<lnode>& srcs() {
    return srcs_;
  }

  uint32_t num_srcs() const {
    return srcs_.size();
  }
  
  const lnode& src(uint32_t index) const {
    assert(index < srcs_.size());
    return srcs_[index];
  }

  lnode& src(uint32_t index) {
    assert(index < srcs_.size());
    return srcs_[index];
  }

  uint32_t add_src(const lnode& src);
  
  uint32_t size() const {
    return size_;
  }

  uint32_t var_id() const {
    return var_id_;
  }

  const source_location& sloc() const {
    return sloc_;
  }

  virtual lnodeimpl* clone(context* ctx, const clone_map& cloned_nodes) = 0;

  virtual bool equals(const lnodeimpl& other) const;

  virtual uint64_t hash() const {
    return 0;
  }

  virtual lnodeimpl* slice(uint32_t offset,
                           uint32_t length,
                           const source_location& sloc);

  virtual void write(uint32_t dst_offset,
                     const lnode& src,
                     uint32_t src_offset,
                     uint32_t length,
                     const source_location& sloc);

  virtual void print(std::ostream& out) const;

  std::string debug_info() const;

protected:

  lnodeimpl(context* ctx,
            lnodetype type,
            uint32_t size,
            const source_location& sloc,
            const std::string& name = "",
            uint32_t var_id = 0);

  virtual ~lnodeimpl();

  struct hash_t {
#if defined(__clang__)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wnested-anon-types"
#endif
    union {
      struct {
        uint64_t type : 5;
        uint64_t size : 22;
        uint64_t op   : 5;
        uint64_t arg0 : 16;
        uint64_t arg1 : 16;
      } fields;
      uint64_t value;
    };
#if defined(__clang__)
  #pragma clang diagnostic pop
#endif
    hash_t() : value(0) {}
  };

  context* ctx_;
  uint32_t id_;  
  lnodetype type_;
  uint32_t size_;
  std::vector<lnode> srcs_;  
  source_location sloc_;
  std::string name_;
  uint32_t var_id_;

  friend class context;
};

class undefimpl : public lnodeimpl {
public:

  undefimpl(context* ctx, uint32_t size, const source_location& sloc);  

  virtual lnodeimpl* clone(context*, const clone_map&) override {
    return nullptr;
  }
};

const char* to_string(lnodetype type);

std::ostream& operator<<(std::ostream& out, lnodetype type);

}
}
