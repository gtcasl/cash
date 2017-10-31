#pragma once

#include "port.h"

namespace ch {
namespace internal {

class deviceimpl;

class device {
public:
  device(size_t signature, const std::string& name);
  virtual ~device();

protected:

  void compile();

  deviceimpl* impl_;

  friend context* get_ctx(const device& device);
};

template <typename T>
class device_base : public device {
public:
  template <typename... Ts>
  device_base(size_t signature, const std::string& name, Ts&&... args)
    : device(signature, name) {
    obj_ = std::make_shared<T>(args...);
    obj_->describe();
    this->compile();
  }

protected:
  std::shared_ptr<T> obj_;
};

context* get_ctx(const device& device);

///////////////////////////////////////////////////////////////////////////////

template <typename IoType>
struct device_traits {
  using io_type = IoType;
};

template <typename T>
class ch_device final : public device_base<T> {
public:
  using base = device_base<T>;
  using base::obj_;
  using traits = device_traits<port_type_t<decltype(obj_->io)>>;

  typename traits::io_type io;

  template <typename... Ts>
  ch_device(const std::string& name, Ts&&... args)
    : base(typeid(T).hash_code(), name, std::forward<Ts>(args)...)
    , io(obj_->io)
  {}

  template <typename... Ts>
  ch_device(Ts&&... args)
    : base(typeid(T).hash_code(),
           identifier_from_typeid(typeid(T).name()).c_str(),
           std::forward<Ts>(args)...)
    , io(obj_->io)
  {}
};

}
}
