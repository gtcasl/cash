#pragma once

#include "port.h"

namespace ch {
namespace internal {

class deviceimpl;

class device {
public:
  device(size_t signature, const std::string& name);
  virtual ~device();

  device(device&& rhs) : impl_(std::move(rhs.impl_)) {}

  device& operator=(device&& rhs) {
    impl_ = std::move(rhs.impl_);
    return *this;
  }

protected:

  device(const device& rhs) = delete;
  device& operator=(const device& rhs) = delete;

  void compile();

  deviceimpl* impl_;

  friend context* get_ctx(const device& device);
};

template <typename T>
class device_base : public device {
public:
  using base = device;

  template <typename... Ts>
  device_base(size_t signature, const std::string& name, Ts&&... args)
    : device(signature, name) {
    obj_ = std::make_shared<T>(args...);
    obj_->describe();
    this->compile();
  }

  device_base(device_base&& rhs)
    : base(std::move(rhs))
    , obj_(std::move(rhs.obj_))
  {}

  device_base& operator=(device_base&& rhs) {
    base::operator=(std::move(rhs));
    impl_ = std::move(rhs.impl_);
    return *this;
  }

protected:

  device_base(const device_base& rhs) = delete;
  device_base& operator=(const device_base& rhs) = delete;

  std::shared_ptr<T> obj_;
};

context* get_ctx(const device& device);

///////////////////////////////////////////////////////////////////////////////

template <typename IoType>
struct device_traits {
  using io_type = typename IoType::traits::device_type;
};

template <typename T>
class ch_device final : public device_base<T> {
public:
  using base = device_base<T>;
  using base::obj_;
  using traits = device_traits<decltype(obj_->io)>;

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

  ch_device(ch_device&& rhs) : base(std::move(rhs)) {}

  ch_device& operator=(ch_device&& rhs) {
    base::operator=(std::move(rhs));
    return *this;
  }

protected:

  ch_device(const ch_device& rhs) = delete;
  ch_device& operator=(const ch_device& rhs) = delete;
};

}
}
