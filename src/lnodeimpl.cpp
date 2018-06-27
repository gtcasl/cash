#include "lnodeimpl.h"
#include "proxyimpl.h"
#include "context.h"

using namespace ch::internal;

const char* ch::internal::to_string(lnodetype type) {
  static const char* sc_names[] = {
    CH_LNODE_ENUM(CH_LNODE_NAME)
  };
  return sc_names[CH_LNODE_INDEX(type)];
}

lnodeimpl::lnodeimpl(context* ctx,
                     lnodetype type,
                     uint32_t size,                     
                     const source_location& sloc,
                     const std::string& name,
                     uint32_t var_id)
  : ctx_(ctx)
  , id_(ctx->node_id())
  , type_(type)
  , value_(size)
  , sloc_(sloc)
  , name_(to_string(type))
  , var_id_(var_id) {
  if (!name.empty()) {
    name_ = name;
  }
}

lnodeimpl::~lnodeimpl() {}

uint32_t lnodeimpl::add_src(const lnode& src) {
  uint32_t index = srcs_.size();
  srcs_.push_back(src);
  return index;
}

bool lnodeimpl::equals(const lnodeimpl& rhs) const {
  if (this->type() == rhs.type()
   && this->size() == rhs.size()
   && this->srcs().size() == rhs.srcs().size()) {
    for (unsigned i = 0, n = this->srcs().size(); i < n; ++i) {
      if (this->src(i).id() != rhs.src(i).id())
        return false;
    }
    return true;
  }
  return false;
}

lnodeimpl* lnodeimpl::slice(uint32_t offset,
                            uint32_t length,
                            const source_location& sloc) {
  assert(length <= value_.size());
  if (value_.size() == length)
    return this;
  return ctx_->create_node<proxyimpl>(this, offset, length, sloc);
}

void lnodeimpl::print(std::ostream& out, uint32_t level) const {
  out << "#" << id_ << " <- " << this->type() << value_.size();
  uint32_t n = srcs_.size();
  if (n > 0) {
    out << "(";
    for (uint32_t i = 0; i < n; ++i) {
      if (i > 0)
        out << ", ";
      out << "#" << srcs_[i].id();
    }
    out << ")";
  }
  if (level == 2) {
    out << " = " << value_;
  }
}

///////////////////////////////////////////////////////////////////////////////

undefimpl::undefimpl(context* ctx, uint32_t size, const source_location& sloc)
  : lnodeimpl(ctx, type_undef, size, sloc)
{}
