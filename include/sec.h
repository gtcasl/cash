#pragma once

#include "logic.h"
#include "system.h"
#include "streams.h"
#include <iostream>
#include <string>
#include <vector>

namespace ch {

class lnodeimpl;
enum seclabel {
  UNSET=-1, L=0, H=1,
};
/*class secpolicy {

  public:
    secpolicy(uint size) : lattice_(size, std::vector<uint>(size, 0)) { //default is leq
      for (uint i = 0; i < size; i++) {
        for (uint x = i; x < size; x++) {
            lattice_[i][x] = 1;
        }
      }
    }
    secpolicy(std::vector<std::vector<uint>> &latticet) {
      lattice_= latticet;
    }
  private:
    std::vector<std::vector<uint>> lattice_;
 // leq=0; //default: info can flow if src label <= to dst label
 // L  H TS
 // L[1][1][1]
 // H[0][1][1]
 // TS[0][0][1]
  
}; */

class sec_api {
public:

  static void set_policy(uint size) {
    lattice_.erase(lattice_.begin(), lattice_.end());
    lattice_.resize(size, std::vector<uint>(size, 0));

    for (uint i = 0; i < size; i++) {
        for (uint x = i; x < size; x++) {
            lattice_[i][x] = 1;
        }
    }

  }
  static void set_policy(std::vector<std::vector<uint>> &latticet) {
    lattice_.erase(lattice_.begin(), lattice_.end());
    lattice_.resize(latticet.size(), std::vector<uint>(latticet.size(), 0));

    for (auto v: latticet) {
      lattice_.push_back(v);
    }

  }
  static auto policy() {
    return lattice_;
  }
  static bool isSecure(seclabel srclabel, seclabel dstlabel) {
      if (lattice_.empty()){
        return false; //should throw error
      }
      return lattice_[srclabel][dstlabel];
    }
  template <typename T> 
  static void set_label(T Obj, seclabel labelt) {
    auto lnode = internal::logic_accessor::buffer(Obj);
    set_label_int(lnode, labelt);
  }
  template <class T, class Z, class K> //will have to later enforce K to be constrained on Z
  static void set_label_dyn(T dst, Z src, std::function<seclabel(K)> typefunc) {
    auto lnodedst = internal::logic_accessor::buffer(dst);
    auto lnodesrc = internal::logic_accessor::buffer(src);
    std::function<seclabel()> f = [=]() { //copy capture?
      /* return typeFunc(src->impl()->value()); //how to get value from node?
      //is this feasible here without using ctx?
      */
      //temporary
      K obj;
      return typefunc(obj);
    };
    set_dynlabel_int(lnodedst, lnodesrc, f);
  }
  static void set_label_int(internal::logic_buffer &lnode, seclabel labelt);
  static void set_dynlabel_int(internal::logic_buffer &lnodedst,
                                std::function<seclabel()> typeFunc);

protected:

  friend class internal::system_accessor;
  friend class internal::logic_accessor;
  //static secpolicy *policy_;
  static std::vector<std::vector<uint>> lattice_;


};

}
