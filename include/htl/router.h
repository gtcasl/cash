#pragma once

#include "queue.h"
#include "onehot.h"
#include "mux.h"
#include "xbar.h"
#include "arbiter.h"

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

  __struct (Type, (
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
          unsigned BufferSize,
          typename FlitType,
          typename Routing = DefaultRouting<FlitType>>
struct RouterConfig {
  static_assert(NumInPorts * NumOutPorts > 1, "invalid ports size");
  static constexpr unsigned num_input_ports  = NumInPorts;
  static constexpr unsigned num_output_ports = NumOutPorts;
  static constexpr unsigned buffer_size      = BufferSize;
  using flit_type = FlitType;
  using routing_function = Routing;
};

template <typename Cfg>
class Router {
public:
  using flit_t = ch_valid_t<typename Cfg::flit_type>;

  __interface (port_io, (
    __in  (flit_t)  flit,
    __out (ch_bool) credit
  ));

  __io (
    (ch_vec<port_io, Cfg::num_input_ports>) in_ports,
    (ch_vec<ch_flip_io<port_io>, Cfg::num_output_ports>) out_ports
  );

  Router(unsigned x, unsigned y) : x_(x), y_(y) {}

  void describe() {
    using bits_in_t  = ch_bit<Cfg::num_input_ports>;
    using bits_out_t = ch_bit<Cfg::num_output_ports>;

    // input buffers    
    ch_vec<ch_module<ch_queue<typename Cfg::flit_type, Cfg::buffer_size>>,
               Cfg::num_input_ports> buffers;
    ch_vec<flit_t, Cfg::num_input_ports> fifo_out;
    bits_in_t fifo_out_ready;
    bits_in_t fifo_in_ready;
    for (unsigned i = 0; i < Cfg::num_input_ports; ++i) {
      buffers[i].io.enq.data  = io.in_ports[i].flit.data;
      buffers[i].io.enq.valid = io.in_ports[i].flit.valid;
      buffers[i].io.deq.ready = fifo_out_ready[i];
      fifo_in_ready[i]  = buffers[i].io.enq.ready;
      fifo_out[i].data  = buffers[i].io.deq.data;
      fifo_out[i].valid = buffers[i].io.deq.valid;
    }

    // routing logic
    typename Cfg::routing_function routing;
    ch_vec<ch_uint<log2up(Cfg::num_output_ports)>, Cfg::num_input_ports> out_port_id;
    for(unsigned i = 0; i < Cfg::num_input_ports; ++i) {
      out_port_id[i] = routing(fifo_out[i].data, i, x_, y_);
    }

    // switch allocation request input
    ch_vec<bits_out_t, Cfg::num_input_ports> sa_req_input;
    for (unsigned i = 0; i < Cfg::num_input_ports; ++i) {
      sa_req_input[i] = ch_sel(
            fifo_out[i].valid,
            (ch_bit<ch_width_v<bits_out_t>>(1) << out_port_id[i]),
            0x0);
    }

    // switch allocation request
    ch_vec<bits_in_t, Cfg::num_output_ports> sa_req;
    for (unsigned i = 0; i < Cfg::num_output_ports; ++i) {
      for (unsigned j = 0; j < Cfg::num_input_ports; ++j) {
        sa_req[i][j] = ch_sel(io.out_ports[i].credit, sa_req_input[j][i], 0x0);
      }
    }

    // switch allocation response
    ch_vec<ch_module<ch_matArbiter<Cfg::num_input_ports>>, Cfg::num_output_ports> arbiter;
    ch_vec<bits_in_t, Cfg::num_output_ports> sa_resp;
    for (unsigned j = 0; j < Cfg::num_output_ports; ++j) {
      arbiter[j].io.in = sa_req[j];
      sa_resp[j] = arbiter[j].io.grant;
    }

    // input port responses
    ch_vec<bits_out_t, Cfg::num_input_ports> sa_resp_input;
    for (unsigned i = 0; i < Cfg::num_input_ports; ++i) {
      for (unsigned j = 0; j < Cfg::num_output_ports; ++j) {
        sa_resp_input[i][j] = sa_resp[j][i];
      }
    }

    // can read next flit from the FIFO
    for (unsigned i = 0; i < Cfg::num_input_ports; ++i) {
      fifo_out_ready[i] = ch_orr(sa_req_input[i] & sa_resp_input[i]);
    }

    // crossbar
    ch_module<ch_hxbar<flit_t, Cfg::num_input_ports, Cfg::num_output_ports>> xbar;
    xbar.io.sel = sa_resp.as_bit();
    xbar.io.in = fifo_out;

    // outgoing flit
    for (unsigned j = 0; j < Cfg::num_output_ports; ++j) {
      io.out_ports[j].flit = xbar.io.out[j];
    }

    // outgoing credit
    for (unsigned i = 0; i < Cfg::num_input_ports; ++i) {
      io.in_ports[i].credit = fifo_in_ready[i];
    }

    /*__if (ch_clock()) {
      ch_print(stringf("{}: router%d.%d: io.in_ports.flit={}", x_, y_), ch_now(), io.in_ports[0].flit.valid);
      for (unsigned i = 1; i < Cfg::num_input_ports; ++i) {
        ch_print("-{}", io.in_ports[i].flit.valid);
      }
      ch_print("\n");

      ch_print(stringf("{}: router%d.%d: fifo_out_val={}", x_, y_), ch_now(), fifo_out[0].valid);
      for (unsigned i = 1; i < Cfg::num_input_ports; ++i) {
        ch_print("-{}", fifo_out[i].valid);
      }
      ch_print("\n");

      ch_print(stringf("{}: router%d.%d: out_port_id={}", x_, y_), ch_now(), out_port_id[0]);
      for(unsigned i = 1; i < Cfg::num_input_ports; ++i) {
        ch_print("-{}", out_port_id[i]);
      }
      ch_print("\n");

      ch_print(stringf("{}: router%d.%d: sa_req={}", x_, y_), ch_now(), sa_req[0]);
      for (unsigned j = 0; j < Cfg::num_output_ports; ++j) {
        ch_print("-{}", sa_req[j]);
      }
      ch_print("\n");

      ch_print(stringf("{}: router%d.%d: sa_resp={}", x_, y_), ch_now(), sa_resp[0]);
      for (unsigned j = 1; j < Cfg::num_output_ports; ++j) {
        ch_print("-{}", sa_resp[j]);
      }
      ch_print("\n");

      ch_print(stringf("{}: router%d.%d: io.out_ports.flit={}", x_, y_), ch_now(), io.out_ports[0].flit.valid);
      for (unsigned j = 1; j < Cfg::num_output_ports; ++j) {
        ch_print("-{}", io.out_ports[j].flit.valid);
      }
      ch_print("\n");
    };*/
  }

protected:

  unsigned x_;
  unsigned y_;
};

}
}
}
