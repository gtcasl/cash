#include "bitv.h"
#include "lnodeimpl.h"
#include "ioimpl.h"
#include "proxyimpl.h"
#include "litimpl.h"
#include "tickable.h"
#include "cdomain.h"
#include "snodeimpl.h"
#include "context.h"

using namespace std;
using namespace chdl_internal;

lnodeimpl::lnodeimpl(const std::string& name, context* ctx, uint32_t size) 
  : m_name(name)
  , m_ctx(ctx)
  , m_value(size) {
  m_id = ctx->add_node(this);  
}

lnodeimpl::~lnodeimpl() {
  for (auto node : m_refs) {
    node->m_impl = nullptr;
  }
}

void lnodeimpl::replace_refs(lnodeimpl* impl) {
  assert(impl != this);
  for (auto node : m_refs) {
    assert(node->m_impl == this);
    node->m_impl = impl;
    impl->add_ref(node);
  }
  m_refs.clear();
}

lnodeimpl* lnodeimpl::resolve(lnodeimpl* impl) {
  return m_ctx->resolve(impl, this);
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

void lnodeimpl::print(std::ostream& out) const {
  out << "#" << m_id << " <- " << m_name << m_value.get_size();
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
  out << endl;
}

///////////////////////////////////////////////////////////////////////////////

undefimpl::undefimpl(context* ctx, uint32_t size) 
  : lnodeimpl("undef", ctx, size) 
{}

undefimpl::~undefimpl() {
  assert(m_refs.empty());
  m_ctx->remove_node(this);
}

void undefimpl::remove_ref(const lnode* curr_owner, lnodeimpl* new_owner) {
  m_refs.erase(curr_owner);
  if (new_owner) {
    assert(this->get_size() == new_owner->get_size());
    this->replace_refs(new_owner);
  }
  if (this->unreferenced())
    this->release();
}

void undefimpl::update_refs(uint32_t start, lnodeimpl* src, uint32_t offset, uint32_t length) {
  assert(length <= src->get_size());
  assert(length <= this->get_size());  
  if (length < this->get_size()) {
    // copy region smaller than dst buffer
    proxyimpl* proxy = new proxyimpl(m_ctx, this->get_size());
    this->replace_refs(proxy);
    proxy->add_node(0, this, 0, this->get_size());
    proxy->add_node(start, src, offset, length, true);    
  } else {
    assert(length == this->get_size());
    lnodeimpl* impl = src; 
    if (length < src->get_size()) {
      // copy region smaller than src buffer 
      impl = new proxyimpl(m_ctx, length);
      reinterpret_cast<proxyimpl*>(impl)->add_node(0, src, offset, length);
    }
    this->replace_refs(impl);
    this->release();
  }
}

const bitvector& undefimpl::eval(ch_cycle t) {
  CHDL_ABORT("undefined node: %d!", m_id);
  return m_value; 
}

void undefimpl::print_vl(std::ostream& out) const {
  //--
}

///////////////////////////////////////////////////////////////////////////////

lnode::lnode(const lnode& rhs) : m_impl(nullptr) {  
  this->assign(rhs.m_impl, true);
}

lnode::lnode(lnode&& rhs) : m_impl(nullptr) {  
  this->move(rhs);
}

lnode::lnode(lnodeimpl* impl) : m_impl(nullptr) {
  this->assign(impl, true);
}

lnode::lnode(const std::vector< partition<lnode> >& data, uint32_t size) : m_impl(nullptr) {  
  uint32_t dst_offset = 0;
  for (auto& p : data) {
    this->assign(dst_offset, p.data.m_impl, p.offset, p.length, size, true);   
    dst_offset += p.length;
  }
}

lnode::lnode(const bitvector& value) : m_impl(nullptr) {
  this->assign(ctx_curr()->create_literal(value), true);
}

lnode::~lnode() {
  this->reset();
}

void lnode::assign(const bitvector& value) {
  this->assign(ctx_curr()->create_literal(value));
}

lnode& lnode::operator=(const lnode& rhs) {
  this->assign(rhs.m_impl);
  return *this;
}

lnode& lnode::operator=(lnode&& rhs) {
  this->move(rhs);
  return *this;
}

lnode& lnode::operator=(lnodeimpl* rhs) {
  this->assign(rhs);
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

const lnode& lnode::ensureInitialized(uint32_t size, uint32_t offset, uint32_t length) const {
  if (m_impl == nullptr) {   
    context* ctx = ctx_curr();
    if (length == 0 || length == size) {
      m_impl = new undefimpl(ctx, size);
    } else {
      m_impl = new proxyimpl(ctx, size);
      reinterpret_cast<proxyimpl*>(m_impl)->resize(offset, length);
    }
    m_impl->add_ref(this);
  } else {
    proxyimpl* proxy = dynamic_cast<proxyimpl*>(m_impl);
    if (proxy && !proxy->includes(offset, length)) {
      proxy->resize(offset, length);
    }
  }
  assert(m_impl->get_size() >= length);
  return *this;
}

void lnode::reset(lnodeimpl* impl, bool initialization) const {
  if (impl) {
    if (!initialization) {
      impl = impl->resolve(m_impl);
    }
    impl->add_ref(this);
  }
  if (m_impl) {
    m_impl->remove_ref(this, impl);
  }
  m_impl = impl;
}

void lnode::assign(lnodeimpl* impl, bool initialization) const {
  assert(impl);
  assert(impl != m_impl);
  this->reset(impl, initialization);
}

void lnode::move(lnode& rhs) {
  assert(rhs.m_impl);
  assert(rhs.m_impl != m_impl);
  if (m_impl != rhs.m_impl) {
    this->reset();
    m_impl = rhs.m_impl;
    m_impl->add_ref(this);
  }
  rhs.reset();
}

void lnode::read(std::vector< partition<lnode> >& out, uint32_t offset, uint32_t length, uint32_t size) const {
  assert((offset + length) <= size);
  this->ensureInitialized(size, offset, length);
  out.push_back({*this, offset, length});
}

void lnode::write(uint32_t dst_offset, const std::vector< partition<lnode> >& data, uint32_t src_offset, uint32_t src_length, uint32_t size) {
  assert((dst_offset + src_length) <= size);
  for (auto& p : data) {
    if (src_offset < p.length) {
      uint32_t len = std::min(p.length - src_offset, src_length);
      this->assign(dst_offset, p.data.m_impl, p.offset + src_offset, len, size, false);         
      src_length -= len;
      if (src_length == 0)
        return;
      dst_offset += len;                
      src_offset = p.length;
    }
    src_offset -= p.length;
  }
}

void lnode::assign(uint32_t dst_offset, lnodeimpl* src, uint32_t src_offset, uint32_t src_length, uint32_t size, bool initialization) {
  assert(src);
  assert(src != m_impl);
  assert(size > dst_offset);
  assert(size >= dst_offset + src_length);
  
  context* ctx = src->get_ctx();
  
  if (src_length == size) {
    assert(dst_offset == 0);
    if (src->get_size() > src_length) {
      proxyimpl* proxy = new proxyimpl(ctx, src_length);
      proxy->add_node(0, src, src_offset, src_length);
      src = proxy;
    }
    this->assign(src, initialization);
  } else {
    assert(src_length < size);
    if (m_impl) {
      assert(m_impl->get_size() == size);
      if (src->get_size() > src_length) {
        proxyimpl* proxy = new proxyimpl(ctx, src_length);
        proxy->add_node(0, src, src_offset, src_length);
        src = proxy;
      }
      
      proxyimpl* dst = dynamic_cast<proxyimpl*>(m_impl);
      if (dst == nullptr) {
        dst = new proxyimpl(ctx, size);
        lnodeimpl* impl = m_impl;
        impl->replace_refs(dst);
        dst->add_node(0, impl, 0, size);
      }
      
      proxyimpl* dst_subset = new proxyimpl(ctx, src_length);
      dst_subset->add_node(0, dst, dst_offset, src_length);
      lnode ds(dst_subset);
      ds.assign(src, initialization);
      
      dst->add_node(dst_offset, ds.m_impl, 0, src_length);
    } else {
      proxyimpl* proxy = new proxyimpl(ctx, size);
      proxy->add_node(dst_offset, src, src_offset, src_length);
      this->assign(proxy, initialization);
    }    
  }
}
