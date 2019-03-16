#pragma once

#include "common.h"
#include "bfd.h"
#include <execinfo.h>

namespace ch {
namespace internal {

class src_loc_manager {
public:

  src_loc_manager() : active_(false), addr_(nullptr) {
    bfd_init();
  }

  ~src_loc_manager() {
    for (auto entry : symbols_) {
      delete entry.second;
    }
  }

  bool register_source_location(uint32_t level) {
    if (active_)
      return false;
    std::string module;
    void* addr;
    if (!get_callstack_addr(level+1, addr, module))
      return false;
    if (addr == addr_) {
      active_ = true;
      return true;
    }
    addr_ = nullptr;
    syminfo_t* sym;
    auto it = symbols_.find(module);
    if (it != symbols_.end()) {
      sym = it->second;
    } else {
      sym = load_symbols(module);
      if (sym == nullptr)
        return false;
      symbols_.emplace(module, sym);
    }
    if (!get_source_location(sym, addr, sloc_))
      return false;
    addr_ = addr;
    active_ = true;
    return true;
  }

  void release_source_location() {
    assert(active_);
    active_ = false;
  }

  const source_location& sloc() const {
    assert(active_);
    return sloc_;
  }

private:

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

    void lookup(bfd *abfd, asection *section) {
      if (found)
        return;
      if ((bfd_get_section_flags(abfd, section) & SEC_ALLOC) == 0)
        return;
      auto vma = bfd_get_section_vma(abfd, section);
      if (addr < vma)
        return;
      auto size = bfd_get_section_size(section);
      if (addr >= vma + size)
        return;
      found = bfd_find_nearest_line_discriminator(
            abfd, section, syms, addr - vma,  &filename, &functionname, &line, &discriminator);
    }
  };

  syminfo_t* load_symbols(const std::string module) {
    std::unique_ptr<bfd, decltype(&bfd_close)> abfd(bfd_openr(module.c_str(), nullptr), bfd_close);
    if (!abfd)
      return nullptr;
    if (!bfd_check_format(abfd.get(), bfd_object))
      return nullptr;
    if ((bfd_get_file_flags(abfd.get()) & HAS_SYMS) == 0)
      return nullptr;
    asymbol** syms = nullptr;
    ssize_t symcount = 0;
    auto storage = bfd_get_symtab_upper_bound(abfd.get());
    if (storage > 0) {
      syms = (asymbol**)malloc(storage);
      if (syms) {
        symcount = bfd_canonicalize_symtab(abfd.get(), syms);
      }
    }
    if (symcount <= 0) {
      auto storage = bfd_get_dynamic_symtab_upper_bound(abfd.get());
      if (storage) {
        syms = (asymbol**)malloc(storage);
        if (syms) {
          symcount = bfd_canonicalize_symtab(abfd.get(), syms);
        }
      }
    }
    if (symcount <= 0) {
      if (syms) {
        free(syms);
      }
      return nullptr;
    }
    return new syminfo_t(abfd.release(), syms);
  }

  static void find_address_in_section_cb(bfd *abfd, asection *section, void *data) {
    reinterpret_cast<src_finder_t*>(data)->lookup(abfd, section);
  }

  bool get_source_location(syminfo_t* sym, void* addr, source_location& sloc) {
    src_finder_t finder(sym->syms, (bfd_vma)addr);
    bfd_map_over_sections(sym->handle, &find_address_in_section_cb, &finder);
    if (!finder.found)
      return false;
    sloc = source_location((finder.filename ? finder.filename : ""), finder.line);
    return true;
  }

  bool get_callstack_addr(uint32_t level, void*& addr, std::string& module) {
    uint32_t l = 1 + level;
    std::vector<void*> callstack(1+l);
    uint32_t num_frames = backtrace(callstack.data(), callstack.size());
    if (l >= num_frames)
      return false;
    auto symbols = backtrace_symbols(callstack.data(), num_frames);
    if (symbols == nullptr)
      return false;
    const char* module_path_begin = symbols[l];
    const char* module_path_end = module_path_begin;
    while (*module_path_end && *module_path_end != '(') {
      ++module_path_end;
    }
    module.assign(module_path_begin, module_path_end);
    addr = callstack[l];
    free(symbols);
    return true;
  }

  bool active_;
  void* addr_;
  source_location sloc_;
  std::unordered_map<std::string, syminfo_t*> symbols_;
};

}}
