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

  static_assert(has_logic_io_v<T>, "missing io port");
  static_assert(is_detected_v<detect_describe_t, T>, "missing describe() method");
  using base = device_base;
  using io_type = ch_flip_io<decltype(T::io)>;

  io_type io;

  template <typename... Args,
            CH_REQUIRE(std::is_constructible_v<T, Args...>)>
  ch_module(Args&&... args)
    : base(std::type_index(typeid(T)), is_reuse_module_v<T, Args...>, idname<T>())
    , obj_(this->load<T>(std::forward<Args>(args)...))
    , io(obj_->io)
  {}

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

template <>
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
};

}
}
