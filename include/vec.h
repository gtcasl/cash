#pragma once

#include "ioport.h"

namespace ch {
namespace internal {

template <typename T, unsigned N>
class vec_base {
public:
  vec_base() {}
  vec_base(const vec_base& other) : items_(other.items_) {}
  vec_base(vec_base&& other) : items_(std::move(other.items_)) {}

  vec_base& operator=(const vec_base& other) {
    items_ = other.items_;
    return *this;
  }

  vec_base& operator=(vec_base&& other) {
    for (unsigned i = 0; i < N; ++i) {
      items_[i] = std::move(other.items_[i]);
    }
    return *this;
  }

  template <typename U>
  vec_base& operator=(const vec_base<U, N>& other) {
    static_assert(std::is_constructible_v<T, U>, "invalid type");
    for (unsigned i = 0; i < N; ++i) {
      items_[i] = other.items_[i];
    }
    return *this;
  }

  const T& at(size_t i) const {
    CH_CHECK(i < N, "invalid subscript index");
    return items_[i];
  }

  T& at(size_t i) {
    CH_CHECK(i < N, "invalid subscript index");
    return items_[i];
  }

  const T& operator[](size_t i) const {
    return this->at(i);
  }

  T& operator[](size_t i) {
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

  auto begin() {
    return items_.begin();
  }

  auto cbegin() const {
    return items_.cbegin();
  }

  auto end() const {
    return items_.cend();
  }

  auto end() {
    return items_.end();
  }

  auto cend() const {
    return items_.cend();
  }

  auto rbegin() const {
    return items_.crbegin();
  }

  auto rbegin() {
    return items_.rbegin();
  }

  auto crbegin() const {
    return items_.crbegin();
  }

  auto rend() const {
    return items_.crend();
  }

  auto rend() {
    return items_.rend();
  }

  auto crend() const {
    return items_.crend();
  }

  auto size() const {
    return items_.size();
  }

  auto empty() const {
    return items_.empty();
  }auto front() {
    return items_.front();
  }

  auto back() {
    return items_.back();
  }

  template <typename U>
  void fill(const U& value) {
    for (unsigned i = 0; i < N; ++i) {
      items_[i] = value;
    }
  }

protected:

  template <typename... Ts,
            CH_REQUIRE_0(sizeof...(Ts) == N && are_all_constructible_v<T, Ts...>)>
  vec_base(Ts&&... values)
    : items_{T(std::forward<Ts>(values))...}
  {}

  template <typename... Ts,
            CH_REQUIRE_0(sizeof...(Ts) == N && are_all_constructible_v<T, Ts...>)>
  vec_base(const source_location& sloc, Ts&&... values)
    : items_{T(std::forward<Ts>(values), sloc)...}
  {}

  template <typename U, std::size_t...Is>
  vec_base(const U& other, std::index_sequence<Is...>)
    : items_{T(other[Is])...}
  {}
  
  std::array<T, N> items_;
};

template <typename T, unsigned N, typename Enable = void>
class ch_vec {};

///////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned N>
class ch_vec<T, N, std::enable_if_t<is_logic_only_v<T>>> : public vec_base<T, N> {
public:
  using traits = logic_traits<N * ch_width_v<T>,
                              false,
                              ch_vec,
                              ch_vec<ch_scalar_t<T>, N>>;
  using base = vec_base<T, N>;
  using base::operator [];
  using base::items_;

  explicit ch_vec(const logic_buffer& buffer = logic_buffer(traits::bitwidth, CH_CUR_SLOC))
    : ch_vec(buffer, std::make_index_sequence<N>(), buffer.data().sloc())
  {}

  ch_vec(const ch_vec& other, CH_SLOC)
    : ch_vec(logic_accessor::copy(other, sloc))
  {}

  ch_vec(ch_vec&& other) : base(std::move(other))
  {}

  template <typename U,
            CH_REQUIRE_0(std::is_constructible_v<T, U>)>
  explicit ch_vec(const vec_base<U, N>& other, CH_SLOC)
    : ch_vec(logic_accessor::copy(other, sloc))
  {}

