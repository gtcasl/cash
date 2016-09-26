#include "busimpl.h"
#include "ioimpl.h"

using namespace std;
using namespace chdl_internal;

busimpl::busimpl(uint32_t size) 
  : m_value(size)
  , m_obridge(nullptr)
  , m_ctime(~0ull) {
  //--
}

busimpl::~busimpl() {
  for (auto& b : m_bridges) {
    b.second->detach();
  }
}

void busimpl::bind(context* ctx, unsigned index, iobridge* bridge) {
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

void busimpl::bind(busimpl* src) {
  if (src->m_obridge == nullptr)
    CHDL_ABORT("source not valid!");
  
  // get src portid
  const portid_t* portid = src->get_portid(src->m_obridge);
  assert(portid != nullptr);

  // apply binding
  this->bind(portid->ctx, portid->idx, src->m_obridge);
}

bool busimpl::ready() const {
  if (m_obridge)
    return m_obridge->ready();  
  return true;
}

bool busimpl::valid() const {
  if (m_obridge)
    return m_obridge->valid();
  return true;
}

const bitvector& busimpl::eval(ch_cycle t) {
  if (m_obridge && m_ctime != t) {
    m_ctime = t;
    m_value = m_obridge->eval(t);
  }
  return m_value;
}

const busimpl::portid_t* busimpl::get_portid(iobridge* bridge) const {
  auto iter = std::find_if(m_bridges.begin(), m_bridges.end(),
    [bridge](const bridges_t::value_type& v)->bool { return v.second == bridge; });
  if (iter == m_bridges.end())
    return nullptr;
  return &iter->first;
}

void busimpl::get_bindings(std::set<context*>& bindings) const {
  for (auto& p : m_bridges) {
    bindings.emplace(p.first.ctx);
  }
}
