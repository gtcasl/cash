#pragma once

#include "bit.h"

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
  uint32_t src_width = sizeof(typename T::value_type) * 8;
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
  memory(uint32_t data_width, uint32_t num_items, bool write_enable);

  memory(uint32_t data_width,
         uint32_t num_items,
         bool write_enable,
         const std::vector<uint8_t>& init_data);

  const lnode& read(const lnode& addr) const;

  void write(const lnode& addr, const lnode& value);

  void write(const lnode& addr, const lnode& value, const lnode& enable);

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

  explicit ch_rom(const std::string& init_file)
    : mem_(width_v<T>, N, false, toByteVector(init_file, data_width, N))
  {}

  explicit ch_rom(const std::initializer_list<uint32_t>& init_data)
    : mem_(width_v<T>, N, false, toByteVector(init_data, data_width, N))
  {}

  template <typename U, std::size_t M, CH_REQUIRE_0(is_bitvector_array_type<U>::value)>
  explicit ch_rom(const std::array<U, M>& init_data)
    : mem_(width_v<T>, N, false, toByteVector(init_data, data_width, N))
  {}

  template <typename U, CH_REQUIRE_0(is_bitvector_array_type<U>::value)>
  explicit ch_rom(const std::vector<U>& init_data)
    : mem_(width_v<T>, N, false, toByteVector(init_data, data_width, N))
  {}

  template <typename U,
            CH_REQUIRE_0(is_bit_convertible<U, addr_width>::value)>
  auto read(const U& addr) const {
    auto l_addr = get_lnode<U, addr_width>(addr);
    return const_type_t<T>(bit_buffer(mem_.read(l_addr)));
  }
    
protected:
  memory mem_;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned N>
class ch_ram {
public:
  static constexpr unsigned size = N;
  static constexpr unsigned data_width = width_v<T>;
  static constexpr unsigned addr_width = log2ceil(N);
  using value_type = T;

  ch_ram() : mem_(width_v<T>, N, true, {}) {}

  explicit ch_ram(const std::string& init_file)
    : mem_(width_v<T>, N, true, toByteVector(init_file, data_width, N))
  {}

  explicit ch_ram(const std::initializer_list<uint32_t>& init_data)
    : mem_(width_v<T>, N, true, toByteVector(init_data, data_width, N))
  {}

  template <typename U, std::size_t M, CH_REQUIRE_0(is_bitvector_array_type<U>::value)>
  explicit ch_ram(const std::array<U, M>& init_data)
    : mem_(width_v<T>, N, true, toByteVector(init_data, data_width, N))
  {}

  template <typename U, CH_REQUIRE_0(is_bitvector_array_type<U>::value)>
  explicit ch_ram(const std::vector<U>& init_data)
    : mem_(width_v<T>, N, true, toByteVector(init_data, data_width, N))
  {}

  template <typename U,
            CH_REQUIRE_0(is_bit_convertible<U, addr_width>::value)>
  auto read(const U& addr) const {
    auto laddr = get_lnode<U, addr_width>(addr);
    return const_type_t<T>(bit_buffer(mem_.read(laddr)));
  }

  template <typename U, typename V,
            CH_REQUIRE_0(is_bit_convertible<U, addr_width>::value),
            CH_REQUIRE_0(is_cast_convertible<T, V>::value)>
  void write(const U& addr, const V& value) {
    auto l_addr  = get_lnode<U, addr_width>(addr);
    auto l_value = get_lnode<T, width_v<V>>(value);
    mem_.write(l_addr, l_value);
  }

  template <typename U, typename V, typename E,
            CH_REQUIRE_0(is_bit_convertible<U, addr_width>::value),
            CH_REQUIRE_0(is_cast_convertible<T, V>::value),
            CH_REQUIRE_0(is_bit_convertible<E>::value)>
  void write(const U& addr, const V& value, const E& enable) {
    static_assert(1 == width_v<E>, "invalid predicate size");
    auto l_addr   = get_lnode<U, addr_width>(addr);
    auto l_value  = get_lnode<T, width_v<V>>(value);
    auto l_enable = get_lnode(enable);
    mem_.write(l_addr, l_value, l_enable);
  }
    
protected:
  memory mem_;
};

}
}
