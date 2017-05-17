#pragma once

#include "lnodeimpl.h"
#include "tickable.h"
#include "cdomain.h"

namespace cash_internal {

class regimpl : public tickable, public lnodeimpl {
public:
  regimpl(lnodeimpl* next);
  virtual ~regimpl();
  
  const lnode& get_next() const {
    return srcs_[0];
  }
  
  const bitvector& eval(ch_cycle t) override;  
  void print_vl(std::ostream& out) const override;

  void tick(ch_cycle t) override;
  void tick_next(ch_cycle t) override;
  
protected:

  cdomain*  cd_;
  bitvector q_next_;
};

class latchimpl : public tickable, public lnodeimpl {
public:
  latchimpl(
      lnodeimpl* next,
      lnodeimpl* init,
      lnodeimpl* enable,      
      lnodeimpl* reset
  );
  virtual ~latchimpl();
  
  const bitvector& eval(ch_cycle t) override;  
  void print_vl(std::ostream& out) const override;

  void tick(ch_cycle t) override;
  void tick_next(ch_cycle t) override;
  
protected:

  cdomain* cd_;
};

}
