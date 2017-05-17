#include "bit.h"
#include "lnodeimpl.h"
#include "ioimpl.h"
#include "proxyimpl.h"
#include "litimpl.h"
#include "tickable.h"
#include "regimpl.h"
#include "cdomain.h"
#include "snodeimpl.h"
#include "context.h"

using namespace std;
using namespace chdl_internal;

lnodeimpl::lnodeimpl(ch_operator op, context* ctx, uint32_t size) 
  : m_op(op)
  , m_ctx(ctx)
  , m_value(size) {
  m_id = ctx->add_node(this);  
}

lnodeimpl::~lnodeimpl() {  
  for (auto iter = m_refs.begin(), iterEnd = m_refs.end(); iter != iterEnd;) {
    (*iter++).node->clear();
  }
  m_ctx->remove_node(this);  
}

void lnodeimpl::add_ref(const lnode* node, const lnode* owner) {
  m_refs.emplace(node, owner);  
}

void lnodeimpl::remove_ref(const lnode* node) {
  m_refs.erase(node);
}

void lnodeimpl::update_ref(const lnode* node, lnodeimpl* impl) {
  CHDL_ABORT("Not yet implemented");
}

const lnode* lnodeimpl::get_ref_owner(const lnode* node) {
  auto iter = m_refs.find(node);
  if (iter != m_refs.end()) {
    return iter->owner;
  }
  return nullptr;
}

bool lnodeimpl::ready() const {
  for (auto& src : m_srcs) {
    if (!src.ready())
      return false;
  }
  return true;
}

bool lnodeimpl::valid() const {
  for (auto& src : m_srcs) {
    if (!src.valid())
      return false;
  }
  return true;
}

const char* lnodeimpl::get_name() const {
  static const char* sc_names[] = {
    CHDL_OPERATOR_ENUM(CHDL_OPERATOR_NAME)
  };
  return sc_names[(int)m_op];
}

void lnodeimpl::print(std::ostream& out) const {
  out << "#" << m_id << " <- " << this->get_name() << m_value.get_size();
  uint32_t n = m_srcs.size();
  if (n > 0) {
    out << "(";
    for (uint32_t i = 0; i < n; ++i) {
      if (i > 0)
        out << ", ";
      out << "#" << m_srcs[i].get_id();
    }
    out << ")";
  }
}

///////////////////////////////////////////////////////////////////////////////

undefimpl::undefimpl(context* ctx, uint32_t size) 
  : lnodeimpl(op_undef, ctx, size) 
{}

const bitvector& undefimpl::eval(ch_cycle t) {
  CHDL_ABORT("undefined node: %d!", m_id);
  return m_value; 
}

void undefimpl::print_vl(std::ostream& out) const {
  TODO("Not yet Implemented!");
}

///////////////////////////////////////////////////////////////////////////////

lnode::lnode(uint32_t size) : m_impl(nullptr) {
  // force initialization of nested objects
  if (ctx_curr()->conditional_enabled()) {
    this->ensureInitialized(size);
  }
}

lnode::lnode(const lnode& rhs) : m_impl(nullptr) { 
  this->assign(rhs.m_impl, &rhs, true);
}

lnode::lnode(lnode&& rhs) : m_impl(nullptr) {
  this->move(rhs);
}

lnode::lnode(lnodeimpl* impl) : m_impl(nullptr) { 
  this->assign(impl, nullptr, true);
}

lnode::lnode(const bitstream_type& data) : m_impl(nullptr) {
  uint32_t dst_offset = 0;
  for (auto& p : data) {
    this->assign(dst_offset, p.data, p.offset, p.length, data.get_size(), true);   
    dst_offset += p.length;
  }
}

lnode::lnode(const bitvector& value) : m_impl(nullptr) {
  this->assign(ctx_curr()->create_literal(value), nullptr, true);
}

lnode::~lnode() {
  this->clear();
}

void lnode::assign(const bitvector& value) {
  this->assign(ctx_curr()->create_literal(value), nullptr);
}

lnode& lnode::operator=(const lnode& rhs) {
  this->assign(rhs.m_impl, &rhs);
  return *this;
}

lnode& lnode::operator=(lnode&& rhs) {
  this->move(rhs);
  return *this;
}

