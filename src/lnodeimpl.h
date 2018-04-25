#pragma once

#include "lnode.h"

#define CH_LNODE_TYPE(t) type_##t,
#define CH_LNODE_NAME(n) #n,
#define CH_LNODE_INDEX(op) ((int)op)
#define CH_LNODE_ENUM(m) \
  m(undef) \
  m(lit) \
  m(input) \
  m(output) \
  m(proxy) \
  m(cd) \
  m(alu) \
  m(sel) \
  m(reg) \
  m(mem) \
  m(memport) \
  m(bind) \
  m(bindport) \
  m(tap) \
  m(assert) \
  m(tick) \
  m(print)

namespace ch {
namespace internal {
  
enum lnodetype {
  CH_LNODE_ENUM(CH_LNODE_TYPE)
};

class lnodeimpl {
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

  uint32_t num_srcs() const {
    return srcs_.size();
  }

  const std::vector<lnode>& srcs() const {
    return srcs_;
  }
  
  std::vector<lnode>& srcs() {
    return srcs_;
  }
  
  const lnode& src(unsigned index) const {
    assert(index < srcs_.size());
    return srcs_[index];
  }

  lnode& src(unsigned index) {
    assert(index < srcs_.size());
    return srcs_[index];
  }

  unsigned add_src(unsigned index, const lnode& src);
  
  uint32_t size() const {
    return value_.size();
  }
  
  const bitvector& value() const {
    return value_;
  }

  bitvector& value() {
    return value_;
  }

  uint32_t var_id() const {
    return var_id_;
  }

  const source_location& sloc() const {
    return sloc_;
  }

  virtual lnodeimpl* slice(uint32_t offset, uint32_t length);

  virtual const bitvector& eval(ch_tick t) = 0;
  
  virtual void print(std::ostream& out, uint32_t level) const;

protected:

  lnodeimpl(context* ctx,
            lnodetype type,
            uint32_t size,
            unsigned var_id = 0,
            const std::string& name = "",
            const source_location& sloc = source_location());

  virtual ~lnodeimpl();

  context* ctx_;
  uint32_t id_;  
  lnodetype type_;
  std::vector<lnode> srcs_;
  bitvector value_;
  uint32_t var_id_;
  std::string name_;
  source_location sloc_;

  friend class context;
};

class undefimpl : public lnodeimpl {
public:

  undefimpl(context* ctx, uint32_t size);

  const bitvector& eval(ch_tick t) override;
};

const char* to_string(lnodetype type);

std::ostream& operator<<(std::ostream& out, lnodetype type);

}
}
