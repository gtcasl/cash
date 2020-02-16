#pragma once

#include "literals.h"
#include "bool.h"
#include "bit.h"
#include "int.h"
#include "uint.h"
#include "enum.h"
#include "vec.h"
#include "union.h"
#include "struct.h"
#include "inout.h"
#include "cd.h"
#include "reg.h"
#include "mem.h"
#include "select.h"
#include "if.h"
#include "switch.h"
#include "apifunc.h"
#include "module.h"
#include "device.h"
#include "simulator.h"
#include "tracer.h"
#include "codegen.h"
#include "udf.h"
#include "streams.h"
#include "debug.h"
#include "cflags.h"

namespace ch {

//
// utility namespace
//
namespace utility {  
  using ch::internal::ispow2;
  using ch::internal::log2floor;
  using ch::internal::log2ceil;
  using ch::internal::log2up;  
  using ch::internal::ceildiv;
  using ch::internal::roundup;
  using ch::internal::blend;
  using ch::internal::bit_cast;
  using ch::internal::stringf;
  using ch::internal::make_array_n;
  using ch::internal::make_list_n;
  using ch::internal::static_for;
  using ch::internal::idname;
}

//
// core namespace
//
namespace logic {

  using namespace ch::utility;

  using ch::internal::ch_width_v;
  using ch::internal::ch_signed_v;
  using ch::internal::ch_direction_v;

  using ch::internal::ch_system_t;
  using ch::internal::ch_logic_t;

  //
  // data types
  //

  using ch::internal::ch_bit;
  using ch::internal::ch_sbit;

  using ch::internal::ch_int;
  using ch::internal::ch_sint;

  using ch::internal::ch_uint;
  using ch::internal::ch_suint;

  using ch::internal::ch_reg;
  using ch::internal::ch_vec;
  using ch::internal::ch_rom;
  using ch::internal::ch_mem;

  //
  // adapter types
  //

  using ch::internal::ch_system_io;
  using ch::internal::ch_logic_io;
  using ch::internal::ch_flip_io;

  using ch::internal::ch_in;
  using ch::internal::ch_out;
  using ch::internal::ch_direction;

  using ch::internal::ch_module;

  using ch::internal::ch_udf_comb;
  using ch::internal::ch_udf_seq;

  using ch::internal::ch_ostream;

  //
  // declared types
  //

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

  using ch_sbit1   = ch_sbit<1>;
  using ch_sbit2   = ch_sbit<2>;
  using ch_sbit4   = ch_sbit<4>;
  using ch_sbit8   = ch_sbit<8>;
  using ch_sbit16  = ch_sbit<16>;
  using ch_sbit32  = ch_sbit<32>;
  using ch_sbit64  = ch_sbit<64>;
  using ch_sbit128 = ch_sbit<128>;
  using ch_sbit256 = ch_sbit<256>;
  using ch_sbit512 = ch_sbit<512>;

  using ch_sint1   = ch_sint<1>;
  using ch_sint2   = ch_sint<2>;
  using ch_sint4   = ch_sint<4>;
  using ch_sint8   = ch_sint<8>;
  using ch_sint16  = ch_sint<16>;
  using ch_sint32  = ch_sint<32>;
  using ch_sint64  = ch_sint<64>;
  using ch_sint128 = ch_sint<128>;
  using ch_sint256 = ch_sint<256>;
  using ch_sint512 = ch_sint<512>;

  using ch_suint1  = ch_suint<1>;
  using ch_suint2  = ch_suint<2>;
  using ch_suint4  = ch_suint<4>;
  using ch_suint8  = ch_suint<8>;
  using ch_suint16 = ch_suint<16>;
  using ch_suint32 = ch_suint<32>;
  using ch_suint64 = ch_suint<64>;
  using ch_suint128= ch_suint<128>;
  using ch_suint256= ch_suint<256>;
  using ch_suint512= ch_suint<512>;

