#include "simref.h"
#include "bindimpl.h"
#include "litimpl.h"
#include "regimpl.h"
#include "memimpl.h"
#include "ioimpl.h"
#include "selectimpl.h"
#include "proxyimpl.h"
#include "memimpl.h"
#include "aluimpl.h"
#include "assertimpl.h"
#include "printimpl.h"
#include "timeimpl.h"
#include "udfimpl.h"

using namespace ch::internal;

using instr_map_t = std::unordered_map<uint32_t, const block_type*>;

class instr_proxy : public instr_base {
private:

  struct range_t {
    const block_type* src_data;
    uint32_t src_offset;
    uint32_t dst_offset;
    uint32_t length;
  };

  const range_t* ranges_;
  uint32_t num_ranges_;
  block_type* dst_;

  instr_proxy(const range_t* ranges, uint32_t num_ranges, block_type* dst)
    : ranges_(ranges)
    , num_ranges_(num_ranges)
    , dst_(dst)
  {}

public:

  static instr_proxy* create(proxyimpl* node, instr_map_t& map) {
    uint32_t dst_size = node->size();
    uint32_t dst_nblocks = ceildiv<uint32_t>(dst_size, bitwidth_v<block_type>);
    uint32_t dst_bytes = sizeof(block_type) * dst_nblocks;
    uint32_t num_ranges = node->ranges().size();

    uint32_t range_bytes = 0;
    for (uint32_t i = 0; i < num_ranges; ++i) {
      range_bytes += sizeof(range_t);
    }

    auto buf = new uint8_t[sizeof(instr_proxy) + dst_bytes + range_bytes]();
    auto buf_cur = buf + sizeof(instr_proxy);
    auto dst = (block_type*)buf_cur;
    map[node->id()] = dst;

    buf_cur += dst_bytes;

    auto ranges = (range_t*)buf_cur;
    for (uint32_t i = 0; i < num_ranges; ++i) {
      auto& dst_range = ranges[i];
      auto& src_range = node->range(i);
      auto& src = node->src(src_range.src_idx);
      dst_range.src_data   = map.at(src.id());
      dst_range.src_offset = src_range.src_offset;
      dst_range.dst_offset = src_range.dst_offset;
      dst_range.length     = src_range.length;
    }

    return new (buf) instr_proxy(ranges, num_ranges, dst);
  }

  void destroy () override {
    this->~instr_proxy();
    ::operator delete [](this);
  }

  void eval() override {
    for (const range_t *r = ranges_, *r_end = r + num_ranges_ ;r != r_end; ++r) {
      bv_copy(dst_, r->dst_offset, r->src_data, r->src_offset, r->length);
    }
  }
};


///////////////////////////////////////////////////////////////////////////////

class instr_output : public instr_base {
public:

  static instr_output* create(outputimpl* node, instr_map_t& map) {
    return new instr_output(node, map);
  }

  void destroy () override {
    delete this;
  }

  void eval() override {
    bv_copy(dst_, src_, size_);
  }

private:

  instr_output(outputimpl* node, instr_map_t& map)
    : src_(map.at(node->src(0).id()))
    , dst_(node->value().words())
    , size_(node->size())
  {}

  const block_type* src_;
  block_type* dst_;
  uint32_t size_;
};

///////////////////////////////////////////////////////////////////////////////

class instr_alu_base : public instr_base {
public:

  static instr_alu_base* create(aluimpl* node, instr_map_t& map);

protected:

  instr_alu_base(const block_type* o_src0,
                 uint32_t o_src0_size,
                 const block_type* o_src1,
                 uint32_t o_src1_size,
                 block_type* src0,
                 uint32_t src0_size,
                 block_type* src1,
                 uint32_t src1_size,
                 block_type* dst,
                 uint32_t dst_size)
    : o_src0_(o_src0)
    , o_src0_size_(o_src0_size)
    , o_src1_(o_src1)
    , o_src1_size_(o_src1_size)
    , src0_(src0)
    , src0_size_(src0_size)
    , src1_(src1)
    , src1_size_(src1_size)
    , dst_(dst)
    , dst_size_(dst_size)
  {}

  const block_type* o_src0_;
  uint32_t o_src0_size_;
  const block_type* o_src1_;
  uint32_t o_src1_size_;
  block_type* src0_;
  uint32_t src0_size_;
  block_type* src1_;
  uint32_t src1_size_;
  block_type* dst_;
  uint32_t dst_size_;
};

template <ch_op op, bool is_signed, bool resize_opds>
class instr_alu : instr_alu_base {
public:

  void destroy () override {
    this->~instr_alu();
    ::operator delete [](this);
  }

