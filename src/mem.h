#pragma once

#include "bit.h"

namespace cash {
namespace internal {

class memimpl;

class memory {
public:
  memory(uint32_t data_width, uint32_t addr_width, bool writeEnable);

  void load(const std::string& file);

  template <typename T>
  void load(const std::vector<T>& data, uint32_t data_width, uint32_t lines) {
    assert(data.size() <= (lines * CH_CEILDIV(data_width, sizeof(T) * 8)));
    std::vector<uint8_t> packed;
    packed.reserve(CH_CEILDIV(data_width * lines, 8));
    uint8_t curr_value = 0;
    uint8_t curr_size = 0;
    for (const T& x : data) {
      for (int i = 0, n = std::min<uint32_t>(sizeof(T) * 8, data_width); i < n; ++i) {
        curr_value |= ((x >> i) & 0x1) << curr_size++;
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

  lnodeimpl* read(const lnode& addr) const;

  void write(const lnode& addr, const lnode& data);
  
private:

  void load(const std::vector<uint8_t>& data);

  memimpl* impl_;
};

template <unsigned W, unsigned A>
class ch_rom {
public:
    ch_rom() : mem_(W, A, false) {}
  
    ch_rom(const std::string& init_file) : mem_(W, A, false) {
      mem_.load(init_file);
    }
    
    template <typename T>
    ch_rom(const std::vector<T>& init_data) : mem_(W, A, false) {
      mem_.load<T>(init_data, W, 1 << A);
    }
    
    template <typename T>
    ch_rom(const std::initializer_list<T>& init_data) : mem_(W, A, false) {
      mem_.load<T>(init_data, W, 1 << A);
    }
    
    const auto operator[](const ch_bitbase<A>& addr) const {
      return make_bit<W>(mem_.read(get_lnode(addr)));
    }
    
    const auto operator[](const ch_bit<A>& addr) const {
      return make_bit<W>(mem_.read(get_lnode(addr)));
    }
    
private:
    memory mem_;
};

template <unsigned W, unsigned A>
class ch_ram {
public:    
    template <unsigned N>
    class reference : public ch_bitbase<N> {
    public:
      using base = ch_bitbase<N>;
      using base::operator=;
      using data_type = typename base::data_type;

    protected:

      reference(memory& mem, const ch_bitbase<A>& addr)
        : mem_(mem)
        , addr_(addr)
      {}

      reference(reference&&) = default;
      reference& operator=(reference&&) = default;

      void read_data(data_type& inout, size_t offset, size_t length) const override {
        CH_CHECK(offset + length <= N, "invalid read range");
        inout.push(mem_.read(get_lnode(addr_)), offset, length);
      }

      void write_data(size_t dst_offset, const data_type& in, size_t src_offset, size_t length) override {
        CH_CHECK(dst_offset != 0 || length != N, "partial update not supported!");
        if (0 == src_offset) {
          mem_.write(get_lnode(addr_), lnode(in));
        } else {
          data_type in2(length);
          for (auto slice : in) {
            if (src_offset < slice.length) {
              uint32_t len = std::min(slice.length - src_offset, length);
              in2.push(slice.src, slice.offset + src_offset, len);
              length -= len;
              if (0 == length)
                break;
              src_offset = slice.length;
            }
            src_offset -= slice.length;
          }
          mem_.write(get_lnode(addr_), lnode(in2));
        }
      }
      
      memory& mem_;
      const ch_bitbase<A>& addr_;
      
      friend class ch_ram;
    };  
  
    ch_ram() : mem_(W, A, true) {}
  
    ch_ram(const std::string& init_file) : mem_(W, A, true) {
      mem_.load(init_file);
    }

    template <typename T>
    ch_ram(const std::vector<T>& init_data) : mem_(W, A, true) {
      mem_.load<T>(init_data, W, 1 << A);
    }

    template <typename T>
    ch_ram(const std::initializer_list<T>& init_data) : mem_(W, A, true) {
      mem_.load<T>(init_data, W, 1 << A);
    }
    
    const auto operator[](const ch_bitbase<A>& addr) const {
      return make_bit<W>(mem_.read(get_lnode(addr)));
    }
    
    const auto operator[](const ch_bit<A>& addr) const {
      return make_bit<W>(mem_.read(get_lnode(addr)));
    }
    
    reference<W> operator[](const ch_bitbase<A>& addr) {
      return reference<W>(mem_, addr);
    }
    
    reference<W> operator[](const ch_bit<A>& addr) {
      return reference<W>(mem_, addr);
    }
    
private:    
    memory mem_;
};

}
}
