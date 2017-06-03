#pragma once

#include "bit.h"

namespace cash {
namespace detail {

lnodeimpl* createWireNode(lnodeimpl* src);

template <typename T>
class ch_wire : public T {
public:
  using value_type = T;
  using base = ch_bitbase<T::bit_count>;
  using data_type = typename T::data_type;
  using bus_type = typename T::bus_type;

  ch_wire() : T(createWireNode(nullptr)) {}

  ch_wire(const value_type& rhs)
    : T(createWireNode(get_node(rhs).get_impl()))
  {}
};

}}
