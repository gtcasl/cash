#include "selectimpl.h"
#include "select.h"

using namespace std;
using namespace chdl_internal;

selectimpl::selectimpl(const ch_node& test, const ch_node& a, const ch_node& b) 
  : nodeimpl(a.get_ctx(), a.get_size()), m_ctime(~0ull) {
  m_srcs.emplace_back(test);
  m_srcs.emplace_back(a);
  m_srcs.emplace_back(b);
}

const bitvector& selectimpl::eval(ch_cycle t) {
  if (m_ctime != t) {
    m_ctime = t;
    m_value = m_srcs[0].eval(t).get_bit(0) ? m_srcs[1].eval(t) : m_srcs[2].eval(t);
  }
  return m_value;
}

void selectimpl::print(std::ostream& out) const {
  TODO();
}

void selectimpl::print_vl(std::ostream& out) const {
  TODO();
}

ch_node chdl_internal::createSelectNode(const ch_node& test, const ch_node& a, const ch_node& b) {
  
}
