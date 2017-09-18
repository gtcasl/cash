#include <cash.h>

using namespace cash::core;
using namespace cash::core_literals;
using namespace cash::sim;

#define CHECK(x) if (!(x)) { assert(false); exit(1); }


template <typename D, typename T>
struct Base0 {
  D* self() { return (D*)this; }
  int foo(T x) {
    return x + D::size;
  }
};

template <typename D>
struct Base1 : public Base0<D, int> {
  void bar() {}
};

template <typename D>
struct Base1_R : public Base1<D> {
  void read() {}
};

template <typename D>
struct Base1_W : public Base1<D> {
  void write() {}
};

template <int N>
class ObjR : Base1_R< ObjR<N> > {
private:
  struct __Y { int m; };
public:
  using Y = __Y;
  static constexpr int size = N;
};

template <int N>
struct ObjW : Base1_R< ObjW<N> > {
  static constexpr int size = N;
};

template <unsigned N>
__out(ch_bit<N>, ch_bit1) Adder(
    const ch_bit<N>& lhs,
    const ch_bit<N>& rhs,
    const ch_bit1& cin) {
  auto sum = (0_b, lhs) + ch_zext<N+1>(rhs) + ch_zext<N+1>(cin);
  ch_bit<N> out = sum.template slice<N>();
  ch_bit1 cout = sum[N];
  __ret(out, cout);
}

int main(int argc, char **argv) {

  ObjR<3> r;
  ObjR<3>::Y q;
  ObjW<5> w;


  std::ofstream vcd_file("adder.vcd");
  ch_bus1 cout, cin(1);
  ch_bus2 out, lhs(1), rhs(3);
  
  auto adder = ch_function(Adder<2>);
  std::tie(out, cout) = adder(lhs, rhs, cin);

  /*std::ofstream v_file("adder.v");
  adder.to_verilog("adder", v_file);
  v_file.close();*/

  ch_vcdtracer tracer(vcd_file, adder);
  __trace(tracer, lhs, rhs, cin, out, cout);
  tracer.run();
  
  std::cout << "result:" << std::endl;
  std::cout << "cout = " << cout << std::endl;
  std::cout << "out = " << out << std::endl;

  CHECK(cout == 1 && out == 1);

  return 0;
}
