#include "memimpl.h"
#include "mem.h"
#include "context.h"
#include "litimpl.h"
#include "proxyimpl.h"

using namespace ch::internal;

sdata_type ch::internal::loadInitData(const std::string& file,
                                      uint32_t data_width,
                                      uint32_t num_items) {

  auto skip_space_or_comment = [](const char* str, uint32_t len) {
    while (len) {
      if (std::isspace(str[0])) {
        ++str;
        --len;
      } else
      if (len && str[0] == '/') {
        CH_CHECK(len > 1, "invalid character");
        if (str[1] == '/')
          return str + len; // return end of string

        CH_CHECK(str[1] == '*', "invalid character");
        str += 2;
        len -= 2;
        while (!(len > 1 && str[0] == '*' && str[1] == '/')) {
          ++str;
          --len;
        }
        CH_CHECK(len > 1, "invalid character");
        str += 2;
        len -= 2;
      } else {
        break;
      }
    }
    return str;
  };

  auto skip_next = [](const char* str, uint32_t len) {
    while (len && !(std::isspace(str[0]) || str[0] == '/')) {
      ++str;
      --len;
    }
    return str;
  };

  auto addr_width = log2ceil(num_items);
  sdata_type out(data_width * num_items);
  sdata_type sword(data_width);
  sdata_type saddr(addr_width);
  std::ifstream in(file, std::ios::binary);
  std::string line;
  uint32_t addr = 0;

  while (std::getline(in, line)) {
    auto str_orig = line.c_str();
    uint32_t len_orig = line.length();
    while (len_orig) {
      auto str = skip_space_or_comment(str_orig, len_orig);
      uint32_t len = len_orig - (str - str_orig);
      if (0 == len)
        break;

      bool is_address = false;
      if (str[0] == '@') {
        CH_CHECK(len > 1, "invalid character");
        ++str;
        --len;
        is_address = true;
      }

      str_orig = skip_next(str, len);
      uint32_t wlen = str_orig - str;

      if (is_address) {
        bv_assign(saddr.words(), data_width, str, wlen, 4);
        addr = bv_cast<uint32_t>(saddr.words(), data_width);
      } else {
        bv_assign(sword.words(), data_width, str, wlen, 4);
        out.copy(addr * data_width, sword, 0, data_width);
        ++addr;
      }

      str += wlen;
      len -= wlen;
      str_orig = str;
      len_orig = len;
    }
  }

  return out;
}

///////////////////////////////////////////////////////////////////////////////

memimpl::memimpl(context* ctx,
                 uint32_t data_width,
                 uint32_t num_items,
                 const sdata_type& init_data,
                 bool force_logic_ram,
                 const source_location& sloc,
                 const std::string& name)
  : ioimpl(ctx, type_mem, data_width * num_items, sloc, name)
  , init_data_(init_data)
  , data_width_(data_width)
  , num_items_(num_items)
  , force_logic_ram_(force_logic_ram)
{}

lnodeimpl* memimpl::clone(context* ctx, const clone_map&) const {
  return ctx->create_node<memimpl>(data_width_, num_items_, init_data_, force_logic_ram_, sloc_, name_);
}

memportimpl* memimpl::create_arport(lnodeimpl* addr, const source_location& sloc) {
  for (auto port : rdports_) {
    if (port->addr().id() == addr->id())
      return port;
  }
  auto impl = ctx_->create_node<marportimpl>(this, addr, sloc);
  rdports_.emplace_back(impl);
  return impl;
}

memportimpl* memimpl::create_srport(lnodeimpl* cd,
                                    lnodeimpl* addr,
                                    lnodeimpl* enable,
                                    const source_location& sloc) {
  for (auto port : rdports_) {
    if (port->addr().id() == addr->id())
      return port;
  }
  auto impl = ctx_->create_node<msrportimpl>(this, cd, addr, enable, sloc);
  rdports_.emplace_back(impl);
  return impl;
}

