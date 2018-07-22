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

  void bind_input(const lnode& src, const lnode& ioport, const source_location& sloc);

  void bind_output(const lnode& dst, const lnode& ioport,const source_location& sloc);

  context* module() const {
    return module_;
  }

  void eval() override;

  void print(std::ostream& out, uint32_t level) const override;

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

protected:  

  bindportimpl(context* ctx,
               lnodetype type,
               bindimpl* bind,
               const lnode& ioport,
               const source_location& sloc);

  ~bindportimpl();

  bindimpl* binding_;
  lnode ioport_;

  friend class context;
};

///////////////////////////////////////////////////////////////////////////////

class bindinimpl : public bindportimpl {
public:

  void initialize() override;

  void eval() override;

  void print(std::ostream& out, uint32_t level) const override;

protected:

  bindinimpl(context* ctx,
             bindimpl* bind,
             const lnode& src,
             const lnode& ioport,
             const source_location& sloc);

  ~bindinimpl();

  uint32_t* words_;

  friend class context;
};

///////////////////////////////////////////////////////////////////////////////

class bindoutimpl : public bindportimpl {
public:

  void initialize() override;

  void eval() override;

  void print(std::ostream& out, uint32_t level) const override;

protected:

  bindoutimpl(context* ctx,
              bindimpl* bind,
              const lnode& ioport,
              const source_location& sloc);

  ~bindoutimpl();

  uint32_t* words_;

  friend class context;
};

}
}