  using ch::internal::ch_bool;
  using ch::internal::ch_sbool;

  //
  // constants
  //

  const ch_sbool ch_false(0);
  const ch_sbool ch_true(1);

  //
  // globals
  //

  using ch::internal::ch_cout;

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
  // logic functions
  //

  using ch::internal::ch_not;
  using ch::internal::ch_andl;
  using ch::internal::ch_orl;

  //
  // binary functions
  //

  using ch::internal::ch_inv;
  using ch::internal::ch_and;
  using ch::internal::ch_or;
  using ch::internal::ch_xor;

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
  // slicing functions
  //

  using ch::internal::ch_slice;
  using ch::internal::ch_aslice;

  //
  // resize functions
  //

  using ch::internal::ch_resize;
  using ch::internal::ch_pad;

  //
  // concatenation function
  //

  using ch::internal::ch_cat;

  //
  // duplicate function
  //

  using ch::internal::ch_dup;

  //
  // shuffle function
  //

  using ch::internal::ch_shuffle;

  //
  // cast function
  //

  using ch::internal::ch_as;

  //
  // reference functions
  //

  using ch::internal::ch_ref;
  using ch::internal::ch_sliceref;
  using ch::internal::ch_asliceref;
  using ch::internal::ch_tie;

  //
  // clone function
  //

  using ch::internal::ch_clone;

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
  // higher order functions
  //

  using ch::internal::ch_map;
  using ch::internal::ch_fold;
  using ch::internal::ch_zip;
  using ch::internal::ch_scan;

  //
  // sequential functions
  //

  using ch::internal::ch_next;
  using ch::internal::ch_nextEn;
  using ch::internal::ch_delay;
  using ch::internal::ch_clock;
  using ch::internal::ch_reset;
  using ch::internal::ch_pushcd;
  using ch::internal::ch_popcd;
  using ch::internal::ch_cd;

  //
  // debug functions
  //

  using ch::internal::ch_print;
  using ch::internal::ch_println;
  using ch::internal::ch_assert;
  using ch::internal::ch_tap;
  using ch::internal::ch_now;
}

//
// system namespace
//
namespace system {

  using namespace ch::utility;

  //
  // read/write function
  //

  using ch::internal::ch_read;
  using ch::internal::ch_write;

  //
  // basic types
  //

  using ch::internal::ch_tick;

  //
  // objects
  //

  using ch::internal::ch_device;
  using ch::internal::ch_simulator;
  using ch::internal::ch_tracer;
  using ch::internal::ch_flags;

  //
  // diagnosis functions
  //

  using ch::internal::ch_stats;
  using ch::internal::ch_setflags;
  using ch::internal::ch_getflags;

  //
  // codegen functions
  //

  using ch::internal::ch_toVerilog;
  using ch::internal::ch_toFIRRTL;
}

//
// literals
//
inline namespace literals {
  using namespace ch::internal::literals;
}

namespace core {
  using namespace ch::logic;
  using namespace ch::system;
  using namespace ch::literals;
}

//
// user defined functions
//
namespace extension {
  using ch::internal::sdata_type;
  using ch::internal::ch_bitbase;
  using ch::internal::ch_sbitbase;
  using ch::internal::ch_numbase;
  using ch::internal::ch_snumbase;  
  using ch::internal::logic_traits;
  using ch::internal::system_traits;
  using ch::internal::logic_buffer;
  using ch::internal::system_buffer;
  using ch::internal::make_logic_buffer;
  using ch::internal::make_system_buffer;
  using ch::internal::system_accessor;
  using ch::internal::logic_accessor;
  using ch::internal::udf_verilog;
  using ch::internal::udf_vostream;
  using ch::internal::source_info;  
  using ch::internal::is_data_type_v;
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
#define __sio      CH_SCIO
#define __flip     CH_FLIP

#define __requires  CH_REQUIRES

#define __unused   CH_UNUSED
