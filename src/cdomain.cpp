#include "cdomain.h"
#include "ioimpl.h"
#include "litimpl.h"
#include "context.h"

using namespace std;
using namespace cash::detail;

clock_event::clock_event()
  : edgedir_(EDGE_POS)
  , cval_(false)
{}

clock_event::clock_event(lnodeimpl* signal, EDGE_DIR edgedir)
  : signal_(signal)
  , edgedir_(edgedir)
  , cval_(false) 
{}

clock_event::~clock_event() {
  //--
}

bool clock_event::eval(ch_cycle t) {
  bool value = signal_.eval(t)[0];
  if (cval_ != value) {
    cval_ = value;
    return (value  && (edgedir_ == EDGE_POS || edgedir_ == EDGE_ANY)) ||
           (!value && (edgedir_ == EDGE_NEG || edgedir_ == EDGE_ANY));
  }
  return false;
}

void clock_event::print_vl(ostream& out) const {
  switch (edgedir_) {
  case EDGE_POS:
    out << "posedge ";
    break;
  case EDGE_NEG:
    out << "negedge ";
    break;  
  case EDGE_ANY:
    // do nothing
    break;
  }
  out << "__x" << signal_.get_id();
}

///////////////////////////////////////////////////////////////////////////////

cdomain::cdomain(context* ctx, const std::vector<clock_event>& sensitivity_list)
  : ctx_(ctx) {
  sensitivity_list_.reserve(sensitivity_list.size());
  for (const clock_event& e : sensitivity_list) {
    // constants are omitted by default
    if (dynamic_cast<litimpl*>(e.get_signal())) {
      continue;
    }
    // ensure unique signals
    auto it = std::find(sensitivity_list_.begin(), sensitivity_list_.end(), e.get_signal());
    CH_CHECK(it == sensitivity_list_.end(), "a duplicate signal event provided");    
    sensitivity_list_.emplace_back(e);
  }
} 

cdomain::~cdomain() {
  ctx_->remove_cdomain(this);
}

void cdomain::add_use(tickable* reg) {
  regs_.emplace_back(reg);
  this->acquire();
}

void cdomain::remove_use(tickable* reg) {
  regs_.remove(reg);
  this->release();
}

bool cdomain::operator==(const std::vector<clock_event>& events) const {
  if (events.size() != sensitivity_list_.size())
    return false;
  for (const clock_event& e1 : sensitivity_list_) {
    bool found = false;
    for (const clock_event& e2 : events) {
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
  for (clock_event& event : sensitivity_list_) {
    if (event.eval(t)) {
      for (tickable* reg : regs_)
        reg->tick(t);
      return;
    }
  }
}

void cdomain::tick_next(ch_cycle t) {
  for (auto reg : regs_) {
    reg->tick_next(t);
  }
}

void cdomain::print_vl(ostream& out) const {
  bool first_event = true;
  for (const clock_event& event : sensitivity_list_) {
    if (first_event)
      first_event = false;
    else
      out << ", ";
    event.print_vl(out);
  }
}
