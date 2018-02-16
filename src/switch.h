#pragma once

#include "if.h"

namespace ch {
namespace internal {

class switch_t {
public:
  switch_t(const lnode& key) {
    begin_branch(key.get_impl());
  }
  ~switch_t() {
    end_branch();
  }

  template <typename K> friend class switch_body_t;
};
using switch_ptr = std::shared_ptr<switch_t>;

template <typename K> class switch_case_t;

template <typename K> class switch_body_t;

template <typename K>
class switch_case_t {
public:
  switch_case_t(const switch_ptr& p_switch) : switch_(p_switch) {}

  template <typename V,
            CH_REQUIRES(is_cast_convertible<K, V>::value)>
  switch_body_t<K> operator,(const V& value);

  void operator,(const fvoid_t& body) {
    cond_block(body);
  }

protected:
  switch_ptr switch_;
};

template <typename K>
class switch_body_t {
public:
  switch_body_t(const switch_ptr& p_switch, const lnode& value)
    : switch_(p_switch)
    , value_(value)
  {}

  switch_case_t<K> operator,(const fvoid_t& body);

protected:
  switch_ptr switch_;
  lnode value_;
};

template <typename K>
template <typename V, typename>
switch_body_t<K> switch_case_t<K>::operator,(const V& value) {
  return switch_body_t<K>(switch_, get_lnode<V, width_v<K>>(value));
}

template <typename K>
switch_case_t<K> switch_body_t<K>::operator,(const fvoid_t& body) {
  cond_block(value_, body);
  return switch_case_t<K>(switch_);
}

template <typename K,
          CH_REQUIRES(is_bit_convertible<K>::value)>
auto ch_switch(const K& key) {
  return switch_case_t<K>(std::make_shared<switch_t>(get_lnode(key)));
}

}
}

#define CH_SWITCH(key)  ch_switch(key)
#define CH_CASE(pred)   , pred, [&]()
#define CH_DEFAULT      , [&]()
