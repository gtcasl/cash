#pragma once

#include "bitv.h"
#include "reg.h"
#include "mem.h"
#include "arithm.h"
#include "select.h"
#include "bus.h"
#include "device.h"
#include "sim.h"
#include "vcd.h"
#include "assertion.h"
#include "aggregate.h"

namespace chdl {

  //
  // basic types
  //

  using chdl_internal::IS_POW2;
  using chdl_internal::LOG2;
  using chdl_internal::CLOG2;

  using ch_logic = chdl_internal::ch_logic;

  template<unsigned N, typename T>
  using ch_vec = chdl_internal::ch_vec<N, T>;

  template<unsigned N>
  using ch_bitv = chdl_internal::ch_bitv<N>;

  template<unsigned N>
  using ch_uint = chdl_internal::ch_bitv<N>;

  template<unsigned N>
  using ch_bitbase = chdl_internal::ch_bitbase<N>;

  //
  // pre-defined data types
  //

  typedef ch_bitv<2>  ch_bit2;
  typedef ch_bitv<4>  ch_bit4;
  typedef ch_bitv<8>  ch_bit8;
  typedef ch_bitv<16> ch_bit16;
  typedef ch_bitv<32> ch_bit32;
  typedef ch_bitv<64> ch_bit64;

  typedef ch_uint<2>  ch_uint2;
  typedef ch_uint<4>  ch_uint4;
  typedef ch_uint<8>  ch_uint8;
  typedef ch_uint<16> ch_uint16;
  typedef ch_uint<32> ch_uint32;
  typedef ch_uint<64> ch_uint64;

  //
  // subscript operators
  //

  using chdl_internal::ch_zext;
  using chdl_internal::ch_sext;
  using chdl_internal::ch_concat;
  using chdl_internal::ch_slice;
  using chdl_internal::ch_aslice;
  using chdl_internal::ch_shuffle;

  //
  // conditional operators
  //

  using chdl_internal::ch_select;

  //
  // register functions
  //

  using chdl_internal::ch_reg;
  using chdl_internal::ch_latch;
  using chdl_internal::ch_pushclock;
  using chdl_internal::ch_popclock;
  using chdl_internal::ch_pushreset;
  using chdl_internal::ch_popreset;
  using chdl_internal::ch_clock;
  using chdl_internal::ch_reset;

  //
  // gates functions
  //

  using chdl_internal::ch_lit;
  using chdl_internal::ch_nand;
  using chdl_internal::ch_inv;
  using chdl_internal::ch_nor;
  using chdl_internal::ch_and;
  using chdl_internal::ch_or;
  using chdl_internal::ch_xor;
  using chdl_internal::ch_xnor;

  //
  // compare functions
  //

  using chdl_internal::ch_eq;
  using chdl_internal::ch_ne;
  using chdl_internal::ch_lt;
  using chdl_internal::ch_gt;
  using chdl_internal::ch_le;
  using chdl_internal::ch_ge;

  //
  // reduce functions
  //

  using chdl_internal::ch_andr;
  using chdl_internal::ch_orr;
  using chdl_internal::ch_xorr;

  //
  // arithmetic functions
  //

  using chdl_internal::ch_add;
  using chdl_internal::ch_sub;
  using chdl_internal::ch_neg;
  using chdl_internal::ch_mult;
  using chdl_internal::ch_div;
  using chdl_internal::ch_sll;
  using chdl_internal::ch_slr;
  using chdl_internal::ch_rotl;
  using chdl_internal::ch_rotr;

  //
  // memory functions
  //

  using chdl_internal::ch_rom;
  using chdl_internal::ch_mem;

  //
  // other functions
  //

  using chdl_internal::ch_mux;
  using chdl_internal::ch_demux;
  using chdl_internal::ch_log2;
  using chdl_internal::ch_lsb;
  using chdl_internal::ch_enc;
  using chdl_internal::ch_penc;

  //
  // utility functions
  //

  using chdl_internal::ch_assert;
  using chdl_internal::ch_tap;
  using chdl_internal::ch_print;

  //
  // miscellaneous
  //

  using chdl_internal::fstring;

  //
  // simulation namespace
  //
  namespace sim {

    //
    // basic types
    //

    using ch_cycle  = chdl_internal::ch_cycle;
    using ch_signal = chdl_internal::ch_signal;

    template<unsigned N>
    using ch_bus = chdl_internal::ch_bus<N>;

    //
    // api objects
    //

    using ch_device     = chdl_internal::ch_device;
    using ch_simulator  = chdl_internal::ch_simulator;
    using ch_tracer     = chdl_internal::ch_tracer;
    using ch_vcdtracer  = chdl_internal::ch_vcdtracer;
  }
}

//
// utility macros
//

#define __ch_module  CHDL_MODULE
#define __ch_modulex CHDL_MODULEX
#define __ch_tap     CHDL_TAP
#define __ch_trace   CHDL_TRACE
#define __ch_assert  CHDL_ASSERT
#define __ch_struct  CHDL_STRUCT
#define __ch_union   CHDL_UNION
