#pragma once

#include "port.h"

namespace ch {
namespace internal {

class moduleimpl;

class module {
public:
  module(size_t signature, const char* name);
  virtual ~module();
    
protected:

  void end_context();

  moduleimpl* impl_;

  friend context* get_ctx(const module& module);
};

context* get_ctx(const module& module);

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class ch_module final : public module {
private:
  T impl_;

public:  
  typename decltype(impl_.io)::port_type io;

  template <typename... Ts>
  ch_module(const char* name, const Ts&... args)
    : module(typeid(T).hash_code(), name)
    , impl_(args...)
    , io(impl_.io) {
    impl_.describe();
    this->end_context();
  }

  template <typename... Ts>
  ch_module(const Ts&... args)
    : module(typeid(T).hash_code(), identifier_from_typeid(typeid(T).name()).c_str())
    , impl_(args...)
    , io(impl_.io) {
    impl_.describe();
    this->end_context();
  }
};

}
}
