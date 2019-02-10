#pragma once

#include <htl/queue.h>
#include <htl/onehot.h>
#include <htl/mux.h>
#include <htl/xbar.h>
#include <htl/arbiter.h>

namespace ch {
namespace htl {
namespace router {

using namespace ch::logic;
using namespace ch::literals;

__enum (Direction, (Local, East, South, West, North));

template <unsigned NumTileX,
          unsigned NumTileY,
          unsigned FlitBits,
          unsigned ParityBits,
          unsigned TimeBits>
struct DefaultFlit {
  static_assert(NumTileX * NumTileY > 1, "invalid tile size");
  using TileId   = ch_uint<log2up(NumTileX * NumTileY)>;
  using FlitTime = ch_uint<TimeBits>;
  using Parity   = ch_uint<ParityBits>;

  __struct (TilePos, (
    (ch_uint<log2up(NumTileX)>) x,
    (ch_uint<log2up(NumTileY)>) y
  ));

  static constexpr int P = FlitBits - 1 - ch_width_v<TileId> - ch_width_v<TilePos> - TimeBits - ParityBits;
  static_assert(P >= 0, "invalid flit size");

  __struct (type, (
    (TileId)    src_id,
    (TilePos)   dest_pos,
    (FlitTime)  gen_time,
    (Parity)    parity,
    (ch_bit<P>) payload
  ));
};

template <typename Flit>
struct DefaultRouting {
  auto operator()(const Flit& flit_in,
                  unsigned port_in,
                  unsigned pos_x,
                  unsigned pos_y) {
    Direction out;
    switch (port_in) {
    case Direction::East:
      out = ch_sel<Direction>
              (flit_in.dest_pos.x < pos_x, Direction::West)
              (flit_in.dest_pos.y > pos_y, Direction::North)
              (flit_in.dest_pos.y < pos_y, Direction::South)
              (Direction::Local);
      break;
    case Direction::South:
      out = ch_sel<Direction>
              (flit_in.dest_pos.y > pos_y, Direction::North)
              (Direction::Local);
      break;
    case Direction::West:
      out = ch_sel<Direction>
              (flit_in.dest_pos.x > pos_x, Direction::East)
              (flit_in.dest_pos.y > pos_y, Direction::North)
              (flit_in.dest_pos.y < pos_y, Direction::South)
              (Direction::Local);
      break;
    case Direction::North:
      out = ch_sel<Direction>
              (flit_in.dest_pos.y < pos_y, Direction::South)
              (Direction::Local);
      break;
    case Direction::Local:
      out = ch_sel<Direction>
              (flit_in.dest_pos.x > pos_x, Direction::East)
              (flit_in.dest_pos.x < pos_x, Direction::West)
              (flit_in.dest_pos.y > pos_y, Direction::North)
              (flit_in.dest_pos.y < pos_y, Direction::South)
              (Direction::Local);
      break;
    default:
      abort();
    }
    return out.as_uint();
  }
};

template <unsigned NumInPorts,
          unsigned NumOutPorts,
          unsigned NumInBufs,
          typename FlitType,
          typename Routing = DefaultRouting<FlitType>>
struct RouterConfig {
  static_assert(NumInPorts * NumOutPorts > 1, "invalid ports size");
  static constexpr unsigned num_input_ports   = NumInPorts;
  static constexpr unsigned num_output_ports  = NumOutPorts;
  static constexpr unsigned num_input_buffers = NumInBufs;
  using flit_type = FlitType;
  using routing_function = Routing;
};

template <typename Cfg>
class Router {
public:
  using FlitData   = typename Cfg::flit_type;
  using Flit       = ch_valid_t<FlitData>;
  using vFlitIn    = ch_vec<Flit, Cfg::num_input_ports>;
  using vFlitOut   = ch_vec<Flit, Cfg::num_output_ports>;
  using vCreditIn  = ch_vec<ch_bool, Cfg::num_output_ports>;
  using vCreditOut = ch_vec<ch_bool, Cfg::num_input_ports>;
  using bits_in_t  = ch_bit<Cfg::num_input_ports>;
  using bits_out_t = ch_bit<Cfg::num_output_ports>;
  using outportid_t= ch_uint<log2up(Cfg::num_output_ports)>;

  __io(
    __in (vFlitIn)     flit_in,
    __in (vCreditIn)   credit_in,
    __out (vFlitOut)   flit_out,
    __out (vCreditOut) credit_out
  );

  Router(unsigned x, unsigned y) : x_(x), y_(y) {}

