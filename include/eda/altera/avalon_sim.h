#include <vector>
#include <list>
#include <memory>
#include <optional>
#include <random>
#include <eda/altera/avalon.h>

namespace eda {
namespace altera {
namespace avalon {

using namespace ch::sim;
using namespace ch::literals;
using namespace ch::utility;

class avm_slave_driver_impl {
protected:

  struct rd_rsp_t {
    uint32_t master;
    bitvector data;
  };

  struct wr_rsp_t {
    uint32_t master;
  };

  struct rd_req_t {
    uint32_t master;
    uint64_t address;
    uint64_t bytemask;
    uint64_t req_time;
    uint64_t rsp_time;
  };

  struct wr_req_t {
    uint32_t master;
    uint64_t address;
    bitvector data;
    uint64_t bytemask;
    uint64_t req_time;
    uint64_t rsp_time;
  };

  std::default_random_engine rand_gen_;
  std::vector<std::pair<uint8_t*, uint32_t>> buffers_;
  std::list<rd_req_t> rd_reqs_;
  std::list<wr_req_t> wr_reqs_;
  uint32_t data_width_;
  uint32_t arb_idx_;
  uint32_t max_rd_reqs_;
  uint32_t max_wr_reqs_;
  uint32_t rd_latency_;
  uint32_t wr_latency_;
  uint32_t active_masters_;
  uint64_t last_rsp_time_;
  uint32_t burst_wr_cntr_;

  bool process_rd_req(uint64_t t,
                      uint32_t master,
                      uint64_t address,
                      uint64_t bytemask,
                      uint32_t burstsize);

  bool process_wr_req(uint64_t t,
                      uint32_t master,
                      const bitvector& data,
                      uint64_t address,
                      uint64_t bytemask,
                      uint32_t burstsize);

  std::optional<rd_rsp_t> process_rd_rsp(uint64_t t);

  std::optional<wr_rsp_t> process_wr_rsp(uint64_t t);

  bool arbitration(uint32_t master);

  bool ramdom_stall(uint64_t time);

  uint64_t calc_response_time(uint64_t rsp_time);

protected:

  avm_slave_driver_impl(uint32_t data_width,
                        uint32_t max_rd_reqs,
                        uint32_t max_wr_reqs,
                        uint32_t rd_latency,
                        uint32_t wr_latency);

public:

  void bind(uint32_t master, const void* buffer, uint32_t size);

  void flush();
};

template <typename AVM>
class avm_slave_driver : public avm_slave_driver_impl {
public:
  using io_type = ch_scalar_io<avalon_mm_io<AVM>>;

  avm_slave_driver(uint32_t max_rd_reqs,
                   uint32_t max_wr_reqs,
                   uint32_t rd_latency,
                   uint32_t wr_latency)
    : avm_slave_driver_impl(AVM::DataW,
                            max_rd_reqs,
                            max_wr_reqs,
                            rd_latency,
                            wr_latency)
  {}

  void connect(const io_type& io) {
    masters_.emplace_back(new io_type(io));
    buffers_.resize(++active_masters_);
  }

  void tick(ch_tick t) {
    // default output signals
    for (auto& master : masters_) {
      master->waitrequest   = false;
      master->readdatavalid = false;
      master->writeack      = false;
    }

    // process read responses
    if (!rd_reqs_.empty()) {
      auto ret = this->process_rd_rsp(t);
      if (ret) {
        auto& master = masters_.at(ret->master);
        master->readdatavalid = true;
        master->readdata.write(0, ret->data.data(), ret->data.num_bytes(), 0, data_width_);
      }
    }

    // process write responses
    if (!wr_reqs_.empty()) {
      auto ret = this->process_wr_rsp(t);
      if (ret) {
        auto& master = masters_.at(ret->master);
        master->writeack = true;
      }
    }

    // process requests
    for (unsigned i = 0; i < masters_.size(); ++i) {
      auto& master = masters_[i];
      if (master->read) {
        if (!this->process_rd_req(t,
                                  i,
                                  (uint64_t)master->address,
                                  (uint64_t)master->byteenable,
                                  (uint32_t)master->burstcount)) {
          master->waitrequest = true;
        }
      } else
      if (master->write) {
        if (!this->process_wr_req(t,
                                  i,
                                  (bitvector)master->writedata,
                                  (uint64_t)master->address,
                                  (uint64_t)master->byteenable,
                                  (uint32_t)master->burstcount)) {
          master->waitrequest = true;
        }
      }
    }
  }

protected:

  std::vector<std::unique_ptr<io_type>> masters_;
};

}
}
}
