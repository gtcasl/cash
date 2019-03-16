#pragma once

#include "if.h"

namespace ch {
namespace internal {

class switch_t {
public:

  switch_t(const lnode& key) {
    begin_branch(key.impl());
  }

  ~switch_t() {
    end_branch();
  }

  template <typename K> friend class switch_body_t;
};

using switch_ptr = std::shared_ptr<switch_t>;

template <typename K> class switch_case_t;

template <typename K>
class switch_body_t {
public:

  switch_body_t(const switch_ptr& p_switch, const sdata_type& value)
    : switch_(p_switch)
    , value_(value)
  {}

  switch_case_t<K> operator,(const fvoid_t& body);

protected:

  switch_ptr switch_;
  sdata_type value_;
};

template <typename K>
class switch_case_t {
public:

  switch_case_t(const switch_ptr& p_switch) : switch_(p_switch) {}

  template <typename V,
            CH_REQUIRE_0(!std::is_convertible_v<V, fvoid_t>)>
  switch_body_t<K> operator,(const V& value) {
    static_assert(is_equality_comparable_v<K, V>, "invalid type");
    if constexpr (std::is_enum_v<V>) {
      return switch_body_t<K>(switch_, sdata_type(ch_width_v<K>, (int)value));
    } else {
      return switch_body_t<K>(switch_, sdata_type(ch_width_v<K>, value));
    }
  }

  void operator,(const fvoid_t& body) {
    cond_block(body);
  }

protected:

  switch_ptr switch_;
};

template <typename K>
switch_case_t<K> switch_body_t<K>::operator,(const fvoid_t& body) {
  cond_block(value_, body);
  return switch_case_t<K>(switch_);
}

template <typename K>
auto ch_switch(const K& key) {
  static_assert(is_bit_base_v<K>, "invalid type");
  CH_SOURCE_LOCATION(1);
  return switch_case_t<K>(std::make_shared<switch_t>(get_lnode(key)));
}

}
}

#define CH_SWITCH(key)  ch_switch(key)
#define CH_CASE(pred)   , pred, [&]()
#define CH_DEFAULT      , [&]()
