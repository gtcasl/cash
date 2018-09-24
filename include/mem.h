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
  // the container has data elements size aligned to the buffer stride
  uint32_t src_width = sizeof(typename T::value_type) * 8;
  CH_CHECK(container.size() == (ceildiv(data_width, src_width) * num_items), "invalid input size");
  std::vector<uint8_t> packed(ceildiv<int>(data_width * num_items, 8));
  uint32_t word_size(std::min<uint32_t>(src_width, data_width));
  uint32_t curr_value(0), pos(0);
  for (auto item : container) {
    for (std::size_t i = 0; i < word_size; ++i) {
      curr_value |= ((item >> i) & 0x1) << (pos & 0x7);      
      if (0x7 == (pos & 0x7)) {
        packed[pos >> 3] = curr_value;
        curr_value = 0;
      }
      if ((++pos % data_width) == 0)
        break;
    }
  }
  if (pos & 0x7) {
    packed[pos >> 3] = curr_value;
    curr_value = 0;
  }
  assert(0 == curr_value);
  assert(pos == data_width * num_items);
  return packed;
}

///////////////////////////////////////////////////////////////////////////////

class memory {
public:
  memory(uint32_t data_width,
         uint32_t num_items,
         bool write_enable,
         bool sync_read,
         const std::vector<uint8_t>& init_data,
         const source_location& sloc);

  lnodeimpl* read(const lnode& addr,
                  const lnode& enable,
                  const source_location& sloc) const;

  void write(const lnode& addr,
             const lnode& value,
             const lnode& enable,
             const source_location& sloc);

protected:
  memimpl* impl_;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned N, bool SyncRead = false>
class ch_rom {
public:
  static constexpr unsigned size = N;
  static constexpr unsigned data_width = ch_width_v<T>;
  static constexpr unsigned addr_width = log2ceil(N);
  using value_type = T;

  explicit ch_rom(const std::string& init_file, CH_SLOC)
    : mem_(ch_width_v<T>, N, false, SyncRead, toByteVector(init_file, data_width, N), sloc)
  {}

  explicit ch_rom(const std::initializer_list<uint32_t>& init_data, CH_SLOC)
    : mem_(ch_width_v<T>, N, false, SyncRead, toByteVector(init_data, data_width, N), sloc)
  {}

  template <typename U, std::size_t M>
  explicit ch_rom(const std::array<U, M>& init_data, CH_SLOC)
    : mem_(ch_width_v<T>, N, false, SyncRead, toByteVector(init_data, data_width, N), sloc) {
    static_assert(is_bitvector_array_type_v<U>, "invalid type");
  }

  template <typename U>
  explicit ch_rom(const std::vector<U>& init_data, CH_SLOC)
    : mem_(ch_width_v<T>, N, false, SyncRead, toByteVector(init_data, data_width, N), sloc) {
    static_assert(is_bitvector_array_type_v<U>, "invalid type");
  }

  template <typename U>
  auto read(const U& addr, CH_SLOC) const {
    static_assert(is_bit_convertible_v<U, addr_width>, "invalid type");
    auto laddr = to_lnode<addr_width>(addr, sloc);
    return make_type<T>(mem_.read(laddr, bitvector(1, 1), sloc), sloc);
  }

  template <typename U, typename E>
  auto read(const U& addr, const E& enable, CH_SLOC) const {
    static_assert(is_bit_convertible_v<U, addr_width>, "invalid type");
    static_assert(is_bit_convertible_v<E, 1>, "invalid type");
    auto laddr = to_lnode<addr_width>(addr, sloc);
    auto l_enable = get_lnode(enable);
    return make_type<T>(mem_.read(laddr, l_enable, sloc), sloc);
  }

protected:
  memory mem_;
};

template <typename T, unsigned N, bool SyncRead = false>
class ch_mem {
public:
  static constexpr unsigned size = N;
  static constexpr unsigned data_width = ch_width_v<T>;
  static constexpr unsigned addr_width = log2ceil(N);
  using value_type = T;

  ch_mem(CH_SLOC) : mem_(ch_width_v<T>, N, true, SyncRead, {}, sloc) {}

  template <typename U>
  auto read(const U& addr, CH_SLOC) const {
    static_assert(is_bit_convertible_v<U, addr_width>, "invalid type");
    auto laddr = to_lnode<addr_width>(addr, sloc);
    return make_type<T>(mem_.read(laddr, bitvector(1, 1), sloc), sloc);
  }

  template <typename U, typename E>
  auto read(const U& addr, const E& enable, CH_SLOC) const {
    static_assert(is_bit_convertible_v<U, addr_width>, "invalid type");
    static_assert(is_bit_convertible_v<E, 1>, "invalid type");
    auto laddr = to_lnode<addr_width>(addr, sloc);
    auto l_enable = get_lnode(enable);
    return make_type<T>(mem_.read(laddr, l_enable, sloc), sloc);
  }

  template <typename U, typename V>
  void write(const U& addr, const V& value, CH_SLOC) {
    static_assert(is_bit_convertible_v<U, addr_width>, "invalid type");
    static_assert(std::is_constructible_v<T, V>, "invalid type");
    auto l_addr  = to_lnode<addr_width>(addr, sloc);
    auto l_value = to_lnode<T>(value, sloc);
    mem_.write(l_addr, l_value, bitvector(1, 1), sloc);
  }

  template <typename U, typename V, typename E>
  void write(const U& addr, const V& value, const E& enable, CH_SLOC) {
    static_assert(is_bit_convertible_v<U, addr_width>, "invalid type");
    static_assert(std::is_constructible_v<T, V>, "invalid type");
    static_assert(is_bit_convertible_v<E, 1>, "invalid type");
    auto l_addr   = to_lnode<addr_width>(addr, sloc);
    auto l_value  = to_lnode<T>(value, sloc);
    auto l_enable = get_lnode(enable);
    mem_.write(l_addr, l_value, l_enable, sloc);
  }
    
protected:
  memory mem_;
};

}
}
