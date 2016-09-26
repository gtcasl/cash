#pragma once

#include "nodeimpl.h"
#include "tickable.h"
#include "cdomain.h"

namespace chdl_internal {

class regimpl : public tickable, public nodeimpl {
public:
  regimpl(const ch_node& next);
  virtual ~regimpl();
  
  const bitvector& eval(ch_cycle t) override;  
  void print_vl(std::ostream& out) const override;

  void tick(ch_cycle t) override;
  void tick_next(ch_cycle t) override;
  
protected:

  cdomain* m_cd;
  bitvector m_q;
  bitvector m_next_q;
  ch_cycle m_ctime;
};

class latchimpl : public tickable, public nodeimpl {
public:
  latchimpl(
      const ch_node& next,
      const ch_node& init,
      const ch_node& enable,      
      const ch_node& reset
  );
  virtual ~latchimpl();
  
  const bitvector& eval(ch_cycle t) override;  
  void print_vl(std::ostream& out) const override;

  void tick(ch_cycle t) override;
  void tick_next(ch_cycle t) override;
  
protected:

  cdomain* m_cd;
  bitvector m_q;
  ch_cycle m_ctime;
};

}
