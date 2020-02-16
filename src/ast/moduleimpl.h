#pragma once

#include "ioimpl.h"

namespace ch {
namespace internal {

class moduleimpl : public ioimpl {
public:

  context* target() const {
    return target_;
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

  void remove_port(lnodeimpl* port);

  void print(std::ostream& out) const override;

protected:

  moduleimpl(context* ctx, 
             context* target, 
             const std::string& name,
             const source_location& sloc);

  ~moduleimpl() override;

  context* target_;
  std::vector<lnode> outputs_;

  friend class context;
};

///////////////////////////////////////////////////////////////////////////////

class moduleportimpl : public ioimpl {
public:

  moduleimpl* module() const {
    return module_;
  }

  auto& ioport() const {
    return ioport_;
  }

  lnodeimpl* clone(context* ctx, const clone_map& cloned_nodes) const override;

  void print(std::ostream& out) const override;

protected:

  moduleportimpl(context* ctx,
                 moduleimpl* module,
                 lnodeimpl* src,
                 inputimpl* ioport,
                 const source_location& sloc);

  moduleportimpl(context* ctx,
                 moduleimpl* module,
                 outputimpl* ioport,
                 const source_location& sloc);

  ~moduleportimpl() override;

  moduleimpl* module_;
  lnode ioport_;

  friend class context;
};

}
}
