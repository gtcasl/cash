#pragma once

#include "int.h"
#include "arithm.h"

namespace ch {
namespace internal {

class ch_float32 : public ch_int<32> {
public:  
  using traits = logic_traits<32, true, ch_float32, ch_int<32>>;
  using base = ch_int<32>;

  ch_float32(const logic_buffer_ptr& buffer = make_logic_buffer(32, CH_SRC_LOCATION))
    : base(buffer)
  {}

  ch_float32(const ch_float32& rhs,
             const source_location& sloc = CH_SRC_LOCATION)
    : base(rhs, sloc)
  {}

  ch_float32(ch_float32&& rhs) : base(std::move(rhs)) {}

  explicit ch_float32(const ch_logic<32>& rhs,
                      const source_location& sloc = CH_SRC_LOCATION)
    : base(rhs, sloc)
  {}

  explicit ch_float32(const ch_scalar<32>& rhs,
                      const source_location& sloc = CH_SRC_LOCATION)
    : base(rhs, sloc)
  {}

  explicit ch_float32(float rhs,
                      const source_location& sloc = CH_SRC_LOCATION)
    : base(bitcast<uint32_t, float>(rhs), sloc)
  {}

  ch_float32& operator=(const ch_float32& rhs) {
    base::operator=(rhs);
    return *this;
  }

  ch_float32& operator=(ch_float32&& rhs) {
    base::operator=(std::move(rhs));
    return *this;
  }

  ch_float32& operator=(float rhs) {
    base::operator=(bitcast<uint32_t, float>(rhs));
    return *this;
  }

  // compare operators

  auto operator<(const ch_float32& rhs) const {
    return base::operator<(rhs);
  }

  auto operator<=(const ch_float32& rhs) const {
    return base::operator<=(rhs);
  }

  auto operator>(const ch_float32& rhs) const {
    return base::operator>(rhs);
  }

  auto operator>=(const ch_float32& rhs) const {
    return base::operator>=(rhs);
  }

  // arithmetic operators

  auto operator+(const ch_float32& rhs) const {
    auto ret = createAluNode(op_fadd, 32, get_lnode(*this), get_lnode(rhs));
    return make_type<ch_float32>(ret);
  }

  auto operator-(const ch_float32& rhs) const {
    auto ret = createAluNode(op_fsub, 32, get_lnode(*this), get_lnode(rhs));
    return make_type<ch_float32>(ret);
  }

  auto operator*(const ch_float32& rhs) const {
    auto ret = createAluNode(op_fmult, 32, get_lnode(*this), get_lnode(rhs));
    return make_type<ch_float32>(ret);
  }

  auto operator/(const ch_float32& rhs) const {
    auto ret = createAluNode(op_fdiv, 32, get_lnode(*this), get_lnode(rhs));
    return make_type<ch_float32>(ret);
  }

protected:

  CH_FRIEND_OP1((), ==, const ch_float32&, float)
  CH_FRIEND_OP1((), !=, const ch_float32&, float)
  CH_FRIEND_OP1((), <, const ch_float32&, float)
  CH_FRIEND_OP1((), <=, const ch_float32&, float)
  CH_FRIEND_OP1((), >, const ch_float32&, float)
  CH_FRIEND_OP1((), >=, const ch_float32&, float)

  CH_FRIEND_OP1((), +, const ch_float32&, float)
  CH_FRIEND_OP1((), -, const ch_float32&, float)
  CH_FRIEND_OP1((), *, const ch_float32&, float)
  CH_FRIEND_OP1((), /, const ch_float32&, float)
};

template <unsigned Delay>
auto ch_fadd(const ch_float32& lhs, const ch_float32& rhs, const ch_logic<1>& enable = ch_logic<1>(true)) {
  auto ret = createAluNode(op_fadd, 32, Delay, get_lnode(enable), get_lnode(lhs), get_lnode(rhs));
  return make_type<ch_float32>(ret);
}

template <unsigned Delay>
auto ch_fsub(const ch_float32& lhs, const ch_float32& rhs, const ch_logic<1>& enable = ch_logic<1>(true)) {
  auto ret = createAluNode(op_fsub, 32, Delay, get_lnode(enable), get_lnode(lhs), get_lnode(rhs));
  return make_type<ch_float32>(ret);
}

template <unsigned Delay>
auto ch_fmult(const ch_float32& lhs, const ch_float32& rhs, const ch_logic<1>& enable = ch_logic<1>(true)) {
  auto ret = createAluNode(op_fmult, 32, Delay, get_lnode(enable), get_lnode(lhs), get_lnode(rhs));
  return make_type<ch_float32>(ret);
}

template <unsigned Delay>
auto ch_fdiv(const ch_float32& lhs, const ch_float32& rhs, const ch_logic<1>& enable = ch_logic<1>(true)) {
  auto ret = createAluNode(op_fdiv, 32, Delay, get_lnode(enable), get_lnode(lhs), get_lnode(rhs));
  return make_type<ch_float32>(ret);
}

}
}
