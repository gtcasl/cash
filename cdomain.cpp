#include "cdomain.h"
#include "ioimpl.h"
#include "litimpl.h"
#include "context.h"

using namespace std;
using namespace chdl_internal;

clock_event::clock_event(const ch_node& node, EDGE_DIR edgedir)
  : m_node(node)
  , m_edgedir(edgedir)
  , m_cval(false) 
{}

clock_event::~clock_event() {
  //--
}

bool clock_event::eval(ch_cycle t) {
  bool value = m_node.eval(t).get_bit(0);
  if (m_cval != value) {
    m_cval = value;
    return (value  && (m_edgedir == EDGE_POS || m_edgedir == EDGE_ANY)) ||
           (!value && (m_edgedir == EDGE_NEG || m_edgedir == EDGE_ANY));
  }
  return false;
}

void clock_event::print_vl(ostream& out) const {
  switch (m_edgedir) {
  case EDGE_POS:
    out << "posedge ";
    break;
  case EDGE_NEG:
    out << "negedge ";
    break;
  }
  out << "__x" << m_node.get_id();
}

///////////////////////////////////////////////////////////////////////////////

cdomain::cdomain(context* ctx, const std::vector<clock_event>& sensitivity_list)
  : m_ctx(ctx) {
  m_sensitivity_list.reserve(sensitivity_list.size());
  for (auto& e : sensitivity_list) {
    assert(get_impl<undefimpl>(e.get_signal()) == nullptr);
    // constants are omitted by default
    if (get_impl<litimpl>(e.get_signal())) {
      continue;
    }
    // ensure unique signals
    auto it = std::find(m_sensitivity_list.begin(), m_sensitivity_list.end(), e.get_signal());
    if (it != m_sensitivity_list.end())
      CHDL_ABORT("a duplicate signal event provided");    
    m_sensitivity_list.emplace_back(e);
  }
} 

cdomain::~cdomain() {
  m_ctx->cdomains.remove(this);
}

void cdomain::add_use(tickable* reg) {
  this->add_ref();
  m_regs.emplace_back(reg);
}

void cdomain::remove_use(tickable* reg) {
  m_regs.remove(reg);
  this->release();
}

bool cdomain::operator==(const std::vector<clock_event>& events) const {
  if (events.size() != m_sensitivity_list.size())
    return false;
  for (auto& e1 : m_sensitivity_list) {
    bool found = false;
    for (auto& e2 : events) {
      if (e1 == e2) {
        found = true;
        break;
      }
    }
    if (!found)
      return false;
  }
  return true;
}

void cdomain::tick(ch_cycle t) {
  for (auto& event : m_sensitivity_list) {
    if (event.eval(t)) {
      for (auto reg : m_regs)
        reg->tick(t);
      return;
    }
  }
}

void cdomain::tick_next(ch_cycle t) {
  for (auto reg : m_regs) {
    reg->tick_next(t);
  }
}

void cdomain::print_vl(ostream& out) const {
  bool first_event = true;
  for (auto& event : m_sensitivity_list) {
    if (first_event)
      first_event = false;
    else
      out << ", ";
    event.print_vl(out);
  }
}
