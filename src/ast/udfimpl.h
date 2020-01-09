#pragma once

#include "ioimpl.h"

namespace ch {
namespace internal {

class udf_iface;

class udfimpl : public ioimpl {
public:

  udf_iface* udf() const {
    return udf_;
  }

  auto& inputs() {
    return inputs_;
  }

  auto& outputs() {
    return outputs_;
  }

  void add_input(lnodeimpl* input) {
    this->add_src(input);
    inputs_.push_back(input);
  }

  void add_output(lnodeimpl* output) {
    outputs_.push_back(output);
  }

  void remove_port(lnodeimpl* port);

protected:

  udfimpl(context* ctx,
          lnodetype type,
          udf_iface* udf,
          const std::string& name,
          const source_location& sloc);

  ~udfimpl();

  udf_iface* udf_;
  std::vector<lnode> inputs_;
  std::vector<lnode> outputs_;

  friend class context;
};

///////////////////////////////////////////////////////////////////////////////

class udfcimpl : public udfimpl {
public:

  lnodeimpl* clone(context* ctx, const clone_map& cloned_nodes) const override;

protected:

  udfcimpl(context* ctx,
           udf_iface* udf,
           const std::string& name,
           const source_location& sloc);

  ~udfcimpl() override;

  friend class context;
};

///////////////////////////////////////////////////////////////////////////////

class udfsimpl : public udfimpl {
public:

  const lnode& cd() const {
    return this->src(cd_idx_);
  }

  const lnode& reset() const {
    return this->src(reset_idx_);
  }

  lnodeimpl* clone(context* ctx, const clone_map& cloned_nodes) const override;

protected:

  udfsimpl(context* ctx,
           udf_iface* udf,
           lnodeimpl* cd,
           lnodeimpl* reset,
           const std::string& name,
           const source_location& sloc);

  ~udfsimpl() override;

  int cd_idx_;
  int reset_idx_;

  friend class context;
};

///////////////////////////////////////////////////////////////////////////////

class udfportimpl : public ioportimpl {
public:

  udfimpl* udf() const {
    return udf_;
  }

  lnodeimpl* clone(context* ctx, const clone_map& cloned_nodes) const override;

protected:

  udfportimpl(context* ctx,
              unsigned size,
              lnodeimpl* src,
              udfimpl* udf,
              const io_value_t& value,
              const std::string& name,
              const source_location& sloc);

  udfportimpl(context* ctx,
              unsigned size,
              udfimpl* udf,
              const io_value_t& value,
              const std::string& name,
              const source_location& sloc);

  ~udfportimpl();

  udfimpl* udf_;

  friend class context;
};

}}
