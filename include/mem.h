#pragma once

#include "logic.h"

namespace ch {
namespace internal {

class memimpl;

sdata_type loadInitData(const std::string& file,
                        uint32_t data_width,
                        uint32_t num_items);

template <typename T>
static sdata_type loadInitData(const T& container,
                               uint32_t data_width,
                               uint32_t num_items) {
  // the container has data elements size aligned to the buffer stride
  static constexpr uint32_t WORD_SIZE = bitwidth_v<block_type>;
  static constexpr uint32_t WORD_MASK = WORD_SIZE - 1;

  sdata_type out(data_width * num_items);
  uint32_t src_width = bitwidth_v<typename T::value_type>;
  CH_CHECK(container.size() == (ceildiv(data_width, src_width) * num_items), "invalid input size");
  uint32_t chunk_width(std::min<uint32_t>(src_width, data_width));
  block_type word(0);
  uint32_t pos(0);
  for (auto item : container) {
    for (uint32_t i = 0; i < chunk_width; ++i) {
      word |= block_type((item >> i) & 0x1) << (pos & WORD_MASK);
      if (WORD_MASK == (pos & WORD_MASK)) {
        out.word(pos / WORD_SIZE) = word;
        word = 0;
      }
      if ((++pos % data_width) == 0)
        break;
    }
  }
  if (pos & WORD_MASK) {
    out.word(pos / WORD_SIZE) = word;
    word = 0;
  }
  assert(0 == word);
  assert(pos == data_width * num_items);
  return out;
}

///////////////////////////////////////////////////////////////////////////////

class memory {
public:
  memory(uint32_t data_width,
         uint32_t num_items,
         const sdata_type& init_data,
         bool force_logic_ram,
         const source_location& sloc);

  lnodeimpl* aread(const lnode& addr,
                   const source_location& sloc) const;

  lnodeimpl* sread(const lnode& addr,
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

template <typename T, unsigned N, bool ForceLogicRAM = false>
class ch_rom {
public:
  static constexpr unsigned size = N;
  static constexpr unsigned data_width = ch_width_v<T>;
  static constexpr unsigned addr_width = log2ceil(N);
  using value_type = T;

  explicit ch_rom(const std::string& init_file, CH_SLOC)
    : mem_(ch_width_v<T>, N, loadInitData(init_file, data_width, N), ForceLogicRAM, sloc)
  {}

  explicit ch_rom(const std::initializer_list<uint32_t>& init_data, CH_SLOC)
    : mem_(ch_width_v<T>, N, loadInitData(init_data, data_width, N), ForceLogicRAM, sloc)
  {}

  template <typename U, std::size_t M>
  explicit ch_rom(const std::array<U, M>& init_data, CH_SLOC)
    : mem_(ch_width_v<T>, N, loadInitData(init_data, data_width, N), ForceLogicRAM, sloc) {
    static_assert(is_bitvector_array_type_v<U>, "invalid type");
  }

  template <typename U>
  explicit ch_rom(const std::vector<U>& init_data, CH_SLOC)
    : mem_(ch_width_v<T>, N, loadInitData(init_data, data_width, N), ForceLogicRAM, sloc) {
    static_assert(is_bitvector_array_type_v<U>, "invalid type");
  }

  template <typename U>
  explicit ch_rom(const sdata_type& init_data, CH_SLOC)
    : mem_(ch_width_v<T>, N, init_data, ForceLogicRAM, sloc) {
    static_assert(is_bitvector_array_type_v<U>, "invalid type");
  }

  template <typename U>
  auto read(const U& addr, CH_SLOC) const {
    static_assert(is_bit_convertible_v<U, addr_width>, "invalid type");
    auto laddr = to_lnode<addr_width>(addr, sloc);
    return make_type<T>(mem_.aread(laddr, sloc), sloc);
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

  ch_mem(CH_SLOC) : mem_(ch_width_v<T>, N, {}, false, sloc) {}

  explicit ch_mem(const std::string& init_file, CH_SLOC)
    : mem_(ch_width_v<T>, N, loadInitData(init_file, data_width, N), false, sloc)
  {}

  explicit ch_mem(const std::initializer_list<uint32_t>& init_data, CH_SLOC)
    : mem_(ch_width_v<T>, N, loadInitData(init_data, data_width, N), false, sloc)
  {}

  template <typename U, std::size_t M>
  explicit ch_mem(const std::array<U, M>& init_data, CH_SLOC)
    : mem_(ch_width_v<T>, N, loadInitData(init_data, data_width, N), false, sloc) {
    static_assert(is_bitvector_array_type_v<U>, "invalid type");
  }

  template <typename U>
  explicit ch_mem(const std::vector<U>& init_data, CH_SLOC)
    : mem_(ch_width_v<T>, N, loadInitData(init_data, data_width, N), false, sloc) {
    static_assert(is_bitvector_array_type_v<U>, "invalid type");
  }

  template <typename U>
  explicit ch_mem(const sdata_type& init_data, CH_SLOC)
    : mem_(ch_width_v<T>, N, init_data, false, sloc) {
    static_assert(is_bitvector_array_type_v<U>, "invalid type");
  }

  template <typename U>
  auto read(const U& addr, CH_SLOC) const {
    static_assert(is_bit_convertible_v<U, addr_width>, "invalid type");
    auto laddr = to_lnode<addr_width>(addr, sloc);
    if constexpr (SyncRead) {
      return make_type<T>(mem_.sread(laddr, sdata_type(1,1), sloc), sloc);
    } else {
      return make_type<T>(mem_.aread(laddr, sloc), sloc);
    }
  }

  template <typename U, typename E>
  auto read(const U& addr, const E& enable, CH_SLOC) const {
    static_assert(SyncRead, "invalid memory type");
    static_assert(is_bit_convertible_v<U, addr_width>, "invalid type");
    static_assert(is_bit_convertible_v<E, 1>, "invalid type");
    auto laddr = to_lnode<addr_width>(addr, sloc);
    auto l_enable = get_lnode(enable);
    return make_type<T>(mem_.sread(laddr, l_enable, sloc), sloc);
  }

  template <typename U, typename V>
  void write(const U& addr, const V& value, CH_SLOC) {
    static_assert(is_bit_convertible_v<U, addr_width>, "invalid type");
    static_assert(std::is_constructible_v<T, V>, "invalid type");
    auto l_addr  = to_lnode<addr_width>(addr, sloc);
    auto l_value = to_lnode<T>(value, sloc);
    mem_.write(l_addr, l_value, sdata_type(1,1), sloc);
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
