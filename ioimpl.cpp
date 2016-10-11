#include "ioimpl.h"
#include "snodeimpl.h"
#include "context.h"

using namespace std;
using namespace chdl_internal;

inputimpl::inputimpl(const std::string& name, context* ctx, uint32_t size) 
  : ioimpl(name, ctx, size)
  , m_bus(nullptr)
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
  assert(m_bus);
  return m_bus->read();
}

void inputimpl::print(std::ostream& out) const {
  out << "#" << m_id << " <- " << m_name << m_value.get_size() << "("; 
  if (m_bus) {
    out << "$" << m_bus->get_id();
  } else {
    out << "?";
  }
  out << ")" << endl;
}

///////////////////////////////////////////////////////////////////////////////

outputimpl::outputimpl(const std::string& name, const lnode& src) 
  : ioimpl(name, src.get_ctx(), src.get_size())
  , m_bus(nullptr) {
  m_srcs.reserve(1);
  m_srcs.emplace_back(src);
}

outputimpl::~outputimpl() {
  if (m_bus)
    m_bus->release();
}

const bitvector& outputimpl::eval(ch_cycle t) {
  const bitvector& bits = m_srcs[0].eval(t);
  if (m_bus)
    m_bus->write(bits);
  return bits;
}

snodeimpl* outputimpl::get_bus() {
  if (m_bus == nullptr) {
    m_bus = new snodeimpl(m_value.get_size());
    m_bus->acquire();
  }
  return m_bus;
}

void outputimpl::print(std::ostream& out) const {
  out << "#" << m_id << " <- " << m_name << m_value.get_size();
  out << "(" << "#" << m_srcs[0].get_id() << ")";
  out << endl;
}

///////////////////////////////////////////////////////////////////////////////

tapimpl::tapimpl(const std::string& name, const lnode& src) 
  : outputimpl("tap", src)
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
