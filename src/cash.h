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
#include "device.h"
#include "sim.h"
#include "vcd.h"
#include "assertion.h"
#include "struct.h"
#include "union.h"
#include "enum.h"

namespace cash {

//
// utility namespace
//

namespace utility {
  using cash::detail::fstring;
}

//
// core namespace
//
namespace core {

  using namespace cash::utility;

  //
  // basic types
  //

  using cash::detail::ispow2;
  using cash::detail::ilog2;
  using cash::detail::ilog2ceil;

  template<typename T, unsigned N> using ch_vec = cash::detail::ch_vec<T, N>;

  template<unsigned N> using ch_bit = cash::detail::ch_bit<N>;
  using ch_logic = cash::detail::ch_logic;

  template<unsigned N> using ch_bitbase = cash::detail::ch_bitbase<N>;
  using ch_logicbase = cash::detail::ch_logicbase;

  template<typename T> using ch_seq = cash::detail::ch_seq<T>;

  using ch_float = cash::detail::ch_real;

  //
  // pre-defined bit types
  //

  using ch_bit2  = ch_bit<2>;
  using ch_bit4  = ch_bit<4>;
  using ch_bit8  = ch_bit<8>;
  using ch_bit16 = ch_bit<16>;
  using ch_bit32 = ch_bit<32>;
  using ch_bit64 = ch_bit<64>;

  //
  // subscript operators
  //

  using cash::detail::ch_zext;
  using cash::detail::ch_sext;
  using cash::detail::ch_concat;
  using cash::detail::ch_slice;
  using cash::detail::ch_aslice;
  using cash::detail::ch_shuffle;

  //
  // conditional operators
  //

  using cash::detail::ch_select;
  using cash::detail::ch_if;
  using cash::detail::ch_switch;

  //
  // register functions
  //

  using cash::detail::ch_reg;
  using cash::detail::ch_latch;
  using cash::detail::ch_pushclock;
  using cash::detail::ch_popclock;
  using cash::detail::ch_pushreset;
  using cash::detail::ch_popreset;
  using cash::detail::ch_clock;
  using cash::detail::ch_reset;

  //
  // gates functions
  //

  using cash::detail::ch_nand;
  using cash::detail::ch_inv;
  using cash::detail::ch_nor;
  using cash::detail::ch_and;
  using cash::detail::ch_or;
  using cash::detail::ch_xor;
  using cash::detail::ch_xnor;

  //
  // compare functions
  //

  using cash::detail::ch_eq;
  using cash::detail::ch_ne;
  using cash::detail::ch_lt;
  using cash::detail::ch_gt;
  using cash::detail::ch_le;
  using cash::detail::ch_ge;

  //
  // reduce functions
  //

  using cash::detail::ch_andr;
  using cash::detail::ch_orr;
  using cash::detail::ch_xorr;

  //
  // arithmetic functions
  //

  using cash::detail::ch_add;
  using cash::detail::ch_sub;
  using cash::detail::ch_neg;
  using cash::detail::ch_mult;
  using cash::detail::ch_div;
  using cash::detail::ch_sll;
  using cash::detail::ch_slr;
  using cash::detail::ch_rotl;
  using cash::detail::ch_rotr;

  //
  // memory functions
  //

  using cash::detail::ch_rom;
  using cash::detail::ch_mem;

  //
  // other functions
  //

  using cash::detail::ch_mux;
  using cash::detail::ch_demux;
  using cash::detail::ch_log2;
  using cash::detail::ch_lsb;
  using cash::detail::ch_enc;
  using cash::detail::ch_dec;
  using cash::detail::ch_min;
  using cash::detail::ch_max;

  //
  // utility functions
  //

  using cash::detail::ch_tick;
  using cash::detail::ch_assert;
  using cash::detail::ch_tap;
  using cash::detail::ch_print;
}

//
// simulation namespace
//
namespace sim {

  using namespace cash::utility;

  //
  // basic types
  //

  using ch_cycle  = cash::detail::ch_cycle;
  
  template<unsigned N> using ch_bus = cash::detail::ch_bus<N>;
  using ch_signal = cash::detail::ch_signal;

  template<unsigned N> using ch_busbase = cash::detail::ch_busbase<N>;
  using ch_signalbase = cash::detail::ch_signalbase;

  //
  // pre-defined bus types
  //

  using ch_bus2   = ch_bus<2>;
  using ch_bus4   = ch_bus<4>;
  using ch_bus8   = ch_bus<8>;
  using ch_bus16  = ch_bus<16>;
  using ch_bus32  = ch_bus<32>;
  using ch_bus64  = ch_bus<64>;
  
  //
  // api objects
  //

  using ch_device     = cash::detail::ch_device;
  using ch_simulator  = cash::detail::ch_simulator;
  using ch_tracer     = cash::detail::ch_tracer;
  using ch_vcdtracer  = cash::detail::ch_vcdtracer;
}

//
// literals
//

inline namespace core_literals { 
  using namespace cash::detail::core_literals;
}

inline namespace sim_literals {
  using namespace cash::detail::sim_literals;
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

#define __out      CH_OUT
#define __ret      CH_RET
#define __tie      CH_TIE
