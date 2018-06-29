#pragma once

#include "device.h"

namespace ch {
namespace internal {

template <typename IoType>
struct module_traits {
  using io_type = ch_flip_t<IoType>;
};

template <typename T>
class ch_module final : private device {
public:  
  using base = device;
  using traits = module_traits<decltype(T::io)>;

  typename traits::io_type io;

  template <typename... Ts>
  ch_module(const std::string& name, Ts&&... args)
    : device(std::type_index(typeid(T)), name)
    , io(build(T(std::forward<Ts>(args)...)).io, source_location())
  {}

  template <typename... Ts>
  ch_module(Ts&&... args)
    : device(std::type_index(typeid(T)),
             identifier_from_typeid(typeid(T).name()).c_str())
    , io(build(T(std::forward<Ts>(args)...)).io, source_location())
  {}

  ch_module(ch_module&& other) : base(std::move(other)), io(std::move(other.io)) {}

protected:

  auto&& build(T&& obj) {
    obj.describe();
    this->compile();
    return obj;
  }

  ch_module(const ch_module& other) = delete;

  ch_module& operator=(const ch_module& other) = delete;

  ch_module& operator=(ch_module&& other) = delete;
};

}
}
