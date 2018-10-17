#include <vector>
#include <list>
#include <memory>
#include <optional>
#include <random>
#include <eda/altera/avalon.h>

namespace eda {
namespace altera {
namespace avalon {

using namespace ch::logic;
using namespace ch::system;
using namespace ch::literals;

class avm_slave_driver_impl {
protected:

  struct req_t {
    bool is_write;
    uint32_t master;
    uint64_t address;
    uint64_t byteenable;
    uint64_t req_time;
    uint64_t rsp_time;
  };

  struct rsp_t {
    uint32_t master;
    uint8_t* data;
  };

  struct wr_burst_t {
    uint32_t counter;
    uint32_t master;
    uint32_t address;
  };

  using rd_rsp_t = std::pair<uint32_t, sdata_type>;
  using wr_rsp_t = uint32_t;

  std::default_random_engine rand_gen_;
  std::vector<std::pair<uint8_t*, uint32_t>> buffers_;
  std::list<req_t> reqs_;
  std::list<sdata_type> wr_data_;
  uint32_t data_size_;
  uint32_t max_burst_size_;
  uint32_t reqs_queue_size_;
  uint32_t rd_latency_;
  uint32_t wr_latency_;
  uint32_t arb_idx_;  
  uint64_t last_rsp_time_;
  wr_burst_t wr_burst_;

  bool check_channel(uint64_t t, uint32_t master);

  void process_rd_req(uint64_t t,
                      uint32_t master,
                      uint64_t address,
                      uint64_t bytemask,
                      uint32_t burstsize);

  void process_wr_req(uint64_t t,
                      uint32_t master,
                      const sdata_type& data,
                      uint64_t address,
                      uint64_t bytemask,
                      uint32_t burstsize);

  std::optional<rsp_t> process_rsp(uint64_t t);

  bool arbitration(uint32_t master);

  bool ramdom_stall(uint64_t time);

  uint64_t calc_response_time(uint64_t rsp_time);

protected:

  avm_slave_driver_impl(uint32_t data_size,
                        uint32_t max_burst_size,
                        uint32_t reqs_queue_size,
                        uint32_t rd_latency,
                        uint32_t wr_latency);

public:

  void bind(uint32_t master, const void* buffer, uint32_t size);

  void flush();
};

template <typename AVM>
class avm_slave_driver : public avm_slave_driver_impl {
public:
  using io_type = ch_system_io<avalon_mm_io<AVM>>;

  avm_slave_driver(uint32_t reqs_queue_size,
                   uint32_t rd_latency,
                   uint32_t wr_latency)
    : avm_slave_driver_impl(AVM::DataW / 8,
                            (1 << (AVM::BurstW-1)),
                            reqs_queue_size,
                            rd_latency,
                            wr_latency)
  {}

  void connect(const io_type& io) {
    auto port = new io_type(io);
    ports_.emplace_back(port);
    buffers_.resize(ports_.size());

    // reset output signals
    port->waitrequest = false;
    port->readdatavalid = false;
    port->writeack = false;
  }

  void tick(ch_tick t) {
    // update output signals
    for (unsigned i = 0; i < ports_.size(); ++i) {
      auto& port = ports_[i];
      port->waitrequest = !this->check_channel(t, i);
      port->readdatavalid = false;
      port->writeack = false;
    }

    // process responses
    if (!reqs_.empty()) {      
      auto rsp = this->process_rsp(t);
      if (rsp) {
        auto& port = ports_.at(rsp->master);
        if (rsp->data) {
          port->readdata.write(0, rsp->data, 0, data_size_ * 8);
          port->readdatavalid = true;
        } else {
          port->writeack = true;
        }
      }
    }

    // process requests
    for (unsigned i = 0; i < ports_.size(); ++i) {
      auto& port = ports_[i];
      if (port->waitrequest)
        continue;
      if (port->read) {
        this->process_rd_req(t,
                             i,
                             (uint64_t)port->address,
                             (uint64_t)port->byteenable,
                             (uint32_t)port->burstcount);
      } else
      if (port->write) {
        this->process_wr_req(t,
                             i,
                             (sdata_type)port->writedata,
                             (uint64_t)port->address,
                             (uint64_t)port->byteenable,
                             (uint32_t)port->burstcount);
      }
    }
  }

protected:

  std::vector<std::unique_ptr<io_type>> ports_;
};

}
}
}
