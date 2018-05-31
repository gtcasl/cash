#include "simulatorimpl.h"
#include "simulator.h"
#include "deviceimpl.h"
#include "litimpl.h"
#include "ioimpl.h"
#include "cdimpl.h"

using namespace ch::internal;

void clock_driver::add_signal(lnodeimpl* node) {
  node->value()[0] = value_;
  nodes_.push_back(node);
}

void clock_driver::flip() {
  value_ = !value_;
  for (auto node : nodes_) {
    node->value()[0] = value_;
  }
}

///////////////////////////////////////////////////////////////////////////////

simulatorimpl::simulatorimpl(const std::initializer_list<context*>& contexts)
  : clk_driver_(true)
  , reset_driver_(false) {
  // enqueue all contexts
  for (auto ctx : contexts) {
    auto ret = contexts_.emplace(ctx);
    if (ret.second) {
      ctx->acquire();
    }
  }
  // initialize
  this->initialize();
}

simulatorimpl::~simulatorimpl() {
  for (auto ctx : contexts_) {
    ctx->release();
  }
}

void simulatorimpl::initialize() {
  // bind default clocks to clock driver
  for (auto ctx : contexts_) {
    auto clk = ctx->default_clk();
    if (clk) {
      clk_driver_.add_signal(clk);
    }
    auto reset = ctx->default_reset();
    if (reset) {
      reset_driver_.add_signal(reset);
    }
  }

  // build run list
  for (auto ctx : contexts_) {
    ctx->build_run_list(run_list_);
  }

  // initialize all nodes
  for (auto node : run_list_) {
    node->initialize();
  }
}

void simulatorimpl::tick(ch_tick) {
  // evaluate all nodes
  for (auto node : run_list_) {
    node->eval();
  }
}

ch_tick simulatorimpl::reset(ch_tick t) {
  // reset all contexts
  for (auto node : run_list_) {
    node->reset();
  }

  // reset signal
  if (!reset_driver_.empty()) {
    reset_driver_.flip();
    t = this->step(t);
    reset_driver_.flip();
  }

  return t;
}

ch_tick simulatorimpl::step(ch_tick t) {
  if (!clk_driver_.empty()) {
    for (int i = 0; i < 2; ++i) {
      clk_driver_.flip();
      this->tick(t++);
    }
  } else {
    this->tick(t++);
  }
  return t;
}

ch_tick simulatorimpl::step(ch_tick t, uint32_t count) {
  while (count--) {
    t = this->step(t);
  }
  return t;
}

ch_tick simulatorimpl::run(const std::function<bool(ch_tick t)>& callback) {
  auto t = this->reset(0);
  for (auto start = t; callback(t - start);) {
    t = this->step(t);
  }
  return t;
}

void simulatorimpl::run(ch_tick ticks) {
  for (auto t = this->reset(0); t < ticks;) {
    t = this->step(t);
  }
}

///////////////////////////////////////////////////////////////////////////////

ch_simulator::ch_simulator(const std::initializer_list<context*>& contexts) {
  impl_ = new simulatorimpl(contexts);
  impl_->acquire();
}

ch_simulator::ch_simulator(simulatorimpl* impl) : impl_(impl) {
  if (impl) {
    impl->acquire();
  }
}

ch_simulator::ch_simulator(const ch_simulator& simulator) : impl_(simulator.impl_) {
  if (impl_) {
    impl_->acquire();
  }
}

ch_simulator::~ch_simulator() {
  if (impl_) {
    impl_->release();
  }
}

ch_simulator& ch_simulator::operator=(const ch_simulator& simulator) {
  if (simulator.impl_) {
    simulator.impl_->acquire();
  }
  if (impl_) {
    impl_->release();
  }
  impl_ = simulator.impl_;
  return *this;
}

ch_tick ch_simulator::run(const std::function<bool(ch_tick t)>& callback) {
  return impl_->run(callback);
}

void ch_simulator::run(ch_tick ticks) {
  impl_->run(ticks);
}

ch_tick ch_simulator::reset(ch_tick t) {
  return impl_->reset(t);
}

ch_tick ch_simulator::step(ch_tick t, uint32_t count) {
  return impl_->step(t, count);
}
