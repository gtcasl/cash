#pragma once

#include "port.h"

namespace ch {
namespace internal {

template <typename T, unsigned N, typename Enable = void>
class const_vec {};

template <typename T, unsigned N, typename Enable = void>
class ch_vec {};

template <typename T, unsigned N>
class const_vec_base {
public:
  const_vec_base() {}
  const_vec_base(const const_vec_base& rhs) : items_(rhs.items_) {}
  const_vec_base(const_vec_base&& rhs) : items_(std::move(rhs.items_)) {}

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

  template <typename... Ts,
            CH_REQUIRE_0(sizeof...(Ts) == N && are_all_cast_convertible<T, Ts...>::value)>
  explicit const_vec_base(Ts&&... values)
    : items_{T(std::forward<Ts>(values))...}
  {}

  template <typename... Ts,
            CH_REQUIRE_0(sizeof...(Ts) == N && are_all_cast_convertible<T, Ts...>::value)>
  explicit const_vec_base(const source_location& sloc, Ts&&... values)
    : items_{T(std::forward<Ts>(values), sloc)...}
  {}
  
  std::array<T, N> items_;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned N>
class vec_base : public const_vec_base<T, N> {
public:
  using base = const_vec_base<T, N>;
  using base::operator [];
  using base::items_;

  vec_base() {}
  vec_base(const vec_base& rhs) : base(rhs) {}
  vec_base(vec_base&& rhs) : base(std::move(rhs)) {}

  vec_base& operator=(const vec_base& rhs) {
    items_ = rhs.items_;
    return *this;
  }

  vec_base& operator=(vec_base&& rhs) {
    items_ = std::move(rhs.items_);
    return *this;
  }

