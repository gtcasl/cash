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

using data_map_t = std::unordered_map<uint32_t, const block_type*>;

#define __aligned_sizeof(x) (4*((sizeof(x) + 3)/4))

class instr_proxy_base : public instr_base {
public:

  static instr_proxy_base* create(proxyimpl* node, data_map_t& map);

protected:

  struct range_t {
    const block_type* src_data;
    uint32_t src_offset;
    uint32_t dst_offset;
    uint32_t length;
  };

  instr_proxy_base(block_type* dst) : dst_(dst) {}

  block_type* dst_;
};

template <bool is_scalar>
class instr_slice : public instr_proxy_base {
public:

  void destroy() override {
    this->~instr_slice();
    ::operator delete [](this);
  }

  void eval() override {
    if constexpr (is_scalar) {
      bv_slice_vector_small(dst_, dst_size_, src_data_, src_offset_);
    } else {
      bv_slice_vector(dst_, dst_size_, src_data_, src_offset_);
    }
  }

private:

  instr_slice(block_type* dst, uint32_t dst_size, const block_type* src_data, uint32_t src_offset)
    : instr_proxy_base(dst)
    , dst_size_(dst_size)
    , src_data_(src_data)
    , src_offset_(src_offset)
  {}

  uint32_t dst_size_;
  const block_type* src_data_;
  uint32_t src_offset_;

  friend class instr_proxy_base;
};

template <bool is_scalar>
class instr_proxy : public instr_proxy_base {
private:

  const range_t* ranges_;
  uint32_t num_ranges_;

  instr_proxy(block_type* dst, const range_t* ranges, uint32_t num_ranges)
    : instr_proxy_base(dst)
    , ranges_(ranges)
    , num_ranges_(num_ranges)
  {}

  friend class instr_proxy_base;

public:

  void destroy() override {
    this->~instr_proxy();
    ::operator delete [](this);
  }

  void eval() override {
    if constexpr (is_scalar) {
      block_type src_block;
      uint32_t dst_offset;
      const range_t *r0 = ranges_;
      {
        uint32_t lr = (bitwidth_v<block_type> - r0->length);
        src_block = ((r0->src_data[0] >> r0->src_offset) << lr) >> lr;
        dst_offset = r0->length;
      }
      for (const range_t *r = r0 + 1, *r_end = r0 + num_ranges_ ;r != r_end; ++r) {
        uint32_t lr = (bitwidth_v<block_type> - r->length);
        src_block |= (((r->src_data[0] >> r->src_offset) << lr) >> lr) << dst_offset;
        dst_offset += r->length;
      }
      dst_[0] = src_block;
    } else {
      for (const range_t *r = ranges_, *r_end = r + num_ranges_ ;r != r_end; ++r) {
        auto dst = dst_ + (r->dst_offset / bitwidth_v<block_type>);
        auto dst_offset = r->dst_offset % bitwidth_v<block_type>;
        bv_copy_vector(dst, dst_offset, r->src_data, r->src_offset, r->length);
      }
    }
  }
};

instr_proxy_base* instr_proxy_base::create(proxyimpl* node, data_map_t& map) {
  uint32_t dst_size = node->size();
  uint32_t dst_nblocks = ceildiv<uint32_t>(dst_size, bitwidth_v<block_type>);
  uint32_t dst_bytes = sizeof(block_type) * dst_nblocks;
  uint32_t num_ranges = node->ranges().size();

  if (1 == num_ranges
   && node->range(0).length == dst_size) {
    auto buf = new uint8_t[__aligned_sizeof(instr_slice<false>) + dst_bytes]();
    auto buf_cur = buf + __aligned_sizeof(instr_slice<false>);
    auto dst = (block_type*)buf_cur;
    map[node->id()] = dst;

    auto& src_range = node->range(0);
    auto& src = node->src(src_range.src_idx);
    auto src_data = map.at(src.id()) + src_range.src_offset / bitwidth_v<block_type>;
    auto src_offset = src_range.src_offset % bitwidth_v<block_type>;

    bool is_scalar = (dst_size <= bitwidth_v<block_type>);
    if (is_scalar) {
      return new (buf) instr_slice<true>(dst, dst_size, src_data, src_offset);
    } else {
      return new (buf) instr_slice<false>(dst, dst_size, src_data, src_offset);
    }
  } else {
    uint32_t range_bytes = 0;
    for (uint32_t i = 0; i < num_ranges; ++i) {
      range_bytes += __aligned_sizeof(instr_proxy_base::range_t);
    }

    auto buf = new uint8_t[__aligned_sizeof(instr_proxy<false>) + dst_bytes + range_bytes]();
    auto buf_cur = buf + __aligned_sizeof(instr_proxy<false>);
    auto dst = (block_type*)buf_cur;
    map[node->id()] = dst;

    buf_cur += dst_bytes;

    bool is_scalar = (dst_size <= bitwidth_v<block_type>);

    uint32_t src_length = 0;
    auto ranges = (instr_proxy_base::range_t*)buf_cur;
    for (uint32_t i = 0; i < num_ranges; ++i) {
      auto& dst_range = ranges[i];
      auto& src_range = node->range(i);
      auto& src = node->src(src_range.src_idx);
      dst_range.src_data   = map.at(src.id()) + (src_range.src_offset / bitwidth_v<block_type>);
      dst_range.src_offset = src_range.src_offset % bitwidth_v<block_type>;
      dst_range.dst_offset = src_range.dst_offset;
      dst_range.length     = src_range.length;

      is_scalar &= (dst_range.src_offset + dst_range.length) <= bitwidth_v<block_type>;
      src_length += src_range.length;
    }
    is_scalar &= (src_length == dst_size);

    if (is_scalar) {
      return new (buf) instr_proxy<true>(dst, ranges, num_ranges);
    } else {
      return new (buf) instr_proxy<false>(dst, ranges, num_ranges);
    }
  }
}

