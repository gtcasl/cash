#pragma once

#include <cstdint>
#include <vector>

namespace ch {
namespace internal {

struct range_t {
  uint32_t start;
  uint32_t end;

  range_t(uint32_t end) : start(0), end(end) {}

  range_t(uint32_t start, uint32_t end) : start(start), end(end) {}

  auto overlaps(const range_t& other) const {
    return (other.start < this->end) && (this->start < other.end);
  }

  friend auto operator&(const range_t& lhs, const range_t& rhs) {
    if (!lhs.overlaps(rhs))
      return range_t(0, 0);
    if (rhs.start <= lhs.start && rhs.end >= lhs.end) {
      // rhs fully overlaps lhs
      return lhs;
    }
    if (rhs.start < lhs.start) {
      // rhs overlaps on the left
      return range_t(lhs.start, rhs.end);
    }
    if (rhs.end > lhs.end) {
      // rhs overlaps on the right
      return range_t(rhs.start, lhs.end);
    }
    // rhs fully included
    return rhs;
  }

  auto operator+(uint32_t offset) const {
    range_t ret(*this);
    ret += offset;
    return ret;
  }

  auto operator-(uint32_t offset) const {
    range_t ret(*this);
    ret -= offset;
    return ret;
  }

  range_t& operator+=(uint32_t offset) {
    this->start += offset;
    this->end += offset;
    return *this;
  }

  range_t& operator-=(uint32_t offset) {
    this->start -= offset;
    this->end -= offset;
    return *this;
  }

  bool operator==(const range_t& other) const {
    return (this->start == other.start) && (this->end == other.end);
  }

  bool operator!=(const range_t& other) const {
    return !this->operator==(other);
  }

  auto empty() const {
    return (start == end);
  }
};

struct interval_t {
  std::vector<range_t> ranges;

  interval_t() {}

  interval_t(uint32_t end) {
    this->ranges.emplace_back(end);
  }

  interval_t(uint32_t start, uint32_t end) {
    this->ranges.emplace_back(start, end);
  }

  interval_t(const range_t& range) {
    this->ranges.emplace_back(range.start, range.end);
  }

  auto operator&(const range_t& other) const {
    interval_t ret;
    for (auto& r : this->ranges) {
      auto s = r & other;
      if (s.empty())
        continue;
      ret.ranges.push_back(s);
    }
    return ret;
  }

  auto operator&(const interval_t& other) const {
    interval_t ret;
    for (auto& sr : other.ranges) {
      for (auto& dr : this->ranges) {
        auto s = sr & dr;
        if (s.empty())
          continue;
        ret.ranges.push_back(s);
      }
    }
    return ret;
  }

  auto operator+(uint32_t offset) const {
    auto ret(*this);
    ret += offset;
    return ret;
  }

  auto operator-(uint32_t offset) const {
    auto ret(*this);
    ret -= offset;
    return ret;
  }

  interval_t& operator+=(const range_t& other) {
    if (this->ranges.empty()
     || (this->ranges.front().start >= other.end)) {
      // no overlap on the left
      this->ranges.insert(this->ranges.begin(), other);
      return *this;
    } else if (this->ranges.back().end <= other.start) {
      // no overlap on the right
      this->ranges.insert(this->ranges.end(), other);
      return *this;
    }

    //
    // the interval overlaps with range
    //
    bool insert = false;
    range_t src = other;
    auto it = this->ranges.begin();
    for (; it != this->ranges.end();) {
      if (it->start >= other.end) {
        insert = true;
        break;
      }

      if (!it->overlaps(src)) {
        ++it;
        continue;
      }

      insert = true;
      if (src.start == it->start && src.end == it->end) {
        // exact match, return
        insert = false;
        break;
      } else if (src.start <= it->start && src.end >= it->end) {
        // source fully overlaps, remove range
        it = this->ranges.erase(it);
      } else if (src.start < it->start) {
        // source overlaps on the left, extend source right
        src.end = it->end;
        it = this->ranges.erase(it);
      } else if (src.end > it->end) {
        // source overlaps on the right, extend source left
        src.start = it->start;
        it = this->ranges.erase(it);
      } else {
        // source fully included, return
        insert = false;
        break;
      }
    }

    if (insert) {
      this->ranges.insert(it, src);
    }

    return *this;
  }

  interval_t& operator-=(const range_t& other) {
    for (auto it = ranges.begin(); it != this->ranges.end();) {
      // do ranges overlap?
      if (!it->overlaps(other)) {
        ++it;
        continue;
      }

      if (other.start <= it->start && other.end >= it->end) {
        // source fully overlaps, remove range
        it = this->ranges.erase(it);
      } else if (other.start < it->start) {
        // source overlaps on the left, shrink range on the left
        it->start = other.end;
        it = this->ranges.erase(it);
      } else if (other.end > it->end) {
        // source overlaps on the right, shrink range on the right
        it->end = other.start;
        it = this->ranges.erase(it);
      } else {
        // source fully included, split range
        if (it->start == other.start) {
          it->start = other.end;
        } else {
          range_t right(other.end, it->end);
          it->end = other.start;
          if (!right.empty()) {
            this->ranges.insert(++it, right);
          }
        }
        break;
      }
    }

    return *this;
  }

  interval_t& operator&=(const range_t& other) {
    *this = this->operator&(other);
    return *this;
  }

  interval_t& operator&=(const interval_t& other) {
    *this = this->operator&(other);
    return *this;
  }

  interval_t& operator+=(const interval_t& other) {
    for (auto& range : other.ranges) {
      this->operator+=(range);
    }
    return *this;
  }

  auto operator+(const interval_t& other) const {
    auto ret(*this);
    ret.operator+=(other);
    return ret;
  }

  auto operator-(const interval_t& other) const {
    auto ret(*this);
    ret.operator-=(other);
    return ret;
  }

  interval_t& operator-=(const interval_t& other) {
    for (auto& range : other.ranges) {
      this->operator-=(range);
    }
    return *this;
  }

  interval_t& operator+=(uint32_t offset) {
    for (auto& range : this->ranges) {
      range += offset;
    }
    return *this;
  }

  interval_t& operator-=(uint32_t offset) {
    for (auto& range : this->ranges) {
      range -= offset;
    }
    return *this;
  }

  bool operator==(const interval_t& other) const {
    if (this->ranges.size() != other.ranges.size())
      return false;
    for (size_t i = 0; i < this->ranges.size(); ++i) {
      if (this->ranges[i] != other.ranges[i])
        return false;
    }
    return true;
  }

  bool operator!=(const interval_t& other) const {
    return !this->operator==(other);
  }

  auto empty() const {
    return ranges.empty();
  }
};

}
}