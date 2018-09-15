#pragma once

#include "bitvector.h"

namespace ch {
namespace internal {

#define CH_OP_ARY(x)   op_flags((int)x & (0x1 << 5))
#define CH_OP_CLASS(x) op_flags((int)x & (0x7 << 6))

#define CH_OP_TYPE(n, v) n = v,
#define CH_OP_NAME(n, v) #n,
#define CH_OP_INDEX(op)  ((int)op & 0x1f)
#define CH_OP_ENUM(m) \
  m(eq,     0 | op_flags::binary | op_flags::equality | op_flags::symmetric) \
  m(ne,     1 | op_flags::binary | op_flags::equality | op_flags::symmetric) \
  m(lt,     2 | op_flags::binary | op_flags::relational) \
  m(gt,     3 | op_flags::binary | op_flags::relational) \
  m(le,     4 | op_flags::binary | op_flags::relational) \
  m(ge,     5 | op_flags::binary | op_flags::relational) \
  m(notl,   6 | op_flags::unary  | op_flags::logical) \
  m(andl,   7 | op_flags::binary | op_flags::logical | op_flags::symmetric) \
  m(orl,    8 | op_flags::binary | op_flags::logical | op_flags::symmetric) \
  m(inv,    9 | op_flags::unary  | op_flags::bitwise) \
  m(andb,  10 | op_flags::binary | op_flags::bitwise | op_flags::symmetric) \
  m(orb,   11 | op_flags::binary | op_flags::bitwise | op_flags::symmetric) \
  m(xorb,  12 | op_flags::binary | op_flags::bitwise | op_flags::symmetric) \
  m(andr,  13 | op_flags::unary  | op_flags::reduce) \
  m(orr,   14 | op_flags::unary  | op_flags::reduce) \
  m(xorr,  15 | op_flags::unary  | op_flags::reduce) \
  m(shl,   16 | op_flags::binary | op_flags::shift) \
  m(shr,   17 | op_flags::binary | op_flags::shift) \
  m(neg,   18 | op_flags::unary  | op_flags::arithmetic) \
  m(add,   19 | op_flags::binary | op_flags::arithmetic | op_flags::symmetric) \
  m(sub,   20 | op_flags::binary | op_flags::arithmetic) \
  m(mul ,  21 | op_flags::binary | op_flags::arithmetic | op_flags::symmetric) \
  m(div,   22 | op_flags::binary | op_flags::arithmetic) \
  m(mod,   23 | op_flags::binary | op_flags::arithmetic) \
  m(pad,   24 | op_flags::unary  | op_flags::misc)

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
  symmetric  = 1 << 9,
};

inline constexpr auto operator|(op_flags lsh, op_flags rhs) {
  return (int)lsh | (int)rhs;
}

inline constexpr auto operator|(int lsh, op_flags rhs) {
  return lsh | (int)rhs;
}

inline constexpr auto operator|(op_flags lsh, int rhs) {
  return (int)lsh | rhs;
}

enum class ch_op {
  CH_OP_ENUM(CH_OP_TYPE)
};

const char* to_string(ch_op op);

///////////////////////////////////////////////////////////////////////////////

using ch_tick = uint64_t;

class lnodeimpl;

class lnode {
public:

  lnode() : impl_(nullptr) {}

  lnode(lnodeimpl* impl) : impl_(impl) {
    assert(impl);
  }

  lnode(const bitvector& value);

  lnode(uint32_t size,
        const source_location& sloc,
        const std::string& name = "",
        uint32_t var_id = 0);

  lnode(const lnode& src,
        const source_location& sloc,
        const std::string& name = "",
        uint32_t var_id = 0);

  lnode(uint32_t size,
        const lnode& src,
        uint32_t src_offset,
        const source_location& sloc,
        const std::string& name = "",
        uint32_t var_id = 0);

  lnode(const lnode& other) : impl_(other.impl_) {}

  lnode& operator=(const lnode& other) {
    impl_ = other.impl_;
    return *this;
  }

  void write(uint32_t dst_offset,
             const lnode& in,
             uint32_t src_offset,
             uint32_t length,
             const source_location& sloc);

  bool empty() const {
    return (nullptr == impl_);
  }

  lnodeimpl* impl() const;
  
  uint32_t id() const;

  const std::string& name() const;
  
  uint32_t size() const;

  const bitvector& data() const;

  bitvector& data();

  uint32_t var_id() const;

  void set_var_id(uint32_t var_id);

  const source_location& sloc() const;

  lnodeimpl* clone(const source_location& sloc) const;

protected:

  mutable lnodeimpl* impl_;

  inline friend bool operator==(const lnode& lhs, const lnode& rhs) {
    return lhs.id() == rhs.id();
  }

  inline friend bool operator!=(const lnode& lhs, const lnode& rhs) {
    return lhs.id() != rhs.id();
  }

  inline friend bool operator<(const lnode& lhs, const lnode& rhs) {
    return lhs.id() < rhs.id();
  }
};

}
}
