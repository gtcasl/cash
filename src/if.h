#pragma once

#include "bit.h"

namespace ch {
namespace internal {

using fvoid_t = std::function<void ()>;

void begin_branch(lnodeimpl* key);
void end_branch();

void cond_block(const lnode& pred, fvoid_t func);
void cond_block(fvoid_t func);

class if_t {
public:

  if_t() {
    begin_branch(nullptr);
  }

  ~if_t() {
    end_branch();
  }
};

using if_ptr = std::shared_ptr<if_t>;

class if_body_t;

class if_cond_t {
public:

  if_cond_t(const if_ptr& p_if)
    : if_(p_if)
  {}

  template <typename P,
            CH_REQUIRES(is_logic_compatible<P>::value),
            CH_REQUIRES(is_bit_compatible<P>::value)>
  if_body_t operator,(const P& pred);

  void operator,(const fvoid_t& body) {
    cond_block(body);
  }

protected:

  if_ptr if_;
};

class if_body_t {
public:

  if_body_t(const if_ptr& p_if, const lnode& pred)
    : if_(p_if)
    , pred_(pred)
  {}

  if_cond_t operator,(const fvoid_t& body);

protected:

  if_ptr if_;
  lnode  pred_;
};

template <typename P, typename, typename>
if_body_t if_cond_t::operator,(const P& pred) {
  static_assert(1 == width_v<P>, "invalid predicate size");
  return if_body_t(if_, get_lnode(pred));
}

inline if_cond_t if_body_t::operator,(const fvoid_t& body) {
  cond_block(pred_, body);
  return if_cond_t(if_);
}

template <typename P,
          CH_REQUIRES(is_bit_compatible<P>::value)>
if_body_t ch_if(const P& pred) {
  static_assert(1 == width_v<P>, "invalid predicate size");
  return if_body_t(std::make_shared<if_t>(), get_lnode(pred));
}

}
}

#define CH_IF(pred)   ch_if(pred), [&]()
#define CH_ELIF(pred) , pred, [&]()
#define CH_ELSE       , [&]()
