#include <eda/altera/avalon_sim.h>

using namespace eda::altera::avalon;

namespace eda {
namespace altera {
namespace avalon {

class avm_slave_driver_impl {
protected:

  struct req_t {
    uint32_t channel;
    bool is_write;
    uint64_t address;
    uint64_t byteenable;
    uint64_t rsp_time;
  };

  struct wr_burst_t {
    uint32_t channel;
    uint32_t counter;
    uint32_t address;
  };

  using rd_rsp_t = std::pair<uint32_t, sdata_type>;
  using wr_rsp_t = uint32_t;

  std::vector<std::pair<uint8_t*, uint32_t>> buffers_;
  std::list<req_t> reqs_;
  std::list<sdata_type> wr_data_;
  avm_slave_driver_base* instance_;
  uint32_t data_size_;
  uint32_t max_burst_size_;
  uint32_t reqs_queue_size_;
  uint32_t latency_;
  uint64_t curr_time_;
  uint32_t arbiter_idx_;
  wr_burst_t wr_burst_;

  bool ramdom_stall() {
    auto sample = rand() / double(RAND_MAX);
    return (sample > 0.7);
  }

  uint32_t arbitration() {
    if (wr_burst_.counter != 0)
      return wr_burst_.channel;
    if (arbiter_idx_ == buffers_.size())
      arbiter_idx_ = 0;
    return arbiter_idx_++;
  }

  void process_request(uint32_t channel) {
    auto req = instance_->get_request_info(channel);
    assert(req.burstcount >= 1);
    assert(req.burstcount <= max_burst_size_);
    auto rsp_time = curr_time_ + latency_;
    if (req.write) {
      if (wr_burst_.counter != 0) {
        assert(wr_burst_.channel == channel);        
        reqs_.push_back({channel, true, wr_burst_.address, req.byteenable, rsp_time});
        wr_burst_.address += data_size_;
        --wr_burst_.counter;
      } else {
        reqs_.push_back({channel, true, req.address, req.byteenable, rsp_time});
        if (req.burstcount > 1) {
          wr_burst_.counter = req.burstcount - 1;
          wr_burst_.channel  = channel;
          wr_burst_.address = req.address + data_size_;
        }
      }
      wr_data_.push_back(req.wdata);
    } else {
      for (uint32_t i = 0; i < req.burstcount; ++i) {
        reqs_.push_back({channel, false, req.address + i * data_size_, req.byteenable, rsp_time});
      }
    }
  }

  std::pair<uint32_t, const uint8_t*> process_responses() {
    uint32_t rsp_channel = -1;
    uint8_t* wdata = nullptr;
    auto full_writemask = (1ull << data_size_) - 1;
    for (auto it = reqs_.begin(), end = reqs_.end(); it != end; ++it) {
      auto& req = *it;
      if (req.rsp_time > curr_time_)
        continue;
      rsp_channel = req.channel;
      auto& buffer = buffers_[rsp_channel];
      if (req.is_write) {
        auto& data = wr_data_.front();
        if (full_writemask == (req.byteenable & full_writemask)) {
          CH_CHECK(req.address + data_size_ <= buffer.second, "out of bound access");
          data.read(0, buffer.first + req.address, 0, data_size_ * 8);
        } else {
          for (uint32_t i = 0; i < data_size_; ++i) {
            if (0 == (req.byteenable & (1ull << i)))
              continue;
            CH_CHECK(req.address + i + 1 <= buffer.second, "out of bound access");
            data.read(i * 8, buffer.first + req.address + i, 0, 8);
          }
        }
        wr_data_.pop_front();
      } else {
        CH_CHECK(req.address + data_size_ <= buffer.second, "out of bound access");
        wdata = buffer.first + req.address;
      }
      reqs_.erase(it);
      break;
    }
    return std::make_pair(rsp_channel, wdata);
  }

public:

  avm_slave_driver_impl(avm_slave_driver_base* instance,
                        uint32_t data_size,
                        uint32_t max_burst_size,
                        uint32_t reqs_queue_size,
                        uint32_t latency)
    : instance_(instance)
    , data_size_(data_size)
    , max_burst_size_(max_burst_size)
    , reqs_queue_size_(reqs_queue_size)
    , latency_(latency)
    , curr_time_(0)
    , arbiter_idx_(0)
    , wr_burst_({}) {
    assert(reqs_queue_size >= 2 * max_burst_size);
  }

  void create_channel() {
    buffers_.resize(buffers_.size() + 1);
  }

  void bind(uint32_t channel, const void* buffer, uint32_t size) {
    buffers_[channel] = std::pair((uint8_t*)buffer, size);
  }

  auto tick(uint32_t reqs_mask) {
    uint32_t rsp_channel = -1;
    const uint8_t* rsp_wdata = nullptr;

    // process pending responses
    if (!reqs_.empty()) {
      std::tie(rsp_channel, rsp_wdata) = this->process_responses();
    }

    // next active channel
    auto active_channel = this->arbitration();
    uint32_t wait_mask = ~(1 << active_channel);

    // check request buffer capacity
    if (reqs_.size() > (reqs_queue_size_ - max_burst_size_))
      wait_mask = -1;

    // random stall
    if (this->ramdom_stall())
      wait_mask = -1;

    // process active request
    if (~wait_mask & reqs_mask) {
      this->process_request(active_channel);
    }

    // advance current time
    ++curr_time_;

    // return status
    return avm_slave_driver_base::status_t{wait_mask, rsp_channel, rsp_wdata};
  }

  void flush() {
    // commit pending responses
    while (!reqs_.empty()) {
      curr_time_ = reqs_.front().rsp_time;
      process_responses();
    }
  }
};

}
}
}

///////////////////////////////////////////////////////////////////////////////

avm_slave_driver_base::avm_slave_driver_base(uint32_t data_size,
                                             uint32_t max_burst_size,
                                             uint32_t reqs_queue_size,
                                             uint32_t latency) {
  impl_ = new avm_slave_driver_impl(
        this, data_size, max_burst_size, reqs_queue_size, latency);
}

avm_slave_driver_base::~avm_slave_driver_base() {
  delete impl_;
}

void avm_slave_driver_base::create_channel() {
  impl_->create_channel();
}

void avm_slave_driver_base::bind(uint32_t channel, const void* buffer, uint32_t size) {
  impl_->bind(channel, buffer, size);
}

avm_slave_driver_base::status_t avm_slave_driver_base::tick(uint32_t reqs_mask) {
  return impl_->tick(reqs_mask);
}

void avm_slave_driver_base::flush() {
  impl_->flush();
}
