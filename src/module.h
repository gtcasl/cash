#pragma once

#include "port.h"

namespace cash {
namespace internal {

template <typename Derived>
class ch_module {
public:
  using module_type = Derived;

  ch_module() {
    assert(false);
  }

  template <typename... Ts>
  void operator()(Ts&&... args) {
    reinterpret_cast<Derived*>(this)->io(std::forward<Ts>(args)...);
  }

  //--
protected:
  //--
};

#define CH_MODULE(name) \
  struct name : public ch_module<name>

}}
