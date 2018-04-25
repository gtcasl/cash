#include "simulatorimpl.h"
#include "simulator.h"
#include "deviceimpl.h"
#include "litimpl.h"
#include "ioimpl.h"

using namespace ch::internal;

void clock_driver::add_signal(lnodeimpl* node) {
  node->get_value()[0] = value_;
  nodes_.push_back(node);
}

void clock_driver::flip() {
  value_ = !value_;
  for (auto node : nodes_) {
    node->get_value()[0] = value_;
  }
}

///////////////////////////////////////////////////////////////////////////////

simulatorimpl::simulatorimpl(const std::initializer_list<context*>& contexts)
  : initialized_(false) {
  for (auto ctx : contexts) {
    auto ret = contexts_.emplace(ctx);
    if (ret.second) {
      ctx->acquire();
    }
  }
}

simulatorimpl::~simulatorimpl() {
  for (auto ctx : contexts_) {
    ctx->release();
  }
}

void simulatorimpl::add_device(const device& device) {
  auto ctx = get_ctx(device);
  auto ret = contexts_.emplace(ctx);
  if (ret.second) {
    ctx->acquire();
  }
}

void simulatorimpl::ensureInitialize() {
  // bind default clocks to clock driver
  for (auto ctx : contexts_) {
    auto clk = ctx->get_default_clk();
    if (clk) {
      clk_driver_.add_signal(clk);
    }
    auto reset = ctx->get_default_reset();
    if (reset) {
      reset_driver_.add_signal(reset);
    }
  }
}

void simulatorimpl::tick(ch_tick t) {
  // ensure initialized
  if (!initialized_) {
    this->ensureInitialize();
    initialized_ = true;
  }

  // evaluate all contexts

  for (auto ctx : contexts_) {
    ctx->tick(t);
  }

  for (auto ctx : contexts_) {
    ctx->tick_next(t);
  }

  for (auto ctx : contexts_) {
    ctx->eval(t);
  #ifndef NDEBUG
    int dump_ast_level = platform::self().get_dump_ast();
    if (2 == dump_ast_level) {
      std::cerr << "tick " << t << ":" << std::endl;
      ctx->dump_ast(std::cerr, 2);
    }
  #endif
  }
}

ch_tick simulatorimpl::reset(ch_tick t) {
  // ensure initialized
  if (!initialized_) {
    this->ensureInitialize();
    initialized_ = true;
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
      this->tick(t++);
      clk_driver_.flip();
    }
  } else {
    this->tick(t++);
  }
  return t;
}

ch_tick simulatorimpl::step(ch_tick t, unsigned count) {
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

void ch_simulator::add_device(const device& device) {
  impl_->add_device(device);
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

ch_tick ch_simulator::step(ch_tick t, unsigned count) {
  return impl_->step(t, count);
}
