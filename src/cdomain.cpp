#include "cdomain.h"
#include "ioimpl.h"
#include "litimpl.h"
#include "context.h"

using namespace ch::internal;

clock_event::clock_event()
  : pos_edge_(false)
  , cval_(false)
{}

clock_event::clock_event(const lnode& signal, bool pos_edge)
  : signal_(signal)
  , pos_edge_(pos_edge)
  , cval_(false) {
  assert(1 == signal.get_size());
}

clock_event::~clock_event() {
  //--
}

bool clock_event::eval(ch_tick t) {
  bool value = signal_.eval(t)[0];
  if (cval_ != value) {
    cval_ = value;
    return (value && pos_edge_) || (!value && !pos_edge_);
  }
  return false;
}

///////////////////////////////////////////////////////////////////////////////

cdomain::cdomain(context* ctx, const std::vector<clock_event>& sensitivity_list)
  : ctx_(ctx) {
  sensitivity_list_.reserve(sensitivity_list.size());
  for (auto& e : sensitivity_list) {
    // ensure unique signals
    auto it = std::find(sensitivity_list_.begin(), sensitivity_list_.end(), e.get_signal());
    CH_CHECK(it == sensitivity_list_.end(), "a duplicate clock event provided");
    sensitivity_list_.emplace_back(e);
  }
} 

cdomain::~cdomain() {
  ctx_->remove_cdomain(this);
}

bool cdomain::operator==(const std::vector<clock_event>& events) const {
  if (events.size() != sensitivity_list_.size())
    return false;
  for (auto& e1 : sensitivity_list_) {
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

void cdomain::add_use(tickable* reg) {
  regs_.emplace_back(reg);
  this->acquire();
}

void cdomain::remove_use(tickable* reg) {
  regs_.remove(reg);
  this->release();
}

void cdomain::tick(ch_tick t) {
  for (clock_event& event : sensitivity_list_) {
    if (event.eval(t)) {
      for (auto reg : regs_) {
        reg->tick(t);
      }
      return;
    }
  }
}

void cdomain::tick_next(ch_tick t) {
  for (auto reg : regs_) {
    reg->tick_next(t);
  }
}
