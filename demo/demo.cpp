#include <cash/core.h>
#include <cash/sec.h>

using namespace ch::core;

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
    ch_reg<ch_bit<4>> reg(0);
    //reg.set_label(); //what is impl on next iteration when reg value updated
    //ch::sec_api::set_label(reg, ch::seclabel::H);
    ch::sec_api::set_label(io.lhs, ch::seclabel::L);
    ch::sec_api::set_label(io.rhs, ch::seclabel::L);
    ch::sec_api::set_label(io.out, ch::seclabel::L);
    ch::sec_api::set_policy(2);
  }
};

int main() {
  // instantiate a 4-bit adder
  ch_device<Adder<4>> my_adder;

  // assign input values
  my_adder.io.lhs = 1;
  my_adder.io.rhs = 3;

  // run simulation
  ch_simulator sim(my_adder);
  sim.run();
  
  // get result
    std::cout << "result = "  << my_adder.io.out << std::endl;

  return 0;
}
