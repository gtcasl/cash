#include <iostream>
#include <fstream>
#include "common.h"

using namespace std;
using namespace std::placeholders;

__ch_struct(dataS1_t)(
    (ch_bit4) a,
    (ch_bit4) b,
    (ch_bit4) c,
    (ch_bit4) d
);

__ch_struct(dataS2_t)(
    (ch_bit4) r,
    (ch_bit4) s,
    (ch_bit4) t
);

__ch_union(dataU_t)(
  (dataS1_t) a,
  (dataS2_t) b
);

template <unsigned N> 
 __ch_struct(dataT_t)(
  (ch_bitv<N>) a,
  (ch_bitv<N>) b,
  (ch_bitv<N>) c,
  (ch_bitv<N>) d
);

typedef dataT_t<4> datad4_t;

ch_bit4 test_proxies(const ch_bit4& in1, const ch_bitv<64>& in2) {
  ch_logic w(1_b);
  ch_bit2 a, b, c; 
  (a[0], b[0]) = ch_lit<2>(0x1);
  (a[0], b[0], b[1]) = ch_lit<3>(0x1);
  (a.slice<2>(0), w) = ch_lit<3>(0x1);
  //(in2.slice<2>(0), w) = ch_lit<3>(0x1); //-- readonly error expected!
  (a, w) = ch_lit<3>(0x1);
  ch_bit2 q0 = ch_and(in1.slice<2>(0), in2.slice<2>(0));
  ch_bit2 q1 = in1.slice<2>(0);
  ch_bit4 q2 = (in1.slice<2>(0), in2.slice<2>(0));
  ch_bit2 q3 = (in1[0], in2[0]);
  ch_bit4 x = ch_mux(in2, in1);
  ch_bit4 y((in1.slice<2>(1), (w, x[0])));
  //(in1[0], w, in2[0]) = (q0, w);  //-- readonly error expected!
  (a, (b, c)) = (x, y.slice<2>(0));
  (w, x[0], w) = in2.slice<3>(1);  
  y = x + 0x1;
  y = in2.slice<4>(0) + 0x1;
  y = (in2.slice<3>(0), w) + 0x1;
  (w, x.slice<2>(0), w) = in2.slice<4>(0);   
  
  a.slice<1>(0) = 0x0;  
  __ch_tap(y);  
  return y;
}

ch_bit4 Counter4a(
    const ch_logic& clk,  
    const ch_logic& enable,    
    const ch_logic& reset,   
    const ch_bit4& start
  ) {
  ch_bit4 out;
  ch_pushclock(clk);
  ch_pushreset(reset);
  out = ch_reg(ch_select(enable, out + 1, out), start);
  ch_popclock();
  ch_popreset();
  return out;
}

ch_bit4 Counter4b(
    const ch_logic& clk,  
    const ch_logic& enable,    
    const ch_logic& reset,   
    const ch_bit4& start
  ) {
  ch_bit4 out;
  ch_pushclock(clk);
  ch_pushreset(reset);
  out = ch_reg(ch_select(enable, out + 1, out), start);
  ch_popclock();
  ch_popreset();
  return out;
}

ch_bit4 Counter4c() {
  ch_bit4 out;
  out = ch_reg(out + 1);
  return out;
};

ch_logic clock_gater(
    const ch_logic& clk, 
    const ch_logic& enable,
    const ch_logic& reset
  ) {
  ch_logic enable_latched = ch_latch(enable, ~clk, reset);
  return clk & enable_latched;
}

template <unsigned N>
__ch_out(ch_bitv<N>, ch_bitv<N>) CounterX(    
    const ch_logic& enable,
    const ch_bitbase<N>& start,
    const ch_bitbase<N>& max
  ) {
  ch_bitv<N> out;
  ch_bitv<N> out_next;
  ch_bitv<N> count;
  ch_bitv<N> next1 = ch_select<N>(count == max, 0x0, count + 0x1);
  ch_bitv<N> next2 = ch_select(enable, next1, count);
  count = ch_reg(next2, start);
  out = count;
  out_next = next2;
  return __ch_ret(out, out_next);
}

