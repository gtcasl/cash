#pragma once

#include "ioimpl.h"
#include "cdimpl.h"

namespace ch {
namespace internal {

class bindportimpl;

class bindimpl : public ioimpl {
public:

  const auto& inputs() {
    return srcs_;
  }

  const auto& outputs() {
    return outputs_;
  }

  void remove_output(bindportimpl* output);

  context* module() const {
    return module_;
  }

  void eval() override;

  void print(std::ostream& out, uint32_t level) const override;

protected:

  bindimpl(context* ctx, context* module);

  ~bindimpl();

  void bind_input(const lnode& src, const lnode& ioport);

  void bind_output(const lnode& dst, const lnode& ioport);

  context* module_;
  std::vector<lnode> outputs_;

  friend class context;
};

///////////////////////////////////////////////////////////////////////////////

class bindportimpl : public ioimpl {
public:

  const lnode& ioport() const {
    return ioport_;
  }

  bool is_output() const {
    return is_output_;
  }

  const lnode& binding() const {
    return srcs_[0];
  }

  void initialize() override;

  void eval() override;

  void print(std::ostream& out, uint32_t level) const override;

protected:  

  bindportimpl(context* ctx, const lnode& src, const lnode& ioport);

  ~bindportimpl();

  lnode ioport_;
  bool is_output_;
  uint32_t* words_;

  friend class context;
};

}
}
