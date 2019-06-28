#include "libjit.h"
#include <jit/jit-dump.h>
#include "common.h"

static jit_type_t to_native_type(jit_type_t type) {
  auto kind = jit_type_get_kind(type);
  switch (kind) {
  case JIT_TYPE_UBYTE:
  case JIT_TYPE_SBYTE:
  case JIT_TYPE_USHORT:
  case JIT_TYPE_SHORT:
  case JIT_TYPE_UINT:
  case JIT_TYPE_INT:
    return jit_type_int32;
  case JIT_TYPE_ULONG:
  case JIT_TYPE_LONG:
    return jit_type_int64;
  default:
    std::abort();
  }
}

static jit_type_t to_signed_type(jit_type_t type) {
  auto kind = jit_type_get_kind(type);
  switch (kind) {
  case JIT_TYPE_UBYTE:
  case JIT_TYPE_SBYTE:
    return jit_type_sbyte;
  case JIT_TYPE_USHORT:
  case JIT_TYPE_SHORT:
    return jit_type_short;
  case JIT_TYPE_UINT:
  case JIT_TYPE_INT:
    return jit_type_int;
  case JIT_TYPE_ULONG:
  case JIT_TYPE_LONG:
    return jit_type_long;
  default:
    std::abort();
  }
}

static jit_type_t to_unsigned_type(jit_type_t type) {
  auto kind = jit_type_get_kind(type);
  switch (kind) {
  case JIT_TYPE_UBYTE:
  case JIT_TYPE_SBYTE:
    return jit_type_ubyte;
  case JIT_TYPE_USHORT:
  case JIT_TYPE_SHORT:
    return jit_type_ushort;
  case JIT_TYPE_UINT:
  case JIT_TYPE_INT:
    return jit_type_uint;
  case JIT_TYPE_ULONG:
  case JIT_TYPE_LONG:
    return jit_type_ulong;
  default:
    std::abort();
  }
}

static jit_value_t to_signed_value(jit_function_t func, jit_value_t value) {
  auto t = jit_value_get_type(value);
  auto t_kind = jit_type_get_kind(t);
  auto st = to_signed_type(t);
  auto st_kind = jit_type_get_kind(st);
  if (t_kind == st_kind)
    return value;
  return jit_insn_convert(func, value, st, 0);
}

static jit_value_t to_unsigned_value(jit_function_t func, jit_value_t value) {
  auto t = jit_value_get_type(value);
  auto t_kind = jit_type_get_kind(t);
  auto ut = to_unsigned_type(t);
  auto ut_kind = jit_type_get_kind(ut);
  if (t_kind == ut_kind)
    return value;
  return jit_insn_convert(func, value, ut, 0);
}

///////////////////////////////////////////////////////////////////////////////

jit_value_t jit_value_create_int_constant(jit_function_t func,
                                          jit_ulong const_value,
                                          jit_type_t type) {
  auto size = jit_type_get_size(type);
  if (size <= 4) {
    return jit_value_create_nint_constant(func, type, const_value);
  } else {
    return jit_value_create_long_constant(func, type, const_value);
  }
}

jit_ulong jit_value_get_int_constant(jit_value_t value) {
  assert(jit_value_is_constant(value));
  auto type = jit_value_get_type(value);
  auto size = jit_type_get_size(type);
  jit_ulong res;
  if (size <= 4) {
    res = jit_value_get_nint_constant(value);
  } else {
    res = jit_value_get_long_constant(value);
  }
  if (size < 8) {
    auto mask = (1ull << (8 * size)) - 1;
    res &= mask;
  }
  return res;
}

jit_value_t jit_insn_sdiv(jit_function_t func, jit_value_t value1, jit_value_t value2) {
  auto lhs = to_signed_value(func, value1);
  auto rhs = to_signed_value(func, value2);
  return to_unsigned_value(func, jit_insn_div(func, lhs, rhs));
}

jit_value_t jit_insn_udiv(jit_function_t func, jit_value_t value1, jit_value_t value2) {
  return jit_insn_div(func, value1, value2);
}

jit_value_t jit_insn_srem(jit_function_t func, jit_value_t value1, jit_value_t value2) {
  auto lhs = to_signed_value(func, value1);
  auto rhs = to_signed_value(func, value2);
  return to_unsigned_value(func, jit_insn_rem(func, lhs, rhs));
}

jit_value_t jit_insn_urem(jit_function_t func, jit_value_t value1, jit_value_t value2) {
  return jit_insn_rem(func, value1, value2);
}

