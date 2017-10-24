#pragma once

#include "bit.h"

namespace ch {
namespace internal {

class memimpl;

class memory {
public:
  memory(uint32_t data_width, uint32_t addr_width, bool writeEnable);

  template <typename T>
  void load(T it, T end, std::size_t size, uint32_t data_width, uint32_t lines) {
    assert(size <= (lines * CH_CEILDIV(data_width, sizeof(decltype(*it)) * 8)));
    std::vector<uint8_t> packed;
    packed.reserve(CH_CEILDIV(data_width * lines, 8));
    uint8_t curr_value = 0;
    uint8_t curr_size = 0;
    for (;it != end; ++it) {
      for (std::size_t i = 0, n = std::min<std::size_t>(sizeof(decltype(*it)) * 8, data_width); i < n; ++i) {
        curr_value |= ((*it >> i) & 0x1) << curr_size++;
        if (curr_size == 8) {
          packed.emplace_back(curr_value);
          curr_value = 0;
          curr_size = 0;
        }
      }
    }
    if (curr_size) {
      packed.emplace_back(curr_value);
    }
    this->load(packed);
  }

  void load(const std::string& init_file);

  const lnode& get_port(const lnode& addr) const;

  void write(const lnode& port, const lnode& data);

protected:

  void load(const std::vector<uint8_t>& init_data);

  memimpl* impl_;
};

template <unsigned N>
class memport_ref {
public:
  using traits = logic_traits<N, memport_ref, const_bit<N>, ch_bit<N>, ch_scalar<N>>;

  template <typename T, CH_REQUIRES(is_bit_convertible<T, N>::value)>
  memport_ref& operator=(const T& rhs) {
    mem_.write(buffer_.get_data(), get_lnode<T, N>(rhs));
    return *this;
  }

protected:
  memport_ref(memory& mem, const lnode& addr)
    : buffer_(mem.get_port(addr))
    , mem_(mem)
  {}

  const bit_buffer& get_buffer() const {
    return buffer_;
  }

  bit_buffer& get_buffer() {
    return buffer_;
  }

  bit_buffer buffer_;
  memory& mem_;

  friend class bit_accessor;
  template <unsigned W, unsigned A> friend class ch_ram;
};

template <unsigned W, unsigned A>
class ch_rom {
public:
    ch_rom() : mem_(W, A, false) {}
  
    ch_rom(const std::string& init_file) : mem_(W, A, false) {
      mem_.load(init_file);
    }

    ch_rom(const std::initializer_list<uint32_t>& init_data) : mem_(W, A, false) {
      mem_.load(init_data.begin(), init_data.end(), init_data.size(), W, 1 << A);
    }

    template <typename T, std::size_t N>
    ch_rom(const std::array<T, N>& init_data) : mem_(W, A, false) {
      mem_.load(init_data.begin(), init_data.end(), init_data.size(), W, 1 << A);
    }

    template <typename T>
    ch_rom(const std::vector<T>& init_data) : mem_(W, A, false) {
      mem_.load(init_data.begin(), init_data.end(), init_data.size(), W, 1 << A);
    }
    
    template <typename T,
              CH_REQUIRES(is_bit_convertible<T, A>::value)>
    const auto operator[](const T& addr) const {
      return make_type<ch_bit<W>>(mem_.get_port(get_lnode<T, A>(addr)));
    }
    
protected:
    memory mem_;
};

template <unsigned W, unsigned A>
class ch_ram {
public:
    ch_ram() : mem_(W, A, true) {}
  
    ch_ram(const std::string& init_file) : mem_(W, A, true) {
      mem_.load(init_file);
    }

    ch_ram(const std::initializer_list<uint32_t>& init_data) : mem_(W, A, true) {
      mem_.load(init_data.begin(), init_data.end(), init_data.size(), W, 1 << A);
    }

    template <typename T, std::size_t N>
    ch_ram(const std::array<T, N>& init_data) : mem_(W, A, true) {
      mem_.load(init_data.begin(), init_data.end(), init_data.size(), W, 1 << A);
    }

    template <typename T>
    ch_ram(const std::vector<T>& init_data) : mem_(W, A, true) {
      mem_.load(init_data.begin(), init_data.end(), init_data.size(), W, 1 << A);
    }
    
    template <typename T,
              CH_REQUIRES(is_bit_convertible<T, A>::value)>
    const auto operator[](const T& addr) const {
      return make_type<ch_bit<W>>(mem_.get_port(get_lnode<T, A>(addr)));
    }
    
    template <typename T,
              CH_REQUIRES(is_bit_convertible<T, A>::value)>
    memport_ref<W> operator[](const T& addr) {
      return memport_ref<W>(mem_, get_lnode<T, A>(addr));
    }
    
protected:
    memory mem_;
};

}
}
