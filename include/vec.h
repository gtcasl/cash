#pragma once

#include "ioport.h"
#include "streams.h"

namespace ch {
namespace internal {

template <typename T, std::size_t N>
class vec_base : public std::array<T, N> {
public:
  static const std::size_t array_size = N;   
  using base = std::array<T, N>;  
  using base::operator [];

protected:

  struct arg_ctor_t {
    explicit arg_ctor_t() = default;
  };

  struct arg_in_place_t {
    explicit arg_in_place_t() = default;
  };

  struct arg_tuple_t {
    explicit arg_tuple_t() = default;
  };

  static constexpr arg_ctor_t     arg_ctor{};
  static constexpr arg_in_place_t arg_in_place{};
  static constexpr arg_tuple_t    arg_tuple{};

  template <typename... Us>
  vec_base(arg_ctor_t, Us&&... values) 
    : base{T(std::forward<Us>(values))...}
  {}

  template <typename... Us>
  vec_base(arg_in_place_t, Us&&... values) 
    : base{std::forward<Us>(values)...}
  {}

  template <typename... Us>
  vec_base(arg_tuple_t, Us&&... values) 
    : base{std::make_from_tuple<T>(values)...}
  {}

  template <typename... Us>
  vec_base(const source_location& sloc, Us&&... values) 
    : base{T(std::forward<Us>(values), sloc)...} 
  {}

  vec_base(const vec_base& other) : base(other) {}

  vec_base(vec_base&& other) : base(std::move(other)) {} 
};

template <typename T, std::size_t N, typename Enable = void>
class ch_vec {};

///////////////////////////////////////////////////////////////////////////////

template <typename T, std::size_t N>
class ch_vec<T, N, std::enable_if_t<is_logic_only_v<T>>> : public vec_base<T, N> {
public:
  using traits = logic_traits<N * ch_width_v<T>,
                              false,
                              ch_vec,
                              ch_vec<ch_system_t<T>, N>>;
  using base = vec_base<T, N>;
  using base::operator [];

  explicit ch_vec(const logic_buffer& buffer 
                    = make_logic_buffer(traits::bitwidth, CH_CUR_SRC_INFO))
    : ch_vec(buffer, std::make_index_sequence<N>())
  {}

#define CH_VEC_GEN_TMPL(a, i, x)  typename Arg##i
#define CH_VEC_GEN_TYPE(a, i, x)  Arg##i
#define CH_VEC_GEN_DECL(a, i, x)  Arg##i&& arg##i
#define CH_VEC_GEN_ARG(a, i, x)   std::forward<Arg##i>(arg##i)
#define CH_VEC_GEN_SINFO(a, i, x) !std::is_same_v<std::decay_t<Arg##i>, source_info>
#define CH_VEC_GEN(...) \
  template <CH_FOR_EACH(CH_VEC_GEN_TMPL, , CH_SEP_COMMA, __VA_ARGS__), \
            CH_REQUIRES(CH_FOR_EACH(CH_VEC_GEN_SINFO, , CH_SEP_ANDL, __VA_ARGS__) \
                     && is_fold_constructible_v<T, CH_FOR_EACH(CH_VEC_GEN_TYPE, , CH_SEP_COMMA, __VA_ARGS__)> \
                     && (N >= CH_NARG(__VA_ARGS__)) \
                     && !std::is_convertible_v<std::decay_t<Arg0>, logic_buffer>)> \
  ch_vec(CH_FOR_EACH(CH_VEC_GEN_DECL, , CH_SEP_COMMA, __VA_ARGS__), CH_SRC_INFO) \
    : ch_vec(make_logic_buffer(traits::bitwidth, srcinfo)) { \
    this->operator=({CH_FOR_EACH(CH_VEC_GEN_ARG, , CH_SEP_COMMA, __VA_ARGS__)}); \
  }
CH_VA_ARGS_MAP(CH_VEC_GEN)
#undef CH_VEC_GEN_TMPL
#undef CH_VEC_GEN_TYPE
#undef CH_VEC_GEN_DECL
#undef CH_VEC_GEN_ARG
#undef CH_VEC_GEN_SINFO
#undef CH_VEC_GEN

