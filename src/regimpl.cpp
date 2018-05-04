#include "reg.h"
#include "regimpl.h"
#include "proxyimpl.h"
#include "select.h"
#include "context.h"

using namespace ch::internal;

reg_buffer::reg_buffer(unsigned size,
                                 const source_location& sloc,
                                 const std::string& name)
  : logic_buffer(
      ctx_curr()->create_node<regimpl>(
        ctx_curr()->create_node<proxyimpl>(size)),
      sloc, name) {
  this->write(0, value_, 0, size);
}

reg_buffer::reg_buffer(const lnode& data,
                                 const source_location& sloc,
                                 const std::string& name)
  : logic_buffer(
      ctx_curr()->create_node<regimpl>(
        ctx_curr()->create_node<proxyimpl>(data.size()),
        data),
      sloc, name) {
  this->write(0, value_, 0, data.size());
}

void reg_buffer::write(uint32_t dst_offset,
                            const lnode& data,
                            uint32_t src_offset,
                            uint32_t length) {
  auto proxy = reinterpret_cast<proxyimpl*>(value_.impl());
  auto reg = dynamic_cast<regimpl*>(proxy->src(0).impl());
  reg->next().write(dst_offset, data, src_offset, length);
}

///////////////////////////////////////////////////////////////////////////////

regimpl::regimpl(context* ctx, const lnode& next, const lnode& init)
  : lnodeimpl(ctx, type_reg, next.size()) {
  auto cd = ctx->current_cd();
  cd->add_reg(this);
  srcs_.emplace_back(cd);  
  srcs_.emplace_back(next);
  srcs_.emplace_back(init);
}

regimpl::regimpl(context* ctx, const lnode& next)
  : lnodeimpl(ctx, type_reg, next.size()) {
  auto cd = ctx->current_cd();
  cd->add_reg(this);
  srcs_.emplace_back(cd);
  srcs_.emplace_back(next);
}

regimpl::~regimpl() {
  this->detach();
}

void regimpl::detach() {
  if (!srcs_[0].empty()) {
    reinterpret_cast<cdimpl*>(srcs_[0].impl())->remove_reg(this);
    srcs_[0].clear();
  }
}

std::size_t regimpl::hash() const {
  hash_t ret;
  ret.fields.type = this->type();
  ret.fields.size = this->size();
  auto n = this->srcs().size();
  if (n > 0) {
    ret.fields.arg0 = this->src(0).id();
    if (n > 1) {
      ret.fields.arg1 = this->src(1).id();
    }
  }
  return ret.value;
}

void regimpl::tick(ch_tick t) {
  CH_UNUSED(t);
  value_ = q_next_;
}

void regimpl::tick_next(ch_tick t) {
  if (this->has_init()) {
    auto& reset = reinterpret_cast<cdimpl*>(srcs_[0].impl())->reset();
    q_next_ = reset.eval(t)[0] ? srcs_[2].eval(t) : srcs_[1].eval(t);
  } else {
    q_next_ = srcs_[1].eval(t);
  }
}

const bitvector& regimpl::eval(ch_tick t) {
  CH_UNUSED(t);
  return value_; 
}

///////////////////////////////////////////////////////////////////////////////

void ch::internal::ch_pushcd(const ch_logic<1>& clock,
                             const ch_logic<1>& reset,
                             bool posedge) {
  auto ctx = ctx_curr();
  auto _cd = ctx->create_cdomain(get_lnode(clock), get_lnode(reset), posedge);
  ctx->push_cd(_cd);
}

void ch::internal::ch_popcd() {
  ctx_curr()->pop_cd();
}

ch_logic<1> ch::internal::ch_clock() {
  auto cd = ctx_curr()->current_cd();
  return make_type<ch_logic<1>>(cd->clock());
}

ch_logic<1> ch::internal::ch_reset() {
  auto cd = ctx_curr()->current_cd();
  return make_type<ch_logic<1>>(cd->reset());
}
