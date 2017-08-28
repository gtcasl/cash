#pragma once

#include "bitbase.h"
#include "vec.h"

namespace cash {
namespace detail {

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

  ch_bit clone() const {
    return node_.clone(N);
  }
  
protected:

  ch_bit(lnodeimpl* node) : node_(node) {
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
                  size_t src_length) override {
    node_.write_data(dst_offset, in, src_offset, src_length, N);
  }

  lnode node_;

  template <unsigned M> friend ch_bit<M> make_bit(lnodeimpl* node);
};

template <unsigned N>
ch_bit<N> make_bit(lnodeimpl* node) {
  return ch_bit<N>(node);
}

// concatenation operator

#define CH_CONCAT_GEN(cB, cA, B, A) \
  template <unsigned NB, unsigned NA> \
  auto operator,(cB b, cA a) { \
    return b.template concat(a); \
  } \
  template <unsigned NB, unsigned NA> \
  auto operator,(cB b, A a) { \
    return b.template concat(a); \
  } \
  template <unsigned NB, unsigned NA> \
  auto operator,(B b, cA a) { \
    return b.template concat(a); \
  } \
  template <unsigned NB, unsigned NA> \
  auto operator,(B b, A a) { \
    return b.template concat(a); \
  } \
  template <unsigned NB, unsigned NA> \
  auto ch_concat(cB b, cA a) { \
    return b.template concat(a); \
  } \
  template <unsigned NB, unsigned NA> \
  auto ch_concat(cB b, A a) { \
    return b.template concat(a); \
  } \
  template <unsigned NB, unsigned NA> \
  auto ch_concat(B b, cA a) { \
    return b.template concat(a); \
  } \
  template <unsigned NB, unsigned NA> \
  auto ch_concat(B b, A a) { \
    return b.template concat(a); \
  }

CH_CONCAT_GEN(const const_bitref<NB>&,
              const const_bitref<NA>&,
              const bitref<NB>&,
              const bitref<NA>&)

CH_CONCAT_GEN(const const_bitref<NB>&,
              const ch_bitbase<NA>&,
              const bitref<NB>&,
              ch_bitbase<NA>&)

CH_CONCAT_GEN(const ch_bitbase<NB>&,
              const const_bitref<NA>&,
              ch_bitbase<NB>&,
              const bitref<NA>&)

CH_CONCAT_GEN(const ch_bitbase<NB>&,
              const ch_bitbase<NA>&,
              ch_bitbase<NB>&,
              ch_bitbase<NA>&)

#undef CH_CONCAT_GEN

// slice operators

template <unsigned N, unsigned M>
auto ch_slice(const ch_bitbase<M>& in, size_t index = 0) {
  return in.template slice<N>(index);
}

template <unsigned N, unsigned M>
auto ch_slice(ch_bitbase<M>& in, size_t index = 0) {
  return in.template slice<N>(index);
}

template <unsigned N, unsigned M>
auto ch_aslice(const ch_bitbase<M>& in, size_t index = 0) {
  return in.template aslice<N>(index);
}

template <unsigned N, unsigned M>
auto ch_aslice(ch_bitbase<M>& in, size_t index = 0) {
  return in.template aslice<N>(index);
}

// extend operators

template <unsigned D>
class zext_select {
public:
    template <unsigned M>
    ch_bit<(M+D)> operator() (const ch_bitbase<M>& in) {
      return (ch_bit<D>(0x0), in);
    }
};

template <>
class zext_select<0> {
public:
    template <unsigned M>
    ch_bit<M> operator() (const ch_bitbase<M>& in) {
      return in;
    }
};

template <unsigned M, unsigned D>
class sext_pad {
public:
    ch_bit<(M+D)> operator() (const ch_bitbase<M>& in) {
      return (in[M-1], ch_bit<D>(0x0), ch_slice<M-1>(in, 1));
    }    
};

template <unsigned D>
class sext_pad<1, D> {
public:
    ch_bit<(1+D)> operator() (const ch_bitbase<1>& in) {
      return (in, ch_bit<D>(0x0));
    }
};

template <unsigned D>
class sext_select {
public:
    template <unsigned M>
    ch_bit<(M+D)> operator() (const ch_bitbase<M>& in) {
      return sext_pad<M, D>()(in);
    }
};

template <>
class sext_select<0> {
public:
    template <unsigned M>
    ch_bit<M> operator() (const ch_bitbase<M>& in) {
      return in;
    }
};

template <unsigned N, unsigned M>
ch_bit<N> ch_zext(const ch_bitbase<M>& in) {
  static_assert(N >= M, "invalid extend size");
  return zext_select<(N-M)>()(in);
}

template <unsigned N, unsigned M>
ch_bit<N> ch_sext(const ch_bitbase<M>& in) {
  static_assert(N >= M, "invalid extend size");
  return sext_select<(N-M)>()(in);
}

// shuffle operators

template <unsigned N, unsigned I>
ch_bit<N> ch_shuffle(const ch_bitbase<N>& in,
                     const std::array<uint32_t, I>& indices) {
  static_assert((I % N) == 0, "invalid indices size");
  ch_bit<N> ret;
  for (unsigned i = 0; i < I; ++i) {
    ret.template aslice<<(N / I)>(i) = in.template aslice<(N / I)>(indices[i]);
  }
  return ret;
}

// utility functions

ch_bit<64> ch_tick();

template <typename...Args>
void ch_print(const std::string& format, const Args& ...args) {
  createPrintNode(format, {get_node(args)...});
}

template <typename...Args>
void ch_print(const ch_bitbase<1>& pred,
              const std::string& format,
              const Args& ...args) {
  createPrintNode(get_node(pred), format, {get_node(args)...});
}

template <typename...Args>
void ch_print(const ch_bit<1>& pred,
              const std::string& format,
              const Args& ...args) {
  createPrintNode(get_node(pred), format, {get_node(args)...});
}

}
}