  template <typename U,
            CH_REQUIRE_0(is_logic_type_v<U>)>
  explicit ch_vec(const U& other, CH_SLOC)
    : ch_vec(logic_accessor::copy(other, sloc)) {
    static_assert(ch_width_v<U> == N * ch_width_v<T>, "invalid size");
  }

  template <typename U,
            CH_REQUIRE_1(is_scalar_type_v<U>)>
  explicit ch_vec(const U& other, CH_SLOC)
    : ch_vec(logic_buffer(scalar_accessor::data(other), sloc)) {
    static_assert(ch_width_v<U> == N * ch_width_v<T>, "invalid size");
  }

  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  explicit ch_vec(U other, CH_SLOC)
    : ch_vec(logic_buffer(bitvector(traits::bitwidth, other), sloc))
  {}

  template <typename U>
  explicit ch_vec(const std::initializer_list<U>& values, CH_SLOC)
    : ch_vec(logic_buffer(traits::bitwidth, sloc)) {
    assert(values.size() == N);
    int i = N - 1;
    for (auto& value : values) {
      items_[i--] = value;
    }
  }

  ch_vec& operator=(const ch_vec& other) {
    logic_accessor::copy(*this, other);
    return *this;
  }

  ch_vec& operator=(ch_vec&& other) {
    logic_accessor::move(*this, std::move(other));
    return *this;
  }

  template <typename U,
            CH_REQUIRE_0(is_scalar_type_v<U>)>
  ch_vec& operator=(const U& other) {
    static_assert(ch_width_v<U> == N * ch_width_v<T>, "invalid size");
    this->buffer().write(scalar_accessor::data(other));
    return *this;
  }

  template <typename U,
            CH_REQUIRE_1(is_logic_type_v<U>)>
  ch_vec& operator=(const U& other) {
    static_assert(ch_width_v<U> == N * ch_width_v<T>, "invalid size");
    logic_accessor::copy(*this, other);
    return *this;
  }

  CH_LOGIC_INTERFACE(ch_vec)

protected:

  template <std::size_t...Is>
  ch_vec(const logic_buffer& buffer, std::index_sequence<Is...>, const source_location& sloc)
    : base(logic_buffer(ch_width_v<T>, buffer, Is * ch_width_v<T>, sloc)...)
  {}

  logic_buffer buffer() const {
    return logic_accessor::buffer(items_[0]).source();
  }

  friend class logic_accessor;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned N>
class ch_vec<T, N, std::enable_if_t<is_scalar_only_v<T>>> : public vec_base<T, N> {
public:
  using traits = scalar_traits<N * ch_width_v<T>,
                               false,
                               ch_vec,
                               ch_vec<ch_logic_t<T>, N>>;
  using base = vec_base<T, N>;
  using base::operator [];
  using base::items_;

  explicit ch_vec(const scalar_buffer_ptr& buffer = make_scalar_buffer(traits::bitwidth))
    : ch_vec(buffer, std::make_index_sequence<N>())
  {}

  ch_vec(const ch_vec& other)
    : ch_vec(scalar_accessor::copy(other))
  {}

  ch_vec(ch_vec&& other) : base(std::move(other)) {}

  template <typename U,
            CH_REQUIRE_0(std::is_constructible_v<T, U>)>
  explicit ch_vec(const vec_base<U, N>& other)
    : ch_vec(scalar_accessor::copy(other))
  {}

  template <typename U,
              CH_REQUIRE_0(is_scalar_type_v<U>)>
  explicit ch_vec(const U& other)
    : ch_vec(scalar_accessor::copy(other)) {
    static_assert(ch_width_v<U> == N * ch_width_v<T>, "invalid size");
  }

  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  explicit ch_vec(U other)
    : ch_vec(make_scalar_buffer(bitvector(traits::bitwidth, other)))
  {}

  template <typename U>
  explicit ch_vec(const std::initializer_list<U>& values, CH_SLOC)
    : ch_vec(make_scalar_buffer(traits::bitwidth)) {
    assert(values.size() == N);
    int i = N - 1;
    for (auto& value : values) {
      items_[i--] = value;
    }
  }

