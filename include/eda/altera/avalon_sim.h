#include <vector>
#include <list>
#include <memory>
#include <optional>
#include <random>
#include "avalon.h"

namespace eda {
namespace altera {
namespace avalon {

using namespace ch::logic;
using namespace ch::system;
using namespace ch::literals;

class avm_slave_driver_impl;

class avm_slave_driver_base {
public:

  virtual ~avm_slave_driver_base();

  void flush();

protected:

  struct status_t {
    uint32_t wait_mask;
    uint32_t rsp_channel;
    const uint8_t* rsp_wdata;
  };

  struct request_t {
    bool write;
    sdata_type wdata;
    uint64_t address;
    uint64_t byteenable;
    uint32_t burstcount;
  };

  avm_slave_driver_base(uint32_t num_ports,
                        uint32_t data_size,
                        uint32_t max_burst_size,
                        uint32_t reqs_queue_size,
                        uint32_t latency);

  status_t tick(uint32_t reqs_mask);

  void bind(uint32_t channel, const void* buffer, uint32_t size);

  virtual request_t get_request_info(uint32_t channel) = 0;

  avm_slave_driver_impl* impl_;
  friend class avm_slave_driver_impl;
};

template <typename AVM>
class avm_slave_driver : public avm_slave_driver_base {
public:
  using base = avm_slave_driver_base;
  using io_type = ch_flip_io<ch_system_io<avalon_mm_io<AVM>>>;

  avm_slave_driver(uint32_t num_ports, uint32_t reqs_queue_size, uint32_t latency)
    : avm_slave_driver_base(num_ports, 
                            AVM::DataW / 8,
                            (1 << (AVM::BurstW-1)),
                            reqs_queue_size,
                            latency)
    , ports_(num_ports)
  {}

  void bind(uint32_t channel, const io_type& io) {
    CH_CHECK(channel < ports_.size(), "invalid port index");
    auto port = std::make_unique<io_type>(io);    
    // reset output signals
    port->waitrequest = false;
    port->readdatavalid = false;
    port->writeack = false;   
    // add to list
    ports_[channel] = std::move(port);
  }

  void bind(uint32_t channel, const void* buffer, uint32_t size) {
    CH_CHECK(channel < ports_.size(), "invalid port index");
    base::bind(channel, buffer, size);
  }

  void bind(uint32_t channel, const io_type& io, const void* buffer, uint32_t size) {
    this->bind(channel, io);
    this->bind(channel, buffer, size);
  }

  void tick() {
    // get requests status
    uint32_t reqs_mask = 0;
    for (uint32_t i = 0; i < ports_.size(); ++i) {
      auto& port = ports_[i];
      auto read  = static_cast<uint32_t>(port->read);
      auto write = static_cast<uint32_t>(port->write);
      assert(!(read && write));
      reqs_mask |= ((read | write) << i);
    }

    // process tick event
    auto status = avm_slave_driver_base::tick(reqs_mask);

    // process responses
    for (unsigned i = 0; i < ports_.size(); ++i) {
      auto& port = ports_[i];
      port->readdatavalid = false;
      port->writeack = false;
      if (i == status.rsp_channel) {
        if (status.rsp_wdata) {
          ch_write(port->readdata, 0, status.rsp_wdata, 0, ch_width_v<decltype(port->readdata)>);
          port->readdatavalid = true;
        } else {
          port->writeack = true;
        }
      }
      port->waitrequest = (status.wait_mask >> i) & 0x1;
    }
  }

protected:

  request_t get_request_info(uint32_t channel) override {
    assert(channel < ports_.size());
    auto& port = ports_[channel];
    return request_t{static_cast<bool>(port->write),
                     static_cast<sdata_type>(port->writedata),
                     static_cast<uint64_t>(port->address),
                     static_cast<uint64_t>(port->byteenable),
                     static_cast<uint32_t>(port->burstcount)};
  }

  std::vector<std::unique_ptr<io_type>> ports_;
};

}
}
}
