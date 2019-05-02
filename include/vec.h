#pragma once

#include "ioport.h"

namespace ch {
namespace internal {

template <typename T, unsigned N>
class vec_base : public std::array<T, N> {
protected:
  using base = std::array<T, N>;
  static const std::size_t array_size = N;

  template <typename... Us,
            CH_REQUIRE_0(sizeof...(Us) == N && is_fold_constructible_v<T, Us...>)>
  vec_base(Us&&... values)
    : base{T(std::forward<Us>(values))...}
  {}

  template <typename U, std::size_t...Is>
  vec_base(const U& other, std::index_sequence<Is...>)
    : base{T(other[Is])...}
  {}

public:
  vec_base() {}
  vec_base(const vec_base& other) : base(other) {}
  vec_base(vec_base&& other) : base(std::move(other)) {}

  template <typename U>
  vec_base& operator=(const vec_base<U, N>& other) {
    static_assert(std::is_constructible_v<T, U>, "invalid type");
    for (unsigned i = 0; i < N; ++i) {
      this->at(i) = other.at(i);
    }
    return *this;
  }
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
                              ch_vec<ch_system_t<T>, N>>;
  using base = vec_base<T, N>;
  using base::operator [];

  ch_vec(const logic_buffer& buffer =
      logic_buffer(traits::bitwidth, idname<ch_vec>()))
    : ch_vec(buffer, std::make_index_sequence<N>())
  {}

  template <typename U,
            CH_REQUIRE_0(std::is_constructible_v<T, U>)>
  explicit ch_vec(const vec_base<U, N>& other)
    : ch_vec(logic_buffer(traits::bitwidth, idname<ch_vec>())) {
    this->operator=(other);
  }

  template <typename U,
            CH_REQUIRE_0(is_logic_type_v<U>)>
  explicit ch_vec(const U& other)
    : ch_vec(logic_buffer(traits::bitwidth, idname<ch_vec>())) {
    static_assert(ch_width_v<U> == N * ch_width_v<T>, "invalid size");
    this->operator=(other);
  }

  template <typename U,
            CH_REQUIRE_1(is_system_type_v<U>)>
  explicit ch_vec(const U& other)
    : ch_vec(logic_buffer(traits::bitwidth, idname<ch_vec>())) {
    static_assert(ch_width_v<U> == N * ch_width_v<T>, "invalid size");
    this->operator=(other);
  }

  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  explicit ch_vec(U value)
    : ch_vec(logic_buffer(traits::bitwidth, idname<ch_vec>())) {
    ch_scbit<traits::bitwidth> tmp(make_system_buffer(sdata_from_fill(value, ch_width_v<T>, N)));
    this->operator=(tmp);
  }

  template <typename U>
  explicit ch_vec(const std::initializer_list<U>& values)
    : ch_vec(logic_buffer(traits::bitwidth, idname<ch_vec>())) {
    this->operator=(values);
  }

  ch_vec(const ch_vec& other)
    : ch_vec(logic_buffer(traits::bitwidth, idname<ch_vec>())) {
    this->operator=(other);
  }

  ch_vec(ch_vec&& other) : base(std::move(other)) {}

  ch_vec& operator=(const ch_vec& other) {
    CH_SOURCE_LOCATION(1);
    logic_accessor::assign(*this, other);
    return *this;
  }

  ch_vec& operator=(ch_vec&& other) {
    CH_SOURCE_LOCATION(1);
    logic_accessor::move(*this, std::move(other));
    return *this;
  }

  template <typename U,
            CH_REQUIRE_0(is_system_type_v<U>)>
  ch_vec& operator=(const U& other) {
    static_assert(ch_width_v<U> == N * ch_width_v<T>, "invalid size");
    CH_SOURCE_LOCATION(1);
    logic_accessor::assign(*this, system_accessor::data(other));
    return *this;
  }

  template <typename U,
            CH_REQUIRE_1(is_logic_type_v<U>)>
  ch_vec& operator=(const U& other) {
    static_assert(ch_width_v<U> == N * ch_width_v<T>, "invalid size");
    CH_SOURCE_LOCATION(1);
    logic_accessor::assign(*this, other);
    return *this;
  }

  template <typename U>
  ch_vec& operator=(const std::initializer_list<U>& values) {
    assert(values.size() == N);
    CH_SOURCE_LOCATION(1);
    int i = N - 1;
    for (auto& value : values) {
      this->at(i--) = value;
    }
    return *this;
  }

  CH_LOGIC_INTERFACE(ch_vec)

protected:

  template <std::size_t...Is>
  ch_vec(const logic_buffer& buffer, std::index_sequence<Is...>)
    : base(logic_buffer(ch_width_v<T>, buffer, Is * ch_width_v<T>, stringf("%d", Is))...)
  {}

  const logic_buffer& buffer() const {
    return logic_accessor::source(this->at(0));
  }

  friend class logic_accessor;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned N>
class ch_vec<T, N, std::enable_if_t<is_system_only_v<T>>> : public vec_base<T, N> {
public:
  using traits = system_traits<N * ch_width_v<T>,
                               false,
                               ch_vec,
                               ch_vec<ch_logic_t<T>, N>>;
  using base = vec_base<T, N>;
  using base::operator [];

  ch_vec(const system_buffer_ptr& buffer = make_system_buffer(traits::bitwidth))
    : ch_vec(buffer, std::make_index_sequence<N>())
  {}