mwportimpl* memimpl::create_wport(lnodeimpl* cd,
                                  lnodeimpl* addr,
                                  lnodeimpl* wdata,
                                  lnodeimpl* enable,
                                  const source_location& sloc) {
  for (auto port : wrports_) {
    if (port->addr().id() == addr->id())
      CH_ABORT("duplicate memory write to the same address not allowed");
  }
  auto impl = ctx_->create_node<mwportimpl>(this, cd, addr, wdata, enable, sloc);
  wrports_.emplace_back(impl);
  return impl;
}

void memimpl::remove_port(memportimpl* port) {
  switch (port->type()) {
  case type_marport:
  case type_msrport:
    for (auto it = rdports_.begin(), end = rdports_.end(); it != end; ++it) {
      if ((*it)->id() == port->id()) {
        rdports_.erase(it);
        break;
      }
    }
    break;
  case type_mwport:
    for (auto it = wrports_.begin(), end = wrports_.end(); it != end; ++it) {
      if ((*it)->id() == port->id()) {
        wrports_.erase(it);
        break;
      }
    }
    break;
   default:
    break;
  }
}

int memimpl::port_index(memportimpl* port) const {
  switch (port->type()) {
  case type_marport:
  case type_msrport:
    for (int i = 0, n = rdports_.size(); i < n; ++i) {
      if (rdports_[i]->id() == port->id())
        return i;
    }
    break;
  case type_mwport:
    for (int i = 0, n = wrports_.size(); i < n; ++i) {
      if (wrports_[i]->id() == port->id())
        return i;
    }
    break;
  default:
    break;
  }
  return -1;
}

bool memimpl::is_readwrite(memportimpl* port) const {
  if (type_mwport == port->type()) {
    for (auto p : wrports_) {
      if (p->addr().id() == port->id())
        return true;
    }
  } else {
    for (auto p : rdports_) {
      if (p->addr().id() == port->id())
        return true;
    }
  }
  return false;
}

bool memimpl::is_logic_rom() const {
  if (!wrports_.empty())
    return false;
  for (auto p : rdports_) {
    if (p->has_cd())
      return false;
  }
  return true;
}

void memimpl::print(std::ostream& out) const {
  out << "#" << id_ << " <- " << this->type() << this->size();
  uint32_t n = this->srcs().size();
  if (n > 0) {
    out << "(";
    for (uint32_t i = 0; i < n; ++i) {
      if (i > 0)
        out << ", ";
      out << "#" << this->src(i).id();
    }
    out << ")";
  }
}

///////////////////////////////////////////////////////////////////////////////

memportimpl::memportimpl(context* ctx,
                         lnodetype type,
                         uint32_t size,
                         memimpl* mem,
                         lnodeimpl* cd,
                         lnodeimpl* addr,
                         lnodeimpl* enable,
                         const source_location& sloc)
  : ioimpl(ctx, type, size, sloc, mem->name())
  , mem_(mem)
  , cd_idx_(-1)
  , addr_idx_(-1)
  , enable_idx_(-1) {
  mem_ = mem;
  mem->acquire();

  // allocate clock domain
  if (cd) {
    cd_idx_ = this->add_src(cd);
  }

  // add port address
  addr_idx_ = this->add_src(addr);

  // add enable predicate
  if (enable
   && !(type_lit == enable->type()
    && reinterpret_cast<litimpl*>(enable)->value().is_ones())) {
    enable_idx_ = this->add_src(enable);
  }
}

memportimpl::~memportimpl() {
  mem_->release();
}

///////////////////////////////////////////////////////////////////////////////

marportimpl::marportimpl(context* ctx,
                         memimpl* mem,
                         lnodeimpl* addr,
                         const source_location& sloc)
  : memportimpl(ctx, type_marport, mem->data_width(), mem, nullptr, addr, nullptr, sloc) {
  // add memory as source
  this->add_src(mem);
}

marportimpl::~marportimpl() {
  mem_->remove_port(this);
}

lnodeimpl* marportimpl::clone(context*, const clone_map& cloned_nodes) const {
  auto mem = reinterpret_cast<memimpl*>(cloned_nodes.at(mem_->id()));
  auto addr = cloned_nodes.at(this->addr().id());
  return mem->create_arport(addr, sloc_);
}

