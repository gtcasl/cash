#pragma once

#include "device.h"

namespace ch {
namespace internal {

template <typename T>
class ch_module final : private device {
public:  
  using base = device;
  using io_type = ch_flip_io<decltype(T::io)>;

  io_type io;

  ch_module(CH_SLOC)
    : device(std::type_index(typeid(T)), identifier_from_typeid(typeid(T).name()).c_str())
    , io(build(T()).io, sloc)
  {}

  template <typename U0,
            CH_REQUIRE_0(std::is_constructible_v<T, U0>)>
  ch_module(U0&& arg0, CH_SLOC)
    : device(std::type_index(typeid(T)), identifier_from_typeid(typeid(T).name()).c_str())
    , io(build(T(std::forward<U0>(arg0))).io, sloc)
  {}

  template <typename U0, typename U1,
            CH_REQUIRE_0(std::is_constructible_v<T, U0, U1>)>
  ch_module(U0&& arg0, U1&& arg1, CH_SLOC)
    : device(std::type_index(typeid(T)), identifier_from_typeid(typeid(T).name()).c_str())
    , io(build(T(std::forward<U0>(arg0),
                 std::forward<U1>(arg1))).io, sloc)
  {}

  template <typename U0, typename U1, typename U2,
            CH_REQUIRE_0(std::is_constructible_v<T, U0, U1, U2>)>
  ch_module(U0&& arg0, U1&& arg1, U2&& arg2, CH_SLOC)
    : device(std::type_index(typeid(T)), identifier_from_typeid(typeid(T).name()).c_str())
    , io(build(T(std::forward<U0>(arg0),
                 std::forward<U1>(arg1),
                 std::forward<U2>(arg2))).io, sloc)
  {}

  template <typename U0, typename U1, typename U2, typename U3,
            CH_REQUIRE_0(std::is_constructible_v<T, U0, U1, U2, U3>)>
  ch_module(U0&& arg0, U1&& arg1, U2&& arg2, U3&& arg3, CH_SLOC)
    : device(std::type_index(typeid(T)), identifier_from_typeid(typeid(T).name()).c_str())
    , io(build(T(std::forward<U0>(arg0),
                 std::forward<U1>(arg1),
                 std::forward<U2>(arg2),
                 std::forward<U3>(arg3))).io, sloc)
  {}

  template <typename U0, typename U1, typename U2, typename U3, typename... Us,
            CH_REQUIRE_0(std::is_constructible_v<T, U0, U1, U2, U3, Us...>)>
  ch_module(U0&& arg0, U1&& arg1, U2&& arg2, U3&& arg3, Us&&... args)
    : device(std::type_index(typeid(T)), identifier_from_typeid(typeid(T).name()).c_str())
    , io(build(T(std::forward<U0>(arg0),
                 std::forward<U1>(arg1),
                 std::forward<U2>(arg2),
                 std::forward<U3>(arg3),
                 std::forward<Us>(args)...)).io, source_location())
  {}

  ch_module(ch_module&& other)
    : base(std::move(other))
    , io(std::move(other.io))
  {}

protected:

  auto&& build(T&& obj) {
    obj.describe();
    this->compile();
    return obj;
  }

  ch_module(const ch_module& other) = delete;

  ch_module& operator=(const ch_module& other) = delete;

  ch_module& operator=(ch_module&& other) = delete;
};

}
}
