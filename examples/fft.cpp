#include <math.h>
#include <complex>
#include <core.h>
#include <htl/counter.h>
#include <htl/decoupled.h>
#include <htl/complex.h>
#include <htl/fixed.h>
#include <htl/sdf.h>
#include "common.h"

using namespace ch::core;
using namespace ch::htl;

// reference: https://ieeexplore.ieee.org/document/508145/

template <typename T, unsigned N, unsigned stage>
class twiddle_table {
private:
  static constexpr unsigned A = N / (1 << (2*stage+2));
  using rom_t = ch_rom<T, 4*A>;

  static auto init_data() {
    std::vector<uint8_t> buffer(ceildiv<uint32_t>(ch_width_v<T>, 8) * 4*A);
    double coeff = -2.0 * M_PI / N;
    for (unsigned x = 0; x < 4*A; ++x) {
      unsigned k = 0;
      if (x >= 3*A) {
        k = (3 << (2*stage)) * (x-3*A);
      } else if (x >= 2*A) {
        k = (1 << (2*stage)) * (x-2*A);
      } else if (x >= 1*A) {
        k = (2 << (2*stage)) * (x-1*A);
      }
      ch_system_t<T> tw;
      tw.re = std::cos(coeff * k);
      tw.im = std::sin(coeff * k);
      ch_read(tw, 0, buffer.data(), x * ch_width_v<T>, ch_width_v<T>);
    }
    return buffer;
  }

  rom_t rom_;

public:

  twiddle_table() : rom_(init_data()) {}

  auto read(const ch_uint<rom_t::addr_width>& addr) const {
    return rom_.read(addr);
  }
};

template <typename T, unsigned N>
class Fft {
public:  
  static_assert(ispow2(N), "invalid size");
  static constexpr unsigned logN = log2floor(N);
  static_assert(0 == (logN & 0x1), "invalid size");
  using value_type = ch_complex<T>;
  using state_t = ch_valid_t<value_type>;

  __io (
    (ch_enq_io<value_type>) in,
    (ch_deq_io<value_type>) out
  );

  void describe() {
    state_t state{sdf_.io.deq.valid, sdf_.io.deq.data};
    static_for<0, logN/2>([&](auto stage) {
      state = this->butterfly21<stage>(state.clone());
      state = this->butterfly22<stage>(state.clone());
      if constexpr (stage < logN/2-1) {
        state = this->rotation<stage>(state.clone());
      }
    });
    controller(state);
  }

private:

  auto trivial_rotate(const ch_complex<T>& x) {
    return ch_complex<T>(-x.re, x.im);
  }

  auto butterfly(const ch_complex<T>& lhs, const ch_complex<T>& rhs) const {
    return std::tuple(lhs + rhs, lhs - rhs);
  }

  template <unsigned stage>
  auto butterfly21(const state_t& in) {
    state_t out;
    value_type d_in;
    constexpr unsigned A = 1 << (logN - 2 * stage);

    ch_counter<A> index(in.valid && sdf_.io.enq.ready);
    auto toggle = index.value()[log2ceil(A)-1];
    auto d_out  = ch_delayEn(d_in, sdf_.io.enq.ready, A/2);
    auto [bf1, bf2] = butterfly(d_out, in.data);
        d_in  = ch_sel(toggle, bf2, in.data);
    auto ret  = ch_sel(toggle, bf1, d_out);
    out.data  = ch_delayEn(ret, sdf_.io.enq.ready, 1);
    out.valid = ch_delayEn(in.valid, sdf_.io.enq.ready, A/2 + 1, false);

    return out;
  }

  template <unsigned stage>
  auto butterfly22(const state_t& in) {
    state_t out;
    value_type d_in;
    constexpr unsigned A = 1 << (logN - 2 * stage);

    ch_counter<A> index1(in.valid && sdf_.io.enq.ready);
    auto rotate = index1.value()[log2ceil(A)-1];
    auto tv_rot = trivial_rotate(in.data);
    auto b_in   = ch_delayEn(ch_sel(rotate, tv_rot, in.data), sdf_.io.enq.ready, 1);
    auto value  = ch_delayEn(in.data, sdf_.io.enq.ready, 1);
    auto valid  = ch_delayEn(in.valid, sdf_.io.enq.ready, 1, false);

    ch_counter<A/2> index2(valid && sdf_.io.enq.ready);
    auto toggle = index2.value()[log2ceil(A)-2];
    auto d_out  = ch_delayEn(d_in, sdf_.io.enq.ready, A/4);
    auto [bf1, bf2] = butterfly(d_out, b_in);
        d_in  = ch_sel(toggle, bf2, value);
    auto ret  = ch_sel(toggle, bf1, d_out);
    out.data  = ch_delayEn(ret, sdf_.io.enq.ready, 1);
    out.valid = ch_delayEn(valid, sdf_.io.enq.ready, A/4 + 1, false);

    return out;
  }

