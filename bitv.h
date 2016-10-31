#pragma once

#include "bitbase.h"
#include "vec.h"

#define CHDL_CONCAT_GEN(T, TcB, TcA, TB, TA, cB, cA, B, A) \
  T inline const_concat_ref<TcB, TcA> operator,(cB b, cA a) { return make_const_concat_ref<TcB, TcA>(b, a); } \
  T inline const_concat_ref<TcB, TA> operator,(cB b, A a) { return make_const_concat_ref<TcB, TA>(b, a); } \
  T inline const_concat_ref<TB, TcA> operator,(B b, cA a) { return make_const_concat_ref<TB, TcA>(b, a); } \
  T inline concat_ref<TB, TA> operator,(B b, A a) { return make_concat_ref<TB, TA>(b, a); } \
  T inline const_concat_ref<TcB, TcA> ch_concat(cB b, cA a) { return make_const_concat_ref<TcB, TcA>(b, a); } \
  T inline const_concat_ref<TcB, TA> ch_concat(cB b, A a) { return make_const_concat_ref<TcB, TA>(b, a); } \
  T inline const_concat_ref<TB, TcA> ch_concat(B b, cA a) { return make_const_concat_ref<TB, TcA>(b, a); } \
  T inline concat_ref<TB, TA> ch_concat(B b, A a) { return make_concat_ref<TB, TA>(b, a); }

namespace chdl_internal {

template <unsigned N> class ch_bus;
using ch_signal = ch_bus<1>;

template <unsigned N> class ch_bitv;
using ch_logic = ch_bitv<1>;

template <unsigned N> 
class ch_bitv : public ch_bitbase<N> {
public:
  using base = ch_bitbase<N>;
  typedef typename base::bitstream_type bitstream_type;
  typedef ch_bus<N>  bus_type;
      
  ch_bitv() {}
  
  ch_bitv(const ch_bitv& rhs) : m_node(rhs.m_node.ensureInitialized(N)) {}
  
  ch_bitv(const ch_bitbase<N>& rhs) : m_node(rhs.get_node().get_impl()) {}
  
  ch_bitv(const bitvector& rhs) : m_node(rhs) {
    assert(rhs.get_size() == N);
  }
    
#define CHDL_DEF_CTOR(type) \
    ch_bitv(type value) : m_node(bitvector(value, N)) { \
      assert(m_node.get_size() == N); \
    }
  CHDL_DEF_CTOR(const std::initializer_list<uint32_t>&)
  CHDL_DEF_CTOR(char)
  CHDL_DEF_CTOR(int8_t)
  CHDL_DEF_CTOR(uint8_t)
  CHDL_DEF_CTOR(int16_t)
  CHDL_DEF_CTOR(uint16_t)
  CHDL_DEF_CTOR(int32_t)
  CHDL_DEF_CTOR(uint32_t)
  CHDL_DEF_CTOR(int64_t)
  CHDL_DEF_CTOR(uint64_t)
#undef CHDL_DEF_CTOR
  
  explicit ch_bitv(lnodeimpl* node) : m_node(node) {
    assert(m_node.get_size() == N);
  }
  
  ch_bitv& operator=(const ch_bitv& rhs) {
    m_node = rhs.m_node.ensureInitialized(N);
    return *this;
  }
  
  ch_bitv& operator=(const ch_bitbase<N>& rhs) {
    base::operator =(rhs);
    return *this;
  }
  
#define CHDL_DEF_AOP(type) \
  ch_bitv& operator=(type value) { \
    m_node.assign(bitvector(value, N)); \
    assert(m_node.get_size() == N); \
    return *this; \
  } 
  CHDL_DEF_AOP(const std::initializer_list<uint32_t>&)
  CHDL_DEF_AOP(char)
  CHDL_DEF_AOP(int8_t)
  CHDL_DEF_AOP(uint8_t)
  CHDL_DEF_AOP(int16_t)
  CHDL_DEF_AOP(uint16_t)
  CHDL_DEF_AOP(int32_t)
  CHDL_DEF_AOP(uint32_t)
  CHDL_DEF_AOP(int64_t)
  CHDL_DEF_AOP(uint64_t)
#undef CHDL_DEF_AOP
  
  lnode get_node() const override { 
    return m_node.ensureInitialized(N);
  }
  
protected:
  
  void read(bitstream_type& inout, size_t offset, size_t length) const override {
    m_node.read(inout, offset, length, N);
  }
  
  void write(size_t dst_offset, const bitstream_type& in, size_t src_offset, size_t src_length) override {
    m_node.write(dst_offset, in, src_offset, src_length, N);
  }
  
