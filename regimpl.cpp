#include "regimpl.h"
#include "context.h"

using namespace std;
using namespace chdl_internal;

/*regimpl::regimpl(context* ctx,
                 cdomain* cd,
                 const node& next,
                 const node* enable,
                 const node* init,
                 const node* reset)
  : nodeimpl(ctx)
  , m_reset(-1)
  , m_enable(-1)
  , m_init(-1)
  , m_next(-1)
  , m_q(0)
  , m_next_q(0)
  , m_ctime(~0ull)
{
  m_cd = cd;
  cd->add_use(this);

  m_next = m_srcs.size();
  m_srcs.emplace_back(next);

  if (reset) {
    m_reset = m_srcs.size();
    m_srcs.emplace_back(*reset);

    m_init = m_srcs.size();
    if (init) {      
      m_srcs.emplace_back(*init);
    } else {
      node l0((nodeimpl*)ctx->get_lit(false));
      m_srcs.emplace_back(l0);
    }
  }

  if (enable) {
    m_enable = m_srcs.size();
    m_srcs.emplace_back(*enable);
  }  
  
  // add source dependencies to clock signals
  auto& sensitivity_list = m_cd->get_sensitivity_list();
  for (auto& e : sensitivity_list) {
    const node& signal = e.get_signal();
    if ((reset && reset->get_id() == signal.get_id()) ||
        (enable && enable->get_id() == signal.get_id())) {
      continue; // skip
    }
    m_srcs.emplace_back(signal);
  }
}*/

regimpl::~regimpl() {
  m_cd->remove_use(this);
}

const bitvector& regimpl::eval(ch_cycle t) {
  return m_q; 
}

void regimpl::print(ostream& out) const {
  //out << "  reg " << m_srcs[m_next] << ' ' << m_id << endl;
}

void regimpl::print_vl(ostream& out) const {
  /*out << "  always @ (";
  m_cd->print_vl(out);
  out << ")" << endl
      << "    begin" << endl;
  if (m_reset != -1) {
    out << "      if (__x" <<  m_srcs[m_reset].get_id() << ")" << endl
        << "        __x" << m_id << " <= " << "__x" << m_srcs[m_init] << ';' << endl;
    if (m_enable != -1) {
      out << "      else if (__x" <<  m_srcs[m_enable].get_id() << ")" << endl
          << "        __x" << m_id << " <= " << "__x" << m_srcs[m_next] << ';' << endl;
    } else {
      out << "      else" << endl
          << "        __x" << m_id << " <= " << "__x" << m_srcs[m_next] << ';' << endl;
    }
  } else 
  if (m_enable != -1) {
    out << "      if (__x" <<  m_srcs[m_enable].get_id() << ")" << endl
        << "        __x" << m_id << " <= " << "__x" << m_srcs[m_next] << ';' << endl;
  } else {  
    out << "      __x" << m_id << " <= " << "__x" << m_srcs[m_next] << ';' << endl;
  }
  out << "    end" << endl;*/
}

void regimpl::tick(ch_cycle t) { 
  m_q = m_next_q;
}

void regimpl::tick_next(ch_cycle t) {
  /*if (m_reset != -1 &&
      m_srcs[m_reset].eval(t)) {
    assert(m_init != -1);
    m_next_q = m_srcs[m_init].eval(t);
    m_q = m_next_q;
  } else   
  if (m_enable != -1) {
    if (m_srcs[m_enable].eval(t)) {
      m_next_q = m_srcs[m_next].eval(t);
      m_q = m_next_q;
    }
  } else {
    m_next_q = m_srcs[m_next].eval(t);
  }*/
}
