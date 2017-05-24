#pragma once

#include "bitbase.h"
#include "vec.h"

namespace cash {
namespace detail {

template <unsigned N> class ch_bus;
using ch_signal = ch_bus<1>;

template <unsigned N> class ch_bit;
using ch_logic = ch_bit<1>;

void createPrintNode(lnodeimpl* cond, const std::string& format, 
                     const std::initializer_list<lnodeimpl*>& args);

template <unsigned N> 
class ch_bit : public ch_bitbase<N> {
public:
  using base = ch_bitbase<N>;
  using data_type = typename base::data_type;
  using bus_type = ch_bus<N>;
      
  ch_bit() : node_(N) {}
  
  ch_bit(const ch_bit& rhs) : node_(rhs.node_.ensureInitialized(N)) {}
  
  ch_bit(const ch_bitbase<N>& rhs) : node_(get_node(rhs).get_impl()) {}
  
  ch_bit(const bitvector& rhs) : node_(rhs) {
    assert(rhs.get_size() == N);
  }
  
  ch_bit(bool value) : node_(bitvector(value ? 0x1 : 0x0, N)) { \
    static_assert(N == 1, "bool assignents only allowed on single-bit objects");
  }
    
#define CH_DEF_CTOR(type) \
    ch_bit(type value) : node_(bitvector(value, N)) { \
      assert(node_.get_size() == N); \
    }
  CH_DEF_CTOR(const std::initializer_list<uint32_t>&)
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
  
  explicit ch_bit(lnodeimpl* node) : node_(node) {
    assert(node_.get_size() == N);
  }
  
  ch_bit& operator=(const ch_bit& rhs) {
    node_ = rhs.node_.ensureInitialized(N);
    return *this;
  }
  
  ch_bit& operator=(const ch_bitbase<N>& rhs) {
    base::operator =(rhs);
    return *this;
  }
  
  ch_bit& operator=(bool value) {
    static_assert(N == 1, "bool assignents only allowed on single-bit objects");
    node_.assign(bitvector(value ? 0x1 : 0x0 , N)); \
    assert(node_.get_size() == N); \
    return *this;
  } 
  
#define CH_DEF_AOP(type) \
  ch_bit& operator=(type value) { \
    node_.assign(bitvector(value, N)); \
    assert(node_.get_size() == N); \
    return *this; \
  } 
  CH_DEF_AOP(const std::initializer_list<uint32_t>&)
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
  
protected:

  void read_data(data_type& inout, size_t offset, size_t length) const override {
    node_.read_data(inout, offset, length, N);
  }
  
  void write_data(size_t dst_offset, const data_type& in, size_t src_offset, size_t src_length) override {
    node_.write_data(dst_offset, in, src_offset, src_length, N);
  }
  
  lnode node_;

  template <unsigned N_> friend lnode get_node(const ch_bit<N_>& b);
};

template <unsigned N>
lnode get_node(const ch_bit<N>& b) {
  return b.node_.ensureInitialized(N);
}

// concatenation operator

#define CH_CONCAT_GEN(cB, cA, B, A) \
  template <unsigned NB, unsigned NA> auto operator,(cB b, cA a) { return b.template concat(a); } \
  template <unsigned NB, unsigned NA> auto operator,(cB b, A a) { return b.template concat(a); } \
  template <unsigned NB, unsigned NA> auto operator,(B b, cA a) { return b.template concat(a); } \
  template <unsigned NB, unsigned NA> auto operator,(B b, A a) { return b.template concat(a); } \
  template <unsigned NB, unsigned NA> auto ch_concat(cB b, cA a) { return b.template concat(a); } \
  template <unsigned NB, unsigned NA> auto ch_concat(cB b, A a) { return b.template concat(a); } \
  template <unsigned NB, unsigned NA> auto ch_concat(B b, cA a) { return b.template concat(a); } \
  template <unsigned NB, unsigned NA> auto ch_concat(B b, A a) { return b.template concat(a); }

CH_CONCAT_GEN(const const_bitref<NB>&, const const_bitref<NA>&,
                const bitref<NB>&, const bitref<NA>&)

CH_CONCAT_GEN(const const_bitref<NB>&, const ch_bitbase<NA>&,
                const bitref<NB>&, ch_bitbase<NA>&)

CH_CONCAT_GEN(const ch_bitbase<NB>&, const const_bitref<NA>&,
                ch_bitbase<NB>&, const bitref<NA>&)

CH_CONCAT_GEN(const ch_bitbase<NB>&, const ch_bitbase<NA>&,
                ch_bitbase<NB>&, ch_bitbase<NA>&)

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
    ch_bit<(1+D)> operator() (const ch_logicbase& in) {
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
ch_bit<N> ch_shuffle(const ch_bitbase<N>& in, const std::array<uint32_t, I>& indices) {
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
  createPrintNode(nullptr, format, {get_node(args).get_impl()...});
}

template <typename...Args>
void ch_print(const ch_logicbase& cond, const std::string& format, const Args& ...args) {
  createPrintNode(get_node(cond).get_impl(), format, {get_node(args).get_impl()...});
}

template <typename...Args>
void ch_print(const ch_logic& cond, const std::string& format, const Args& ...args) {
  createPrintNode(get_node(cond).get_impl(), format, {get_node(args).get_impl()...});
}

}
}
