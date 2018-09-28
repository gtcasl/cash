#include <random>
#include <eda/altera/avalon_sim.h>

using namespace eda::altera::avalon;

static std::default_random_engine randGen;

avm_slave_driver_impl::avm_slave_driver_impl(uint32_t data_width,
                               uint32_t max_rd_reqs,
                               uint32_t max_wr_reqs,
                               uint32_t rd_latency,
                               uint32_t wr_latency)
  : data_width_(data_width)
  , arb_idx_(0)
  , max_rd_reqs_(max_rd_reqs)
  , max_wr_reqs_(max_wr_reqs)
  , rd_latency_(rd_latency)
  , wr_latency_(wr_latency)
  , active_masters_(0)
  , last_rsp_time_(0)
  , burst_wr_cntr_(0)
{}

void avm_slave_driver_impl::bind(uint32_t master, const void* buffer, uint32_t size) {
  buffers_[master] = std::pair((uint8_t*)buffer, size);
}

void avm_slave_driver_impl::flush() {
  while (!rd_reqs_.empty() || !wr_reqs_.empty()) {
    uint64_t r_time = -1, w_time = -1;
    if (!rd_reqs_.empty()) {
      r_time = rd_reqs_.front().rsp_time;
    }
    if (!wr_reqs_.empty()) {
      w_time = wr_reqs_.front().rsp_time;
    }
    if (r_time < w_time) {
      process_rd_rsp(r_time);
    } else {
      process_wr_rsp(w_time);
    }
  }
}

bool avm_slave_driver_impl::process_rd_req(uint64_t time,
                                    uint32_t master,
                                    uint64_t address,
                                    uint64_t bytemask,
                                    uint32_t burstsize) {
  // check arbitration
  if (!this->arbitration(master))
    return false;

  // check request buffer capacity
  if (rd_reqs_.size() == max_rd_reqs_)
    return false;

  // check random stall
  if (this->ramdom_stall(time))
    return false;

  // submit new request
  assert(burstsize >= 1);
  auto data_size = data_width_ >> 3;
  for (uint32_t i = 0; i < burstsize; ++i) {
    auto rsp_time = this->calc_response_time(time + 2 * rd_latency_);
    rd_req_t req{master, address + i * data_size, bytemask, time, rsp_time};
    rd_reqs_.emplace_back(req);
  }
  return true;
}

bool avm_slave_driver_impl::process_wr_req(uint64_t time,
                                    uint32_t master,
                                    const sdata_type& data,
                                    uint64_t address,
                                    uint64_t bytemask,
                                    uint32_t burstsize) {
  // check arbitration
  if (!this->arbitration(master))
    return false;

  // check request buffer capacity
  assert(burstsize <= max_wr_reqs_);
  if (0 == burst_wr_cntr_ && wr_reqs_.size() > (max_wr_reqs_ - burstsize))
    return false;

  // check random stall
  if (this->ramdom_stall(time))
    return false;

  // submit new request
  assert(burstsize >= 1);
  auto data_size = data_width_ >> 3;
  if (burst_wr_cntr_ != 0) {
    auto rsp_time = this->calc_response_time(time + 2 * wr_latency_);
    const wr_req_t& prev_req = wr_reqs_.back();
    wr_req_t req{master, prev_req.address + data_size, data, bytemask, time, rsp_time};
    wr_reqs_.emplace_back(req);
    --burst_wr_cntr_;
  } else {
    auto rsp_time = this->calc_response_time(time + 2 * wr_latency_);
    wr_req_t req{master, address, data, bytemask, time, rsp_time};
    wr_reqs_.emplace_back(req);
    burst_wr_cntr_ = burstsize - 1;
  }
  return true;
}

std::optional<avm_slave_driver_impl::rd_rsp_t>
avm_slave_driver_impl::process_rd_rsp(uint64_t time) {
  for (auto it = rd_reqs_.begin(), end = rd_reqs_.end(); it != end; ++it) {
    auto& req = *it;
    if (req.rsp_time <= time) {
      rd_rsp_t rsp;
      rsp.master = req.master;
      rsp.data.resize(data_width_);
      rsp.data.write(0, buffers_[req.master].first + req.address, 0, data_width_);
      rd_reqs_.erase(it);
      return std::optional(rsp);
    }
  }
  return {};
}

std::optional<avm_slave_driver_impl::wr_rsp_t>
avm_slave_driver_impl::process_wr_rsp(uint64_t time) {
  auto data_size = data_width_ / 8;
  auto full_mask = (1ull << data_size) - 1;
  for (auto it = wr_reqs_.begin(), end = wr_reqs_.end(); it != end; ++it) {
    auto& req = *it;
    if (req.rsp_time <= time) {
      wr_rsp_t rsp;
      rsp.master = req.master;
      if (full_mask == (req.bytemask & full_mask)) {
        req.data.read(0, buffers_[req.master].first + req.address, 0, data_width_);
      } else {
        for (uint32_t i = 0; i < data_size; ++i) {
          if (0 == (req.bytemask & (1ull << i)))
            continue;
          req.data.read(i*8, buffers_[req.master].first + req.address + i, 0, 8);
        }
      }
      wr_reqs_.erase(it);
      return std::optional(rsp);
    }
  }
  return {};
}

bool avm_slave_driver_impl::ramdom_stall(uint64_t /*time*/) {
  std::uniform_int_distribution<> dist(0, 100);
  return dist(randGen) > 90;
}

bool avm_slave_driver_impl::arbitration(uint32_t master) {
  if (burst_wr_cntr_ != 0) {
    return (master == wr_reqs_.back().master);
  }
  if (arb_idx_ == active_masters_)
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
