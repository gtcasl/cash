#include "aluimpl.h"
#include "proxyimpl.h"
#include "logic.h"
#include "context.h"

using namespace ch::internal;

aluimpl::aluimpl(context* ctx, ch_op op, uint32_t size, bool is_signed,
                 const lnode& in, const source_location& sloc)
  : lnodeimpl(ctx, type_alu, size, sloc)
  , op_(op)
  , is_signed_(is_signed)
  , need_resizing_(false) {
  name_ = to_string(op);
  srcs_.push_back(in);
}

aluimpl::aluimpl(context* ctx, ch_op op, uint32_t size, bool is_signed,
                 const lnode& lhs, const lnode& rhs, const source_location& sloc)
  : lnodeimpl(ctx, type_alu, size, sloc)
  , op_(op)
  , is_signed_(is_signed)
  , need_resizing_(false) {
  name_ = to_string(op);
  srcs_.push_back(lhs);
  srcs_.push_back(rhs);
}

bool aluimpl::equals(const lnodeimpl& other) const {
  if (lnodeimpl::equals(other)) {
    auto _other = reinterpret_cast<const aluimpl&>(other);
    return (this->op() == _other.op());
  }
  return false;
}

std::size_t aluimpl::hash() const {
  hash_t ret;
  ret.fields.type = this->type();
  ret.fields.size = this->size();  
  auto n = this->srcs().size();  
  ret.fields.arg0 = (int)this->op();
  if (n > 0) {
    ret.fields.srcs = n;
    ret.fields.arg1 = this->src(0).id();
    if (n > 1) {
      ret.fields.arg2 = this->src(1).id();
    }
  }
  return ret.value;
}

void aluimpl::initialize() {
  // access source node data
  src0_ = nullptr;
  src1_ = nullptr;
  if (srcs_.size() > 0) {
    src0_ = &srcs_[0].data();
    if (srcs_.size() > 1) {
      src1_ = &srcs_[1].data();
    }
  }

  // allocate shadow buffers if needed
  auto op_class = CH_OP_CLASS(op_);
  if (op_flags::equality == op_class
   || op_flags::relational == op_class) {
    if (src0_->size() != src1_->size()) {
     if (src0_->size() < src1_->size()) {
       t_src0_.resize(src1_->size());
       src0_ = &t_src0_;
     } else {
       t_src1_.resize(src0_->size());
       src1_ = &t_src1_;
     }
     need_resizing_ = true;
   }
  } else
  if (op_flags::bitwise == op_class
   || op_flags::arithmetic == op_class)
  {
    if (src0_->size() != this->size()) {
      t_src0_.resize(this->size());
      src0_ = &t_src0_;
      need_resizing_ = true;
    }
    if (src1_ && src1_->size() != this->size()) {
      t_src1_.resize(this->size());
      src1_ = &t_src1_;
      need_resizing_ = true;
    }
  }
}

void aluimpl::update_shadow_buffers() {
  if (src0_ == &t_src0_) {
    if (t_src0_.size() > srcs_[0].size()) {
      if (is_signed_) {
        bv_sext(t_src0_, srcs_[0].data());
      } else {
        bv_zext(t_src0_, srcs_[0].data());
      }
    } else {
      t_src0_.copy(0, srcs_[0].data(), 0, t_src0_.size());
    }
  }
  if (src1_ == &t_src1_) {
    if (t_src1_.size() > srcs_[1].size()) {
      if (is_signed_) {
        bv_sext(t_src1_, srcs_[1].data());
      } else {
        bv_zext(t_src1_, srcs_[1].data());
      }
    } else {
      t_src1_.copy(0, srcs_[1].data(), 0, t_src1_.size());
    }
  }
}

