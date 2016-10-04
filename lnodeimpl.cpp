#include "lnodeimpl.h"
#include "context.h"
#include "proxyimpl.h"
#include "litimpl.h"
#include "ioimpl.h"
#include "tickable.h"
#include "ioimpl.h"
#include "bitv.h"

using namespace std;
using namespace chdl_internal;

lnodeimpl::lnodeimpl(const std::string& name, context* ctx, uint32_t size, bool undefined) 
  : m_name(name)
  , m_ctx(ctx)
  , m_value(size) {
  m_id = ++ctx->nodeids;
  if (undefined) {
    ctx->undefs.emplace_back(this);
  } else {
    ctx->nodes.emplace_back(this);
  }
}

lnodeimpl::~lnodeimpl() {
  for (auto node : m_refs) {
    node->m_impl = nullptr;
  }
}

void lnodeimpl::replace_ref(lnodeimpl* impl) {
  assert(impl != this);
  for (auto node : m_refs) {
    assert(node->m_impl == this);
    node->m_impl = impl;
    impl->add_ref(node);
  }
  m_refs.clear();
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

undefimpl::undefimpl(const std::string& name, context* ctx, uint32_t size) 
  : lnodeimpl(name, ctx, size, true) {
  const char* dbg_node = std::getenv("CHDL_DEBUG_NODE");
  if (dbg_node) {
    uint64_t dbg_node_id = strtoll(dbg_node, nullptr, 10);
    assert(m_id != dbg_node_id);
  }
}

undefimpl::~undefimpl() {
  assert(m_refs.empty());
  assert(m_ctx->undefs.size() > 0);
  m_ctx->undefs.remove(this);
}

const bitvector& undefimpl::eval(ch_cycle t) {
  CHDL_ABORT("undefined node: %ld!", m_id);
  return m_value; 
}

void undefimpl::print_vl(std::ostream& out) const {
  //--
}

///////////////////////////////////////////////////////////////////////////////

lnode::lnode(const lnode& rhs) : m_impl(nullptr) {  
  this->assign(rhs.m_impl);
}

lnode::lnode(lnode&& rhs) : m_impl(nullptr) {  
  this->move(rhs);
}

lnode::lnode(const lnode& rhs, uint32_t size) : m_impl(nullptr) {
  rhs.ensureInitialized(size);  
  this->assign(rhs.m_impl);
}

lnode::lnode(lnodeimpl* impl) : m_impl(nullptr) {
  this->assign(impl);
}

lnode::lnode(const std::initializer_list<uint32_t>& value, uint32_t size) : m_impl(nullptr) {
  this->assign(ctx_curr()->create_literal(value, size));
}

lnode::~lnode() {
  this->clear();
}

void lnode::clear() {
  if (m_impl) {
    m_impl->remove_ref(this);
    undefimpl* impl_ = dynamic_cast<undefimpl*>(m_impl);
    if (impl_ && impl_->unreferenced())
      delete impl_;    
    m_impl = nullptr;
  }
}

void lnode::assign(const std::initializer_list<uint32_t>& value, uint32_t size) {
  this->assign(ctx_curr()->create_literal(value, size));
}

lnode& lnode::operator=(const lnode& rhs) {
  this->assign(rhs.m_impl);
  return *this;
}

lnode& lnode::operator=(lnode&& rhs) {
  this->move(rhs);
  return *this;
}

uint64_t lnode::get_id() const {
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

void lnode::ensureInitialized(uint32_t size) const {
  if (m_impl == nullptr) {
    m_impl = new undefimpl(ctx_curr(), size);
    m_impl->add_ref(this);
  }
  assert(m_impl->get_size() == size);
}

void lnode::assign(lnodeimpl* impl) const {
  assert(impl);
  if (m_impl == impl)
    return;
  if (m_impl) {
    assert(m_impl->get_size() == impl->get_size());
    m_impl->remove_ref(this);
    undefimpl* undef = dynamic_cast<undefimpl*>(m_impl);
    if (undef) {
      undef->replace_ref(impl);
      delete undef;
    }
  }
  impl->add_ref(this);
  m_impl = impl;
}

void lnode::move(lnode& rhs) {
  assert(rhs.m_impl);
  if (m_impl != rhs.m_impl) {
    if (m_impl) {
      m_impl->remove_ref(this);
      undefimpl* undef = dynamic_cast<undefimpl*>(m_impl);
      if (undef && undef->unreferenced())
        delete undef;
    }  
    m_impl = rhs.m_impl;
    m_impl->add_ref(this);
  }
  rhs.clear();
}

void lnode::assign(uint32_t dst_offset, const lnode& src, uint32_t src_offset, uint32_t src_length, uint32_t size) {
  assert(size > dst_offset && size >= dst_offset + src_length);
  if (size == src_length && size == src.get_size()) {
    assert(dst_offset == 0 && src_offset == 0);
    this->assign(src.m_impl);
  } else {
    proxyimpl* proxy = dynamic_cast<proxyimpl*>(m_impl);
    if (proxy) {
      proxy->add_src(dst_offset, src, src_offset, src_length);
    } else {
      proxyimpl* proxy = new proxyimpl(src.get_ctx(), size);
      proxy->add_src(dst_offset, src, src_offset, src_length);
      this->assign(proxy);
    }
  }  
}

///////////////////////////////////////////////////////////////////////////////

ch_logicbase& ch_logicbase::operator=(const std::initializer_list<uint32_t>& value) {
  return this->operator =(ch_logic(value));
}

ch_logicbase::operator const lnode&() const { 
  return ch_logic(*this); 
}

ch_logicbase::operator lnode&() { 
  return ch_logic(*this);
}

///////////////////////////////////////////////////////////////////////////////

lnode chdl_internal::createNullNode(uint32_t size) {
  return lnode(new nullimpl(ctx_curr(), size));
}
