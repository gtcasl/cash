#pragma once

#include "ioimpl.h"
#include "tickable.h"

namespace ch {
namespace internal {

class callimpl : public tickable, public ioimpl {
public:
  void bind_input(const lnode& input, const lnode& src);

  context* get_module_ctx() const {
    return module_ctx_;
  }

  void tick(ch_tick t) override;

  void tick_next(ch_tick t) override;

  const bitvector& eval(ch_tick t) override;

  void print(std::ostream& out, uint32_t level) const override;

protected:
  callimpl(context* ctx, context* module_ctx);
  ~callimpl();

  context* module_ctx_;
  ch_tick tick_;

  friend class context;
};

///////////////////////////////////////////////////////////////////////////////

class callportimpl : public ioimpl {
public:
  const lnode& get_output() const {
    return output_;
  }

  const bitvector& eval(ch_tick t) override;

  void print(std::ostream& out, uint32_t level) const override;

protected:
  callportimpl(context* ctx, callimpl* call, const lnode& output);
  ~callportimpl() {}

  lnode output_;
  ch_tick tick_;

  friend class context;
};

}
}
