#pragma once

#include "common.h"
#include "bitvector.h"
#include "traits.h"
#include "lnode.h"
#include "scalar.h"
#include "scbit.h"
#include "scint.h"
#include "scuint.h"
#include "literals.h"
#include "logic.h"
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
  using ch::internal::make_array_n;
  using ch::internal::make_list_n;
}

//
// core namespace
//
namespace core {

  using namespace ch::utility;

  //
  // data types
  //

  using ch::internal::ch_bit;
  using ch::internal::ch_int;
  using ch::internal::ch_uint;

  using ch::internal::ch_scbit;
  using ch::internal::ch_scint;
  using ch::internal::ch_scuint;

  using ch::internal::ch_reg;
  using ch::internal::ch_vec;
  using ch::internal::ch_rom;
  using ch::internal::ch_mem;

  //
  // utility types
  //

  using ch::internal::ch_width_v;
  using ch::internal::ch_signed_v;
  using ch::internal::ch_direction_v;

  using ch::internal::ch_scalar_t;
  using ch::internal::ch_logic_t;

  using ch::internal::ch_scalar_io;
  using ch::internal::ch_logic_io;
  using ch::internal::ch_flip_io;

  using ch::internal::ch_in;
  using ch::internal::ch_out;
  using ch::internal::ch_direction;

  using ch::internal::ch_module;

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
  // equality functions
  //

  using ch::internal::ch_eq;
  using ch::internal::ch_ne;

  //
  // relational functions
  //

  using ch::internal::ch_lt;
  using ch::internal::ch_le;
  using ch::internal::ch_gt;
  using ch::internal::ch_ge;

  //
  // binary functions
  //

  using ch::internal::ch_inv;
  using ch::internal::ch_and;
  using ch::internal::ch_or;

  //
  // shift functions
  //

  using ch::internal::ch_shl;
  using ch::internal::ch_shr;

  //
  // arithmetic functions
  //

  using ch::internal::ch_neg;
  using ch::internal::ch_add;
  using ch::internal::ch_sub;
  using ch::internal::ch_mul;
  using ch::internal::ch_div;
  using ch::internal::ch_mod;

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

  using ch::internal::ch_tick;
  
  //
  // objects
  //

  using ch::internal::ch_device;
  using ch::internal::ch_device_list;
  using ch::internal::ch_simulator;
  using ch::internal::ch_tracer;

  using ch::internal::bitvector;

  //
  // utility functions
  //

  using ch::internal::ch_toVerilog;
  using ch::internal::ch_toFirrtl;
  using ch::internal::ch_stats;
}

//
// user defined functions
//
namespace extension {
  using ch::internal::is_object_type_v;
  using ch::internal::is_bit_convertible_v;
  using ch::internal::is_scbit_convertible_v;
  using ch::internal::is_bitvector_extended_type_v;

  using ch::internal::source_location;
  using ch::internal::logic_traits;
  using ch::internal::scalar_traits;
  using ch::internal::logic_buffer;
  using ch::internal::scalar_buffer_ptr;  
  using ch::internal::logic_buffer;
  using ch::internal::make_scalar_buffer;
  using ch::internal::scalar_accessor;
  using ch::internal::logic_accessor;
  using ch::internal::udf_comb;
  using ch::internal::udf_seq;
  using ch::internal::udf_output;
  using ch::internal::udf_inputs;
  using ch::internal::lnode;

  using ch::internal::scalar_op_equality;
  using ch::internal::scalar_op_logical;
  using ch::internal::scalar_op_bitwise;
  using ch::internal::scalar_op_shift;
  using ch::internal::scalar_op_padding;
  using ch::internal::scalar_op_cast;
  using ch::internal::scalar_op_relational;
  using ch::internal::scalar_op_arithmetic;

  using ch::internal::logic_op_equality;
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

#define __unused   CH_UNUSED
#define __count_of CH_COUNTOF
#define __width_of CH_WIDTH_OF
