#pragma once

#include "lnodeimpl.h"
#include "udf.h"

namespace ch {
namespace internal {

class udf_iface : public refcounted {
public:

  udf_iface(uint32_t id,
            bool is_seq,
            uint32_t output_size,
            const std::initializer_list<uint32_t>& inputs_size,
            udf_base* impl);

  ~udf_iface();

  uint32_t id() const {
    return id_;
  }

  void set_managed(bool value) {
    is_managed_ = value;
  }

  bool is_managed() const {
    return is_managed_;
  }

  bool is_seq() const {
    return is_seq_;
  }

  uint32_t output_size() const {
    return output_size_;
  }

  const std::vector<uint32_t>& inputs_size() const {
    return inputs_size_;
  }

  udf_base* impl() const {
    return impl_;
  }

private:

  uint32_t id_;
  bool is_managed_;
  bool is_seq_;
  uint32_t output_size_;
  std::vector<uint32_t> inputs_size_;
  udf_base* impl_;
};

///////////////////////////////////////////////////////////////////////////////

class udfimpl : public lnodeimpl {
public:

  udf_iface* udf() const {
    return udf_;
  }

protected:

  udfimpl(context* ctx,
          lnodetype type,
          udf_iface* udf,
          const std::vector<lnode>& srcs,
          const source_location& sloc);

  ~udfimpl();

  udf_iface* udf_;

  friend class context;
};

///////////////////////////////////////////////////////////////////////////////

class udfcimpl : public udfimpl {
public:

  lnodeimpl* clone(context* ctx, const clone_map& cloned_nodes) const override;

protected:

  udfcimpl(context* ctx,
          udf_iface* udf,
          const std::vector<lnode>& srcs,
          const source_location& sloc);

  friend class context;
};

///////////////////////////////////////////////////////////////////////////////

class udfsimpl : public udfimpl {
public:

  const lnode& cd() const {
    return this->src(cd_idx_);
  }

  lnodeimpl* clone(context* ctx, const clone_map& cloned_nodes) const override;

protected:

  udfsimpl(context* ctx,
           udf_iface* udf,
           lnodeimpl* cd,
           const std::vector<lnode>& srcs,
           const source_location& sloc);

  int cd_idx_;

  friend class context;
};

}}