  ch_vec(const std::initializer_list<T>& values, CH_SRC_INFO)
    : ch_vec(make_logic_buffer(traits::bitwidth, srcinfo)) {
    this->operator=(values);
  }

  template <typename U,
            CH_REQUIRES(std::is_constructible_v<T, U>)>
  ch_vec(const std::array<U, N>& other, CH_SRC_INFO)
    : ch_vec(make_logic_buffer(traits::bitwidth, srcinfo)) {
    this->operator=(other);
  }

  template <typename U,
            CH_REQUIRES(std::is_constructible_v<T, U>)>
  ch_vec(const vec_base<U, N>& other, CH_SRC_INFO)
    : ch_vec(make_logic_buffer(traits::bitwidth, srcinfo)) {
    this->operator=(other);
  }

  ch_vec(const ch_vec& other, CH_SRC_INFO)
    : ch_vec(make_logic_buffer(traits::bitwidth, srcinfo)) {
    this->operator=(other);
  }

  ch_vec(ch_vec&& other) : base(std::move(other)) {}

  ch_vec& operator=(const ch_vec& other) {
    logic_accessor::assign(*this, other);
    return *this;
  }

  ch_vec& operator=(ch_vec&& other) {
    logic_accessor::move(*this, std::move(other));
    return *this;
  }

  ch_vec& operator=(const std::initializer_list<T>& values) {
    CH_CHECK(values.size() <= N, "value out of range");
    if (0 == values.size())
      return *this;
    auto it = values.begin();
    auto last = *it++;
    int i = N - 1;
    for (std::size_t j = N - values.size(); j--;) {
      (*this)[i--] = last;
    }    
    (*this)[i--] = last;
    while (it != values.end()) {
      (*this)[i--] = *it++;
    }
    return *this;
  }

  template <typename U>
  ch_vec& operator=(const std::array<U, N>& other) {
    static_assert(std::is_constructible_v<T, U>, "invalid type");
    for (std::size_t i = 0; i < N; ++i) {
      (*this)[i] = other[i];
    }
    return *this;
  }

  template <typename U>
  ch_vec& operator=(const vec_base<U, N>& other) {
    static_assert(std::is_constructible_v<T, U>, "invalid type");
    for (std::size_t i = 0; i < N; ++i) {
      (*this)[i] = other[i];
    }
    return *this;
  }

  friend auto operator==(ch_vec lhs, const ch_vec& rhs) {
    auto srcinfo = logic_accessor::srcinfo(lhs);
    return ch_eq(lhs.as_bit(), rhs.as_bit(), srcinfo);
  }

  friend auto operator!=(ch_vec lhs, const ch_vec& rhs) {
    auto srcinfo = logic_accessor::srcinfo(lhs);
    return ch_ne(lhs.as_bit(), rhs.as_bit(), srcinfo);
  }

  template <typename U>
  friend auto operator==(ch_vec lhs, const std::array<U, N>& rhs) {
    static_assert(is_equality_comparable_v<T, U>, "nested type is not comparable");
    auto srcinfo = logic_accessor::srcinfo(lhs);
    auto ret = ch_eq(lhs[0], rhs[N - 1], srcinfo);
    for (std::size_t i = 1; i < N; ++i) {
      ret &= ch_eq(lhs[i], rhs[N - 1 - i], srcinfo);
    }
    return ret;
  }

  template <typename U>
  friend auto operator!=(ch_vec lhs, const std::array<U, N>& rhs) {
    static_assert(is_equality_comparable_v<T, U>, "nested type is not comparable");
    auto srcinfo = logic_accessor::srcinfo(lhs);
    auto ret = ch_ne(lhs[0], rhs[N - 1], srcinfo);
    for (std::size_t i = 1; i < N; ++i) {
      ret &= ch_ne(lhs[i], rhs[N - 1 - i], srcinfo);
    }
    return ret;
  }