  ch_vec(const ch_vec& other)
    : ch_vec(system_accessor::copy(other))
  {}

  ch_vec(ch_vec&& other) : base(std::move(other)) {}

  template <typename U,
            CH_REQUIRE_0(std::is_constructible_v<T, U>)>
  explicit ch_vec(const vec_base<U, N>& other)
    : ch_vec(system_accessor::copy(other))
  {}

  template <typename U,
              CH_REQUIRE_0(is_system_type_v<U>)>
  explicit ch_vec(const U& other)
    : ch_vec(system_accessor::copy(other)) {
    static_assert(ch_width_v<U> == N * ch_width_v<T>, "invalid size");
  }

  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  explicit ch_vec(U value)
    : ch_vec(make_system_buffer(sdata_from_fill(value, ch_width_v<T>, N)))
  {}

  template <typename U>
  explicit ch_vec(const std::initializer_list<U>& values)
    : ch_vec(make_system_buffer(traits::bitwidth)) {
    assert(values.size() == N);
    int i = N - 1;
    for (auto& value : values) {
      this->at(i--) = value;
    }
  }

  ch_vec& operator=(const ch_vec& other) {
    system_accessor::assign(*this, other);
    return *this;
  }

  ch_vec& operator=(ch_vec&& other) {
    system_accessor::move(*this, std::move(other));
    return *this;
  }

  template <typename U,
            CH_REQUIRE_0(is_system_type_v<U>)>
  ch_vec& operator=(const U& other) {
    static_assert(ch_width_v<U> == N * ch_width_v<T>, "invalid size");
    system_accessor::assign(*this, other);
    return *this;
  }

  CH_SYSTEM_INTERFACE(ch_vec)

protected:

  template <std::size_t...Is>
  ch_vec(const system_buffer_ptr& buffer, std::index_sequence<Is...>)
    : base(make_system_buffer(ch_width_v<T>, buffer, Is * ch_width_v<T>)...)
  {}

  const system_buffer_ptr& buffer() const {
    return system_accessor::source(this->at(0));
  }

  friend std::ostream& operator<<(std::ostream& out, const ch_vec& in) {
    out << "(";
    for (unsigned i = 0; i < N; ++i) {
      if (i) {
        out << ",";
      }
      out << in[i];
    }
    out << ")";
    return out;
  }

  friend class system_accessor;
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
                                 ch_vec<ch_system_io<T>, N>>;
  using base = vec_base<T, N>;
  using base::operator [];

  explicit ch_vec(const std::string& name = idname<ch_vec>())
    : ch_vec(sloc_getter(), name, std::make_index_sequence<N>())
  {}

  explicit ch_vec(const typename traits::flip_io& other)
    : ch_vec(sloc_getter(), other, std::make_index_sequence<N>())
  {}

  ch_vec(const ch_vec& other)
    : ch_vec(sloc_getter(), other, std::make_index_sequence<N>())
  {}

  ch_vec(ch_vec&& other) : base(std::move(other)) {}

  void operator()(typename traits::flip_io& other) {
    CH_SOURCE_LOCATION(1);
    for (unsigned i = 0; i < N; ++i) {
      this->at(i)(other[i]);
    }
  }

protected:

  ch_vec& operator=(const ch_vec& other) = delete;

  ch_vec& operator=(ch_vec&& other) = delete;

  template <std::size_t...Is>
  ch_vec(const sloc_getter&, const std::string& name, std::index_sequence<Is...>)
    : base(stringf("%s_%d", name.c_str(), Is)...)
  {}

  template <typename U, std::size_t...Is>
  ch_vec(const sloc_getter&, const vec_base<U, N>& other, std::index_sequence<Is...>)
    : base(other[Is]...)
  {}
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned N>
class ch_vec<T, N, std::enable_if_t<is_system_io_v<T>>> : public vec_base<T, N> {
public:
  static_assert(is_system_io_v<T>, "invalid type");
  using traits = system_io_traits<N * ch_width_v<T>,
                                  ch_direction_v<T>,
                                  ch_vec,
                                  ch_vec<ch_flip_io<T>, N>,
                                  ch_vec<ch_logic_io<T>, N>>;
  using base = vec_base<T, N>;
  using base::operator [];

  explicit ch_vec(const typename traits::logic_io& other)
    : ch_vec(other, std::make_index_sequence<N>())
  {}

  ch_vec(const ch_vec& other)
    : ch_vec(other, std::make_index_sequence<N>())
  {}

  ch_vec(ch_vec&& other) : base(std::move(other)) {}

  void operator()(typename traits::flip_io& other) {
    for (unsigned i = 0; i < N; ++i) {
      this->at(i)(other[i]);
    }
  }

protected:

  ch_vec& operator=(const ch_vec& other) = delete;

  ch_vec& operator=(ch_vec&& other) = delete;

  template <typename U, std::size_t...Is>
  ch_vec(const vec_base<U, N>& other, std::index_sequence<Is...>)
    : base(other[Is]...)
  {}

  friend std::ostream& operator<<(std::ostream& out, const ch_vec& in) {
    out << "(";
    for (unsigned i = 0; i < N; ++i) {
      if (i) {
        out << ",";
      }
      out << in[i];
    }
    out << ")";
    return out;
  }
};

}
}
