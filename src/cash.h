#pragma once

#include "scalar.h"
#include "literals.h"
#include "logic.h"
#include "select.h"
#include "if.h"
#include "switch.h"
#include "reg.h"
#include "mem.h"
#include "assertion.h"
#include "vec.h"
#include "enum.h"
#include "union.h"
#include "struct.h"
#include "float32.h"
#include "port.h"
#include "inout.h"
#include "module.h"
#include "simulator.h"
#include "vcdtracer.h"
#include "verilog.h"
#include "firrtl.h"
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

  using ch::internal::source_location;

  template <unsigned N> using ch_bit = ch::internal::ch_bit<N>;
  template <unsigned N> using const_bit = ch::internal::const_bit<N>;

  template <unsigned N> using ch_scalar = ch::internal::ch_scalar<N>;
  template <unsigned N> using const_scalar = ch::internal::const_scalar<N>;

  template <typename T, unsigned N> using ch_vec = ch::internal::ch_vec<T, N>;
  template <typename T, unsigned N> using ch_const_vec = ch::internal::const_vec<T, N>;

  using ch_float32 = ch::internal::ch_float32;

  template <typename T> using ch_reg = ch::internal::ch_reg<T>;

  template <typename... Ts>
  inline constexpr unsigned ch_width_v = ch::internal::width_v<Ts...>;

  using ch_direction = ch::internal::ch_direction;

  template <typename T> using ch_scalar_t = ch::internal::scalar_type_t<T>;
  template <typename T> using ch_logic_t  = ch::internal::logic_type_t<T>;
  template <typename T> using ch_value_t  = ch::internal::value_type_t<T>;
  template <typename T> using ch_const_t  = ch::internal::const_type_t<T>;
  template <typename T> using ch_flip_t   = ch::internal::flip_type_t<T>;
  template <typename T> using ch_io_t     = ch::internal::io_type_t<T>;

  template <typename T>
  inline constexpr ch_direction ch_direction_v = ch::internal::direction_v<T>;

  template <typename T> using ch_in = ch::internal::ch_in<T>;
  template <typename T> using ch_out = ch::internal::ch_out<T>;
  template <typename T> using ch_module = ch::internal::ch_module<T>;

  //
  // type traits
  //

  template <typename T, unsigned N = ch_width_v<T>>
  using ch_is_bit_convertible = ch::internal::is_bit_convertible<T, N>;

  template <typename T, unsigned N = ch_width_v<T>>
  using ch_is_scalar_convertible = ch::internal::is_scalar_convertible<T, N>;

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

  using ch_bool = ch_bit1;
  const const_scalar<1> ch_false(0);
  const const_scalar<1> ch_true(1);

  //
  // subscript operators
  //

  using ch::internal::ch_clone;
  using ch::internal::ch_slice;
  using ch::internal::ch_aslice;
  using ch::internal::ch_zext;
  using ch::internal::ch_sext;
  using ch::internal::ch_cat;
  using ch::internal::ch_shuffle;

  //
  // conditional operators
  //

  using ch::internal::ch_select;
  using ch::internal::ch_case;
  using ch::internal::ch_if;
  using ch::internal::ch_switch;

  //
  // sequential functions
  //

  using ch::internal::ch_regNext;
  using ch::internal::ch_delay;
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

  using ch::internal::ch_min;
  using ch::internal::ch_max;

  //
  // utility functions
  //

  using ch::internal::ch_assert;
  using ch::internal::ch_tap;
  using ch::internal::ch_print;

  //
  // floating point functions
  //

  using ch::internal::ch_fadd;
  using ch::internal::ch_fsub;
  using ch::internal::ch_fmult;
  using ch::internal::ch_fdiv;
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

  template <typename T> using ch_device = ch::internal::ch_device<T>;
  using ch_simulator = ch::internal::ch_simulator;
  using ch_tracer    = ch::internal::ch_tracer;
  using ch_vcdtracer = ch::internal::ch_vcdtracer;

  //
  // functions
  //

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
// macro operators
//

#define __if       CH_IF
#define __elif     CH_ELIF
#define __else     CH_ELSE

#define __switch   CH_SWITCH
#define __case     CH_CASE
#define __default  CH_DEFAULT

#define __tap      CH_TAP
#define __assert   CH_ASSERT

#define __struct   CH_STRUCT
#define __union    CH_UNION
#define __enum     CH_ENUM

#define __in(...)  (ch_in<__VA_ARGS__>)
#define __out(...) (ch_out<__VA_ARGS__>)
#define __inout    CH_INOUT
#define __io       CH_IO
#define __flip     CH_FLIP

#define __require0 CH_REQUIRE_0
#define __require1 CH_REQUIRE_1
#define __require2 CH_REQUIRE_2
#define __require3 CH_REQUIRE_3

#define __source_location CH_SRC_LOCATION
