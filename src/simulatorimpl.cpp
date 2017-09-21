#include "simulatorimpl.h"
#include "simulator.h"
#include "deviceimpl.h"
#include "ioimpl.h"

using namespace cash::internal;

simulatorimpl::simulatorimpl(const std::initializer_list<const ch_device*>& devices)
  : initialized_(false)
  , clk_(nullptr)
  , reset_(nullptr) {
  for (auto device : devices) {
    context* ctx = device->impl_->get_ctx();
    auto ret = contexts_.emplace(ctx);
    if (ret.second)
      ctx->acquire();
  }
}

simulatorimpl::~simulatorimpl() {
  if (clk_)
    clk_->release();
  if (reset_)
    reset_->release();
  for (auto ctx : contexts_) {
    ctx->release();
  }
}

void simulatorimpl::add_device(const ch_device& device) {
  context* ctx = device.impl_->get_ctx();
  auto ret = contexts_.emplace(ctx);
  if (ret.second) {
    ctx->acquire();
  }
}

void simulatorimpl::ensureInitialize() {
  // bind context taps
  for (auto ctx : contexts_) {
    if (ctx->clk_) {
      if (nullptr == clk_) {
        clk_ = new snodeimpl(1);
        clk_->acquire();
        clk_->set_bit(0, true); // set 'high' by default
      }
      ctx->clk_->bind(clk_);
    }

    if (ctx->reset_) {
      if (nullptr == reset_) {
        reset_ = new snodeimpl(1);
        reset_->acquire();
      }
      ctx->reset_->bind(reset_);
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

void simulatorimpl::run(const std::function<bool(ch_tick t)>& callback) {
  ch_tick start = this->reset(0);
  for (ch_tick t = start; callback(t - start);) {
    t = this->step(t);
  }
}

void simulatorimpl::run(ch_tick ticks) {
  ch_tick t = this->reset(0);
  for (; t < ticks;) {
    t = this->step(t);
  }
}

ch_tick simulatorimpl::reset(ch_tick t) {
  // ensure initialized
  if (!initialized_) {
    this->ensureInitialize();
    initialized_ = true;
  }

  if (reset_) {
    reset_->set_bit(0, true);
    t = this->step(t);
    reset_->set_bit(0, false);
  }

  return t;
}

ch_tick simulatorimpl::step(ch_tick t) {
  if (clk_) {
    for (int i = 0; i < 2; ++i) {
      clk_->set_bit(0, !clk_->get_bit(0));
      this->tick(t++);
    }
  } else {
    this->tick(t++);
  }
  return t;
}

///////////////////////////////////////////////////////////////////////////////

ch_simulator::ch_simulator(const std::initializer_list<const ch_device*>& devices) {
  impl_ = new simulatorimpl(devices);
  impl_->acquire();
}

ch_simulator::ch_simulator(simulatorimpl* impl) : impl_(impl) {
  if (impl)
    impl->acquire();
}

ch_simulator::ch_simulator(const ch_simulator& simulator) : impl_(simulator.impl_) {
  if (impl_)
    impl_->acquire();
}

ch_simulator::~ch_simulator() {
  if (impl_)
    impl_->release();
}

ch_simulator& ch_simulator::operator=(const ch_simulator& simulator) {
  if (simulator.impl_)
    simulator.impl_->acquire();
  if (impl_)
    impl_->release();
  impl_ = simulator.impl_;
  return *this;
}

void ch_simulator::add_device(const ch_device& device) {
  impl_->add_device(device);
}

void ch_simulator::tick(ch_tick t) { 
  impl_->tick(t);
}

void ch_simulator::run(const std::function<bool(ch_tick t)>& callback) {
  impl_->run(callback);
}

void ch_simulator::run(ch_tick ticks) {
  impl_->run(ticks);
}

ch_tick ch_simulator::reset(ch_tick t) {
  return impl_->reset(t);
}

ch_tick ch_simulator::step(ch_tick t) {
  return impl_->step(t);
}
