#include "sec.h"
#include "lnodeimpl.h"
#include "ioport.h"
#include "ioimpl.h"
#include "bv.h"

namespace ch {
  std::vector<std::vector<uint>>  sec_api::lattice_= {};
  void sec_api::set_label_int(internal::logic_buffer &lnode, seclabel labelt) {
     lnode.impl()->set_label(labelt);
     //std::cout << labelt << std::endl;
     std::cout << "set node " << lnode.impl()->id() << " label to: " << (lnode.impl()->label()) << std::endl;
  }
  //template<typename K>
  void sec_api::set_dynlabel_int(internal::logic_buffer &nodeValueSrct,
                                 internal::logic_buffer &nodeToSett,
                                 std::function<seclabel(uint8_t)> typefunc) {

    //src/compiler/simref.cpp:1681

    auto nodeValueSrc = nodeValueSrct.impl();
    auto nodeToSet = nodeToSett.impl();



    switch (nodeValueSrc->type()) {
        default: {

        } break;

        case internal::type_input: {
            auto input = reinterpret_cast<internal::inputimpl*>(nodeValueSrc);
            std::ostringstream stream;
            stream << input->value();
            std::cout << "nodevaluesrc: " << input->value() << std::endl;
            auto fakenum = std::stoi(stream.str());
            nodeToSet->set_dynlabel([=]()->seclabel{return typefunc(fakenum);});
            
        } break;
    }
  }
  //could have library of functions for each case
}
