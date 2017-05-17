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
  using cash_internal::fstring;
}

//
// core namespace
//
namespace core {

  using namespace cash::utility;

  //
  // basic types
  //

  using cash_internal::ispow2;
  using cash_internal::ilog2;
  using cash_internal::ilog2ceil;

  template<typename T, unsigned N> using ch_vec = cash_internal::ch_vec<T, N>;

  template<unsigned N> using ch_bit = cash_internal::ch_bit<N>;
  using ch_logic = cash_internal::ch_logic;

  template<unsigned N> using ch_bitbase = cash_internal::ch_bitbase<N>;
  using ch_logicbase = cash_internal::ch_logicbase;

  template<typename T> using ch_seq = cash_internal::ch_seq<T>;

  using ch_float = cash_internal::ch_real;

  //
  // pre-defined bitv types
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

  using cash_internal::ch_zext;
  using cash_internal::ch_sext;
  using cash_internal::ch_concat;
  using cash_internal::ch_slice;
  using cash_internal::ch_aslice;
  using cash_internal::ch_shuffle;

  //
  // conditional operators
  //

  using cash_internal::ch_select;
  using cash_internal::ch_if;
  using cash_internal::ch_switch;

  //
  // register functions
  //

  using cash_internal::ch_reg;
  using cash_internal::ch_latch;
  using cash_internal::ch_pushclock;
  using cash_internal::ch_popclock;
  using cash_internal::ch_pushreset;
  using cash_internal::ch_popreset;
  using cash_internal::ch_clock;
  using cash_internal::ch_reset;

  //
  // gates functions
  //

  using cash_internal::ch_nand;
  using cash_internal::ch_inv;
  using cash_internal::ch_nor;
  using cash_internal::ch_and;
  using cash_internal::ch_or;
  using cash_internal::ch_xor;
  using cash_internal::ch_xnor;

  //
  // compare functions
  //

  using cash_internal::ch_eq;
  using cash_internal::ch_ne;
  using cash_internal::ch_lt;
  using cash_internal::ch_gt;
  using cash_internal::ch_le;
  using cash_internal::ch_ge;

  //
  // reduce functions
  //

  using cash_internal::ch_andr;
  using cash_internal::ch_orr;
  using cash_internal::ch_xorr;

  //
  // arithmetic functions
  //

  using cash_internal::ch_add;
  using cash_internal::ch_sub;
  using cash_internal::ch_neg;
  using cash_internal::ch_mult;
  using cash_internal::ch_div;
  using cash_internal::ch_sll;
  using cash_internal::ch_slr;
  using cash_internal::ch_rotl;
  using cash_internal::ch_rotr;

  //
  // memory functions
  //

  using cash_internal::ch_rom;
  using cash_internal::ch_mem;

  //
  // other functions
  //

  using cash_internal::ch_mux;
  using cash_internal::ch_demux;
  using cash_internal::ch_log2;
  using cash_internal::ch_lsb;
  using cash_internal::ch_enc;
  using cash_internal::ch_dec;
  using cash_internal::ch_min;
  using cash_internal::ch_max;

  //
  // utility functions
  //

  using cash_internal::ch_tick;
  using cash_internal::ch_assert;
  using cash_internal::ch_tap;
  using cash_internal::ch_print;
}

//
// simulation namespace
//
namespace sim {

  using namespace cash::utility;

  //
  // basic types
  //

  using ch_cycle  = cash_internal::ch_cycle;
  
  template<unsigned N> using ch_bus = cash_internal::ch_bus<N>;
  using ch_signal = cash_internal::ch_signal;

  template<unsigned N> using ch_busbase = cash_internal::ch_busbase<N>;
  using ch_signalbase = cash_internal::ch_signalbase;

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
  // literals
  //
  
  
  //
  // api objects
  //

  using ch_device     = cash_internal::ch_device;
  using ch_simulator  = cash_internal::ch_simulator;
  using ch_tracer     = cash_internal::ch_tracer;
  using ch_vcdtracer  = cash_internal::ch_vcdtracer;
}

//
// literals
//

inline namespace core_literals { 
  using namespace cash_internal::core_literals;
}

inline namespace sim_literals {
  using namespace cash_internal::sim_literals;
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
