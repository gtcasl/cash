#pragma once

#include "nodeimpl.h"
#include "tickable.h"
#include "cdomain.h"

namespace chdl_internal {

class regimpl : public tickable, public nodeimpl {
public:
  regimpl(
      context* ctx,
      cdomain* cd,
      const ch_node& next,
      const ch_node* enable = nullptr,
      const ch_node* init = nullptr,
      const ch_node* reset = nullptr
  );
  virtual ~regimpl();

  const bitvector& eval(ch_cycle t) override;
  void print(std::ostream& out) const override;
  void print_vl(std::ostream& out) const override;

  void tick(ch_cycle t);
  void tick_next(ch_cycle t);
  
protected:

  cdomain* m_cd;
  int  m_reset;
  int  m_enable;
  int  m_init;
  int  m_next;
  bitvector m_q;
  bitvector m_next_q;
  ch_cycle m_ctime;
};

}
