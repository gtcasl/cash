#pragma once

#include "jit/jit.h"
#include "jit/jit-dump.h"

#define	JIT_TYPE_INT8		JIT_TYPE_UBYTE
#define	JIT_TYPE_INT16	JIT_TYPE_USHORT
#define	JIT_TYPE_INT32	JIT_TYPE_UINT
#define	JIT_TYPE_INT64  JIT_TYPE_ULONG

#define jit_type_int8  jit_type_ubyte
#define jit_type_int16 jit_type_ushort
#define jit_type_int32 jit_type_uint
#define jit_type_int64 jit_type_ulong
#define jit_type_ptr   jit_type_void_ptr

jit_value_t jit_value_create_int_constant(jit_function_t func, jit_long const_value, jit_type_t type);
jit_long jit_value_get_int_constant(jit_value_t value);

jit_value_t jit_insn_sdiv(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_udiv(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_srem(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_urem(jit_function_t func, jit_value_t value1, jit_value_t value2);

jit_value_t jit_insn_slt(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_ult(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_sle(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_ule(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_sgt(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_ugt(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_sge(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_uge(jit_function_t func, jit_value_t value1, jit_value_t value2);

jit_value_t jit_insn_smin(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_umin(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_smax(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_umax(jit_function_t func, jit_value_t value1, jit_value_t value2);

jit_value_t jit_insn_sext(jit_function_t func, jit_value_t value, jit_type_t type);

jit_value_t jit_insn_select(jit_function_t func, jit_value_t cond, jit_value_t case_true, jit_value_t case_false);
jit_value_t jit_insn_switch(jit_function_t func, jit_value_t key, const jit_value_t* preds, const jit_value_t* values, unsigned int num_cases, jit_value_t def_value);

void jit_insn_set_marker(jit_function_t func, const char* name);

int jit_dump_ast(FILE *stream, jit_function_t func, const char *name);
int jit_dump_asm(FILE *stream, jit_function_t func, const char *name);
