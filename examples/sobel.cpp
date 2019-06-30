#include <cash.h>
#include <htl/decoupled.h>
#include <htl/counter.h>
#include <htl/queue.h>
#include "common.h"

using namespace ch::logic;
using namespace ch::system;
using namespace ch::htl;
using namespace ch::literals;

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

    input_rows[2] = q_in_.io.deq.data;
    input_rows[1] = ch_delayEn(input_rows[2], enable_, width_);
    input_rows[0] = ch_delayEn(input_rows[1], enable_, width_);

    for (int j = 0; j < 3; ++j) {
      for (int i = 0; i < 2; ++i) {
        window[j][i] = ch_nextEn(window[j][i + 1], enable_);
      }
      window[j][2] = ch_nextEn(input_rows[j], enable_);
    }

    // 5-cycles compute pipeline
    auto gx1a = ch_nextEn(ch_add<9>(window[0][0], window[2][0]), enable_);
    auto gx1b = ch_nextEn(ch_cat(window[1][0], 0_b).as_uint(), enable_);
    auto gx1c = ch_nextEn(ch_add<9>(window[0][2], window[2][2]), enable_);
    auto gx1d = ch_nextEn(ch_cat(window[1][2], 0_b).as_uint(), enable_);
    auto gx2a = ch_nextEn(ch_add<10>(gx1a, gx1b), enable_);
    auto gx2b = ch_nextEn(ch_add<10>(gx1c, gx1d), enable_);
    auto gx3  = ch_nextEn(ch_sub<11>(gx2b, gx2a), enable_);
    auto gx4  = ch_nextEn(ch_abs(gx3.as_int()), enable_);

    auto gy1a = ch_nextEn(ch_add<9>(window[0][0], window[0][2]), enable_);
    auto gy1b = ch_nextEn(ch_cat(window[0][1], 0_b).as_uint(), enable_);
    auto gy1c = ch_nextEn(ch_add<9>(window[2][0], window[2][2]), enable_);
    auto gy1d = ch_nextEn(ch_cat(window[2][1], 0_b).as_uint(), enable_);
    auto gy2a = ch_nextEn(ch_add<10>(gy1a, gy1b), enable_);
    auto gy2b = ch_nextEn(ch_add<10>(gy1c, gy1d), enable_);
    auto gy3  = ch_nextEn(ch_sub<11>(gy2b, gy2a), enable_);
    auto gy4  = ch_nextEn(ch_abs(gy3.as_int()), enable_);

    auto g5  = ch_nextEn(ch_add<12>(gx4, gy4), enable_);
    auto out = ch_slice<8>(ch_min(g5, 255));

    //--
    ch_counter<~0u> delay_ctr(enable_);
    ch_reg<ch_bool> done(false);
    __if (delay_ctr.value() == (5 + width_ * height_)) {
      done->next = true;
    };
    io.done = done;

    //--
    auto input_pending = delay_ctr.value() < (width_ * height_);
    auto init_cycles = 2 * width_ + 3 + 5;
    auto valid_out = (delay_ctr.value() >= init_cycles) && !done;
    this->controller(out.as_uint(), valid_out, input_pending);
  }

protected:

  void controller(const T& value_out,
                  const ch_bool& valid_out,
                  const ch_bool& input_pending) {
    //--
    auto enq_stalled = input_pending && !q_in_.io.deq.valid;
    auto deq_stalled = q_out_.io.enq.valid && !q_out_.io.enq.ready;
    enable_ = !enq_stalled && !deq_stalled;

    //--
    q_in_.io.enq(io.in);
    q_in_.io.deq.ready  = !deq_stalled;
    q_out_.io.deq(io.out);
    q_out_.io.enq.data  = value_out;
    q_out_.io.enq.valid = valid_out && !enq_stalled;
  }

  uint32_t width_;
  uint32_t height_;
  ch_module<ch_llqueue<T, 2>> q_in_;
  ch_module<ch_llqueue<T, 2>> q_out_;
  ch_bool enable_;
};

static const uint8_t src_image[36] = {0xff,0xff,0xff,0xff,0xff,0xff,
                                      0xff,0xff,0xff,0xff,0xff,0xff,
                                      0x80,0x80,0x80,0x80,0x80,0x80,
                                      0x40,0x40,0x40,0x40,0x40,0x40,
                                      0x20,0x20,0x20,0x20,0x20,0x20,
                                      0x10,0x10,0x10,0x10,0x10,0x10};

static const uint8_t ref_image[36] = {0xff,0xff,0xff,0xff,0xff,0xff,
                                      0xff,0xff,0xff,0xff,0xff,0xff,
                                      0xff,0xff,0xff,0xff,0xff,0xff,
                                      0xc0,0xc0,0xc0,0xc0,0x00,0x00,
                                      0x00,0x00,0x00,0x00,0x00,0x00,
                                      0x00,0x00,0x00,0x00,0x00,0x00};

int main() {
  std::vector<uint8_t> dst_image(36);

  //--
  ch_device<sobel<ch_uint8>> device(6, 6);
  ch_tracer tracer(device);

  uint32_t in_pixel = 0;
  uint32_t out_pixel = 0;

  auto ticks = tracer.run([&](ch_tick t)->bool {
    device.io.in.valid = (in_pixel < 36);
    device.io.out.ready = (out_pixel < 36);
    // enqueue data
    if (!!device.io.in.valid && !!device.io.in.ready) {
      device.io.in.data = src_image[in_pixel++];
    }
    // dequeue data
    if (!!device.io.out.valid && !!device.io.out.ready) {
      dst_image.at(out_pixel++) = static_cast<uint8_t>(device.io.out.data);
    }
    // stop simulation when done
    return !device.io.done && (t < 100000);
  });

  std::cout << "Simulation run time: " << std::dec << ticks/2 << " cycles" << std::endl;

  // verify output image
  for (int i = 0; i < 36; ++i) {
    CHECK(dst_image[i] == ref_image[i]);
  }

  ch_toVerilog("sobel.v", device);

  tracer.toText("sobel.log");
  tracer.toVCD("sobel.vcd");
  tracer.toTestBench("sobel_tb.v", "sobel.v", true);
  int ret = !system("iverilog sobel_tb.v -o sobel_tb.iv")
          & !system("! vvp sobel_tb.iv | grep 'ERROR' || false");

  return (0 == ret);
}
