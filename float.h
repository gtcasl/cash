#pragma once

#include "bit.h"
#include "arithm.h"

namespace chdl_internal {

class ch_float : public ch_bit<32> {
public:
  using base = ch_bit<32>;
  using bitstream_type = typename base::bitstream_type;
  using bus_type = ch_bus<32>;  
  using base::operator=;
  using base::base;
  
  ch_float() {}
  ch_float(const ch_float& rhs) : base(rhs) {}
  ch_float(float rhs) : base(bit_cast<uint32_t, float>(rhs)) {}
  
  ch_float& operator=(const ch_float& rhs) {
    base::operator =(rhs);
    return *this;
  }
  
  ch_float& operator=(float rhs) {
    base::operator =(ch_float(rhs));
    return *this;
  }
};

inline ch_float operator+(const ch_float& lhs, const ch_float& rhs) {
  return ch_float(createAluNode(alu_op_fadd, 32, lhs.get_node().get_impl(), rhs.get_node().get_impl()));
}

inline ch_float operator-(const ch_float& lhs, const ch_float& rhs) {
  return ch_float(createAluNode(alu_op_fsub, 32, lhs.get_node().get_impl(), rhs.get_node().get_impl()));
}

inline ch_float operator*(const ch_float& lhs, const ch_float& rhs) {
  return ch_float(createAluNode(alu_op_fmult, 32, lhs.get_node().get_impl(), rhs.get_node().get_impl()));
}

inline ch_float operator/(const ch_float& lhs, const ch_float& rhs) {
  return ch_float(createAluNode(alu_op_fdiv, 32, lhs.get_node().get_impl(), rhs.get_node().get_impl()));
}

}
