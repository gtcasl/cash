#pragma once

#include "device.h"

namespace ch {
namespace internal {

template <typename IoType>
struct module_traits {
  using io_type = flip_type_t<IoType>;
};

template <typename T>
class ch_module final : public device_base<T> {
public:  
  using base = device_base<T>;
  using base::obj_;
  using traits = module_traits<decltype(obj_->io)>;

  typename traits::io_type io;

  template <typename... Ts>
  ch_module(const std::string& name, Ts&&... args)
    : base(typeid(T).hash_code(), name, std::forward<Ts>(args)...)
    ,io(obj_->io)
  {}

  template <typename... Ts>
  ch_module(Ts&&... args)
    : base(typeid(T).hash_code(),
           identifier_from_typeid(typeid(T).name()).c_str(),
           std::forward<Ts>(args)...)
    , io(obj_->io)
  {}

  ch_module(ch_module&& rhs) : base(std::move(rhs)) {}

  ch_module& operator=(ch_module&& rhs) {
    base::operator=(std::move(rhs));
    return *this;
  }

protected:

  ch_module(const ch_module& rhs) = delete;

  ch_module& operator=(const ch_module& rhs) = delete;
};

}
}
