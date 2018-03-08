#pragma once

#include "if.h"

namespace ch {
namespace internal {

class switch_t {
public:
  switch_t(const lnode& key, const source_location& sloc) {
    begin_branch(key.get_impl(), sloc);
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
  switch_body_t(const switch_ptr& p_switch, const bitvector& value)
    : switch_(p_switch)
    , value_(value)
  {}

  switch_case_t<K> operator,(const fvoid_t& body);

protected:
  switch_ptr switch_;
  bitvector value_;
};

template <typename K>
class switch_case_t {
public:
  switch_case_t(const switch_ptr& p_switch) : switch_(p_switch) {}

  template <typename V,
            CH_REQUIRE_0(is_cast_convertible<K, V>::value)>
  switch_body_t<K> operator,(const V& value) {
    return switch_body_t<K>(switch_, bitvector(width_v<K>, value));
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

template <typename K,
          CH_REQUIRE_0(is_bit_convertible<K>::value)>
auto ch_switch(const K& key, const source_location& sloc = CH_SOURCE_LOCATION) {
  return switch_case_t<K>(std::make_shared<switch_t>(get_lnode(key), sloc));
}

}
}

#define CH_SWITCH(key)  ch_switch(key)
#define CH_CASE(pred)   , pred, [&]()
#define CH_DEFAULT      , [&]()
