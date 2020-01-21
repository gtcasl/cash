#pragma once

#include "ioport.h"
#include "streams.h"

namespace ch {
namespace internal {

template <typename T, std::size_t N>
class vec_base {
public:
  typedef T                                       value_type;
  typedef T*                                      pointer;
  typedef const T*                                const_pointer;
  typedef value_type&                             reference;
  typedef const value_type&                       const_reference;
  typedef value_type*                             iterator;
  typedef const value_type*                       const_iterator;
  typedef std::size_t                             size_type;
  typedef std::ptrdiff_t                          difference_type;
  typedef std::reverse_iterator<iterator>         reverse_iterator;
  typedef std::reverse_iterator<const_iterator>   const_reverse_iterator;

  static const std::size_t array_size = N;

  void fill(const value_type& __u) { 
    storage_.fill(begin(), size(), __u); 
  }
  
  void swap(vec_base& __other) { 
    storage_.swap(begin(), end(), __other.begin()); 
  }
  
  iterator begin() { 
    return storage_.begin();
  }
  
  const_iterator begin() const { 
    return storage_.begin();
  }
  
  iterator end() { 
    return storage_.end();
  }
  
  const_iterator end() const { 
    return storage_.end();
  }
  
  reverse_iterator rbegin() { 
    return storage_.rbegin();
  }
  
  const_reverse_iterator rbegin() const { 
    return storage_.rbegin();
  }
  
  reverse_iterator rend() { 
    return storage_.rend();
  }
  
  const_reverse_iterator rend() const { 
    return storage_.rend();
  }
  
  const_iterator cbegin() const { 
    return storage_.cbegin();
  }
  
  const_iterator cend() const { 
    return storage_.cend();
  }
  
  const_reverse_iterator crbegin() const { 
    return storage_.crbegin();
  }
  
  const_reverse_iterator crend() const { 
    return storage_.crend();
  }
  
  constexpr size_type size() const { 
    return storage_.size(); 
  }
  
  constexpr size_type max_size() const { 
    return storage_.max_size(); 
  }
  
  bool empty() const { 
    return storage_.empty(); 
  }

  reference operator[](size_type index) {
    return storage_[index];
  }

  const_reference operator[](size_type index) const {
    return storage_[index];
  }

  reference at(size_type index) {
    return storage_.at(index);
  }
  
  const_reference at(size_type index) const {
    return storage_.at(index);
  }

  reference front() { 
    return storage_.front(); 
  }
  
  const_reference front() const { 
    return storage_.front(); 
  }
  
  reference back() { 
    return storage_.back(); 
  }
  
  const_reference back() const { 
    storage_.back();  
  }
  
  T* data() { 
    return storage_.data(); 
  }
  
  const T* data() const { 
    return storage_.data(); 
  }

protected: 

  template <typename... Us,
            CH_REQUIRE(sizeof...(Us) == N && is_fold_constructible_v<T, Us...>)>
  vec_base(Us&&... values) 
    : storage_{T(std::forward<Us>(values))...} 
  {}

  template <typename... Us,
            CH_REQUIRE(sizeof...(Us) == N && is_fold_constructible_v<T, Us...>)>
  vec_base(const source_info& sloc, Us&&... values) 
    : storage_{T(std::forward<Us>(values), sloc)...} 
  {}

  vec_base(const vec_base& other) : storage_(other.storage_) {}

  vec_base(vec_base&& other) : storage_(std::move(other.storage_)) {} 

private:

  std::array<T, N> storage_;
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

  ch_vec(const logic_buffer& buffer 
    = make_logic_buffer(traits::bitwidth, idname<ch_vec>(), CH_CUR_SLOC))
    : ch_vec(buffer, std::make_index_sequence<N>())
  {}

  ch_vec(const std::initializer_list<T>& values, CH_SLOC)
    : ch_vec(make_logic_buffer(traits::bitwidth, idname<ch_vec>(), sloc)) {
    this->operator=(values);
  }

#define CH_VEC_GEN_TMPL(a, i, x) typename Arg##i
#define CH_VEC_GEN_TYPE(a, i, x) Arg##i
#define CH_VEC_GEN_DECL(a, i, x) Arg##i&& arg##i
#define CH_VEC_GEN_ARG(a, i, x)  std::forward<Arg##i>(arg##i)
#define CH_VEC_GEN(...) \
  template <CH_FOR_EACH(CH_VEC_GEN_TMPL, , CH_SEP_COMMA, __VA_ARGS__), \
            CH_REQUIRE(std::is_constructible_v<T, std::common_type_t<CH_FOR_EACH(CH_VEC_GEN_TYPE, , CH_SEP_COMMA, __VA_ARGS__)>> \
                    && (N >= CH_NARG(__VA_ARGS__)) \
                    && !std::is_convertible_v<remove_cv_ref_t<Arg0>, logic_buffer>)> \
  ch_vec(CH_FOR_EACH(CH_VEC_GEN_DECL, , CH_SEP_COMMA, __VA_ARGS__), CH_SLOC) \
    : ch_vec(make_logic_buffer(traits::bitwidth, idname<ch_vec>(), sloc)) { \
    this->operator=({CH_FOR_EACH(CH_VEC_GEN_ARG, , CH_SEP_COMMA, __VA_ARGS__)}); \
  }
CH_VA_ARGS_MAP(CH_VEC_GEN)
#undef CH_VEC_GEN_TMPL
#undef CH_VEC_GEN_TYPE
#undef CH_VEC_GEN_DECL
#undef CH_VEC_GEN_ARG
#undef CH_VEC_GEN

