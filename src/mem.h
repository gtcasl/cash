#pragma once

#include "bit.h"

namespace cash {
namespace detail {

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
    
    ch_bit<W> operator[](const ch_bitbase<A>& addr) const {
      return ch_bit<W>(mem_.read(get_node(addr)));
    }
    
    ch_bit<W> operator[](const ch_bit<A>& addr) const {
      return ch_bit<W>(mem_.read(get_node(addr)));
    }
    
private:
    memory mem_;
};

template <unsigned W, unsigned A>
class ch_ram {
public:    
    class reference {
    public:    
      
      void operator=(const ch_bitbase<W>& data) {
        mem_.write(get_node(addr_), get_node(data));
      }
      
      void operator=(const ch_bit<W>& data) {
        mem_.write(get_node(addr_), get_node(data));
      }
      
      operator ch_bit<W>() const {
        return ch_bit<W>(mem_.read(get_node(addr_)));
      }
      
    protected:
      
      reference(memory& mem, const ch_bitbase<A>& addr)
        : mem_(mem)
        , addr_(addr)
      {}
      
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
    
    ch_bit<W> operator[](const ch_bitbase<A>& addr) const {
      return ch_bit<W>(mem_.read(get_node(addr)));
    }
    
    ch_bit<W> operator[](const ch_bit<A>& addr) const {
      return ch_bit<W>(mem_.read(get_node(addr)));
    }
    
    reference operator[](const ch_bitbase<A>& addr) {
      return reference(mem_, addr);
    }
    
    reference operator[](const ch_bit<A>& addr) {
      return reference(mem_, addr);
    }
    
private:    
    memory mem_;
};

}
}