  void eval() override {
    if constexpr (resize_opds) {
      if (src0_size_ != o_src0_size_) {
        if constexpr (is_signed) {
          bv_sext(src0_, src0_size_, o_src0_, o_src0_size_);
        } else {
          bv_zext(src0_, src0_size_, o_src0_, o_src0_size_);
        }
      }
      if (src1_size_ != o_src1_size_) {
        if constexpr (is_signed) {
          bv_sext(src1_, src1_size_, o_src1_, o_src1_size_);
        } else {
          bv_zext(src1_, src1_size_, o_src1_, o_src1_size_);
        }
      }
    }

    switch (op) {
    case ch_op::eq:
      bv_assign(dst_, dst_size_, bv_eq(src0_,  src1_, src0_size_));
      break;
    case ch_op::ne:
      bv_assign(dst_, dst_size_, !bv_eq(src0_,  src1_, src0_size_));
      break;
    case ch_op::lt:
      if constexpr (is_signed) {
        bv_assign(dst_, dst_size_, bv_slt(src0_,  src1_, src0_size_));
      } else {
        bv_assign(dst_, dst_size_, bv_ult(src0_,  src1_, src0_size_));
      }
      break;
    case ch_op::gt:
      if constexpr (is_signed) {
        bv_assign(dst_, dst_size_, bv_slt(src1_,  src0_, src0_size_));
      } else {
        bv_assign(dst_, dst_size_, bv_ult(src1_,  src0_, src0_size_));
      }
      break;
    case ch_op::le:
      if constexpr (is_signed) {
        bv_assign(dst_, dst_size_, !bv_slt(src1_,  src0_, src0_size_));
      } else {
        bv_assign(dst_, dst_size_, !bv_ult(src1_,  src0_, src0_size_));
      }
      break;
    case ch_op::ge:
      if constexpr (is_signed) {
        bv_assign(dst_, dst_size_, !bv_slt(src0_,  src1_, src0_size_));
      } else {
        bv_assign(dst_, dst_size_, !bv_ult(src0_,  src1_, src0_size_));
      }
      break;

    case ch_op::notl:
      bv_assign(dst_, dst_size_, !bv_orr(src0_, src0_size_));
      break;
    case ch_op::andl:
      bv_assign(dst_, dst_size_, bv_orr(src0_, src0_size_) && bv_orr(src1_, src1_size_));
      break;
    case ch_op::orl:
      bv_assign(dst_, dst_size_, bv_orr(src0_, src0_size_) || bv_orr(src1_, src1_size_));
      break;

    case ch_op::inv:
      bv_inv(dst_, src0_, dst_size_);
      break;
    case ch_op::andb:
      bv_and(dst_, src0_, src1_, dst_size_);
      break;
    case ch_op::orb:
      bv_or(dst_, src0_, src1_, dst_size_);
      break;
    case ch_op::xorb:
      bv_xor(dst_, src0_, src1_, dst_size_);
      break;

    case ch_op::andr:
      bv_assign(dst_, dst_size_, bv_andr(src0_, src0_size_));
      break;
    case ch_op::orr:
      bv_assign(dst_, dst_size_, bv_orr(src0_, src0_size_));
      break;
    case ch_op::xorr:
      bv_assign(dst_, dst_size_, bv_xorr(src0_, src0_size_));
      break;

    case ch_op::shl:
      bv_sll(dst_, dst_size_, src0_, src0_size_, bv_cast<uint32_t>(src1_, src1_size_));
      break;
    case ch_op::shr:
      if constexpr (is_signed) {
        bv_sra(dst_, dst_size_, src0_, src0_size_, bv_cast<uint32_t>(src1_, src1_size_));
      } else {
        bv_srl(dst_, dst_size_, src0_, src0_size_, bv_cast<uint32_t>(src1_, src1_size_));
      }
      break;

    case ch_op::add:
      bv_add(dst_, src0_, src1_, dst_size_);
      break;
    case ch_op::sub:
      bv_sub(dst_, src0_, src1_, dst_size_);
      break;
    case ch_op::neg:
      bv_neg(dst_, src0_, dst_size_);
      break;
    case ch_op::mult:
      bv_mult(dst_, dst_size_, src0_, src0_size_, src1_, src1_size_);
      break;
    case ch_op::div:
      if constexpr (is_signed) {
        bv_sdiv(dst_, dst_size_, src0_, src0_size_, src1_, src1_size_);
      } else {
        bv_udiv(dst_, dst_size_, src0_, src0_size_, src1_, src1_size_);
      }
      break;
    case ch_op::mod:
      if constexpr (is_signed) {
        bv_smod(dst_, dst_size_, src0_, src0_size_, src1_, src1_size_);
      } else {
        bv_umod(dst_, dst_size_, src0_, src0_size_, src1_, src1_size_);
      }
      break;

    case ch_op::pad:
      if constexpr (is_signed) {
        bv_sext(dst_, dst_size_, src0_, src0_size_);
      } else {
        bv_zext(dst_, dst_size_, src0_, src0_size_);
      }
      break;

    default:
      CH_ABORT("invalid opcode");
    }
  }

private:

  instr_alu(const block_type* o_src0,
            uint32_t o_src0_size_,
            const block_type* o_src1,
            uint32_t o_src1_size,
            block_type* src0,
            uint32_t src0_size_,
            block_type* src1,
            uint32_t src1_size,
            block_type* dst,
            uint32_t dst_size_)
    : instr_alu_base(o_src0, o_src0_size_,
                     o_src1, o_src1_size,
                     src0, src0_size_,
                     src1, src1_size,
                     dst, dst_size_)
    {}

  friend class instr_alu_base;
};

