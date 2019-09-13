#pragma once

#include "ioport.h"
#include "streams.h"

namespace ch {
namespace internal {

template <typename T, unsigned N>
class vec_base : public std::array<T, N> {
protected:
  static const std::size_t array_size = N;
  using base = std::array<T, N>;  
  using base::operator [];

  template <typename... Us,
            CH_REQUIRE(sizeof...(Us) == N && is_fold_constructible_v<T, Us...>)>
  vec_base(Us&&... values)
    : base{T(std::forward<Us>(values))...}
  {}

public:  
  vec_base(const vec_base& other) : base(other) {}
  vec_base(vec_base&& other) : base(std::move(other)) {}
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

  ch_vec(const logic_buffer& buffer = make_logic_buffer(traits::bitwidth, idname<ch_vec>()))
    : ch_vec(buffer, std::make_index_sequence<N>())
  {}

  ch_vec(const std::initializer_list<T>& values)
    : ch_vec(make_logic_buffer(traits::bitwidth, idname<ch_vec>())) {
    this->operator=(values);
  }

  template <typename Arg0, typename... Args,
              CH_REQUIRE(std::is_constructible_v<T, Arg0>
                      && !std::is_convertible_v<remove_cv_ref_t<Arg0>, logic_buffer>
                      && (std::is_same_v<Arg0, Args> && ...))>
  ch_vec(Arg0&& arg0, Args&&... args)
    : ch_vec(make_logic_buffer(traits::bitwidth, idname<ch_vec>())) {
    this->operator=({std::forward<Arg0>(arg0), std::forward<Args>(args)...});
  }

  template <typename U,
            CH_REQUIRE(std::is_constructible_v<T, U>)>
  explicit ch_vec(const std::array<U, N>& other)
    : ch_vec(make_logic_buffer(traits::bitwidth, idname<ch_vec>())) {
    this->operator=(other);
  }

  ch_vec(const ch_vec& other)
    : ch_vec(make_logic_buffer(traits::bitwidth, idname<ch_vec>())) {
    this->operator=(other);
  }

  ch_vec(ch_vec&& other) : base(std::move(other)) {}

  ch_vec& operator=(const ch_vec& other) {
    CH_API_ENTRY(1);
    logic_accessor::assign(*this, other);
    return *this;
  }

  ch_vec& operator=(ch_vec&& other) {
    CH_API_ENTRY(1);
    logic_accessor::move(*this, std::move(other));
    return *this;
  }

  template <typename U>
  ch_vec& operator=(const std::array<U, N>& other) {
    CH_API_ENTRY(1);
    static_assert(std::is_constructible_v<T, U>, "invalid type");
    for (unsigned i = 0; i < N; ++i) {
      (*this)[i] = other[i];
    }
    return *this;
  }

  ch_vec& operator=(const std::initializer_list<T>& values) {
    CH_API_ENTRY(1);
    assert(values.size() <= N);
    if (0 == values.size())
      return *this;
    auto it = values.begin();
    auto last = *it++;
    int i = N - 1;
    for (unsigned j = N - values.size(); j--;) {
      (*this)[i--] = last;
    } 
    (*this)[i--] = last;   
    while (it != values.end()) {
      (*this)[i--] = *it++;
    }
    return *this;
  }

  auto operator==(const ch_vec& other) const {
    CH_API_ENTRY(1);
    return (this->as_bit() == other.as_bit());
  }

  auto operator!=(const ch_vec& other) const {
    CH_API_ENTRY(1);
    return (this->as_bit() != other.as_bit());
  }

  template <typename U>
  friend auto operator==(const ch_vec& lhs, const std::array<U, N>& rhs) {
    CH_API_ENTRY(1);
    static_assert(is_equality_comparable_v<T, U>, "nested type is not equality-comparable");
    auto ret(lhs[0] == rhs[0]);
    for (unsigned i = 1; i < N; ++i) {
      ret &= (lhs[i] == rhs[i]);
    }
    return ret;
  }

  template <typename U>
  friend auto operator==(const std::array<U, N>& lhs, const ch_vec& rhs) {
    CH_API_ENTRY(1);
    return (rhs == lhs);
  }

  template <typename U>
  friend auto operator!=(const ch_vec& lhs, const std::array<U, N>& rhs) {
    CH_API_ENTRY(1);
    return !(lhs == rhs);
  }

