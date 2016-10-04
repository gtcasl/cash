#include "selectimpl.h"
#include "select.h"

using namespace std;
using namespace chdl_internal;

selectimpl::selectimpl(const lnode& test, const lnode& a, const lnode& b) 
  : lnodeimpl("select", a.get_ctx(), a.get_size()), m_ctime(~0ull) {
  m_srcs.emplace_back(test);
  m_srcs.emplace_back(a);
  m_srcs.emplace_back(b);
}

const bitvector& selectimpl::eval(ch_cycle t) {
  if (m_ctime != t) {
    m_ctime = t;
    m_value = m_srcs[0].eval(t)[0] ? m_srcs[1].eval(t) : m_srcs[2].eval(t);
  }
  return m_value;
}

void selectimpl::print_vl(std::ostream& out) const {
  TODO();
}

lnode chdl_internal::createSelectNode(const lnode& test, const lnode& a, const lnode& b) {
  return lnode(new selectimpl(test, a, b));
}
