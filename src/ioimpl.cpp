#include "ioimpl.h"
#include "context.h"

using namespace ch::internal;

ioimpl::ioimpl(context* ctx,
               lnodetype type,
               uint32_t size,
               const source_location& sloc,
               const std::string& name)
  : lnodeimpl(ctx, type, size, sloc, name)
{}

///////////////////////////////////////////////////////////////////////////////

ioportimpl::ioportimpl(context* ctx,
                       lnodetype type,
                       uint32_t size,
                       const io_value_t& value,
                       const source_location& sloc,
                       const std::string& name)
  : ioimpl(ctx, type, size, sloc, name)
  , value_(value)
{}

///////////////////////////////////////////////////////////////////////////////

inputimpl::inputimpl(context* ctx,
                     uint32_t size,
                     const io_value_t& value,
                     const std::string& name,
                     const source_location& sloc)
  : ioportimpl(ctx, type_input, size, value, sloc, name)
{}

inputimpl::~inputimpl() {}

lnodeimpl* inputimpl::clone(context* ctx, const clone_map&) {
  return ctx->create_node<inputimpl>(size_, value_, name_, sloc_);
}

void inputimpl::print(std::ostream& out) const {
  out << "#" << id_ << " <- " << this->type() << size_;
  out << "(" << name_;
  if (!binding_.empty()) {
    out << ", $" << binding_.id();
  }
  out << ")";
}

///////////////////////////////////////////////////////////////////////////////

outputimpl::outputimpl(context* ctx,
                       const lnode& src,
                       const io_value_t& value,
                       const std::string& name,
                       const source_location& sloc)
  : ioportimpl(ctx, type_output, src.size(), value, sloc, name) {
  srcs_.emplace_back(src);
}

outputimpl::~outputimpl() {}

lnodeimpl* outputimpl::clone(context* ctx, const clone_map& cloned_nodes) {
  auto src = cloned_nodes.at(this->src(0).id());
  return ctx->create_node<outputimpl>(src, value_, name_, sloc_);
}

void outputimpl::print(std::ostream& out) const {
  out << "#" << id_ << " <- " << this->type() << size_;
  out << "(" << name_ << ", #" << srcs_[0].id() << ")";
}

///////////////////////////////////////////////////////////////////////////////

tapimpl::tapimpl(context* ctx,
                 const lnode& src,
                 const io_value_t& value,
                 const std::string& name,
                 const source_location& sloc)
  : ioportimpl(ctx, type_tap, src.size(), value, sloc, name) {
  srcs_.emplace_back(src);
}

tapimpl::~tapimpl() {}

lnodeimpl* tapimpl::clone(context* ctx, const clone_map& cloned_nodes) {
  auto src = cloned_nodes.at(this->src(0).id());
  return ctx->create_node<tapimpl>(src, value_, name_, sloc_);
}

void tapimpl::print(std::ostream& out) const {
  out << "#" << id_ << " <- " << this->type() << size_;
  out << "(" << name_ << ", #" << srcs_[0].id() << ")";
}

///////////////////////////////////////////////////////////////////////////////

lnodeimpl* ch::internal::createInputNode(const std::string& name,
                                         uint32_t size,
                                         const source_location& sloc) {
  auto value = smart_ptr<sdata_type>::make(size);
  return ctx_curr()->create_node<inputimpl>(size, value, name, sloc);
}

lnodeimpl* ch::internal::createOutputNode(const std::string& name,
                                          const lnode& src,
                                          const source_location& sloc) {
  auto value = smart_ptr<sdata_type>::make(src.size());
  return ctx_curr()->create_node<outputimpl>(src, value, name, sloc);
}

///////////////////////////////////////////////////////////////////////////////

system_io_buffer::system_io_buffer(const lnode& io)
  : base(sdata_type(), nullptr, 0, io.size())
  , io_(reinterpret_cast<ioportimpl*>(io.impl())->value())
{}

const sdata_type& system_io_buffer::data() const {
  return *io_;
}

void system_io_buffer::read(uint32_t src_offset,
                            sdata_type& dst,
                            uint32_t dst_offset,
                            uint32_t length) const {
  return dst.copy(dst_offset, *io_, src_offset, length);
}

void system_io_buffer::write(uint32_t dst_offset,
                             const sdata_type& src,
                             uint32_t src_offset,
                             uint32_t length) {
  io_->copy(dst_offset, src, src_offset, length);
}

void system_io_buffer::read(uint32_t src_offset,
                            void* out,
                            uint32_t byte_alignment,
                            uint32_t dst_offset,
                            uint32_t length) const {
  return io_->read(src_offset, out, byte_alignment, dst_offset, length);
}

void system_io_buffer::write(uint32_t dst_offset,
                             const void* in,
                             uint32_t byte_alignment,
                             uint32_t src_offset,
                             uint32_t length) {
  io_->write(dst_offset, in, byte_alignment, src_offset, length);
}

void system_io_buffer::bind(system_io_buffer* out) {
  out->io_.reset_all(io_);
}
