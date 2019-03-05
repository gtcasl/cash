#pragma once

#include "lnode.h"

#define CH_LNODE_TYPE(t) type_##t,
#define CH_LNODE_NAME(n) #n,
#define CH_LNODE_INDEX(op) ((int)op)
#define CH_LNODE_ENUM(m) \
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
  return type == type_reg
      || type == type_mwport
      || type == type_msrport
      || type == type_udfs;
}

class cdimpl;
cdimpl* get_snode_cd(lnodeimpl* node);

lnodeimpl* get_snode_enable(lnodeimpl* node);

lnodeimpl* get_snode_reset(lnodeimpl* node);

using clone_map = std::unordered_map<uint32_t, lnodeimpl*>;

class lnodeimpl : public refcounted {
public:

  uint32_t id() const {
    return id_;
  }

  const std::string& name() const {
    return name_;
  }

  std::string& name() {
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
  
  uint32_t num_srcs() const {
    return srcs_.size();
  }
  
  const lnode& src(uint32_t index) const {
    assert(index < srcs_.size());
    return srcs_[index];
  }

  uint32_t size() const {
    return size_;
  }

  size_t hash() const;

  const source_location& sloc() const {
    return sloc_;
  }

  std::vector<lnode>& srcs();

  lnode& src(uint32_t index);

  uint32_t add_src(const lnode& src);

  void remove_src(uint32_t index);

  void resize(uint32_t size);

  virtual lnodeimpl* clone(context* ctx, const clone_map& cloned_nodes) const = 0;

  virtual bool equals(const lnodeimpl& other) const;

  virtual lnodeimpl* slice(uint32_t offset,
                           uint32_t length,
                           const source_location& sloc) const;

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
            const std::string& name = "");

  virtual ~lnodeimpl();

  context* ctx_;
  std::string name_;
  source_location sloc_;
  const uint32_t id_;
  const lnodetype type_;
  mutable size_t hash_;

private:

  std::vector<lnode> srcs_;
  uint32_t size_;

  friend class context;
};

const char* to_string(lnodetype type);

std::ostream& operator<<(std::ostream& out, lnodetype type);

}
}