  template <typename U>
  friend auto operator==(const std::array<U, N>& lhs, ch_vec rhs) {
    return (rhs == lhs);
  }

  template <typename U>
  friend auto operator!=(const std::array<U, N>& lhs, ch_vec rhs) {
    return (rhs != lhs);
  }

  CH_LOGIC_INTERFACE(ch_vec)

protected:

  template <std::size_t...Is>
  ch_vec(const logic_buffer& buffer, std::index_sequence<Is...>)
    : base(base::arg_ctor, 
           make_logic_buffer(ch_width_v<T>, 
                             buffer, 
                             Is * ch_width_v<T>, 
                             source_info(buffer.sloc(), stringf("%d", Is)))...)
  {}

  const logic_buffer& __buffer() const {
    return logic_accessor::source((*this)[0]);
  }

  friend ch_ostream& operator<<(ch_ostream& out, const ch_vec& in) {
    out << "(";
    for (std::size_t i = 0; i < N; ++i) {
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

template <typename T, std::size_t N>
class ch_vec<T, N, std::enable_if_t<is_system_only_v<T>>> : public vec_base<T, N> {
public:
  using traits = system_traits<N * ch_width_v<T>,
                               false,
                               ch_vec,
                               ch_vec<ch_logic_t<T>, N>>;
  using base = vec_base<T, N>;
  using base::operator [];

  explicit ch_vec(const system_buffer& buffer 
                    = make_system_buffer(traits::bitwidth))
    : ch_vec(buffer, std::make_index_sequence<N>())
  {}

  template <typename Arg0, typename... Args,
            CH_REQUIRES(is_fold_constructible_v<T, Arg0, Args...>
                     && (N >= (1 + sizeof...(Args)))
                     && !std::is_convertible_v<std::decay_t<Arg0>, system_buffer>)>
  ch_vec(Arg0&& arg0, Args&&... args)
    : ch_vec(make_system_buffer(traits::bitwidth)) {    
    this->operator=({std::forward<Arg0>(arg0), std::forward<Args>(args)...});   
  }

  ch_vec(const std::initializer_list<T>& values)
    : ch_vec(make_system_buffer(traits::bitwidth)) {
    this->operator=(values);
  }

  template <typename U,
            CH_REQUIRES(std::is_constructible_v<T, U>)>
  ch_vec(const std::array<U, N>& other)
    : ch_vec(make_system_buffer(traits::bitwidth)) {
    base::operator=(other);
  }

  template <typename U,
            CH_REQUIRES(std::is_constructible_v<T, U>)>
  ch_vec(const vec_base<U, N>& other)
    : ch_vec(make_system_buffer(traits::bitwidth)) {
    base::operator=(other);
  }

  ch_vec(const ch_vec& other)
    : ch_vec(make_system_buffer(traits::bitwidth)) {
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

  ch_vec& operator=(const std::initializer_list<T>& values) {
    CH_CHECK(values.size() <= N, "value out of range");
    if (0 == values.size())
      return *this;
    auto it = values.begin();
    auto last = *it++;
    int i = N - 1;
    for (std::size_t j = N - values.size(); j--;) {
      (*this)[i--] = last;
    } 
    (*this)[i--] = last;   
    while (it != values.end()) {
      (*this)[i--] = *it++;
    }
    return *this;
  }

  template <typename U>
  ch_vec& operator=(const std::array<U, N>& other) {
    static_assert(std::is_constructible_v<T, U>, "invalid type");
    for (std::size_t i = 0; i < N; ++i) {
      (*this)[i] = other[i];
    }
    return *this;
  }

  template <typename U>
  ch_vec& operator=(const vec_base<U, N>& other) {
    static_assert(std::is_constructible_v<T, U>, "invalid type");
    for (std::size_t i = 0; i < N; ++i) {
      (*this)[i] = other[i];
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
    auto ret = (lhs[0] == rhs[0]);
    for (std::size_t i = 1; i < N; ++i) {
      ret = ret && (lhs[i] == rhs[i]);
    }
    return ret;
  }

  template <typename U>
  friend auto operator==(const std::array<U, N>& lhs, const ch_vec& rhs) {
    static_assert(is_equality_comparable_v<T, U>, "nested type is not equality-comparable");
    auto ret = (lhs[0] != rhs[0]);
    for (std::size_t i = 1; i < N; ++i) {
      ret = ret && (lhs[i] != rhs[i]);
    }
    return ret;
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
    : base(base::arg_ctor, 
           make_system_buffer(ch_width_v<T>, 
                              buffer, 
                              Is * ch_width_v<T>, 
                              stringf("%d", Is))...)
  {}

  const system_buffer& __buffer() const {
    return system_accessor::source((*this)[0]);
  }

  friend std::ostream& operator<<(std::ostream& out, const ch_vec& in) {
    out << "(";
    for (std::size_t i = 0; i < N; ++i) {
      if (i) { out << ", "; }
      out << in[N - 1 - i];
    }
    out << ")";
    return out;
  }

  friend class system_accessor;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, std::size_t N>
class ch_vec<T, N, std::enable_if_t<is_logic_io_v<T>>> : public vec_base<T, N> {
public:
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

  explicit ch_vec(const std::string& name = "io", CH_SLOC)
    : ch_vec(name, sloc, std::make_index_sequence<N>())
  {}

  explicit ch_vec(const typename traits::flip_io& other, CH_SLOC)
    : ch_vec(other, sloc, std::make_index_sequence<N>())
  {}

  explicit ch_vec(const typename traits::system_flip_io& other, CH_SLOC)
    : ch_vec(other, sloc, std::make_index_sequence<N>())
  {}

  ch_vec(const ch_vec& other)
    : ch_vec(other, std::make_index_sequence<N>())
  {}

  ch_vec(ch_vec&& other) : base(std::move(other)) {}

  void operator()(typename traits::flip_io& other) {
    for (std::size_t i = 0; i < N; ++i) {
      (*this)[i](other[i]);
    }
  }

protected:

  ch_vec& operator=(const ch_vec& other) = delete;

  ch_vec& operator=(ch_vec&& other) = delete;

  template <std::size_t... Is>
  ch_vec(const std::string& name, const source_location& sloc, std::index_sequence<Is...>)
    : base(sloc, stringf("%s_%d", name.c_str(), Is)...)
  {}

  template <typename U, std::size_t... Is>
  ch_vec(const vec_base<U, N>& other, const source_location& sloc, std::index_sequence<Is...>)
    : base(sloc, other.at(Is)...)
  {}
  
  template <std::size_t... Is>
  ch_vec(const ch_vec& other, std::index_sequence<Is...>)
    : base(base::arg_in_place, other.at(Is)...)
  {}

  friend ch_ostream& operator<<(ch_ostream& out, const ch_vec& in) {
    out << "(";
    for (std::size_t i = 0; i < N; ++i) {
      if (i) { out << ", "; }
      out << in[N - 1 - i];
    }
    out << ")";
    return out;
  }
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, std::size_t N>
class ch_vec<T, N, std::enable_if_t<is_system_io_v<T>>> : public vec_base<T, N> {
public:
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
    for (std::size_t i = 0; i < N; ++i) {
      (*this)[i](other[i]);
    }
  }

protected:

  ch_vec& operator=(const ch_vec& other) = delete;

  ch_vec& operator=(ch_vec&& other) = delete;

  template <std::size_t...Is>
  ch_vec(const std::string& name, std::index_sequence<Is...>)
    : base(base::arg_ctor, stringf("%s_%d", name.c_str(), Is)...)
  {}

  template <typename U, std::size_t...Is>
  ch_vec(const vec_base<U, N>& other, std::index_sequence<Is...>)
    : base(base::arg_ctor, other.at(Is)...)
  {}

   template <std::size_t...Is>
  ch_vec(const ch_vec& other, std::index_sequence<Is...>)
    : base(base::arg_in_place, other.at(Is)...)
  {}

  friend std::ostream& operator<<(std::ostream& out, const ch_vec& in) {
    out << "(";
    for (std::size_t i = 0; i < N; ++i) {
      if (i) { out << ", "; }
      out << in[N - 1 - i];
    }
    out << ")";
    return out;
  }
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, std::size_t N>
class ch_vec<T, N, std::enable_if_t<is_reg_type_v<T> 
                                 || is_mem_type_v<T> 
                                 || is_module_type_v<T> 
                                 || is_udf_type_v<T>>> : public vec_base<T, N> {
public:
  using base = vec_base<T, N>;
  using base::operator [];
  using traits = typename T::traits;

  explicit ch_vec(CH_SRC_INFO)
    : ch_vec(srcinfo, std::make_index_sequence<N>())
  {}

#define CH_VEC_GEN_TMPL(a, i, x)  typename Arg##i
#define CH_VEC_GEN_TYPE(a, i, x)  Arg##i
#define CH_VEC_GEN_TYPEF(a, i, x) Arg##i&&
#define CH_VEC_GEN_DECL(a, i, x)  Arg##i&& arg##i
#define CH_VEC_GEN_ARG(a, i, x)   std::forward<Arg##i>(arg##i)
#define CH_VEC_GEN_SINFO(a, i, x) !std::is_same_v<std::decay_t<Arg##i>, source_info>
#define CH_VEC_GEN(...) \
  template <CH_FOR_EACH(CH_VEC_GEN_TMPL, , CH_SEP_COMMA, __VA_ARGS__), \
            CH_REQUIRES(CH_FOR_EACH(CH_VEC_GEN_SINFO, , CH_SEP_ANDL, __VA_ARGS__) \
                     && is_fold_constructible_v<T, CH_FOR_EACH(CH_VEC_GEN_TYPE, , CH_SEP_COMMA, __VA_ARGS__)> \
                     && (N >= CH_NARG(__VA_ARGS__)))> \
  ch_vec(CH_FOR_EACH(CH_VEC_GEN_DECL, , CH_SEP_COMMA, __VA_ARGS__), CH_SRC_INFO) \
    : ch_vec(srcinfo, \
             std::tuple<CH_FOR_EACH(CH_VEC_GEN_TYPEF, , CH_SEP_COMMA, __VA_ARGS__)>{ \
                 CH_FOR_EACH(CH_VEC_GEN_ARG, , CH_SEP_COMMA, __VA_ARGS__)}, \
             std::make_index_sequence<N>()) \
  {}
CH_VA_ARGS_MAP(CH_VEC_GEN)
#undef CH_VEC_GEN_TMPL
#undef CH_VEC_GEN_TYPE
#undef CH_VEC_GEN_TYPEF
#undef CH_VEC_GEN_DECL
#undef CH_VEC_GEN_ARG
#undef CH_VEC_GEN_SINFO
#undef CH_VEC_GEN

  ch_vec(const ch_vec& other)
    : ch_vec(other, std::make_index_sequence<N>())
  {}

  ch_vec(ch_vec&& other) : base(std::move(other)) 
  {}

protected:

  template <typename Args, std::size_t I>
  static constexpr auto get_element(const Args& args) {
    return std::forward<std::tuple_element_t<std::min(I, std::tuple_size_v<Args> - 1), Args>>(
                       std::get<std::min(I, std::tuple_size_v<Args> - 1)>(args));
  }

  template <std::size_t... Is>
  ch_vec(const source_info& srcinfo, std::index_sequence<Is...>)
    : base(base::arg_ctor, source_info(srcinfo.sloc(), stringf("%s_%d", srcinfo.name().c_str(), Is))...)
  {}

  template <typename Args, std::size_t... Is>
  ch_vec(const source_info& srcinfo, const Args& args, std::index_sequence<Is...>)
    : base(base::arg_tuple, std::forward_as_tuple(get_element<Args, Is>(args), 
             source_info(srcinfo.sloc(), stringf("%s_%d", srcinfo.name().c_str(), Is)))...)
  {}

  template <std::size_t... Is>
  ch_vec(const ch_vec& other, std::index_sequence<Is...>)
    : base(base::arg_in_place, other.at(Is)...)
  {}
};

}
}
