#pragma once

#include "reg.h"

namespace cash {
namespace internal {

template <typename T>
class ch_seq : public T {
public:
  using value_type = T;
  using base = ch_bitbase<T::bitcount>;
  using data_type = typename T::data_type;
  using bus_type = typename T::bus_type;

  T next;

  ch_seq() {
    auto reg = ch_reg(next);
    T::operator=(std::move(reg));
    next = *this;
  }
  
  template <typename U,
            CH_REQUIRES(is_weak_convertible<U, T>::value)>
  ch_seq(const U& init) {
    auto reg = ch_reg(next, static_cast<typename reference_cast<U, T>::type>(init));
    T::operator=(std::move(reg));
    next = *this;
  }

  ch_seq(ch_seq&& rhs) {
    reinterpret_cast<T&>(*this) = std::move(reinterpret_cast<T&>(rhs));
    next = std::move(rhs.next);
  }

  ch_seq& operator=(ch_seq&& rhs) {
    reinterpret_cast<T&>(*this) = std::move(reinterpret_cast<T&>(rhs));
    next = std::move(rhs.next);
  }

protected:

  // for readonly access
  ch_seq& operator=(const ch_seq&) = delete;
};

}
}
