#pragma once

#include "bitbase.h"
#include "vec.h"

#define CHDL_CONCAT_GEN(T, TcB, TcA, TB, TA, cB, cA, B, A) \
  T inline const_concat_ref<TcB, TcA> operator,(cB b, cA a) { return const_concat_ref<TcB, TcA>(b, a); } \
  T inline const_concat_ref<TcB, TA> operator,(cB b, A a) { return const_concat_ref<TcB, TA>(b, a); } \
  T inline const_concat_ref<TB, TcA> operator,(B b, cA a) { return const_concat_ref<TB, TcA>(b, a); } \
  T inline concat_ref<TB, TA> operator,(B b, A a) { return concat_ref<TB, TA>(b, a); } \
  T inline const_concat_ref<TcB, TcA> ch_concat(cB b, cA a) { return const_concat_ref<TcB, TcA>(b, a); } \
  T inline const_concat_ref<TcB, TA> ch_concat(cB b, A a) { return const_concat_ref<TcB, TA>(b, a); } \
  T inline const_concat_ref<TB, TcA> ch_concat(B b, cA a) { return const_concat_ref<TB, TcA>(b, a); } \
  T inline concat_ref<TB, TA> ch_concat(B b, A a) { return concat_ref<TB, TA>(b, a); }

namespace chdl_internal {

template <unsigned N> class ch_bus;
using ch_signal = ch_bus<1>;

template <unsigned N> class ch_bitv;
using ch_logic = ch_bitv<1>;

template <unsigned N> 
class ch_bitv : public ch_bitbase<N> {
public:
  using base = ch_bitbase<N>;
  using base::operator=;
  typedef typename base::data_type data_type;
  typedef ch_bitv<N> logic_type;
  typedef ch_bus<N>  bus_type;
      
  ch_bitv() {}
  
  ch_bitv(const ch_bitv& rhs) : m_node(rhs.m_node, N) {}
  
  ch_bitv(const ch_bitbase<N>& rhs) {
    this->operator =(rhs);
  }
  
  ch_bitv(int value) : m_node({(uint32_t)value}, N) {}
  
  ch_bitv(const std::initializer_list<uint32_t>& value) : m_node(value, N) {}
  
  explicit ch_bitv(const lnode& node) : m_node(node, N) {}
  
  base& operator=(const std::initializer_list<uint32_t>& value) {
    m_node.assign(value, N);
    return *this;
  }
  
  operator const lnode&() const { 
    return m_node; 
  }
  
  operator lnode&() { 
    return m_node; 
  }
  
protected:
  
  void read(std::vector< partition<data_type> >& out, size_t offset, size_t length) const override {
    m_node.ensureInitialized(N);
    out.push_back({m_node, offset, length});
  }
  
  void write(size_t dst_offset, const std::vector< partition<data_type> >& src, size_t src_offset, size_t src_length) override {
    for (auto& p : src) {
      if (src_offset < p.length) {
        size_t len = std::min(p.length - src_offset, src_length);
        m_node.assign(dst_offset, p.data, p.offset + src_offset, len, N);         
        src_length -= len;
        if (src_length == 0)
          return;
        dst_offset += len;                
        src_offset = p.length;
      }
      src_offset -= p.length;
    }
  }
  
