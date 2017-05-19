#pragma once

#include "bit.h"
#include "arithm.h"

namespace cash {
namespace detail {

class ch_real : public ch_bit<32> {
public:
  using base = ch_bit<32>;
  using data_type = typename base::data_type;
  using bus_type = ch_bus<32>;  
  using base::operator=;
  using base::base;
  
  ch_real() {}
  ch_real(const ch_real& rhs) : base(rhs) {}
  ch_real(float rhs) : base(bitcast<uint32_t, float>(rhs)) {}
  
  ch_real& operator=(const ch_real& rhs) {
    base::operator =(rhs);
    return *this;
  }
  
  ch_real& operator=(float rhs) {
    base::operator =(ch_real(rhs));
    return *this;
  }
};

inline ch_real operator+(const ch_real& lhs, const ch_real& rhs) {
  return ch_real(createAluNode(alu_op_fadd, 32, get_node(lhs).get_impl(), get_node(rhs).get_impl()));
}

inline ch_real operator-(const ch_real& lhs, const ch_real& rhs) {
  return ch_real(createAluNode(alu_op_fsub, 32, get_node(lhs).get_impl(), get_node(rhs).get_impl()));
}

inline ch_real operator*(const ch_real& lhs, const ch_real& rhs) {
  return ch_real(createAluNode(alu_op_fmult, 32, get_node(lhs).get_impl(), get_node(rhs).get_impl()));
}

inline ch_real operator/(const ch_real& lhs, const ch_real& rhs) {
  return ch_real(createAluNode(alu_op_fdiv, 32, get_node(lhs).get_impl(), get_node(rhs).get_impl()));
}

}
}
