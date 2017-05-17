#pragma once

#include "bit.h"
#include "arithm.h"

namespace cash_internal {

class ch_real : public ch_bit<32> {
public:
  using base = ch_bit<32>;
  using bitstream_type = typename base::bitstream_type;
  using bus_type = ch_bus<32>;  
  using base::operator=;
  using base::base;
  
  ch_real() {}
  ch_real(const ch_real& rhs) : base(rhs) {}
  ch_real(float rhs) : base(bit_cast<uint32_t, float>(rhs)) {}
  
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
  return ch_real(createAluNode(alu_op_fadd, 32, lhs.get_node().get_impl(), rhs.get_node().get_impl()));
}

inline ch_real operator-(const ch_real& lhs, const ch_real& rhs) {
  return ch_real(createAluNode(alu_op_fsub, 32, lhs.get_node().get_impl(), rhs.get_node().get_impl()));
}

inline ch_real operator*(const ch_real& lhs, const ch_real& rhs) {
  return ch_real(createAluNode(alu_op_fmult, 32, lhs.get_node().get_impl(), rhs.get_node().get_impl()));
}

inline ch_real operator/(const ch_real& lhs, const ch_real& rhs) {
  return ch_real(createAluNode(alu_op_fdiv, 32, lhs.get_node().get_impl(), rhs.get_node().get_impl()));
}

}
