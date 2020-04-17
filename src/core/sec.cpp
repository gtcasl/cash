#include "sec.h"
#include "lnodeimpl.h"

namespace ch {
  std::vector<std::vector<uint>>  sec_api::lattice_= {};
  void sec_api::set_label_int(internal::logic_buffer &lnode, seclabel labelt) {
     lnode.impl()->set_label(labelt);
     //std::cout << labelt << std::endl;
     std::cout << "set node " << lnode.impl()->id() << " label to: " << (lnode.impl()->label()) << std::endl;
  }
}