///////////////////////////////////////////////////////////////////////////////

class instr_output_base : public instr_base {
public:

  static instr_output_base* create(ioportimpl* node, data_map_t& map);

protected:

  instr_output_base(block_type* dst, const block_type* src, uint32_t size)
    : dst_(dst)
    , src_(src)
    , size_(size)
  {}

  block_type* dst_;
  const block_type* src_;
  uint32_t size_;
};

template <bool is_scalar>
class instr_output : public instr_output_base {
public:

  void destroy() override {
    delete this;
  }

  void eval() override {
    if constexpr (is_scalar) {
      bv_copy_scalar(dst_, src_);
    } else {
      bv_copy_vector(dst_, src_, size_);
    }
  }

private:

  instr_output(block_type* dst, const block_type* src, uint32_t size)
    : instr_output_base(dst, src, size)
  {}

  friend class instr_output_base;
};

instr_output_base* instr_output_base::create(ioportimpl* node, data_map_t& map) {
  auto dst  = node->value()->words();
  auto src  = map.at(node->src(0).id());
  auto size = node->size();
  if (size <= bitwidth_v<block_type>) {
    return new instr_output<true>(dst, src, size);
  } else {
    return new instr_output<false>(dst, src, size);
  }
}

///////////////////////////////////////////////////////////////////////////////

class instr_alu_base : public instr_base {
public:

  static instr_alu_base* create(aluimpl* node, data_map_t& map);

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

template <ch_op op, bool is_signed, bool is_scalar, bool resize_opds>
class instr_alu : instr_alu_base {
public:

  void destroy() override {
    this->~instr_alu();
    ::operator delete [](this);
  }

