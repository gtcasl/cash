#pragma once

#include "ioport.h"

namespace ch {
namespace internal {

class deviceimpl;
class context;

class device {
public:

  device();

  virtual ~device();

  device(const device& other);

  device(device&& other);

  device& operator=(const device& other);

  device& operator=(device&& other);

  auto impl() const {
    return impl_;
  }

protected:

  device(const std::type_index& signature, bool has_args, const std::string& name);

  bool begin_build() const;

  void end_build();

  deviceimpl* impl_;

  template <typename T> friend class device_base;
};

using ch_device_list = std::vector<device>;

///////////////////////////////////////////////////////////////////////////////

template <typename T = void>
class ch_device final : public device {
public:
  using base = device;
  using io_type = ch_system_io<decltype(T::io)>;

protected:
  std::shared_ptr<io_type> _;

public:
  io_type& io;

  template <typename... Us>
  ch_device(const std::string& name, Us&&... args)
    : device(std::type_index(typeid(T)), name)
    , _(build(std::forward<Us>(args)...))
    , io(*_)
  {}

  template <typename... Us>
  ch_device(Us&&... args)
    : device(std::type_index(typeid(T)), (sizeof...(Us) != 0), typeid(T).name())
    , _(build(std::forward<Us>(args)...))
    , io(*_)
  {}

  ch_device(ch_device&& other)
    : base(std::move(other))
    , io(std::move(other.io))
  {}

protected:

  template <typename... Us>
  auto build(Us&&... args) {
    std::shared_ptr<io_type> out;
    if (this->begin_build()) {
      T obj(std::forward<Us>(args)...);
      obj.describe();
      this->end_build();
      out = std::make_shared<io_type>(obj.io);
    } else {
      decltype(T::io) obj_io;
      this->end_build();
      out = std::make_shared<io_type>(obj_io);
    }
    return out;
  }

  ch_device(const ch_device& other) = delete;

  ch_device& operator=(const ch_device& other) = delete;

  ch_device& operator=(ch_device&& other) = delete;
};

template <>
class ch_device<void> : public device {
public:
  using base = device;

  ch_device() {}

  ch_device(const base& other) : base(other) {}

  ch_device(base&& other) : base(std::move(other)) {}

  ch_device& operator=(const base& other) {
    base::operator=(other);
    return *this;
  }

  ch_device& operator=(base&& other) {
    base::operator=(std::move(other));
    return *this;
  }
};

///////////////////////////////////////////////////////////////////////////////

void ch_stats(std::ostream& out, const device& device);

}
}
