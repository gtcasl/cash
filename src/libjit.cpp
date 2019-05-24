#include "libjit.h"
#include "common.h"

jit_value_t jit_value_create_int_constant(jit_function_t func,
                                      jit_type_t type,
                                      jit_long const_value) {
  auto size = jit_type_get_size(type);
  if (size <= 4) {
    return jit_value_create_nint_constant(func, type, const_value);
  } else {
    return jit_value_create_long_constant(func, type, const_value);
  }
}

jit_long jit_value_get_int_constant(jit_value_t value) {
  auto type = jit_value_get_type(value);
  auto size = jit_type_get_size(type);
  if (size <= 4) {
    return jit_value_get_nint_constant(value);
  } else {
    return jit_value_get_long_constant(value);
  }
}

void jit_insn_set_marker(jit_function_t func, const char* name) {
  jit_insn_new_block(func);
  auto block = jit_function_get_current(func);
  jit_block_set_meta(block, 0, (void*)name, nullptr);
}

int jit_dump_ast(FILE *stream, jit_function_t func, const char *name) {
  fprintf(stream, "function %s(", name);

  // dump signature
  auto signature = jit_function_get_signature(func);
  uint32_t num_params = jit_type_num_params(signature);
  for (uint32_t param = 0; param < num_params; ++param) {
    if (param != 0) {
      fputs(", ", stream);
    }
    auto value = jit_value_get_param(func, param);
    jit_dump_value(stream, func, value, 0);
    fputs(" : ", stream);
    jit_dump_type(stream, jit_type_get_param(signature, param));
  }

  fprintf(stream, ") : ");
  jit_dump_type(stream, jit_type_get_return(signature));
  putc('\n', stream);

  // dump blocks
  jit_block_t block = nullptr;
  while ((block = jit_block_next(func, block)) != nullptr) {
    auto meta = jit_block_get_meta(block, 0);
    if (meta) {
      if (((char*)meta)[0] != '\0') {
        auto sinfo = (const char*)meta;
        fprintf(stream, "# </sref %s\n", sinfo);
        if (strchr(sinfo, '@')) {
          delete [] sinfo; // release allocation
        }
      } else {
        fprintf(stream, "# sref/>\n");
      }
    }

    // dump label if present
    auto label = jit_block_get_label(block);
    if (label != jit_label_undefined) {
      for (;;) {
        fprintf(stream, ".L%ld:", (long) label);
        label = jit_block_get_next_label(block, label);
        if (jit_label_undefined == label) {
          fprintf(stream, "\n");
          break;
        }
        fprintf(stream, " ");
      }
    }

    // dump the instructions
    jit_insn_iter_t iter;
    jit_insn_iter_init(&iter, block);
    jit_insn_t insn = nullptr;
    while ((insn = jit_insn_iter_next(&iter)) != nullptr) {
      putc('\t', stream);
      jit_dump_insn(stream, func, insn);
      putc('\n', stream);
    }
  }
  fprintf(stream, "end\n");
  fflush(stream);

  return 1;
}

int jit_dump_asm(FILE *stream, jit_function_t func, const char *name) {
  jit_dump_function(stream, func, name);
  return 1;
}
