#include "simref.h"
#include "bindimpl.h"
#include "litimpl.h"
#include "regimpl.h"
#include "memimpl.h"
#include "ioimpl.h"
#include "selectimpl.h"
#include "proxyimpl.h"
#include "memimpl.h"
#include "opimpl.h"
#include "assertimpl.h"
#include "printimpl.h"
#include "timeimpl.h"
#include "udfimpl.h"
#include "compile.h"

using namespace ch::internal;
//using namespace ch::internal::simref;

namespace ch::internal::simref {

struct instr_base {

  instr_base() {}

  virtual ~instr_base() {}

  virtual void destroy() = 0;

  virtual void eval() = 0;
};

using data_map_t  = std::unordered_map<uint32_t, const block_type*>;
using instr_map_t = std::unordered_map<uint32_t, instr_base*>;
using node_map_t  = std::unordered_map<uint32_t, uint32_t>;

#define __aligned_sizeof(...) (4*((sizeof(__VA_ARGS__) + 3)/4))

///////////////////////////////////////////////////////////////////////////////

class instr_proxy_base : public instr_base {
public:

  static instr_proxy_base* create(proxyimpl* node, data_map_t& map);

protected:

  struct range_t {
    const block_type* data;
    uint32_t offset;
    uint32_t length;
  };

  instr_proxy_base(block_type* dst, uint32_t dst_size)
    : dst_(dst)
    , dst_size_(dst_size)
  {}

  block_type* dst_;
  uint32_t dst_size_;
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

  instr_slice(block_type* dst, uint32_t dst_size,
              const block_type* src_data, uint32_t src_offset)
    : instr_proxy_base(dst, dst_size)
    , src_data_(src_data)
    , src_offset_(src_offset)
  {}

  const block_type* src_data_;
  uint32_t src_offset_;

  friend class instr_proxy_base;
};

template <bool is_scalar>
class instr_proxy : public instr_proxy_base {
public:

  void destroy() override {
    this->~instr_proxy();
    ::operator delete [](this);
  }

  void eval() override {
    if constexpr (is_scalar) {
      if (dst_size_ <= bitwidth_v<block_type>) {
        block_type dst_block = 0;
        uint32_t dst_offset = 0;
        for (auto *r = ranges_, *r_end = r + num_ranges_ ;r != r_end; ++r) {
          uint32_t lr = (bitwidth_v<block_type> - r->length);
          auto src_block = (block_type((r->data[0] >> r->offset) << lr) >> lr);
          dst_block |= src_block << dst_offset;
          dst_offset += r->length;
        }
        dst_[0] = dst_block;
      } else {
        auto dst = dst_;
        block_type dst_block = 0;
        uint32_t dst_offset = 0;
        for (auto *r = ranges_, *r_end = r + num_ranges_ ;r != r_end; ++r) {
          auto dst_lsb = dst_offset % bitwidth_v<block_type>;
          uint32_t lr = (bitwidth_v<block_type> - r->length);
          auto src_block = (block_type((r->data[0] >> r->offset) << lr) >> lr);
          dst_block |= src_block << dst_lsb;
          if (dst_lsb >= lr) {
            *dst++ = dst_block; // flush current block
            dst_block = dst_lsb ? (src_block >> (bitwidth_v<block_type> - dst_lsb)) : 0;
          }
          dst_offset += r->length;
        }
        if ((dst_size_ % bitwidth_v<block_type>) != 0) {
          *dst = dst_block; // flush last block
        }
      }
    } else {
      uint32_t dst_offset(0);
      for (auto *r = ranges_, *r_end = r + num_ranges_ ;r != r_end; ++r) {
        auto dst_idx = dst_offset / bitwidth_v<block_type>;
        auto dst_lsb = dst_offset % bitwidth_v<block_type>;
        bv_copy_vector(dst_ + dst_idx, dst_lsb, r->data, r->offset, r->length);
        dst_offset += r->length;
      }
    }
  }

private:

  instr_proxy(block_type* dst, uint32_t dst_size, const range_t* ranges, uint32_t num_ranges)
    : instr_proxy_base(dst, dst_size)
    , ranges_(ranges)
    , num_ranges_(num_ranges)
  {}

  const range_t* ranges_;
  uint32_t num_ranges_;

