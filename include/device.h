#pragma once

#include "ioport.h"

namespace ch {
namespace internal {

class deviceimpl;
class context;

class device_base {
public:

  device_base();

  virtual ~device_base();

  device_base(const device_base& other);

  device_base(device_base&& other);

  device_base& operator=(const device_base& other);

  device_base& operator=(device_base&& other);

  auto impl() const {
    return impl_;
  }

protected:

  device_base(const std::type_index& signature, bool is_pod, const std::string& name);

  bool begin();

  void build();

  void end();

  deviceimpl* impl_;

  template <typename T> friend class io_loader;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class io_loader {
public:
  template <typename... Args>
  io_loader(device_base* dev, Args&&... args) {
    if (dev->begin()) {
      {
        CH_API_ENTRY(2);
        obj_ = new T(std::forward<Args>(args)...);        
      }
      obj_->describe();
      empty_ = nullptr;
    } else {
      CH_API_ENTRY(2);
      obj_ = nullptr;
      empty_ = new empty_t();
    }
    {
      CH_API_ENTRY(2);
      dev->build();
    }
    dev->end();
  }

  ~io_loader() {
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
class ch_device final : public device_base {
public:
  static_assert(has_logic_io_v<T>, "missing io port");
  static_assert(is_detected_v<detect_describe_t, T>, "missing describe() method");
  using base = device_base;
  using io_type = ch_flip_io<ch_system_io<decltype(T::io)>>;

  io_type io;

  template <typename... Args,
            CH_REQUIRE(std::is_constructible_v<T, Args...>)>
  ch_device(const std::string& name, Args&&... args)
    : base(std::type_index(typeid(T)), 0 == sizeof...(Args), name)
    , io(io_loader<T>(this, std::forward<Args>(args)...).get())
  {}

  template <typename... Args,
            CH_REQUIRE(std::is_constructible_v<T, Args...>)>
  ch_device(Args&&... args)
    : base(std::type_index(typeid(T)), 0 == sizeof...(Args), idname<T>(true))
    , io(io_loader<T>(this, std::forward<Args>(args)...).get())
  {}

  ch_device(const ch_device& other) 
    : base(other)
    , io(other.io) 
  {}

  ch_device(ch_device&& other)
    : base(std::move(other))
    , io(std::move(other.io))
  {}

protected: 

  ch_device& operator=(const ch_device& other) = delete;

  ch_device& operator=(ch_device&& other) = delete;
};

template <>
class ch_device<void> : public device_base {
public:
  using base = device_base;

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

void ch_stats(std::ostream& out, const device_base& device);

}
}
