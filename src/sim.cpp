#include "sim.h"
#include "cdomain.h"
#include "context.h"
#include "snodeimpl.h"
#include "ioimpl.h"
#include "compile.h"

using namespace std;
using namespace cash::detail;

ch_simulator::ch_simulator(const std::initializer_list<const ch_device*>& devices)
  : initialized_(false)
  , clk_(nullptr)
  , reset_(nullptr) {
  for (auto device : devices) {
    context* ctx = device->ctx_; 
    auto ret = contexts_.emplace(ctx);
    if (ret.second)
      ctx->acquire();
  }
}

ch_simulator::~ch_simulator() {
  if (clk_)
    clk_->release();
  if (reset_)
    reset_->release();
  for (auto ctx : contexts_) {
    ctx->release();
  }
}

void ch_simulator::add_device(const ch_device& device) {
  context* ctx = device.ctx_; 
  auto ret = contexts_.emplace(ctx);
  if (ret.second)
    ctx->acquire();
}

void ch_simulator::ensureInitialize() {
  // bind context taps
  for (auto ctx : contexts_) {
    if (ctx->clk_) {
      if (nullptr == clk_) {
        clk_ = new snodeimpl(1);
        clk_->write(0u, 0x1); // initialize the clock to '1'
        clk_->acquire();
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

void ch_simulator::tick(ch_cycle t) { 
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
      std::cerr << "cycle " << t << ":" << endl;
      ctx->dump_ast(std::cerr, 2);
    }
  #endif
  }
}

void ch_simulator::run(const std::function<bool(ch_cycle time)>& callback) {
  ch_cycle start = this->reset(0);
  for (ch_cycle time = start; callback(time - start); ++time) {
    this->step(time);
  }
}

void ch_simulator::run(ch_cycle cycles) {
  ch_cycle time = this->reset(0);
  for (; time < cycles; ++time) {
    this->step(time);
  }
}

ch_cycle ch_simulator::reset(ch_cycle t) {
  // ensure initialized
  if (!initialized_) {
    this->ensureInitialize();
    initialized_ = true;
  }

  if (reset_) {
    (*reset_)[0] = true;    
    this->step(t++);
    (*reset_)[0] = false;
  }
  
  return t;
}

void ch_simulator::step(ch_cycle t) {
  if (clk_) {
    for (int i = 0; i < 2; ++i) {
      (*clk_)[0] = !(*clk_)[0];
      this->tick(t * 2 + i);      
    }
  } else {
    this->tick(t);
  }
}

///////////////////////////////////////////////////////////////////////////////

ch_tracer::ch_tracer(std::ostream& out, const std::initializer_list<const ch_device*>& devices) 
  : ch_simulator(devices)
  , out_(out) {}

ch_tracer::~ch_tracer() {  
  for (auto& tap : taps_) {
    tap.bus->release();
  }
}

void ch_tracer::ensureInitialize() {
  // call parent ensureInitialize()
  ch_simulator::ensureInitialize();
  
  // register clock signals
  if (clk_) {
    this->add_trace("clk", clk_);
  }
  if (reset_) {
    this->add_trace("reset", reset_);
  }

  // register context taps
  for (auto ctx : contexts_) {    
    for (tapimpl* tap : ctx->taps_) {
      this->add_trace(tap->get_tapName(), tap->get_bus());
    #ifndef NDEBUG
      int dump_cfg_level = platform::self().get_dump_cfg();
      if (dump_cfg_level) {
        std::cout << "CFG dump for tap variable: " << tap->get_tapName() << std::endl;
        ctx->dump_cfg(tap, std::cout, dump_cfg_level);
      }
    #endif
    }
  }
}

void ch_tracer::add_trace(const std::string& name, snodeimpl* bus) {
  CH_CHECK(!initialized_, "new tap not allowed after simulation has started");
  
  // resolve duplicate names  
  string full_name(name);
  unsigned instances = dup_taps_[name]++;
  if (instances > 0) {
    if (instances == 1) {
      // rename first instance
      auto iter = std::find_if(taps_.begin(), taps_.end(),
        [name](const tap_t& t)->bool { return t.name == name; });
      assert(iter != taps_.end());
      iter->name = fstring("%s_%d", name.c_str(), 0);
    }
    full_name = fstring("%s_%d", name.c_str(), instances);
  }
  taps_.emplace_back(full_name, bus);
  bus->acquire();
}

void ch_tracer::tick(ch_cycle t) {
  // advance simulation
  ch_simulator::tick(t);
  
  CH_TODO();
}

///////////////////////////////////////////////////////////////////////////////

void cash::detail::register_tap(const string& name, lnodeimpl* node) {
  node->get_ctx()->register_tap(name, node);
}
