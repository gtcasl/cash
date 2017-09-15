#pragma once

#include "bit.h"
#include "bus.h"
#include "literals.h"
#include "select.h"
#include "if.h"
#include "switch.h"
#include "reg.h"
#include "seq.h"
#include "real.h"
#include "mem.h"
#include "arithm.h"
#include "bus.h"
#include "port.h"
#include "device.h"
#include "simulator.h"
#include "vcdtracer.h"
#include "assertion.h"
#include "struct.h"
#include "union.h"
#include "enum.h"

namespace cash {

//
// utility namespace
//

namespace utility {
  using cash::internal::fstring;
}

//
// core namespace
//
namespace core {

  using namespace cash::utility;

  //
  // basic types
  //

  using cash::internal::ispow2;
  using cash::internal::ilog2;
  using cash::internal::ilog2ceil;

  template <typename T, unsigned N> using ch_vec = cash::internal::ch_vec<T, N>;

  template <unsigned N> using ch_bit = cash::internal::ch_bit<N>;

  template <unsigned N> using ch_bitbase = cash::internal::ch_bitbase<N>;

  template <typename T> using ch_seq = cash::internal::ch_seq<T>;

  using ch_float = cash::internal::ch_real;

  template <typename T> using ch_in = cash::internal::ch_in<T>;
  template <typename T> using ch_out = cash::internal::ch_out<T>;

  //
  // bit types
  //

  using ch_bit1   = ch_bit<1>;
  using ch_bit2   = ch_bit<2>;
  using ch_bit4   = ch_bit<4>;
  using ch_bit8   = ch_bit<8>;
  using ch_bit16  = ch_bit<16>;
  using ch_bit32  = ch_bit<32>;
  using ch_bit64  = ch_bit<64>;
  using ch_bit128 = ch_bit<128>;

  //
  // boolean types
  //

  using cash::internal::ch_true;
  using cash::internal::ch_false;

  //
  // subscript operators
  //

  using cash::internal::ch_zext;
  using cash::internal::ch_sext;
  using cash::internal::ch_cat;
  using cash::internal::ch_slice;
  using cash::internal::ch_aslice;
  using cash::internal::ch_shuffle;

  //
  // conditional operators
  //

  using cash::internal::ch_select;
  using cash::internal::ch_if;
  using cash::internal::ch_switch;

  //
  // register functions
  //

  using cash::internal::ch_reg;
  using cash::internal::ch_latch;
  using cash::internal::ch_pushClock;
  using cash::internal::ch_popClock;
  using cash::internal::ch_pushReset;
  using cash::internal::ch_popReset;
  using cash::internal::ch_getClock;
  using cash::internal::ch_getReset;
  using cash::internal::ch_getTick;

  //
  // gates functions
  //

  using cash::internal::ch_nand;
  using cash::internal::ch_inv;
  using cash::internal::ch_nor;
  using cash::internal::ch_and;
  using cash::internal::ch_or;
  using cash::internal::ch_xor;
  using cash::internal::ch_xnor;

  //
  // compare functions
  //

  using cash::internal::ch_eq;
  using cash::internal::ch_ne;
  using cash::internal::ch_lt;
  using cash::internal::ch_gt;
  using cash::internal::ch_le;
  using cash::internal::ch_ge;

  //
  // reduce functions
  //

  using cash::internal::ch_andr;
  using cash::internal::ch_orr;
  using cash::internal::ch_xorr;

  //
  // arithmetic functions
  //

  using cash::internal::ch_add;
  using cash::internal::ch_sub;
  using cash::internal::ch_neg;
  using cash::internal::ch_mult;
  using cash::internal::ch_div;
  using cash::internal::ch_sll;
  using cash::internal::ch_slr;
  using cash::internal::ch_rotl;
  using cash::internal::ch_rotr;

  //
  // memory functions
  //

  using cash::internal::ch_rom;
  using cash::internal::ch_ram;

  //
  // other functions
  //

  using cash::internal::ch_mux;
  using cash::internal::ch_demux;
  using cash::internal::ch_log2;
  using cash::internal::ch_lsb;
  using cash::internal::ch_enc;
  using cash::internal::ch_dec;
  using cash::internal::ch_min;
  using cash::internal::ch_max;

  //
  // utility functions
  //

  using cash::internal::ch_tie;
  using cash::internal::ch_assert;
  using cash::internal::ch_tap;
  using cash::internal::ch_print;
}

//
// simulation namespace
//
namespace sim {

  using namespace cash::utility;

  //
  // basic types
  //

  using ch_tick  = cash::internal::ch_tick;
  
  template <unsigned N> using ch_bus = cash::internal::ch_bus<N>;

  template <unsigned N> using ch_busbase = cash::internal::ch_busbase<N>;

  //
  // bus types
  //

  using ch_bus1   = ch_bus<1>;
  using ch_bus2   = ch_bus<2>;
  using ch_bus4   = ch_bus<4>;
  using ch_bus8   = ch_bus<8>;
  using ch_bus16  = ch_bus<16>;
  using ch_bus32  = ch_bus<32>;
  using ch_bus64  = ch_bus<64>;
  using ch_bus128 = ch_bus<128>;
  
  //
  // objects
  //

  using ch_device    = cash::internal::ch_device;
  using ch_simulator = cash::internal::ch_simulator;
  using ch_tracer    = cash::internal::ch_tracer;
  using ch_vcdtracer = cash::internal::ch_vcdtracer;

  //
  // functions
  //
  using cash::internal::ch_function;
  using cash::internal::ch_module;

}

//
// literals
//

inline namespace core_literals {
  using namespace cash::internal::core_literals;
}

inline namespace sim_literals {
  using namespace cash::internal::sim_literals;
}

}

//
// utility macros
//

#define __if       CH_IF
#define __elif     CH_ELIF
#define __else     CH_ELSE

#define __switch   CH_SWITCH
#define __case     CH_CASE
#define __default  CH_DEFAULT

#define __tap      CH_TAP
#define __trace    CH_TRACE
#define __assert   CH_ASSERT

#define __struct   CH_STRUCT
#define __union    CH_UNION
#define __enum     CH_ENUM

#define __inout    CH_INOUT
#define __io       CH_IO
#define __module   CH_MODULE

#define __out      CH_OUT
#define __ret      CH_RET
