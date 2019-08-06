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

  template <typename T, typename... Args>
  auto load(Args&&... args) {
    T* obj;
    bool is_dup = this->begin();
    {
      CH_API_ENTRY(2);
      obj = new T(std::forward<Args>(args)...);
    }
    if (!is_dup) {
      this->begin_build();
      obj->describe();
      this->end_build();
    }
    this->end();
    return obj;
  }

  bool begin();

  void begin_build();

  void end_build();

  void end();

  deviceimpl* impl_;

  template <typename T> friend class io_loader;
};

///////////////////////////////////////////////////////////////////////////////

CH_DEF_SFINAE_CHECK(has_logic_io, is_logic_io_v<decltype(T::io)>);

template<typename T>
using detect_describe_t = decltype(std::declval<T&>().describe());

template <typename T, typename... Args>
inline constexpr bool is_reuse_module_v = (0 == sizeof...(Args))
                                       && (sizeof(T) == sizeof(decltype(T::io)));

///////////////////////////////////////////////////////////////////////////////

template <typename T = void>
class ch_device final : public device_base {
protected:

  ch_device& operator=(const ch_device& other) = delete;

  ch_device& operator=(ch_device&& other) = delete;

  std::shared_ptr<T> obj_;

public:

  static_assert(has_logic_io_v<T>, "missing io port");
  static_assert(is_detected_v<detect_describe_t, T>, "missing describe() method");
  using base = device_base;
  using io_type = ch_flip_io<ch_system_io<decltype(T::io)>>;

  io_type io;

  template <typename... Args,
            CH_REQUIRE(std::is_constructible_v<T, Args...>)>
  ch_device(const std::string& name, Args&&... args)
    : base(std::type_index(typeid(T)), is_reuse_module_v<T, Args...>, name)
    , obj_(this->load<T>(std::forward<Args>(args)...))
    , io(obj_->io)
  {}

  template <typename... Args,
            CH_REQUIRE(std::is_constructible_v<T, Args...>)>
  ch_device(Args&&... args)
    : base(std::type_index(typeid(T)), is_reuse_module_v<T, Args...>, idname<T>(true))
    , obj_(this->load<T>(std::forward<Args>(args)...))
    , io(obj_->io)
  {}

  ch_device(const ch_device& other) 
    : base(other)
    , obj_(other.obj_)
    , io(other.io)
  {}

  ch_device(ch_device&& other)
    : base(std::move(other))
    , obj_(std::move(other.obj_))
    , io(std::move(other.io))
  {}
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
