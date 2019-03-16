#pragma once

#include <unwind.h>
#include <dlfcn.h>
#include <bfd.h>
#include "common.h"

namespace ch {
namespace internal {

class sloc_manager {
public:

  sloc_manager() : active_(false), addr_(nullptr) {
    bfd_init();
  }

  ~sloc_manager() {
    for (auto entry : symbols_) {
      delete entry.second;
    }
  }

  bool register_source_location(uint32_t level) {
    if (active_)
      return false;
    std::string module;
    void* addr;
    if (!get_callstack_info(level+1, addr, module))
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

  const source_location& get_source_location() const {
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

  struct bt_data_t {
    uint32_t nskip;
    void* addr;

    bt_data_t(uint32_t level) : nskip(level+1), addr(nullptr) {}

    _Unwind_Reason_Code walk(_Unwind_Context* ctx) {
      int ip_before_insn = 0;
      auto pc = _Unwind_GetIPInfo(ctx, &ip_before_insn);
      if (!ip_before_insn)
        --pc;
      auto ip = reinterpret_cast<void*>(pc);
      if (--nskip == 0) {
        addr = ip;
        return _URC_END_OF_STACK;
      }
      return _URC_NO_REASON;
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

  static _Unwind_Reason_Code backtrace_cb(_Unwind_Context* ctx, void *data) {
    return (reinterpret_cast<bt_data_t*>(data))->walk(ctx);
  }

  bool get_callstack_info(uint32_t level, void*& addr, std::string& module) {
    bt_data_t bt_data(level+1);
    _Unwind_Backtrace(&backtrace_cb, &bt_data);
    if (nullptr == bt_data.addr)
      return false;
    Dl_info dlinfo;
    if (!dladdr(bt_data.addr, &dlinfo)) {
      return false;
    }
    addr = bt_data.addr;
    module = dlinfo.dli_fname;
    return true;
  }

  bool active_;
  void* addr_;
  source_location sloc_;
  std::unordered_map<std::string, syminfo_t*> symbols_;
};

}}