  vec_base& operator=(const const_vec_base<T, N>& rhs) {
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

protected:

  vec_base(const const_vec_base<T, N>& rhs) : base(rhs) {}

  template <typename... Ts,
            CH_REQUIRE_0(sizeof...(Ts) == N && are_all_cast_convertible<T, Ts...>::value)>
  explicit vec_base(Ts&&... values) : base(std::forward<Ts>(values)...) {}

  template <typename... Ts,
            CH_REQUIRE_0(sizeof...(Ts) == N && are_all_cast_convertible<T, Ts...>::value)>
  explicit vec_base(const source_location& sloc, Ts&&... values) : base(sloc, std::forward<Ts>(values)...) {}
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned N>
class const_vec<T, N, typename std::enable_if_t<is_logic_type<T>::value>>
    : public const_vec_base<T, N> {
public:
  static_assert(is_logic_type<T>::value, "invalid value type");
  static_assert(!is_const_type<T>::value, "invalid value type");
  using traits = logic_traits<N * width_v<T>,
                              const_vec,
                              const_vec,
                              ch_vec<T, N>,
                              const_vec<scalar_type_t<T>, N>>;
  using base = const_vec_base<T, N>;
  using base::operator [];
  using base::items_;

  const_vec(const bit_buffer& buffer = bit_buffer(traits::bitwidth, CH_SOURCE_LOCATION))
    : const_vec(buffer, std::make_index_sequence<N>())
  {}

  const_vec(const const_vec& rhs, const source_location& sloc = CH_SOURCE_LOCATION)
    : const_vec(bit_accessor::copy_buffer(rhs, sloc))
  {}

  const_vec(const_vec&& rhs) : base(std::move(rhs))
  {}

  explicit const_vec(const const_bit<traits::bitwidth>& rhs,
                     const source_location& sloc = CH_SOURCE_LOCATION)
    : const_vec(bit_accessor::copy_buffer(rhs, sloc))
  {}

  explicit const_vec(const const_scalar<traits::bitwidth>& rhs,
                     const source_location& sloc = CH_SOURCE_LOCATION)
    : const_vec(bit_buffer(scalar_accessor::get_data(rhs), sloc))
  {}

  template <typename U, CH_REQUIRE_0(std::is_integral_v<U>)>
  explicit const_vec(U rhs, const source_location& sloc = CH_SOURCE_LOCATION)
    : const_vec(bit_buffer(bitvector(traits::bitwidth, rhs), sloc))
  {}

  template <typename U>
  explicit const_vec(const std::initializer_list<U>& values,
                     const source_location& sloc = CH_SOURCE_LOCATION)
    : const_vec(bit_buffer(traits::bitwidth, sloc)) {
    assert(values.size() == N);
    int i = N - 1;
    for (auto& value : values) {
      items_[i--] = value;
    }
  }

  CH_LOGIC_READONLY_INTERFACE(const_vec)

protected:

  template <typename V>
  void init(const V& value) {
    bit_accessor::copy(
        items_[0],
        static_cast<aggregate_init_cast_t<T, V>>(value));
  }

  template <typename V0, typename... Vs>
  void init(const V0& value0, const Vs&... values) {
    bit_accessor::copy(
        items_[sizeof...(Vs)],
        static_cast<aggregate_init_cast_t<T, V0>>(value0));
    this->init(values...);
  }

  template <std::size_t...Is>
  explicit const_vec(const bit_buffer& buffer, std::index_sequence<Is...>)
    : base(bit_buffer(width_v<T>, buffer, Is * width_v<T>)...)
  {}

  const bit_buffer_ptr& get_buffer() const {
    return bit_accessor::get_buffer(items_[0])->get_source();
  }

  bit_buffer_ptr& get_buffer() {
    return bit_accessor::get_buffer(items_[0])->get_source();
  }

  friend class bit_accessor;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned N>
class ch_vec<T, N, typename std::enable_if_t<is_logic_type<T>::value>>
    : public const_vec<T, N> {
public:
  static_assert(is_logic_type<T>::value, "invalid value type");
  static_assert(!is_const_type<T>::value, "invalid value type");
  using traits = logic_traits<N * width_v<T>,
                              ch_vec,
                              const_vec<T, N>,
                              ch_vec,
                              ch_vec<scalar_type_t<T>, N>>;
  using base = const_vec<T, N>;
  using base::operator [];
  using base::items_;

  ch_vec(const bit_buffer& buffer = bit_buffer(traits::bitwidth, CH_SOURCE_LOCATION))
    : base(buffer)
  {}

  ch_vec(const ch_vec& rhs, const source_location& sloc = CH_SOURCE_LOCATION)
    : base(rhs, sloc)
  {}

  ch_vec(ch_vec&& rhs) : base(std::move(rhs)) {}

  template <typename U>
  explicit ch_vec(const const_vec<U, N>& rhs,
                  const source_location& sloc = CH_SOURCE_LOCATION)
    : base(rhs, sloc)
  {}

  explicit ch_vec(const const_bit<traits::bitwidth>& rhs,
                  const source_location& sloc = CH_SOURCE_LOCATION)
    : base(rhs, sloc)
  {}

  explicit ch_vec(const const_scalar<traits::bitwidth>& rhs,
                  const source_location& sloc = CH_SOURCE_LOCATION)
    : base(rhs, sloc)
  {}

  template <typename U, CH_REQUIRE_0(std::is_integral_v<U>)>
  explicit ch_vec(U rhs,
                  const source_location& sloc = CH_SOURCE_LOCATION)
    : base(rhs, sloc)
  {}

  template <typename U>
  explicit ch_vec(const std::initializer_list<U>& values,
                  const source_location& sloc = CH_SOURCE_LOCATION)
    : base(values, sloc)
  {}

  ch_vec& operator=(const ch_vec& rhs) {
    bit_accessor::copy(*this, rhs);
    return *this;
  }

  ch_vec& operator=(ch_vec&& rhs) {
    bit_accessor::move(*this, std::move(rhs));
    return *this;
  }

  ch_vec& operator=(const const_vec<T, N>& rhs) {
    bit_accessor::copy(*this, rhs);
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

  CH_LOGIC_WRITABLE_INTERFACE(ch_vec)
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned N>
class const_vec<T, N, typename std::enable_if_t<is_scalar_type<T>::value>>
    : public const_vec_base<T, N> {
public:
  static_assert(is_scalar_type<T>::value, "invalid value type");
  static_assert(!is_const_type<T>::value, "invalid value type");
  using traits = scalar_traits<N * width_v<T>,
                               const_vec,
                               const_vec,
                               ch_vec<T, N>,
                               const_vec<logic_type_t<T>, N>>;
  using base = const_vec_base<T, N>;
  using base::operator [];
  using base::items_;

  const_vec(const scalar_buffer& buffer = scalar_buffer(traits::bitwidth))
    : const_vec(buffer, std::make_index_sequence<N>())
  {}

  const_vec(const const_vec& rhs)
    : const_vec(scalar_accessor::copy_buffer(rhs))
  {}

  const_vec(const_vec&& rhs) : base(std::move(rhs)) {}

  template <typename U>
  explicit const_vec(const const_vec<U, N>& rhs)
    : const_vec(scalar_accessor::copy_buffer(rhs))
  {}

  explicit const_vec(const const_scalar<traits::bitwidth>& rhs)
    : const_vec(scalar_accessor::copy_buffer(rhs))
  {}

  template <typename U, CH_REQUIRE_0(std::is_integral_v<U>)>
  explicit const_vec(U rhs)
    : const_vec(scalar_buffer(bitvector(traits::bitwidth, rhs)))
  {}

  template <typename... Vs,
            CH_REQUIRE_0(sizeof...(Vs) == N && are_all_cast_convertible<T, Vs...>::value)>
  explicit const_vec(Vs&&... values) : const_vec() {
    this->init(std::forward<Vs>(values)...);
  }

  CH_SCALAR_READONLY_INTERFACE(const_vec)

protected:

  template <typename V>
  void init(const V& value) {
    scalar_accessor::copy(
        items_[0],
        static_cast<aggregate_init_cast_t<T, V>>(value));
  }

  template <typename V0, typename... Vs>
  void init(const V0& value0, const Vs&... values) {
    scalar_accessor::copy(
        items_[sizeof...(Vs)],
        static_cast<aggregate_init_cast_t<T, V0>>(value0));
    this->init(values...);
  }

  template <std::size_t...Is>
  explicit const_vec(const scalar_buffer& buffer, std::index_sequence<Is...>)
    : base(scalar_buffer(width_v<T>, buffer, Is * width_v<T>)...)
  {}

  const scalar_buffer_ptr& get_buffer() const {
    return scalar_accessor::get_buffer(items_[0])->get_source();
  }

  scalar_buffer_ptr& get_buffer() {
    return scalar_accessor::get_buffer(items_[0])->get_source();
  }

  friend class scalar_accessor;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned N>
class ch_vec<T, N, typename std::enable_if_t<is_scalar_type<T>::value>>
    : public const_vec<T, N> {
public:
  static_assert(is_scalar_type<T>::value, "invalid value type");
  static_assert(!is_const_type<T>::value, "invalid value type");
  using traits = scalar_traits<N * width_v<T>,
                               ch_vec,
                               const_vec<T, N>,
                               ch_vec,
                               ch_vec<logic_type_t<T>, N>>;
  using base = const_vec<T, N>;
  using base::operator [];
  using base::items_;

  ch_vec(const scalar_buffer& buffer = scalar_buffer(traits::bitwidth)) : base(buffer) {}
  ch_vec(const ch_vec& rhs) : base(rhs) {}
  ch_vec(ch_vec&& rhs) : base(std::move(rhs)) {}

  template <typename U>
  explicit ch_vec(const const_vec<U, N>& rhs) : base(rhs) {}

  explicit ch_vec(const const_scalar<traits::bitwidth>& rhs) : base(rhs) {}

  template <typename U, CH_REQUIRE_0(std::is_integral_v<U>)>
  explicit ch_vec(U rhs) : base(rhs) {}

  template <typename... Vs,
            CH_REQUIRE_0(sizeof...(Vs) == N && are_all_cast_convertible<T, Vs...>::value)>
  explicit ch_vec(Vs&&... values) : base(std::forward<Vs>(values)...) {}

  ch_vec& operator=(const ch_vec& rhs) {
    scalar_accessor::copy(*this, rhs);
    return *this;
  }

  ch_vec& operator=(ch_vec&& rhs) {
    scalar_accessor::move(*this, std::move(rhs));
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

  CH_SCALAR_WRITABLE_INTERFACE(ch_vec)
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned N>
class ch_vec_device_io : public vec_base<device_type_t<T>, N> {
public:
  static_assert(is_io_type<T>::value, "invalid type");
  using traits = io_traits<ch_vec_device_io,
                           direction_v<T>,
                           ch_vec_device_io<flip_type_t<T>, N>,
                           ch_vec<T, N>,
                           ch_vec<logic_type_t<T>, N>>;

  using base = vec_base<device_type_t<T>, N>;
  using base::operator [];

  ch_vec_device_io(const ch_vec<T, N>& rhs)
    : ch_vec_device_io(rhs, std::make_index_sequence<N>())
  {}

protected:

  ch_vec_device_io(const ch_vec_device_io& rhs) = delete;
  ch_vec_device_io(ch_vec_device_io&& rhs) = delete;

  ch_vec_device_io& operator=(const ch_vec_device_io& rhs) = delete;
  ch_vec_device_io& operator=(ch_vec_device_io&& rhs) = delete;

  template <typename U, std::size_t...Is>
  explicit ch_vec_device_io(const vec_base<U, N>& rhs,
                            std::index_sequence<Is...>)
    : base(rhs[Is]...)
  {}
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned N>
class ch_vec<T, N, typename std::enable_if_t<is_io_type<T>::value>>
    : public vec_base<T, N> {
public:
  static_assert(is_io_type<T>::value, "invalid type");
  using traits = io_traits<ch_vec,
                           direction_v<T>,
                           ch_vec<flip_type_t<T>, N>,
                           ch_vec_device_io<T, N>,
                           ch_vec<logic_type_t<T>, N>>;

  using base = vec_base<T, N>;
  using base::operator [];
  using base::items_;

  ch_vec(const std::string& name = "io", const source_location& sloc = CH_SOURCE_LOCATION)
    : ch_vec(name, sloc, std::make_index_sequence<N>())
  {}

  ch_vec(const ch_vec<flip_type_t<T>, N>& rhs, const source_location& sloc = CH_SOURCE_LOCATION)
    : ch_vec(rhs, sloc, std::make_index_sequence<N>())
  {}

  void operator()(typename traits::flip_type& rhs) {
    for (unsigned i = 0, n = items_.size(); i < n; ++i) {
      items_[i](rhs[i]);
    }
  }

protected:

  ch_vec(const ch_vec& rhs) = delete;
  ch_vec(ch_vec&& rhs) = delete;

  ch_vec& operator=(const ch_vec& rhs) = delete;
  ch_vec& operator=(ch_vec&& rhs) = delete;

  template <std::size_t...Is>
  explicit ch_vec(const std::string& name,
                  const source_location& sloc,
                  std::index_sequence<Is...>)
    : base(sloc, fstring("%s_%d", name.c_str(), Is)...)
  {}

  template <typename U, std::size_t...Is>
  explicit ch_vec(const vec_base<U, N>& rhs,
                  const source_location& sloc,
                  std::index_sequence<Is...>)
    : base(sloc, rhs[Is]...)
  {}
};

}
}