jit_value_t jit_insn_slt(jit_function_t func, jit_value_t value1, jit_value_t value2) {
  auto lhs = to_signed_value(func, value1);
  auto rhs = to_signed_value(func, value2);
  return to_unsigned_value(func, jit_insn_lt(func, lhs, rhs));
}

jit_value_t jit_insn_ult(jit_function_t func, jit_value_t value1, jit_value_t value2) {
  return jit_insn_lt(func, value1, value2);
}

jit_value_t jit_insn_sle(jit_function_t func, jit_value_t value1, jit_value_t value2) {
  auto lhs = to_signed_value(func, value1);
  auto rhs = to_signed_value(func, value2);
  return to_unsigned_value(func, jit_insn_le(func, lhs, rhs));
}

jit_value_t jit_insn_ule(jit_function_t func, jit_value_t value1, jit_value_t value2) {
  return jit_insn_le(func, value1, value2);
}

jit_value_t jit_insn_sgt(jit_function_t func, jit_value_t value1, jit_value_t value2) {
  auto lhs = to_signed_value(func, value1);
  auto rhs = to_signed_value(func, value2);
  return to_unsigned_value(func, jit_insn_gt(func, lhs, rhs));
}

jit_value_t jit_insn_ugt(jit_function_t func, jit_value_t value1, jit_value_t value2) {
  return jit_insn_gt(func, value1, value2);
}

jit_value_t jit_insn_sge(jit_function_t func, jit_value_t value1, jit_value_t value2) {
  auto lhs = to_signed_value(func, value1);
  auto rhs = to_signed_value(func, value2);
  return to_unsigned_value(func, jit_insn_ge(func, lhs, rhs));
}

jit_value_t jit_insn_uge(jit_function_t func, jit_value_t value1, jit_value_t value2) {
  return jit_insn_ge(func, value1, value2);
}

jit_value_t jit_insn_smin(jit_function_t func, jit_value_t value1, jit_value_t value2) {
  auto lhs = to_signed_value(func, value1);
  auto rhs = to_signed_value(func, value2);
  return to_unsigned_value(func, jit_insn_min(func, lhs, rhs));
}

jit_value_t jit_insn_umin(jit_function_t func, jit_value_t value1, jit_value_t value2) {
  return jit_insn_min(func, value1, value2);
}

jit_value_t jit_insn_smax(jit_function_t func, jit_value_t value1, jit_value_t value2) {
  auto lhs = to_signed_value(func, value1);
  auto rhs = to_signed_value(func, value2);
  return to_unsigned_value(func, jit_insn_max(func, lhs, rhs));
}

jit_value_t jit_insn_umax(jit_function_t func, jit_value_t value1, jit_value_t value2) {
  return jit_insn_max(func, value1, value2);
}

jit_value_t jit_insn_sext(jit_function_t func, jit_value_t value, jit_type_t type) {
  auto vtype = jit_value_get_type(value);
  auto vt_size = jit_type_get_size(vtype);
  auto t_size = jit_type_get_size(type);
  assert(vt_size <= t_size);
  if (vt_size == t_size)
    return value;
  auto stype = to_signed_type(vtype);
  auto svalue = jit_insn_convert(func, value, stype, 0);
  return jit_insn_convert(func, svalue, type, 0);
}

jit_value_t jit_insn_select(jit_function_t func,
                            jit_value_t cond,
                            jit_value_t case_true,
                            jit_value_t case_false) {
  auto type = jit_value_get_type(case_true);
  auto dst = jit_value_create(func, type);
  jit_insn_store(func, dst, case_true);
  jit_label_t l_exit(jit_label_undefined);
  jit_insn_branch_if(func, cond, &l_exit);
  jit_insn_store(func, dst, case_false);
  jit_insn_label(func, &l_exit);
  return dst;
}

