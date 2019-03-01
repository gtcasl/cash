#pragma once

#include "device.h"

namespace ch {
namespace internal {

template <typename T>
class ch_module final : public device {
public:
  using base = device;
  using io_type = ch_flip_io<decltype(T::io)>;

protected:
  std::shared_ptr<io_type> _;

public:
  io_type& io;

  ch_module(CH_SLOC)
    : device(std::type_index(typeid(T)), false, typeid(T).name())
    , _(build(sloc))
    , io(*_)
  {}

#define CH_MODULE_TMPL(a, i, x) typename __U##i
#define CH_MODULE_REQUIRE(a, i, x) __U##i
#define CH_MODULE_DECL(a, i, x) const __U##i& arg##i
#define CH_MODULE_ARG(a, i, x) arg##i
#define CH_MODULE(...) \
  template <CH_FOR_EACH(CH_MODULE_TMPL, , CH_SEP_COMMA, __VA_ARGS__), \
            CH_REQUIRE_0(std::is_constructible_v<T, CH_FOR_EACH(CH_MODULE_REQUIRE, , CH_SEP_COMMA, __VA_ARGS__)>)> \
  ch_module(CH_FOR_EACH(CH_MODULE_DECL, , CH_SEP_COMMA, __VA_ARGS__), CH_SLOC) \
    : device(std::type_index(typeid(T)), true, typeid(T).name()) \
    , _(build(sloc, CH_FOR_EACH(CH_MODULE_ARG, , CH_SEP_COMMA, __VA_ARGS__))) \
    , io(*_) \
  {}
CH_VA_ARGS_MAP(CH_MODULE)
#undef CH_MODULE_TMPL
#undef CH_MODULE_REQUIRE
#undef CH_MODULE_DECL
#undef CH_MODULE_ARG
#undef CH_MODULE

  ch_module(ch_module&& other)
    : base(std::move(other))
    , io(std::move(other.io))
  {}

protected:

  template <typename... Args>
  auto build(const source_location& sloc, Args&&... args) {
    std::shared_ptr<io_type> out;
    if (this->begin_build()) {
      T obj(std::forward<Args>(args)...);
      obj.describe();
      this->end_build();
      out = std::make_shared<io_type>(obj.io, sloc);
    } else {
      decltype(T::io) obj_io(sloc);
      this->end_build();
      out = std::make_shared<io_type>(obj_io, sloc);
    }
    return out;
  }

  ch_module(const ch_module& other) = delete;

  ch_module& operator=(const ch_module& other) = delete;

  ch_module& operator=(ch_module&& other) = delete;
};

}
}
