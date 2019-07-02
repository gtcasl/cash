#include <cash.h>
#include <htl/decoupled.h>
#include <htl/counter.h>
#include <htl/sdf.h>
#include "common.h"

using namespace ch::core;
using namespace ch::htl;

template <typename T>
class sobel {
public:
  __io (
    (ch_enq_io<T>) in,
    (ch_deq_io<T>) out,
    __out(ch_bool) done
  );

  sobel(uint32_t width, uint32_t height)
    : width_(width)
    , height_(height)
  {}

  void describe() {
    std::array<std::array<T, 3>, 3> window;
    std::array<T, 3> input_rows;

    input_rows[2] = sdf_.io.in.data;
    input_rows[1] = ch_delayEn(input_rows[2], sdf_.io.out.ready, width_);
    input_rows[0] = ch_delayEn(input_rows[1], sdf_.io.out.ready, width_);

    for (int j = 0; j < 3; ++j) {
      for (int i = 0; i < 2; ++i) {
        window[j][i] = ch_nextEn(window[j][i + 1], sdf_.io.out.ready);
      }
      window[j][2] = ch_nextEn(input_rows[j], sdf_.io.out.ready);
    }

    // 5-cycles compute pipeline
    auto gx1a = ch_nextEn(ch_add<9>(window[0][0], window[2][0]), sdf_.io.out.ready);
    auto gx1b = ch_nextEn(ch_cat(window[1][0], 0_b).as_uint(), sdf_.io.out.ready);
    auto gx1c = ch_nextEn(ch_add<9>(window[0][2], window[2][2]), sdf_.io.out.ready);
    auto gx1d = ch_nextEn(ch_cat(window[1][2], 0_b).as_uint(), sdf_.io.out.ready);
    auto gx2a = ch_nextEn(ch_add<10>(gx1a, gx1b), sdf_.io.out.ready);
    auto gx2b = ch_nextEn(ch_add<10>(gx1c, gx1d), sdf_.io.out.ready);
    auto gx3  = ch_nextEn(ch_sub<11>(gx2b, gx2a), sdf_.io.out.ready);
    auto gx4  = ch_nextEn(ch_abs(gx3.as_int()), sdf_.io.out.ready);

    auto gy1a = ch_nextEn(ch_add<9>(window[0][0], window[0][2]), sdf_.io.out.ready);
    auto gy1b = ch_nextEn(ch_cat(window[0][1], 0_b).as_uint(), sdf_.io.out.ready);
    auto gy1c = ch_nextEn(ch_add<9>(window[2][0], window[2][2]), sdf_.io.out.ready);
    auto gy1d = ch_nextEn(ch_cat(window[2][1], 0_b).as_uint(), sdf_.io.out.ready);
    auto gy2a = ch_nextEn(ch_add<10>(gy1a, gy1b), sdf_.io.out.ready);
    auto gy2b = ch_nextEn(ch_add<10>(gy1c, gy1d), sdf_.io.out.ready);
    auto gy3  = ch_nextEn(ch_sub<11>(gy2b, gy2a), sdf_.io.out.ready);
    auto gy4  = ch_nextEn(ch_abs(gy3.as_int()), sdf_.io.out.ready);

    auto g5  = ch_nextEn(ch_add<12>(gx4, gy4), sdf_.io.out.ready);
    auto out = ch_slice<8>(ch_min(g5, 255));

    //--
    ch_counter<~0u> delay_ctr(sdf_.io.out.ready);
    ch_reg<ch_bool> done(false);
    __if (delay_ctr.value() == (5 + width_ * height_)) {
      done->next = true;
    };    

    //--
    io.done = done;
    sdf_.io.in.ready = !(delay_ctr.value() < (width_ * height_));
    sdf_.io.out.valid = (delay_ctr.value() >= 2 * width_ + 3 + 5) && !done;
    sdf_.io.out.data = out;
    sdf_.io.enq(io.in);
    sdf_.io.deq(io.out);
  }

protected:

  ch_module<ch_sdf<T>> sdf_;
  uint32_t width_;
  uint32_t height_;  
};

static bool verify(const std::vector<uint8_t>& input,
                   const std::vector<uint8_t>& output,
                   uint32_t width,
                   uint32_t height) {
  const int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
  const int Gy[3][3] = {{-1,-2,-1}, { 0, 0, 0}, { 1, 2, 1}};
  uint32_t o = 0, size = width * height;
  for (uint32_t j = 0; j < height; ++j) {
    for (uint32_t i = 0; i < width; ++i) {
      int sumx(0), sumy(0);
      for (uint32_t wj = 0; wj < 3; ++wj) {
        for (uint32_t wi = 0; wi < 3; ++wi) {
          uint32_t addr = (i+wi) + (j+wj) * width;
          if (addr >= size)
            return true;
          int src = input.at(addr);
          sumx += Gx[wj][wi] * src;
          sumy += Gy[wj][wi] * src;
        }
      }
      int sum = std::abs(sumx) + std::abs(sumy);
      int ref = std::min(sum, 255);
      int out = output.at(o++);
      if (out != ref) {
        std::cout << o << ": " << std::hex << "out=" << out << ", ref=" << ref << std::endl;
        assert(false);
        return false;
      }
    }
  }
  return true;
}

int main() {
  uint32_t width, height;
  std::vector<uint8_t> src_image;
  if (!readPGM("res/einstein.pgm", &width, &height, &src_image))
    return -1;

  auto num_pixels = width * height;
  std::vector<uint8_t> dst_image(num_pixels);

  //--
  ch_device<sobel<ch_uint8>> device(width, height);
  ch_tracer tracer(device);

  uint32_t in_pixel = 0;
  uint32_t out_pixel = 0;

  auto ticks = tracer.run([&](ch_tick t)->bool {
    device.io.in.valid = (in_pixel < num_pixels);
    device.io.out.ready = (out_pixel < num_pixels);
    // enqueue data
    if (!!device.io.in.valid && !!device.io.in.ready) {
      device.io.in.data = src_image[in_pixel++];
    }
    // dequeue data
    if (!!device.io.out.valid && !!device.io.out.ready) {
      dst_image.at(out_pixel++) = static_cast<uint8_t>(device.io.out.data);
    }
    // stop simulation when done
    return !device.io.done && (t < 100000000);
  });

  std::cout << "Simulation run time: " << std::dec << ticks/2 << " cycles" << std::endl;

  // write ouput image
  if (!writePGM(dst_image, width, height, "sobel.pgm"))
    return false;

  // verify output image
  CHECK(verify(src_image, dst_image, width, height));

  ch_toVerilog("sobel.v", device);

  tracer.toText("sobel.log");
  tracer.toVCD("sobel.vcd");
  tracer.toTestBench("sobel_tb.v", "sobel.v", true);
  int ret = !system("iverilog sobel_tb.v -o sobel_tb.iv")
          & !system("! vvp sobel_tb.iv | grep 'ERROR' || false");

  return (0 == ret);
}
