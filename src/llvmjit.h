#pragma once

#include <stdio.h>

typedef char jit_sbyte;
typedef unsigned char jit_ubyte;
typedef short jit_short;
typedef unsigned short jit_ushort;
typedef int jit_int;
typedef unsigned int jit_uint;
typedef long jit_nint;
typedef unsigned long jit_nuint;
typedef long jit_long;
typedef unsigned long jit_ulong;
typedef float jit_float32;
typedef double jit_float64;
typedef long double jit_nfloat;
typedef void *jit_ptr;

#define	jit_min_int		(((jit_int)1) << (sizeof(jit_int) * 8 - 1))
#define	jit_max_int		((jit_int)(~jit_min_int))
#define	jit_max_uint	((jit_uint)(~((jit_uint)0)))
#define	jit_min_long	(((jit_long)1) << (sizeof(jit_long) * 8 - 1))
#define	jit_max_long	((jit_long)(~jit_min_long))
#define	jit_max_ulong	((jit_ulong)(~((jit_ulong)0)))

// Opaque structure that represents a type descriptor.
typedef struct _jit_type *jit_type_t;

// Opaque structure that represents a context.
typedef struct _jit_context *jit_context_t;

// Opaque structure that represents a function.
typedef struct _jit_function *jit_function_t;

// Opaque structure that represents a block.
typedef struct _jit_block *jit_block_t;

// Opaque structure that represents an instruction.
typedef struct _jit_insn *jit_insn_t;

// Opaque structure that represents a value.
typedef struct _jit_value *jit_value_t;

// Block label identifier.
typedef jit_nuint jit_label_t;

// Value that represents an undefined label.
#define	jit_label_undefined	((jit_label_t)~((jit_uint)0))

// Value that represents an undefined offset.
#define	JIT_NO_OFFSET		(~((unsigned int)0))

// Function that is used to free user-supplied metadata.
typedef void (*jit_meta_free_func)(void *data);

//
// Type API
//

// ABI types for function signatures.
typedef enum {
  jit_abi_cdecl,			/* Native C calling conventions */
  jit_abi_vararg,			/* Native C with optional variable arguments */
  jit_abi_stdcall,		/* Win32 STDCALL (same as cdecl if not Win32) */
  jit_abi_fastcall		/* Win32 FASTCALL (same as cdecl if not Win32) */
} jit_abi_t;

#define	JIT_TYPE_INVALID	   -1
#define	JIT_TYPE_VOID				  0
#define	JIT_TYPE_INT8 				1
#define	JIT_TYPE_INT16				3
#define	JIT_TYPE_INT32		   	5
#define	JIT_TYPE_INT64			  9
#define	JIT_TYPE_PTR				  17

extern const jit_type_t jit_type_void;
extern const jit_type_t jit_type_int8;
extern const jit_type_t jit_type_int16;
extern const jit_type_t jit_type_int32;
extern const jit_type_t jit_type_int64;
extern const jit_type_t jit_type_ptr;

jit_type_t jit_type_create_signature(jit_abi_t abi, jit_type_t return_type, jit_type_t *params, unsigned int num_params, int incref);
void jit_type_free(jit_type_t type);
int jit_type_get_kind(jit_type_t type);
jit_nuint jit_type_get_size(jit_type_t type);

//
// Contexts API
//

jit_context_t jit_context_create(void);
void jit_context_destroy(jit_context_t context);
void jit_context_build_start(jit_context_t context);
void jit_context_build_end(jit_context_t context);

//
// Function API
//

jit_function_t jit_function_create(jit_context_t context, jit_type_t signature);
int jit_function_compile(jit_function_t func);
void *jit_function_to_closure(jit_function_t func);
jit_block_t jit_function_get_current(jit_function_t func);

//
// Value API
//

jit_value_t jit_value_create(jit_function_t func, jit_type_t type);
jit_type_t jit_value_get_type(jit_value_t value);
jit_value_t jit_value_get_param(jit_function_t func, unsigned int param);

