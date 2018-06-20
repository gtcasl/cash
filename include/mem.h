#pragma once

#include "logic.h"

namespace ch {
namespace internal {

class memimpl;

std::vector<uint8_t> toByteVector(const std::string& init_file,
                                  uint32_t data_width,
                                  uint32_t num_items);

template <typename T>
static auto toByteVector(const T& container,
                         uint32_t data_width,
                         uint32_t num_items) {
  uint32_t src_width = CH_WIDTH_OF(typename T::value_type);
  CH_CHECK(container.size() == (CH_CEILDIV(data_width, src_width) * num_items), "invalid input size");
  std::vector<uint8_t> packed(CH_CEILDIV(data_width * num_items, 8));
  uint32_t word_size(std::min<uint32_t>(src_width, data_width));
  uint32_t curr_value(0), pos(0);
  for (auto item : container) {
    for (std::size_t i = 0; i < word_size; ++i, ++pos) {
      curr_value |= ((item >> i) & 0x1) << (pos & 0x7);
      if (0x7 == (pos & 0x7)) {
        packed[pos >> 3] = curr_value;
        curr_value = 0;
      }
    }
  }
  if (pos & 0x7) {
    packed[pos >> 3] = curr_value;
  }
  return packed;
}

///////////////////////////////////////////////////////////////////////////////

class memory {
public:
  memory(uint32_t data_width,
         uint32_t num_items,
         bool write_enable,
         const std::vector<uint8_t>& init_data,
         const source_location& sloc);

  lnodeimpl* read(const lnode& addr, const source_location& sloc) const;

  void write(const lnode& addr,
             const lnode& value,
             const lnode& enable,
             const source_location& sloc);

protected:
  memimpl* impl_;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned N>
class ch_rom {
public:
  static constexpr unsigned size = N;
  static constexpr unsigned data_width = width_v<T>;
  static constexpr unsigned addr_width = log2ceil(N);
  using value_type = T;

  explicit ch_rom(const std::string& init_file, CH_SLOC)
    : mem_(width_v<T>, N, false, toByteVector(init_file, data_width, N), sloc)
  {}

  explicit ch_rom(const std::initializer_list<uint32_t>& init_data, CH_SLOC)
    : mem_(width_v<T>, N, false, toByteVector(init_data, data_width, N), sloc)
  {}

  template <typename U, std::size_t M,
            CH_REQUIRE_0(is_bitvector_array_type_v<U>)>
  explicit ch_rom(const std::array<U, M>& init_data, CH_SLOC)
    : mem_(width_v<T>, N, false, toByteVector(init_data, data_width, N), sloc)
  {}

  template <typename U,
            CH_REQUIRE_0(is_bitvector_array_type_v<U>)>
  explicit ch_rom(const std::vector<U>& init_data, CH_SLOC)
    : mem_(width_v<T>, N, false, toByteVector(init_data, data_width, N), sloc)
  {}

  template <typename U,
            CH_REQUIRE_0(is_logic_convertible_v<U, addr_width>)>
  auto read(const U& addr, CH_SLOC) const {
    auto laddr = get_lnode<U, addr_width>(addr);
    return make_type<T>(mem_.read(laddr, sloc), sloc);
  }

protected:
  memory mem_;
};

template <typename T, unsigned N>
class ch_mem {
public:
  static constexpr unsigned size = N;
  static constexpr unsigned data_width = width_v<T>;
  static constexpr unsigned addr_width = log2ceil(N);
  using value_type = T;

  ch_mem(CH_SLOC) : mem_(width_v<T>, N, true, {}, sloc) {}

  template <typename U,
            CH_REQUIRE_0(is_logic_convertible_v<U, addr_width>)>
  auto read(const U& addr, CH_SLOC) const {
    auto laddr = get_lnode<U, addr_width>(addr);
    return make_type<T>(mem_.read(laddr, sloc), sloc);
  }

  template <typename U, typename V,
            CH_REQUIRE_0(is_logic_convertible_v<U, addr_width>),
            CH_REQUIRE_0(std::is_constructible_v<T, V>)>
  void write(const U& addr, const V& value, CH_SLOC) {
    auto l_addr  = get_lnode<U, addr_width>(addr);
    auto l_value = get_lnode<T, data_width>(value);
    mem_.write(l_addr, l_value, bitvector(1, 1), sloc);
  }

  template <typename U, typename V, typename E,
            CH_REQUIRE_0(is_logic_convertible_v<U, addr_width>),
            CH_REQUIRE_0(std::is_constructible_v<T, V>),
            CH_REQUIRE_0(is_logic_convertible_v<E>)>
  void write(const U& addr, const V& value, const E& enable, CH_SLOC) {
    static_assert(1 == width_v<E>, "invalid predicate size");
    auto l_addr   = get_lnode<U, addr_width>(addr);
    auto l_value  = get_lnode<T, data_width>(value);
    auto l_enable = get_lnode(enable);
    mem_.write(l_addr, l_value, l_enable, sloc);
  }
    
protected:
  memory mem_;
};

}
}
