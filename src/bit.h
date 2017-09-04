#pragma once

#include "bitbase.h"
#include "vec.h"

namespace cash {
namespace internal {

void createPrintNode(const std::string& format,
                     const std::initializer_list<lnode>& args);

void createPrintNode(const lnode& pred,
                     const std::string& format,
                     const std::initializer_list<lnode>& args);

template <unsigned N> class ch_bus;

template <unsigned N>
class ch_bit : public ch_bitbase<N> {
public:
  using base = ch_bitbase<N>;
  using data_type = typename base::data_type;
  using bus_type = ch_bus<N>;
      
  ch_bit() : node_(N) {}
  
  ch_bit(const ch_bit& rhs) : node_(rhs.node_, N) {}

  ch_bit(ch_bit&& rhs) : node_(std::move(rhs.node_), N) {}

  ch_bit(const ch_bitbase<N>& rhs) : node_(get_node(rhs), N) {}
  
  ch_bit(const bitvector& rhs) : node_(rhs) {}

  ch_bit(const ch_literal<N>& rhs) : node_(rhs.value_) {}
    
#define CH_DEF_CTOR(type) \
  ch_bit(type value) : node_(bitvector(N, value)) {}
  CH_DEF_CTOR(const std::initializer_list<uint32_t>&)
  CH_DEF_CTOR(bool)
  CH_DEF_CTOR(char)
  CH_DEF_CTOR(int8_t)
  CH_DEF_CTOR(uint8_t)
  CH_DEF_CTOR(int16_t)
  CH_DEF_CTOR(uint16_t)
  CH_DEF_CTOR(int32_t)
  CH_DEF_CTOR(uint32_t)
  CH_DEF_CTOR(int64_t)
  CH_DEF_CTOR(uint64_t)
#undef CH_DEF_CTOR
  
  ch_bit& operator=(const ch_bit& rhs) {
    node_.assign(rhs.node_, N);
    return *this;
  }

  ch_bit& operator=(ch_bit&& rhs) {
    node_.move(rhs.node_, N);
    return *this;
  }
  
  ch_bit& operator=(const bitvector& rhs) {
    node_.assign(rhs);
    return *this;
  }

  ch_bit& operator=(const ch_bitbase<N>& rhs) {
    data_type data(N);
    rhs.read_data(data, 0, N);
    this->write_data(0, data, 0, N);
    return *this;
  }
  
#define CH_DEF_AOP(type) \
  ch_bit& operator=(type value) { \
    node_.assign(bitvector(N, value)); \
    return *this; \
  } 
  CH_DEF_AOP(const std::initializer_list<uint32_t>&)
  CH_DEF_AOP(bool)
  CH_DEF_AOP(char)
  CH_DEF_AOP(int8_t)
  CH_DEF_AOP(uint8_t)
  CH_DEF_AOP(int16_t)
  CH_DEF_AOP(uint16_t)
  CH_DEF_AOP(int32_t)
  CH_DEF_AOP(uint32_t)
  CH_DEF_AOP(int64_t)
  CH_DEF_AOP(uint64_t)
#undef CH_DEF_AOP

  const auto clone() const {
    return make_bit<N>(node_.clone(N));
  }
  
protected:

  ch_bit(const lnode& node) : node_(std::move(node)) {
    assert(node_.get_size() == N);
  }

  void read_data(data_type& inout,
                 size_t offset,
                 size_t length) const override {
    node_.read_data(inout, offset, length, N);
  }
  
  void write_data(size_t dst_offset,
                  const data_type& in,
                  size_t src_offset,
                  size_t length) override {
    node_.write_data(dst_offset, in, src_offset, length, N);
  }

  lnode node_;

  template <unsigned M> friend const ch_bit<M> make_bit(const lnode& node);
};

template <unsigned N>
const ch_bit<N> make_bit(const lnode& node) {
  assert(node.get_size() == N);
  return ch_bit<N>(node);
}

// concatenation operator

template <unsigned NB, unsigned NA>
const auto ch_cat(const ch_bitbase<NB>& b, const ch_bitbase<NA>& a) {
  const auto na(get_node(a));
  const auto nb(get_node(b));
  lnode::data_type data(NA+NB);
  data.push_back({na, 0, NA});
  data.push_back({nb, 0, NB});
  return make_bit<NA+NB>(data);
}

template <unsigned NB, unsigned NA>
const auto operator,(const ch_bitbase<NB>& b, const ch_bitbase<NA>& a) {
  return ch_cat(b, a);
}

template<class... Args>
concatref<Args...> ch_tie(Args&... args) {
  return concatref<Args...>(args...);
}

// slice operators

template <unsigned N, unsigned M>
const auto ch_slice(const ch_bitbase<M>& in, size_t index = 0) {
  return in.template slice<N>(index);
}

template <unsigned N, unsigned M>
const auto ch_aslice(const ch_bitbase<M>& in, size_t index = 0) {
  return in.template aslice<N>(index);
}

// extend operators

template <unsigned D>
class zext_select {
public:
    template <unsigned M>
    const auto operator() (const ch_bitbase<M>& in) {
      return (ch_bit<D>(0x0), in);
    }
};

template <>
class zext_select<0> {
public:
    template <unsigned M>
    const ch_bit<M> operator() (const ch_bitbase<M>& in) {
      return in;
    }
};

template <unsigned M, unsigned D>
class sext_pad {
public:
   const auto operator() (const ch_bitbase<M>& in) {
      return (in[M-1], ch_bit<D>(0x0), ch_slice<M-1>(in, 1));
    }    
};

template <unsigned D>
class sext_pad<1, D> {
public:
    const auto operator() (const ch_bitbase<1>& in) {
      return (in, ch_bit<D>(0x0));
    }
};

template <unsigned D>
class sext_select {
public:
    template <unsigned M>
    const auto operator() (const ch_bitbase<M>& in) {
      return sext_pad<M, D>()(in);
    }
};

template <>
class sext_select<0> {
public:
    template <unsigned M>
   const ch_bit<M> operator() (const ch_bitbase<M>& in) {
      return in;
    }
};

template <unsigned N, unsigned M>
const auto ch_zext(const ch_bitbase<M>& in) {
  static_assert(N >= M, "invalid extend size");
  return zext_select<(N-M)>()(in);
}

template <unsigned N, unsigned M>
const auto ch_sext(const ch_bitbase<M>& in) {
  static_assert(N >= M, "invalid extend size");
  return sext_select<(N-M)>()(in);
}

// shuffle operators

template <unsigned N, unsigned I>
const auto ch_shuffle(const ch_bitbase<N>& in,
                     const std::array<uint32_t, I>& indices) {
  static_assert((I % N) == 0, "invalid indices size");
  ch_bit<N> ret;
  for (unsigned i = 0; i < I; ++i) {
    ret.template aslice<<(N / I)>(i) = in.template aslice<(N / I)>(indices[i]);
  }
  return ret;
}

// utility functions

const ch_bit<64> ch_getTick();

template <typename...Args>
void ch_print(const std::string& format, const Args& ...args) {
  createPrintNode(format, {get_node(args)...});
}

}
}
