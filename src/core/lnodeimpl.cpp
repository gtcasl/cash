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

///////////////////////////////////////////////////////////////////////////////

lnodeimpl::lnodeimpl(uint32_t id,
                     lnodetype type,
                     uint32_t size,                     
                     context* ctx,
                     const std::string& name,
                     const source_location& sloc)
  : id_(id)
  , type_(type)
  , size_(size)
  , ctx_(ctx)
  , name_(name)
  , sloc_(sloc)
  , hash_(0)
  , prev_(nullptr)
  , next_(nullptr)
  , users_(nullptr)
{}

lnodeimpl::~lnodeimpl() {
  for (lnode *curr = users_; curr;) {
    auto user = curr;
    curr = curr->next_user_;
    assert(user->impl_ == this);
    user->impl_ = nullptr;
    user->next_user_ = nullptr;
  }
  users_ = nullptr;
}

void lnodeimpl::set_src(uint32_t index, lnodeimpl* src) {
  assert(index < srcs_.size());  
  srcs_[index] = src;
  hash_ = 0;
}

uint32_t lnodeimpl::add_src(lnodeimpl* src) {
  auto index = srcs_.size();
  srcs_.push_back(src);
  hash_ = 0;
  return index;
}

void lnodeimpl::insert_src(uint32_t index, lnodeimpl* src) {
  srcs_.insert(srcs_.begin() + index, src);
  hash_ = 0;
}

lnodeimpl* lnodeimpl::remove_src(uint32_t index) {
  auto tmp = srcs_.at(index).impl();
  srcs_.erase(srcs_.begin() + index);
  hash_ = 0;
  return tmp;
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
   && this->num_srcs() == other.num_srcs()) {
    for (unsigned i = 0, n = this->num_srcs(); i < n; ++i) {
      if (this->src(i).id() != other.src(i).id())
        return false;
    }
    return true;
  }
  return false;
}

lnodeimpl* lnodeimpl::slice(uint32_t offset, uint32_t length, const source_location& sloc) const {
  assert(length <= size_);
  auto self = const_cast<lnodeimpl*>(this);
  if (size_ == length)
    return self;
  return ctx_->create_node<proxyimpl>(self, offset, length, "slice", sloc);
}

bool lnodeimpl::has_user(lnode* user) const {
  for (const lnode *curr = users_; curr; curr = curr->next_user_) {
    if (curr == user)
      return true;
  }
  return false;
}

void lnodeimpl::add_user(lnode* user) {
  user->next_user_ = users_;
  users_ = user;
}

void lnodeimpl::remove_user(lnode* user) {
  for (lnode *prev = nullptr, *curr = users_; curr;) {
    assert(curr->impl_ == this);
    if (curr == user) {
      if (prev) {
        prev->next_user_ = curr->next_user_;
      } else {
        users_ = curr->next_user_;
      }
      curr->impl_ = nullptr;
      return;
    }
    prev = curr;
    curr = curr->next_user_;
  }
  assert(false);
}

void lnodeimpl::replace_uses(lnodeimpl* node) {  
  assert(this != node);
  assert(users_);
  for (lnode *curr = users_; curr;) {
    assert(!node->has_user(curr));
    auto user = curr;
    curr = curr->next_user_;
    assert(user->impl_ == this);
    user->impl_ = node;
    user->next_user_ = nullptr;
    node->add_user(user);
  }
  users_ = nullptr;
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
  std::string desc(to_string(type_));
  if (!name_.empty()) {
    desc += "-" + name_;
  }
  return stringf("'%s (%d)' in module '%s (%d)' (%s:%d)",
                 desc.c_str(),
                 id_,
                 ctx_->name().c_str(),
                 ctx_->id(),
                 sloc_.file().c_str(),
                 sloc_.line());
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