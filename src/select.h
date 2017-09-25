#pragma once

#include "bit.h"

namespace cash {
namespace internal {

lnodeimpl* createSelectNode(const lnode& pred, const lnode& a, const lnode& b);

class select_impl {
public:
  
  select_impl() {}

  select_impl(const lnode& key) : key_(key) {}

  ~select_impl() {}
  
  void push(const lnode& pred, const lnode& value) {
    stmts_.push({pred, value});
  }
  
  lnodeimpl* eval(const lnode& value);

protected:

  struct stmt_t {
    lnode pred;
    lnode value;
  };

  using stmts_t = std::stack<stmt_t>;

  lnode key_;
  stmts_t stmts_;
};

template <typename T>
class select_t {
public:
    
  select_t(const lnode& pred, const lnode& value) {
    impl_.push(pred, value);
  }

  template <typename V,
            CH_REQUIRES(is_cast_convertible<V, T>::value)>
  select_t<T>& operator()(const ch_bitbase<1>& pred, const V& value) {
    impl_.push(get_lnode(pred), get_lnode<V, T::bitcount>(value));
    return *this;
  }
  
  template <typename V,
            CH_REQUIRES(is_cast_convertible<V, T>::value)>
  const auto operator()(const V& value) {
    return make_type<T>(impl_.eval(get_lnode<V, T::bitcount>(value)));
  }
  
protected:
  
  select_impl impl_;
};

template <typename K, typename V>
class case_t {
public:

  case_t(const lnode& key, const lnode& pred, const lnode& value) : impl_(key) {
    impl_.push(pred, value);
  }

  template <typename P, typename T,
            CH_REQUIRES(is_equality_comparable<P, K>::value),
            CH_REQUIRES(is_cast_convertible<T, V>::value)>
  case_t& operator()(const P& pred, const T& value) {
    impl_.push(get_lnode<P, K::bitcount>(pred), get_lnode<T, V::bitcount>(value));
    return *this;
  }

  template <typename T,
            CH_REQUIRES(is_cast_convertible<T, V>::value)>
  const auto operator()(const T& value) {
    return make_type<V>(impl_.eval(get_lnode<T, V::bitcount>(value)));
  }
  
protected:
  
  select_impl impl_;
};

template <typename V,
          CH_REQUIRES(is_bit_convertible<V>::value)>
auto ch_select(const ch_bitbase<1>& pred, const V& value) {
  return select_t<typename V::value_type>(get_lnode(pred), get_lnode(value));
}

template <typename R, typename V,
          CH_REQUIRES(is_cast_convertible<V, R>::value)>
auto ch_select(const ch_bitbase<1>& pred, const V& value) {
  return select_t<R>(
        get_lnode(pred), get_lnode<V, R::bitcount>(value));
}

template <typename K, typename P, typename V,
          CH_REQUIRES(is_bit_convertible<K>::value),
          CH_REQUIRES(is_equality_comparable<P, K>::value),
          CH_REQUIRES(is_bit_convertible<V>::value)>
auto ch_case(const K& key, const P& pred, const V& value) {
  return case_t<K, typename V::value_type>(
        get_lnode(key), get_lnode<P, K::bitcount>(pred), get_lnode(value));
}

template <typename R, typename K, typename P, typename V,
          CH_REQUIRES(is_bit_convertible<K>::value),
          CH_REQUIRES(is_equality_comparable<P, K>::value),
          CH_REQUIRES(is_cast_convertible<V, R>::value)>
auto ch_case(const K& key, const P& pred, const V& value) {
  return case_t<K, R>(
        get_lnode(key), get_lnode<P, K::bitcount>(pred), get_lnode<V, R::bitcount>(value));
}

template <typename U, typename V,
          CH_REQUIRES(deduce_type<U, V>::bitcount != 0),
          CH_REQUIRES(is_bit_convertible<U, deduce_type<U, V>::bitcount>::value),
          CH_REQUIRES(is_bit_convertible<V, deduce_type<U, V>::bitcount>::value)>
const auto ch_select(const ch_bitbase<1>& pred, const U& _true, const V& _false) {
  return make_type<typename deduce_first_type<U, V>::type>(
        createSelectNode(get_lnode(pred),
                         get_lnode<U, deduce_type<U, V>::bitcount>(_true),
                         get_lnode<V, deduce_type<U, V>::bitcount>(_false)));
}

template <typename R, typename U, typename V,
          CH_REQUIRES(is_cast_convertible<U, R>::value),
          CH_REQUIRES(is_cast_convertible<V, R>::value)>
const auto ch_select(const ch_bitbase<1>& pred, const U& _true, const V& _false) {
  return make_type<R>(
        createSelectNode(get_lnode(pred),
                         get_lnode<U, R::bitcount>(_true),
                         get_lnode<V, R::bitcount>(_false)));
}

template <typename U, typename V,
          CH_REQUIRES(deduce_type<U, V>::bitcount != 0),
          CH_REQUIRES(is_bit_convertible<U, deduce_type<U, V>::bitcount>::value),
          CH_REQUIRES(is_bit_convertible<V, deduce_type<U, V>::bitcount>::value)>
const auto ch_min(const U& lhs, const V& rhs) {
  return ch_select(lhs < rhs, lhs, rhs);
}

template <typename U, typename V,
          CH_REQUIRES(deduce_type<U, V>::bitcount != 0),
          CH_REQUIRES(is_bit_convertible<U, deduce_type<U, V>::bitcount>::value),
          CH_REQUIRES(is_bit_convertible<V, deduce_type<U, V>::bitcount>::value)>
const auto ch_max(const U& lhs, const V& rhs) {
  return ch_select(lhs > rhs, lhs, rhs);
}

}
}