  ch_vec& operator=(const ch_vec& other) {
    scalar_accessor::copy(*this, other);
    return *this;
  }

  ch_vec& operator=(ch_vec&& other) {
    scalar_accessor::move(*this, std::move(other));
    return *this;
  }

  template <typename U,
            CH_REQUIRE_0(is_scalar_type_v<U>)>
  ch_vec& operator=(const U& other) {
    static_assert(ch_width_v<U> == N * ch_width_v<T>, "invalid size");
    scalar_accessor::copy(*this, other);
    return *this;
  }

  CH_SCALAR_INTERFACE(ch_vec)

protected:

  template <std::size_t...Is>
  ch_vec(const scalar_buffer_ptr& buffer, std::index_sequence<Is...>)
    : base(make_scalar_buffer(ch_width_v<T>, buffer, Is * ch_width_v<T>)...)
  {}

  const scalar_buffer_ptr& buffer() const {
    return scalar_accessor::buffer(items_[0])->source();
  }

  friend class scalar_accessor;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned N>
class ch_vec<T, N, std::enable_if_t<is_logic_io_v<T>>> : public vec_base<T, N> {
public:
  static_assert(is_logic_io_v<T>, "invalid type");
  using traits = logic_io_traits<N * ch_width_v<T>,
                                 ch_direction_v<T>,
                                 ch_vec,
                                 ch_vec<ch_flip_io<T>, N>,
                                 ch_vec<ch_scalar_io<T>, N>>;
  using base = vec_base<T, N>;
  using base::operator [];
  using base::items_;

  explicit ch_vec(const std::string& name = "io", CH_SLOC)
    : ch_vec(name, sloc, std::make_index_sequence<N>())
  {}

  explicit ch_vec(const typename traits::flip_io& other, CH_SLOC)
    : ch_vec(other, sloc, std::make_index_sequence<N>())
  {}

  explicit ch_vec(const ch_vec& other, CH_SLOC)
    : ch_vec(other, sloc, std::make_index_sequence<N>())
  {}

  ch_vec(ch_vec&& other) : base(std::move(other)) {}

  void operator()(typename traits::flip_io& other) {
    for (unsigned i = 0, n = items_.size(); i < n; ++i) {
      items_[i](other[i]);
    }
  }

protected:

  ch_vec& operator=(const ch_vec& other) = delete;
  ch_vec& operator=(ch_vec&& other) = delete;

  template <std::size_t...Is>
  ch_vec(const std::string& name, const source_location& sloc, std::index_sequence<Is...>)
    : base(sloc, stringf("%s_%d", name.c_str(), Is)...)
  {}

  template <typename U, std::size_t...Is>
  ch_vec(const vec_base<U, N>& other, const source_location& sloc, std::index_sequence<Is...>)
    : base(sloc, other[Is]...)
  {}
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned N>
class ch_vec<T, N, std::enable_if_t<is_scalar_io_v<T>>> : public vec_base<T, N> {
public:
  static_assert(is_scalar_io_v<T>, "invalid type");
  using traits = scalar_io_traits<N * ch_width_v<T>,
                                  ch_direction_v<T>,
                                  ch_vec,
                                  ch_vec<ch_flip_io<T>, N>,
                                  ch_vec<ch_logic_io<T>, N>>;
  using base = vec_base<T, N>;
  using base::operator [];
  using base::items_;

  explicit ch_vec(const typename traits::logic_io& other)
    : ch_vec(other, std::make_index_sequence<N>())
  {}

  explicit ch_vec(const ch_vec& other)
    : ch_vec(other, std::make_index_sequence<N>())
  {}

  ch_vec(ch_vec&& other) : base(std::move(other)) {}

  void operator()(typename traits::flip_io& other) {
    for (unsigned i = 0, n = items_.size(); i < n; ++i) {
      items_[i](other[i]);
    }
  }

protected:

  ch_vec& operator=(const ch_vec& other) = delete;
  ch_vec& operator=(ch_vec&& other) = delete;

  template <typename U, std::size_t...Is>
  ch_vec(const vec_base<U, N>& other, std::index_sequence<Is...>)
    : base(other[Is]...)
  {}
};

}
}
