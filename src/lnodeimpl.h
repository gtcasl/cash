#pragma once

#include "lnode.h"

#define CH_OPERATOR_TYPE(t) op_##t,
#define CH_OPERATOR_NAME(n) #n,
#define CH_OPERATOR_ENUM(m) \
  m(undef) \
  m(proxy) \
  m(lit) \
  m(input) \
  m(output) \
  m(clk) \
  m(reset) \
  m(alu) \
  m(select) \
  m(reg) \
  m(mem) \
  m(memport) \
  m(tap) \
  m(assert) \
  m(tick) \
  m(print)

namespace cash {
namespace internal {
  
enum ch_operator {
  CH_OPERATOR_ENUM(CH_OPERATOR_TYPE)
};

class lnodeimpl {
public:
  lnodeimpl(ch_operator op, context* ctx, uint32_t size);
  virtual ~lnodeimpl();
  
  uint32_t get_id() const {
    return id_;
  }
  
  ch_operator get_op() const {
    return op_;
  }

  context* get_ctx() const {
    return ctx_;
  }

  uint32_t get_num_srcs() const {
    return srcs_.size();
  }

  const std::vector<lnode>& get_srcs() const {
    return srcs_;
  }
  
  std::vector<lnode>& get_srcs() {
    return srcs_;
  }
  
  const lnode& get_src(unsigned i) const {
    assert(i < srcs_.size());
    return srcs_[i];
  }
  
  const lnode& get_src(unsigned i) {
    assert(i < srcs_.size());
    return srcs_[i];
  }
  
  uint32_t get_size() const {
    return value_.get_size();
  }
  
  const bitvector& get_value() const { 
    return value_;
  }
  
  void set_value(const bitvector& value) {
    value_ = value;
  }

  bool get_bool(unsigned i) const {
    return value_[i];
  }

  void set_bool(unsigned i, bool value) {
    value_[i] = value;
  }

  void read_bytes(uint32_t dst_offset, void* out, uint32_t out_cbsize, uint32_t src_offset, uint32_t size) const {
    value_.read(dst_offset, out, out_cbsize, src_offset, size);
  }

  void write_bytes(uint32_t dst_offset, const void* in, uint32_t in_cbsize, uint32_t src_offset, uint32_t size) {
    value_.write(dst_offset, in, in_cbsize, src_offset, size);
  }

  virtual lnodeimpl* get_slice(uint32_t offset, uint32_t length);
  
  virtual bool ready() const;
  virtual bool valid() const;  
  virtual const bitvector& eval(ch_tick t) = 0;
  
  virtual void print(std::ostream& out, uint32_t level) const;

protected:
  
  uint32_t id_;
  ch_operator op_;
  context* ctx_;
  std::vector<lnode> srcs_;
  bitvector value_; 
  
  friend class context;
};

class undefimpl : public lnodeimpl {
public:
  undefimpl(context* ctx, uint32_t size);

  const bitvector& eval(ch_tick t) override;
};

const char* to_string(ch_operator op);

std::ostream& operator<<(std::ostream& out, ch_operator op);

}
}