  void eval() override {
    if constexpr (resize_opds && !is_scalar) {
      if (src0_size_ != o_src0_size_) {
        bv_pad<is_signed>(src0_, src0_size_, o_src0_, o_src0_size_);
      }
      if (src1_size_ != o_src1_size_) {
        bv_pad<is_signed>(src1_, src1_size_, o_src1_, o_src1_size_);
      }
    }

    switch (op) {
    case ch_op::eq:
      if constexpr (is_scalar) {
        block_type u = resize_opds ? sign_ext(src0_[0], src0_size_) : src0_[0];
        block_type v = resize_opds ? sign_ext(src1_[0], src1_size_) : src1_[0];
        bv_assign(dst_, dst_size_, bv_eq_scalar(&u, &v));
      } else {
        bv_assign(dst_, dst_size_, bv_eq_vector(src0_,  src1_, src0_size_));
      }
      break;
    case ch_op::ne:
      if constexpr (is_scalar) {
        block_type u = resize_opds ? sign_ext(src0_[0], src0_size_) : src0_[0];
        block_type v = resize_opds ? sign_ext(src1_[0], src1_size_) : src1_[0];
        bv_assign(dst_, dst_size_, !bv_eq_scalar(&u, &v));
      } else {
        bv_assign(dst_, dst_size_, !bv_eq_vector(src0_,  src1_, src0_size_));
      }
      break;
    case ch_op::lt:
      if constexpr (is_scalar) {
        block_type u = resize_opds ? sign_ext(src0_[0], src0_size_) : src0_[0];
        block_type v = resize_opds ? sign_ext(src1_[0], src1_size_) : src1_[0];
        bv_assign(dst_, dst_size_, bv_lt_scalar<is_signed>(&u, &v, src0_size_));
      } else {
        bv_assign(dst_, dst_size_, bv_lt_vector<is_signed>(src0_,  src1_, src0_size_));
      }
      break;
    case ch_op::gt:
      if constexpr (is_scalar) {
        block_type u = resize_opds ? sign_ext(src0_[0], src0_size_) : src0_[0];
        block_type v = resize_opds ? sign_ext(src1_[0], src1_size_) : src1_[0];
        bv_assign(dst_, dst_size_, bv_lt_scalar<is_signed>(&v, &u, src0_size_));
      } else {
        bv_assign(dst_, dst_size_, bv_lt_vector<is_signed>(src1_,  src0_, src0_size_));
      }
      break;
    case ch_op::le:
      if constexpr (is_scalar) {
        block_type u = resize_opds ? sign_ext(src0_[0], src0_size_) : src0_[0];
        block_type v = resize_opds ? sign_ext(src1_[0], src1_size_) : src1_[0];
        bv_assign(dst_, dst_size_, !bv_lt_scalar<is_signed>(&v, &u, src0_size_));
      } else {
        bv_assign(dst_, dst_size_, !bv_lt_vector<is_signed>(src1_,  src0_, src0_size_));
      }
      break;
    case ch_op::ge:
      if constexpr (is_scalar) {
        block_type u = resize_opds ? sign_ext(src0_[0], src0_size_) : src0_[0];
        block_type v = resize_opds ? sign_ext(src1_[0], src1_size_) : src1_[0];
        bv_assign(dst_, dst_size_, !bv_lt_scalar<is_signed>(&u, &v, src0_size_));
      } else {
        bv_assign(dst_, dst_size_, !bv_lt_vector<is_signed>(src0_,  src1_, src0_size_));
      }
      break;

    case ch_op::notl:
      if constexpr (is_scalar) {
        bv_assign(dst_, dst_size_, !bv_orr_scalar(src0_));
      } else {
        bv_assign(dst_, dst_size_, !bv_orr_vector(src0_, src0_size_));
      }
      break;
    case ch_op::andl:
      if constexpr (is_scalar) {
        bv_assign(dst_, dst_size_, bv_orr_scalar(src0_) && bv_orr_scalar(src1_));
      } else {
        bv_assign(dst_, dst_size_, bv_orr_vector(src0_, src0_size_) && bv_orr_vector(src1_, src1_size_));
      }
      break;
    case ch_op::orl:
      if constexpr (is_scalar) {
        bv_assign(dst_, dst_size_, bv_orr_scalar(src0_) || bv_orr_scalar(src1_));
      } else {
        bv_assign(dst_, dst_size_, bv_orr_vector(src0_, src0_size_) || bv_orr_vector(src1_, src1_size_));
      }
      break;

    case ch_op::inv:
      if constexpr (is_scalar) {
        block_type u = resize_opds ? sign_ext(src0_[0], src0_size_) : src0_[0];
        bv_inv_scalar(dst_, &u, dst_size_);
      } else {
        bv_inv_vector(dst_, src0_, dst_size_);
      }
      break;
    case ch_op::andb:
      if constexpr (is_scalar) {
        block_type u = resize_opds ? sign_ext(src0_[0], src0_size_) : src0_[0];
        block_type v = resize_opds ? sign_ext(src1_[0], src1_size_) : src1_[0];
        bv_and_scalar(dst_, &u, &v);
      } else {
        bv_and_vector(dst_, src0_, src1_, dst_size_);
      }
      break;
    case ch_op::orb:
      if constexpr (is_scalar) {
        block_type u = resize_opds ? sign_ext(src0_[0], src0_size_) : src0_[0];
        block_type v = resize_opds ? sign_ext(src1_[0], src1_size_) : src1_[0];
        bv_or_scalar(dst_, &u, &v);
      } else {
        bv_or_vector(dst_, src0_, src1_, dst_size_);
      }
      break;
    case ch_op::xorb:
      if constexpr (is_scalar) {
        block_type u = resize_opds ? sign_ext(src0_[0], src0_size_) : src0_[0];
        block_type v = resize_opds ? sign_ext(src1_[0], src1_size_) : src1_[0];
        bv_xor_scalar(dst_, &u, &v);
      } else {
        bv_xor_vector(dst_, src0_, src1_, dst_size_);
      }
      break;

    case ch_op::andr:
      if constexpr (is_scalar) {
        bv_assign(dst_, dst_size_, bv_andr_scalar(src0_, src0_size_));
      } else {
        bv_assign(dst_, dst_size_, bv_andr_vector(src0_, src0_size_));
      }
      break;
    case ch_op::orr:
      if constexpr (is_scalar) {
        bv_assign(dst_, dst_size_, bv_orr_scalar(src0_));
      } else {
        bv_assign(dst_, dst_size_, bv_orr_vector(src0_, src0_size_));
      }
      break;
    case ch_op::xorr:
      if constexpr (is_scalar) {
        bv_assign(dst_, dst_size_, bv_xorr_scalar(src0_));
      } else {
        bv_assign(dst_, dst_size_, bv_xorr_vector(src0_, src0_size_));
      }
      break;

    case ch_op::shl:
      if constexpr (is_scalar) {
        bv_shl_scalar(dst_, dst_size_, src0_, bv_cast<uint32_t>(src1_, src1_size_));
     } else {
        bv_shl_vector(dst_, dst_size_, src0_, src0_size_, bv_cast<uint32_t>(src1_, src1_size_));
      }
      break;
    case ch_op::shr:
      if constexpr (is_scalar) {
        auto dist = bv_cast<uint64_t>(src1_, src1_size_);
        bv_shr_scalar<is_signed>(dst_, dst_size_, src0_, src0_size_, dist);
      } else {
        auto dist = bv_cast<uint64_t>(src1_, src1_size_);
        bv_shr_vector<is_signed>(dst_, dst_size_, src0_, src0_size_, dist);
      }
      break;

    case ch_op::add:
      if constexpr (is_scalar) {
        block_type u = resize_opds ? sign_ext(src0_[0], src0_size_) : src0_[0];
        block_type v = resize_opds ? sign_ext(src1_[0], src1_size_) : src1_[0];
        bv_add_scalar(dst_, &u, &v, dst_size_);
      } else {
        bv_add_vector(dst_, src0_, src1_, dst_size_);
      }
      break;
    case ch_op::sub:
      if constexpr (is_scalar) {
        block_type u = resize_opds ? sign_ext(src0_[0], src0_size_) : src0_[0];
        block_type v = resize_opds ? sign_ext(src1_[0], src1_size_) : src1_[0];
        bv_sub_scalar(dst_, &u, &v, dst_size_);
      } else {
        bv_sub_vector(dst_, src0_, src1_, dst_size_);
      }
      break;
    case ch_op::neg:
      if constexpr (is_scalar) {
        block_type u = resize_opds ? sign_ext(src0_[0], src0_size_) : src0_[0];
        bv_neg_scalar(dst_, &u, dst_size_);
      } else {
        bv_neg_vector(dst_, src0_, dst_size_);
      }
      break;
    case ch_op::mult:
      if constexpr (is_scalar) {
        bv_mult_scalar<is_signed>(dst_, dst_size_, src0_, src0_size_, src1_, src1_size_);
      } else {
        bv_mult_vector<is_signed>(dst_, dst_size_, src0_, src0_size_, src1_, src1_size_);
      }
      break;
    case ch_op::div:
      if constexpr (is_scalar) {
        bv_div_scalar<is_signed>(dst_, dst_size_, src0_, src0_size_, src1_, src1_size_);
      } else {
        bv_div_vector<is_signed>(dst_, dst_size_, src0_, src0_size_, src1_, src1_size_);
      }
      break;
    case ch_op::mod:
      if constexpr (is_scalar) {
        bv_mod_scalar<is_signed>(dst_, dst_size_, src0_, src0_size_, src1_, src1_size_);
      } else {
        bv_mod_vector<is_signed>(dst_, dst_size_, src0_, src0_size_, src1_, src1_size_);
      }
      break;

    case ch_op::pad:
      if constexpr (is_scalar) {
        bv_pad_scalar<is_signed>(dst_, dst_size_, src0_, src0_size_);
      } else {
        bv_pad_vector<is_signed>(dst_, dst_size_, src0_, src0_size_);
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

instr_alu_base* instr_alu_base::create(aluimpl* node, data_map_t& map) {
  uint32_t dst_size = node->size();

  const block_type* o_src0 = nullptr;
  uint32_t o_src0_size = 0;
  const block_type* o_src1 = nullptr;
  uint32_t o_src1_size = 0;

  bool is_scalar = (dst_size <= bitwidth_v<block_type>);

  // access source node data
  if (node->srcs().size() > 0) {
    o_src0 = map.at(node->src(0).id());
    o_src0_size = node->src(0).size();
    is_scalar &= (o_src0_size <= bitwidth_v<block_type>);
    if (node->srcs().size() > 1) {
      o_src1 = map.at(node->src(1).id());
      o_src1_size = node->src(1).size();
      is_scalar &= (o_src1_size <= bitwidth_v<block_type>);
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
        if (!is_scalar) {
          if (src0_size < src1_size) {
            src0_size = src1_size;
          } else {
            src1_size = src0_size;
          }
        }
        resize_opds = true;
      }
    } else {
      // resize source operands to match destination
      if (src0_size != dst_size) {
        if (src0_size < dst_size) {
          resize_opds = true;
        }
        if (!is_scalar) {
          src0_size = dst_size;
        }
      }
      if (src1 && src1_size != dst_size) {
        if (src1_size < dst_size) {
          resize_opds = true;
        }
        if (!is_scalar) {
          src1_size = dst_size;
        }
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

  auto buf = new uint8_t[__aligned_sizeof(instr_alu_base) + dst_bytes + t_src0_bytes + t_src1_bytes]();
  auto buf_cur = buf + __aligned_sizeof(instr_alu_base);
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

  // disable resize for unsigned scalars
  if (is_scalar && !is_signed && resize_opds)
    resize_opds = false;

#define CREATE_ALU_INST(op, sign_enable, resize_enable) \
  case op: \
    if (is_scalar) { \
      if (sign_enable && is_signed) { \
        if (resize_enable && resize_opds) { \
          return new (buf) instr_alu<op, true, true, true>(o_src0, o_src0_size, \
                                                           o_src1, o_src1_size, src0, src0_size, \
                                                           src1, src1_size, dst, dst_size); \
        } else { \
          return new (buf) instr_alu<op, true, true, false>(o_src0, o_src0_size, \
                                                            o_src1, o_src1_size, src0, src0_size, \
                                                            src1, src1_size, dst, dst_size); \
        }  \
      } else { \
        if (resize_enable && resize_opds) { \
          return new (buf) instr_alu<op, false, true, true>(o_src0, o_src0_size, \
                                                            o_src1, o_src1_size, src0, src0_size, \
                                                            src1, src1_size, dst, dst_size); \
        } else { \
          return new (buf) instr_alu<op, false, true, false>(o_src0, o_src0_size, \
                                                             o_src1, o_src1_size, src0, src0_size, \
                                                             src1, src1_size, dst, dst_size); \
        } \
      } \
    } else { \
      if (sign_enable && is_signed) { \
        if (resize_enable && resize_opds) { \
          return new (buf) instr_alu<op, true, false, true>(o_src0, o_src0_size, \
                                                            o_src1, o_src1_size, src0, src0_size, \
                                                            src1, src1_size, dst, dst_size); \
        } else { \
          return new (buf) instr_alu<op, true, false, false>(o_src0, o_src0_size, \
                                                             o_src1, o_src1_size, src0, src0_size, \
                                                             src1, src1_size, dst, dst_size); \
        }  \
      } else { \
        if (resize_enable && resize_opds) { \
          return new (buf) instr_alu<op, false, false, true>(o_src0, o_src0_size, \
                                                             o_src1, o_src1_size, src0, src0_size, \
                                                             src1, src1_size, dst, dst_size); \
        } else { \
          return new (buf) instr_alu<op, false, false, false>(o_src0, o_src0_size, \
                                                              o_src1, o_src1_size, src0, src0_size, \
                                                              src1, src1_size, dst, dst_size); \
        } \
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
  CREATE_ALU_INST(ch_op::andl, false, false);
  CREATE_ALU_INST(ch_op::orl, false, false);
  CREATE_ALU_INST(ch_op::inv, true, true);
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
  CREATE_ALU_INST(ch_op::neg, true, true);
  CREATE_ALU_INST(ch_op::mult, true, false);
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

  static instr_select* create(selectimpl* node, data_map_t& map) {
    uint32_t dst_size = node->size();
    uint32_t dst_nblocks = ceildiv<uint32_t>(dst_size, bitwidth_v<block_type>);
    bool has_key      = node->has_key();
    uint32_t key_size = node->src(0).size();
    uint32_t num_srcs = node->srcs().size();

    uint32_t dst_bytes = sizeof(block_type) * dst_nblocks;
    uint32_t src_bytes = sizeof(block_type*) * node->srcs().size();

    auto buf = new uint8_t[__aligned_sizeof(instr_select) + dst_bytes + src_bytes]();

    auto buf_cur = buf + __aligned_sizeof(instr_select);
    auto dst = (block_type*)buf_cur;
    map[node->id()] = dst;

    buf_cur += dst_bytes;

    auto srcs = (const block_type**)buf_cur;
    for (uint32_t i = 0; i < num_srcs; ++i) {
      srcs[i] = map.at(node->src(i).id());
    }

    return new (buf) instr_select(has_key, key_size, srcs, num_srcs, dst, dst_size);
  }

  void destroy() override {
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

  static instr_cd* create(cdimpl* node, data_map_t& map) {
    auto clk = map.at(node->clk().id());
    return new instr_cd(clk, node->pos_edge());
  }

  void add_bypass(instr_base* instr, uint32_t step) {
    bypass_nodes_.emplace_back(instr, step);
  }

  void destroy() override {
    delete this;
  }

  void eval() override {
    auto value = static_cast<bool>(clk_[0]);
    bool changed = (prev_val_ != value) && (0 == (value ^ pos_edge_));
    prev_val_ = value;
    if (changed) {
      for (auto& b : bypass_nodes_) {
        b.first->step = 1;
      }
    } else {
      for (auto& b : bypass_nodes_) {
        b.first->step = b.second;
      }
    }
  }

private:

  instr_cd(const block_type* clk, bool pos_edge)
    : clk_(clk)
    , pos_edge_(pos_edge)
    , prev_val_(false)
  {}

  std::vector<std::pair<instr_base*, uint32_t>> bypass_nodes_;
  const block_type* clk_;  
  bool pos_edge_;
  bool prev_val_;
};

///////////////////////////////////////////////////////////////////////////////

class instr_reg_base : public instr_base {
public:

  static instr_reg_base* create(regimpl* node, data_map_t& map);

  void init(regimpl* node, data_map_t& map) {
    next_     = map.at(node->next().id());
    enable_   = node->has_enable() ? map.at(node->enable().id()) : nullptr;
    reset_    = node->has_init_data() ? map.at(node->reset().id()) : nullptr;
    initdata_ = node->has_init_data() ? map.at(node->init_data().id()) : nullptr;
  }

protected:

  instr_reg_base(block_type* pipe, uint32_t pipe_size, block_type* dst, uint32_t size)
    : initdata_(nullptr)
    , pipe_(pipe)
    , pipe_size_(pipe_size)
    , reset_(nullptr)
    , enable_(nullptr)
    , next_(nullptr)
    , dst_(dst)
    , size_(size)
  {}

  const block_type* initdata_;
  block_type* pipe_;
  uint32_t pipe_size_;
  const block_type* reset_;
  const block_type* enable_;
  const block_type* next_;
  block_type* dst_;
  uint32_t size_;
};

template <bool is_scalar, bool is_pipe, bool has_init, bool has_enable>
class instr_reg : public instr_reg_base {
public:

  void destroy() override {
    this->~instr_reg();
    ::operator delete [](this);
  }

  void eval() override {
    if constexpr (is_scalar) {
      if constexpr (has_init) {
        // check reset state
        if (reset_ && static_cast<bool>(reset_[0])) {
          bv_copy_scalar(dst_, initdata_);
          if constexpr (is_pipe) {
            for (uint32_t i = 0; i < pipe_size_; i+= size_) {
              bv_copy_scalar(pipe_, i, initdata_, 0, size_);
            }
          }
          return;
        }
      }

      if constexpr (has_enable) {
        // check enable state
        if (enable_ && !static_cast<bool>(enable_[0]))
          return;
      }

      if constexpr (is_pipe) {
        // advance pipeline
        bv_slice_scalar(dst_, size_, pipe_, 0);
        bv_shr_scalar<false>(pipe_, pipe_size_, pipe_, pipe_size_, size_);
        bv_copy_scalar(pipe_, pipe_size_ - size_, next_, 0, size_);
      } else {
        // push next value
        bv_copy_scalar(dst_, next_);
      }
    } else {
      if constexpr (has_init) {
        // check reset state
        if (reset_ && static_cast<bool>(reset_[0])) {
          bv_copy(dst_, initdata_, size_);
          if constexpr (is_pipe) {
            for (uint32_t i = 0; i < pipe_size_; i+= size_) {
              bv_copy(pipe_, i, initdata_, 0, size_);
            }
          }
          return;
        }
      }

      if constexpr (has_enable) {
        // check enable state
        if (enable_ && !static_cast<bool>(enable_[0]))
          return;
      }

      if constexpr (is_pipe) {
        // advance pipeline
        bv_slice(dst_, size_, pipe_, 0);
        bv_shr<false>(pipe_, pipe_size_, pipe_, pipe_size_, size_);
        bv_copy(pipe_, pipe_size_ - size_, next_, 0, size_);
      } else {
        // push next value
        bv_copy(dst_, next_, size_);
      }
    }
  }

protected:

  instr_reg(block_type* pipe, uint32_t pipe_size, block_type* dst, uint32_t size)
    : instr_reg_base(pipe, pipe_size, dst, size)
  {}

  friend class instr_reg_base;
};

instr_reg_base* instr_reg_base::create(regimpl* node, data_map_t& map) {
  uint32_t dst_size  = node->size();
  uint32_t nblocks   = ceildiv<uint32_t>(dst_size, bitwidth_v<block_type>);
  uint32_t dst_bytes = sizeof(block_type) * nblocks;

  uint32_t pipe_size = dst_size * (node->length() - 1);
  uint32_t pipe_bytes = sizeof(block_type) * ceildiv<uint32_t>(pipe_size, bitwidth_v<block_type>);

  auto buf = new uint8_t[__aligned_sizeof(instr_reg_base) + dst_bytes + pipe_bytes]();
  auto buf_cur = buf + __aligned_sizeof(instr_reg_base);
  auto dst = (block_type*)buf_cur;
  map[node->id()] = dst;

  buf_cur += dst_bytes;
  auto pipe = (block_type*)buf_cur;

  bool is_scalar = (dst_size <= sizeof(block_type)) && (pipe_size <= sizeof(block_type));
  if (is_scalar) {
    if (1 == node->length()) {
      if (node->has_init_data()) {
        if (node->has_enable()) {
          return new (buf) instr_reg<true, false, true, true>(pipe, pipe_size, dst, dst_size);
        } else {
          return new (buf) instr_reg<true, false, true, false>(pipe, pipe_size, dst, dst_size);
        }
      } else {
        if (node->has_enable()) {
          return new (buf) instr_reg<true, false, false, true>(pipe, pipe_size, dst, dst_size);
        } else {
          return new (buf) instr_reg<true, false, false, false>(pipe, pipe_size, dst, dst_size);
        }
      }
    } else {
      if (node->has_init_data()) {
        if (node->has_enable()) {
          return new (buf) instr_reg<true, true, true, true>(pipe, pipe_size, dst, dst_size);
        } else {
          return new (buf) instr_reg<true, true, true, false>(pipe, pipe_size, dst, dst_size);
        }
      } else {
        if (node->has_enable()) {
          return new (buf) instr_reg<true, true, false, true>(pipe, pipe_size, dst, dst_size);
        } else {
          return new (buf) instr_reg<true, true, false, false>(pipe, pipe_size, dst, dst_size);
        }
      }
    }
  } else {
    if (1 == node->length()) {
      if (node->has_init_data()) {
        if (node->has_enable()) {
          return new (buf) instr_reg<false, false, true, true>(pipe, pipe_size, dst, dst_size);
        } else {
          return new (buf) instr_reg<false, false, true, false>(pipe, pipe_size, dst, dst_size);
        }
      } else {
        if (node->has_enable()) {
          return new (buf) instr_reg<false, false, false, true>(pipe, pipe_size, dst, dst_size);
        } else {
          return new (buf) instr_reg<false, false, false, false>(pipe, pipe_size, dst, dst_size);
        }
      }
    } else {
      if (node->has_init_data()) {
        if (node->has_enable()) {
          return new (buf) instr_reg<false, true, true, true>(pipe, pipe_size, dst, dst_size);
        } else {
          return new (buf) instr_reg<false, true, true, false>(pipe, pipe_size, dst, dst_size);
        }
      } else {
        if (node->has_enable()) {
          return new (buf) instr_reg<false, true, false, true>(pipe, pipe_size, dst, dst_size);
        } else {
          return new (buf) instr_reg<false, true, false, false>(pipe, pipe_size, dst, dst_size);
        }
      }
    }
  }
}

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
    , dst_(dst)
    , data_size_(data_size)
    , addr_size_(addr_size)
  {}

  ~instr_mem() {
    for (uint32_t i = 0; i < num_rdports_; ++i) {
      delete [] rdports_[i].data;
    }
  }

public:

  static instr_mem* create(memimpl* node, data_map_t& map) {
    uint32_t dst_size  = node->size();
    uint32_t dst_nblocks = ceildiv<uint32_t>(dst_size, bitwidth_v<block_type>);
    uint32_t dst_bytes = sizeof(block_type) * dst_nblocks;
    uint32_t data_size = node->data_width();
    uint32_t data_bytes = sizeof(block_type) * ceildiv<uint32_t>(data_size, bitwidth_v<block_type>);
    uint32_t addr_size = log2ceil(node->num_items());

    uint32_t num_rdports = node->is_sync_read() ? node->rdports().size() : 0;
    uint32_t rdports_bytes = 0;
    for (uint32_t i = 0; i < num_rdports; ++i) {
      rdports_bytes += sizeof(rdport_t);
    }

    uint32_t num_wrports = node->wrports().size();
    uint32_t wrports_bytes = 0;
    for (uint32_t i = 0; i < num_wrports; ++i) {
      wrports_bytes += sizeof(wrport_t);
    }

    auto buf = new uint8_t[__aligned_sizeof(instr_mem) + dst_bytes + rdports_bytes + wrports_bytes]();
    auto buf_cur = buf + __aligned_sizeof(instr_mem);
    auto dst = (block_type*)buf_cur;
    map[node->id()] = dst;

    buf_cur += dst_bytes;
    auto rdports = (rdport_t*)buf_cur;


    for (uint32_t i = 0; i < num_rdports; ++i) {
      auto p = node->rdports()[i];
      rdports[i].data = new block_type[data_bytes]();
      map[p->id()] = rdports[i].data;
    }

    buf_cur += rdports_bytes;
    auto wrports = (wrport_t*)buf_cur;

    if (node->has_init_data()) {
      bv_copy(dst, node->init_data().words(), dst_size);
    }

    return new (buf) instr_mem(rdports, num_rdports, wrports, num_wrports,
                               dst, data_size, addr_size);
  }

  void destroy() override {
    this->~instr_mem();
    ::operator delete [](this);
  }

  void init(memimpl* node, data_map_t& map) {
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
    // evaluate synchronous read ports
    for (const rdport_t *p = rdports_, *p_end = p + num_rdports_ ; p != p_end; ++p) {
      // check enable state
      if (p->enable && !static_cast<bool>(p->enable[0]))
        continue;
      // memory read
      auto addr = bv_cast<uint32_t>(p->addr, addr_size_);
      bv_slice(p->data, data_size_, dst_, addr * data_size_);
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

class instr_mrport_base : public instr_base {
public:

  static instr_mrport_base* create(mrportimpl* node, data_map_t& map) ;

protected:

  instr_mrport_base(const block_type* store,
                    block_type* dst,
                    uint32_t dst_size,
                    const block_type* addr,
                    uint32_t addr_size)
    : store_(store)
    , dst_(dst)
    , dst_size_(dst_size)
    , addr_(addr)
    , addr_size_(addr_size)
  {}

  const block_type* store_;
  block_type* dst_;
  uint32_t dst_size_;  
  const block_type* addr_;
  uint32_t addr_size_;
};

template <bool is_scalar>
class instr_mrport : public instr_mrport_base {
public:

  void destroy() override {
    this->~instr_mrport();
    ::operator delete [](this);
  }

  void eval() override {
    auto src_offset = bv_cast<uint32_t>(addr_, addr_size_) * dst_size_;
    auto src = store_ + (src_offset / bitwidth_v<block_type>);
    auto src_begin_rem = src_offset % bitwidth_v<block_type>;
    if constexpr (is_scalar) {
      bv_slice_vector_small(dst_, dst_size_, src, src_begin_rem);
    } else {
      bv_slice_vector(dst_, dst_size_, src, src_begin_rem);
    }
  }

private:

  instr_mrport(const block_type* store,
               block_type* dst,
               uint32_t dst_size,
               const block_type* addr,
               uint32_t addr_size)
    : instr_mrport_base(store, dst, dst_size, addr, addr_size)
  {}

  friend class instr_mrport_base;
};

instr_mrport_base* instr_mrport_base::create(mrportimpl* node, data_map_t& map) {
  uint32_t dst_size  = node->size();
  uint32_t nblocks   = ceildiv<uint32_t>(dst_size, bitwidth_v<block_type>);
  uint32_t dst_bytes = sizeof(block_type) * nblocks;

  auto buf = new uint8_t[__aligned_sizeof(instr_mrport_base) + dst_bytes]();
  auto buf_cur = buf + __aligned_sizeof(instr_mrport_base);
  auto dst = (block_type*)buf_cur;
  map[node->id()] = dst;

  auto store = map.at(node->mem()->id());
  auto addr = map.at(node->addr().id());
  auto addr_size = node->addr().size();

  bool is_scalar = (dst_size <= bitwidth_v<block_type>);
  if (is_scalar) {
    return new (buf) instr_mrport<true>(store, dst, dst_size, addr, addr_size);
  } else {
    return new (buf) instr_mrport<false>(store, dst, dst_size, addr, addr_size);
  }
}

///////////////////////////////////////////////////////////////////////////////

class instr_assert : public instr_base {
public:

  static instr_assert* create(assertimpl* node, data_map_t& map) {
    return new instr_assert(node, map);
  }

  void destroy() override {
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

  instr_assert(assertimpl* node, data_map_t& map)
    : cond_(map.at(node->cond().id()))
    , pred_(node->has_pred() ? map.at(node->pred().id()) : nullptr)
    , msg_(node->msg())
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

  static instr_time* create(timeimpl* node, data_map_t& map) {
    return new instr_time(node, map);
  }

  void destroy() override {
    delete this;
  }

  void eval() override {
    dst_ = tick_++;
  }

private:

  ch_tick tick_;
  sdata_type dst_;

  instr_time(timeimpl* node, data_map_t& map)
    : tick_(0)
    , dst_(node->size()) {
    map[node->id()] = dst_.words();
  }
};

///////////////////////////////////////////////////////////////////////////////

class instr_print : public instr_base {
public:

  static instr_print* create(printimpl* node, data_map_t& map) {
    return new instr_print(node, map);
  }

  void destroy() override {
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

  instr_print(printimpl* node, data_map_t& map)
    : enum_strings_(node->enum_strings())
    , pred_(node->has_pred() ? map.at(node->pred().id()) : nullptr)
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

  static instr_udfc* create(udfcimpl* node, data_map_t& map) {
    return new instr_udfc(node, map);
  }

  void destroy() override {
    delete this;
  }

  void eval() override {
    udf_->eval(dst_, srcs_);
  }

private:

  instr_udfc(udfcimpl* node, data_map_t& map)
    : udf_(node->udf())
    , dst_(node->size()) {
    srcs_.resize(node->srcs().size());
    for (uint32_t i = 0, n = udf_->inputs_size().size(); i < n; ++i) {
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

  static instr_udfs* create(udfsimpl* node, data_map_t& map) {
    return new instr_udfs(node, map);
  }

  void destroy() override {
    delete this;
  }

  void init(udfsimpl* node, data_map_t& map) {
    reset_ = node->has_init_data() ? map.at(node->reset().id()) : nullptr;    
    for (uint32_t i = 0, n = udf_->inputs_size().size(); i < n; ++i) {
      auto& src = node->src(i);
      srcs_[i].emplace(const_cast<block_type*>(map.at(src.id())), src.size());
    }
  }

  void eval() override {
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

  instr_udfs(udfsimpl* node, data_map_t& map)
    : udf_(node->udf())
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
  for (auto constant : constants_) {
    delete [] constant;
  }
}

void simref::initialize(const std::vector<lnodeimpl*>& eval_list) {
  data_map_t data_map;
  std::unordered_map<uint32_t, instr_base*> instr_map;
  std::unordered_map<uint32_t, uint32_t> node_map;
  instr_map.reserve(eval_list.size());
  instrs_.reserve(eval_list.size());

  auto ctx = eval_list.back()->ctx();

  // lower synchronous nodes
  for (auto node : ctx->snodes()) {
    switch (node->type()) {
    case type_reg:
      instr_map[node->id()] = instr_reg_base::create(reinterpret_cast<regimpl*>(node), data_map);
      break;
    case type_mem:
      instr_map[node->id()] = instr_mem::create(reinterpret_cast<memimpl*>(node), data_map);
      break;
    case type_udfs:
      instr_map[node->id()] = instr_udfs::create(reinterpret_cast<udfsimpl*>(node), data_map);
      break;
    default:
      break;
    }
  }

  // lower all nodes
  for (auto node : eval_list) {
    instr_base* instr = nullptr;
    switch (node->type()) {
    case type_undef:
      assert(false);
      break;
    case type_lit:
      data_map[node->id()] = this->create_constants(reinterpret_cast<litimpl*>(node));
      break;
    case type_proxy:
      instr = instr_proxy_base::create(reinterpret_cast<proxyimpl*>(node), data_map);
      break;
    case type_input: {
      auto input = reinterpret_cast<inputimpl*>(node);
      if (input->has_binding()) {
        data_map[node->id()] = data_map.at(input->binding().id());
      } else {
        data_map[node->id()] = input->value()->words();
      }
    } break;
    case type_output: {
      auto output = reinterpret_cast<outputimpl*>(node);
      data_map[node->id()] = data_map.at(output->src(0).id());
      if (!output->has_binding()) {
        instr = instr_output_base::create(output, data_map);
      }
    } break;
    case type_alu:
      instr = instr_alu_base::create(reinterpret_cast<aluimpl*>(node), data_map);
      break;
    case type_sel:
      instr = instr_select::create(reinterpret_cast<selectimpl*>(node), data_map);
      break;
    case type_cd:
      instr = instr_cd::create(reinterpret_cast<cdimpl*>(node), data_map);
      break;
    case type_reg:
      instr = instr_map.at(node->id());
      reinterpret_cast<instr_reg_base*>(instr)->init(reinterpret_cast<regimpl*>(node), data_map);
      break;
    case type_mem:
      instr = instr_map.at(node->id());
      reinterpret_cast<instr_mem*>(instr)->init(reinterpret_cast<memimpl*>(node), data_map);
      break;
    case type_mrport: {
      auto port = reinterpret_cast<mrportimpl*>(node);
      if (!port->is_sync_read()) {
        instr = instr_mrport_base::create(port, data_map);
      }
    } break;
    case type_mwport:
    case type_bind:
    case type_bindin:
    case type_bindout:
      // skip
      break;    
    case type_tap:
      instr = instr_output_base::create(reinterpret_cast<tapimpl*>(node), data_map);
      break;
    case type_assert:
      instr = instr_assert::create(reinterpret_cast<assertimpl*>(node), data_map);
      break;
    case type_time:
      instr = instr_time::create(reinterpret_cast<timeimpl*>(node), data_map);
      break;
    case type_print:
      instr = instr_print::create(reinterpret_cast<printimpl*>(node), data_map);
      break;
    case type_udfc:
      instr = instr_udfc::create(reinterpret_cast<udfcimpl*>(node), data_map);
      break;
    case type_udfs:
      instr = instr_map.at(node->id());
      reinterpret_cast<instr_udfs*>(instr)->init(reinterpret_cast<udfsimpl*>(node), data_map);
      break;
    }

    if (instr) {
      instr_map[node->id()] = instr;
      node_map[instrs_.size()] = node->id();
      instrs_.emplace_back(instr);
    }
  }

  // setup clock domains bypass
  for (auto cd : ctx->cdomains()) {
    std::unordered_set<uint32_t> bypass_nodes;
    this->generate_clk_bypass_list(bypass_nodes, ctx, cd->id());
    auto cd_instr = reinterpret_cast<instr_cd*>(instr_map.at(cd->id()));
    uint32_t i = 0, n = instrs_.size();
    for (; i < n;) {
      if (instrs_[i++] == cd_instr)
        break;
    }
    bool skip_enabled = false;
    uint32_t skip_start = 0;
    for (;i < n; ++i) {
      auto node_id = node_map.at(i);
      bool bypass = bypass_nodes.count(node_id);
      if (bypass && !skip_enabled) {
        skip_enabled = true;
        skip_start = i;
      } else
      if (!bypass && skip_enabled) {
        skip_enabled = false;
        cd_instr->add_bypass(instrs_[skip_start-1], i - skip_start + 1);
      }
    }
    if (skip_enabled) {
      cd_instr->add_bypass(instrs_[skip_start-1], i - skip_start + 1);
    }
  }
}

void simref::generate_clk_bypass_list(std::unordered_set<uint32_t>& out, context* ctx, uint32_t cd_id) {
  std::unordered_set<uint32_t> visited_nodes;
  std::unordered_set<uint32_t> changed_nodes;

  std::function<bool (lnodeimpl*)> dfs_visit = [&](lnodeimpl* node)->bool {
    if (visited_nodes.count(node->id())) {
      return (changed_nodes.count(node->id()) != 0);
    }
    visited_nodes.emplace(node->id());

    auto type = node->type();
    bool changed = false;

    if (is_snode_type(type)) {
      if ((type_reg == type
        && cd_id == reinterpret_cast<regimpl*>(node)->cd().id())
       || (type_mem == type
        && reinterpret_cast<memimpl*>(node)->has_cd()
        && cd_id == reinterpret_cast<memimpl*>(node)->cd().id())
       || (type_udfs == type
        && cd_id == reinterpret_cast<udfsimpl*>(node)->cd().id()))
        return false;

      if (type_reg == type
       || (type_mem == type && reinterpret_cast<memimpl*>(node)->has_cd())
       || type_udfs == type) {
        // update changeset here in case there is a cycle with the source nodes
        changed_nodes.emplace(node->id());
        changed = true;
      }
    }

    switch (type) {
    case type_cd:
    case type_input:
    case type_time:
    case type_print:
      changed = true;
      [[fallthrough]];
    default:
      // visit source nodes
      for (auto& src : node->srcs()) {
        changed |= dfs_visit(src.impl());
      }
      break;
    }

    if (changed) {
      changed_nodes.emplace(node->id());
    }

    return changed;
  };

  // visit output nodes
  for (auto node : ctx->outputs()) {
    dfs_visit(node);
  }
  for (auto node : ctx->taps()) {
    dfs_visit(node);
  }
  for (auto node : ctx->gtaps()) {
    dfs_visit(node);
  }

  // create bypass list
  for (auto node : ctx->nodes()) {
    if (!changed_nodes.count(node->id()))
      out.emplace(node->id());
  }
}

block_type* simref::create_constants(litimpl* node) {
  auto num_words = ceildiv<uint32_t>(node->size(), bitwidth_v<block_type>);
  auto constant = new block_type[num_words];
  std::copy_n(node->value().words(), num_words, constant);
  constants_.push_back(constant);
  return constant;
}

void simref::eval() {
  for (uint32_t i = 0, n = instrs_.size(); i < n;) {
    instrs_[i]->eval();
    i += instrs_[i]->step;
  }
}
