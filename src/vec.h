#pragma once

#include "port.h"

namespace ch {
namespace internal {

template <typename T, unsigned N> class const_vec_base;
template <typename T, unsigned N> class ch_vec_base;

template <typename T, unsigned N>
class const_vec_base {
public:
  static constexpr unsigned bitsize = N * T::bitsize;

  const_vec_base() {}
  const_vec_base(const const_vec_base& rhs) : items_(rhs.items_) {}
  const_vec_base(const_vec_base&& rhs) : items_(std::move(rhs.items_)) {}

  template <typename U>
  explicit const_vec_base(const const_vec_base<U, N>& rhs) {
    this->assign(rhs);
  }

  template <typename... Vs,
            CH_REQUIRES(are_all_cast_convertible<T, Vs...>::value)>
  explicit const_vec_base(const Vs&... values) {
    this->init(values...);
  }

  const T& at(size_t i) const {
    CH_CHECK(i < N, "invalid subscript index");
    return items_[i];
  }

  const T& operator[](size_t i) const {
    return this->at(i);
  }

  auto front() const {
    return items_.front();
  }

  auto back() const {
    return items_.back();
  }

  auto begin() const {
    return items_.cbegin();
  }

  auto cbegin() const {
    return items_.cbegin();
  }

  auto end() const {
    return items_.cend();
  }

  auto cend() const {
    return items_.cend();
  }

  auto rbegin() const {
    return items_.crbegin();
  }

  auto crbegin() const {
    return items_.crbegin();
  }

  auto rend() const {
    return items_.crend();
  }

  auto crend() const {
    return items_.crend();
  }

  auto size() const {
    return items_.size();
  }

  auto empty() const {
    return items_.empty();
  }

protected:
  
  std::array<T, N> items_;

  template <typename V>
  void init(const V& value) {
    items_[0] = value;
  }

  template <typename V0, typename... Vs>
  void init(const V0& value0, const Vs&... values) {
    items_[sizeof...(Vs)] = value0;
    this->init(values...);
  }

  template <typename U>
  void assign(const const_vec_base<U, N>& rhs) {
    for (unsigned i = 0; i < N; ++i) {
      items_[i] = rhs[i];
    }
  }

  // TODO: ugly hack to create vec from logic
  template <typename U> class ch_in;
};

template <typename T, unsigned N>
class ch_vec_base : public const_vec_base<T, N> {
public:
  using base = const_vec_base<T, N>;
  using base::operator [];
  using base::items_;

  ch_vec_base() {}
  ch_vec_base(const ch_vec_base& rhs) : base(rhs) {}
  ch_vec_base(ch_vec_base&& rhs) : base(rhs) {}

  ch_vec_base(const const_vec_base<T, N>& rhs) : base(rhs) {}

  template <typename U>
  explicit ch_vec_base(const const_vec_base<U, N>& rhs) : base(rhs) {}

  template <typename U>
  explicit ch_vec_base(const ch_vec_base<U, N>& rhs) : base(rhs) {}

  template <typename... Vs,
            CH_REQUIRES(are_all_cast_convertible<T, Vs...>::value)>
  explicit ch_vec_base(const Vs&... values) : base(values...) {}

  ch_vec_base& operator=(const ch_vec_base& rhs) {
    items_ = rhs.items_;
    return *this;
  }

  ch_vec_base& operator=(ch_vec_base&& rhs) {
    items_ = std::move(rhs.items_);
    return *this;
  }

  template <typename U>
  ch_vec_base& operator=(const const_vec_base<U, N>& rhs) {
    this->assign(rhs);
    return *this;
  }

  template <typename U>
  ch_vec_base& operator=(const ch_vec_base<U, N>& rhs) {
    this->assign(rhs);
    return *this;
  }

  T& at(size_t i) {
    CH_CHECK(i < N, "invalid subscript index");
    return items_[i];
  }

  T& operator[](size_t i) {
    return this->at(i);
  }

  auto front() {
    return items_.front();
  }

  auto back() {
    return items_.back();
  }

  auto begin() {
    return items_.begin();
  }

  auto end() {
    return items_.end();
  }

  auto rbegin() {
    return items_.rbegin();
  }

  auto rend() {
    return items_.rend();
  }

  template <typename U>
  void fill(const U& value) {
    for (unsigned i = 0; i < N; ++i) {
      items_[i] = value;
    }
  }
};

template <typename T, unsigned N>
class ch_scalar_vec : public ch_vec_base<T, N> {
public:
  using type = scalar_traits<ch_scalar_vec<scalar_type_t<T>, N>, ch_scalar_vec<logic_type_t<T>, N>>;

private:
  //--
};

template <typename T, unsigned N> class ch_logic_vec;

template <typename T, unsigned N>
class ch_logic_const_vec : public const_vec_base<T, N> {
public:
  using type = logic_traits<ch_logic_const_vec<logic_type_t<T>, N>, ch_logic_const_vec<logic_type_t<T>, N>, ch_logic_vec<value_type_t<T>, N>, ch_logic_vec<scalar_type_t<T>, N>>;

private:
  //--
};

template <typename T, unsigned N>
class ch_logic_vec : public ch_vec_base<T, N> {
public:
  using type = logic_traits<ch_logic_vec<logic_type_t<T>, N>, ch_logic_const_vec<logic_type_t<T>, N>, ch_logic_vec<value_type_t<T>, N>, ch_logic_vec<scalar_type_t<T>, N>>;

private:
  //--
};

template <typename T, unsigned N>
class ch_io_vec : public ch_vec_base<T, N> {
public:
  using type = io_traits<ch_io_vec<io_type_t<T>, N>, direction_v<T>, ch_io_vec<flip_type_t<T>, N>, ch_io_vec<port_type_t<T>, N>, ch_io_vec<logic_type_t<T>, N>>;

private:
  //--
};

template <typename T, unsigned N>
using const_vec = std::conditional_t<is_logic_type<T>::value, ch_logic_const_vec<T, N>,
                      std::conditional_t<is_io_type<T>::value, ch_io_vec<T, N>, ch_scalar_vec<T, N>>>;

template <typename T, unsigned N>
using ch_vec = std::conditional_t<is_logic_type<T>::value, ch_logic_vec<T, N>,
                  std::conditional_t<is_io_type<T>::value, ch_io_vec<T, N>, ch_scalar_vec<T, N>>>;

}
}
