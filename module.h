#pragma once

#include <functional>
#include "vec.h"
#include "node.h"

/*namespace chdl_internal {

class ch_logic;

class module_arg {  
public:
  template <typename T>
  module_arg(const T& value, const std::string& name) 
    : m_nodes(T::bit_count), m_name(name) {    
    for (unsigned i = 0; i < T::bit_count; ++i) {
      m_nodes[i] = &type_indexer<T, node>::get(value, i);
    }
  }
  ~module_arg() {}
  
private:
  std::vector<const node*> m_nodes;
  std::string m_name;
};

class module;

module* module_enter(const std::string& name, 
                     const std::string& func, 
                     unsigned level, 
                     const std::vector<module_arg>& args);

void module_exit(module* module);

class module_visitor {
public:
  template <typename... Args>
  module_visitor(const std::string& name, 
                 const std::string& func, 
                 unsigned level,
                 const Args&... args) {
    m_module = module_enter(name, func, level, {args ...});
  }
  ~module_visitor() {
    module_exit(m_module);    
  } 
private:
  module* m_module;
};

}

#define CHDL_MAKE_MODULE_ARG(i, x) chdl_internal::module_arg(x, CHDL_STRINGIZE(x))
#define CHDL_MAKE_MODULE_ARG_SEP() ,

#define CHDL_GATE(...) \
  chdl_internal::module_visitor chdl_module_visitor(__FUNCTION__, __PRETTY_FUNCTION__, 0,\
    CHDL_FOR_EACH(CHDL_MAKE_MODULE_ARG, CHDL_MAKE_MODULE_ARG_SEP, __VA_ARGS__))

#define CHDL_GATEX(name,...) \
  chdl_internal::module_visitor chdl_module_visitor(chdl_internal::fstring(CHDL_UNPAREN(name)), __PRETTY_FUNCTION__, 0,\
    CHDL_FOR_EACH(CHDL_MAKE_MODULE_ARG, CHDL_MAKE_MODULE_ARG_SEP, __VA_ARGS__))

#define CHDL_COMPONENT(...) \
  chdl_internal::module_visitor chdl_module_visitor(__FUNCTION__, __PRETTY_FUNCTION__, 1,\
    CHDL_FOR_EACH(CHDL_MAKE_MODULE_ARG, CHDL_MAKE_MODULE_ARG_SEP, __VA_ARGS__))

#define CHDL_COMPONENTX(name,...) \
  chdl_internal::module_visitor chdl_module_visitor(chdl_internal::fstring(CHDL_UNPAREN(name)), __PRETTY_FUNCTION__, 1,\
    CHDL_FOR_EACH(CHDL_MAKE_MODULE_ARG, CHDL_MAKE_MODULE_ARG_SEP, __VA_ARGS__))

#define CHDL_MODULE(...) \
  chdl_internal::module_visitor chdl_module_visitor(__FUNCTION__, __PRETTY_FUNCTION__, 2,\
    CHDL_FOR_EACH(CHDL_MAKE_MODULE_ARG, CHDL_MAKE_MODULE_ARG_SEP, __VA_ARGS__))

#define CHDL_MODULEX(name,...) \
  chdl_internal::module_visitor chdl_module_visitor(chdl_internal::fstring(CHDL_UNPAREN(name)), __PRETTY_FUNCTION__, 2,\
    CHDL_FOR_EACH(CHDL_MAKE_MODULE_ARG, CHDL_MAKE_MODULE_ARG_SEP, __VA_ARGS__))
*/