instr_alu_base* instr_alu_base::create(aluimpl* node, instr_map_t& map) {
  uint32_t dst_size = node->size();

  const block_type* o_src0 = nullptr;
  uint32_t o_src0_size = 0;
  const block_type* o_src1 = nullptr;
  uint32_t o_src1_size = 0;

  // access source node data
  if (node->srcs().size() > 0) {
    o_src0 = map.at(node->src(0).id());
    o_src0_size = node->src(0).size();
    if (node->srcs().size() > 1) {
      o_src1 = map.at(node->src(1).id());
      o_src1_size = node->src(1).size();
    }
  }

  block_type* src0 = (block_type*)o_src0;
  uint32_t src0_size = o_src0_size;
  block_type* src1 = (block_type*)o_src1;
  uint32_t src1_size = o_src1_size;

  bool resize_opds = false;

  // allocate shadow buffers if needed
  auto op = node->op();
  auto op_prop = CH_OP_PROP(op);
  if (op_prop & op_flags::eq_opd_size) {
    auto op_class = CH_OP_CLASS(op);
    if (op_flags::equality == op_class
     || op_flags::relational == op_class) {
      // resize source operands to match each other
      if (src0_size != src1_size) {
        if (src0_size < src1_size) {
          src0_size = src1_size;
        } else {
          src1_size = src0_size;
        }
        resize_opds = true;
      }
    } else {
      // resize source operands to match destination
      if (src0_size != dst_size) {
        if (src0_size < dst_size) {
          resize_opds = true;
        }
        src0_size = dst_size;
      }
      if (src1 && src1_size != dst_size) {
        if (src1_size < dst_size) {
          resize_opds = true;
        }
        src1_size = dst_size;
      }
    }
  }

  uint32_t dst_bytes = sizeof(block_type) * ceildiv<uint32_t>(dst_size, bitwidth_v<block_type>);

  uint32_t t_src0_bytes = 0;
  if (src0_size != o_src0_size) {
    t_src0_bytes = sizeof(block_type) * ceildiv<uint32_t>(src0_size, bitwidth_v<block_type>);
  }

  uint32_t t_src1_bytes = 0;
  if (src1_size != o_src1_size) {
    t_src1_bytes = sizeof(block_type) * ceildiv<uint32_t>(src1_size, bitwidth_v<block_type>);
  }

  auto buf = new uint8_t[sizeof(instr_alu_base) + dst_bytes + t_src0_bytes + t_src1_bytes]();
  auto buf_cur = buf + sizeof(instr_alu_base);
  auto dst = (block_type*)buf_cur;
  map[node->id()] = dst;

  buf_cur += dst_bytes;

  if (t_src0_bytes) {
    src0 = (block_type*)buf_cur;
    buf_cur += t_src0_bytes;
  }

  if (t_src1_bytes) {
    src1 = (block_type*)buf_cur;
    buf_cur += t_src1_bytes;
  }

  bool is_signed = node->is_signed();

#define CREATE_ALU_INST(op, sign_enable, resize_enable) \
  case op: \
    if (sign_enable && is_signed) { \
      if (resize_enable && resize_opds) { \
        return new (buf) instr_alu<op, true, true>(o_src0, o_src0_size, \
                                                   o_src1, o_src1_size, src0, src0_size, \
                                                   src1, src1_size, dst, dst_size); \
      } else { \
        return new (buf) instr_alu<op, true, false>(o_src0, o_src0_size, \
                                                    o_src1, o_src1_size, src0, src0_size, \
                                                    src1, src1_size, dst, dst_size); \
      }  \
    } else { \
      if (resize_enable && resize_opds) { \
        return new (buf) instr_alu<op, false, true>(o_src0, o_src0_size, \
                                                    o_src1, o_src1_size, src0, src0_size, \
                                                    src1, src1_size, dst, dst_size); \
      } else { \
        return new (buf) instr_alu<op, false, false>(o_src0, o_src0_size, \
                                                     o_src1, o_src1_size, src0, src0_size, \
                                                     src1, src1_size, dst, dst_size); \
      } \
    }

  switch (node->op()) {
  CREATE_ALU_INST(ch_op::eq, true, true);
  CREATE_ALU_INST(ch_op::ne, true, true);
  CREATE_ALU_INST(ch_op::lt, true, true);
  CREATE_ALU_INST(ch_op::gt, true, true);
  CREATE_ALU_INST(ch_op::le, true, true);
  CREATE_ALU_INST(ch_op::ge, true, true);
  CREATE_ALU_INST(ch_op::notl, false, false);
  CREATE_ALU_INST(ch_op::andl, true, true);
  CREATE_ALU_INST(ch_op::orl, true, true);
  CREATE_ALU_INST(ch_op::inv, false, false);
  CREATE_ALU_INST(ch_op::andb, true, true);
  CREATE_ALU_INST(ch_op::orb, true, true);
  CREATE_ALU_INST(ch_op::xorb, true, true);
  CREATE_ALU_INST(ch_op::andr, false, false);
  CREATE_ALU_INST(ch_op::orr, false, false);
  CREATE_ALU_INST(ch_op::xorr, false, false);
  CREATE_ALU_INST(ch_op::shl, false, false);
  CREATE_ALU_INST(ch_op::shr, true, false);
  CREATE_ALU_INST(ch_op::add, true, true);
  CREATE_ALU_INST(ch_op::sub, true, true);
  CREATE_ALU_INST(ch_op::neg, false, false);
  CREATE_ALU_INST(ch_op::mult, true, true);
  CREATE_ALU_INST(ch_op::div, true, false);
  CREATE_ALU_INST(ch_op::mod, true, false);
  CREATE_ALU_INST(ch_op::pad, true, false);
  default:
    CH_ABORT("invalid opcode");
  }
#undef CREATE_ALU_INST
}

