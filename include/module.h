#pragma once

#include "device.h"

namespace ch {
namespace internal {

template <typename T = void>
class ch_module final : public device_base {
protected:

  ch_module& operator=(const ch_module& other) = delete;

  ch_module& operator=(ch_module&& other) = delete;

  std::shared_ptr<T> obj_;

public:

  using base = device_base;
  using traits = module_traits<T>;
  typename traits::io_type io;

  explicit ch_module(CH_SRC_INFO)
    : base(std::type_index(typeid(T)), is_pod_module_v<T>, idname<T>())
    , obj_(this->load<T>(srcinfo.name(), srcinfo.sloc()))
    , io(obj_->io, srcinfo.sloc())
  {}

#define CH_MODULE_GEN_TMPL(a, i, x)  typename Arg##i
#define CH_MODULE_GEN_TYPE(a, i, x)  Arg##i
#define CH_MODULE_GEN_DECL(a, i, x)  Arg##i&& arg##i
#define CH_MODULE_GEN_ARG(a, i, x)   std::forward<Arg##i>(arg##i)
#define CH_MODULE_GEN_SINFO(a, i, x) !std::is_same_v<std::decay_t<Arg##i>, source_info>
#define CH_MODULE_GEN(...) \
  template <CH_FOR_EACH(CH_MODULE_GEN_TMPL, , CH_SEP_COMMA, __VA_ARGS__), \
            CH_REQUIRES(CH_FOR_EACH(CH_MODULE_GEN_SINFO, , CH_SEP_ANDL, __VA_ARGS__) \
                     && std::is_constructible_v<T, CH_FOR_EACH(CH_MODULE_GEN_TYPE, , CH_SEP_COMMA, __VA_ARGS__)>)> \
  ch_module(CH_FOR_EACH(CH_MODULE_GEN_DECL, , CH_SEP_COMMA, __VA_ARGS__), CH_SRC_INFO) \
    : base(std::type_index(typeid(T)), is_pod_module_v<T, CH_FOR_EACH(CH_MODULE_GEN_TYPE, , CH_SEP_COMMA, __VA_ARGS__)>, idname<T>()) \
    , obj_(this->load<T>(srcinfo.name(), srcinfo.sloc(), CH_FOR_EACH(CH_MODULE_GEN_ARG, , CH_SEP_COMMA, __VA_ARGS__))) \
    , io(obj_->io, srcinfo.sloc()) \
  {}
CH_VA_ARGS_MAP(CH_MODULE_GEN)
#undef CH_MODULE_GEN_TMPL
#undef CH_MODULE_GEN_TYPE
#undef CH_MODULE_GEN_DECL
#undef CH_MODULE_GEN_ARG
#undef CH_MODULE_GEN_SINFO
#undef CH_MODULE_GEN

  ch_module(const ch_module& other) 
    : base(other)
    , obj_(other.obj_)
    , io(other.io) 
  {}

  ch_module(ch_module&& other)
    : base(std::move(other))
    , obj_(std::move(other.obj_))
    , io(std::move(other.io))
  {}

  const T* operator->() const {
    return obj_.get();
  }
};

/*template <>
class ch_module<void> : public device_base {
public:
  using base = device_base;

  ch_module() {}

  ch_module(const base& other) : base(other) {}

  ch_module(base&& other) : base(std::move(other)) {}

  ch_module& operator=(const base& other) {
    base::operator=(other);
    return *this;
  }

  ch_module& operator=(base&& other) {
    base::operator=(std::move(other));
    return *this;
  }
};*/

}
}
