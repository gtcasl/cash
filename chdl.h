#pragma once

#include "bit.h"
#include "bus.h"
#include "literals.h"
#include "select.h"
#include "if.h"
#include "switch.h"
#include "reg.h"
#include "seq.h"
#include "float.h"
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

namespace chdl {

//
// utility namespace
//

namespace utility {
  using chdl_internal::fstring;
}

//
// core namespace
//
namespace core {

  using namespace chdl::utility;

  //
  // basic types
  //

  using chdl_internal::IS_POW2;
  using chdl_internal::LOG2;
  using chdl_internal::CLOG2;

  template<typename T, unsigned N> using ch_vec = chdl_internal::ch_vec<T, N>;

  template<unsigned N> using ch_bit = chdl_internal::ch_bit<N>;
  using ch_logic = chdl_internal::ch_logic;

  template<unsigned N> using ch_bitbase = chdl_internal::ch_bitbase<N>;
  using ch_logicbase = chdl_internal::ch_logicbase;

  template<typename T> using ch_seq = chdl_internal::ch_seq<T>;

  using ch_float = chdl_internal::ch_float;

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
  using chdl_internal::ch_if;
  using chdl_internal::ch_switch;

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
  using chdl_internal::ch_dec;
  using chdl_internal::ch_min;
  using chdl_internal::ch_max;

  //
  // utility functions
  //

  using chdl_internal::ch_tick;
  using chdl_internal::ch_assert;
  using chdl_internal::ch_tap;
  using chdl_internal::ch_print;  
}

//
// simulation namespace
//
namespace sim {

  using namespace chdl::utility;

  //
  // basic types
  //

  using ch_cycle  = chdl_internal::ch_cycle; 
  
  template<unsigned N> using ch_bus = chdl_internal::ch_bus<N>;
  using ch_signal = chdl_internal::ch_signal;

  template<unsigned N> using ch_busbase = chdl_internal::ch_busbase<N>;
  using ch_signalbase = chdl_internal::ch_signalbase;

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

  using ch_device     = chdl_internal::ch_device;
  using ch_simulator  = chdl_internal::ch_simulator;
  using ch_tracer     = chdl_internal::ch_tracer;
  using ch_vcdtracer  = chdl_internal::ch_vcdtracer;
}

//
// literals
//

inline namespace core_literals { 
  using namespace chdl_internal::core_literals;
}

inline namespace sim_literals {
  using namespace chdl_internal::sim_literals;
}

}

//
// utility macros
//

#define __if          CHDL_IF
#define __elif        CHDL_ELIF
#define __else        CHDL_ELSE

#define __switch      CHDL_SWITCH
#define __case        CHDL_CASE
#define __default     CHDL_DEFAULT

#define __ch_tap      CHDL_TAP
#define __ch_trace    CHDL_TRACE
#define __ch_assert   CHDL_ASSERT

#define __ch_struct   CHDL_STRUCT
#define __ch_union    CHDL_UNION
#define __ch_enum     CHDL_ENUM

#define __ch_out      CHDL_OUT
#define __ch_ret      CHDL_RET
#define __ch_tie      CHDL_TIE
