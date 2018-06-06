#pragma once

#include "logic.h"

namespace ch {
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

  template <typename P, typename V,
            CH_REQUIRE_0(is_logic_compatible_v<P>),
            CH_REQUIRE_0(std::is_constructible_v<T, V>)>
  select_t<T>& operator()(const P& pred, const V& value) {
    static_assert(1 == width_v<P>, "invalid predicate size");
    impl_.push(get_lnode(pred), get_lnode<V, width_v<T>>(value));
    return *this;
  }
  
  template <typename V,
            CH_REQUIRE_0(std::is_constructible_v<T, V>)>
  auto operator()(const V& value) {
    return make_type<T>(impl_.eval(get_lnode<V, width_v<T>>(value)));
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

  template <typename P, typename T,
            CH_REQUIRE_0(is_equality_comparable_v<P, K>),
            CH_REQUIRE_0(std::is_constructible_v<V, T>)>
  case_t& operator()(const P& pred, const T& value) {
    impl_.push(get_lnode<P, width_v<K>>(pred),
               get_lnode<T, width_v<V>>(value));
    return *this;
  }

  template <typename T,
            CH_REQUIRE_0(std::is_constructible_v<V, T>)>
  auto operator()(const T& value) {
    return make_type<V>(impl_.eval(get_lnode<T, width_v<V>>(value)));
  }
  
protected:
  
  select_impl impl_;
};

template <typename P, typename V,
          CH_REQUIRE_0(is_logic_compatible_v<P>),
          CH_REQUIRE_0(is_logic_convertible_v<V>)>
auto ch_select(const P& pred, const V& value) {
  static_assert(1 == width_v<P>, "invalid predicate size");
  return select_t<logic_type_t<V>>(get_lnode(pred), get_lnode(value));
}

template <typename R, typename P, typename V,
          CH_REQUIRE_0(is_logic_convertible_v<P>),
          CH_REQUIRE_0(std::is_constructible_v<R, V>)>
auto ch_select(const P& pred, const V& value) {
  static_assert(1 == width_v<P>, "invalid predicate size");
  return select_t<R>(get_lnode(pred), get_lnode<V, width_v<R>>(value));
}

template <typename K, typename V, typename P,
          CH_REQUIRE_0(is_logic_convertible_v<K>),
          CH_REQUIRE_0(is_equality_comparable_v<P, K>),
          CH_REQUIRE_0(is_logic_convertible_v<V>)>
auto ch_case(const K& key, const P& pred, const V& value) {
  return case_t<K, logic_type_t<V>>(get_lnode(key),
                                    get_lnode<P, width_v<K>>(pred),
                                    get_lnode(value));
}

template <typename R, typename K, typename V, typename P,
          CH_REQUIRE_0(is_logic_convertible_v<K>),
          CH_REQUIRE_0(is_equality_comparable_v<P, K>),
          CH_REQUIRE_0(std::is_constructible_v<R, V>)>
auto ch_case(const K& key, const P& pred, const V& value) {
  return case_t<K, R>(get_lnode(key),
                      get_lnode<P, width_v<K>>(pred),
                      get_lnode<V, width_v<R>>(value));
}

template <typename P, typename U, typename V,
          CH_REQUIRE_0(width_v<deduce_type_t<false, U, V>> != 0),
          CH_REQUIRE_0(is_logic_convertible_v<P>),
          CH_REQUIRE_0(is_logic_convertible_v<U, width_v<deduce_type_t<false, U, V>>>),
          CH_REQUIRE_0(is_logic_convertible_v<V, width_v<deduce_type_t<false, U, V>>>)>
auto ch_select(const P& pred, const U& _true, const V& _false) {
  static_assert(1 == width_v<P>, "invalid predicate size");
  return make_type<logic_type_t<deduce_first_type_t<U, V>>>(
        createSelectNode(get_lnode(pred),
                         get_lnode<U, width_v<deduce_type_t<false, U, V>>>(_true),
                         get_lnode<V, width_v<deduce_type_t<false, U, V>>>(_false)));
}

template <typename R, typename P, typename U, typename V,
          CH_REQUIRE_0(is_logic_convertible_v<P>),
          CH_REQUIRE_0(std::is_constructible_v<R, U>),
          CH_REQUIRE_0(std::is_constructible_v<R, V>)>
auto ch_select(const P& pred, const U& _true, const V& _false) {
  static_assert(1 == width_v<P>, "invalid predicate size");
  return make_type<R>(createSelectNode(get_lnode(pred),
                                       get_lnode<U, R>(_true),
                                       get_lnode<V, R>(_false)));
}

template <typename U, typename V,
          CH_REQUIRE_0(width_v<deduce_type_t<false, U, V>> != 0),
          CH_REQUIRE_0(is_logic_convertible_v<U, width_v<deduce_type_t<false, U, V>>>),
          CH_REQUIRE_0(is_logic_convertible_v<V, width_v<deduce_type_t<false, U, V>>>)>
auto ch_min(const U& lhs, const V& rhs) {
  return ch_select(lhs < rhs, lhs, rhs);
}

template <typename U, typename V,
          CH_REQUIRE_0(width_v<deduce_type_t<false, U, V>> != 0),
          CH_REQUIRE_0(is_logic_convertible_v<U, width_v<deduce_type_t<false, U, V>>>),
          CH_REQUIRE_0(is_logic_convertible_v<V, width_v<deduce_type_t<false, U, V>>>)>
auto ch_max(const U& lhs, const V& rhs) {
  return ch_select(lhs > rhs, lhs, rhs);
}

}
}