  template <unsigned stage>
  auto rotation(const state_t& in) {
    state_t out;
    twiddle_table<value_type, N, stage> twiddle;
    constexpr unsigned A = 1 << (logN - 2 * stage);

    ch_counter<A> index(in.valid && sdf_.io.enq.ready);
    auto x  = ch_delayEn(in.data, sdf_.io.enq.ready, 1);
    auto tw = ch_delayEn(twiddle.read(index.value()), sdf_.io.enq.ready, 1);    
    out.data  = ch_delayEn(x * tw, sdf_.io.enq.ready, 5);
    out.valid = ch_delayEn(in.valid, sdf_.io.enq.ready, 6, false);

    return out;
  }

  void controller(const state_t& out) {
    ch_counter<N> index(sdf_.io.deq.valid && sdf_.io.enq.ready);
    sdf_.io.deq.ready = (0 == index.value());
    sdf_.io.enq.valid = out.valid;
    sdf_.io.enq.data  = out.data;
    sdf_.io.in(io.in);
    sdf_.io.out(io.out);
  }

  ch_module<ch_sdf<value_type>> sdf_;
};

static const int FFT_SIZE = 64;

static const uint32_t in_samples[FFT_SIZE] = {
  0xff7601be,0x1870173,0xfe74021c,0x160ff28,0x47fedd,0xa9ffe2,0x12ff4f,0x2220251,
  0x11d00b2,0x8cfe2a,0xfeaffd86,0x18ffe25,0xff7efe3e,0xfdfffe1b,0xfe8f028e,0x1bc0011,
  0xfef50094,0x2000b4,0x26cfff8,0x164fef0,0x1620023,0x201ff7d,0xff3ffee4,0x2250193,
  0x24dfdcc,0xfde10022,0xd6fe6d,0xff3a01ff,0xfd8bfdc5,0xfdc3ffc9,0x269fea9,0x1cc020f,
  0x34fece,0x155ff5c,0xdc0010,0xfda40029,0x236ffae,0x1220235,0x139fee5,0xff4100b7,
  0xfe4a00f6,0x1f2ffb1,0xff2201af,0x204fe9d,0xf5ff3c,0x740256,0x1d600ce,0x22cffb1,
  0x19dff7b,0x21b00f1,0xfe8cffe9,0x227024e,0x1f3fe32,0xffa700b9,0xfee1009d,0xff040177,
  0xfe99ffbb,0xfedbfe66,0xff93004a,0x215fe4f,0xfe16fdf8,0x155fffa,0x23a027b,0xff6700f2
};

static const uint32_t ref_samples[FFT_SIZE] = {
  0x19bcffcf,0xf0fef047,0x495e9ee,0xfa5dfd7c,0xde00b49,0xf3dcfc37,0x4690c80,0xf46312c4,
  0xff7217ff,0x7b208b5,0xe3a307de,0x651040a,0x45aeee3,0xfbc2ec01,0xf9bf0368,0x1481006c,
  0xf52f0753,0xfd2df565,0xf0550507,0xf39f0119,0x37fe25,0x2fedab,0xff8e0012,0x170092a,
  0x475f6fb,0xf5990ccd,0x13680714,0x9ea0ca0,0x42f0a7b,0xf1dbef79,0x113e0180,0xfb18fce4,
  0x729ffac,0xee8310ee,0x64dfe1c,0xf7e7f77a,0xf6de15f4,0x58401f8,0x17fd063b,0xf0750c31,
  0xe996f621,0xfe7cf7f1,0xe87f9e6,0x257f204,0xec07f784,0x105bf660,0xe92d092a,0xb5902d6,
  0xc561379,0xc2c08f3,0xf8280f59,0xffcefc27,0xfd1a0687,0x51602db,0x6aefea1,0xfada1839,
  0x6b5037b,0xe95f215,0xef020c5e,0xf8f80226,0xff39f485,0x102d0517,0xf4080d4e,0xf0b6063a
};

int main() {
  // create FFT device
  ch_device<Fft<ch::htl::ch_fixed<16, 15>, FFT_SIZE>> device;
  ch_tracer tracer(device);

  unsigned in_sample = 0;
  unsigned out_sample = 0;  
  std::vector<uint32_t> out_samples(FFT_SIZE);

  // run simulation
  auto ticks = tracer.run([&](ch_tick t)->bool {
    device.io.in.valid = (in_sample < FFT_SIZE);
    device.io.out.ready = (out_sample < FFT_SIZE);
    // enqueue data
    if (device.io.in.valid && device.io.in.ready) {
      device.io.in.data.as_int() = in_samples[in_sample++];
    }
    // dequeue data
    if (device.io.out.valid && device.io.out.ready) {
      out_samples[out_sample++] = (int)device.io.out.data.as_int();
    }
    // stop simulation when done
    return (out_sample < FFT_SIZE) && (t < MAX_TICKS);
  }, 2);

  std::cout << "Simulation run time: " << std::dec << ticks/2 << " cycles" << std::endl;

  // verify output
  for (int i = 0; i < FFT_SIZE; ++i) {
    CHECK(out_samples[i] == ref_samples[i]);
  }

  ch_toVerilog("fft.v", device);
  ch_toFIRRTL("fft.fir", device);

  tracer.toText("fft.log");
  tracer.toVCD("fft.vcd");
  tracer.toVerilog("fft_tb.v", "fft.v");
  int ret = !system("iverilog fft_tb.v -o fft_tb.iv")
          & !system("! vvp fft_tb.iv | grep 'ERROR' || false");

  return (0 == ret);
}
