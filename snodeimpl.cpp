#include "snodeimpl.h"
#include "ioimpl.h"
#include "bus.h"

using namespace std;
using namespace chdl_internal;

snodeimpl::snodeimpl(uint32_t size) 
  : m_value(size)
  , m_obridge(nullptr)
  , m_ctime(~0ull) 
{}

snodeimpl::snodeimpl(const std::initializer_list<uint32_t>& value, uint32_t size) 
  : m_value(value, size)  
  , m_obridge(nullptr)
  , m_ctime(~0ull) 
{}

snodeimpl::~snodeimpl() {
  for (auto& b : m_bridges) {
    b.second->detach();
  }
}

void snodeimpl::bind(context* ctx, unsigned index, iobridge* bridge) {
  obridge* out = dynamic_cast<obridge*>(bridge);
  if (out) {
    if (m_obridge)
      CHDL_ABORT("duplicate source binding!");
    m_obridge = out;
  }

  // remove existing binding
  const portid_t pid = {ctx, index};
  auto iter = m_bridges.find(pid);
  if (iter != m_bridges.end())
    iter->second->detach();

  // set new binding
  bridge->add_ref();
  m_bridges[pid] = bridge;
}

void snodeimpl::bind(snodeimpl* src) {
  if (src->m_obridge == nullptr)
    CHDL_ABORT("source not valid!");
  
  // get src portid
  const portid_t* portid = src->get_portid(src->m_obridge);
  assert(portid != nullptr);

  // apply binding
  this->bind(portid->ctx, portid->idx, src->m_obridge);
}

bool snodeimpl::ready() const {
  if (m_obridge)
    return m_obridge->ready();  
  return true;
}

bool snodeimpl::valid() const {
  if (m_obridge)
    return m_obridge->valid();
  return true;
}

const bitvector& snodeimpl::eval(ch_cycle t) {
  if (m_obridge && m_ctime != t) {
    m_ctime = t;
    m_value = m_obridge->eval(t);
  }
  return m_value;
}

const snodeimpl::portid_t* snodeimpl::get_portid(iobridge* bridge) const {
  auto iter = std::find_if(m_bridges.begin(), m_bridges.end(),
    [bridge](const bridges_t::value_type& v)->bool { return v.second == bridge; });
  if (iter == m_bridges.end())
    return nullptr;
  return &iter->first;
}

void snodeimpl::get_bindings(std::set<context*>& bindings) const {
  for (auto& p : m_bridges) {
    bindings.emplace(p.first.ctx);
  }
}

///////////////////////////////////////////////////////////////////////////////

ch_signalbase& ch_signalbase::operator=(const std::initializer_list<uint32_t>& value) {
  return this->operator =(ch_signal(value));
}

ch_signalbase::operator const snode&() const { 
  return ch_signal(*this); 
}

ch_signalbase::operator snode&() { 
  return ch_signal(*this);
}

///////////////////////////////////////////////////////////////////////////////

snode::snode(const snode& rhs) {
  this->assign(rhs.m_impl); 
}

snode::snode(snode&& rhs) : m_impl(nullptr) {  
  this->move(rhs);
}

snode::snode(const snode& rhs, uint32_t size) : m_impl(nullptr) {
  rhs.ensureInitialized(size);  
  this->assign(rhs.m_impl);
}

snode::snode(snodeimpl* impl) : m_impl(nullptr) {
  this->assign(impl);
}

snode::snode(const std::initializer_list<uint32_t>& value, uint32_t size) : m_impl(nullptr) {
  this->assign(new snodeimpl(value, size));  
}

snode::~snode() {
  if (m_impl) {
    m_impl->release();
    m_impl == nullptr;
  }
}

snode& snode::operator=(const snode& rhs) {
  this->assign(rhs.m_impl);
  return *this;
}

snode& snode::operator=(snode&& rhs) {
  this->move(rhs);
  return *this;
}

uint32_t snode::get_size() const {
  return m_impl ? m_impl->get_size() : 0;
}

void snode::ensureInitialized(uint32_t size) const {
  if (m_impl == nullptr) {
    m_impl = new snodeimpl(size);
  }
  assert(m_impl->get_size() == size);
}

void snode::move(snode& rhs) {  
  if (m_impl)
    m_impl->release();
  m_impl = rhs.m_impl;
  rhs.m_impl = nullptr;
}

void snode::assign(const std::initializer_list<uint32_t>& value, uint32_t size) {
  this->assign(new snodeimpl(value, size));
}

void snode::assign(snodeimpl* impl) {
  TODO();
}

void snode::assign(uint32_t dst_offset, const snode& src, uint32_t src_offset, uint32_t src_length, uint32_t size) {
  TODO();
}

uint32_t snode::read(uint32_t idx) const {
  assert(m_impl);
  return m_impl->read(idx);
}

void snode::write(uint32_t idx, uint32_t value) {
  assert(m_impl);
  m_impl->write(idx, value);
}
