#pragma once

#include "common.h"

namespace ch {
namespace internal {

struct syminfo_t;
struct sloc_ctx_t;

class sloc_manager {
public:

  ~sloc_manager();

  static sloc_manager& instance();

  sloc_ctx_t* begin_module();

  void end_module(sloc_ctx_t* ctx);

  bool register_source_location(uint32_t stack_level);

  void release_source_location();

  const source_location& get_source_location() const;

private:

  sloc_manager();

  std::unordered_map<std::string, syminfo_t*> symbols_;
  sloc_ctx_t* ctx_;
};

sloc_ctx_t* sloc_begin_module();

void sloc_end_module(sloc_ctx_t* ctx);

source_location get_source_location();

}}