  template <typename U,
            CH_REQUIRE(std::is_constructible_v<T, U>)>
  explicit ch_vec(const std::array<U, N>& other, CH_SLOC)
    : ch_vec(make_logic_buffer(traits::bitwidth, idname<ch_vec>(), sloc)) {
    this->operator=(other);
  }

  template <typename U,
            CH_REQUIRE(std::is_constructible_v<T, U>)>
  explicit ch_vec(const vec_base<U, N>& other, CH_SLOC)
    : ch_vec(make_logic_buffer(traits::bitwidth, idname<ch_vec>(), sloc)) {
    this->operator=(other);
  }

  ch_vec(const ch_vec& other, CH_SLOC)
    : ch_vec(make_logic_buffer(traits::bitwidth, idname<ch_vec>(), sloc)) {
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

  ch_vec& operator=(const std::initializer_list<T>& values) {
    assert(values.size() <= N);
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

  friend auto operator==(const sloc_proxy<ch_vec>& lhs, const ch_vec& rhs) {
    return ch_eq(lhs.data.as_bit(), rhs.as_bit(), lhs.sloc);
  }

  friend auto operator!=(const sloc_proxy<ch_vec>& lhs, const ch_vec& rhs) {
    return ch_ne(lhs.data.as_bit(), rhs.as_bit(), lhs.sloc);
  }

  template <typename U>
  friend auto operator==(const sloc_proxy<ch_vec>& lhs, const std::array<U, N>& rhs) {
    static_assert(is_equality_comparable_v<T, U>, "nested type is not comparable");
    auto ret = ch_eq(lhs.data[0], rhs[N - 1], lhs.sloc);
    for (std::size_t i = 1; i < N; ++i) {
      ret &= ch_eq(lhs.data[i], rhs[N - 1 - i], lhs.sloc);
    }
    return ret;
  }

  template <typename U>
  friend auto operator!=(const sloc_proxy<ch_vec>& lhs, const std::array<U, N>& rhs) {
    static_assert(is_equality_comparable_v<T, U>, "nested type is not comparable");
    auto ret = ch_ne(lhs.data[0], rhs[N - 1], lhs.sloc);
    for (std::size_t i = 1; i < N; ++i) {
      ret &= ch_ne(lhs.data[i], rhs[N - 1 - i], lhs.sloc);
    }
    return ret;
  }

  template <typename U>
  friend auto operator==(const std::array<U, N>& lhs, const sloc_proxy<ch_vec>& rhs) {
    return (rhs == lhs);
  }

  template <typename U>
  friend auto operator!=(const std::array<U, N>& lhs, const sloc_proxy<ch_vec>& rhs) {
    return (rhs != lhs);
  }

  CH_LOGIC_INTERFACE(ch_vec)

protected:

  template <std::size_t...Is>
  ch_vec(const logic_buffer& buffer, std::index_sequence<Is...>)
    : base(make_logic_buffer(ch_width_v<T>, buffer, Is * ch_width_v<T>, stringf("%d", Is), buffer.sloc())...)
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

  template <typename U,
            CH_REQUIRE(std::is_constructible_v<T, U>)>
  explicit ch_vec(const vec_base<U, N>& other)
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

  ch_vec& operator=(const std::initializer_list<T>& values) {
    assert(values.size() <= N);
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

  explicit ch_vec(const std::string& name = "io", CH_SLOC)
    : ch_vec(sloc, name, std::make_index_sequence<N>())
  {}

  explicit ch_vec(const typename traits::flip_io& other, CH_SLOC)
    : ch_vec(sloc, other, std::make_index_sequence<N>())
  {}

  explicit ch_vec(const typename traits::system_flip_io& other, CH_SLOC)
    : ch_vec(sloc, other, std::make_index_sequence<N>())
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
  ch_vec(const source_info& sloc, const std::string& name, std::index_sequence<Is...>)
    : base(sloc, stringf("%s_%d", name.c_str(), Is)...)
  {}

  template <typename U, std::size_t... Is>
  ch_vec(const source_info& sloc, const vec_base<U, N>& other, std::index_sequence<Is...>)
    : base(sloc, other.at(Is)...)
  {}

  template <typename U, std::size_t... Is>
  ch_vec(const vec_base<U, N>& other, std::index_sequence<Is...>)
    : base(other.at(Is)...)
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
    for (std::size_t i = 0; i < N; ++i) {
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
    for (std::size_t i = 0; i < N; ++i) {
      if (i) { out << ", "; }
      out << in[N - 1 - i];
    }
    out << ")";
    return out;
  }
};

}
}
