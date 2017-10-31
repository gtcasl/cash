#pragma once

#include "bit.h"

namespace ch {
namespace internal {

class memimpl;

std::vector<uint8_t> toByteVector(const std::string& init_file,
                                  uint32_t data_width,
                                  uint32_t num_items);

template <typename T>
static const auto toByteVector(const T& container,
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

class mem_buffer : public bit_buffer_impl {
public:
  mem_buffer(const lnode& port) : bit_buffer_impl(port) {}

  void write(uint32_t dst_offset,
             const lnode& data,
             uint32_t src_offset,
             uint32_t length) override;
};

///////////////////////////////////////////////////////////////////////////////

class memory {
public:
  memory(uint32_t data_width, uint32_t num_items, bool writeEnable);

  memory(uint32_t data_width,
         uint32_t num_items,
         bool writeEnable,
         const std::vector<uint8_t>& init_data);

  const lnode& get_port(const lnode& addr) const;

protected:

  memimpl* impl_;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned N>
class ch_rom {
public:
  static constexpr unsigned size = N;
  static constexpr unsigned data_width = bitwidth_v<T>;
  static constexpr unsigned addr_width = log2ceil(N);
  using value_type = T;

  ch_rom() : mem_(bitwidth_v<T>, N, false, {}) {}

  ch_rom(const std::string& init_file)
    : mem_(bitwidth_v<T>, N, false, toByteVector(init_file, data_width, N))
  {}

  ch_rom(const std::initializer_list<uint32_t>& init_data)
    : mem_(bitwidth_v<T>, N, false, toByteVector(init_data, data_width, N))
  {}

  template <typename U, std::size_t M>
  ch_rom(const std::array<U, M>& init_data)
    : mem_(bitwidth_v<T>, N, false, toByteVector(init_data, data_width, N))
  {}

  template <typename U>
  ch_rom(const std::vector<U>& init_data)
    : mem_(bitwidth_v<T>, N, false, toByteVector(init_data, data_width, N))
  {}

  template <typename U,
            CH_REQUIRES(is_bit_convertible<U, addr_width>::value)>
  const auto operator[](const U& addr) const {
    return const_type_t<T>(new mem_buffer(mem_.get_port(get_lnode<U, addr_width>(addr))));
  }
    
protected:
  memory mem_;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned N>
class ch_ram {
public:
  static constexpr unsigned size = N;
  static constexpr unsigned data_width = bitwidth_v<T>;
  static constexpr unsigned addr_width = log2ceil(N);
  using value_type = T;

  ch_ram() : mem_(bitwidth_v<T>, N, true, {}) {}

  ch_ram(const std::string& init_file)
    : mem_(bitwidth_v<T>, N, true, toByteVector(init_file, data_width, N))
  {}

  ch_ram(const std::initializer_list<uint32_t>& init_data)
    : mem_(bitwidth_v<T>, N, true, toByteVector(init_data, data_width, N))
  {}

  template <typename U, std::size_t M>
  ch_ram(const std::array<U, M>& init_data)
    : mem_(bitwidth_v<T>, N, true, toByteVector(init_data, data_width, N))
  {}

  template <typename U>
  ch_ram(const std::vector<U>& init_data)
    : mem_(bitwidth_v<T>, N, true, toByteVector(init_data, data_width, N))
  {}

  template <typename U,
            CH_REQUIRES(is_bit_convertible<U, addr_width>::value)>
  const auto operator[](const U& addr) const {
    return const_type_t<T>(new mem_buffer(mem_.get_port(get_lnode<U, addr_width>(addr))));
  }

  template <typename U,
            CH_REQUIRES(is_bit_convertible<U, addr_width>::value)>
  auto operator[](const U& addr) {
    return T(new mem_buffer(mem_.get_port(get_lnode<U, addr_width>(addr))));
  }
    
protected:
  memory mem_;
};

}
}
