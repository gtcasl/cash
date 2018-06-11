#include <cash.h>

using namespace ch::core;
using namespace ch::literals;
using namespace ch::sim;

struct VendingMachine {
  __enum (Coin, (dime, nickel));
  __enum (State, (idle, s5, s10, s15, sOk));
  __io (
    __in(Coin)     coin,
    __out(ch_bool) valid
  );

  void describe() {
    ch_reg<State> state(State::idle);
    __switch (state)
    __case (State::idle) {
      __if (io.coin == Coin::nickel) { state <<= State::s5; };
      __if (io.coin == Coin::dime) { state <<= State::s10; };
    }
    __case (State::s5) {
      __if (io.coin == Coin::nickel) { state <<= State::s10; };
      __if (io.coin == Coin::dime) { state <<= State::s15; };
    }
    __case (State::s10) {
      __if (io.coin == Coin::nickel) { state <<= State::s15; };
      __if (io.coin == Coin::dime) { state <<= State::sOk; };
    }
    __case (State::s15) {
      __if (io.coin == Coin::nickel) { state <<= State::sOk; };
      __if (io.coin == Coin::dime) { state <<= State::sOk; };
    }
    __case (State::sOk) {
      state <<= State::idle;
    };
    io.valid = (state == State::sOk);
  }
};

int main() {
  ch_device<VendingMachine> vending;

  vending.io.coin = VendingMachine::Coin::nickel;

  ch_vcdtracer tracer("vending.vcd", vending);
  tracer.run(2*(1+4));

  std::cout << "result:" << std::endl;
  std::cout << "valid = "  << vending.io.valid << std::endl;

  assert(vending.io.valid);

  ch_toVerilog("vending.v", vending);
  ch_toFIRRTL("vending.fir", vending);

  int ret = system("iverilog vending_tb.v -o vending_tb.iv")
          | system("vvp vending_tb.iv");
  return ret != 0;
}
