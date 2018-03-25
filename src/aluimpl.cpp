#include "aluimpl.h"
#include "proxyimpl.h"
#include "context.h"

using namespace ch::internal;

const char* ch::internal::to_string(ch_alu_op op) {
  static const char* sc_names[] = {
    CH_ALUOP_ENUM(CH_ALUOP_NAME)
  };
  return sc_names[CH_ALUOP_INDEX(op)];
}

bool ch::internal::alu_symmetric(ch_alu_op op) {
  switch (op) {
  case alu_inv:
    return false;
  case alu_and:
  case alu_or:
  case alu_xor:
    return true;
  case alu_andr:
  case alu_orr:
  case alu_xorr:
  case alu_sll:
  case alu_srl:
  case alu_sra:
    return false;
  case alu_add:
    return true;
  case alu_sub:
  case alu_neg:
    return false;
  case alu_mult:
    return true;
  case alu_div:
  case alu_mod:
    return false;
  case alu_eq:
  case alu_ne:
    return true;
  case alu_lt:
  case alu_gt:
  case alu_le:
  case alu_ge:
  case alu_fadd:
  case alu_fsub:
  case alu_fmult:
  case alu_fdiv:
    return false;
  default:
    CH_ABORT("invalid alu operation");
  }
}

///////////////////////////////////////////////////////////////////////////////

template <ch_alu_op op>
static void unaryop(bitvector& out, const bitvector& in) {
  assert(out.get_size() == in.get_size());
  
  switch (op) {
  case alu_inv:
    Inv(out, in);
    break;
  case alu_neg:
    Negate(out, in);
    break;
  default:
    CH_ABORT("invalid alu operation");
  }
}

template <ch_alu_op op>
static void binaryop(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  assert(out.get_size() == lhs.get_size());
  assert(lhs.get_size() == rhs.get_size());
  
  switch (op) {
  case alu_and:
    And(out, lhs, rhs);
    break;
  case alu_or:
    Or(out, lhs, rhs);
    break;
  case alu_xor:
    Xor(out, lhs, rhs);
    break;
  default:
    CH_ABORT("invalid alu operation");
  }
}

template <ch_alu_op op>
static void shiftop(bitvector& out, const bitvector& in, const bitvector& bits) {
  assert(out.get_size() == in.get_size());
  CH_CHECK(bits.find_last() <= 31, "shift amount out of range");
  
  uint32_t wbits = bits.get_word(0);
  switch (op) {  
  case alu_sll:
    Sll(out, in, wbits);
    break;
  case alu_srl:
    Srl(out, in, wbits);
    break;
  case alu_sra:
    Sra(out, in, wbits);
    break;
  default:
    CH_ABORT("invalid alu operation");
  }
}

template <ch_alu_op op>
static void reduceop(bitvector& out, const bitvector& in) {
  assert(out.get_size() == 1);
  
  bool result;
  switch (op) {
  case alu_andr:
    result = AndR(in);
    break;
  case alu_orr:
    result = OrR(in);
    break;
  case alu_xorr:
    result = XorR(in);
    break;
  default:
    CH_ABORT("invalid alu operation");
  } 
  out[0] = result;
}

template <ch_alu_op op>
static void compareop(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  assert(out.get_size() == 1);
  assert(lhs.get_size() == rhs.get_size());
  
  bool result;
  switch (op) {
  case alu_eq:
    result = lhs == rhs;
    break;
  case alu_ne:
    result = !(lhs == rhs);
    break;
  case alu_lt:
    result = (lhs < rhs);
    break;
  case alu_gt:
    result = (rhs < lhs);
    break;
  case alu_le:
    result = !(rhs < lhs);
    break;
  case alu_ge:
    result = !(lhs < rhs);
    break;
  default:
    CH_ABORT("invalid alu operation");
  }
  out[0] = result;
}

