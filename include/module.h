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

  template <typename... Args>
  ch_module(Args&&... args)
    : device(std::type_index(typeid(T)), (sizeof...(Args) != 0), idname<T>())
    , _(this->build(std::forward<Args>(args)...))
    , io(*_)
  {}

  ch_module(ch_module&& other)
    : base(std::move(other))
    , io(std::move(other.io))
  {}

protected:

  template <typename... Args>
  auto build(Args&&... args) {
    std::shared_ptr<io_type> out;
    if (this->begin_build()) {
      std::unique_ptr<T> obj;
      {
        CH_SOURCE_LOCATION(2);
        obj = std::make_unique<T>(std::forward<Args>(args)...);
      }
      obj->describe();
      {
        CH_SOURCE_LOCATION(2);
        this->end_build();
        out = std::make_shared<io_type>(obj->io);
      }
    } else {
      CH_SOURCE_LOCATION(2);
      decltype(T::io) obj_io;
      this->end_build();
      out = std::make_shared<io_type>(obj_io);
    }
    return out;
  }

  ch_module(const ch_module& other) = delete;

  ch_module& operator=(const ch_module& other) = delete;

  ch_module& operator=(ch_module&& other) = delete;
};

}
}