  void describe() {
    // input buffers
    ch_vec<Flit, Cfg::num_input_ports> fifo_out;
    bits_in_t fifo_out_ready;
    bits_in_t fifo_in_ready;
    for (unsigned i = 0; i < Cfg::num_input_ports; ++i) {
      ch_module<ch_queue<FlitData, Cfg::num_input_buffers>> queue;
      queue.io.enq.data  = io.flit_in[i].data;
      queue.io.enq.valid = io.flit_in[i].valid;
      queue.io.deq.ready = fifo_out_ready[i];
      fifo_in_ready[i]  = queue.io.enq.ready;
      fifo_out[i].data  = queue.io.deq.data;
      fifo_out[i].valid = queue.io.deq.valid;

      ch_tap(io.flit_in[i].valid, stringf("io.flit_in%d.valid", i));
      ch_tap(fifo_in_ready[i], stringf("fifo_in_ready%d", i));
      ch_tap(fifo_out[i].valid, stringf("fifo_out%d.valid", i));
      ch_tap(fifo_out[i].data.dest_pos, stringf("fifo_out%d.dest_pos", i));
      ch_tap(fifo_out_ready[i], stringf("fifo_out_ready%d", i));
    }

    // routing logic
    typename Cfg::routing_function routing;
    ch_vec<outportid_t, Cfg::num_input_ports> output_port_id;
    for(unsigned i = 0; i < Cfg::num_input_ports; ++i) {
      output_port_id[i] = routing(fifo_out[i].data, i, x_, y_);
      ch_tap(output_port_id[i], stringf("output_port_id%d", i));
    }

    // switch allocation request input
    ch_vec<bits_out_t, Cfg::num_input_ports> sa_req_input;
    for (unsigned i = 0; i < Cfg::num_input_ports; ++i) {
      sa_req_input[i] = ch_sel(
            fifo_out[i].valid,
            (ch_bit<ch_width_v<bits_out_t>>(1) << output_port_id[i]),
            0x0);
      ch_tap(sa_req_input[i], stringf("sa_req_input%d", i));
    }

    // switch allocation request
    ch_vec<bits_in_t, Cfg::num_output_ports> sa_req;
    for (unsigned i = 0; i < Cfg::num_output_ports; ++i) {
      for (unsigned j = 0; j < Cfg::num_input_ports; ++j) {
        sa_req[i][j] = ch_sel(io.credit_in[i], sa_req_input[j][i], 0x0);
      }
    }

    // switch allocation response
    ch_vec<bits_in_t, Cfg::num_output_ports> sa_resp;
    for (unsigned i = 0; i < Cfg::num_output_ports; ++i) {
      ch_module<ch_rrArbiter<Cfg::num_input_ports>> arbiter;
      arbiter.io.in = sa_req[i];
      sa_resp[i] = arbiter.io.grant;
      ch_tap(sa_req[i], stringf("sa_req%d", i));
      ch_tap(sa_resp[i], stringf("sa_resp%d", i));
    }

    // input port responses
    ch_vec<bits_out_t, Cfg::num_input_ports> sa_resp_input;
    for (unsigned i = 0; i < Cfg::num_input_ports; ++i) {
      for (unsigned j = 0; j < Cfg::num_output_ports; ++j) {
        sa_resp_input[i][j] = sa_resp[j][i];
      }
      ch_tap(sa_resp_input[i], stringf("sa_resp_input%d", i));
    }

    // can read next flit from the FIFO
    for (unsigned i = 0; i < Cfg::num_input_ports; ++i) {
      fifo_out_ready[i] = ch_orr(sa_req_input[i] & sa_resp_input[i]);
    }

    // crossbar
    ch_module<ch_hxbar<Flit, Cfg::num_input_ports, Cfg::num_output_ports>> xbar;
    xbar.io.sel = sa_resp.as_bit();
    xbar.io.in = fifo_out;

    // outgoing flit
    for (unsigned i = 0; i < Cfg::num_output_ports; ++i) {
      io.flit_out[i] = xbar.io.out[i];
      ch_tap(io.flit_out[i].valid, stringf("io.flit_out%d.valid", i));
    }

    // outgoing credit
    for (unsigned i = 0; i < Cfg::num_input_ports; ++i) {
      io.credit_out[i] = fifo_in_ready[i];
      ch_tap(io.credit_out[i], stringf("io.credit_out%d", i));
    }
  }

protected:

  unsigned x_;
  unsigned y_;
};

}
}
}