void aluimpl::eval() {
  if (need_resizing_) {
    this->update_shadow_buffers();
  }

  switch (op_) {
  case ch_op::eq:
    data_.word(0) = (*src0_ == *src1_);
    break;
  case ch_op::ne:
    data_.word(0) = (*src0_ != *src1_);
    break;
  case ch_op::lt:
    data_.word(0) = is_signed_ ? bv_lts(*src0_, *src1_) : bv_ltu(*src0_, *src1_);
    break;
  case ch_op::gt:
    data_.word(0) = is_signed_ ? bv_lts(*src1_, *src0_) : bv_ltu(*src1_, *src0_);
    break;
  case ch_op::le:
    data_.word(0) = !(is_signed_ ? bv_lts(*src1_, *src0_) : bv_ltu(*src1_, *src0_));
    break;
  case ch_op::ge:
    data_.word(0) = !(is_signed_ ? bv_lts(*src0_, *src1_) : bv_ltu(*src0_, *src1_));
    break;

  case ch_op::inv:
    bv_inv(data_, *src0_);
    break;
  case ch_op::andl:
    bv_and(data_, *src0_, *src1_);
    break;
  case ch_op::orl:
    bv_or(data_, *src0_, *src1_);
    break;
  case ch_op::xorl:
    bv_xor(data_, *src0_, *src1_);
    break;

  case ch_op::andr:
    data_.word(0) = bv_andr(*src0_);
    break;
  case ch_op::orr:
    data_.word(0) = bv_orr(*src0_);
    break;
  case ch_op::xorr:
    data_.word(0) = bv_xorr(*src0_);
    break;

  case ch_op::shl:
    bv_sll(data_, *src0_, *src1_);
    break;
  case ch_op::shr:
    if (is_signed_ )
        bv_sra(data_, *src0_, *src1_);
    else
        bv_srl(data_, *src0_, *src1_);
    break;

  case ch_op::add:
    bv_add(data_, *src0_, *src1_);
    break;
  case ch_op::sub:
    bv_sub(data_, *src0_, *src1_);
    break;
  case ch_op::neg:
    bv_neg(data_, *src0_);
    break;
  case ch_op::mul:
    bv_mul(data_, *src0_, *src1_);
    break;
  case ch_op::div:
    if (is_signed_ )
      bv_divs(data_, *src0_, *src1_);
    else
      bv_divu(data_, *src0_, *src1_);
    break;
  case ch_op::mod:
    if (is_signed_ )
      bv_mods(data_, *src0_, *src1_);
    else
      bv_modu(data_, *src0_, *src1_);
    break;

  case ch_op::pad:
    if (is_signed_ )
        bv_sext(data_, *src0_);
    else
        bv_zext(data_, *src0_);
    break;

  default:
    CH_ABORT("invalid opcode");
  }
}

void aluimpl::print(std::ostream& out, uint32_t level) const {
  out << "#" << id_ << " <- " << to_string(this->type()) << data_.size();
  uint32_t n = srcs_.size();
  out << "(" << to_string(op_) << (is_signed_ ? "_s" : "_u") << ", ";
  for (uint32_t i = 0; i < n; ++i) {
    if (i > 0)
      out << ", ";
    out << "#" << srcs_[i].id();
  }
  out << ")";
  if (level == 2) {
    out << " = " << data_;
  }
}

///////////////////////////////////////////////////////////////////////////////

lnodeimpl* ch::internal::createAluNode(
    ch_op op,
    uint32_t size,
    bool is_signed,
    const lnode& in,
    const source_location& sloc) {
  return in.impl()->ctx()->create_node<aluimpl>(op, size, is_signed, in, sloc);
}

lnodeimpl* ch::internal::createAluNode(
    ch_op op,
    uint32_t size,
    bool is_signed,
    const lnode& lhs,
    const lnode& rhs,
    const source_location& sloc) {
  return lhs.impl()->ctx()->create_node<aluimpl>(op, size, is_signed, lhs, rhs, sloc);
}

lnodeimpl* ch::internal::createRotateNode(
    const lnode& next,
    uint32_t dist,
    bool right,
    const source_location& sloc) {
  auto N = next.size();
  auto mod = dist % N;
  auto ret = next.impl()->ctx()->create_node<proxyimpl>(N, sloc);
  if (right) {
    ret->add_source(0, next, mod, N - mod);
    ret->add_source(N - mod, next, 0, mod);
  } else {
    ret->add_source(0, next, N - mod, mod);
    ret->add_source(mod, next, 0, N - mod);
  }
  return ret;
}