  template <typename U>
  friend auto operator!=(const std::array<U, N>& lhs, const ch_vec& rhs) {
    CH_API_ENTRY(1);
    return !(rhs == lhs);
  }

  CH_LOGIC_INTERFACE(ch_vec)

protected:

  template <std::size_t...Is>
  ch_vec(const logic_buffer& buffer, std::index_sequence<Is...>)
    : base(make_logic_buffer(ch_width_v<T>, buffer, Is * ch_width_v<T>, stringf("%d", Is))...)
  {}

  const logic_buffer& __buffer() const {
    return logic_accessor::source((*this)[0]);
  }

  friend ch_ostream& operator<<(ch_ostream& out, const ch_vec& in) {
    out << "(";
    for (unsigned i = 0; i < N; ++i) {
      if (i) {
        out << ", ";
      }
      out << in[N - 1 - i];
    }
    out << ")";
    return out;
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

  ch_vec(const system_buffer& buffer
         = make_system_buffer(traits::bitwidth, idname<ch_vec>()))
    : ch_vec(buffer, std::make_index_sequence<N>())
  {}

  ch_vec(const std::initializer_list<T>& values)
    : ch_vec(make_system_buffer(traits::bitwidth, idname<ch_vec>())) {
    this->operator=(values);
  }

  template <typename Arg0, typename... Args,
              CH_REQUIRE(std::is_constructible_v<T, Arg0>
                      && !std::is_convertible_v<remove_cv_ref_t<Arg0>, system_buffer>
                      && (std::is_same_v<Arg0, Args> && ...))>
  ch_vec(Arg0&& arg0, Args&&... args)
    : ch_vec(make_system_buffer(traits::bitwidth, idname<ch_vec>())) {
    this->operator=({std::forward<Arg0>(arg0), std::forward<Args>(args)...});
  }

  template <typename U,
            CH_REQUIRE(std::is_constructible_v<T, U>)>
  explicit ch_vec(const std::array<U, N>& other)
    : ch_vec(make_system_buffer(traits::bitwidth, idname<ch_vec>())) {
    base::operator=(other);
  }

  ch_vec(const ch_vec& other)
    : ch_vec(make_system_buffer(traits::bitwidth, idname<ch_vec>())) {
    this->operator=(other);
  }

  ch_vec(ch_vec&& other) : base(std::move(other)) {}

  ch_vec& operator=(const ch_vec& other) {
    system_accessor::assign(*this, other);
    return *this;
  }

  ch_vec& operator=(ch_vec&& other) {
    system_accessor::move(*this, std::move(other));
    return *this;
  }

  template <typename U>
  ch_vec& operator=(const std::array<U, N>& other) {
    static_assert(std::is_constructible_v<T, U>, "invalid type");
    for (unsigned i = 0; i < N; ++i) {
      (*this)[i] = other[i];
    }
    return *this;
  }

  ch_vec& operator=(const std::initializer_list<T>& values) {
    assert(values.size() <= N);
    if (0 == values.size())
      return *this;
    auto it = values.begin();
    auto last = *it++;
    int i = N - 1;
    for (unsigned j = N - values.size(); j--;) {
      (*this)[i--] = last;
    }    
    (*this)[i--] = last;
    while (it != values.end()) {
      (*this)[i--] = *it++;
    }
    return *this;
  }

  auto operator==(const ch_vec& other) const {
    return (this->as_bit() == other.as_bit());
  }

  auto operator!=(const ch_vec& other) const {
    return (this->as_bit() != other.as_bit());
  }

  template <typename U>
  friend auto operator==(const ch_vec& lhs, const std::array<U, N>& rhs) {
    static_assert(is_equality_comparable_v<T, U>, "nested type is not equality-comparable");
    auto ret(lhs[0] == rhs[0]);
    for (unsigned i = 1; i < N; ++i) {
      ret = ret && (lhs[i] == rhs[i]);
    }
    return ret;
  }

  template <typename U>
  friend auto operator==(const std::array<U, N>& lhs, const ch_vec& rhs) {
    return (rhs == lhs);
  }

  template <typename U>
  friend auto operator!=(const ch_vec& lhs, const std::array<U, N>& rhs) {
    return !(lhs == rhs);
  }

  template <typename U>
  friend auto operator!=(const std::array<U, N>& lhs, const ch_vec& rhs) {
    return !(rhs == lhs);
  }

  CH_SYSTEM_INTERFACE(ch_vec)

protected:

  template <std::size_t...Is>
  ch_vec(const system_buffer& buffer, std::index_sequence<Is...>)
    : base(make_system_buffer(ch_width_v<T>, buffer, Is * ch_width_v<T>, stringf("%d", Is))...)
  {}

  const system_buffer& __buffer() const {
    return system_accessor::source((*this)[0]);
  }

  friend std::ostream& operator<<(std::ostream& out, const ch_vec& in) {
    out << "(";
    for (unsigned i = 0; i < N; ++i) {
      if (i) { out << ", "; }
      out << in[N - 1 - i];
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
                                 ch_vec<ch_system_io<T>, N>,
                                 ch_vec<ch_flip_io<ch_system_io<T>>, N>,
                                 ch_vec<ch_system_t<T>, N>,
                                 ch_vec<ch_logic_t<T>, N>>;
  using base = vec_base<T, N>;
  using base::operator [];

  explicit ch_vec(const std::string& name = "io")
    : ch_vec(sloc_api_entry(1), name, std::make_index_sequence<N>())
  {}

  explicit ch_vec(const typename traits::flip_io& other)
    : ch_vec(sloc_api_entry(1), other, std::make_index_sequence<N>())
  {}

  explicit ch_vec(const typename traits::system_flip_io& other)
    : ch_vec(sloc_api_entry(1), other, std::make_index_sequence<N>())
  {}

  ch_vec(const ch_vec& other)
    : ch_vec(sloc_api_entry(1), other, std::make_index_sequence<N>())
  {}

  ch_vec(ch_vec&& other) : base(std::move(other)) {}

  void operator()(typename traits::flip_io& other) {
    CH_API_ENTRY(1);
    for (unsigned i = 0; i < N; ++i) {
      (*this)[i](other[i]);
    }
  }

protected:

  ch_vec& operator=(const ch_vec& other) = delete;

  ch_vec& operator=(ch_vec&& other) = delete;

  template <std::size_t...Is>
  ch_vec(const sloc_api_entry&, const std::string& name, std::index_sequence<Is...>)
    : base(stringf("%s_%d", name.c_str(), Is)...)
  {}

  template <typename U, std::size_t...Is>
  ch_vec(const sloc_api_entry&, const vec_base<U, N>& other, std::index_sequence<Is...>)
    : base(other.at(Is)...)
  {}

  friend ch_ostream& operator<<(ch_ostream& out, const ch_vec& in) {
    out << "(";
    for (unsigned i = 0; i < N; ++i) {
      if (i) { out << ", "; }
      out << in[N - 1 - i];
    }
    out << ")";
    return out;
  }
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
                                  ch_vec<ch_logic_io<T>, N>,
                                  ch_vec<ch_flip_io<ch_logic_io<T>>, N>,
                                  ch_vec<ch_system_t<T>, N>,
                                  ch_vec<ch_logic_t<T>, N>>;
  using base = vec_base<T, N>;
  using base::operator [];

  explicit ch_vec(const std::string& name = "io")
    : ch_vec(name, std::make_index_sequence<N>())
  {}

  explicit ch_vec(const typename traits::logic_flip_io& other)
    : ch_vec(other, std::make_index_sequence<N>())
  {}

  ch_vec(const ch_vec& other)
    : ch_vec(other, std::make_index_sequence<N>())
  {}

  ch_vec(ch_vec&& other) : base(std::move(other)) {}

  void operator()(typename traits::flip_io& other) {
    for (unsigned i = 0; i < N; ++i) {
      (*this)[i](other[i]);
    }
  }

protected:

  ch_vec& operator=(const ch_vec& other) = delete;

  ch_vec& operator=(ch_vec&& other) = delete;

  template <std::size_t...Is>
  ch_vec(const std::string& name, std::index_sequence<Is...>)
    : base(stringf("%s_%d", name.c_str(), Is)...)
  {}

  template <typename U, std::size_t...Is>
  ch_vec(const vec_base<U, N>& other, std::index_sequence<Is...>)
    : base(other.at(Is)...)
  {}

  friend std::ostream& operator<<(std::ostream& out, const ch_vec& in) {
    out << "(";
    for (unsigned i = 0; i < N; ++i) {
      if (i) { out << ", "; }
      out << in[N - 1 - i];
    }
    out << ")";
    return out;
  }
};

}
}
