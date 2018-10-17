#include <eda/altera/avalon_sim.h>

using namespace eda::altera::avalon;

avm_slave_driver_impl::avm_slave_driver_impl(uint32_t data_size,
                                             uint32_t max_burst_size,
                                             uint32_t reqs_queue_size,
                                             uint32_t rd_latency,
                                             uint32_t wr_latency)
  : data_size_(data_size)
  , max_burst_size_(max_burst_size)
  , reqs_queue_size_(reqs_queue_size)
  , rd_latency_(rd_latency)
  , wr_latency_(wr_latency)
  , arb_idx_(0)
  , last_rsp_time_(0)
  , wr_burst_({}) {
  assert(reqs_queue_size >= 2 * max_burst_size);
}

void avm_slave_driver_impl::bind(uint32_t master, const void* buffer, uint32_t size) {
  buffers_[master] = std::pair((uint8_t*)buffer, size);
}

void avm_slave_driver_impl::flush() {
  while (!reqs_.empty()) {
    process_rsp(reqs_.front().rsp_time);
  }
}

void avm_slave_driver_impl::process_rd_req(uint64_t time,
                                           uint32_t master,
                                           uint64_t address,
                                           uint64_t bytemask,
                                           uint32_t burstsize) {
  assert(burstsize >= 1);
  assert(burstsize <= max_burst_size_);
  for (uint32_t i = 0; i < burstsize; ++i) {
    auto rsp_time = this->calc_response_time(time + 2 * rd_latency_);
    reqs_.push_back({false, master, address + i * data_size_, bytemask, time, rsp_time});
  }
}

void avm_slave_driver_impl::process_wr_req(uint64_t time,
                                           uint32_t master,
                                           const sdata_type& data,
                                           uint64_t address,
                                           uint64_t bytemask,
                                           uint32_t burstsize) {
  assert(burstsize >= 1);
  assert(burstsize <= max_burst_size_);
  if (wr_burst_.counter != 0) {
    assert(wr_burst_.master == master);
    auto rsp_time = this->calc_response_time(time + 2 * wr_latency_);
    reqs_.push_back({true, master, wr_burst_.address, bytemask, time, rsp_time});
    wr_burst_.address += data_size_;
    --wr_burst_.counter;
  } else {
    auto rsp_time = this->calc_response_time(time + 2 * wr_latency_);
    reqs_.push_back({true, master, address, bytemask, time, rsp_time});
    if (burstsize > 1) {
      wr_burst_.counter = burstsize - 1;
      wr_burst_.master  = master;
      wr_burst_.address = address + data_size_;
    }
  }
  wr_data_.push_back(data);
}

std::optional<avm_slave_driver_impl::rsp_t>
avm_slave_driver_impl::process_rsp(uint64_t time) {
  auto full_writemask = (1ull << data_size_) - 1;
  for (auto it = reqs_.begin(), end = reqs_.end(); it != end; ++it) {
    auto& req = *it;
    if (req.rsp_time > time)
      continue;
    uint32_t master = req.master;
    uint8_t* data = nullptr;
    auto& buffer = buffers_[master];
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
      data = buffer.first + req.address;
    }
    reqs_.erase(it);
    return rsp_t{master, data};
  }
  return {};
}

bool avm_slave_driver_impl::check_channel(uint64_t time, uint32_t master) {
  // bus arbitration
  if (!this->arbitration(master))
    return false;

  // check request buffer capacity
  if (reqs_.size() > (reqs_queue_size_ - max_burst_size_))
    return false;

  // random stall
  if (this->ramdom_stall(time))
    return false;

  // write burst priority
  if (wr_burst_.counter != 0) {
    return (master == wr_burst_.master);
  }

  return true;
}

bool avm_slave_driver_impl::ramdom_stall(uint64_t /*time*/) {
  return (std::rand() % 100) > 80;
}

bool avm_slave_driver_impl::arbitration(uint32_t master) {  
  if (arb_idx_ == buffers_.size())
    arb_idx_ = 0;
  return (master == arb_idx_++);
}

uint64_t avm_slave_driver_impl::calc_response_time(uint64_t rsp_time) {
  if (rsp_time <= last_rsp_time_) {
    rsp_time = last_rsp_time_ + 2;
  }
  last_rsp_time_ = rsp_time;
  return rsp_time;
}