static uint32_t get_output_size(ch_alu_op op, const lnode& a, const lnode& b) {
  switch (op) {
  case alu_and:
  case alu_or:
  case alu_xor:
  case alu_add:
  case alu_sub:
  case alu_mult:
  case alu_div:
  case alu_mod:
  case alu_fadd:
  case alu_fsub:
  case alu_fmult:
  case alu_fdiv:
    assert(a.get_size() == b.get_size());
    return a.get_size();

  case alu_sll:
  case alu_srl:
  case alu_sra:
    return a.get_size();

  case alu_eq:
  case alu_ne:
  case alu_lt:
  case alu_gt:
  case alu_le:
  case alu_ge:
    assert(a.get_size() == b.get_size());
    return 1;

  default:
    CH_ABORT("invalid alu operation");
  }
}

static uint32_t get_output_size(ch_alu_op op, const lnode& a) {
  switch (op) {
  case alu_inv:
  case alu_neg:
    return a.get_size();

  case alu_andr:
  case alu_orr:
  case alu_xorr:
    return 1;
  default:
    CH_ABORT("invalid alu operation");
  }
}

///////////////////////////////////////////////////////////////////////////////

aluimpl::aluimpl(context* ctx, ch_alu_op op, const lnode& in)
  : lnodeimpl(ctx, type_alu, get_output_size(op, in))
  , op_(op)
  , tick_(~0ull) {
  name_ = to_string(op);
  srcs_.push_back(in);
}

aluimpl::aluimpl(context* ctx, ch_alu_op op, const lnode& lhs, const lnode& rhs)
  : lnodeimpl(ctx, type_alu, get_output_size(op, lhs, rhs))
  , op_(op)
  , tick_(~0ull) {
  name_ = to_string(op);
  srcs_.push_back(lhs);
  srcs_.push_back(rhs);
}

