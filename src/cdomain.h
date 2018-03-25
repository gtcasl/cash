#pragma once

#include "lnodeimpl.h"
#include "tickable.h"

namespace ch {
namespace internal {

class clock_event {
public:  
  clock_event();
  clock_event(const lnode& signal, bool pos_edge);
  ~clock_event();
  
  const lnode& get_signal() const {
    return signal_;
  }
  
  bool is_pos_edge() const {
    return pos_edge_;
  }
  
  bool operator==(const lnode& signal) const {
    return (signal_.get_id() == signal.get_id());
  }
  
  bool operator==(const clock_event& e) const {
    return (signal_.get_id() == e.signal_.get_id())
        && (pos_edge_ == e.pos_edge_);
  }
  
  bool eval(ch_tick t);
  
protected:

  lnode signal_;
  bool  pos_edge_;
  bool  cval_;
};

///////////////////////////////////////////////////////////////////////////////

class cdomain : public refcounted {
public:
  cdomain(context* ctx, const std::vector<clock_event>& sensitivity_list);

  const std::vector<clock_event>& get_sensitivity_list() const {
    return sensitivity_list_;
  }
  
  context* get_ctx() const {
    return ctx_;
  }

  bool operator==(const std::vector<clock_event>& events) const;

  void add_use(tickable* reg);

  void remove_use(tickable* reg);

  void tick(ch_tick t);

  void tick_next(ch_tick t);

protected:
  
  ~cdomain();
  
  std::vector<clock_event> sensitivity_list_;
  std::list<tickable*> regs_;
  context* ctx_;
};

}
}