///////////////////////////////////////////////////////////////////////////////

class instr_select : public instr_base {
public:

  static instr_select* create(selectimpl* node, instr_map_t& map) {
    uint32_t dst_size = node->size();
    uint32_t dst_nblocks = ceildiv<uint32_t>(dst_size, bitwidth_v<block_type>);
    bool has_key      = node->has_key();
    uint32_t key_size = node->src(0).size();
    uint32_t num_srcs = node->srcs().size();

    uint32_t dst_bytes = sizeof(block_type) * dst_nblocks;
    uint32_t src_bytes = sizeof(block_type*) * node->srcs().size();

    auto buf = new uint8_t[sizeof(selectimpl) + dst_bytes + src_bytes]();

    auto buf_cur = buf + sizeof(selectimpl);
    auto dst = (block_type*)buf_cur;
    map[node->id()] = dst;

    buf_cur += dst_bytes;

    auto srcs = (const block_type**)buf_cur;
    for (uint32_t i = 0; i < num_srcs; ++i) {
      srcs[i] = map.at(node->src(i).id());
    }

    return new (buf) instr_select(has_key, key_size, srcs, num_srcs, dst, dst_size);
  }

  void destroy () override {
    this->~instr_select();
    ::operator delete [](this);
  }

  void eval() override {
    uint32_t i, last(num_srcs_ - 1);
    if (has_key_) {
      for (i = 1; i < last; i += 2) {
        if (bv_eq(srcs_[0], srcs_[i], key_size_))
          break;
      }
    } else {
      for (i = 0; i < last; i += 2) {
        if (static_cast<bool>(srcs_[i][0]))
          break;
      }
    }

    auto src = (i < last) ? srcs_[i+1] : srcs_[last];
    bv_copy(dst_, src, size_);
  }

private:

  instr_select(bool has_key, uint32_t key_size,
               const block_type** srcs, uint32_t num_srcs,
               block_type* dst, uint32_t size)
    : has_key_(has_key)
    , key_size_(key_size)    
    , srcs_(srcs)
    , num_srcs_(num_srcs)
    , dst_(dst)
    , size_(size)
  {}

  bool has_key_;
  uint32_t key_size_;
  const block_type** srcs_;
  uint32_t num_srcs_;
  block_type* dst_;
  uint32_t size_;
};

///////////////////////////////////////////////////////////////////////////////

class instr_cd : public instr_base {
public:

  static instr_cd* create(cdimpl* node, instr_map_t& map) {
    uint32_t dst_size  = node->size();
    uint32_t nblocks   = ceildiv<uint32_t>(dst_size, bitwidth_v<block_type>);
    uint32_t dst_bytes = sizeof(block_type) * nblocks;

    auto buf = new uint8_t[sizeof(cdimpl) + dst_bytes]();
    auto buf_cur = buf + sizeof(cdimpl);
    auto dst = (block_type*)buf_cur;
    map[node->id()] = dst;

    return new (buf) instr_cd(node, map, dst);
  }

  void destroy () override {
    this->~instr_cd();
    ::operator delete [](this);
  }

  void eval() override {
    auto value = static_cast<bool>(clk_[0]);
    dst_[0] = (prev_val_ != value) && (0 == (value ^ pos_edge_));
    prev_val_ = value;
  }

private:

  instr_cd(cdimpl* node, instr_map_t& map, block_type* dst)
    : clk_(map.at(node->clk().id()))
    , prev_val_(false)
    , pos_edge_(node->pos_edge())
    , dst_(dst)
  {}

  const block_type* clk_;
  bool prev_val_;
  bool pos_edge_;
  block_type* dst_;
};

///////////////////////////////////////////////////////////////////////////////

class instr_reg : public instr_base {
public:

  static instr_reg* create(regimpl* node, instr_map_t& map) {
    uint32_t dst_size  = node->size();
    uint32_t nblocks   = ceildiv<uint32_t>(dst_size, bitwidth_v<block_type>);
    uint32_t dst_bytes = sizeof(block_type) * nblocks;

    uint32_t pipe_length = node->length() - 1;
    uint32_t pipe_array_bytes = 0;
    uint32_t pipe_data_bytes = 0;
    for (uint32_t i = 0; i < pipe_length; ++i) {
      pipe_array_bytes += sizeof(block_type*);
      pipe_data_bytes += dst_bytes;
    }

    auto buf = new uint8_t[sizeof(instr_reg) + dst_bytes + pipe_array_bytes + pipe_data_bytes]();
    auto buf_cur = buf + sizeof(instr_reg);
    auto dst = (block_type*)buf_cur;
    map[node->id()] = dst;

    buf_cur += dst_bytes;

    auto pipe = (block_type**)buf_cur;
    buf_cur += pipe_array_bytes;

    for (uint32_t i = 0; i < pipe_length; ++i) {
      pipe[i] = (block_type*)(buf_cur + i * dst_bytes);
    }

    return new (buf) instr_reg(pipe, pipe_length, dst, dst_size);
  }

