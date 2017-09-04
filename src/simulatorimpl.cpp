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
  if (ret.second)
    ctx->acquire();
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

void simulatorimpl::tick(ch_cycle t) {
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
      std::cerr << "cycle " << t << ":" << std::endl;
      ctx->dump_ast(std::cerr, 2);
    }
  #endif
  }
}

void simulatorimpl::run(const std::function<bool(ch_cycle time)>& callback) {
  ch_cycle start = this->reset(0);
  for (ch_cycle time = start; callback(time - start); ++time) {
    this->step(time);
  }
}

void simulatorimpl::run(ch_cycle cycles) {
  ch_cycle time = this->reset(0);
  for (; time < cycles; ++time) {
    this->step(time);
  }
}

ch_cycle simulatorimpl::reset(ch_cycle t) {
  // ensure initialized
  if (!initialized_) {
    this->ensureInitialize();
    initialized_ = true;
  }

  if (reset_) {
    reset_->set_bit(0, true);
    this->step(t++);
    reset_->set_bit(0, false);
  }

  return t;
}

void simulatorimpl::step(ch_cycle t) {
  if (clk_) {
    for (int i = 0; i < 2; ++i) {
      clk_->set_bit(0, !clk_->get_bit(0));
      this->tick(t * 2 + i);
    }
  } else {
    this->tick(t);
  }
}

///////////////////////////////////////////////////////////////////////////////

ch_simulator::ch_simulator(const std::initializer_list<const ch_device*>& devices) {
  impl_ = new simulatorimpl(devices);
}

ch_simulator::ch_simulator(simulatorimpl* impl): impl_(impl) {}

ch_simulator::~ch_simulator() {
  delete impl_;
}

void ch_simulator::add_device(const ch_device& device) {
  impl_->add_device(device);
}

void ch_simulator::tick(ch_cycle t) { 
  impl_->tick(t);
}

void ch_simulator::run(const std::function<bool(ch_cycle time)>& callback) {
  impl_->run(callback);
}

void ch_simulator::run(ch_cycle cycles) {
  impl_->run(cycles);
}

ch_cycle ch_simulator::reset(ch_cycle t) {
  return impl_->reset(t);
}

void ch_simulator::step(ch_cycle t) {
  impl_->step(t);
}
