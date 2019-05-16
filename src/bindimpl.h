#pragma once

#include "ioimpl.h"

namespace ch {
namespace internal {

class bindportimpl;

class bindimpl : public ioimpl {
public:

  context* module() const {
    return module_;
  }

  auto& inputs() {
    return this->srcs();
  }

  auto& outputs() {
    return outputs_;
  }

  lnodeimpl* clone(context* ctx, const clone_map& cloned_nodes) const override;

  void bind_input(lnodeimpl* src, inputimpl* ioport, const source_location& sloc);

  void bind_output(lnodeimpl* dst, outputimpl* ioport,const source_location& sloc);

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

  auto& ioport() const {
    return ioport_;
  }

  lnodeimpl* clone(context* ctx, const clone_map& cloned_nodes) const override;

  void print(std::ostream& out) const override;

protected:

  bindportimpl(context* ctx,
               bindimpl* bind,
               lnodeimpl* src,
               inputimpl* ioport,
               const source_location& sloc);

  bindportimpl(context* ctx,
              bindimpl* bind,
              outputimpl* ioport,
              const source_location& sloc);

  ~bindportimpl();

  bindimpl* binding_;
  lnode ioport_;

  friend class context;
};

}
}
