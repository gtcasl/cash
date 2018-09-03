#pragma once

#include <cash.h>
#include <htl/mux.h>
#include <htl/decoupled.h>

namespace ch {
namespace htl {

using namespace ch::logic;

template <typename T, unsigned I, unsigned O>
struct ch_hxbar {
  __io(
    __in(ch_bit<I * O>) sel,
    __in(ch_vec<T, I>)  in,
    __out(ch_vec<T, O>) out
  );

  void describe() {
    for (unsigned i = 0; i < O; ++i) {
      io.out[i] = ch_hmux(ch_aslice<I>(io.sel, i), io.in);
    }
  }
};

template <typename T, unsigned I, unsigned O>
struct ch_xbar {
  __io(
    __in(ch_bit<log2ceil(I) * O>) sel,
    __in(ch_vec<T, I>)  in,
    __out(ch_vec<T, O>) out
  );

  void describe() {
    for (unsigned i = 0; i < O; ++i) {
      io.out[i] = ch_mux(ch_aslice<log2ceil(I)>(io.sel, i), io.in);
    }
  }
};

template <typename T, unsigned I, unsigned O>
struct ch_rv_hxbar {
  using value_type = T;
  using in_io  = ch_vec<ch_enq_io<T>, I>;
  using out_io = ch_deq_io<T>;
  __io(
    __in(ch_bit<log2ceil(I)>) sel,
    (in_io)  in,
    (out_io) out
  );
  void describe() {
    for (unsigned i = 0; i < I; ++i) {
      xbar_.io.in[i].data  = io.in[i].data;
      xbar_.io.in[i].valid = io.in[i].valid;
    }
    io.out.data  = xbar_.io.out[0].data;
    io.out.valid = xbar_.io.out[0].valid;
    xbar_.io.sel = ch_bit<I>(1) << io.sel;
    for (unsigned i = 0; i < I; ++i) {
      io.in[i].ready = io.out.ready && (i == io.sel);
    }
  }
private:
  __struct (xb_data_t, (
    (T) data,
    (ch_bool) valid
  ));
  ch_module<ch_hxbar<xb_data_t, I, 1>> xbar_;
};

template <typename T, unsigned I, unsigned O>
struct ch_rv_xbar {
  using value_type = T;
  using in_io  = ch_vec<ch_enq_io<T>, I>;
  using out_io = ch_deq_io<T>;
  __io(
    __in(ch_bit<log2ceil(I)>) sel,
    (in_io)  in,
    (out_io) out
  );
  void describe() {
    for (unsigned i = 0; i < I; ++i) {
      xbar_.io.in[i].data  = io.in[i].data;
      xbar_.io.in[i].valid = io.in[i].valid;
    }
    io.out.data  = xbar_.io.out[0].data;
    io.out.valid = xbar_.io.out[0].valid;
    xbar_.io.sel = io.sel;
    for (unsigned i = 0; i < I; ++i) {
      io.in[i].ready = io.out.ready && (i == io.sel);
    }
  }
private:
  __struct (xb_data_t, (
    (T) data,
    (ch_bool) valid
  ));
  ch_module<ch_xbar<xb_data_t, I, 1>> xbar_;
};

}
}