  void destroy () override {
    this->~instr_reg();
    ::operator delete [](this);
  }

  void init(regimpl* node, instr_map_t& map) {
    cd_       = map.at(node->cd().id());
    next_     = map.at(node->next().id());
    enable_   = node->has_enable() ? map.at(node->enable().id()) : nullptr;
    reset_    = node->has_initdata() ? map.at(node->reset().id()) : nullptr;
    initdata_ = node->has_initdata() ? map.at(node->initdata().id()) : nullptr;
  }

private:

  instr_reg(block_type** pipe, uint32_t pipe_length, block_type* dst, uint32_t size)
    : initdata_(nullptr)
    , cd_(nullptr)
    , reset_(nullptr)
    , enable_(nullptr)
    , next_(nullptr)
    , pipe_(pipe)
    , pipe_length_(pipe_length)
    , dst_(dst)
    , size_(size)
  {}

  void eval() override {
    // check clock transition
    if (!static_cast<bool>(cd_[0]))
      return;

    // check reset state
    if (reset_ && static_cast<bool>(reset_[0])) {
      bv_copy(dst_, initdata_, size_);
      for (uint32_t i = 0; i < pipe_length_; ++i) {
        bv_copy(pipe_[i], initdata_, size_);
      }
      return;
    }

    // check enable state
    if (enable_ && !static_cast<bool>(enable_[0]))
      return;

    // advance pipeline
    block_type* value = dst_;
    if (pipe_length_) {
      auto last = pipe_length_ - 1;
      bv_copy(dst_, pipe_[last], size_);
      for (int i = last; i > 0; --i) {
        bv_copy(pipe_[i], pipe_[i-1], size_);
      }
      value = pipe_[0];
    }
    // push next value
    bv_copy(value, next_, size_);
  }

  const block_type* initdata_;
  const block_type* cd_;
  const block_type* reset_;
  const block_type* enable_;
  const block_type* next_;
  block_type** pipe_;
  uint32_t pipe_length_;
  block_type* dst_;
  uint32_t size_;
};

///////////////////////////////////////////////////////////////////////////////

class instr_mem : public instr_base {
private:

  struct rdport_t {
          block_type* data;
    const block_type* addr;
    const block_type* enable;
  };

  struct wrport_t {
    const block_type* data;
    const block_type* addr;
    const block_type* enable;
  };

  rdport_t* rdports_;
  uint32_t num_rdports_;
  wrport_t* wrports_;
  uint32_t num_wrports_;
  const block_type* cd_;
  block_type* dst_;
  uint32_t data_size_;
  uint32_t addr_size_;

  instr_mem(rdport_t* rdports,
            uint32_t num_rdports,
            wrport_t* wrports,
            uint32_t num_wrports,
            block_type* dst,
            uint32_t data_size,
            uint32_t addr_size)
    : rdports_(rdports)
    , num_rdports_(num_rdports)
    , wrports_(wrports)
    , num_wrports_(num_wrports)
    , cd_(nullptr)
    , dst_(dst)
    , data_size_(data_size)
    , addr_size_(addr_size)
  {}

public:

  static instr_mem* create(memimpl* node, instr_map_t& map) {
    uint32_t dst_size  = node->size();
    uint32_t dst_nblocks = ceildiv<uint32_t>(dst_size, bitwidth_v<block_type>);
    uint32_t dst_bytes = sizeof(block_type) * dst_nblocks;
    uint32_t data_size = node->data_width();
    uint32_t data_bytes = sizeof(block_type) * ceildiv<uint32_t>(data_size, bitwidth_v<block_type>);
    uint32_t addr_size = log2ceil(node->num_items());

    uint32_t num_rdports = node->is_sync_read() ? node->rdports().size() : 0;
    uint32_t rdports_bytes = 0;
    uint32_t rdports_data_bytes = 0;
    for (uint32_t i = 0; i < num_rdports; ++i) {
      rdports_bytes += sizeof(rdport_t);
      rdports_data_bytes += data_bytes;
    }

    uint32_t num_wrports = node->wrports().size();
    uint32_t wrports_bytes = 0;
    for (uint32_t i = 0; i < num_wrports; ++i) {
      wrports_bytes += sizeof(wrport_t);
    }

    auto buf = new uint8_t[sizeof(instr_mem) + dst_bytes + rdports_bytes + rdports_data_bytes + wrports_bytes]();
    auto buf_cur = buf + sizeof(instr_mem);
    auto dst = (block_type*)buf_cur;
    map[node->id()] = dst;

    buf_cur += dst_bytes;

    auto rdports = (rdport_t*)buf_cur;
    buf_cur += rdports_bytes;

    for (uint32_t i = 0; i < num_rdports; ++i) {
      auto p = node->rdports()[i];
      rdports[i].data = (block_type*)(buf_cur + i * data_bytes);
      map[p->id()] = rdports[i].data;
    }

    buf_cur += rdports_data_bytes;
    auto wrports = (wrport_t*)buf_cur;

    if (node->has_initdata()) {
      bv_copy(dst, node->initdata().words(), dst_size);
    }

    return new (buf) instr_mem(rdports, num_rdports, wrports, num_wrports,
                               dst, data_size, addr_size);
  }