void aluimpl::eval(bitvector& inout, ch_tick t) {
  switch (op_) {
  case alu_inv:
    unaryop<alu_inv>(inout, srcs_[0].eval(t));
    break;
  case alu_and:
    binaryop<alu_and>(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;
  case alu_or:
    binaryop<alu_or>(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;
  case alu_xor:
    binaryop<alu_xor>(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;

  case alu_andr:
    reduceop<alu_andr>(inout, srcs_[0].eval(t));
    break;
  case alu_orr:
    reduceop<alu_orr>(inout, srcs_[0].eval(t));
    break;
  case alu_xorr:
    reduceop<alu_xorr>(inout, srcs_[0].eval(t));
    break;

  case alu_sll:
    shiftop<alu_sll>(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;
  case alu_srl:
    shiftop<alu_srl>(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;
  case alu_sra:
    shiftop<alu_sra>(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;

  case alu_add:
    Add(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;
  case alu_sub:
    Sub(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;
  case alu_neg:
    unaryop<alu_neg>(inout, srcs_[0].eval(t));
    break;
  case alu_mult:
  case alu_div:
  case alu_mod:
    CH_TODO();
    break;

  case alu_eq:
    compareop<alu_eq>(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;
  case alu_ne:
    compareop<alu_ne>(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;
  case alu_lt:
    compareop<alu_lt>(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;
  case alu_gt:
    compareop<alu_gt>(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;
  case alu_le:
    compareop<alu_le>(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;
  case alu_ge:
    compareop<alu_ge>(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;

  case alu_fadd:
    fAdd(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;
  case alu_fsub:
    fSub(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;
  case alu_fmult:
    fMult(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;
  case alu_fdiv:
    fDiv(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;

  default:
    CH_ABORT("invalid alu operation");
  }
}

const bitvector& aluimpl::eval(ch_tick t) {  
  if (tick_ != t) {  
    tick_ = t;
    this->eval(value_, t);
  }
  return value_;
}

void aluimpl::print(std::ostream& out, uint32_t level) const {
  out << "#" << id_ << " <- " << to_string(this->get_type()) << value_.get_size();
  uint32_t n = srcs_.size();
  out << "(" << to_string(op_) << ", ";
  for (uint32_t i = 0; i < n; ++i) {
    if (i > 0)
      out << ", ";
    out << "#" << srcs_[i].get_id();
  }
  out << ")";
  if (level == 2) {
    out << " = " << value_;
  }
}

///////////////////////////////////////////////////////////////////////////////

delayed_aluimpl::delayed_aluimpl(context* ctx,
                                 ch_alu_op op,
                                 const lnode& enable,
                                 unsigned delay,
                                 const lnode& in)
  : aluimpl(ctx, op, in) {
  p_value_.resize(delay, bitvector(this->get_size()));
  p_next_.resize(delay, bitvector(this->get_size()));
  {
    auto clk = ctx->get_clk();
    cd_ = ctx->create_cdomain({clock_event(clk, true)});
    cd_->add_use(this);
    clk_idx_ = srcs_.size();
    srcs_.push_back(clk);
  }
  if (!enable.is_empty()) {
    assert(1 == enable.get_size());
    enable_idx_ = srcs_.size();
    srcs_.push_back(enable);
  }  
}

delayed_aluimpl::delayed_aluimpl(context* ctx,
                                 ch_alu_op op,
                                 const lnode& enable,
                                 unsigned delay,
                                 const lnode& lhs,
                                 const lnode& rhs)
  : aluimpl(ctx, op, lhs, rhs) {
  p_value_.resize(delay, bitvector(this->get_size()));
  p_next_.resize(delay, bitvector(this->get_size()));
  {
    auto clk = ctx->get_clk();
    cd_ = ctx->create_cdomain({clock_event(clk, true)});
    cd_->add_use(this);
    clk_idx_ = srcs_.size();
    srcs_.push_back(clk);
  }
  if (!enable.is_empty()) {
    assert(1 == enable.get_size());
    enable_idx_ = srcs_.size();
    srcs_.push_back(enable);
  }
}

delayed_aluimpl::~delayed_aluimpl() {
  cd_->remove_use(this);
}

void delayed_aluimpl::tick(ch_tick t) {
  CH_UNUSED(t);
  for (int i = p_value_.size()-1; i >= 0; --i) {
    p_value_[i] = p_next_[i];
  }
}

void delayed_aluimpl::tick_next(ch_tick t) {
  if (-1 == enable_idx_ || srcs_[enable_idx_].eval(t)[0]) {
    for (int i = p_value_.size()-1; i >= 0; --i) {
      if (0 == i) {
        this->aluimpl::eval(p_next_[0], t);
      } else {
        p_next_[i] = p_value_[i-1];
      }
    }
  } else {
    for (int i = p_value_.size()-1; i >= 0; --i) {
      p_next_[i] = p_value_[i];
    }
  }
}

const bitvector& delayed_aluimpl::eval(ch_tick t) {
  CH_UNUSED(t);
  return p_value_[p_value_.size()-1];
}

///////////////////////////////////////////////////////////////////////////////

lnodeimpl* ch::internal::createAluNode(
    ch_alu_op op,
    const lnode& in,
    unsigned delay,
    const lnode& enable) {
  auto ctx = in.get_ctx();
  aluimpl* impl;
  if (delay != 0) {
    impl = ctx->createNode<delayed_aluimpl>(op, enable, delay, in);
  } else {    
    impl = ctx->createAluNode(op, in);
  }  
  return impl;
}

lnodeimpl* ch::internal::createAluNode(
    ch_alu_op op,
    const lnode& lhs,
    const lnode& rhs,
    unsigned delay,
    const lnode& enable) {
  auto ctx = lhs.get_ctx();
  aluimpl* impl;
  if (delay != 0) {
    impl = ctx->createNode<delayed_aluimpl>(op, enable, delay, lhs, rhs);
  } else {    
    impl = ctx->createAluNode(op, lhs, rhs);
  }  
  return impl;
}

lnodeimpl* ch::internal::createRotateNode(const lnode& next, unsigned dist, bool right) {
  auto ctx = next.get_ctx();
  auto N = next.get_size();
  auto mod = dist % N;
  auto ret = ctx->createNode<proxyimpl>(N);
  if (right) {
    ret->add_source(0, next, mod, N - mod);
    ret->add_source(N - mod, next, 0, mod);
  } else {
    ret->add_source(0, next, N - mod, mod);
    ret->add_source(mod, next, 0, N - mod);
  }
  return ret;
}
