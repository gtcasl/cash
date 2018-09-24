#include "ioimpl.h"
#include "ioport.h"
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
                       const source_location& sloc,
                       const std::string& name)
  : ioimpl(ctx, type, size, sloc, name)
  , value_(size)
{}

///////////////////////////////////////////////////////////////////////////////

inputimpl::inputimpl(context* ctx,
                     uint32_t size,
                     const std::string& name,
                     const source_location& sloc)
  : ioportimpl(ctx, type_input, size, sloc, name)
{}

inputimpl::~inputimpl() {}

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
                       const std::string& name,
                       const source_location& sloc)
  : ioportimpl(ctx, type_output, src.size(), sloc, name) {
  srcs_.emplace_back(src);
}

outputimpl::~outputimpl() {}

void outputimpl::print(std::ostream& out) const {
  out << "#" << id_ << " <- " << this->type() << size_;
  out << "(" << name_ << ", #" << srcs_[0].id() << ")";
}

///////////////////////////////////////////////////////////////////////////////

tapimpl::tapimpl(context* ctx,
                 const lnode& src,
                 const std::string& name,
                 const source_location& sloc)
  : ioportimpl(ctx, type_tap, src.size(), sloc, name) {
  srcs_.emplace_back(src);
}

tapimpl::~tapimpl() {}

void tapimpl::print(std::ostream& out) const {
  out << "#" << id_ << " <- " << this->type() << size_;
  out << "(" << name_ << ", #" << srcs_[0].id() << ")";
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

///////////////////////////////////////////////////////////////////////////////

system_io_buffer::system_io_buffer(const lnode& io)
  : base(bitvector(), nullptr, 0, io.size()), io_(io)
{}

const bitvector& system_io_buffer::data() const {
  return reinterpret_cast<ioportimpl*>(io_.impl())->value();
}

void system_io_buffer::read(uint32_t src_offset,
                            bitvector& dst,
                            uint32_t dst_offset,
                            uint32_t length) const {
  auto port = reinterpret_cast<ioportimpl*>(io_.impl());
  return dst.copy(dst_offset, port->value(), src_offset, length);
}

void system_io_buffer::write(uint32_t dst_offset,
                             const bitvector& src,
                             uint32_t src_offset,
                             uint32_t length) {
  auto port = reinterpret_cast<ioportimpl*>(io_.impl());
  port->value().copy(dst_offset, src, src_offset, length);
}

void system_io_buffer::read(uint32_t src_offset,
                            void* out,
                            uint32_t byte_alignment,
                            uint32_t dst_offset,
                            uint32_t length) const {
  auto port = reinterpret_cast<ioportimpl*>(io_.impl());
  return port->value().read(src_offset, out, byte_alignment, dst_offset, length);
}

void system_io_buffer::write(uint32_t dst_offset,
                             const void* in,
                             uint32_t byte_alignment,
                             uint32_t src_offset,
                             uint32_t length) {
  auto port = reinterpret_cast<ioportimpl*>(io_.impl());
  port->value().write(dst_offset, in, byte_alignment, src_offset, length);
}
