#pragma once

#include "bit.h"

namespace ch {
namespace internal {

class memimpl;

class memory {
public:
  memory(uint32_t data_width, uint32_t addr_width, bool writeEnable);

  template <typename T>
  void load(T it, std::size_t size, uint32_t data_width, uint32_t lines) {
    assert(size <= (lines * CH_CEILDIV(data_width, sizeof(decltype(*it)) * 8)));
    std::vector<uint8_t> packed;
    packed.reserve(CH_CEILDIV(data_width * lines, 8));
    uint32_t word_size(std::min<std::size_t>(sizeof(decltype(*it)) * 8, data_width));
    uint32_t curr_value(0), pos(0);
    for (;size--; ++it) {
      for (std::size_t i = 0; i < word_size; ++i) {
        curr_value |= ((*it >> i) & 0x1) << (pos & 0x7);
        if (0 == (++pos & 0x7)) {
          packed.emplace_back(curr_value);
          curr_value = 0;
        }
      }
    }
    if (pos & 0x7) {
      packed.emplace_back(curr_value);
    }
    this->load(packed);
  }

  void load(const std::string& init_file);

  const lnode& get_port(const lnode& addr) const;

protected:

  void load(const std::vector<uint8_t>& init_data);

  memimpl* impl_;
};

class mem_buffer : public bit_buffer_impl {
public:
  mem_buffer(const lnode& port) : bit_buffer_impl(port) {}

  void write(uint32_t dst_offset,
             const lnode& data,
             uint32_t src_offset,
             uint32_t length) override;
};

template <typename T, unsigned A>
class ch_rom {
public:
    ch_rom() : mem_(bitwidth_v<T>, A, false) {}
  
    ch_rom(const std::string& init_file) : mem_(bitwidth_v<T>, A, false) {
      mem_.load(init_file);
    }

    ch_rom(const std::initializer_list<uint32_t>& init_data) : mem_(bitwidth_v<T>, A, false) {
      mem_.load(init_data.begin(), init_data.size(), bitwidth_v<T>, 1 << A);
    }

    template <typename U, std::size_t N>
    ch_rom(const std::array<U, N>& init_data) : mem_(bitwidth_v<T>, A, false) {
      mem_.load(init_data.begin(), init_data.size(), bitwidth_v<T>, 1 << A);
    }

    template <typename U>
    ch_rom(const std::vector<U>& init_data) : mem_(bitwidth_v<T>, A, false) {
      mem_.load(init_data.begin(), init_data.size(), bitwidth_v<T>, 1 << A);
    }
    
    template <typename U,
              CH_REQUIRES(is_bit_convertible<U, A>::value)>
    const auto operator[](const U& addr) const {
      return const_type_t<T>(new mem_buffer(mem_.get_port(get_lnode<U, A>(addr))));
    }
    
protected:
    memory mem_;
};

template <typename T, unsigned A>
class ch_ram {
public:
    ch_ram() : mem_(bitwidth_v<T>, A, true) {}
  
    ch_ram(const std::string& init_file) : mem_(bitwidth_v<T>, A, true) {
      mem_.load(init_file);
    }

    ch_ram(const std::initializer_list<uint32_t>& init_data) : mem_(bitwidth_v<T>, A, true) {
      mem_.load(init_data.begin(), init_data.size(), bitwidth_v<T>, 1 << A);
    }

    template <typename U, std::size_t N>
    ch_ram(const std::array<U, N>& init_data) : mem_(bitwidth_v<T>, A, true) {
      mem_.load(init_data.begin(), init_data.size(), bitwidth_v<T>, 1 << A);
    }

    template <typename U>
    ch_ram(const std::vector<U>& init_data) : mem_(bitwidth_v<T>, A, true) {
      mem_.load(init_data.begin(), init_data.size(), bitwidth_v<T>, 1 << A);
    }
    
    template <typename U,
              CH_REQUIRES(is_bit_convertible<U, A>::value)>
    const auto operator[](const U& addr) const {
      return const_type_t<T>(new mem_buffer(mem_.get_port(get_lnode<U, A>(addr))));
    }
    
    template <typename U,
              CH_REQUIRES(is_bit_convertible<U, A>::value)>
    auto operator[](const U& addr) {
      return T(new mem_buffer(mem_.get_port(get_lnode<U, A>(addr))));
    }
    
protected:
    memory mem_;
};

}
}
