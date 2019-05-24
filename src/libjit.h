#pragma once

#include "jit/jit.h"
#include "jit/jit-dump.h"

#define	JIT_TYPE_INT8		JIT_TYPE_SBYTE
#define	JIT_TYPE_INT16	JIT_TYPE_SHORT
#define	JIT_TYPE_INT32	JIT_TYPE_INT
#define	JIT_TYPE_INT64  JIT_TYPE_LONG

#define jit_type_int8  jit_type_sbyte
#define jit_type_int16 jit_type_short
#define jit_type_int32 jit_type_int
#define jit_type_int64 jit_type_long
#define jit_type_ptr   jit_type_void_ptr

jit_value_t jit_value_create_int_constant(jit_function_t func, jit_type_t type, jit_long const_value);

jit_long jit_value_get_int_constant(jit_value_t value);

void jit_insn_set_marker(jit_function_t func, const char* name);

int jit_dump_ast(FILE *stream, jit_function_t func, const char *name);

int jit_dump_asm(FILE *stream, jit_function_t func, const char *name);
