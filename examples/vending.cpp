#include <cash.h>

using namespace ch::core;
using namespace ch::literals;
using namespace ch::sim;

struct VendingMachine {
  __io (
    __in(ch_bool)  nickel,
    __in(ch_bool)  dime,
    __out(ch_bool) valid
  );

  __enum (State, (idle, s5, s10, s15, sOk));

  void describe() {
    ch_seq<State> state(State::idle);
    __switch (state)
    __case (State::idle) {
      __if (io.nickel) { state.next = State::s5; };
      __if (io.dime) { state.next = State::s10; };
    }
    __case (State::s5) {
      __if (io.nickel) { state.next = State::s10; };
      __if (io.dime) { state.next = State::s15; };
    }
    __case (State::s10) {
      __if (io.nickel) { state.next = State::s15; };
      __if (io.dime) { state.next = State::sOk; };
    }
    __case (State::s15) {
      __if (io.nickel) { state.next = State::sOk; };
      __if (io.dime) { state.next = State::sOk; };
    }
    __case (State::sOk) {
      state.next = State::idle;
    };
    io.valid = (state == State::sOk);
  }
};

int main() {
  ch_device<VendingMachine> vending;

  vending.io.nickel = true;
  vending.io.dime = false;

  ch_vcdtracer tracer("vending.vcd", vending);
  tracer.run(2*(1+4));

  std::cout << "result:" << std::endl;
  std::cout << "valid = "  << vending.io.valid << std::endl;

  assert(vending.io.valid);

  ch_toVerilog("vending.v", vending);
  ch_toFIRRTL("vending.fir", vending);

  return 0;
}
