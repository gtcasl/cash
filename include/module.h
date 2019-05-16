#pragma once

#include "device.h"

namespace ch {
namespace internal {

template <typename T>
class ch_module final : public device {
public:
  static_assert(has_logic_io_v<T>, "missing io port");
  static_assert(is_detected_v<detect_describe_t, T>, "missing describe() method");
  using base = device;
  using io_type = ch_flip_io<decltype(T::io)>;

  io_type io;

  template <typename... Args>
  ch_module(Args&&... args)
    : device(std::type_index(typeid(T)), (sizeof...(Args) != 0), idname<T>())
    , io(module_loader<T>(this, std::forward<Args>(args)...).get())
  {}

  ch_module(ch_module&& other)
    : base(std::move(other))
    , io(std::move(other.io))
  {}

protected:

  ch_module(const ch_module& other) = delete;

  ch_module& operator=(const ch_module& other) = delete;

  ch_module& operator=(ch_module&& other) = delete;
};

}
}