jit_value_t jit_value_create_int_constant(jit_function_t func, jit_type_t type, jit_long const_value);
jit_long jit_value_get_int_constant(jit_value_t value);
int jit_value_is_constant(jit_value_t value);

//
// Instruction API
//

// Structure for iterating over the instructions in a block.
typedef struct {
  jit_block_t	block;
  int posn;
} jit_insn_iter_t;

// Flags for "jit_insn_call" and friends.
#define	JIT_CALL_NOTHROW	(1 << 0)
#define	JIT_CALL_NORETURN	(1 << 1)
#define	JIT_CALL_TAIL			(1 << 2)

jit_value_t jit_insn_add(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_sub(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_mul(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_sdiv(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_udiv(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_srem(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_urem(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_neg(jit_function_t func, jit_value_t value);
jit_value_t jit_insn_and(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_or(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_xor(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_not(jit_function_t func, jit_value_t value);
jit_value_t jit_insn_shl(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_shr(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_ushr(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_eq(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_ne(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_lt(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_le(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_gt(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_ge(jit_function_t func, jit_value_t value1, jit_value_t value2);

jit_value_t jit_insn_to_bool(jit_function_t func, jit_value_t value);
jit_value_t jit_insn_to_not_bool(jit_function_t func, jit_value_t value);

jit_value_t jit_insn_abs(jit_function_t func, jit_value_t value1);
jit_value_t jit_insn_min(jit_function_t func, jit_value_t value1, jit_value_t value2);
jit_value_t jit_insn_max(jit_function_t func, jit_value_t value1, jit_value_t value2);

int jit_insn_store(jit_function_t func, jit_value_t dest, jit_value_t value);
jit_value_t jit_insn_load_relative(jit_function_t func, jit_value_t base_addr, jit_nint offset, jit_type_t type);
int jit_insn_store_relative(jit_function_t func, jit_value_t base_addr, jit_nint offset, jit_value_t value);
jit_value_t jit_insn_add_relative(jit_function_t func, jit_value_t base_addr, jit_nint offset);
jit_value_t jit_insn_load_elem(jit_function_t func, jit_value_t base_addr, jit_value_t index, jit_type_t elem_type);
jit_value_t jit_insn_load_elem_address(jit_function_t func, jit_value_t base_addr, jit_value_t index, jit_type_t elem_type);
int jit_insn_store_elem(jit_function_t func, jit_value_t base_addr, jit_value_t index, jit_value_t value);

jit_value_t jit_insn_address_of(jit_function_t func, jit_value_t value);

void jit_insn_set_marker(jit_function_t func, const char* name);

int jit_insn_branch(jit_function_t func, jit_label_t *label);
int jit_insn_branch_if(jit_function_t func, jit_value_t value, jit_label_t *label);
int jit_insn_branch_if_not(jit_function_t func, jit_value_t value, jit_label_t *label);

int jit_insn_label(jit_function_t func, jit_label_t *label);
int jit_insn_label_tight(jit_function_t func, jit_label_t *label);
int jit_insn_return(jit_function_t func, jit_value_t value);
int jit_insn_move_blocks_to_end(jit_function_t func, jit_label_t from_label, jit_label_t to_label);

int jit_insn_memcpy(jit_function_t func, jit_value_t dest, jit_value_t src, jit_value_t size);
int jit_insn_jump_table(jit_function_t func, jit_value_t value, jit_label_t *labels, unsigned int num_labels);
jit_value_t jit_insn_call_native(jit_function_t func, const char *name, void *native_func, jit_type_t signature, jit_value_t *args, unsigned int num_args, int flags);

//
// Dump API
//

int jit_dump_ast(FILE *stream, jit_function_t func, const char *name);
int jit_dump_asm(FILE *stream, jit_function_t func, const char *name);
