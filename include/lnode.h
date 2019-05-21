#pragma once

#include "traits.h"

namespace ch {
namespace internal {

#define CH_OP_TYPE(n, v) n = v,
#define CH_OP_NAME(n, v) #n,
#define CH_OP_INDEX(op)  ((int)op & 0x1f)
#define CH_OP_ENUM(m) \
  m(eq,     0 | op_flags::binary | op_flags::equality | op_flags::symmetric | op_flags::resize_src) \
  m(ne,     1 | op_flags::binary | op_flags::equality | op_flags::symmetric | op_flags::resize_src) \
  m(lt,     2 | op_flags::binary | op_flags::relational | op_flags::symmetric | op_flags::resize_src | op_flags::is_signed) \
  m(gt,     3 | op_flags::binary | op_flags::relational | op_flags::symmetric | op_flags::resize_src | op_flags::is_signed) \
  m(le,     4 | op_flags::binary | op_flags::relational | op_flags::symmetric | op_flags::resize_src | op_flags::is_signed) \
  m(ge,     5 | op_flags::binary | op_flags::relational | op_flags::symmetric | op_flags::resize_src | op_flags::is_signed) \
  m(notl,   6 | op_flags::unary  | op_flags::logical) \
  m(andl,   7 | op_flags::binary | op_flags::logical | op_flags::symmetric) \
  m(orl,    8 | op_flags::binary | op_flags::logical | op_flags::symmetric) \
  m(inv,    9 | op_flags::unary  | op_flags::bitwise | op_flags::resize_dst) \
  m(andb,  10 | op_flags::binary | op_flags::bitwise | op_flags::symmetric | op_flags::resize_dst) \
  m(orb,   11 | op_flags::binary | op_flags::bitwise | op_flags::symmetric | op_flags::resize_dst) \
  m(xorb,  12 | op_flags::binary | op_flags::bitwise | op_flags::symmetric | op_flags::resize_dst) \
  m(andr,  13 | op_flags::unary  | op_flags::reduce) \
  m(orr,   14 | op_flags::unary  | op_flags::reduce) \
  m(xorr,  15 | op_flags::unary  | op_flags::reduce) \
  m(shl,   16 | op_flags::binary | op_flags::shift) \
  m(shr,   17 | op_flags::binary | op_flags::shift | op_flags::is_signed) \
  m(neg,   18 | op_flags::unary  | op_flags::arithmetic | op_flags::resize_dst | op_flags::is_signed) \
  m(add,   19 | op_flags::binary | op_flags::arithmetic | op_flags::symmetric | op_flags::resize_dst | op_flags::is_signed) \
  m(sub,   20 | op_flags::binary | op_flags::arithmetic | op_flags::resize_dst | op_flags::is_signed) \
  m(mul,   21 | op_flags::binary | op_flags::arithmetic | op_flags::symmetric | op_flags::is_signed) \
  m(div,   22 | op_flags::binary | op_flags::arithmetic | op_flags::is_signed) \
  m(mod,   23 | op_flags::binary | op_flags::arithmetic | op_flags::is_signed) \
  m(pad,   24 | op_flags::unary  | op_flags::misc | op_flags::is_signed)

enum class op_flags {
  unary      = 0 << 5,
  binary     = 1 << 5,
  equality   = 0 << 6,
  relational = 1 << 6,
  logical    = 2 << 6,
  bitwise    = 3 << 6,
  shift      = 4 << 6,
  arithmetic = 5 << 6,
  reduce     = 6 << 6,
  misc       = 7 << 6,
  resize_src = 1 << 9,
  resize_dst = 2 << 9,
  symmetric  = 1 << 11,
  is_signed  = 1 << 12,
};

#define CH_OP_ARY(x)    op_flags((int)x & (0x1 << 5))
#define CH_OP_CLASS(x)  op_flags((int)x & (0x7 << 6))
#define CH_OP_RESIZE(x) op_flags((int)x & (0x3 << 9))
#define CH_OP_PROP(x)   op_flags((int)x & ~((1<<11)-1))

inline constexpr auto operator|(op_flags lsh, op_flags rhs) {
  return (int)lsh | (int)rhs;
}

inline constexpr auto operator|(int lsh, op_flags rhs) {
  return lsh | (int)rhs;
}

inline constexpr auto operator|(op_flags lsh, int rhs) {
  return (int)lsh | rhs;
}

inline constexpr auto operator&(op_flags lsh, op_flags rhs) {
  return (int)lsh & (int)rhs;
}

enum class ch_op {
  CH_OP_ENUM(CH_OP_TYPE)
};

const char* to_string(ch_op op);

std::ostream& operator<<(std::ostream& out, ch_op op);

using ch_tick = uint64_t;

template <typename T>
auto idname(bool remove_template_params = false) {
  return identifier_from_typeid(typeid(T).name(), remove_template_params);
}

///////////////////////////////////////////////////////////////////////////////

bool register_source_location(uint32_t level);
void release_source_location();

class sloc_getter {
public:
  sloc_getter(uint32_t level = 1) {
    owned_ = register_source_location(level+1);
  }
  ~sloc_getter() {
    if (owned_) {
      release_source_location();
    }
  }
private:
  bool owned_;
};

#define CH_SOURCE_LOCATION(level) ch::internal::sloc_getter __sloc_getter__(level)

///////////////////////////////////////////////////////////////////////////////

class lnodeimpl;

class lnode {
public:

  lnode(lnodeimpl* impl = nullptr) : impl_(impl) {}

  lnode(const sdata_type& value);

  lnode(uint32_t size, const std::string& name);

  lnode(const lnode& src, const std::string& name);

  lnode(const lnode& other) : impl_(other.impl_) {}

  lnode& operator=(const lnode& other) {
    impl_ = other.impl_;
    return *this;
  }

  bool empty() const {
    return (nullptr == impl_);
  }

  lnodeimpl* impl() const;

  uint32_t id() const;

  const std::string& name() const;
  
  uint32_t size() const;

  const source_location& sloc() const;

  void write(uint32_t dst_offset,
             const lnode& in,
             uint32_t src_offset,
             uint32_t length);

  inline friend bool operator==(const lnode& lhs, const lnode& rhs) {
    return lhs.id() == rhs.id();
  }

  inline friend bool operator!=(const lnode& lhs, const lnode& rhs) {
    return lhs.id() != rhs.id();
  }

  inline friend bool operator<(const lnode& lhs, const lnode& rhs) {
    return lhs.id() < rhs.id();
  }

protected:

  mutable lnodeimpl* impl_;
};

}
}
