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

  device(const device& rhs);

  device(device&& rhs);

  device& operator=(const device& rhs);

  device& operator=(device&& rhs);

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

template <typename T>
class device_base : public device {
public:
  using base = device;

  template <typename... Ts>
  device_base(const std::type_index& signature, const std::string& name, Ts&&... args)
    : device(signature, name) {
    obj_ = std::make_shared<T>(args...);
    obj_->describe();
    this->compile();
  }

  device_base(const device_base& rhs)
    : base(rhs)
    , obj_(rhs.obj_)
  {}

  device_base(device_base&& rhs)
    : base(std::move(rhs))
    , obj_(std::move(rhs.obj_))
  {}

  device_base& operator=(const device_base& rhs) {
    base::operator=(rhs);
    obj_ = rhs.obj_;
    return *this;
  }

  device_base& operator=(device_base&& rhs) {
    base::operator=(std::move(rhs));
    obj_ = std::move(rhs.obj_);
    return *this;
  }

protected:

  std::shared_ptr<T> obj_;
};

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
    : base(std::type_index(typeid(T)), name, std::forward<Ts>(args)...)
    , io(obj_->io)
  {}

  template <typename... Ts>
  ch_device(Ts&&... args)
    : base(std::type_index(typeid(T)),
           identifier_from_typeid(typeid(T).name()).c_str(),
           std::forward<Ts>(args)...)
    , io(obj_->io)
  {}

  ch_device(ch_device&& rhs) : base(std::move(rhs)), io(std::move(rhs.io)) {}

  ch_device& operator=(ch_device&& rhs) {
    base::operator=(std::move(rhs));
    io = std::move(rhs.io);
    return *this;
  }

protected:

  ch_device(const ch_device& rhs) = delete;

  ch_device& operator=(const ch_device& rhs) = delete;
};

///////////////////////////////////////////////////////////////////////////////

void ch_stats(std::ostream& out, const device& device);

}
}
