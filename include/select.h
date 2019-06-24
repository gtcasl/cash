#pragma once

#include "bit.h"

namespace ch {
namespace internal {

class select_impl {
public:
  
  select_impl() {}

  select_impl(const lnode& key) : key_(key)  {}

  ~select_impl() {}
  
  void push(const lnode& pred, const lnode& value) {
    stmts_.emplace_back(pred, value);
  }
  
  lnode emit(const lnode& def_value);

protected:

  lnode key_;
  std::vector<std::pair<lnode, lnode>> stmts_;
};

template <typename T>
class select_t {
public:
    
  select_t(const lnode& pred, const lnode& value) : impl_() {
    impl_.push(pred, value);
  }

  template <typename V, typename P>
  select_t<T>& operator()(const P& pred, const V& value) {
    static_assert(std::is_constructible_v<T, V>, "invalid type");    
    static_assert(is_bit_base_v<P>, "invalid type");
    static_assert(ch_width_v<P> == 1, "invalid size");
    impl_.push(get_lnode(pred), to_lnode<T>(value));
    return *this;
  }
  
  template <typename V>
  auto operator()(const V& def_value) {
    static_assert(std::is_constructible_v<T, V>, "invalid type");
    CH_SOURCE_LOCATION(1);
    return make_logic_type<T>(impl_.emit(to_lnode<T>(def_value)));
  }
  
protected:
  
  select_impl impl_;
};

template <typename K, typename V>
class case_t {
public:

  case_t(const lnode& key, const lnode& pred, const lnode& value)
    : impl_(key) {
    impl_.push(pred, value);
  }

  template <typename T, typename P>
  case_t& operator()(const P& pred, const T& value) {    
    static_assert(std::is_constructible_v<V, T>, "invalid type");
    static_assert(is_equality_comparable_v<P, K>, "invalid type");
    impl_.push(to_lnode<ch_width_v<K>>(pred), to_lnode<V>(value));
    return *this;
  }

  template <typename T>
  auto operator()(const T& def_value) {
    static_assert(std::is_constructible_v<V, T>, "invalid type");
    CH_SOURCE_LOCATION(1);
    return make_logic_type<V>(impl_.emit(to_lnode<V>(def_value)));
  }
  
protected:
  
  select_impl impl_;
};

template <typename R, typename T, typename P>
auto ch_sel(const P& pred, const T& value) {
  static_assert(is_logic_type_v<R>, "invalid type");
  static_assert(std::is_constructible_v<R, T>, "invalid type");
  static_assert(is_bit_base_v<P>, "invalid type");
  static_assert(ch_width_v<P> == 1, "invalid size");
  return select_t<R>(get_lnode(pred), to_lnode<R>(value));
}

template <typename T, typename P>
auto ch_sel(const P& pred, const T& value) {
  return ch_sel<ch_logic_t<T>, T, P>(pred, value);
}

template <typename R, typename U, typename V, typename P>
auto ch_sel(const P& pred, const U& _true, const V& _false) {
  CH_SOURCE_LOCATION(1);
  return ch_sel<R, U, P>(pred, _true)(_false);
}

template <typename U, typename V, typename P>
auto ch_sel(const P& pred, const U& _true, const V& _false) {
  static_assert(ch_width_v<deduce_type_t<false, U, V>> != 0, "invalid type");
  CH_SOURCE_LOCATION(1);
  return ch_sel<ch_logic_t<deduce_first_type_t<U, V>>, U, V, P>(pred, _true, _false);
}

template <typename U, typename V>
auto ch_min(const U& lhs, const V& rhs) {
  CH_SOURCE_LOCATION(1);
  return ch_sel(lhs < rhs, lhs, rhs);
}

template <typename U, typename V>
auto ch_max(const U& lhs, const V& rhs) {
  CH_SOURCE_LOCATION(1);
  return ch_sel(lhs > rhs, lhs, rhs);
}

template <typename R, typename V, typename K, typename P>
auto ch_case(const K& key, const P& pred, const V& value) {
  static_assert(std::is_constructible_v<R, V>, "invalid type");
  static_assert(is_logic_type_v<K>, "invalid type");
  static_assert(is_sbit_convertible_v<P, ch_width_v<K>>, "invalid type");
  static_assert(is_equality_comparable_v<P, K>, "invalid type");
  CH_SOURCE_LOCATION(1);
  return case_t<K, R>(get_lnode(key),
                      to_lnode<ch_width_v<K>>(pred),
                      to_lnode<R>(value));
}

template <typename V, typename K, typename P>
auto ch_case(const K& key, const P& pred, const V& value) {
  static_assert(is_data_type_v<V>, "invalid type");
  CH_SOURCE_LOCATION(1);
  return ch_case<ch_logic_t<V>, V, K, P>(key, pred, value);
}

}
}
