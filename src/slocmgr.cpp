#include "slocmgr.h"
#include "lnodeimpl.h"
#include <unwind.h>
#include <dlfcn.h>
#include <bfd.h>

namespace ch::internal {

struct sloc_ctx_t {
  source_location sloc;
  void* addr;
  bool active;

  sloc_ctx_t() : addr(nullptr), active(false) {}
};

struct syminfo_t {
  bfd*    handle;
  asymbol** syms;

  syminfo_t(bfd* p_handle = nullptr, asymbol** p_syms = nullptr)
    : handle(p_handle)
    , syms(p_syms)
  {}

  ~syminfo_t() {
    if (handle) {
      bfd_close(handle);
    }
    if (syms) {
      free(syms);
    }
  }
};

struct src_finder_t {
  bfd_boolean  found;
  asymbol**    syms;
  bfd_vma      addr;
  const char*  filename;
  const char*  functionname;
  unsigned int line;
  unsigned int discriminator;

  src_finder_t(asymbol** p_syms, bfd_vma p_addr)
    : found(false)
    , syms(p_syms)
    , addr(p_addr)
    , filename(nullptr)
    , functionname(nullptr)
    , line(0)
    , discriminator(0)
  {}
};

struct bt_data_t {
  uint32_t nskip;
  void* addr;

  bt_data_t(uint32_t stack_level)
    : nskip(stack_level)
    , addr(nullptr)
  {}
};

}

using namespace ch::internal;

static void find_address_in_section_cb(bfd *abfd, asection *section, void *data) {
  auto sf = reinterpret_cast<src_finder_t*>(data);
  if (sf->found)
    return;
  if (0 == (bfd_get_section_flags(abfd, section) & SEC_ALLOC))
    return;
  auto vma = bfd_get_section_vma(abfd, section);
  if (sf->addr < vma)
    return;
  auto size = bfd_get_section_size(section);
  if (sf->addr >= vma + size)
    return;
  sf->found = bfd_find_nearest_line_discriminator(
      abfd, section, sf->syms, sf->addr - vma,  &sf->filename, &sf->functionname, &sf->line, &sf->discriminator);
}

static _Unwind_Reason_Code backtrace_cb(_Unwind_Context* ctx, void *data) {
  int ip_before_insn = 0;
  auto bt = reinterpret_cast<bt_data_t*>(data);
  auto pc = _Unwind_GetIPInfo(ctx, &ip_before_insn);
  if (!ip_before_insn)
    --pc;
  if (--bt->nskip == 0) {
    bt->addr = reinterpret_cast<void*>(pc);
    return _URC_END_OF_STACK;
  }
  return _URC_NO_REASON;
}

static bool find_source_location(syminfo_t* sym, void* addr, source_location* sloc) {
  src_finder_t finder(sym->syms, (bfd_vma)addr);
  bfd_map_over_sections(sym->handle, &find_address_in_section_cb, &finder);
  if (!finder.found)
    return false;
  *sloc = source_location((finder.filename ? finder.filename : ""), finder.line);
  return true;
}

static syminfo_t* load_symbols(const char* module) {
  std::unique_ptr<bfd, decltype(&bfd_close)> abfd(bfd_openr(module, nullptr), bfd_close);
  if (!abfd)
    return nullptr;
  if (!bfd_check_format(abfd.get(), bfd_object))
    return nullptr;
  if ((bfd_get_file_flags(abfd.get()) & HAS_SYMS) == 0)
    return nullptr;  
  bool dynamic = false;
  auto storage = bfd_get_symtab_upper_bound(abfd.get());
  if (storage <= 0) {
    storage = bfd_get_dynamic_symtab_upper_bound(abfd.get());
    if (storage <= 0)
      return nullptr;    
    dynamic = true;
  }
  auto syms = (asymbol**)malloc(storage);
  if (nullptr == syms)
    return nullptr;
  auto symcount =  dynamic ? bfd_canonicalize_dynamic_symtab(abfd.get(), syms) :
                             bfd_canonicalize_symtab(abfd.get(), syms);
  if (symcount <= 0) {
    free(syms);
    return nullptr;
  }
  return new syminfo_t(abfd.release(), syms);
}

///////////////////////////////////////////////////////////////////////////////

sloc_manager::sloc_manager()
  : ctx_(nullptr) {
  bfd_init();
}

sloc_manager::~sloc_manager() {
  assert(nullptr == ctx_);
  for (auto entry : symbols_) {
    delete entry.second;
  }
}

sloc_manager& sloc_manager::instance() {
  static sloc_manager inst;
  return inst;
}

sloc_ctx_t* sloc_manager::begin_module() {
  auto old = ctx_;
  ctx_ = new sloc_ctx_t();
  return old;
}

void sloc_manager::end_module(sloc_ctx_t* ctx) {
  delete ctx_;
  ctx_ = ctx;
}

bool sloc_manager::register_source_location(uint32_t stack_level) {
  if (!ctx_ || ctx_->active)
    return false;

  bt_data_t bt_data(stack_level+3);
  _Unwind_Backtrace(&backtrace_cb, &bt_data);
  if (nullptr == bt_data.addr)
    return false;

  if (bt_data.addr == ctx_->addr) {
    ctx_->active = true;
    return true;
  }

  Dl_info dlinfo;
  if (!dladdr(bt_data.addr, &dlinfo))
    return false;
  auto module = dlinfo.dli_fname;

  syminfo_t* sym;
  auto it = symbols_.find(module);
  if (it != symbols_.end()) {
    sym = it->second;
  } else {
    sym = load_symbols(module);
    if (sym == nullptr) {
      return false;
    }
    symbols_.emplace(module, sym);
  }

  if (!find_source_location(sym, bt_data.addr, &ctx_->sloc))
    return false;

  ctx_->addr = bt_data.addr;
  ctx_->active = true;
  return true;
}

void sloc_manager::release_source_location() {
  assert(ctx_ && ctx_->active);
  ctx_->active = false;
}

const source_location& sloc_manager::get_source_location() const {
  assert(ctx_);
  return ctx_->sloc;
}
