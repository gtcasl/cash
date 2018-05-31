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
  m(time) \
  m(print) \
  m(udf)

namespace ch {
namespace internal {
  
enum lnodetype {
  CH_LNODE_ENUM(CH_LNODE_TYPE)
};

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

  uint32_t add_src(uint32_t index, const lnode& src);
  
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

  virtual bool equals(const lnodeimpl& rhs) const;

  virtual std::size_t hash() const {
    return 0;
  }

  virtual void initialize() {}

  virtual void reset() {}

  virtual void eval() = 0;

  virtual lnodeimpl* slice(uint32_t offset, uint32_t length);

  virtual void print(std::ostream& out, uint32_t level) const;

protected:

  lnodeimpl(context* ctx,
            lnodetype type,
            uint32_t size,
            uint32_t var_id = 0,
            const std::string& name = "",
            const source_location& sloc = source_location());

  virtual ~lnodeimpl();

  struct hash_t {
    union {
      struct {
        std::size_t type : 5;
        std::size_t size : 10;
        std::size_t srcs : 10;
        std::size_t arg0 : 13;
        std::size_t arg1 : 13;
        std::size_t arg2 : 13;
      } fields;
      std::size_t value;
    };
    hash_t() : value(0) {}
  };

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

  void eval() override;
};

const char* to_string(lnodetype type);

std::ostream& operator<<(std::ostream& out, lnodetype type);

}
}
