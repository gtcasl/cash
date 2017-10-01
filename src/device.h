#pragma once

#include "port.h"

namespace cash {
namespace internal {

class deviceimpl;

class ch_device {
public:

  ch_device();
  virtual ~ch_device();

  ch_device(const ch_device& device);

  ch_device& operator=(const ch_device& device);
    
protected:

  void begin_context(const std::string& name);

  void end_context();

  void compile();

  deviceimpl* impl_;

  friend context* get_ctx(const ch_device& device);
};

context* get_ctx(const ch_device& device);

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class ch_module : public ch_device {
public:

  template <typename... Ts>
  ch_module(const Ts&... args) {
    this->begin_context(typeid(T).name());
    impl_ = new T(args...);
    this->compile();
    this->end_context();
  }

  constexpr const T& operator*() const {
    return *impl_;
  }

  constexpr const T* operator->() const {
    return impl_;
  }

private:
  T* impl_;
};

///////////////////////////////////////////////////////////////////////////////

void toVerilog(std::ostream& out, const std::initializer_list<const ch_device*>& devices);

template <typename... Devices>
void ch_toVerilog(std::ostream& out, const ch_device& device, const Devices&... more) {
  toVerilog(out, {&device, &more...});
}

template <typename... Devices>
void ch_toVerilog(const std::string& file, const ch_device& device, const Devices&... more) {
  std::ofstream out(file);
  toVerilog(out, {&device, &more...});
}

void ch_dumpStats(std::ostream& out, const ch_device& device);

}
}
