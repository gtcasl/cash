#pragma once

#include "lnode.h"

#define CH_LNODE_TYPE(t) type_##t,
#define CH_LNODE_NAME(n) #n,
#define CH_LNODE_INDEX(op) ((int)op)
#define CH_LNODE_ENUM(m) \
  m(none) \
  m(lit) \
  m(proxy) \
  m(input) \
  m(output) \
  m(op) \
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
  m(bypass) \
  m(time) \
  m(assert) \
  m(print) \
  m(udfc) \
  m(udfs) \
  m(udfin) \
  m(udfout)

namespace ch {
namespace internal {
  
class context;
class cdimpl;
struct sloc_ctx_t;

enum lnodetype {
  CH_LNODE_ENUM(CH_LNODE_TYPE)
};

using clone_map = std::unordered_map<uint32_t, lnodeimpl*>;

class lnodeimpl : public refcounted {
public:

  uint32_t id() const {
    return id_;
  }
  
  lnodetype type() const {
    return type_;
  }

  const std::string& name() const {
    return name_;
  }

  void set_name(const std::string& name) {
    name_ = name;
  }

  const source_info& sloc() const {
    return sloc_;
  }

  void set_sloc(const source_info& sloc) {
    sloc_ = sloc;
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

  void set_src(uint32_t index, lnodeimpl* src);

  uint32_t add_src(lnodeimpl* src);

  void insert_src(uint32_t index, lnodeimpl* src);

  lnodeimpl* remove_src(uint32_t index);

  uint32_t size() const {
    return size_;
  }

  size_t hash() const;

  void resize(uint32_t size);

  virtual lnodeimpl* clone(context* ctx, const clone_map& cloned_nodes) const = 0;

  virtual bool equals(const lnodeimpl& other) const;

  virtual lnodeimpl* slice(uint32_t offset,
                           uint32_t length,
                           const source_info& sloc) const;

  auto users() const {
   return users_;
  }

  bool has_user(lnode* user) const;

  void add_user(lnode* user);

  void replace_uses(lnodeimpl* node);

  void remove_user(lnode* user);

  virtual void print(std::ostream& out) const;

  std::string debug_info() const;

protected:

  lnodeimpl(uint32_t id,
            lnodetype type,
            uint32_t size,
            context* ctx,
            const std::string& name,
            const source_info& sloc);

  virtual ~lnodeimpl();

  const uint32_t id_;
  const lnodetype type_;

private:

  uint32_t size_;

protected:

  context* ctx_;
  std::string name_;
  source_info sloc_;
  mutable size_t hash_;

private:

  std::vector<lnode> srcs_;

  lnodeimpl* prev_;
  lnodeimpl* next_;
  lnode* users_;

  friend class context;
  friend class node_list;
};

const char* to_string(lnodetype type);

std::ostream& operator<<(std::ostream& out, lnodetype type);

}
}
