#include <cash.h>
#include <math.h>

// reference: https://github.com/tchoi8/verilog/blob/master/examples/sqrt.vl

#define CHECK(x) do { if (!(x)) { std::cout << "FAILED: " << #x << std::endl; std::abort(); } } while (false)

using namespace ch::logic;
using namespace ch::system;
using namespace ch::literals;
using namespace ch::extension;

template <unsigned I, unsigned O>
__inout(sqrt_io, (
  __in  (ch_int<I>) in,
  __out (ch_int<O>) out,
  __out (ch_int<I>) valid
));

template <unsigned I, unsigned O>
struct SqrtUDF {
  ch_system_io<sqrt_io<I, O>> io;

  void eval() {
    io.out = static_cast<int32_t>(sqrt(static_cast<int32_t>(io.in)));
    io.valid = (4 == ticks_++);
  }

  void reset() {
    ticks_ = 0;
  }

  bool to_verilog(std::ostream&, udf_verilog_mode) {
    return false;
  }

  int ticks_;
};

template <unsigned I, unsigned O>
struct Sqrt {
  sqrt_io<I, O> io;

  void describe() {
    ch_udf_seq<SqrtUDF<I, O>> sqrt;
    sqrt.io(io);
  }
};

int main() {
  ch_device<Sqrt<32, 16>> sqrt;

  ch_tracer tracer(sqrt);
  sqrt.io.in = 9;
  tracer.run([&](ch_tick)->bool { return !!sqrt.io.valid; });

  std::cout << "result:" << std::endl;
  std::cout << "out = "  << sqrt.io.out << std::endl;

  ch_toVerilog("sqrt.v", sqrt);

  tracer.toText("sqrt.log");
  tracer.toVCD("sqrt.vcd");
  tracer.toTestBench("sqrt_tb.v", "sqrt.v");
  int ret = system("iverilog sqrt_tb.v -o sqrt_tb.iv")
          | system("! vvp sqrt_tb.iv | grep 'ERROR' || false");
  return ret != 0;
}
