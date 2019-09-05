#include "simulatorimpl.h"
#include "simulator.h"
#include "compile.h"
#include "deviceimpl.h"
#include "litimpl.h"
#include "ioimpl.h"
#include "cdimpl.h"
#include "simref.h"
#include "simjit.h"

using namespace ch::internal;

void clock_driver::add_signal(inputimpl* node) {
  *node->value() = value_;
  nodes_.push_back(node->value());
}

void clock_driver::eval() {
  value_ = !value_;
  for (auto node : nodes_) {
    *node = value_;
  }
}

///////////////////////////////////////////////////////////////////////////////

simulatorimpl::simulatorimpl(const std::vector<device_base>& devices)
  : eval_ctx_(nullptr)
  , clk_driver_(true)
  , reset_driver_(false)
  , sim_driver_(nullptr)
  , verbose_tracing_(false) {
  // enqueue all contexts
  for (auto dev : devices) {
    auto ctx = dev.impl()->ctx();
    if (ctx->bindings().size()
     && (platform::self().cflags() & cflags::codegen_merged) != 0) {
      auto merged_ctx = new context(ctx->name());
      merged_ctx->acquire();
      compiler compiler(merged_ctx);
      compiler.create_merged_context(ctx);
      compiler.optimize();
      ctx = merged_ctx;
    }
    contexts_.emplace_back(ctx);
    ctx->acquire();
  }
}

simulatorimpl::~simulatorimpl() {
  if (sim_driver_) {
    sim_driver_->release();
  }
  if (eval_ctx_) {
    eval_ctx_->release();
  }
  for (auto ctx : contexts_) {
    ctx->release();
  }
}

void simulatorimpl::initialize() {
  {
    if (1 == contexts_.size()
     && 0 == contexts_[0]->bindings().size()) {
      eval_ctx_ = contexts_[0];
      eval_ctx_->acquire();
    } else {
      eval_ctx_ = new context("eval");
      eval_ctx_->acquire();

      // build evaluation context
      {
        compiler compiler(eval_ctx_);
        for (auto ctx : contexts_) {
          compiler.create_merged_context(ctx, verbose_tracing_);
        }
        compiler.optimize();
      }
    }

    // build evaluation list
    std::vector<lnodeimpl*> eval_list;
    {
      compiler compiler(eval_ctx_);
      compiler.build_eval_list(eval_list);
    }

    // initialize driver
  #if defined(LIBJIT) || defined(LLVMJIT)
    if (0 == (platform::self().cflags() & cflags::disable_jit)) {
      sim_driver_ = new simjit::driver();
    } else {
      sim_driver_ = new simref::driver();
    }
  #else
    sim_driver_ = new simref::driver();
  #endif
    sim_driver_->acquire();
    sim_driver_->initialize(eval_list);
  }

  // bind system signals
  auto clk = eval_ctx_->sys_clk();
  if (clk) {
    clk_driver_.add_signal(clk);
  }
  auto reset = eval_ctx_->sys_reset();
  if (reset) {
    reset_driver_.add_signal(reset);
  }
}

void simulatorimpl::eval() {
  sim_driver_->eval();
}

ch_tick simulatorimpl::reset(ch_tick t) {
  if (!reset_driver_.empty()) {
    reset_driver_.eval();
    t = this->step(t, 2);
    reset_driver_.eval();
  }
  return t;
}

ch_tick simulatorimpl::step(ch_tick t, uint32_t count) {
  auto ret = t + count;
  if (clk_driver_.empty()) {
    while (count--) {
      this->eval();
    }
  } else {
    while (count--) {
      clk_driver_.eval();
      this->eval();
    }
  }   
  return ret;
}

ch_tick simulatorimpl::run(const std::function<bool(ch_tick t)>& callback,
                           uint32_t steps) {
  auto t = this->reset(0);
  for (auto start = t; callback(t - start);) {
    t = this->step(t, steps);
  }
  return t;
}

void simulatorimpl::run(ch_tick num_ticks) {
  auto start = this->reset(0);
  if (num_ticks > start) {
    this->step(start, num_ticks - start);
  }
}

///////////////////////////////////////////////////////////////////////////////

ch_simulator::ch_simulator() : impl_(nullptr) {}

ch_simulator::ch_simulator(const std::vector<device_base>& devices) {
  impl_ = new simulatorimpl(devices);
  impl_->acquire();

  // initialize
  impl_->initialize();
}

ch_simulator::ch_simulator(simulatorimpl* impl) : impl_(impl) {
  if (impl) {
    impl->acquire();
  }
}

ch_simulator::ch_simulator(const ch_simulator& other)
  : impl_(other.impl_) {
  if (impl_) {
    impl_->acquire();
  }
}

ch_simulator::ch_simulator(ch_simulator&& other)
  : impl_(std::move(other.impl_)) {
  other.impl_ = nullptr;
}

ch_simulator::~ch_simulator() {
  if (impl_) {
    impl_->release();
  }
}

ch_simulator& ch_simulator::operator=(const ch_simulator& other) {
  if (other.impl_) {
    other.impl_->acquire();
  }
  if (impl_) {
    impl_->release();
  }
  impl_ = other.impl_;
  return *this;
}

ch_simulator& ch_simulator::operator=(ch_simulator&& other) {
  if (impl_) {
    impl_->release();
  }
  impl_ = other.impl_;
  other.impl_ = nullptr;
  return *this;
}

ch_tick ch_simulator::run(const std::function<bool(ch_tick t)>& callback, uint32_t steps) {
  return impl_->run(callback, steps);
}

void ch_simulator::run(ch_tick num_ticks) {
  impl_->run(num_ticks);
}

ch_tick ch_simulator::reset(ch_tick t) {
  return impl_->reset(t);
}

ch_tick ch_simulator::step(ch_tick t, uint32_t count) {
  return impl_->step(t, count);
}

void ch_simulator::eval() {
  impl_->eval();
}
