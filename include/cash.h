#pragma once

#include "literals.h"
#include "scbit.h"
#include "scint.h"
#include "scuint.h"
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
#include "codegen.h"
#include "udf.h"

namespace ch {

//
// utility namespace
//
namespace utility {  
  using ch::internal::ispow2;
  using ch::internal::log2floor;
  using ch::internal::log2ceil;
  using ch::internal::log2up;
  using ch::internal::blend;
  using ch::internal::ceildiv;
  using ch::internal::bit_cast;
  using ch::internal::stringf;
  using ch::internal::make_array_n;
  using ch::internal::make_list_n;
  using ch::internal::static_for;
}

//
// core namespace
//
namespace logic {

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

  using ch::internal::ch_system_t;
  using ch::internal::ch_logic_t;

  using ch::internal::ch_system_io;
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
  using ch_bit256 = ch_bit<256>;
  using ch_bit512 = ch_bit<512>;

  using ch_int1   = ch_int<1>;
  using ch_int2   = ch_int<2>;
  using ch_int4   = ch_int<4>;
  using ch_int8   = ch_int<8>;
  using ch_int16  = ch_int<16>;
  using ch_int32  = ch_int<32>;
  using ch_int64  = ch_int<64>;
  using ch_int128 = ch_int<128>;
  using ch_int256 = ch_int<256>;
  using ch_int512 = ch_int<512>;

  using ch_uint1  = ch_uint<1>;
  using ch_uint2  = ch_uint<2>;
  using ch_uint4  = ch_uint<4>;
  using ch_uint8  = ch_uint<8>;
  using ch_uint16 = ch_uint<16>;
  using ch_uint32 = ch_uint<32>;
  using ch_uint64 = ch_uint<64>;
  using ch_uint128= ch_uint<128>;
  using ch_uint256= ch_uint<256>;
  using ch_uint512= ch_uint<512>;

  using ch_scbool   = ch_scbit<1>;

  using ch_scbit1   = ch_scbit<1>;
  using ch_scbit2   = ch_scbit<2>;
  using ch_scbit4   = ch_scbit<4>;
  using ch_scbit8   = ch_scbit<8>;
  using ch_scbit16  = ch_scbit<16>;
  using ch_scbit32  = ch_scbit<32>;
  using ch_scbit64  = ch_scbit<64>;
  using ch_scbit128 = ch_scbit<128>;
  using ch_scbit256 = ch_scbit<256>;
  using ch_scbit512 = ch_scbit<512>;

  using ch_scint1   = ch_scint<1>;
  using ch_scint2   = ch_scint<2>;
  using ch_scint4   = ch_scint<4>;
  using ch_scint8   = ch_scint<8>;
  using ch_scint16  = ch_scint<16>;
  using ch_scint32  = ch_scint<32>;
  using ch_scint64  = ch_scint<64>;
  using ch_scint128 = ch_scint<128>;
  using ch_scint256 = ch_scint<256>;
  using ch_scint512 = ch_scint<512>;

  using ch_scuint1  = ch_scuint<1>;
  using ch_scuint2  = ch_scuint<2>;
  using ch_scuint4  = ch_scuint<4>;
  using ch_scuint8  = ch_scuint<8>;
  using ch_scuint16 = ch_scuint<16>;
  using ch_scuint32 = ch_scuint<32>;
  using ch_scuint64 = ch_scuint<64>;
  using ch_scuint128= ch_scuint<128>;
  using ch_scuint256= ch_scuint<256>;
  using ch_scuint512= ch_scuint<512>;

  //
  // constants
  //

  const ch_scbit<1> ch_false(0);
  const ch_scbit<1> ch_true(1);

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
  using ch::internal::ch_abs;

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
  // resize functions
  //

  using ch::internal::ch_slice;
  using ch::internal::ch_aslice;
  using ch::internal::ch_pad;
  using ch::internal::ch_resize;
  using ch::internal::ch_cat;
  using ch::internal::ch_dup;
  using ch::internal::ch_shuffle;

  //
  // conditional functions
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

  using ch::internal::ch_next;
  using ch::internal::ch_nextEn;
  using ch::internal::ch_delay;
  using ch::internal::ch_pipe;
  using ch::internal::ch_clock;
  using ch::internal::ch_reset;
  using ch::internal::ch_pushcd;
  using ch::internal::ch_popcd;
  using ch::internal::ch_cd;

  //
  // utility functions
  //

  using ch::internal::ch_ref;
  using ch::internal::ch_sliceref;
  using ch::internal::ch_asliceref;
  using ch::internal::ch_clone;
  using ch::internal::ch_bind;
  using ch::internal::ch_print;
  using ch::internal::ch_now;
  using ch::internal::ch_assert;
  using ch::internal::ch_tap;  
}

//
// system namespace
//
namespace system {

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

  using ch::internal::sdata_type;

  //
  // diagnosis functions
  //

  using ch::internal::ch_stats;

  //
  // codegen functions
  //

  using ch::internal::ch_toVerilog;
  using ch::internal::ch_toFIRRTL;
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
  using ch::internal::system_traits;
  using ch::internal::logic_buffer;
  using ch::internal::system_buffer_ptr;
  using ch::internal::logic_buffer;
  using ch::internal::make_system_buffer;
  using ch::internal::system_accessor;
  using ch::internal::logic_accessor;
  using ch::internal::udf_comb;
  using ch::internal::udf_seq;
  using ch::internal::udf_output;
  using ch::internal::udf_inputs;
  using ch::internal::lnode;

  using ch::internal::system_op_equality;
  using ch::internal::system_op_logical;
  using ch::internal::system_op_bitwise;
  using ch::internal::system_op_shift;
  using ch::internal::system_op_cast;
  using ch::internal::system_op_relational;
  using ch::internal::system_op_arithmetic;

  using ch::internal::logic_op_equality;
  using ch::internal::logic_op_logical;
  using ch::internal::logic_op_bitwise;
  using ch::internal::logic_op_shift;
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
