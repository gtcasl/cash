#pragma once

#include "ioimpl.h"
#include "cdomain.h"

namespace ch {
namespace internal {

class bindportimpl;

class bindimpl : public tickable, public ioimpl {
public:

  void bind_input(const lnode& src, const lnode& ioport);

  void bind_output(const lnode& dst, const lnode& ioport);

  const auto& get_inputs() {
    return srcs_;
  }

  const auto& get_outputs() {
    return outputs_;
  }

  void remove_output(bindportimpl* output);

  context* get_module() const {
    return module_;
  }

  void tick(ch_tick t) override;

  void tick_next(ch_tick t) override;

  const bitvector& eval(ch_tick t) override;

  void print(std::ostream& out, uint32_t level) const override;

protected:

  bindimpl(context* ctx, context* module);

  ~bindimpl();

  context* module_;
  std::vector<lnode> outputs_;
  ch_tick tick_;

  friend class context;
};

///////////////////////////////////////////////////////////////////////////////

class bindportimpl : public ioimpl {
public:

  const lnode& get_ioport() const {
    return ioport_;
  }

  bool is_output() const {
    return is_output_;
  }

  const bitvector& eval(ch_tick t) override;

  void print(std::ostream& out, uint32_t level) const override;

  void detach();

protected:  

  bindportimpl(context* ctx, const lnode& src, const lnode& ioport);

  ~bindportimpl();

  lnode ioport_;
  bool is_output_;
  ch_tick tick_;

  friend class context;
};

}
}
