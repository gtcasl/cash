#include "ioimpl.h"
#include "ioport.h"
#include "context.h"

using namespace ch::internal;

inputimpl::inputimpl(context* ctx,
                     uint32_t size,
                     const std::string& name,
                     const source_location& sloc)
  : ioimpl(ctx, type_input, size, sloc, name)
  , words_(nullptr)
{}

inputimpl::~inputimpl() {
  if (words_) {
    data_.words(words_);
  }
}

void inputimpl::bind(const lnode& input) {
  input_ = input;
}

void inputimpl::initialize() {
  if (!input_.empty()) {
    if (words_) {
      data_.words(words_);
    }
    words_ = data_.words(input_.data().words());
  }
}

void inputimpl::eval() {}

void inputimpl::print(std::ostream& out, uint32_t level) const {
  out << "#" << id_ << " <- " << this->type() << data_.size();
  out << "(" << name_;
  if (!input_.empty()) {
    out << ", $" << input_.id();
  }
  out << ")";
  if (level == 2) {
    out << " = " << data_;
  }
}

///////////////////////////////////////////////////////////////////////////////

outputimpl::outputimpl(context* ctx,
                       const lnode& src,
                       const std::string& name,
                       const source_location& sloc)
  : ioimpl(ctx, type_output, src.size(), sloc, name)
  , words_(nullptr) {
  srcs_.emplace_back(src);
}

outputimpl::~outputimpl() {
  if (words_) {
    data_.words(words_);
  }
}

void outputimpl::initialize() {
  if (words_) {
    data_.words(words_);
  }
  words_ = data_.words(srcs_[0].data().words());
}

void outputimpl::eval() {}

void outputimpl::print(std::ostream& out, uint32_t level) const {
  out << "#" << id_ << " <- " << this->type() << data_.size();
  out << "(" << name_ << ", #" << srcs_[0].id() << ")";
  if (level == 2) {
    out << " = " << data_;
  }
}

///////////////////////////////////////////////////////////////////////////////

tapimpl::tapimpl(context* ctx,
                 const lnode& src,
                 const std::string& name,
                 const source_location& sloc)
  : ioimpl(ctx, type_tap, src.size(), sloc, name)
  , words_(nullptr) {
  srcs_.emplace_back(src);
}

tapimpl::~tapimpl() {
  if (words_) {
    data_.words(words_);
  }
}

void tapimpl::initialize() {
  if (words_) {
    data_.words(words_);
  }
  words_ = data_.words(srcs_[0].data().words());
}

void tapimpl::eval() {}

void tapimpl::print(std::ostream& out, uint32_t level) const {
  out << "#" << id_ << " <- " << this->type() << data_.size();
  out << "(" << name_ << ", #" << srcs_[0].id() << ")";
  if (level == 2) {
    out << " = " << data_;
  }
}

///////////////////////////////////////////////////////////////////////////////

lnodeimpl* ch::internal::createInputNode(const std::string& name,
                                         uint32_t size,
                                         const source_location& sloc) {
  return ctx_curr()->create_node<inputimpl>(size, name, sloc);
}

lnodeimpl* ch::internal::createOutputNode(const std::string& name,
                                          const lnode& src,
                                          const source_location& sloc) {
  return ctx_curr()->create_node<outputimpl>(src, name, sloc);
}