  lnode m_node;
};

// concatenation operator

CHDL_CONCAT_GEN(template <unsigned NB CHDL_COMMA typename TB CHDL_COMMA unsigned NA CHDL_COMMA typename TA>, 
                const_refbase<NB CHDL_COMMA TB>, const_refbase<NA CHDL_COMMA TA>,
                refbase<NB CHDL_COMMA TB>, refbase<NA CHDL_COMMA TA>,
                const const_refbase<NB CHDL_COMMA TB>&, const const_refbase<NA CHDL_COMMA TA>&,
                const refbase<NB CHDL_COMMA TB>&, const refbase<NA CHDL_COMMA TA>&)

CHDL_CONCAT_GEN(template <unsigned NB CHDL_COMMA unsigned NA>, 
                ch_bitbase<NB>, ch_bitbase<NA>,
                ch_bitbase<NB>, ch_bitbase<NA>,
                const ch_bitbase<NB>&, const ch_bitbase<NA>&,
                ch_bitbase<NB>&, ch_bitbase<NA>&)

//--

CHDL_CONCAT_GEN(template <unsigned NB CHDL_COMMA typename TB CHDL_COMMA unsigned NA>, 
                const_refbase<NB CHDL_COMMA TB>, ch_bitbase<NA>,
                refbase<NB CHDL_COMMA TB>, ch_bitbase<NA>,
                const const_refbase<NB CHDL_COMMA TB>&, const ch_bitbase<NA>&,
                const refbase<NB CHDL_COMMA TB>&, ch_bitbase<NA>&)
//--

CHDL_CONCAT_GEN(template <unsigned NB CHDL_COMMA unsigned NA CHDL_COMMA typename TA>, 
                ch_bitbase<NB>, const_refbase<NA CHDL_COMMA TA>,
                ch_bitbase<NB>, refbase<NA CHDL_COMMA TA>,
                const ch_bitbase<NB>&, const const_refbase<NA CHDL_COMMA TA>&,
                ch_bitbase<NB>&, const refbase<NA CHDL_COMMA TA>&)

#undef CHDL_CONCAT_GEN

// null operators

template <unsigned N>
ch_bitv<N> ch_null() {
  return ch_bitv<N>(createNullNode(N));
}

// slice operators

template <unsigned N, unsigned M>
const_slice_ref<ch_bitbase<M>, N> ch_slice(const ch_bitbase<M>& in, size_t index = 0) {
  return in.template slice<N>(index);
}

template <unsigned N, unsigned M>
slice_ref<ch_bitbase<M>, N> ch_slice(ch_bitbase<M>& in, size_t index = 0) {
  return in.template slice<N>(index);
}

template <unsigned N, unsigned M>
const_slice_ref<ch_bitbase<M>, N> ch_aslice(const ch_bitbase<M>& in, size_t index = 0) {
  return in.template aslice<N>(index);
}

template <unsigned N, unsigned M>
slice_ref<ch_bitbase<M>, N> ch_aslice(ch_bitbase<M>& in, size_t index = 0) {
  return in.template aslice<N>(index);
}

// extend operators

template <unsigned D>
class zext_select {
public:
    template <unsigned M>
    ch_bitv<(M+D)> operator() (const ch_bitbase<M>& in) {
      return (ch_bitv<D>(0x0), in);
    }
};

template <>
class zext_select<0> {
public:
    template <unsigned M>
    ch_bitv<M> operator() (const ch_bitbase<M>& in) {
      return in;
    }
};

template <unsigned M, unsigned D>
class sext_pad {
public:
    ch_bitv<(M+D)> operator() (const ch_bitbase<M>& in) {
      return (in[M-1], ch_bitv<D>(0x0), ch_slice<M-1>(in, 1));
    }    
};

template <unsigned D>
class sext_pad<1, D> {
public:
    ch_bitv<(1+D)> operator() (const ch_logicbase& in) {
      return (in, ch_bitv<D>(0x0));
    }
};

template <unsigned D>
class sext_select {
public:
    template <unsigned M>
    ch_bitv<(M+D)> operator() (const ch_bitbase<M>& in) {
      return sext_pad<M, D>()(in);
    }
};

template <>
class sext_select<0> {
public:
    template <unsigned M>
    ch_bitv<M> operator() (const ch_bitbase<M>& in) {
      return in;
    }
};

template <unsigned N, unsigned M>
ch_bitv<N> ch_zext(const ch_bitbase<M>& in) {
  static_assert(N >= M, "invalid extend size");
  return zext_select<(N-M)>()(in);
}

template <unsigned N, unsigned M>
ch_bitv<N> ch_sext(const ch_bitbase<M>& in) {
  static_assert(N >= M, "invalid extend size");
  return sext_select<(N-M)>()(in);
}

// shuffle operators

template <unsigned N, unsigned I>
ch_bitv<N> ch_shuffle(const ch_bitbase<N>& in, const std::array<uint32_t, I>& indices) {
  static_assert((I % N) == 0, "invalid shuffle indices size");
  for (unsigned i = 0; i < I; ++i) {
    ch_aslice<(N / I)>(in) = indices[i];
  }
}

// literal operators

template <unsigned N>
ch_bitv<N> ch_lit(uint32_t value) {
  return ch_bitv<N>(value);
}

template <unsigned N>
ch_bitv<N> ch_lit(const std::initializer_list<uint32_t>& value) {
  return ch_bitv<N>(value);
}

}
