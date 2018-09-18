#pragma once

#include "ioimpl.h"
#include "cdimpl.h"

namespace ch {
namespace internal {

class bindportimpl;

class bindimpl : public ioimpl {
public:

  context* module() const {
    return module_;
  }

  const auto& inputs() {
    return srcs_;
  }

  const auto& outputs() {
    return outputs_;
  }

  void bind_input(const lnode& src, const lnode& ioport, const source_location& sloc);

  void bind_output(const lnode& dst, const lnode& ioport,const source_location& sloc);

  void remove_port(bindportimpl* output);

  void print(std::ostream& out) const override;

protected:

  bindimpl(context* ctx, context* module, const source_location& sloc);

  ~bindimpl();

  context* module_;
  std::vector<lnode> outputs_;

  friend class context;
};

///////////////////////////////////////////////////////////////////////////////

class bindportimpl : public ioimpl {
public:

  bindimpl* binding() const {
    return binding_;
  }

  const lnode& ioport() const {
    return ioport_;
  }

  void print(std::ostream& out) const override;

protected:

  bindportimpl(context* ctx,
               bindimpl* bind,
               const lnode& src,
               const lnode& ioport,
               const source_location& sloc);

  bindportimpl(context* ctx,
              bindimpl* bind,
              const lnode& ioport,
              const source_location& sloc);

  ~bindportimpl();

  bindimpl* binding_;
  lnode ioport_;

  friend class context;
};

}
}
