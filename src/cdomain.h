#pragma once

#include "lnodeimpl.h"
#include "tickable.h"

namespace cash {
namespace detail {

enum EDGE_DIR {
  EDGE_POS = 0,
  EDGE_NEG = 1,
  EDGE_ANY = 2,
};

class clock_event {
public:  
  clock_event();
  clock_event(const lnode& signal, EDGE_DIR edgedir);
  ~clock_event();
  
  const lnode& get_signal() const {
    return signal_;
  }
  
  EDGE_DIR get_edgedir() const {
    return edgedir_;
  }
  
  bool operator==(const lnode& signal) const {
    return (signal_.get_id() == signal.get_id());
  }
  
  bool operator==(const clock_event& e) const {
    return (signal_.get_id() == e.signal_.get_id()) && 
           (edgedir_ == e.edgedir_);
  }
  
  bool eval(ch_cycle t);
  
  void print_vl(std::ostream& out) const;
  
protected:
  lnode    signal_;
  EDGE_DIR edgedir_;
  bool     cval_; 
};

///////////////////////////////////////////////////////////////////////////////

class cdomain : public refcounted {
public:
  cdomain(context* ctx, const std::vector<clock_event>& sensitivity_list);
  
  void add_use(tickable* reg);
  void remove_use(tickable* reg);
  
  const std::vector<clock_event>& get_sensitivity_list() const {
    return sensitivity_list_;
  }
  
  context* get_ctx() const {
    return ctx_;
  }
  
  void tick(ch_cycle t);
  void tick_next(ch_cycle t);
  
  bool operator==(const std::vector<clock_event>& events) const;
  
  void print_vl(std::ostream& out) const;

protected:
  
  ~cdomain();
  
  std::vector<clock_event> sensitivity_list_;
  std::list<tickable*> regs_;
  context* ctx_;
};

}
}