ch_bit4 Counter4f(
    const ch_logic& clk,  
    const ch_logic& enable,    
    const ch_logic& reset  
  ) {
  ch_bit4 out;
  ch_bit4 count;
  ch_bit4 next1 = ch_select<4>(count == 12, 0x0, 0x1);
  ch_bit4 next2 = ch_select(enable, next1, count);
  ch_logic clk2 = clock_gater(clk, reset, enable);
  ch_pushclock(clk2);
  count = ch_reg(next2);
  ch_popclock();
  out = count;
  return out;
}

ch_bitv<16> DataTest() {
  ch_bitv<16> out;
  
  datad4_t data;
  data.a = 0x5;
  data.b = 0x6;
  data.c = 0x7;
  data.d = 0x8;

  out = data.aslice<16>(0) + data.aslice<16>(1);
  
  ch_bit16 q;
  q = 0x0;
  
  q.slice<4>(0) = {0x0, 0x0, 0x0, 0x0};
  
  ch_bit16 x = ch_bit16(0x8);
  ch_bit16 w = ch_select(x == 0x0, out, x);
  auto y = ch_add(out, w);
  
  return out;
}

ch_logic Demo(const ch_logic& input) {
  ch_logic x(input);
  for (int i = 0; i < 2; ++i) {
    x = ch_reg(x);
  }
  return x;
}

void runtest(const std::function<bool(ch_simulator& sim)>& test) {
  ch_vcdtracer sim("test.vcd");
  if (!test(sim))
    sim.run(10);
  sim.close();
} 

int main(int argc, char **argv) {  
  //--
  runtest([&](ch_simulator& sim)->bool {
    ch_signal input, output;
    ch_device myDevice(Demo, input, output);
    __ch_trace(sim, input, output);
    sim.run([&](ch_cycle time)->bool {
      input = (time == 0) ? 1_b : 0_b;
      return (time < 10);
    });
    return true;
  }); 
  
  runtest([&](ch_simulator& sim)->bool {
    ch_bus<16> out;
    ch_device myDevice(DataTest, out);
    __ch_trace(sim, out);
    return false;
  });
    
  runtest([&](ch_simulator& sim)->bool {
    ch_bus<4> out;
    ch_signal clk, enable, reset;
    ch_device myDevice(Counter4f, clk, enable, reset, out);
    __ch_trace(sim, clk, enable, reset, out);
    sim.run([&](ch_cycle time)->bool {
      if (time == false) {
        enable = true;
        reset = true;
      } else {
        reset = false;
      }
      clk.write(~clk.read());
      return (time < 10);
    });
    return true;
  });
    
  runtest([&](ch_simulator& sim)->bool {
    ch_signal out, clk, enable, reset;
    ch_device myDevice(clock_gater, clk, enable, reset, out);
    __ch_trace(sim, clk, enable, reset, out);
    sim.run([&](ch_cycle time)->bool {
      if (time == false) {
        enable = true;
        reset = true;
      } else {
        reset = false;
      }
      clk.write(~clk.read());
      return (time < 10);
    });
    return true;
  });
  
  runtest([&](ch_simulator& sim)->bool {
    ch_bus<4> out;
    ch_device myDevice(Counter4c, out);
    __ch_trace(sim, out);
    return false;
  });
  
  runtest([&](ch_simulator& sim)->bool {
    ch_bus<2> start(0x0), end(0x3), out, out_next;
    ch_signal enable;
    ch_device myDevice(CounterX<2>, enable, start, end, out, out_next);
    __ch_trace(sim, enable, start, end, out, out_next);
    return false;
  });
  
  runtest([&](ch_simulator& sim)->bool {
    ch_signal out, in;
    ch_device myDevice([&](const ch_logic& y)->ch_logic {
      ch_logic x, z;
      ch_bit2 a, b, c; 
      ch_bit4 d, e;      
      a = ch_select(b >= 0x0, c)(b <= 10, c)(b);  
      x = ch_select(y != 0_b, z, 1_b);  
      return x;
    }, in, out);
    __ch_trace(sim, in, out);
    return false;
  });

  return 0;
}
