#pragma once

#include "port.h"

namespace ch {
namespace internal {

template <typename T, unsigned N> class const_vec;
template <typename T, unsigned N> class ch_vec;

template <unsigned N, typename T>
struct const_vec_traits;

template <unsigned N, typename T>
struct vec_traits;

template <unsigned N, typename ScalarType, typename LogicType>
struct const_vec_traits<N, scalar_traits<ScalarType, LogicType>>  {
  using type = scalar_traits<ch_vec<ScalarType, N>, ch_vec<LogicType, N>>;
};

template <unsigned N, typename LogicType, typename ConstType, typename ValueType, typename ScalarType>
struct const_vec_traits<N, logic_traits<LogicType, ConstType, ValueType, ScalarType>>  {
  using type = logic_traits<const_vec<LogicType, N>, const_vec<LogicType, N>, ch_vec<ValueType, N>, ch_vec<ScalarType, N>>;
};

template <unsigned N, typename IoType, ch_direction Direction, typename FlipType, typename PortType, typename LogicType>
struct const_vec_traits<N, io_traits<IoType, Direction, FlipType, PortType, LogicType>>  {
  using type = io_traits<ch_vec<IoType, N>, Direction, ch_vec<FlipType, N>, ch_vec<PortType, N>, ch_vec<LogicType, N>>;
};

template <unsigned N, typename ScalarType, typename LogicType>
struct vec_traits<N, scalar_traits<ScalarType, LogicType>>  {
  using type = scalar_traits<ch_vec<ScalarType, N>, ch_vec<LogicType, N>>;
};

template <unsigned N, typename LogicType, typename ConstType, typename ValueType, typename ScalarType>
struct vec_traits<N, logic_traits<LogicType, ConstType, ValueType, ScalarType>>  {
  using type = logic_traits<ch_vec<LogicType, N>, const_vec<LogicType, N>, ch_vec<ValueType, N>, ch_vec<ScalarType, N>>;
};

template <unsigned N, typename IoType, ch_direction Direction, typename FlipType, typename PortType, typename LogicType>
struct vec_traits<N, io_traits<IoType, Direction, FlipType, PortType, LogicType>>  {
  using type = io_traits<ch_vec<IoType, N>, Direction, ch_vec<FlipType, N>, ch_vec<PortType, N>, ch_vec<LogicType, N>>;
};

template <typename T, unsigned N>
class const_vec {
public:
  static constexpr unsigned bitsize = N * T::bitsize;
  using traits = typename const_vec_traits<N, typename T::traits>::type;
  using value_type = T;

  const_vec() {}
  const_vec(const const_vec& rhs) : items_(rhs.items_) {}
  const_vec(const_vec&& rhs) : items_(std::move(rhs.items_)) {}

  template <typename U>
  explicit const_vec(const const_vec<U, N>& rhs) {
    this->assign(rhs);
  }

  template <typename... Vs>
  explicit const_vec(const Vs&... values) {
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
  void assign(const const_vec<U, N>& rhs) {
    for (unsigned i = 0; i < N; ++i) {
      items_[i] = rhs[i];
    }
  }

  // TODO: ugly hack to create vec from logic
  template <typename U> class ch_in;
};

template <typename T, unsigned N>
class ch_vec : public const_vec<T, N> {
public:
  static constexpr unsigned bitsize = N * T::bitsize;
  using base = const_vec<T, N>;
  using traits = typename vec_traits<N, typename T::traits>::type;
  using value_type = T;
  using base::operator [];
  using base::items_;

  ch_vec() {}
  ch_vec(const ch_vec& rhs) : base(rhs) {}
  ch_vec(ch_vec&& rhs) : base(rhs) {}

  ch_vec(const const_vec<T, N>& rhs) : base(rhs) {}

  template <typename U>
  explicit ch_vec(const const_vec<U, N>& rhs) : base(rhs) {}

  template <typename U>
  explicit ch_vec(const ch_vec<U, N>& rhs) : base(rhs) {}

  template <typename... Vs>
  explicit ch_vec(const Vs&... values) : base(values...) {}

  ch_vec& operator=(const ch_vec& rhs) {
    items_ = rhs.items_;
    return *this;
  }

  ch_vec& operator=(ch_vec&& rhs) {
    items_ = std::move(rhs.items_);
    return *this;
  }

  template <typename U>
  ch_vec& operator=(const const_vec<U, N>& rhs) {
    this->assign(rhs);
    return *this;
  }

  template <typename U>
  ch_vec& operator=(const ch_vec<U, N>& rhs) {
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

}
}
