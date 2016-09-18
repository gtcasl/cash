#pragma once

#include "bitv.h"

namespace chdl_internal {

template <unsigned N, unsigned A>
class ch_rom {
public:
    ch_rom(const std::string& init_file = "") {
      TODO();
    }
    
    ch_rom(const std::vector<uint32_t>& init_data) {
      TODO();
    }
    
    ch_bitv<N> read(const ch_bitbase<A>& addr) {
      TODO();
    }
};

template <unsigned N, unsigned A>
class ch_mem : public ch_rom<N, A> {
public:
    using base = ch_rom<N, A>;
  
    ch_mem(const std::string& init_file = "") : base(init_file) {}
    
    ch_mem(const std::vector<uint32_t>& init_data) : base(init_data) {
      TODO();
    }
    
    void write(const ch_bitbase<N>& value, const ch_bitbase<A>& addr, const ch_logic& enable) {
      TODO();
    }
};

/*void memory_init(
  std::vector<std::vector<node>>& out,
  const std::vector<node>& d,
  const std::vector<node>& da,
  const std::vector<std::vector<node>>& qa,
  const node& w,
  bool rd_sync,
  const std::string& init_file
);

template <unsigned N, unsigned A, unsigned P>
ch_vec<P, ch_bitv<N>> ch_mem(
    const ch_bitbase<N>& d, 
    const ch_bitbase<A>& da, 
    const ch_bitbase<P * A>& qa,
    const ch_logic& w,
    bool rd_sync = false,
    std::string init_file = "") {
  ch_vec<P, ch_bitv<N>> out;
  
  std::vector<std::vector<node>> qa_vec(P), q_vec;
  std::vector<node> d_vec, da_vec;
  
  for (unsigned p = 0; p < P; ++p) {
    for (unsigned i = 0; i < A; ++i) {
      qa_vec[p].emplace_back(qa[p * A + i]);
    }
  }
    
  for (unsigned i = 0; i < A; ++i) {
    da_vec.emplace_back(da[i]);
  }
  
  for (unsigned i = 0; i < N; ++i) {
    d_vec.emplace_back(d[i]);
  }

  memory_init(q_vec, d_vec, da_vec, qa_vec, w, rd_sync, init_file);
    
  for (unsigned p = 0; p < P; ++p) {
    for (unsigned i = 0; i < N; ++i) {
      out[p][i] = q_vec[p][i];
    }
  }

  return out;
}

template <unsigned N, unsigned A>
ch_bitv<N> ch_mem(
    const ch_bitbase<N>& d, 
    const ch_bitbase<A>& da, 
    const ch_bitbase<A>& qa,
    const ch_logic& w,
    bool rd_sync = false,
    const std::string& init_file = "") {
  return ch_mem<N, A, 1>(d, da, ch_vec<1, ch_bitv<A>>(qa), w, rd_sync, init_file)[0];
}

template <unsigned N, unsigned A>
ch_bitv<N> ch_mem(
    const ch_bitbase<N>& d, 
    const ch_bitbase<A>& a,
    const ch_logic& w, 
    bool rd_sync = false,
    const std::string& init_file = "") {
  return ch_mem<N, A>(d, a, a, w, rd_sync, init_file);
}

template <unsigned N, unsigned A>
ch_bitv<N> ch_rom(
    const ch_bitbase<A>& qa, 
    bool rd_sync,
    const std::string& init_file) {
  return ch_mem<N, A>(ch_lit<N>(0), ch_lit<A>(0), qa, '0', rd_sync, init_file)[0];
}*/

}