  lnode m_node;
};

/*template <> 
class ch_bitv<1> : public ch_logicbase {
public:    
  using base = ch_logicbase;
  using base::operator=;
  typedef typename base::data_type data_type;
  typedef ch_bitv<1> logic_type;
  typedef ch_signal  bus_type;
  
  ch_bitv() {}
  
  ch_bitv(const ch_bitv& rhs) : m_node(rhs.m_node, 1) {}
  
  ch_bitv(const ch_logicbase& rhs) {
    this->operator =(rhs);
  }
  
  ch_bitv(int value) : m_node({(uint32_t)value}, 1) {}
  
  ch_bitv(const std::initializer_list<uint32_t>& value) : m_node(value, 1) {}
  
  ch_bitv(bool value) : ch_bitv(value ? 0x1 : 0x0) {}
  
  ch_bitv(char value) : ch_bitv(value != '0') {}
  
  explicit ch_bitv(const lnode& node) : m_node(node, 1) {}
  
  base& operator=(const std::initializer_list<uint32_t>& value) {
    m_node.assign(value, 1);
    return *this;
  }
  
  operator const lnode&() const { 
    return m_node; 
  }
  
  operator lnode&() { 
    return m_node; 
  }
  
protected:
  
  void read(std::vector< partition<data_type> >& out, size_t offset, size_t length) const override {
    assert(length == 1);
    m_node.ensureInitialized(1);    
    out.push_back({m_node, offset, 1});
  }
  
  void write(size_t dst_offset, const std::vector< partition<data_type> >& src, size_t src_offset, size_t src_length) override {
    assert(src_length == 1);
    for (auto& p : src) {
      if (src_offset < p.length) {
        m_node.assign(dst_offset, p.data, p.offset + src_offset, 1, 1);  
        return;
      }
      src_offset -= p.length;
    }
  }
  
  lnode m_node;
};*/

// concatenation operator

CHDL_CONCAT_GEN(template <typename BB CHDL_COMMA typename BA CHDL_COMMA typename AB CHDL_COMMA typename AA>, 
                const_concat_ref<BB CHDL_COMMA BA>, const_concat_ref<AB CHDL_COMMA AA>,
                concat_ref<BB CHDL_COMMA BA>, concat_ref<AB CHDL_COMMA AA>,
                const const_concat_ref<BB CHDL_COMMA BA>&, const const_concat_ref<AB CHDL_COMMA AA>&,
                const concat_ref<BB CHDL_COMMA BA>&, const concat_ref<AB CHDL_COMMA AA>&)

CHDL_CONCAT_GEN(template <typename TB CHDL_COMMA unsigned NB CHDL_COMMA typename TA CHDL_COMMA unsigned NA>, 
                const_slice_ref<TB CHDL_COMMA NB>, const_slice_ref<TA CHDL_COMMA NA>,
                slice_ref<TB CHDL_COMMA NB>, slice_ref<TA CHDL_COMMA NA>,
                const const_slice_ref<TB CHDL_COMMA NB>&, const const_slice_ref<TA CHDL_COMMA NA>&,
                const slice_ref<TB CHDL_COMMA NB>&, const slice_ref<TA CHDL_COMMA NA>&)

CHDL_CONCAT_GEN(template <typename TB CHDL_COMMA typename TA>, 
                const_subscript_ref<TB>, const_subscript_ref<TA>,
                subscript_ref<TB>, subscript_ref<TA>,
                const const_subscript_ref<TB>&, const const_subscript_ref<TA>&,
                const subscript_ref<TB>&, const subscript_ref<TA>&)

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
//--

CHDL_CONCAT_GEN(template <typename BB CHDL_COMMA typename BA CHDL_COMMA typename TA CHDL_COMMA unsigned NA>, 
                const_concat_ref<BB CHDL_COMMA BA>, const_slice_ref<TA CHDL_COMMA NA>,
                concat_ref<BB CHDL_COMMA BA>, slice_ref<TA CHDL_COMMA NA>,
                const const_concat_ref<BB CHDL_COMMA BA>&, const const_slice_ref<TA CHDL_COMMA NA>&,
                const concat_ref<BB CHDL_COMMA BA>&, const slice_ref<TA CHDL_COMMA NA>&)

CHDL_CONCAT_GEN(template <typename BB CHDL_COMMA typename BA CHDL_COMMA typename TA>, 
                const_concat_ref<BB CHDL_COMMA BA>, const_subscript_ref<TA>,
                concat_ref<BB CHDL_COMMA BA>, subscript_ref<TA>,
                const const_concat_ref<BB CHDL_COMMA BA>&, const const_subscript_ref<TA>&,
                const concat_ref<BB CHDL_COMMA BA>&, const subscript_ref<TA>&)

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

//--

CHDL_CONCAT_GEN(template <typename TB CHDL_COMMA unsigned NB CHDL_COMMA typename AB CHDL_COMMA typename AA>, 
                const_slice_ref<TB CHDL_COMMA NB>, const_concat_ref<AB CHDL_COMMA AA>,
                slice_ref<TB CHDL_COMMA NB>, concat_ref<AB CHDL_COMMA AA>,
                const const_slice_ref<TB CHDL_COMMA NB>&, const const_concat_ref<AB CHDL_COMMA AA>&,
                const slice_ref<TB CHDL_COMMA NB>&, const concat_ref<AB CHDL_COMMA AA>&)

CHDL_CONCAT_GEN(template <typename TB CHDL_COMMA unsigned NB CHDL_COMMA typename TA>, 
                const_slice_ref<TB CHDL_COMMA NB>, const_subscript_ref<TA>,
                slice_ref<TB CHDL_COMMA NB>, subscript_ref<TA>,
                const const_slice_ref<TB CHDL_COMMA NB>&, const const_subscript_ref<TA>&,
                const slice_ref<TB CHDL_COMMA NB>&, const subscript_ref<TA>&)

CHDL_CONCAT_GEN(template <typename TB CHDL_COMMA unsigned NB CHDL_COMMA unsigned NA>, 
                const_slice_ref<TB CHDL_COMMA NB>, ch_bitbase<NA>,
                slice_ref<TB CHDL_COMMA NB>, ch_bitbase<NA>,
                const const_slice_ref<TB CHDL_COMMA NB>&, const ch_bitbase<NA>&,
                const slice_ref<TB CHDL_COMMA NB>&, ch_bitbase<NA>&)

CHDL_CONCAT_GEN(template <typename TB CHDL_COMMA unsigned NB>, 
                const_slice_ref<TB CHDL_COMMA NB>, ch_logic,
                slice_ref<TB CHDL_COMMA NB>, ch_logic,
                const const_slice_ref<TB CHDL_COMMA NB>&, const ch_logic&,
                const slice_ref<TB CHDL_COMMA NB>&, ch_logic&)

//--

CHDL_CONCAT_GEN(template <typename TB CHDL_COMMA typename AB CHDL_COMMA typename AA>, 
                const_subscript_ref<TB>, const_concat_ref<AB CHDL_COMMA AA>,
                subscript_ref<TB>, concat_ref<AB CHDL_COMMA AA>,
                const const_subscript_ref<TB>&, const const_concat_ref<AB CHDL_COMMA AA>&,
                const subscript_ref<TB>&, const concat_ref<AB CHDL_COMMA AA>&)

CHDL_CONCAT_GEN(template <typename TB CHDL_COMMA typename TA CHDL_COMMA unsigned NA>, 
                const_subscript_ref<TB>, const_slice_ref<TA CHDL_COMMA NA>,
                subscript_ref<TB>, slice_ref<TA CHDL_COMMA NA>,
                const const_subscript_ref<TB>&, const const_slice_ref<TA CHDL_COMMA NA>&,
                const subscript_ref<TB>&, const slice_ref<TA CHDL_COMMA NA>&)

CHDL_CONCAT_GEN(template <typename TB CHDL_COMMA unsigned NA>, 
                const_subscript_ref<TB>, ch_bitbase<NA>,
                subscript_ref<TB>, ch_bitbase<NA>,
                const const_subscript_ref<TB>&, const ch_bitbase<NA>&,
                const subscript_ref<TB>&, ch_bitbase<NA>&)

CHDL_CONCAT_GEN(template <typename TB>, 
                const_subscript_ref<TB>, ch_logic,
                subscript_ref<TB>, ch_logic,
                const const_subscript_ref<TB>&, const ch_logic&,
                const subscript_ref<TB>&, ch_logic&)

//--

CHDL_CONCAT_GEN(template <unsigned NB CHDL_COMMA typename AB CHDL_COMMA typename AA>, 
                ch_bitbase<NB>, const_concat_ref<AB CHDL_COMMA AA>,
                ch_bitbase<NB>, concat_ref<AB CHDL_COMMA AA>,
                const ch_bitbase<NB>&, const const_concat_ref<AB CHDL_COMMA AA>&,
                ch_bitbase<NB>&, const concat_ref<AB CHDL_COMMA AA>&)

CHDL_CONCAT_GEN(template <unsigned NB CHDL_COMMA typename TA CHDL_COMMA unsigned NA>, 
                ch_bitbase<NB>, const_slice_ref<TA CHDL_COMMA NA>,
                ch_bitbase<NB>, slice_ref<TA CHDL_COMMA NA>,
                const ch_bitbase<NB>&, const const_slice_ref<TA CHDL_COMMA NA>&,
                ch_bitbase<NB>&, const slice_ref<TA CHDL_COMMA NA>&)

CHDL_CONCAT_GEN(template <unsigned NB CHDL_COMMA typename TA>, 
                ch_bitbase<NB>, const_subscript_ref<TA>,
                ch_bitbase<NB>, subscript_ref<TA>,
                const ch_bitbase<NB>&, const const_subscript_ref<TA>&,
                ch_bitbase<NB>&, const subscript_ref<TA>&)

CHDL_CONCAT_GEN(template <unsigned NB>, 
                ch_bitbase<NB>, ch_logic,
                ch_bitbase<NB>, ch_logic,
                const ch_bitbase<NB>&, const ch_logic&,
                ch_bitbase<NB>&, ch_logic&)

//--

CHDL_CONCAT_GEN(template <typename AB CHDL_COMMA typename AA>, 
                ch_logic, const_concat_ref<AB CHDL_COMMA AA>,
                ch_logic, concat_ref<AB CHDL_COMMA AA>,
                const ch_logic&, const const_concat_ref<AB CHDL_COMMA AA>&,
                ch_logic&, const concat_ref<AB CHDL_COMMA AA>&)

CHDL_CONCAT_GEN(template <typename TA CHDL_COMMA unsigned NA>, 
                ch_logic, const_slice_ref<TA CHDL_COMMA NA>,
                ch_logic, slice_ref<TA CHDL_COMMA NA>,
                const ch_logic&, const const_slice_ref<TA CHDL_COMMA NA>&,
                ch_logic&, const slice_ref<TA CHDL_COMMA NA>&)

CHDL_CONCAT_GEN(template <typename TA>, 
                ch_logic, const_subscript_ref<TA>,
                ch_logic, subscript_ref<TA>,
                const ch_logic&, const const_subscript_ref<TA>&,
                ch_logic&, const subscript_ref<TA>&)

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

template <unsigned N>
ch_bitv<N> ch_shuffle(const ch_bitbase<N>& in, const std::initializer_list<int>& indices) {
  TODO();
}

// literal operators

template <unsigned N>
ch_bitv<N> ch_lit(int value) {
  return ch_bitv<N>(value);
}

template <unsigned N>
ch_bitv<N> ch_lit(const std::initializer_list<uint32_t>& value) {
  return ch_bitv<N>(value);
}

}
