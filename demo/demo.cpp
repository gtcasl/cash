#include <cash/core.h>
#include <cash/sec.h>

using namespace ch::core;


ch::seclabel simpleLabel(uint8_t input) {
  std::cout << "label func executed with input:  " << unsigned(input) << std::endl;
  return input ? ch::seclabel::H : ch::seclabel::L;
}

// hardware description
template <unsigned N>
struct Adder {
  __io (
    __in (ch_uint<N>)  lhs,
    __in (ch_uint<N>)  rhs,
    __out (ch_uint<N>) out
  );

  void describe() {
    io.out = io.lhs + io.rhs;

    ch::sec_api::set_policy(2); // Simple L/H lattice
    //dst=L dst=H
    // 1     1 src=L
    // 0     0 src=H
    // valid = lattice[srcLabel][dstLabel] == 1

    ch::sec_api::set_label(io.lhs, ch::seclabel::L);
    ch::sec_api::set_label(io.out, ch::seclabel::L);
    ch::sec_api::set_label(io.rhs, ch::seclabel::H); // this will fail verification.
  }
};

int main() {
  // instantiate a 8-bit adder
  ch_device<Adder<8>> my_adder;

  // assign input values
  my_adder.io.lhs = 1;
  my_adder.io.rhs = 2;

  // run simulation
  ch_simulator sim(my_adder);
  sim.run();
  
  // get result
    std::cout << "result = "  << my_adder.io.out << std::endl;

  return 0;
}
