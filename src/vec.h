#pragma once

#include "port.h"

namespace ch {
namespace internal {

template <typename T, unsigned N>
class const_vec_base {
public:
  const_vec_base() {}
  const_vec_base(const const_vec_base& rhs) : items_(rhs.items_) {}
  const_vec_base(const_vec_base&& rhs) : items_(std::move(rhs.items_)) {}

  template <typename... Vs, CH_REQUIRES(are_all_cast_convertible<T, Vs...>::value)>
  explicit const_vec_base(const Vs&... values) : items_{T(values)...} {}

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

  template <typename V>
  void init(const V& value) {
    items_[0] = value;
  }

  template <typename V0, typename... Vs>
  void init(const V0& value0, const Vs&... values) {
    items_[sizeof...(Vs)] = value0;
    this->init(values...);
  }
  
  std::array<T, N> items_;
};

template <typename T, unsigned N>
class ch_vec_base : public const_vec_base<T, N> {
public:
  using base = const_vec_base<T, N>;
  using base::operator [];
  using base::items_;

  ch_vec_base() {}
  ch_vec_base(const ch_vec_base& rhs) : base(rhs) {}
  ch_vec_base(ch_vec_base&& rhs) : base(std::move(rhs)) {}
  ch_vec_base(const const_vec_base<T, N>& rhs) : base(rhs) {}

  template <typename... Vs, CH_REQUIRES(are_all_cast_convertible<T, Vs...>::value)>
  explicit ch_vec_base(const Vs&... values) : base(values...) {}

  ch_vec_base& operator=(const ch_vec_base& rhs) {
    items_ = rhs.items_;
    return *this;
  }

  ch_vec_base& operator=(ch_vec_base&& rhs) {
    items_ = std::move(rhs.items_);
    return *this;
  }

  ch_vec_base& operator=(const const_vec_base<T, N>& rhs) {
    items_ = rhs.items_;
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

///////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned N> class ch_logic_vec;

template <typename T, unsigned N>
class ch_logic_const_vec : public const_vec_base<T, N> {
public:
  using traits = logic_traits<N * bitwidth_v<T>,
                              ch_logic_const_vec<logic_type_t<T>, N>,
                              ch_logic_const_vec<logic_type_t<T>, N>,
                              ch_logic_vec<value_type_t<T>, N>,
                              ch_logic_vec<scalar_type_t<T>, N>>;
  using base = const_vec_base<T, N>;
  using base::operator [];
  using base::items_;

  ch_logic_const_vec(const bit_buffer& buffer = bit_buffer(traits::bitwidth))
    : ch_logic_const_vec(buffer, std::make_index_sequence<N>())
  {}

  ch_logic_const_vec(const ch_logic_const_vec& rhs)
    : ch_logic_const_vec(bit_accessor::cloneBuffer(rhs))
  {}

  ch_logic_const_vec(ch_logic_const_vec&& rhs) : base(std::move(rhs)) {}

  template <typename U>
  explicit ch_logic_const_vec(const const_vec_base<U, N>& rhs) {
    this->assign(rhs);
  }

  template <typename __T__, CH_REQUIRES(is_integral_or_enum<__T__>::value)>
  explicit ch_logic_const_vec(__T__ rhs)
    : ch_logic_const_vec(bit_buffer(bitvector(traits::bitwidth, rhs)))
  {}

  explicit ch_logic_const_vec(const ch_scalar<traits::bitwidth>& rhs)
    : ch_logic_const_vec(bit_buffer(scalar_accessor::get_data(rhs)))
  {}

  template <typename... Vs, CH_REQUIRES(are_all_cast_convertible<T, Vs...>::value)>
  explicit ch_logic_const_vec(const Vs&... values)
    : ch_logic_const_vec() {
    this->init(values...);
  }

  CH_BIT_READONLY_INTERFACE(ch_logic_const_vec)

protected:

  template <std::size_t...Is>
  explicit ch_logic_const_vec(const bit_buffer& buffer, std::index_sequence<Is...>)
    : base((bit_buffer(bitwidth_v<T>, buffer, Is * bitwidth_v<T>))...)
  {}

  const bit_buffer& get_buffer() const {
    return bit_accessor::get_buffer(items_[0]);
  }

  bit_buffer& get_buffer() {
    return bit_accessor::get_buffer(items_[0]);
  }

  friend class bit_accessor;
};

template <typename T, unsigned N>
class ch_logic_vec : public ch_logic_const_vec<T, N> {
public:
  using traits = logic_traits<N * bitwidth_v<T>,
                              ch_logic_vec<logic_type_t<T>, N>,
                              ch_logic_const_vec<logic_type_t<T>, N>,
                              ch_logic_vec<value_type_t<T>, N>,
                              ch_logic_vec<scalar_type_t<T>, N>>;
  using base = ch_logic_const_vec<T, N>;
  using base::operator [];
  using base::items_;

  ch_logic_vec(const bit_buffer& buffer = bit_buffer(traits::bitwidth)) : base(buffer) {}
  ch_logic_vec(const ch_logic_const_vec<T, N>& rhs) : base(rhs) {}
  ch_logic_vec(const ch_logic_vec& rhs) : base(rhs) {}
  ch_logic_vec(ch_logic_vec&& rhs) : base(std::move(rhs)) {}

  template <typename U>
  explicit ch_logic_vec(const ch_logic_vec<U, N>& rhs) : base(rhs ) {}

  template <typename __T__, CH_REQUIRES(is_integral_or_enum<__T__>::value)>
  explicit ch_logic_vec(__T__ rhs) : base(rhs) {}

  explicit ch_logic_vec(const ch_scalar<traits::bitwidth>& rhs) : base(rhs) {}

  template <typename... Vs, CH_REQUIRES(are_all_cast_convertible<T, Vs...>::value)>
  explicit ch_logic_vec(const Vs&... values) : base(values...) {}

  ch_logic_vec& operator=(const ch_logic_vec& rhs) {
    ch::internal::bit_accessor::copy(*this, rhs);
    return *this;
  }

  ch_logic_vec& operator=(ch_logic_vec&& rhs) {
    ch::internal::bit_accessor::move(*this, std::move(rhs));
    return *this;
  }

  ch_logic_vec& operator=(const ch_logic_const_vec<T, N>& rhs) {
    ch::internal::bit_accessor::copy(*this, rhs);
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

  CH_BIT_WRITABLE_INTERFACE(ch_logic_vec)
private:
  //--
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned N>
class ch_scalar_vec : public ch_vec_base<T, N> {
public:
  using traits = scalar_traits<N * bitwidth_v<T>,
                               ch_scalar_vec<scalar_type_t<T>, N>,
                               ch_scalar_vec<logic_type_t<T>, N>>;

private:
  //--
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned N>
class ch_io_vec : public ch_vec_base<T, N> {
public:
  using type = io_traits<ch_io_vec<io_type_t<T>, N>,
                         direction_v<T>,
                         ch_io_vec<flip_type_t<T>, N>,
                         ch_io_vec<port_type_t<T>, N>,
                         ch_io_vec<logic_type_t<T>, N>>;

private:
  //--
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned N>
using const_vec = std::conditional_t<is_logic_type<T>::value, ch_logic_const_vec<T, N>,
                      std::conditional_t<is_io_type<T>::value, ch_io_vec<T, N>, ch_scalar_vec<T, N>>>;

template <typename T, unsigned N>
using ch_vec = std::conditional_t<is_logic_type<T>::value, ch_logic_vec<T, N>,
                  std::conditional_t<is_io_type<T>::value, ch_io_vec<T, N>, ch_scalar_vec<T, N>>>;

}
}
