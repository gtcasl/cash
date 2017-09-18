#pragma once

#include "reg.h"

namespace cash {
namespace internal {

template <typename T>
class ch_seq;

template <typename T>
struct traits < ch_seq<T> > {
  static constexpr unsigned bitcount = traits<T>::bitcount;
};

template <typename T>
class ch_seq : public traits<T>::const_type {
public:
  using base = typename traits<T>::const_type;
  using value_type = T;

  T next;

  ch_seq() {
    auto reg = ch_reg(next);
    base::operator=(std::move(reg));
    next = *this;
  }
  
  template <typename U,
            CH_REQUIRES(is_cast_convertible<U, T>::value)>
  explicit ch_seq(const U& init) {
    auto reg = ch_reg(next, static_cast<typename reference_cast<U, T>::type>(init));
    base::operator=(std::move(reg));
    next = *this;
  }

  ch_seq(ch_seq&& rhs) {
    reinterpret_cast<base&>(*this) = std::move(reinterpret_cast<T&>(rhs));
    next = std::move(rhs.next);
  }

  ch_seq& operator=(ch_seq&& rhs) {
    reinterpret_cast<base&>(*this) = std::move(reinterpret_cast<T&>(rhs));
    next = std::move(rhs.next);
  }

protected:

  // for readonly access
  ch_seq& operator=(const ch_seq&) = delete;
};

}
}
