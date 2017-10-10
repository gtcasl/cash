#pragma once

#include "bit.h"
#include "literals.h"
#include "select.h"
#include "if.h"
#include "switch.h"
#include "reg.h"
#include "mem.h"
#include "arithm.h"
#include "assertion.h"
#include "vec.h"
#include "enum.h"
#include "struct.h"
#include "union.h"
#include "real.h"
#include "seq.h"
#include "port.h"
#include "module.h"
#include "simulator.h"
#include "vcdtracer.h"
#include "verilog.h"
#include "misc.h"

namespace ch {

//
// utility namespace
//

namespace utility {
  using ch::internal::fstring;
}

//
// core namespace
//
namespace core {

  using namespace ch::utility;

  //
  // basic types
  //

  using ch::internal::ispow2;
  using ch::internal::ilog2;
  using ch::internal::log2ceil;

  template <typename T, unsigned N> using ch_vec = ch::internal::ch_vec<T, N>;

  template <unsigned N> using ch_bit = ch::internal::ch_bit<N>;

  template <unsigned N> using ch_bitbase = ch::internal::ch_bitbase<N>;

  template <typename T> using ch_seq = ch::internal::ch_seq<T>;

  template <typename T> using ch_flip_t = typename T::flip_type;

  using ch_float = ch::internal::ch_real;

  template <typename T> using ch_in = ch::internal::ch_in<T>;
  template <typename T> using ch_out = ch::internal::ch_out<T>;
  template <typename T> using ch_module = ch::internal::ch_module<T>;

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
  // constants
  //

  //const ch_constant<ch_bit1> ch_false(0);
  //const ch_constant<ch_bit1> ch_true(1);

  //
  // subscript operators
  //

  using ch::internal::ch_zext;
  using ch::internal::ch_sext;
  using ch::internal::ch_cat;
  using ch::internal::ch_slice;
  using ch::internal::ch_aslice;
  using ch::internal::ch_shuffle;

  //
  // conditional operators
  //

  using ch::internal::ch_select;
  using ch::internal::ch_case;
  using ch::internal::ch_if;
  using ch::internal::ch_switch;

  //
  // register functions
  //

  using ch::internal::ch_reg;
  using ch::internal::ch_latch;
  using ch::internal::ch_pushClock;
  using ch::internal::ch_popClock;
  using ch::internal::ch_pushReset;
  using ch::internal::ch_popReset;
  using ch::internal::ch_getClock;
  using ch::internal::ch_getReset;
  using ch::internal::ch_getTick;

  //
  // gates functions
  //

  using ch::internal::ch_nand;
  using ch::internal::ch_inv;
  using ch::internal::ch_nor;
  using ch::internal::ch_and;
  using ch::internal::ch_or;
  using ch::internal::ch_xor;
  using ch::internal::ch_xnor;

  //
  // compare functions
  //

  using ch::internal::ch_eq;
  using ch::internal::ch_ne;
  using ch::internal::ch_lt;
  using ch::internal::ch_gt;
  using ch::internal::ch_le;
  using ch::internal::ch_ge;

  //
  // reduce functions
  //

  using ch::internal::ch_andr;
  using ch::internal::ch_orr;
  using ch::internal::ch_xorr;

  //
  // arithmetic functions
  //

  using ch::internal::ch_add;
  using ch::internal::ch_sub;
  using ch::internal::ch_neg;
  using ch::internal::ch_mult;
  using ch::internal::ch_div;
  using ch::internal::ch_sll;
  using ch::internal::ch_srl;
  using ch::internal::ch_sra;
  using ch::internal::ch_rotl;
  using ch::internal::ch_rotr;

  //
  // memory functions
  //

  using ch::internal::ch_rom;
  using ch::internal::ch_ram;

  //
  // other functions
  //

  using ch::internal::ch_mux;
  using ch::internal::ch_min;
  using ch::internal::ch_max;

  //
  // utility functions
  //

  using ch::internal::ch_assert;
  using ch::internal::ch_tap;
  using ch::internal::ch_print;
}

//
// simulation namespace
//
namespace sim {

  using namespace ch::utility;

  //
  // basic types
  //

  using ch_tick  = ch::internal::ch_tick;
  
  //
  // objects
  //

  using ch_simulator = ch::internal::ch_simulator;
  using ch_tracer    = ch::internal::ch_tracer;
  using ch_vcdtracer = ch::internal::ch_vcdtracer;

  //
  // functions
  //

  using ch::internal::ch_peek;
  using ch::internal::ch_poke;
  using ch::internal::ch_toVerilog;
  using ch::internal::ch_dumpStats;
}

//
// literals
//

inline namespace literals {
  using namespace ch::internal::literals;
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

#define __tie      CH_TIE
#define __flip     CH_FLIP
