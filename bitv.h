#pragma once

#include "bitbase.h"
#include "vec.h"

#define CHDL_CONCAT_GEN(T, TcB, TcA, TB, TA, cB, cA, B, A) \
  T inline const_concat_ref<TcB, TcA> ch_concat(cB b, cA a) { return const_concat_ref<TcB, TcA>(b, a); } \
  T inline const_concat_ref<TcB, TA> ch_concat(cB b, A a) { return const_concat_ref<TcB, TA>(b, a); } \
  T inline const_concat_ref<TB, TcA> ch_concat(B b, cA a) { return const_concat_ref<TB, TcA>(b, a); } \
  T inline concat_ref<TB, TA> ch_concat(B b, A a) { return concat_ref<TB, TA>(b, a); } \
  T inline const_concat_ref<TcB, TcA> operator,(cB b, cA a) { return const_concat_ref<TcB, TcA>(b, a); } \
  T inline const_concat_ref<TcB, TA> operator,(cB b, A a) { return const_concat_ref<TcB, TA>(b, a); } \
  T inline const_concat_ref<TB, TcA> operator,(B b, cA a) { return const_concat_ref<TB, TcA>(b, a); } \
  T inline concat_ref<TB, TA> operator,(B b, A a) { return concat_ref<TB, TA>(b, a); }

namespace chdl_internal {

template <unsigned N> 
class ch_bitv : public ch_bitbase<N> {
public:
  using base = ch_bitbase<N>;
  using base::operator=;
  typedef typename base::data_type data_type;
      
  ch_bitv() {}
  
  ch_bitv(const ch_bitv& v) : m_node(v.m_node, N) {}
  
  explicit ch_bitv(const ch_bitbase<N>& v) {
    this->operator =(v);
  }
  
  explicit ch_bitv(const ch_node& node) : m_node(node, N) {}
  
  ch_bitv(uint32_t value) : m_node({value}, N) {}
  
  ch_bitv(const std::initializer_list<uint32_t>& value) : m_node(value, N) {} 
  
  operator const ch_node&() const { 
    return m_node; 
  }
  
  operator ch_node&() { 
    return m_node; 
  }
  
protected:
  
  void read(std::vector< partition<data_type> >& out, size_t offset, size_t length) const override {
    out.push_back({m_node, offset, length});
  }
  
  void write(size_t dst_offset, const std::vector< partition<data_type> >& src, size_t src_offset, size_t src_length) override {
    size_t offset = 0;
    size_t length = src_offset;
    for (auto& p : src) {
      if (src_offset < offset + p.length) {
        size_t s_length = std::min(p.length, src_length);        
        size_t s_offset = p.offset + (length - offset);
        length = offset + p.length;
        m_node.assign(N, dst_offset, p.data, s_offset, s_length);         
        dst_offset += s_length;
        src_length -= s_length;        
      }
      offset += p.length;
    }
  }
  
  ch_node m_node;
};

class ch_logic : public ch_bitv<1> {
public:  
  using base = ch_bitv<1>;
  using base::base::operator=;
  
  ch_logic() {}
  
  ch_logic(const ch_logic& l) : base(l) {}
  
  ch_logic(const ch_bitv<1>& v) : base(v) {}
  
  ch_logic(const ch_bitbase<1>& v) : base(v) {}
  
  ch_logic(bool value) : base(value ? 1 : 0) {}
  
  ch_logic(char value) : base((value == 0 || value == '0') ? 0 : 1) {}
  
  template <unsigned M>
  const_slice_ref<M, base::base> slice(size_t index) = delete;
  
  template <unsigned M>
  slice_ref<M, base::base> slice(size_t index) = delete;
  
  template <unsigned M>
  const_slice_ref<M, base::base> aslice(size_t index) const = delete;
  
  template <unsigned M>
  slice_ref<M, base::base> aslice(size_t index) = delete;
  
  const_subscript_ref<base::base> operator[](size_t index) const = delete;
  
  subscript_ref<base::base> operator[](size_t index) = delete;  
  
protected:

