#pragma once

#include "scbit.h"
#include "scint.h"
#include "scuint.h"
#include "literals.h"
#include "bit.h"
#include "int.h"
#include "uint.h"
#include "reg.h"
#include "mem.h"
#include "vec.h"
#include "enum.h"
#include "union.h"
#include "struct.h"
#include "inout.h"
#include "module.h"
#include "select.h"
#include "if.h"
#include "switch.h"
#include "assertion.h"
#include "simulator.h"
#include "tracer.h"
#include "vcdtracer.h"
#include "verilog.h"
#include "firrtl.h"
#include "udf.h"

namespace ch {

//
// utility namespace
//
namespace utility {
  using ch::internal::bitcast;
  using ch::internal::stringf;  
  using ch::internal::ispow2;
  using ch::internal::ilog2;
  using ch::internal::log2ceil;  
}

//
// core namespace
//
namespace core {

  using namespace ch::utility;

  //
  // data types
  //

  template <unsigned N> using ch_bit  = ch::internal::ch_bit<N>;
  template <unsigned N> using ch_int  = ch::internal::ch_int<N>;
  template <unsigned N> using ch_uint = ch::internal::ch_uint<N>;

  template <unsigned N> using ch_scbit = ch::internal::ch_scbit<N>;
  template <unsigned N> using ch_scint  = ch::internal::ch_scint<N>;
  template <unsigned N> using ch_scuint = ch::internal::ch_scuint<N>;

  template <typename T, unsigned N> using ch_vec = ch::internal::ch_vec<T, N>;

  template <typename T> using ch_reg = ch::internal::ch_reg<T>;

  template <typename T, unsigned N> using ch_rom = ch::internal::ch_rom<T, N>;
  template <typename T, unsigned N> using ch_mem = ch::internal::ch_mem<T, N>;

  //
  // utility types
  //

  template <typename... Ts>
  inline constexpr unsigned ch_width_v = ch::internal::width_v<Ts...>;

  using ch_direction = ch::internal::ch_direction;

  template <typename T> using ch_scalar_t = ch::internal::scalar_type_t<T>;
  template <typename T> using ch_logic_t  = ch::internal::logic_type_t<T>;
  template <typename T> using ch_flip_t   = ch::internal::flip_type_t<T>;
  template <typename T> using ch_io_t     = ch::internal::io_type_t<T>;

  template <typename T>
  inline constexpr ch_direction ch_direction_v = ch::internal::direction_v<T>;

  template <typename T> using ch_in = ch::internal::ch_in<T>;
  template <typename T> using ch_out = ch::internal::ch_out<T>;
  template <typename T> using ch_module = ch::internal::ch_module<T>;

  using ch::internal::ch_udf;

  //
  // declared types
  //

  using ch_bool   = ch_bit<1>;

  using ch_bit1   = ch_bit<1>;
  using ch_bit2   = ch_bit<2>;
  using ch_bit4   = ch_bit<4>;
  using ch_bit8   = ch_bit<8>;
  using ch_bit16  = ch_bit<16>;
  using ch_bit32  = ch_bit<32>;
  using ch_bit64  = ch_bit<64>;
  using ch_bit128 = ch_bit<128>;

  using ch_int1   = ch_int<1>;
  using ch_int2   = ch_int<2>;
  using ch_int4   = ch_int<4>;
  using ch_int8   = ch_int<8>;
  using ch_int16  = ch_int<16>;
  using ch_int32  = ch_int<32>;
  using ch_int64  = ch_int<64>;
  using ch_int128 = ch_int<128>;

  using ch_uint1  = ch_uint<1>;
  using ch_uint2  = ch_uint<2>;
  using ch_uint4  = ch_uint<4>;
  using ch_uint8  = ch_uint<8>;
  using ch_uint16 = ch_uint<16>;
  using ch_uint32 = ch_uint<32>;
  using ch_uint64 = ch_uint<64>;
  using ch_uint128= ch_uint<128>;

  //
  // constants
  //

  const ch_scbit<1> ch_false(0);
  const ch_scbit<1> ch_true(1);

  //
  // subscript operators
  //

  using ch::internal::ch_clone;
  using ch::internal::ch_slice;
  using ch::internal::ch_aslice;
  using ch::internal::ch_pad;
  using ch::internal::ch_cat;
  using ch::internal::ch_shuffle;

  //
  // conditional operators
  //

  using ch::internal::ch_sel;
  using ch::internal::ch_case;
  using ch::internal::ch_if;
  using ch::internal::ch_switch;
  using ch::internal::ch_min;
  using ch::internal::ch_max;

  //
  // sequential functions
  //

  using ch::internal::ch_delay;
  using ch::internal::ch_pushcd;
  using ch::internal::ch_popcd;
  using ch::internal::ch_clock;
  using ch::internal::ch_reset;

  //
  // reduce functions
  //

  using ch::internal::ch_andr;
  using ch::internal::ch_orr;
  using ch::internal::ch_xorr;

  //
  // rotate functions
  //

  using ch::internal::ch_rotl;
  using ch::internal::ch_rotr;

  //
  // utility functions
  //

  using ch::internal::ch_bind;
  using ch::internal::ch_assert;
  using ch::internal::ch_tap;
  using ch::internal::ch_print;
  using ch::internal::ch_time;
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
  using ch_device_list = ch::internal::ch_device_list;
  using ch_simulator   = ch::internal::ch_simulator;
  using ch_tracer      = ch::internal::ch_tracer;
  using ch_vcdtracer   = ch::internal::ch_vcdtracer;

  //
  // utility functions
  //

  using ch::internal::ch_verilog;
  using ch::internal::ch_firrtl;
  using ch::internal::ch_stats;
}

//
// user defined functions
//
namespace extension {
  using ch::internal::is_object_type_v;
  using ch::internal::is_bit_convertible_v;
  using ch::internal::is_scbit_convertible_v;

  using ch::internal::bitvector;
  using ch::internal::source_location;
  using ch::internal::logic_traits;
  using ch::internal::scalar_traits;
  using ch::internal::logic_buffer_ptr;
  using ch::internal::scalar_buffer_ptr;
  using ch::internal::make_logic_buffer;
  using ch::internal::make_scalar_buffer;
  using ch::internal::udf_comb;
  using ch::internal::udf_seq;
  using ch::internal::udf_output;
  using ch::internal::udf_inputs;
  using ch::internal::lnode;

  using ch::internal::scalar_op_compare;
  using ch::internal::scalar_op_logical;
  using ch::internal::scalar_op_bitwise;
  using ch::internal::scalar_op_shift;
  using ch::internal::scalar_op_padding;
  using ch::internal::scalar_op_cast;
  using ch::internal::scalar_op_relational;
  using ch::internal::scalar_op_arithmetic;

  using ch::internal::logic_op_compare;
  using ch::internal::logic_op_logical;
  using ch::internal::logic_op_bitwise;
  using ch::internal::logic_op_shift;
  using ch::internal::logic_op_padding;
  using ch::internal::logic_op_relational;
  using ch::internal::logic_op_arithmetic;
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

#define __sloc     CH_SLOC

#define __width_of CH_WIDTH_OF
