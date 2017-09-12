#pragma once

#include "port.h"

namespace cash {
namespace internal {

template <typename Derived>
class ch_module {
public:
  using module_type = Derived;

  template <typename... Ts>
  void operator()(Ts&&... args) {
    reinterpret_cast<Derived*>(this)->io(std::forward<Ts>(args)...);
  }

  //--
protected:
  //--
};

}}
