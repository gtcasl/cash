#include "ioimpl.h"
#include "busimpl.h"
#include "context.h"

using namespace std;
using namespace chdl_internal;

ioimpl::ioimpl(context* ctx, uint32_t size, const std::string name)
  : nodeimpl(ctx, size)
  , m_name(name)
  , m_bridge(nullptr)
{}

ioimpl::~ioimpl() {
  if (m_bridge) 
    m_bridge->detach();  
}

void ioimpl::bind(iobridge* bridge) {
  if (m_bridge)
    m_bridge->detach();  
  bridge->add_ref();
  m_bridge = bridge;
}

///////////////////////////////////////////////////////////////////////////////

inputimpl::inputimpl(context* ctx, uint32_t size, const std::string name)
  : ioimpl(ctx, size, name) {}

bool inputimpl::ready() const {
  return m_bridge->ready();
}

bool inputimpl::valid() const {
  return m_bridge->valid();
}

const bitvector& inputimpl::eval(ch_cycle t) {
  return m_bridge->eval(t);
}

///////////////////////////////////////////////////////////////////////////////

outputimpl::outputimpl(const ch_node& src, const std::string name) 
  : ioimpl(src.get_ctx(), src.get_size(), name) {
  m_srcs.reserve(1);
  m_srcs.emplace_back(src);
}

const bitvector& outputimpl::eval(ch_cycle t) {
  return m_srcs[0].eval(t);
}

///////////////////////////////////////////////////////////////////////////////

void ibridge::detach() {
  m_impl = nullptr;
  refcounted::release();
}

const bitvector& ibridge::eval(ch_cycle t) {
  assert(m_impl);
  return m_impl->eval(t);
}

bool ibridge::ready() const {
  return m_impl->ready();
}

bool ibridge::valid() const {
  return m_impl->valid();
}

///////////////////////////////////////////////////////////////////////////////

void obridge::detach() {
  m_impl = nullptr;
  refcounted::release();
}

const bitvector& obridge::eval(ch_cycle t) {
  assert(m_impl);
  return m_impl->eval(t);
}

bool obridge::ready() const  {
  return m_impl->ready();
}

bool obridge::valid() const  {
  return m_impl->valid();
}