///////////////////////////////////////////////////////////////////////////////

msrportimpl::msrportimpl(context* ctx,
                         memimpl* mem,
                         lnodeimpl* cd,
                         lnodeimpl* addr,
                         lnodeimpl* enable,
                         const source_location& sloc)
  : memportimpl(ctx, type_msrport, mem->data_width(), mem, cd, addr, enable, sloc) {
  // add memory as source
  this->add_src(mem);
}

msrportimpl::~msrportimpl() {
  mem_->remove_port(this);
}

lnodeimpl* msrportimpl::clone(context*, const clone_map& cloned_nodes) const {
  auto mem = reinterpret_cast<memimpl*>(cloned_nodes.at(mem_->id()));
  auto addr = cloned_nodes.at(this->addr().id());
  auto cd = cloned_nodes.at(this->cd().id());
  lnodeimpl* enable = nullptr;
  if (this->has_enable()) {
    enable = cloned_nodes.at(this->enable().id());
  }
  return mem->create_srport(cd, addr, enable, sloc_);
}

///////////////////////////////////////////////////////////////////////////////

mwportimpl::mwportimpl(context* ctx,
                       memimpl* mem,
                       lnodeimpl* cd,
                       lnodeimpl* addr,
                       lnodeimpl* wdata,
                       lnodeimpl* enable,
                       const source_location& sloc)
  : memportimpl(ctx, type_mwport, 0, mem, cd, addr, enable, sloc) {
  // add as memory source
  mem->add_src(this);

  // add data source
  wdata_idx_ = this->add_src(wdata);
}

mwportimpl::~mwportimpl() {
  mem_->remove_port(this);
}

lnodeimpl* mwportimpl::clone(context* ctx, const clone_map& cloned_nodes) const {
  memimpl* mem;
  auto it = cloned_nodes.find(mem_->id());
  if (it == cloned_nodes.end()) {
    mem = reinterpret_cast<memimpl*>(mem_->clone(ctx, cloned_nodes));
  } else {
    mem = reinterpret_cast<memimpl*>(it->second);
  }
  auto addr = cloned_nodes.at(this->addr().id());
  auto wdata = cloned_nodes.at(this->wdata().id());
  lnodeimpl* enable = nullptr;
  if (this->has_enable()) {
    enable = cloned_nodes.at(this->enable().id());
  }
  lnodeimpl* cd = nullptr;
  if (this->has_cd()) {
    cd = cloned_nodes.at(this->cd().id());
  }
  return mem->create_wport(cd, addr, wdata, enable, sloc_);
}

///////////////////////////////////////////////////////////////////////////////

memory::memory(uint32_t data_width,
               uint32_t num_items,
               const sdata_type& init_data,
               bool is_logic_rom,
               const std::string& name,
               const sloc_getter&) {
  CH_CHECK(!ctx_curr()->conditional_enabled(), "memory objects disallowed inside conditional blocks");
  auto id = identifier_from_typeid(name);
  auto sloc = get_source_location();
  impl_ = ctx_curr()->create_node<memimpl>(data_width, num_items, init_data, is_logic_rom, sloc, id);
}

lnode memory::aread(const lnode& addr) const {
  auto sloc = get_source_location();
  return impl_->create_arport(addr.impl(), sloc);
}

lnode memory::sread(const lnode& addr, const lnode& enable) const {
  auto sloc = get_source_location();
  auto cd = ctx_curr()->current_cd(sloc);
  return impl_->create_srport(cd, addr.impl(), enable.impl(), sloc);
}

void memory::write(const lnode& addr, const lnode& value, const lnode& enable) {
  CH_CHECK(!ctx_curr()->conditional_enabled(), "memory access disallowed inside conditional blocks");
  auto sloc = get_source_location();
  auto cd = ctx_curr()->current_cd(sloc);
  impl_->create_wport(cd, addr.impl(), value.impl(), enable.impl(), sloc);
}