  void destroy () override {
    this->~instr_mem();
    ::operator delete [](this);
  }

  void init(memimpl* node, instr_map_t& map) {
    cd_ = node->has_cd() ? map.at(node->cd().id()) : nullptr;

    for (uint32_t i = 0; i < num_rdports_; ++i) {
      auto p = node->rdports()[i];
      rdports_[i].addr   = map.at(p->addr().id());
      rdports_[i].enable = p->has_enable() ? map.at(p->enable().id()) : nullptr;
    }

    for (uint32_t i = 0; i < num_wrports_; ++i) {
      auto p = node->wrports()[i];
      wrports_[i].data = map.at(p->wdata().id());
      wrports_[i].addr = map.at(p->addr().id());
      wrports_[i].enable = p->has_enable() ? map.at(p->enable().id()) : nullptr;
    }
  }

  void eval() override {
    // check clock transition
    if (!cd_ || !static_cast<bool>(cd_[0]))
      return;

    // evaluate synchronous read ports
    for (const rdport_t *p = rdports_, *p_end = p + num_rdports_ ; p != p_end; ++p) {
      // check enable state
      if (p->enable && !static_cast<bool>(p->enable[0]))
        continue;
      // memory read
      auto addr = bv_cast<uint32_t>(p->addr, addr_size_);
      bv_copy(p->data, 0, dst_, addr * data_size_, data_size_);
    }

    // evaluate synchronous write ports
    for (wrport_t *p = wrports_, *p_end = p + num_wrports_ ; p != p_end; ++p) {
      // check enable state
      if (p->enable && !static_cast<bool>(p->enable[0]))
        continue;
      // memory write
      auto addr = bv_cast<uint32_t>(p->addr, addr_size_);
      bv_copy(dst_, addr * data_size_, p->data, 0, data_size_);
    }
  }
};

///////////////////////////////////////////////////////////////////////////////

class instr_mrport : public instr_base {
public:

  static instr_mrport* create(mrportimpl* node, instr_map_t& map) {
    uint32_t dst_size  = node->size();
    uint32_t nblocks   = ceildiv<uint32_t>(dst_size, bitwidth_v<block_type>);
    uint32_t dst_bytes = sizeof(block_type) * nblocks;

    auto buf = new uint8_t[sizeof(mrportimpl) + dst_bytes]();
    auto buf_cur = buf + sizeof(mrportimpl);
    auto dst = (block_type*)buf_cur;
    map[node->id()] = dst;

    auto store = map.at(node->mem()->id());
    auto addr = map.at(node->addr().id());
    auto addr_size = node->addr().size();

    return new (buf) instr_mrport(store, addr, dst, dst_size, addr_size);
  }

  void destroy () override {
    this->~instr_mrport();
    ::operator delete [](this);
  }

  void eval() override {
    auto a = bv_cast<uint32_t>(addr_, addr_size_);
    bv_copy(dst_, 0, store_, a * dst_size_, dst_size_);
  }

private:

  instr_mrport(const block_type* store,
              const block_type* addr,
              block_type* dst,
              uint32_t dst_size,
              uint32_t addr_size)
    : store_(store)
    , addr_(addr)
    , dst_(dst)
    , dst_size_(dst_size)
    , addr_size_(addr_size)
  {}

  const block_type* store_;
  const block_type* addr_;
  block_type* dst_;
  uint32_t dst_size_;
  uint32_t addr_size_;
};

///////////////////////////////////////////////////////////////////////////////

class instr_tap : public instr_base {
public:

  static instr_tap* create(tapimpl* node, instr_map_t& map) {
    return new instr_tap(node, map);
  }

  void destroy () override {
    delete this;
  }

  void eval() override {
    bv_copy(dst_, src_, size_);
  }

private:

  instr_tap(tapimpl* node, instr_map_t& map)
    : src_(map.at(node->src(0).id()))
    , dst_(node->value().words())
    , size_(node->size())
  {}

  const block_type* src_;
  block_type* dst_;
  uint32_t size_;
};

///////////////////////////////////////////////////////////////////////////////

class instr_assert : public instr_base {
public:

  static instr_assert* create(assertimpl* node, instr_map_t& map) {
    return new instr_assert(node, map);
  }

  void destroy () override {
    delete this;
  }

  void eval() override {
    if ((!pred_ || static_cast<bool>(pred_[0]))
     && !static_cast<bool>(cond_[0])) {
      fprintf(stderr, "assertion failure at tick %ld, %s (%s:%d)\n",
              tick_, msg_.c_str(), sloc_.file(), sloc_.line());
      std::abort();
    }
    ++tick_;
  }

private:

  instr_assert(assertimpl* node, instr_map_t& map)
    : cond_(map.at(node->condition().id()))
    , pred_(node->is_predicated() ? map.at(node->predicate().id()) : nullptr)
    , msg_(node->message())
    , sloc_(node->sloc())
    , tick_(0)
  {}

  const block_type* cond_;
  const block_type* pred_;
  std::string msg_;
  source_location sloc_;
  ch_tick tick_;
};

///////////////////////////////////////////////////////////////////////////////

class instr_time : public instr_base {
public:

  static instr_time* create(timeimpl* node, instr_map_t& map) {
    return new instr_time(node, map);
  }

  void destroy () override {
    delete this;
  }

  void eval() override {
    dst_ = tick_++;
  }

private:

  ch_tick tick_;
  sdata_type dst_;

  instr_time(timeimpl* node, instr_map_t& map)
    : tick_(0)
    , dst_(node->size()) {
    map[node->id()] = dst_.words();
  }
};

///////////////////////////////////////////////////////////////////////////////

class instr_print : public instr_base {
public:

  static instr_print* create(printimpl* node, instr_map_t& map) {
    return new instr_print(node, map);
  }

  void destroy () override {
    delete this;
  }

  void eval() override {
    if (pred_ && !static_cast<bool>(pred_[0]))
      return;
    if (format_ != "") {
      std::stringstream strbuf;
      for (const char *str = format_.c_str(); *str != '\0'; ++str) {
        if (*str == '{') {
          fmtinfo_t fmt;
          str = parse_format_index(&fmt, str);
          auto& src = srcs_[fmt.index];
          switch (fmt.type) {
          case fmttype::Int:
            strbuf << src;
            break;
          case fmttype::Float:
            strbuf << bit_cast<float>(static_cast<int>(src));
            break;
          case fmttype::Enum:
            strbuf << enum_strings_[fmt.index](static_cast<int>(src));
           break;
          }
        } else {
          strbuf.put(*str);
        }
      }
      std::cout << strbuf.rdbuf();
    }
    std::cout << std::endl;
  }

private:

  instr_print(printimpl* node, instr_map_t& map)
    : enum_strings_(node->enum_strings())
    , pred_(node->is_predicated() ? map.at(node->predicate().id()) : nullptr)
    , format_(node->format()) {
    srcs_.resize(node->enum_strings().size());
    for (uint32_t i = (pred_ ? 1 : 0), j = 0, n = node->srcs().size(); i < n; ++i, ++j) {
      auto src = node->src(i).impl();
      srcs_[j].emplace(const_cast<block_type*>(map.at(src->id())), src->size());
    }
  }

  ~instr_print() {
    for (auto& src : srcs_) {
      src.emplace(nullptr);
    }
  }

  std::vector<enum_string_cb> enum_strings_;
  std::vector<sdata_type> srcs_;
  const block_type* pred_;
  std::string format_;
};

///////////////////////////////////////////////////////////////////////////////

class instr_udfc : public instr_base {
public:

  static instr_udfc* create(udfcimpl* node, instr_map_t& map) {
    return new instr_udfc(node, map);
  }

  void destroy () override {
    delete this;
  }

  void eval() override {
    udf_->eval(dst_, srcs_);
  }

private:

  instr_udfc(udfcimpl* node, instr_map_t& map)
    : udf_(node->udf())
    , dst_(node->size()) {
    srcs_.resize(node->srcs().size());
    for (uint32_t i = 0, n = srcs_.size(); i < n; ++i) {
      auto& src = node->src(i);
      srcs_[i].emplace(const_cast<block_type*>(map.at(src.id())), src.size());
    }
    map[node->id()] = dst_.words();
  }

  ~instr_udfc() {
    for (auto& src : srcs_) {
      src.emplace(nullptr);
    }
  }

  udf_iface* udf_;
  udf_inputs srcs_;
  sdata_type dst_;
};

///////////////////////////////////////////////////////////////////////////////

class instr_udfs : public instr_base {
public:

  static instr_udfs* create(udfsimpl* node, instr_map_t& map) {
    return new instr_udfs(node, map);
  }

  void destroy () override {
    delete this;
  }

  void init(udfsimpl* node, instr_map_t& map) {
    cd_ = map.at(node->cd().id());
    reset_ = node->has_initdata() ? map.at(node->reset().id()) : nullptr;    
    for (uint32_t i = 0, n = srcs_.size(); i < n; ++i) {
      auto& src = node->src(i);
      srcs_[i].emplace(const_cast<block_type*>(map.at(src.id())), src.size());
    }
  }

  void eval() override {
    // check clock transition
    if (!static_cast<bool>(cd_[0]))
      return;

    sdata_type* value = &dst_;

    // advance the pipeline
    if (!pipe_.empty()) {
      auto last = pipe_.size() - 1;
      dst_ = pipe_[last];
      for (int i = last; i > 0; --i) {
        pipe_[i] = pipe_[i-1];
      }
      value = &pipe_[0];
    }

    // push new entry
    if (reset_ && static_cast<bool>(reset_[0])) {
      udf_->reset(*value, srcs_);
    } else {
      udf_->eval(*value, srcs_);
    }
  }

private:

  instr_udfs(udfsimpl* node, instr_map_t& map)
    : udf_(node->udf())
    , cd_(nullptr)
    , reset_(nullptr)
    , dst_(node->size()) {
    srcs_.resize(node->srcs().size());
    pipe_.resize(udf_->delta() - 1, sdata_type(dst_.size()));
    map[node->id()] = dst_.words();
  }

  ~instr_udfs() {
    for (auto& src : srcs_) {
      src.emplace(nullptr);
    }
  }

  std::vector<sdata_type> pipe_;
  udf_iface* udf_;
  udf_inputs srcs_;
  const block_type* cd_;
  const block_type* reset_;
  sdata_type dst_;
};

///////////////////////////////////////////////////////////////////////////////

simref::simref() {}

simref::~simref() {
  for (auto instr : instrs_) {
    instr->destroy();
  }
}

void simref::initialize(const std::vector<lnodeimpl*>& eval_list) {
  instr_map_t instr_map;
  std::unordered_map<uint32_t, instr_base*> snodes;
  snodes.reserve(eval_list.size());
  instrs_.reserve(eval_list.size());

  // lower synchronous nodes
  for (auto node : eval_list) {
    switch (node->type()) {
    case type_reg:
      snodes[node->id()] = instr_reg::create(reinterpret_cast<regimpl*>(node), instr_map);
      break;
    case type_mem:
      snodes[node->id()] = instr_mem::create(reinterpret_cast<memimpl*>(node), instr_map);
      break;
    case type_udfs:
      snodes[node->id()] = instr_udfs::create(reinterpret_cast<udfsimpl*>(node), instr_map);
      break;
    default:
      break;
    }
  }

  // lower all nodes
  for (auto node : eval_list) {
    switch (node->type()) {
    case type_undef:
      assert(false);
      break;
    case type_lit:
      instr_map[node->id()] = reinterpret_cast<litimpl*>(node)->value().words();
      break;
    case type_proxy:
      instrs_.emplace_back(instr_proxy::create(reinterpret_cast<proxyimpl*>(node), instr_map));
      break;
    case type_input: {
      auto input = reinterpret_cast<inputimpl*>(node);
      if (input->is_bind()) {
        instr_map[node->id()] = instr_map.at(input->binding().id());
      } else {
        instr_map[node->id()] = input->value().words();
      }
    } break;
    case type_output: {
      auto output = reinterpret_cast<outputimpl*>(node);
      instr_map[node->id()] = instr_map.at(output->src(0).id());
      if (!output->is_bind()) {
        instrs_.emplace_back(instr_output::create(output, instr_map));
      }
    } break;
    case type_alu:
      instrs_.emplace_back(instr_alu_base::create(reinterpret_cast<aluimpl*>(node), instr_map));
      break;
    case type_sel:
      instrs_.emplace_back(instr_select::create(reinterpret_cast<selectimpl*>(node), instr_map));
      break;
    case type_cd:
      instrs_.emplace_back(instr_cd::create(reinterpret_cast<cdimpl*>(node), instr_map));
      break;
    case type_reg: {
      auto instr = reinterpret_cast<instr_reg*>(snodes.at(node->id()));
      instr->init(reinterpret_cast<regimpl*>(node), instr_map);
      instrs_.emplace_back(instr);
    } break;
    case type_mem: {
      auto instr = reinterpret_cast<instr_mem*>(snodes.at(node->id()));
      instr->init(reinterpret_cast<memimpl*>(node), instr_map);
      instrs_.emplace_back(instr);
    } break;
    case type_mrport: {
      auto port = reinterpret_cast<mrportimpl*>(node);
      if (!port->is_sync_read()) {
        instrs_.emplace_back(instr_mrport::create(port, instr_map));
      }
    } break;
    case type_mwport:
    case type_bind:
      // skip
      break;
    case type_bindin:
      instr_map[node->id()] = instr_map.at(reinterpret_cast<bindportimpl*>(node)->src(0).id());
      break;
    case type_bindout:
      instr_map[node->id()] = instr_map.at(reinterpret_cast<bindportimpl*>(node)->ioport().id());
      break;
    case type_tap:
      instrs_.emplace_back(instr_tap::create(reinterpret_cast<tapimpl*>(node), instr_map));
      break;
    case type_assert:
      instrs_.emplace_back(instr_assert::create(reinterpret_cast<assertimpl*>(node), instr_map));
      break;
    case type_time:
      instrs_.emplace_back(instr_time::create(reinterpret_cast<timeimpl*>(node), instr_map));
      break;
    case type_print:
      instrs_.emplace_back(instr_print::create(reinterpret_cast<printimpl*>(node), instr_map));
      break;
    case type_udfc:
      instrs_.emplace_back(instr_udfc::create(reinterpret_cast<udfcimpl*>(node), instr_map));
      break;
    case type_udfs: {
      auto instr = reinterpret_cast<instr_udfs*>(snodes.at(node->id()));
      instr->init(reinterpret_cast<udfsimpl*>(node), instr_map);
      instrs_.emplace_back(instr);
    } break;
    }
  }
}

void simref::eval() {
  for (auto instr : instrs_) {
    instr->eval();
  }
}
