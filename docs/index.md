---
layout: default
---

# What is Cash?

Cash is an embedded domain specific language for describing and simulating hardware in C++.

# Documentation

Cash documentation can be found in the [wiki](https://github.com/gtcasl/cash/wiki).

## Basic Example: A Generic Counter

```cpp
template <unsigned N>
struct Counter {
  __io (
    __out(ch_bit<N>) out
  );

  void describe() {
    ch_seq<ch_bit<N>> out;
    out.next = out + 1;
    io.out = out;
  }
};

int main() {
  ch_device<Counter<4>> my_counter;
  ch_simulator sim(my_counter);
  sim.run();
  std::cout << "result: " << my_counter.io.out << std::endl;
  return 0;
}
```

## Build Instructions

## Requirements

# Build Status

# Contributions

Blaise Tine -- Project initiator and main developer

# License
