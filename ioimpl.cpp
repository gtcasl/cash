#include "ioimpl.h"
#include "snodeimpl.h"
#include "context.h"

using namespace std;
using namespace chdl_internal;

ioimpl::ioimpl(const std::string& name, context* ctx, uint32_t size)
  : lnodeimpl(name, ctx, size)  
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

inputimpl::inputimpl(const std::string& name, uint32_t index, context* ctx, uint32_t size) 
  : ioimpl(name, ctx, size)
  , m_index(index){}

bool inputimpl::ready() const {
  return m_bridge->ready();
}

bool inputimpl::valid() const {
  return m_bridge->valid();
}

const bitvector& inputimpl::eval(ch_cycle t) {
  return m_bridge->eval(t);
}

void inputimpl::print(std::ostream& out) const {
  out << "#" << m_id << " <- " << m_name << m_value.get_size();
  if (m_index != -1)
    out << "(" << m_index << ")";
  out << endl;
}

///////////////////////////////////////////////////////////////////////////////

outputimpl::outputimpl(const std::string& name, uint32_t index, const lnode& src) 
  : ioimpl(name, src.get_ctx(), src.get_size())
  , m_index(index) {
  m_srcs.reserve(1);
  m_srcs.emplace_back(src);
}

const bitvector& outputimpl::eval(ch_cycle t) {
  return m_srcs[0].eval(t);
}

void outputimpl::print(std::ostream& out) const {
  out << "#" << m_id << " <- " << m_name << m_value.get_size();
  if (m_index != -1)
    out << "(" << m_index << ")";
  out << endl;
}

///////////////////////////////////////////////////////////////////////////////

tapimpl::tapimpl(const std::string& name, const lnode& src) 
  : ioimpl("tap", src.get_ctx(), src.get_size())
  , m_tapName(name) {
  m_srcs.reserve(1);
  m_srcs.emplace_back(src);
}

const bitvector& tapimpl::eval(ch_cycle t) {
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