  friend class instr_proxy_base;
};

instr_proxy_base* instr_proxy_base::create(proxyimpl* node, data_map_t& map) {
  uint32_t dst_size = node->size();
  uint32_t dst_nblocks = ceildiv(dst_size, bitwidth_v<block_type>);
  uint32_t dst_bytes = sizeof(block_type) * dst_nblocks;
  uint32_t num_ranges = node->ranges().size();

  if (1 == num_ranges
   && node->range(0).length == dst_size) {
    auto buf = new uint8_t[__aligned_sizeof(instr_slice<false>) + dst_bytes]();
    auto buf_cur = buf + __aligned_sizeof(instr_slice<false>);
    auto dst = (block_type*)buf_cur;
    map[node->id()] = dst;
    bv_init(dst, dst_size);

    auto& src_range = node->range(0);
    auto& src = node->src(src_range.src_idx);
    auto src_idx = src_range.src_offset / bitwidth_v<block_type>;
    auto src_lsb = src_range.src_offset % bitwidth_v<block_type>;

    bool is_scalar = (dst_size <= bitwidth_v<block_type>);
    if (is_scalar) {
      return new (buf) instr_slice<true>(dst, dst_size, map.at(src.id()) + src_idx, src_lsb);
    } else {
      return new (buf) instr_slice<false>(dst, dst_size, map.at(src.id()) + src_idx, src_lsb);
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
    bv_init(dst, dst_size);

    buf_cur += dst_bytes;

    bool is_scalar = true;
    auto ranges = (instr_proxy_base::range_t*)buf_cur;
    for (uint32_t i = 0; i < num_ranges; ++i) {
      auto& dst_range = ranges[i];
      auto& src_range = node->range(i);
      auto& src = node->src(src_range.src_idx);
      uint32_t src_idx = src_range.src_offset / bitwidth_v<block_type>;
      uint32_t src_lsb = src_range.src_offset % bitwidth_v<block_type>;
      dst_range.data   = map.at(src.id()) + src_idx;
      dst_range.offset = src_lsb;
      dst_range.length = src_range.length;
      is_scalar &= (src_lsb + src_range.length <= bitwidth_v<block_type>);
    }

    if (is_scalar) {
      return new (buf) instr_proxy<true>(dst, dst_size, ranges, num_ranges);
    } else {
      return new (buf) instr_proxy<false>(dst, dst_size, ranges, num_ranges);
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

class instr_op_base : public instr_base {
public:

  static instr_op_base* create(opimpl* node, data_map_t& map);

protected:

  instr_op_base(block_type* dst,
                 uint32_t dst_size,
                 const block_type* src0,
                 uint32_t src0_size,
                 const block_type* src1,
                 uint32_t src1_size)
    : dst_(dst)
    , dst_size_(dst_size)
    , src0_(src0)
    , src0_size_(src0_size)
    , src1_(src1)
    , src1_size_(src1_size)
  {}

  block_type* dst_;
  uint32_t dst_size_;
  const block_type* src0_;
  uint32_t src0_size_;
  const block_type* src1_;
  uint32_t src1_size_;
};

template <ch_op op, bool is_signed, bool is_scalar, bool resize_opds>
class instr_op : instr_op_base {
public:

  void destroy() override {
    this->~instr_op();
    ::operator delete [](this);
  }

  void eval() override {
    //--
    using bit_accessor_t = StaticBitAccessor<is_signed, resize_opds, block_type>;

    switch (op) {
    case ch_op::eq:
      if constexpr (is_scalar) {
        bv_assign_scalar(dst_, bv_eq_scalar<is_signed, block_type, bit_accessor_t>(src0_, src0_size_, src1_, src1_size_));
      } else {
        bv_assign_scalar(dst_, bv_eq_vector<is_signed, block_type, bit_accessor_t>(src0_, src0_size_, src1_, src1_size_));
      }
      break;
    case ch_op::ne:
      if constexpr (is_scalar) {
        bv_assign_scalar(dst_, !bv_eq_scalar<is_signed, block_type, bit_accessor_t>(src0_, src0_size_, src1_, src1_size_));
      } else {
        bv_assign_scalar(dst_, !bv_eq_vector<is_signed, block_type, bit_accessor_t>(src0_, src0_size_, src1_, src1_size_));
      }
      break;

    case ch_op::lt:
      if constexpr (is_scalar) {
        bv_assign_scalar(dst_, bv_lt_scalar<is_signed, block_type, bit_accessor_t>(src0_, src0_size_, src1_, src1_size_));
      } else {
        bv_assign_scalar(dst_, bv_lt_vector<is_signed, block_type, bit_accessor_t>(src0_, src0_size_, src1_, src1_size_));
      }
      break;
    case ch_op::gt:
      if constexpr (is_scalar) {
        bv_assign_scalar(dst_, bv_lt_scalar<is_signed, block_type, bit_accessor_t>(src1_, src1_size_, src0_, src0_size_));
      } else {
        bv_assign_scalar(dst_, bv_lt_vector<is_signed, block_type, bit_accessor_t>(src1_, src1_size_, src0_, src0_size_));
      }
      break;
    case ch_op::le:
      if constexpr (is_scalar) {
        bv_assign_scalar(dst_, !bv_lt_scalar<is_signed, block_type, bit_accessor_t>(src1_, src1_size_, src0_, src0_size_));
      } else {
        bv_assign_scalar(dst_, !bv_lt_vector<is_signed, block_type, bit_accessor_t>(src1_, src1_size_, src0_, src0_size_));
      }
      break;
    case ch_op::ge:
      if constexpr (is_scalar) {
        bv_assign_scalar(dst_, !bv_lt_scalar<is_signed, block_type, bit_accessor_t>(src0_, src0_size_, src1_, src1_size_));
      } else {
        bv_assign_scalar(dst_, !bv_lt_vector<is_signed, block_type, bit_accessor_t>(src0_, src0_size_, src1_, src1_size_));
      }
      break;

    case ch_op::notl:
      if constexpr (is_scalar) {
        bv_assign_scalar(dst_, bv_notl_scalar(src0_));
      } else {
        bv_assign_scalar(dst_, bv_notl_vector(src0_, src0_size_));
      }
      break;
    case ch_op::andl:
      if constexpr (is_scalar) {
        bv_assign_scalar(dst_, bv_andl_scalar(src0_, src1_));
      } else {
        bv_assign_scalar(dst_, bv_andl_vector(src0_, src0_size_, src1_, src1_size_));
      }
      break;
    case ch_op::orl:
      if constexpr (is_scalar) {
        bv_assign_scalar(dst_, bv_orl_scalar(src0_, src1_));
      } else {
        bv_assign_scalar(dst_, bv_orl_vector(src0_, src0_size_, src1_, src1_size_));
      }
      break;

    case ch_op::inv:
      if constexpr (is_scalar) {
        bv_inv_scalar<is_signed, block_type, bit_accessor_t>(dst_, dst_size_, src0_, src0_size_);
      } else {
        bv_inv_vector<is_signed, block_type, bit_accessor_t>(dst_, dst_size_, src0_, src0_size_);
      }
      break;
    case ch_op::andb:
      if constexpr (is_scalar) {
        bv_and_scalar<is_signed, block_type, bit_accessor_t>(dst_, dst_size_, src0_, src0_size_, src1_, src1_size_);
      } else {
        bv_and_vector<is_signed, block_type, bit_accessor_t>(dst_, dst_size_, src0_, src0_size_, src1_, src1_size_);
      }
      break;
    case ch_op::orb:
      if constexpr (is_scalar) {
        bv_or_scalar<is_signed, block_type, bit_accessor_t>(dst_, dst_size_, src0_, src0_size_, src1_, src1_size_);
      } else {
        bv_or_vector<is_signed, block_type, bit_accessor_t>(dst_, dst_size_, src0_, src0_size_, src1_, src1_size_);
      }
      break;
    case ch_op::xorb:
      if constexpr (is_scalar) {
        bv_xor_scalar<is_signed, block_type, bit_accessor_t>(dst_, dst_size_, src0_, src0_size_, src1_, src1_size_);
      } else {
        bv_xor_vector<is_signed, block_type, bit_accessor_t>(dst_, dst_size_, src0_, src0_size_, src1_, src1_size_);
      }
      break;

    case ch_op::andr:
      if constexpr (is_scalar) {
        bv_assign_scalar(dst_, bv_andr_scalar(src0_, src0_size_));
      } else {
        bv_assign_scalar(dst_, bv_andr_vector(src0_, src0_size_));
      }
      break;
    case ch_op::orr:
      if constexpr (is_scalar) {
        bv_assign_scalar(dst_, bv_orr_scalar(src0_));
      } else {
        bv_assign_scalar(dst_, bv_orr_vector(src0_, src0_size_));
      }
      break;
    case ch_op::xorr:
      if constexpr (is_scalar) {
        bv_assign_scalar(dst_, bv_xorr_scalar(src0_));
      } else {
        bv_assign_scalar(dst_, bv_xorr_vector(src0_, src0_size_));
      }
      break;

    case ch_op::shl:
      if constexpr (is_scalar) {
        auto dist = bv_cast<uint32_t>(src1_, src1_size_);
        bv_shl_scalar(dst_, dst_size_, src0_, dist);
     } else {
        auto dist = bv_cast<uint32_t>(src1_, src1_size_);
        bv_shl_vector(dst_, dst_size_, src0_, src0_size_, dist);
      }
      break;
    case ch_op::shr:
      if constexpr (is_scalar) {
        auto dist = bv_cast<uint32_t>(src1_, src1_size_);
        bv_shr_scalar<is_signed>(dst_, dst_size_, src0_, src0_size_, dist);
      } else {
        auto dist = bv_cast<uint32_t>(src1_, src1_size_);
        bv_shr_vector<is_signed>(dst_, dst_size_, src0_, src0_size_, dist);
      }
      break;

    case ch_op::neg:
      if constexpr (is_scalar) {
        bv_neg_scalar<is_signed, block_type, bit_accessor_t>(dst_, dst_size_, src0_, src0_size_);
      } else {
        bv_neg_vector<is_signed, block_type, bit_accessor_t>(dst_, dst_size_, src0_, src0_size_);
      }
      break;
    case ch_op::add:
      if constexpr (is_scalar) {
        bv_add_scalar<is_signed, block_type, bit_accessor_t>(dst_, dst_size_, src0_, src0_size_, src1_, src1_size_);
      } else {
        bv_add_vector<is_signed, block_type, bit_accessor_t>(dst_, dst_size_, src0_, src0_size_, src1_, src1_size_);
      }
      break;
    case ch_op::sub:
      if constexpr (is_scalar) {
        bv_sub_scalar<is_signed, block_type, bit_accessor_t>(dst_, dst_size_, src0_, src0_size_, src1_, src1_size_);
      } else {
        bv_sub_vector<is_signed, block_type, bit_accessor_t>(dst_, dst_size_, src0_, src0_size_, src1_, src1_size_);
      }
      break;

    case ch_op::mul:
      if constexpr (is_scalar) {
        bv_mul_scalar<is_signed>(dst_, dst_size_, src0_, src0_size_, src1_, src1_size_);
      } else {
        bv_mul_vector<is_signed>(dst_, dst_size_, src0_, src0_size_, src1_, src1_size_);
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

  instr_op(block_type* dst, uint32_t dst_size_,
            const block_type* src0, uint32_t src0_size_,
            const block_type* src1, uint32_t src1_size)
    : instr_op_base(dst, dst_size_,
                     src0, src0_size_,
                     src1, src1_size)
    {}

  friend class instr_op_base;
};

instr_op_base* instr_op_base::create(opimpl* node, data_map_t& map) {
  uint32_t dst_size = node->size();
  bool is_signed = node->is_signed();

  const block_type* src0 = nullptr;
  uint32_t src0_size = 0;
  const block_type* src1 = nullptr;
  uint32_t src1_size = 0;

  bool is_scalar = (dst_size <= bitwidth_v<block_type>);

  // access source node data
  if (node->srcs().size() > 0) {
    src0 = map.at(node->src(0).id());
    src0_size = node->src(0).size();
    is_scalar &= (src0_size <= bitwidth_v<block_type>);
    if (node->srcs().size() > 1) {
      src1 = map.at(node->src(1).id());
      src1_size = node->src(1).size();
      if (CH_OP_CLASS(node->op()) != op_flags::shift) {
        is_scalar &= (src1_size <= bitwidth_v<block_type>);
      }
    }
  }

  // determine is operands need resizing
  bool resize_opds = node->should_resize_opds();

  uint32_t dst_bytes = sizeof(block_type) * ceildiv(dst_size, bitwidth_v<block_type>);

  auto buf = new uint8_t[__aligned_sizeof(instr_op_base) + dst_bytes]();
  auto buf_cur = buf + __aligned_sizeof(instr_op_base);
  auto dst = (block_type*)buf_cur;
  map[node->id()] = dst;
  bv_init(dst, dst_size);

#define CREATE_OP_INST(op, sign_enable, resize_enable) \
  case op: \
    if (is_scalar) { \
      if (sign_enable && is_signed) { \
        if (resize_enable && resize_opds) { \
          return new (buf) instr_op<op, true, true, true>(dst, dst_size, src0, src0_size, src1, src1_size); \
        } else { \
          return new (buf) instr_op<op, true, true, false>(dst, dst_size, src0, src0_size, src1, src1_size); \
        }  \
      } else { \
        if (resize_enable && resize_opds) { \
          return new (buf) instr_op<op, false, true, true>(dst, dst_size, src0, src0_size, src1, src1_size); \
        } else { \
          return new (buf) instr_op<op, false, true, false>(dst, dst_size, src0, src0_size, src1, src1_size); \
        } \
      } \
    } else { \
      if (sign_enable && is_signed) { \
        if (resize_enable && resize_opds) { \
          return new (buf) instr_op<op, true, false, true>(dst, dst_size, src0, src0_size, src1, src1_size); \
        } else { \
          return new (buf) instr_op<op, true, false, false>(dst, dst_size, src0, src0_size, src1, src1_size); \
        }  \
      } else { \
        if (resize_enable && resize_opds) { \
          return new (buf) instr_op<op, false, false, true>(dst, dst_size, src0, src0_size, src1, src1_size); \
        } else { \
          return new (buf) instr_op<op, false, false, false>(dst, dst_size, src0, src0_size, src1, src1_size); \
        } \
      } \
    }

  switch (node->op()) {
  CREATE_OP_INST(ch_op::eq, true, true);
  CREATE_OP_INST(ch_op::ne, true, true);
  CREATE_OP_INST(ch_op::lt, true, true);
  CREATE_OP_INST(ch_op::gt, true, true);
  CREATE_OP_INST(ch_op::le, true, true);
  CREATE_OP_INST(ch_op::ge, true, true);
  CREATE_OP_INST(ch_op::notl, false, false);
  CREATE_OP_INST(ch_op::andl, false, false);
  CREATE_OP_INST(ch_op::orl, false, false);
  CREATE_OP_INST(ch_op::inv, true, true);
  CREATE_OP_INST(ch_op::andb, true, true);
  CREATE_OP_INST(ch_op::orb, true, true);
  CREATE_OP_INST(ch_op::xorb, true, true);
  CREATE_OP_INST(ch_op::andr, false, false);
  CREATE_OP_INST(ch_op::orr, false, false);
  CREATE_OP_INST(ch_op::xorr, false, false);
  CREATE_OP_INST(ch_op::shl, false, false);
  CREATE_OP_INST(ch_op::shr, true, false);
  CREATE_OP_INST(ch_op::neg, true, true);
  CREATE_OP_INST(ch_op::add, true, true);
  CREATE_OP_INST(ch_op::sub, true, true);
  CREATE_OP_INST(ch_op::mul, true, false);
  CREATE_OP_INST(ch_op::div, true, false);
  CREATE_OP_INST(ch_op::mod, true, false);
  CREATE_OP_INST(ch_op::pad, true, false);
  default:
    CH_ABORT("invalid opcode");
  }
#undef CREATE_OP_INST
}

///////////////////////////////////////////////////////////////////////////////

class instr_select_base : public instr_base {
public:

  static instr_select_base* create(selectimpl* node, data_map_t& map);

protected:

  instr_select_base(block_type* dst, uint32_t size,
                    const block_type** srcs, uint32_t num_srcs)
    : dst_(dst)
    , size_(size)
    , srcs_(srcs)
    , srcs_last_(srcs + num_srcs - 1)
  {}

  block_type* dst_;
  uint32_t size_;
  const block_type** srcs_;
  const block_type** srcs_last_;
};

template <bool is_scalar>
class instr_select : public instr_select_base {
public:

  void destroy() override {
    this->~instr_select();
    ::operator delete [](this);
  }

  void eval() override {
    auto *src = srcs_, *last = srcs_last_;
    for (;src < last; src += 2) {
      if (static_cast<bool>(**src)) {
        ++src;
        break;
      }
    }
    if constexpr (is_scalar) {
      bv_copy_scalar(dst_, *src);
    } else {
      bv_copy_vector(dst_, *src, size_);
    }
  }

private:

  instr_select(block_type* dst, uint32_t size,
               const block_type** srcs, uint32_t num_srcs)
    : instr_select_base(dst, size, srcs, num_srcs)
  {}

  friend class instr_select_base;
};

template <bool is_scalar>
class instr_case : public instr_select_base {
public:

  void destroy() override {
    this->~instr_case();
    ::operator delete [](this);
  }

  void eval() override {
    auto *key = srcs_, *src = srcs_ + 1, *last = srcs_last_;
    for (;src < last; src += 2) {
      if constexpr (is_scalar) {
        if (bv_eq_scalar<false, block_type, ClearBitAccessor<block_type>>(*key, key_size_, *src, key_size_)) {
          ++src;
          break;
        }
      } else {
        if (bv_eq_vector<false, block_type, ClearBitAccessor<block_type>>(*key, key_size_, *src, key_size_)) {
          ++src;
          break;
        }
      }
    }
    if constexpr (is_scalar) {
      bv_copy_scalar(dst_, *src);
    } else {
      bv_copy_vector(dst_, *src, size_);
    }
  }

private:

  instr_case(block_type* dst, uint32_t size,
             const block_type** srcs, uint32_t num_srcs,
             uint32_t key_size)
    : instr_select_base(dst, size, srcs, num_srcs)
    , key_size_(key_size)
  {}

  uint32_t key_size_;

  friend class instr_select_base;
};

instr_select_base* instr_select_base::create(selectimpl* node, data_map_t& map) {
  uint32_t dst_size = node->size();
  uint32_t dst_nblocks = ceildiv(dst_size, bitwidth_v<block_type>);
  uint32_t dst_bytes = sizeof(block_type) * dst_nblocks;

  uint32_t num_srcs = node->srcs().size();
  uint32_t src_bytes = sizeof(block_type*) * num_srcs;

  bool is_scalar = dst_size <= bitwidth_v<block_type>;
  if (node->has_key()) {
    uint32_t key_size = node->src(0).size();
    is_scalar &= key_size <= bitwidth_v<block_type>;

    auto buf = new uint8_t[__aligned_sizeof(instr_case<false>) + dst_bytes + src_bytes]();
    auto buf_cur = buf + __aligned_sizeof(instr_case<false>);
    auto dst = (block_type*)buf_cur;
    map[node->id()] = dst;
    bv_init(dst, dst_size);
    buf_cur += dst_bytes;

    auto srcs = (const block_type**)buf_cur;
    for (uint32_t i = 0; i < num_srcs; ++i) {
      srcs[i] = map.at(node->src(i).id());
    }

    if (is_scalar) {
      return new (buf) instr_case<true>(dst, dst_size, srcs, num_srcs, key_size);
    } else {
      return new (buf) instr_case<false>(dst, dst_size, srcs, num_srcs, key_size);
    }
  } else {
    auto buf = new uint8_t[__aligned_sizeof(instr_select<false>) + dst_bytes + src_bytes]();
    auto buf_cur = buf + __aligned_sizeof(instr_select<false>);
    auto dst = (block_type*)buf_cur;
    map[node->id()] = dst;
    bv_init(dst, dst_size);
    buf_cur += dst_bytes;

    auto srcs = (const block_type**)buf_cur;
    for (uint32_t i = 0; i < num_srcs; ++i) {
      srcs[i] = map.at(node->src(i).id());
    }

    if (is_scalar) {
      return new (buf) instr_select<true>(dst, dst_size, srcs, num_srcs);
    } else {
      return new (buf) instr_select<false>(dst, dst_size, srcs, num_srcs);
    }
  }
}

///////////////////////////////////////////////////////////////////////////////

class instr_cd : public instr_base {
public:

  static instr_cd* create(cdimpl* node, data_map_t& map) {
    return new instr_cd(node, map);
  }

  void destroy() override {
    delete this;
  }

  void eval() override {
    auto clk = static_cast<bool>(clk_[0]);
    dst_ = (clk ^ prev_clk_) && (clk ^ neg_edge_);
    prev_clk_ = clk;
  }

private:

  instr_cd(cdimpl* node, data_map_t& map)
    : dst_(1, false)
    , clk_(map.at(node->clk().id()))
    , neg_edge_(!node->pos_edge())
    , prev_clk_(false) {
    map[node->id()] = dst_.words();
  }

  sdata_type dst_;
  const block_type* clk_;
  bool neg_edge_;
  bool prev_clk_;  
};

///////////////////////////////////////////////////////////////////////////////

class instr_reg_base : public instr_base {
public:

  static instr_reg_base* create(regimpl* node, data_map_t& map);

  void init(regimpl* node, data_map_t& map) {
    cd_       = map.at(node->cd().id());
    initdata_ = node->has_init_data() ? map.at(node->init_data().id()) : nullptr;
    reset_    = node->has_init_data() ? map.at(node->reset().id()) : nullptr;
    enable_   = node->has_enable() ? map.at(node->enable().id()) : nullptr;
    next_     = map.at(node->next().id());
  }

protected:

  instr_reg_base(block_type* dst, uint32_t size)
    : cd_(nullptr)
    , initdata_(nullptr)
    , reset_(nullptr)
    , enable_(nullptr)
    , next_(nullptr)
    , dst_(dst)
    , size_(size)
  {}

  const block_type* cd_;
  const block_type* initdata_;
  const block_type* reset_;
  const block_type* enable_;
  const block_type* next_;
  block_type* dst_;
  uint32_t size_;
};

template <bool is_scalar, bool has_init, bool has_enable>
class instr_reg : public instr_reg_base {
public:

  void destroy() override {
    this->~instr_reg();
    ::operator delete [](this);
  }

  void eval() override {
    if (!static_cast<bool>(cd_[0]))
      return;

    if constexpr (is_scalar) {
      if constexpr (has_init) {
        if (static_cast<bool>(reset_[0])) {
          bv_copy_scalar(dst_, initdata_);
          return;
        }
      }

      if constexpr (has_enable) {
        if (!static_cast<bool>(enable_[0]))
          return;
      }

      bv_copy_scalar(dst_, next_);
    } else {
      if constexpr (has_init) {
        if (static_cast<bool>(reset_[0])) {
          bv_copy_vector(dst_, initdata_, size_);
          return;
        }
      }

      if constexpr (has_enable) {
        if (!static_cast<bool>(enable_[0]))
          return;
      }

      bv_copy_vector(dst_, next_, size_);
    }
  }

protected:

  instr_reg(block_type* dst, uint32_t size)
    : instr_reg_base(dst, size)
  {}

  friend class instr_reg_base;
};

template <bool is_scalar, bool has_init, bool has_enable>
class instr_pipe : public instr_reg_base {
public:

  void destroy() override {
    this->~instr_pipe();
    ::operator delete [](this);
  }

  void eval() override {
    if (!static_cast<bool>(cd_[0]))
      return;

    if constexpr (is_scalar) {
      if constexpr (has_init) {
        if (static_cast<bool>(reset_[0])) {
          bv_copy_scalar(dst_, initdata_);
          for (uint32_t i = 0; i < pipe_size_; i += size_) {
            bv_copy_scalar(pipe_, i, initdata_, 0, size_);
          }
          return;
        }
      }

      if constexpr (has_enable) {
        if (!static_cast<bool>(enable_[0]))
          return;
      }

      bv_slice_scalar(dst_, size_, pipe_, 0);
      bv_shr_scalar<false>(pipe_, pipe_size_, pipe_, pipe_size_, size_);
      pipe_[0] |= next_[0] << (pipe_size_ - size_);
    } else {
      if constexpr (has_init) {
        if (static_cast<bool>(reset_[0])) {
          bv_copy(dst_, initdata_, size_);
          for (uint32_t i = 0; i < pipe_size_; i += size_) {
            bv_copy(pipe_, i, initdata_, 0, size_);
          }
          return;
        }
      }

      if constexpr (has_enable) {
        if (!static_cast<bool>(enable_[0]))
          return;
      }

      bv_slice(dst_, size_, pipe_, idx_);
      bv_copy(pipe_, idx_, next_, 0, size_);
      idx_ = std::min(idx_ - size_, pipe_size_ - size_);
    }
  }

protected:

  instr_pipe(block_type* dst, uint32_t size, block_type* pipe, uint32_t pipe_size)
    : instr_reg_base(dst, size)
    , pipe_(pipe)
    , pipe_size_(pipe_size)
    , idx_(0)
  {}

  block_type* pipe_;
  uint32_t pipe_size_;
  uint32_t idx_;

  friend class instr_reg_base;
};

instr_reg_base* instr_reg_base::create(regimpl* node, data_map_t& map) {
  uint32_t dst_size  = node->size();
  uint32_t nblocks   = ceildiv(dst_size, bitwidth_v<block_type>);
  uint32_t dst_bytes = sizeof(block_type) * nblocks;

  bool is_scalar = (dst_size <= bitwidth_v<block_type>);
  uint8_t *buf, *buf_cur;

  uint32_t pipe_size = dst_size * (node->length() - 1);
  if (pipe_size) {
    is_scalar &= (pipe_size <= bitwidth_v<block_type>);

    uint32_t pipe_bytes = sizeof(block_type) * ceildiv(pipe_size, bitwidth_v<block_type>);
    buf = new uint8_t[__aligned_sizeof(instr_pipe<false, false, false>) + dst_bytes + pipe_bytes]();
    buf_cur = buf + __aligned_sizeof(instr_pipe<false, false, false>);
  } else {
    buf = new uint8_t[__aligned_sizeof(instr_reg<false, false, false>) + dst_bytes]();
    buf_cur = buf + __aligned_sizeof(instr_reg<false, false, false>);
  }

  auto dst = (block_type*)buf_cur;
  map[node->id()] = dst;
  bv_init(dst, dst_size);

  buf_cur += dst_bytes;
  auto pipe = (block_type*)buf_cur;
  bv_init(pipe, pipe_size);

  if (!node->is_pipe()) {
    if (is_scalar) {
      if (node->has_init_data()) {
        if (node->has_enable()) {
          return new (buf) instr_reg<true, true, true>(dst, dst_size);
        } else {
          return new (buf) instr_reg<true, true, false>(dst, dst_size);
        }
      } else {
        if (node->has_enable()) {
          return new (buf) instr_reg<true, false, true>(dst, dst_size);
        } else {
          return new (buf) instr_reg<true, false, false>(dst, dst_size);
        }
      }
    } else {
      if (node->has_init_data()) {
        if (node->has_enable()) {
          return new (buf) instr_reg<false, true, true>(dst, dst_size);
        } else {
          return new (buf) instr_reg<false, true, false>(dst, dst_size);
        }
      } else {
        if (node->has_enable()) {
          return new (buf) instr_reg<false, false, true>(dst, dst_size);
        } else {
          return new (buf) instr_reg<false, false, false>(dst, dst_size);
        }
      }
    }
  } else {
    if (is_scalar) {
      if (node->has_init_data()) {
        if (node->has_enable()) {
          return new (buf) instr_pipe<true, true, true>(dst, dst_size, pipe, pipe_size);
        } else {
          return new (buf) instr_pipe<true, true, false>(dst, dst_size, pipe, pipe_size);
        }
      } else {
        if (node->has_enable()) {
          return new (buf) instr_pipe<true, false, true>(dst, dst_size, pipe, pipe_size);
        } else {
          return new (buf) instr_pipe<true, false, false>(dst, dst_size, pipe, pipe_size);
        }
      }
    } else {
      if (node->has_init_data()) {
        if (node->has_enable()) {
          return new (buf) instr_pipe<false, true, true>(dst, dst_size, pipe, pipe_size);
        } else {
          return new (buf) instr_pipe<false, true, false>(dst, dst_size, pipe, pipe_size);
        }
      } else {
        if (node->has_enable()) {
          return new (buf) instr_pipe<false, false, true>(dst, dst_size, pipe, pipe_size);
        } else {
          return new (buf) instr_pipe<false, false, false>(dst, dst_size, pipe, pipe_size);
        }
      }
    }
  }
}

///////////////////////////////////////////////////////////////////////////////

class instr_mport_base : public instr_base {
public:

  ~instr_mport_base() {
    if (own_store_) {
      delete [] store_;
    }
  }

protected:

  instr_mport_base(uint32_t data_size)
    : own_store_(false)
    , store_(nullptr)
    , addr_(nullptr)
    , addr_size_(0)
    , data_size_(data_size)
  {}

  void init(memportimpl* node, data_map_t& map) {
    auto mem = node->mem();
    auto it = map.find(mem->id());
    if (it != map.end()) {
      store_ = const_cast<block_type*>(it->second);
    } else {
      uint32_t nblocks = ceildiv(mem->size(), bitwidth_v<block_type>);
      store_ = new block_type[nblocks];
      if (mem->has_init_data()) {
        bv_copy(store_, mem->init_data().words(), mem->size());
      } else {
        bv_init(store_, mem->size());
      }
      map[mem->id()] = store_;
      own_store_ = true;
    }    
    addr_ = map.at(node->addr().id());
    addr_size_ = node->addr().size();
  }

  bool own_store_;
  block_type* store_;  
  const block_type* addr_;
  uint32_t addr_size_;
  uint32_t data_size_;
};

///////////////////////////////////////////////////////////////////////////////

class instr_marport_base : public instr_mport_base {
public:

  static instr_marport_base* create(marportimpl* node, data_map_t& map) ;

protected:

  instr_marport_base(block_type* dst, uint32_t dst_size)
    : instr_mport_base(dst_size)
    , dst_(dst)
  {}

  block_type* dst_;
};

template <bool is_scalar>
class instr_marport : public instr_marport_base {
public:

  void destroy() override {
    this->~instr_marport();
    ::operator delete [](this);
  }

  void eval() override {
    auto addr = bv_cast<uint32_t>(addr_, addr_size_);
    auto src_offset = addr * data_size_;
    auto src_idx = src_offset / bitwidth_v<block_type>;
    auto src_lsb = src_offset % bitwidth_v<block_type>;
    if constexpr (is_scalar) {
      bv_slice_vector_small(dst_, data_size_, store_ + src_idx, src_lsb);
    } else {
      bv_slice_vector(dst_, data_size_, store_ + src_idx, src_lsb);
    }
  }

private:

  instr_marport(block_type* dst, uint32_t dst_size)
    : instr_marport_base(dst, dst_size)
  {}

  friend class instr_marport_base;
};

instr_marport_base* instr_marport_base::create(marportimpl* node, data_map_t& map) {
  uint32_t dst_size  = node->size();
  uint32_t nblocks   = ceildiv(dst_size, bitwidth_v<block_type>);
  uint32_t dst_bytes = sizeof(block_type) * nblocks;

  auto buf = new uint8_t[__aligned_sizeof(instr_marport_base) + dst_bytes]();
  auto buf_cur = buf + __aligned_sizeof(instr_marport_base);
  auto dst = (block_type*)buf_cur;
  map[node->id()] = dst;
  bv_init(dst, dst_size);

  instr_marport_base* instr;
  bool is_scalar = (dst_size <= bitwidth_v<block_type>);
  if (is_scalar) {
    instr = new (buf) instr_marport<true>(dst, dst_size);
  } else {
    instr = new (buf) instr_marport<false>(dst, dst_size);
  }
  instr->init(node, map);
  return instr;
}

///////////////////////////////////////////////////////////////////////////////

class instr_msrport_base : public instr_mport_base {
public:

  static instr_msrport_base* create(msrportimpl* node, data_map_t& map) ;

  void init(msrportimpl* node, data_map_t& map) {
    instr_mport_base::init(node, map);
    cd_ = map.at(node->cd().id());
    if (node->has_enable()) {
      enable_ = map.at(node->enable().id());
    }
  }

protected:

  instr_msrport_base(block_type* dst, uint32_t dst_size)
    : instr_mport_base(dst_size)
    , dst_(dst)
    , cd_(nullptr)
    , enable_(nullptr)
  {}

  block_type* dst_;
  const block_type* cd_;
  const block_type* enable_;
};

template <bool is_scalar>
class instr_msrport : public instr_msrport_base {
public:

  void destroy() override {
    this->~instr_msrport();
    ::operator delete [](this);
  }

  void eval() override {
    if (!static_cast<bool>(cd_[0])
     || (enable_ && !static_cast<bool>(enable_[0])))
      return;
    auto addr = bv_cast<uint32_t>(addr_, addr_size_);
    auto src_offset = addr * data_size_;
    auto src_idx = src_offset / bitwidth_v<block_type>;
    auto src_lsb = src_offset % bitwidth_v<block_type>;
    if constexpr (is_scalar) {
      bv_slice_vector_small(dst_, data_size_, store_ + src_idx, src_lsb);
    } else {
      bv_slice_vector(dst_, data_size_, store_ + src_idx, src_lsb);
    }
  }

private:

  instr_msrport(block_type* dst, uint32_t dst_size)
    : instr_msrport_base(dst, dst_size)
  {}

  friend class instr_msrport_base;
};

instr_msrport_base* instr_msrport_base::create(msrportimpl* node, data_map_t& map) {
  uint32_t dst_size  = node->size();
  uint32_t nblocks   = ceildiv(dst_size, bitwidth_v<block_type>);
  uint32_t dst_bytes = sizeof(block_type) * nblocks;

  auto buf = new uint8_t[__aligned_sizeof(instr_msrport_base) + dst_bytes]();
  auto buf_cur = buf + __aligned_sizeof(instr_msrport_base);
  auto dst = (block_type*)buf_cur;
  map[node->id()] = dst;
  bv_init(dst, dst_size);

  bool is_scalar = (dst_size <= bitwidth_v<block_type>);
  if (is_scalar) {
    return new (buf) instr_msrport<true>(dst, dst_size);
  } else {
    return new (buf) instr_msrport<false>(dst, dst_size);
  }
}

///////////////////////////////////////////////////////////////////////////////

class instr_mwport_base : public instr_mport_base {
public:

  static instr_mwport_base* create(mwportimpl* node, data_map_t& map) ;

protected:

  instr_mwport_base(uint32_t data_size)
    : instr_mport_base(data_size)
    , cd_(nullptr)
    , enable_(nullptr)
    , wdata_(nullptr)
  {}

  void init(mwportimpl* node, data_map_t& map) {
    instr_mport_base::init(node, map);
    cd_ = map.at(node->cd().id());
    if (node->has_enable()) {
      enable_ = map.at(node->enable().id());
      enable_size_ = node->enable().size();
    }
    wdata_ = map.at(node->wdata().id());
  }

  const block_type* cd_;
  const block_type* enable_;
  const block_type* wdata_;
  uint32_t enable_size_;
};

template <bool is_scalar>
class instr_mwport : public instr_mwport_base {
public:

  void destroy() override {
    this->~instr_mwport();
    ::operator delete [](this);
  }

  void eval() override {
    if (!static_cast<bool>(cd_[0])
     || (enable_ && bv_is_zero(enable_, enable_size_)))
      return;
    auto addr = bv_cast<uint32_t>(addr_, addr_size_);
    auto dst_offset = addr * data_size_;
    auto dst_idx = dst_offset / bitwidth_v<block_type>;
    auto dst_lsb = dst_offset % bitwidth_v<block_type>;

    block_type* wdata = const_cast<block_type*>(wdata_);
    sdata_type tmp1;
    if (enable_size_ > 1) {
      sdata_type tmp2, tmp3;
      tmp1.resize(data_size_);
      tmp2.resize(data_size_);
      wdata = tmp1.words();
      auto rdata = tmp2.words();

      auto enable = const_cast<block_type*>(enable_);
      if (enable_size_ < data_size_) {
        tmp3.resize(data_size_);
        enable = tmp3.words();
        tmp3.reset();
        auto w = data_size_ / enable_size_;
        for (uint32_t i = 0; i < enable_size_; ++i) {
          if (bv_get(enable_, i)) {
            for (uint32_t j = 0; j < w; ++j) {
              bv_set(enable, j + i * w, true);
            }
          }
        }
      }

      if constexpr (is_scalar) {
        bv_slice_vector_small(rdata, data_size_, store_ + dst_idx, dst_lsb);
      } else {
        bv_slice_vector(rdata, data_size_, store_ + dst_idx, dst_lsb);
      }

      bv_blend<false, block_type, ClearBitAccessor<block_type>>(
            wdata, data_size_, enable, data_size_, rdata, data_size_, wdata, data_size_);
    }

    if constexpr (is_scalar) {
      bv_copy_vector_small(store_ + dst_idx, dst_lsb, wdata, 0, data_size_);
    } else {
      bv_copy_vector(store_ + dst_idx, dst_lsb, wdata, 0, data_size_);
    }
  }

private:

  instr_mwport(uint32_t data_size) : instr_mwport_base(data_size) {}

  friend class instr_mwport_base;
};

instr_mwport_base* instr_mwport_base::create(mwportimpl* node, data_map_t& map) {
  auto buf = new uint8_t[__aligned_sizeof(instr_mwport_base)]();
  auto data_size = node->mem()->data_width();
  auto is_scalar = (data_size <= bitwidth_v<block_type>);
  instr_mwport_base* instr;
  if (is_scalar) {
    instr = new (buf) instr_mwport<true>(data_size);
  } else {
    instr = new (buf) instr_mwport<false>(data_size);
  }
  instr->init(node, map);
  return instr;
}

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
    dst_ = ++tick_;
  }

private:

  ch_tick tick_;
  sdata_type dst_;

  instr_time(timeimpl* node, data_map_t& map)
    : tick_(0)
    , dst_(node->size(), 0) {
    map[node->id()] = dst_.words();
  }
};

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
    if ((pred_ && !static_cast<bool>(pred_[0]))
      || static_cast<bool>(cond_[0]))
      return;
    auto tick = bv_cast<uint64_t>(time_, 64);
    fprintf(stderr, "assertion failure at tick %ld, %s (%s:%d)\n",
            tick, msg_.c_str(), sloc_.file().c_str(), sloc_.line());
    std::abort();
  }

private:

  instr_assert(assertimpl* node, data_map_t& map)
    : cond_(map.at(node->cond().id()))
    , time_(map.at(node->time().id()))
    , pred_(node->has_pred() ? map.at(node->pred().id()) : nullptr)
    , msg_(node->msg())
    , sloc_(node->sloc())
  {}

  const block_type* cond_;
  const block_type* time_;
  const block_type* pred_;
  std::string msg_;
  source_location sloc_;
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
      fmtparser parser;
      for (const char *str = format_.c_str(); *str != '\0'; ++str) {
        if (*str == '{') {
          fmtinfo_t fmt;
          str = parser.parse(&fmt, str);
          auto& src = srcs_.at(fmt.index);
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
    udf_->impl()->eval(dst_, srcs_.data());
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
  sdata_type dst_;
  std::vector<sdata_type> srcs_;
};

///////////////////////////////////////////////////////////////////////////////

class instr_udfs : public instr_base {
public:

  static instr_udfs* create(udfsimpl* node, data_map_t& map) {
    return new instr_udfs(node, map);
  }

  void init(udfsimpl* node, data_map_t& map) {
    cd_ = map.at(node->cd().id());
    for (uint32_t i = 0, n = udf_->inputs_size().size(); i < n; ++i) {
      auto& src = node->src(i);
      srcs_[i].emplace(const_cast<block_type*>(map.at(src.id())), src.size());
    }
  }

  void destroy() override {
    delete this;
  }

  void eval() override {
    if (!static_cast<bool>(cd_[0]))
      return;
    udf_->impl()->eval(dst_, srcs_.data());
  }

private:

  instr_udfs(udfsimpl* node, data_map_t& map)
    : cd_(nullptr)
    , udf_(node->udf())
    , dst_(node->size()) {
    srcs_.resize(node->srcs().size());
    map[node->id()] = dst_.words();
  }

  ~instr_udfs() {
    for (auto& src : srcs_) {
      src.emplace(nullptr);
    }
  }

  const block_type* cd_;
  udf_iface* udf_;
  sdata_type dst_;
  std::vector<sdata_type> srcs_;
};

///////////////////////////////////////////////////////////////////////////////

struct sim_ctx_t {
  sim_ctx_t() {}

  ~sim_ctx_t() {
    for (auto instr : instrs) {
      instr->destroy();
    }
    for (auto constant : constants) {
      free(constant.first);
    }
  }

  std::vector<std::pair<block_type*, uint32_t>> constants;
  std::vector<instr_base*> instrs;
};

///////////////////////////////////////////////////////////////////////////////

class compiler {
public:
  compiler(sim_ctx_t* ctx) : sim_ctx_(ctx) {}

  ~compiler() {}

  void build(const std::vector<lnodeimpl*>& eval_list) {
    data_map_t data_map;
    instr_map_t instr_map;
    node_map_t node_map;

    instr_map.reserve(eval_list.size());
    sim_ctx_->instrs.reserve(eval_list.size());

    auto ctx = eval_list.back()->ctx();

    // setup constants
    this->setup_constants(ctx, data_map);

    auto sys_time = ctx->sys_time();
    if (sys_time) {
      instr_map[sys_time->id()] = instr_time::create(reinterpret_cast<timeimpl*>(sys_time), data_map);
    }

    // lower synchronous nodes
    for (auto node : ctx->snodes()) {
      switch (node->type()) {
      case type_reg:
        instr_map[node->id()] = instr_reg_base::create(reinterpret_cast<regimpl*>(node), data_map);
        break;
      case type_msrport:
        instr_map[node->id()] = instr_msrport_base::create(reinterpret_cast<msrportimpl*>(node), data_map);
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
      case type_proxy:
        instr = instr_proxy_base::create(reinterpret_cast<proxyimpl*>(node), data_map);
        break;
      case type_input: {
        auto input = reinterpret_cast<inputimpl*>(node);
        data_map[node->id()] = input->value()->words();
      } break;
      case type_output: {
        auto output = reinterpret_cast<outputimpl*>(node);
        data_map[node->id()] = data_map.at(output->src(0).id());
        instr = instr_output_base::create(output, data_map);
      } break;
      case type_op:
        instr = instr_op_base::create(reinterpret_cast<opimpl*>(node), data_map);
        break;
      case type_sel:
        instr = instr_select_base::create(reinterpret_cast<selectimpl*>(node), data_map);
        break;
      case type_cd:
        instr = instr_cd::create(reinterpret_cast<cdimpl*>(node), data_map);
        break;
      case type_reg:
        instr = instr_map.at(node->id());
        reinterpret_cast<instr_reg_base*>(instr)->init(reinterpret_cast<regimpl*>(node), data_map);
        break;
      case type_marport:
        instr = instr_marport_base::create(reinterpret_cast<marportimpl*>(node), data_map);
        break;
      case type_msrport:
        instr = instr_map.at(node->id());
        reinterpret_cast<instr_msrport_base*>(instr)->init(reinterpret_cast<msrportimpl*>(node), data_map);
        break;        
      case type_mwport:
        instr = instr_mwport_base::create(reinterpret_cast<mwportimpl*>(node), data_map);
        break;
      case type_tap:
        instr = instr_output_base::create(reinterpret_cast<tapimpl*>(node), data_map);
        break;
      case type_time:
        instr = instr_map.at(node->id());
        break;
      case type_assert:
        instr = instr_assert::create(reinterpret_cast<assertimpl*>(node), data_map);
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
      case type_lit:
      case type_mem:
        break;
      default:
        std::abort();
        break;
      }

      if (instr) {
        instr_map[node->id()] = instr;
        node_map[sim_ctx_->instrs.size()] = node->id();
        sim_ctx_->instrs.emplace_back(instr);
      }
    }
  }

private:

  void setup_constants(context* ctx, data_map_t& data_map) {
    for (auto node : ctx->literals())  {
      auto lit = reinterpret_cast<litimpl*>(node);
      auto num_words = ceildiv(lit->size(), bitwidth_v<block_type>);
      for (auto& constant : sim_ctx_->constants) {
        if (constant.second >= num_words) {
          uint32_t width = num_words * bitwidth_v<block_type>;
          if (bv_eq<false, block_type, ClearBitAccessor<block_type>>(
                constant.first, width, lit->value().words(), width)) {
            data_map[lit->id()] = constant.first;
            break;
          }
        } else {
          uint32_t width = constant.second * bitwidth_v<block_type>;
          if (bv_eq<false, block_type, ClearBitAccessor<block_type>>(
                constant.first, width, lit->value().words(), width)) {
            auto buf = reinterpret_cast<block_type*>(
                  realloc(constant.first, num_words * sizeof(block_type)));
            std::copy_n(lit->value().words(), num_words, buf);
            for (auto& data : data_map) {
              if (data.second == constant.first)
                data.second = buf;
            }
            data_map[lit->id()] = buf;
            constant.first = buf;
            constant.second = num_words;
            break;
          }
        }
      }
      if (0 == data_map.count(lit->id())) {
        auto buf = reinterpret_cast<block_type*>(malloc(num_words * sizeof(block_type)));
        std::copy_n(lit->value().words(), num_words, buf);
        sim_ctx_->constants.emplace_back(buf, num_words);
        data_map[lit->id()] = buf;
      }
    }
  }

  sim_ctx_t* sim_ctx_;
};

///////////////////////////////////////////////////////////////////////////////

driver::driver() {
  sim_ctx_ = new sim_ctx_t();
}

driver::~driver() {
  delete sim_ctx_;
}

void driver::initialize(const std::vector<lnodeimpl*>& eval_list) {
  compiler compiler(sim_ctx_);
  compiler.build(eval_list);
}

void driver::eval() {
  for (auto instr : sim_ctx_->instrs) {
    instr->eval();
  }
}

}
