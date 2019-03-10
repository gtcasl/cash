#include "lnodeimpl.h"
#include "proxyimpl.h"
#include "regimpl.h"
#include "memimpl.h"
#include "udfimpl.h"
#include "context.h"

using namespace ch::internal;

const char* ch::internal::to_string(lnodetype type) {
  static const char* sc_names[] = {
    CH_LNODE_ENUM(CH_LNODE_NAME)
  };
  return sc_names[CH_LNODE_INDEX(type)];
}

cdimpl* ch::internal::get_snode_cd(lnodeimpl* node) {
  switch (node->type()) {
  case type_reg:
    return reinterpret_cast<cdimpl*>(
          reinterpret_cast<regimpl*>(node)->cd().impl());
  case type_msrport:
    return reinterpret_cast<cdimpl*>(
          reinterpret_cast<memportimpl*>(node)->cd().impl());
  case type_mwport:
    return reinterpret_cast<cdimpl*>(
          reinterpret_cast<memportimpl*>(node)->cd().impl());
  case type_udfs:
    return reinterpret_cast<cdimpl*>(
          reinterpret_cast<udfsimpl*>(node)->cd().impl());
  default:
    std::abort();
  }
  return nullptr;
}

lnodeimpl* ch::internal::get_snode_enable(lnodeimpl* node) {
  switch (node->type()) {
  case type_reg: {
    auto reg = reinterpret_cast<regimpl*>(node);
    return reg->has_enable() ? reg->enable().impl() : nullptr;
  }
  case type_msrport:
  case type_mwport: {
     auto mport = reinterpret_cast<memportimpl*>(node);
     return mport->has_enable() ? mport->enable().impl() : nullptr;
   }
  case type_udfs:
    return nullptr;
  default:
    std::abort();
  }
  return nullptr;
}

lnodeimpl* ch::internal::get_snode_reset(lnodeimpl* node) {
  switch (node->type()) {
  case type_reg: {
    auto reg = reinterpret_cast<regimpl*>(node);
    return reg->has_init_data() ? reg->reset().impl() : nullptr;
  }
  case type_msrport:
  case type_mwport:
  case type_udfs:
    return nullptr;
  default:
    std::abort();
  }
  return nullptr;
}

///////////////////////////////////////////////////////////////////////////////

lnodeimpl::lnodeimpl(context* ctx,
                     lnodetype type,
                     uint32_t size,                     
                     const source_location& sloc,
                     const std::string& name)
  : prev_(nullptr)
  , next_(nullptr)
  , ctx_(ctx)
  , name_(name)
  , sloc_(sloc)
  , id_(ctx->node_id())
  , type_(type)
  , hash_(0)
  , size_(size)
{}

lnodeimpl::~lnodeimpl() {}

std::vector<lnode>& lnodeimpl::srcs() {
  hash_ = 0;
  return srcs_;
}

lnode& lnodeimpl::src(uint32_t index) {
  assert(index < srcs_.size());
  hash_ = 0;
  return srcs_[index];
}

uint32_t lnodeimpl::add_src(const lnode& src) {
  auto index = srcs_.size();
  srcs_.push_back(src);
  hash_ = 0;
  return index;
}

void lnodeimpl::remove_src(uint32_t index) {
  srcs_.erase(srcs_.begin() + index);
  hash_ = 0;
}

void lnodeimpl::resize(uint32_t size) {
  size_ = size;
  hash_ = 0;
}

size_t lnodeimpl::hash() const {
  if (!hash_) {
    hash_ = type_ ^ size_;
    for (auto& src : srcs_) {
      hash_ = hash_combine(hash_, src.impl()->hash());
    }
  }
  return hash_;
}

bool lnodeimpl::equals(const lnodeimpl& other) const {
  if (this->type() == other.type()
   && this->size() == other.size()
   && this->srcs().size() == other.srcs().size()) {
    for (unsigned i = 0, n = this->srcs().size(); i < n; ++i) {
      if (this->src(i).id() != other.src(i).id())
        return false;
    }
    return true;
  }
  return false;
}

lnodeimpl* lnodeimpl::slice(uint32_t offset,
                            uint32_t length,
                            const source_location& sloc) const {
  assert(length <= size_);
  auto self = const_cast<lnodeimpl*>(this);
  if (size_ == length)
    return self;
  return ctx_->create_node<proxyimpl>(self, offset, length, sloc);
}

void lnodeimpl::write(uint32_t,
                      const lnode&,
                      uint32_t,
                      uint32_t,
                      const source_location&) {
  assert(false);
}

void lnodeimpl::print(std::ostream& out) const {
  out << "#" << id_ << " <- " << this->type() << size_;
  out << "(";
  for (uint32_t i = 0; i < srcs_.size(); ++i) {
    if (i)
      out << ", ";
    out << "#" << this->src(i).id();
  }
  out << ")";
}

std::string lnodeimpl::debug_info() const {
  return stringf("'%s#%d (%d)' in module '%s (%d)' (%s:%d:%d)",
                 name_.c_str(),
                 size_,
                 id_,
                 ctx_->name().c_str(),
                 ctx_->id(),
                 sloc_.file(),
                 sloc_.line(),
                 sloc_.index());
}

///////////////////////////////////////////////////////////////////////////////

void node_list::push_back(lnodeimpl* node) {
  if (tail_) {
    node->prev_ = tail_;
    tail_->next_ = node;
  }
  tail_ = node;
  if (head_ == nullptr) {
    head_ = node;
  }
  ++size_;
}

node_list::iterator node_list::erase(const node_list::iterator& it) {
  auto node = it.node_;
  assert(node);
  auto prev = node->prev_;
  auto next = node->next_;
  if (prev) {
    prev->next_ = next;
  } else {
    head_ = next;
  }
  if (next) {
    next->prev_ = prev;
  } else {
    tail_ = prev;
  }
  --size_;
  return iterator(next);
}
