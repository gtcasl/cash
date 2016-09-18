#include "nodeimpl.h"
#include "context.h"
#include "proxyimpl.h"
#include "litimpl.h"
#include "ioimpl.h"
#include "tickable.h"
#include "ioimpl.h"

using namespace std;
using namespace chdl_internal;

nodeimpl::nodeimpl(context* ctx, uint32_t size, bool undefined) 
  : m_ctx(ctx), m_value(size) {
  m_id = ++ctx->nodeids;
  if (undefined) {
    ++ctx->undefcount;
  } else {
    ctx->nodes.emplace_back(this);
  }
}

nodeimpl::~nodeimpl() {
  for (auto node : m_refs) {
    node->m_impl = nullptr;
  }
}

void nodeimpl::replace_ref(nodeimpl* impl) {
  assert(impl != this);
  for (auto node : m_refs) {
    assert(node->m_impl == this);
    node->m_impl = impl;
    impl->add_ref(node);
  }
  m_refs.clear();
}

///////////////////////////////////////////////////////////////////////////////

undefimpl::undefimpl(context* ctx, uint32_t size) : nodeimpl(ctx, size, true) {
  const char* dbg_node = std::getenv("CHDL_DEBUG_NODE");
  if (dbg_node) {
    uint64_t dbg_node_id = strtoll(dbg_node, nullptr, 10);
    assert(m_id != dbg_node_id);
  }
}

undefimpl::~undefimpl() {
  assert(m_refs.empty());
}

bool undefimpl::ready() const {
  return true;  
}

bool undefimpl::valid() const {
  return true;
}

const bitvector& undefimpl::eval(ch_cycle t) {
  CHDL_ABORT("undefined node: %ld!", m_id);
  return m_value; 
}

void undefimpl::print(std::ostream& out) const {
  //--
}

void undefimpl::print_vl(std::ostream& out) const {
  //--
}

///////////////////////////////////////////////////////////////////////////////

ch_node::ch_node(const ch_node& rhs) : m_impl(nullptr) {  
  this->assign(rhs.m_impl, true);
}

ch_node::ch_node(const ch_node& rhs, uint32_t size) : m_impl(nullptr) {
  rhs.ensureInitialized(ctx_curr(), size);  
  this->assign(rhs.m_impl, true);
}

ch_node::ch_node(const std::initializer_list<uint32_t>& value, uint32_t size) : m_impl(nullptr) {
  this->assign(new litimpl(ctx_curr(), size, value), true);
}

ch_node::~ch_node() {
  this->clear();
}

void ch_node::clear() {
  if (m_impl) {
    m_impl->remove_ref(this);
    undefimpl* impl_ = dynamic_cast<undefimpl*>(m_impl);
    if (impl_ && impl_->unreferenced()) {
      --impl_->get_ctx()->undefcount;
      delete impl_;
    }
    m_impl = nullptr;
  }
}

ch_node& ch_node::operator=(const ch_node& rhs) {
  assert(rhs.m_impl);
  if (m_impl != rhs.m_impl)
    this->assign(rhs.m_impl, false);
  return *this;
}

uint64_t ch_node::get_id() const {
  return m_impl ? m_impl->get_id() : 0; 
}

context* ch_node::get_ctx() const {
  assert(m_impl);
  return m_impl->get_ctx();
}

uint32_t ch_node::get_size() const {
  return m_impl ? m_impl->get_size() : 0;
}

bool ch_node::ready() const {
  return m_impl ? m_impl->ready() : true;
}

bool ch_node::valid() const {
  return m_impl ? m_impl->valid() : true;
}

const bitvector& ch_node::eval(ch_cycle t) {
  assert(m_impl);
  return m_impl->eval(t);
}

void ch_node::ensureInitialized(context* ctx, uint32_t size) const {
  if (m_impl == nullptr) {
    m_impl = new undefimpl(ctx, size);
    m_impl->add_ref(this);
  }
}

void ch_node::assign(nodeimpl* impl, bool replace_all) {
  assert(impl);
  if (m_impl) {
    m_impl->remove_ref(this);
    undefimpl* undef = dynamic_cast<undefimpl*>(m_impl);
    if (undef) {
      if (replace_all) {
        undef->replace_ref(impl);
        --undef->get_ctx()->undefcount;
        delete undef;
      } else {
        if (undef->unreferenced()) {
          --undef->get_ctx()->undefcount;
          delete undef;
        }
      }      
    }
  }
  impl->add_ref(this);
  m_impl = impl;
}

void ch_node::assign(uint32_t size, uint32_t dst_offset, const ch_node& src, uint32_t src_offset, uint32_t src_length) {
  assert(size > dst_offset && size >= dst_offset + src_length);
  context* ctx = ctx_curr();
  src.ensureInitialized(ctx, src_length);
  if (size == src_length && size == src.get_size()) {
    assert(dst_offset == 0 && src_offset == 0);
    this->assign(src.m_impl, true);
  } else {
    proxyimpl* proxy = dynamic_cast<proxyimpl*>(m_impl);
    if (proxy) {
      proxy->add_src(dst_offset, src, src_offset, src_length);
    } else {
      this->ensureInitialized(ctx, size);
      proxyimpl* proxy = new proxyimpl(*this);
      proxy->add_src(dst_offset, src, src_offset, src_length);
      this->clear();
      this->assign(proxy, true);
    }
  }  
}

///////////////////////////////////////////////////////////////////////////////

ch_node chdl_internal::createNullNode(uint32_t size) {
  return ch_node(new nullimpl(ctx_curr(), size));
}
