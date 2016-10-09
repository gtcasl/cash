#include "ioimpl.h"
#include "snodeimpl.h"
#include "context.h"

using namespace std;
using namespace chdl_internal;

inputimpl::inputimpl(const std::string& name, uint32_t index, context* ctx, uint32_t size) 
  : ioimpl(name, ctx, size)
  , m_bus(nullptr)
  , m_index(index)
{}

inputimpl::~inputimpl() {
  if (m_bus)
    m_bus->release();
}

void inputimpl::bind(snodeimpl* bus) {
  bus->acquire();
  if (m_bus)
    m_bus->release();
  m_bus = bus;
}

const bitvector& inputimpl::eval(ch_cycle t) {
  return m_bus->eval(t);
}

void inputimpl::print(std::ostream& out) const {
  out << "#" << m_id << " <- " << m_name << m_value.get_size();
  out << "(" << m_index << ", " << "$" << m_bus->get_id() << ")";
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
  out << "(" << m_index << ", " << "#" << m_srcs[0].get_id() << ")";
  out << endl;
}

///////////////////////////////////////////////////////////////////////////////

tapimpl::tapimpl(const std::string& name, const lnode& src) 
  : ioimpl("tap", src.get_ctx(), src.get_size())
  , m_tapName(name) {
  m_srcs.reserve(1);
  m_srcs.emplace_back(src);
}

void tapimpl::print(std::ostream& out) const {
  out << "#" << m_id << " <- " << m_name << m_value.get_size();
  out << "(" << m_tapName << ", " << "#" << m_srcs[0].get_id() << ")";
  out << endl;
}

const bitvector& tapimpl::eval(ch_cycle t) {
  return m_srcs[0].eval(t);
}
