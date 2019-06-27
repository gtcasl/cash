#pragma once

#include "uint.h"

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
         const std::string& name,
         const sloc_getter& slg = sloc_getter());

  lnode aread(const lnode& addr) const;

  lnode sread(const lnode& addr, const lnode& enable) const;

  void write(const lnode& addr, const lnode& value, const lnode& enable);

protected:
  memimpl* impl_;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned N, bool ForceLogicRAM = false>
class ch_rom {
public:
  static constexpr unsigned size = N;
  static constexpr unsigned data_width = ch_width_v<T>;
  static constexpr unsigned addr_width = log2up(N);
  using value_type = T;

  explicit ch_rom(const std::string& init_file)
    : mem_(ch_width_v<T>, N, loadInitData(init_file, data_width, N), ForceLogicRAM, idname<T>())
  {}

  explicit ch_rom(const std::initializer_list<uint32_t>& init_data)
    : mem_(ch_width_v<T>, N, loadInitData(init_data, data_width, N), ForceLogicRAM, idname<T>())
  {}

  template <typename U, std::size_t M>
  explicit ch_rom(const std::array<U, M>& init_data)
    : mem_(ch_width_v<T>, N, loadInitData(init_data, data_width, N), ForceLogicRAM, idname<T>()) {
    static_assert(std::is_integral_v<U>, "invalid type");
  }

  template <typename U>
  explicit ch_rom(const std::vector<U>& init_data)
    : mem_(ch_width_v<T>, N, loadInitData(init_data, data_width, N), ForceLogicRAM, idname<T>()) {
    static_assert(std::is_integral_v<U>, "invalid type");
  }

  template <typename U,
            CH_REQUIRE(std::is_integral_v<U>)>
  explicit ch_rom(const U& value)
    : mem_(ch_width_v<T>, N, sdata_from_fill(value, data_width, N), ForceLogicRAM, idname<T>())
  {}

  auto read(const ch_uint<addr_width>& addr) const {
    CH_SOURCE_LOCATION(1);
    auto laddr = to_lnode<addr_width>(addr);
    return make_logic_type<T>(mem_.aread(laddr));
  }

protected:
  memory mem_;
};

template <typename T, unsigned N, bool SyncRead = false>
class ch_mem {
public:
  static constexpr unsigned size = N;
  static constexpr unsigned data_width = ch_width_v<T>;
  static constexpr unsigned addr_width = log2up(N);
  using value_type = T;

  ch_mem() : mem_(ch_width_v<T>, N, {}, false, idname<T>()) {}

  explicit ch_mem(const std::string& init_file)
    : mem_(ch_width_v<T>, N, loadInitData(init_file, data_width, N), false, idname<T>())
  {}

  explicit ch_mem(const std::initializer_list<uint32_t>& init_data)
    : mem_(ch_width_v<T>, N, loadInitData(init_data, data_width, N), false, idname<T>())
  {}

  template <typename U, std::size_t M>
  explicit ch_mem(const std::array<U, M>& init_data)
    : mem_(ch_width_v<T>, N, loadInitData(init_data, data_width, N), false, idname<T>()) {
    static_assert(std::is_integral_v<U>, "invalid type");
  }

  template <typename U>
  explicit ch_mem(const std::vector<U>& init_data)
    : mem_(ch_width_v<T>, N, loadInitData(init_data, data_width, N), false, idname<T>()) {
    static_assert(std::is_integral_v<U>, "invalid type");
  }

  template <typename U,
            CH_REQUIRE(std::is_integral_v<U>)>
  explicit ch_mem(const U& value)
    : mem_(ch_width_v<T>, N, sdata_from_fill(value, data_width, N), false, idname<T>())
  {}

  auto read(const ch_uint<addr_width>& addr) const {
    CH_SOURCE_LOCATION(1);
    auto laddr = to_lnode<addr_width>(addr);
    if constexpr (SyncRead) {
      return make_logic_type<T>(mem_.sread(laddr, sdata_type(1,1)));
    } else {
      return make_logic_type<T>(mem_.aread(laddr));
    }
  }

  auto read(const ch_uint<addr_width>& addr, const ch_bool& enable) const {
    static_assert(SyncRead, "invalid memory type");
    CH_SOURCE_LOCATION(1);
    auto laddr = to_lnode<addr_width>(addr);
    auto l_enable = get_lnode(enable);
    return make_logic_type<T>(mem_.sread(laddr, l_enable));
  }

  template <typename U>
  void write(const ch_uint<addr_width>& addr, const U& value) {
    static_assert(std::is_constructible_v<T, U>, "invalid type");
    CH_SOURCE_LOCATION(1);
    auto l_addr  = to_lnode<addr_width>(addr);
    auto l_value = to_lnode<T>(value);
    mem_.write(l_addr, l_value, sdata_type(1,1));
  }

  template <typename U, typename E>
  void write(const ch_uint<addr_width>& addr, const U& value, const E& enable) {
    static_assert(std::is_constructible_v<T, U>, "invalidvalue  type");
    static_assert(is_bitbase_v<E>, "invalid enable type");
    static_assert(ch_width_v<E> * (ch_width_v<T> / ch_width_v<E>) == ch_width_v<T>, "invalid enable size");
    CH_SOURCE_LOCATION(1);
    auto l_addr   = to_lnode<addr_width>(addr);
    auto l_value  = to_lnode<T>(value);
    auto l_enable = get_lnode(enable);
    mem_.write(l_addr, l_value, l_enable);
  }
    
protected:
  memory mem_;
};

}
}
