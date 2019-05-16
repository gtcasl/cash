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
  template <typename T> friend class module_loader;
};

using ch_device_list = std::vector<device>;

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class module_loader {
public:
  template <typename... Args>
  module_loader(device* dev, Args&&... args) {
    if (dev->begin_build()) {
      CH_SOURCE_LOCATION(2);
      obj_ = new T(std::forward<Args>(args)...);
      obj_->describe();
      empty_ = nullptr;
    } else {
      CH_SOURCE_LOCATION(2);
      obj_ = nullptr;
      empty_ = new empty_t();
    }
    {
      CH_SOURCE_LOCATION(2);
      dev->end_build();
    }
  }
  ~module_loader() {
    delete obj_;
    delete empty_;
  }
  auto& get() {
    return obj_ ? obj_->io : empty_->io;
  }
private:
  struct empty_t {
    decltype(T::io) io;
  };

  T* obj_;
  empty_t* empty_;
};

///////////////////////////////////////////////////////////////////////////////

CH_DEF_SFINAE_CHECK(has_logic_io, is_logic_io_v<decltype(T::io)>);

template<typename T>
using detect_describe_t = decltype(std::declval<T&>().describe());

///////////////////////////////////////////////////////////////////////////////

template <typename T = void>
class ch_device final : public device {
public:
  static_assert(has_logic_io_v<T>, "missing io port");
  static_assert(is_detected_v<detect_describe_t, T>, "missing describe() method");
  using base = device;
  using io_type = ch_system_io<decltype(T::io)>;

  io_type io;

  template <typename... Args>
  ch_device(const std::string& name, Args&&... args)
    : device(std::type_index(typeid(T)), name)
    , io(module_loader<T>(this, std::forward<Args>(args)...).get())
  {}

  template <typename... Args>
  ch_device(Args&&... args)
    : device(std::type_index(typeid(T)), (sizeof...(Args) != 0), idname<T>(true))
    , io(module_loader<T>(this, std::forward<Args>(args)...).get())
  {}

  ch_device(ch_device&& other)
    : base(std::move(other))
    , io(std::move(other.io))
  {}

protected:

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