jit_value_t jit_insn_switch(jit_function_t func,
                            jit_value_t key,
                            const jit_value_t* preds,
                            const jit_value_t* values,
                            unsigned int num_cases,
                            jit_value_t def_value) {
  assert(num_cases != 0);
  auto j_type = jit_value_get_type(values[0]);
  auto j_ntype = to_native_type(j_type);
  auto j_dst = jit_value_create(func, j_ntype);

  // analyze the select node  
  auto pred_min = std::numeric_limits<uint64_t>::max();
  auto pred_max = std::numeric_limits<uint64_t>::min();
  uint64_t pred_delta = 0;
  uint64_t i_pred_prev = 0;
  bool is_constant = true;
  for (unsigned int i = 0; i < num_cases; ++i) {
    auto pred_value = jit_value_get_int_constant(preds[i]);
    is_constant &= jit_value_is_constant(values[i]);
    pred_delta += (i ? (pred_value - i_pred_prev) : 0);
    pred_min = std::min(pred_value, pred_min);
    pred_max = std::max(pred_value, pred_max);
    i_pred_prev = pred_value;
  }

  auto density = pred_delta ? (float(num_cases) / pred_delta) : 0;
  if (num_cases >= 4 && density > 0.6) {
    //
    // jump table
    //
    jit_label_t l_default(jit_label_undefined);
    jit_label_t l_jump(jit_label_undefined);
    jit_label_t l_exit(jit_label_undefined);
    std::vector<jit_label_t> labels(num_cases, jit_label_undefined);
    std::unordered_map<jit_value_t, uint32_t> unique_values;

    // emit 'case' blocks
    for (unsigned int i = 0; i < num_cases; ++i) {
      auto label = &labels.at(i);
      auto j_src = values[i];
      auto it = unique_values.find(j_src);
      if (it != unique_values.end()) {
        *label = labels.at(it->second);
        continue;
      }
      unique_values[j_src] = i;
      jit_insn_label(func, label);
      jit_insn_store(func, j_dst, j_src);
      jit_insn_branch(func, &l_exit);
    }

    // emit 'default' block
    jit_insn_label(func, &l_default);
    jit_insn_store(func, j_dst, def_value);

    // exit
    jit_insn_label(func, &l_exit);

    // build label table
    jit_insn_label(func, &l_jump);
    auto j_max = jit_value_create_int_constant(func, pred_max, jit_type_int32);
    auto j_pred = jit_insn_ugt(func, key, j_max);
    if (pred_min) {
      auto j_min = jit_value_create_int_constant(func, pred_min, jit_type_int32);
      auto j_tmp = jit_insn_ult(func, key, j_min);
      j_pred = jit_insn_or(func, j_pred, j_tmp);
    }
    jit_insn_branch_if(func, j_pred, &l_default);

    auto j_value = key;
    if (pred_min) {
      auto j_min = jit_value_create_int_constant(func, pred_min, jit_type_int32);
      j_value = jit_insn_sub(func, key, j_min);
    }

    unsigned int k = 0;
    auto distance = (pred_max - pred_min) + 1;
    std::vector<jit_label_t> jump_labels(distance, jit_label_undefined);
    for (uint32_t i = 0; i < distance; ++i) {
      auto p = i + pred_min;
      for (unsigned int j = k; j < num_cases; ++j) {
        auto pred_value = jit_value_get_int_constant(preds[j]);
        if (pred_value == p) {
          jump_labels[i] = labels.at(j);
          ++k;
          break;
        }
      }
      if (jit_label_undefined == jump_labels.at(i)) {
        jump_labels[i] = l_default;
      }
    }

    jit_insn_jump_table(func, j_value, jump_labels.data(), jump_labels.size());
    jit_insn_move_blocks_to_end(func, labels.at(0), l_jump);
  } else {
    std::vector<jit_label_t> labels(num_cases, jit_label_undefined);
    std::unordered_map<jit_value_t, uint32_t> unique_values;
    jit_label_t l_exit(jit_label_undefined);

    // emit jump tests
    for (uint32_t i = 0; i < num_cases; ++i) {
      auto label = &labels.at(i);
      auto j_src = values[i];
      auto it = unique_values.find(j_src);
      if (it != unique_values.end()) {
        label = &labels.at(it->second);
      } else {
        unique_values[j_src] = i;
      }
      auto j_pred = jit_insn_eq(func, key, preds[i]);
      jit_insn_branch_if(func, j_pred, label);
    }

    // emit 'default' block
    jit_insn_store(func, j_dst, def_value);
    jit_insn_branch(func, &l_exit);

    // emit 'case' blocks
    for (unsigned int i = 0; i < num_cases; ++i) {
      auto j_src = values[i];
      auto k = unique_values.at(j_src);
      if (k != i)
        continue;
      jit_insn_label(func, &labels.at(i));
      jit_insn_store(func, j_dst, j_src);
      if (i != num_cases-1) {
        jit_insn_branch(func, &l_exit);
      }
    }

    // exit
    jit_insn_label(func, &l_exit);
  }

  return j_dst;
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
  fputc('\n', stream);

  // dump blocks
  jit_block_t block = nullptr;
  while ((block = jit_block_next(func, block)) != nullptr) {
    auto meta = jit_block_get_meta(block, 0);
    if (meta) {
      if (((char*)meta)[0] != '\0') {
        auto sinfo = (const char*)meta;
        fprintf(stream, "<sref %s/>\n", sinfo);
      } else {
        fprintf(stream, "</sref>\n");
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
      fputc('\t', stream);
      jit_dump_insn(stream, func, insn);
      fputc('\n', stream);
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