  using base::m_node;
};

// concatenation operator

CHDL_CONCAT_GEN(template <typename BB CHDL_COMMA typename BA CHDL_COMMA typename AB CHDL_COMMA typename AA>, 
                const_concat_ref<BB CHDL_COMMA BA>, const_concat_ref<AB CHDL_COMMA AA>,
                concat_ref<BB CHDL_COMMA BA>, concat_ref<AB CHDL_COMMA AA>,
                const const_concat_ref<BB CHDL_COMMA BA>&, const const_concat_ref<AB CHDL_COMMA AA>&,
                const concat_ref<BB CHDL_COMMA BA>&, const concat_ref<AB CHDL_COMMA AA>&)

CHDL_CONCAT_GEN(template <unsigned NB CHDL_COMMA typename TB CHDL_COMMA unsigned NA CHDL_COMMA typename TA>, 
                const_slice_ref<NB CHDL_COMMA TB>, const_slice_ref<NA CHDL_COMMA TA>,
                slice_ref<NB CHDL_COMMA TB>, slice_ref<NA CHDL_COMMA TA>,
                const const_slice_ref<NB CHDL_COMMA TB>&, const const_slice_ref<NA CHDL_COMMA TA>&,
                const slice_ref<NB CHDL_COMMA TB>&, const slice_ref<NA CHDL_COMMA TA>&)

CHDL_CONCAT_GEN(template <unsigned NB CHDL_COMMA unsigned NA>, 
                ch_bitbase<NB>, ch_bitbase<NA>,
                ch_bitbase<NB>, ch_bitbase<NA>,
                const ch_bitbase<NB>&, const ch_bitbase<NA>&,
                ch_bitbase<NB>&, ch_bitbase<NA>&)

CHDL_CONCAT_GEN(, 
                ch_logic, ch_logic,
                ch_logic, ch_logic,
                const ch_logic&, const ch_logic&,
                ch_logic&, ch_logic&)

CHDL_CONCAT_GEN(template <typename BB CHDL_COMMA typename BA CHDL_COMMA unsigned NA CHDL_COMMA typename TA>, 
                const_concat_ref<BB CHDL_COMMA BA>, const_slice_ref<NA CHDL_COMMA TA>,
                concat_ref<BB CHDL_COMMA BA>, slice_ref<NA CHDL_COMMA TA>,
                const const_concat_ref<BB CHDL_COMMA BA>&, const const_slice_ref<NA CHDL_COMMA TA>&,
                const concat_ref<BB CHDL_COMMA BA>&, const slice_ref<NA CHDL_COMMA TA>&)

CHDL_CONCAT_GEN(template <typename BB CHDL_COMMA typename BA CHDL_COMMA unsigned NA>, 
                const_concat_ref<BB CHDL_COMMA BA>, ch_bitbase<NA>,
                concat_ref<BB CHDL_COMMA BA>, ch_bitbase<NA>,
                const const_concat_ref<BB CHDL_COMMA BA>&, const ch_bitbase<NA>&,
                const concat_ref<BB CHDL_COMMA BA>&, ch_bitbase<NA>&)

CHDL_CONCAT_GEN(template <typename BB CHDL_COMMA typename BA>, 
                const_concat_ref<BB CHDL_COMMA BA>, ch_logic,
                concat_ref<BB CHDL_COMMA BA>, ch_logic,
                const const_concat_ref<BB CHDL_COMMA BA>&, const ch_logic&,
                const concat_ref<BB CHDL_COMMA BA>&, ch_logic&)

CHDL_CONCAT_GEN(template <unsigned NB CHDL_COMMA typename TB CHDL_COMMA typename AB CHDL_COMMA typename AA>, 
                const_slice_ref<NB CHDL_COMMA TB>, const_concat_ref<AB CHDL_COMMA AA>,
                slice_ref<NB CHDL_COMMA TB>, concat_ref<AB CHDL_COMMA AA>,
                const const_slice_ref<NB CHDL_COMMA TB>&, const const_concat_ref<AB CHDL_COMMA AA>&,
                const slice_ref<NB CHDL_COMMA TB>&, const concat_ref<AB CHDL_COMMA AA>&)

CHDL_CONCAT_GEN(template <unsigned NB CHDL_COMMA typename AB CHDL_COMMA typename AA>, 
                ch_bitbase<NB>, const_concat_ref<AB CHDL_COMMA AA>,
                ch_bitbase<NB>, concat_ref<AB CHDL_COMMA AA>,
                const ch_bitbase<NB>&, const const_concat_ref<AB CHDL_COMMA AA>&,
                ch_bitbase<NB>&, const concat_ref<AB CHDL_COMMA AA>&)

CHDL_CONCAT_GEN(template <typename AB CHDL_COMMA typename AA>, 
                ch_logic, const_concat_ref<AB CHDL_COMMA AA>,
                ch_logic, concat_ref<AB CHDL_COMMA AA>,
                const ch_logic&, const const_concat_ref<AB CHDL_COMMA AA>&,
                ch_logic&, const concat_ref<AB CHDL_COMMA AA>&)

CHDL_CONCAT_GEN(template <unsigned NB CHDL_COMMA typename TB CHDL_COMMA unsigned NA>, 
                const_slice_ref<NB CHDL_COMMA TB>, ch_bitbase<NA>,
                slice_ref<NB CHDL_COMMA TB>, ch_bitbase<NA>,
                const const_slice_ref<NB CHDL_COMMA TB>&, const ch_bitbase<NA>&,
                const slice_ref<NB CHDL_COMMA TB>&, ch_bitbase<NA>&)

CHDL_CONCAT_GEN(template <unsigned NB CHDL_COMMA typename TB>, 
                const_slice_ref<NB CHDL_COMMA TB>, ch_logic,
                slice_ref<NB CHDL_COMMA TB>, ch_logic,
                const const_slice_ref<NB CHDL_COMMA TB>&, const ch_logic&,
                const slice_ref<NB CHDL_COMMA TB>&, ch_logic&)

CHDL_CONCAT_GEN(template <unsigned NB CHDL_COMMA unsigned NA CHDL_COMMA typename TA>, 
                ch_bitbase<NB>, const_slice_ref<NA CHDL_COMMA TA>,
                ch_bitbase<NB>, slice_ref<NA CHDL_COMMA TA>,
                const ch_bitbase<NB>&, const const_slice_ref<NA CHDL_COMMA TA>&,
                ch_bitbase<NB>&, const slice_ref<NA CHDL_COMMA TA>&)

CHDL_CONCAT_GEN(template <unsigned NA CHDL_COMMA typename TA>, 
                ch_logic, const_slice_ref<NA CHDL_COMMA TA>,
                ch_logic, slice_ref<NA CHDL_COMMA TA>,
                const ch_logic&, const const_slice_ref<NA CHDL_COMMA TA>&,
                ch_logic&, const slice_ref<NA CHDL_COMMA TA>&)

CHDL_CONCAT_GEN(template <unsigned NB>, 
                ch_bitbase<NB>, ch_logic,
                ch_bitbase<NB>, ch_logic,
                const ch_bitbase<NB>&, const ch_logic&,
                ch_bitbase<NB>&, ch_logic&)

CHDL_CONCAT_GEN(template <unsigned NA>, 
                ch_logic, ch_bitbase<NA>,
                ch_logic, ch_bitbase<NA>,
                const ch_logic&, const ch_bitbase<NA>&,
                ch_logic&, ch_bitbase<NA>&)

// null operators

template <unsigned N>
ch_bitv<N> ch_null() {
  return ch_bitv<N>(createNullNode(N));
}

// slice operators

template <unsigned N, unsigned M>
const_slice_ref<N, ch_bitbase<M>> ch_slice(const ch_bitbase<M>& in, size_t index = 0) {
  return in.template slice<N>(index);
}

template <unsigned N, unsigned M>
slice_ref<N, ch_bitbase<M>> ch_slice(ch_bitbase<M>& in, size_t index = 0) {
  return in.template slice<N>(index);
}

template <unsigned N, unsigned M>
const_slice_ref<N, ch_bitbase<M>> ch_aslice(const ch_bitbase<M>& in, size_t index = 0) {
  return in.template aslice<N>(index);
}

template <unsigned N, unsigned M>
slice_ref<N, ch_bitbase<M>> ch_aslice(ch_bitbase<M>& in, size_t index = 0) {
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
    ch_bitv<(1+D)> operator() (const ch_bitbase<1>& in) {
      return (in[0], ch_bitv<D>(0x0));
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

template <unsigned N>
ch_bitv<N> ch_shuffle(const ch_bitbase<N>& in, const std::initializer_list<int>& indices) {
  TODO();
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
