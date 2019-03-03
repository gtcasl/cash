#include <htl/router.h>
#include "common.h"

using namespace ch::htl::router;
using namespace std::placeholders;

class TestBench {
public:

  enum {
    NUM_TILES_X = 2,
    NUM_TILES_Y = 2
  };

  using Flit = DefaultFlit<NUM_TILES_X, NUM_TILES_Y, 64, 11, 16>::Type;
  using Cfg = RouterConfig<5, 5, 4, Flit>;
  typedef Router<Cfg> router_t;
  typedef ch_vec<ch_vec<router_t::flit_t, NUM_TILES_X>, NUM_TILES_Y> flitIn_t;
  typedef ch_vec<ch_vec<ch_bool, NUM_TILES_X>, NUM_TILES_Y> creditIn_t;
  typedef ch_vec<ch_vec<ch_vec<router_t::flit_t, Cfg::num_output_ports>, NUM_TILES_X>, NUM_TILES_Y> flitOut_t;
  typedef ch_vec<ch_vec<ch_vec<ch_bool, Cfg::num_input_ports>, NUM_TILES_X>, NUM_TILES_Y> creditOut_t;

  TestBench() {
    ch_toVerilog("router.v", device_);
    tracer_ = ch_tracer(device_);
    status_ = 0;
  }

  bool run() {
    tracer_.run(std::bind(&TestBench::tick, this, _1));
    tracer_.toText("router.log");
    tracer_.toVCD("router.vcd");
    tracer_.toTestBench("router_tb.v", "router.v");
    tracer_.toVerilator("router_tb.h", "TestBench");
    status_ |= system("iverilog router_tb.v -o router_tb.iv");
    status_ |= system("! vvp router_tb.iv | grep 'ERROR' || false");
    return (0 == status_);
  }

  struct NoC {
    __io (
      __in  (flitIn_t)    flits_in,
      __in  (creditIn_t)  credits_in,
      __out (flitOut_t)   flits_out,
      __out (creditOut_t) credits_out
    );

    void describe() {
      ch_vec<router_t::flit_t, Cfg::num_output_ports> flit_links[NUM_TILES_Y][NUM_TILES_X];
      ch_vec<ch_bool, Cfg::num_input_ports> credit_links[NUM_TILES_Y][NUM_TILES_X];

      //--
      for (int j = 0; j < NUM_TILES_Y; ++j) {
        for (int i = 0; i < NUM_TILES_X; ++i) {
          // router
          ch_module<router_t> router(i, j);

          for (uint32_t p = 0; p < Cfg::num_output_ports; ++p) {
            flit_links[j][i][p] = router.io.out_ports[p].flit;
          }
          for (uint32_t p = 0; p < Cfg::num_input_ports; ++p) {
            credit_links[j][i][p] = router.io.in_ports[p].credit;
          }

          // Local
          router.io.in_ports[Direction::Local].flit = io.flits_in[j][i];
          router.io.out_ports[Direction::Local].credit = io.credits_in[j][i];

          // East
          if (i < (NUM_TILES_X-1)) {
            router.io.in_ports[Direction::East].flit = flit_links[j][i+1][Direction::West];
            router.io.out_ports[Direction::East].credit = credit_links[j][i+1][Direction::West];
          } else {
            router.io.in_ports[Direction::East].flit.as_bit() = 0;
            router.io.out_ports[Direction::East].credit = 0;
          }

          // South
          if (j > 0) {
            router.io.in_ports[Direction::South].flit = flit_links[j-1][i][Direction::North];
            router.io.out_ports[Direction::South].credit = credit_links[j-1][i][Direction::North];
          } else {
            router.io.in_ports[Direction::South].flit.as_bit() = 0;
            router.io.out_ports[Direction::South].credit = 0;
          }

          // West
          if (i > 0){
            router.io.in_ports[Direction::West].flit = flit_links[j][i-1][Direction::East];
            router.io.out_ports[Direction::West].credit = credit_links[j][i-1][Direction::East];
          } else {
            router.io.in_ports[Direction::West].flit.as_bit() = 0;
            router.io.out_ports[Direction::West].credit = 0;
          }

          // North
          if (j < (NUM_TILES_Y-1)){
            router.io.in_ports[Direction::North].flit = flit_links[j+1][i][Direction::South];
            router.io.out_ports[Direction::North].credit = credit_links[j+1][i][Direction::South];
          } else {
            router.io.in_ports[Direction::North].flit.as_bit() = 0;
            router.io.out_ports[Direction::North].credit  = 0;
          }

          // outputs
          for (uint32_t p = 0; p < Cfg::num_output_ports; ++p) {
            io.flits_out[j][i][p] = router.io.out_ports[p].flit;
          }
          for (uint32_t p = 0; p < Cfg::num_input_ports; ++p) {
            io.credits_out[j][i][p] = router.io.in_ports[p].credit;
          }
        }
      }
    }
  };

  bool tick(ch_tick t) {
    switch (t) {
    case 0:
      // initialize the local input of each router
      for (int j = 0; j < NUM_TILES_Y; ++j) {
        for(int i = 0; i < NUM_TILES_X; ++i) {
           device_.io.flits_in[j][i].as_scbit() = 0x0;
           device_.io.credits_in[j][i] = 0x1; // assume attached PE can always receive flits
        }
      }
      break;
    case 8:
      // PE on router (0,0) injects a new packet for router (1,1)
      device_.io.flits_in[0][0].valid = true;
      device_.io.flits_in[0][0].data.dest_pos.x = 0x1;
      device_.io.flits_in[0][0].data.dest_pos.y = 0x1;
      break;
    case 10:
      status_ |= !device_.io.flits_out[0][0][Direction::East].valid; // flit exits router(0,0) East port
      assert(0 == status_);
      device_.io.flits_in[0][0].as_scbit() = 0x0;
      break;
    case 12:
      status_ |= !device_.io.flits_out[0][1][Direction::North].valid; // flit exits router(1,0) North port
      assert(0 == status_);
      break;
    case 14:
      status_ |= !device_.io.flits_out[1][1][Direction::Local].valid; // flit exits router(1,1) Local port
      assert(0 == status_);
      break;
    }
    return (t <= 20);
  }

private:

  ch_device<NoC> device_;
  ch_tracer tracer_;
  int status_;
};

TEST_CASE("router", "[router]") {
  SECTION("basic", "[basic]") {
    TESTX([]()->bool {
      TestBench testbench;
      return testbench.run();
    });
  }
}