lnode& lnode::operator=(lnodeimpl* rhs) {
  this->assign(rhs, nullptr);
  return *this;
}

uint32_t lnode::get_id() const {
  return m_impl ? m_impl->get_id() : 0; 
}

context* lnode::get_ctx() const {
  assert(m_impl);
  return m_impl->get_ctx();
}

uint32_t lnode::get_size() const {
  return m_impl ? m_impl->get_size() : 0;
}

bool lnode::ready() const {
  return m_impl ? m_impl->ready() : true;
}

bool lnode::valid() const {
  return m_impl ? m_impl->valid() : true;
}

const bitvector& lnode::eval(ch_cycle t) {
  assert(m_impl);
  return m_impl->eval(t);
}

const lnode& lnode::ensureInitialized(uint32_t size) const {
  if (m_impl == nullptr) {
    m_impl = new undefimpl(ctx_curr(), size);
  }
  assert(m_impl->get_size() == size);
  return *this;
}

void lnode::clear() const {
  if (m_impl)
    m_impl->remove_ref(this);
  m_impl = nullptr;
}

lnodeimpl* lnode::get_impl() const {
  assert(m_impl);
  return m_impl;
}

void lnode::move(lnode& rhs) {
  assert(rhs.m_impl);
  assert(rhs.m_impl != m_impl);
  if (m_impl != rhs.m_impl) {
    this->clear();
    m_impl = rhs.m_impl;
    m_impl->add_ref(this, rhs.m_impl->get_ref_owner(&rhs));
  }
  rhs.clear();
}

void lnode::assign(lnodeimpl* impl, const lnode* src, bool initialization) const {
  if (impl) {
    if (!initialization) {
      // resolve conditionals if inside a branch
      impl = impl->get_ctx()->resolve_conditional(m_impl, impl);
      if (impl == m_impl)
        return;
    } 
    impl->add_ref(this, src);
  }
  if (m_impl) {
    CHDL_CHECK(impl != m_impl, "redundant assignment for node %s%d(#%d)!\n", m_impl->get_name(), m_impl->get_size(), m_impl->get_id());    
    m_impl->remove_ref(this);
    m_impl->update_ref(this, impl);
  }  
  m_impl = impl;
}

void lnode::read(bitstream_type& inout, uint32_t offset, uint32_t length, uint32_t size) const {
  assert((offset + length) <= size);
  this->ensureInitialized(size);
  inout.push({*this, offset, length});
}

void lnode::write(uint32_t dst_offset, const bitstream_type& in, uint32_t src_offset, uint32_t src_length, uint32_t size) {
  assert((dst_offset + src_length) <= size);
  for (auto& p : in) {
    if (src_offset < p.length) {
      uint32_t len = std::min(p.length - src_offset, src_length);
      this->assign(dst_offset, p.data, p.offset + src_offset, len, size);         
      src_length -= len;
      if (src_length == 0)
        return;
      dst_offset += len;                
      src_offset = p.length;
    }
    src_offset -= p.length;
  }
}

void lnode::assign(uint32_t dst_offset, const lnode& src, uint32_t src_offset, uint32_t src_length, uint32_t size, bool initialization) {
  assert(size > dst_offset);
  assert(size >= dst_offset + src_length);
  
  const lnode* src_node = &src;
  lnodeimpl* src_impl = src_node->get_impl();    
  context* const ctx = src_impl->get_ctx();
  
  // check if full assignment
  if (src_length == size) {
    assert(dst_offset == 0);
    // check if partial source
    if (src_impl->get_size() > src_length) {
      proxyimpl* const proxy = new proxyimpl(ctx, src_length);
      proxy->add_node(0, src, src_offset, src_length);
      src_impl = proxy;
      src_node = nullptr;
    }
  } else {
    // partial assignment using proxy
    assert(src_length < size);    
    proxyimpl* const proxy = new proxyimpl(ctx, size);  
    this->ensureInitialized(size);
    proxy->add_node(0, *this, 0, size);      
    proxy->add_node(dst_offset, src, src_offset, src_length);
    src_impl = proxy;
    src_node = nullptr;
  }
  
  this->assign(src_impl, src_node, initialization);
}
