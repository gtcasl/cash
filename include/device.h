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

  device(const std::type_index& signature, const std::string& name);

  void compile();

  deviceimpl* impl_;

  template <typename T> friend class device_base;
};

///////////////////////////////////////////////////////////////////////////////

class ch_device_list {
public:
  ch_device_list() {}

  ch_device_list(const std::initializer_list<device>& devices)
    : container_(devices)
  {}

  void push_back(const device& device) {
    container_.push_back(device);
  }

  const device& operator[](size_t index) const {
    return container_[index];
  }

  auto begin() const {
    return container_.begin();
  }

  auto end() const {
    return container_.end();
  }

  auto size() const {
    return container_.size();
  }

protected:
  std::vector<device> container_;
};

///////////////////////////////////////////////////////////////////////////////

template <typename IoType>
struct device_traits {
  using io_type = typename IoType::traits::device_type;
};

template <typename T = void>
class ch_device final : public device {
public:  
  using base = device;
  using traits = device_traits<decltype(T::io)>;
  typename traits::io_type io;

  template <typename... Ts>
  ch_device(const std::string& name, Ts&&... args)
    : device(std::type_index(typeid(T)), name)
    , io(build(T(std::forward<Ts>(args)...)).io)
  {}

  template <typename... Ts>
  ch_device(Ts&&... args)
    : device(std::type_index(typeid(T)),
             identifier_from_typeid(typeid(T).name()).c_str())
    , io(build(T(std::forward<Ts>(args)...)).io)
  {}

  ch_device(ch_device&& other)
    : base(std::move(other))
    , io(std::move(other.io))
  {}

protected:

  auto&& build(T&& obj) {
    obj.describe();
    this->compile();
    return obj;
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
