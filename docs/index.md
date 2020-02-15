---
layout: default
---

# What's Cash?

Cash is a C++ embedded domain specific library (EDSL) for hardware design and simulation. 
It uses template metaprogramming and macro-based reflection to extend the C++ language with hardware specific constructs. 
Cash enables developpers to describe and simulate their hardware designs in a single source program, leveraging the large ecosystem of C++ development tools and libraries.

# Requirements

Cash requires a C++17 compiler to build and works best with clang 9.0 to leverage its custom plugin for code reflection.

Other dependencies include:

  - [LLVM](https://www.llvm.org)
  - [LIBJIT](https://www.gnu.org/software/libjit)
  - [iVerilog](http://iverilog.icarus.com)
  - [Catch](https://github.com/catchorg/Catch2)

# Build Status

[![Linux Build Status](https://travis-ci.org/gtcasl/cash.png?branch=master)](https://travis-ci.org/gtcasl/cash) 
[![codecov.io](http://codecov.io/github/gtcasl/cash/coverage.svg?branch=master)](http://codecov.io/github/gtcasl/cash?branch=master)

# System Setup

**Ubuntu 18.04 (Bionic)**

Install Build Essentials:
```shell    
$ sudo build-essential zlib1g-dev
```    
Install IVerilog:
```shell
$ sudo apt-get install iverilog
```    
Install LLVM 9.0:
```shell
$ sudo apt-get install clang-9 libclang-9-dev
```
# Installation

To install Cash you must clone the repository and create a build directory:
```shell
$ git clone https://github.com/gtcasl/cash.git && cd cash
$ mkdir build && cd build
```
Then use run cmake to generate the makefile and export the package informations:
```shell
$ cmake ..
```
Build and install Cash on your system:
```shell
$ make -j`nproc` all
$ sudo make install
```
Test your build
```shell
$ make test
```

**Alternative Installation using LIBJIT Compiler**

Install LIBJIT dependencies:
```shell  
$ sudo apt-get install libtool autoconf flex bison texinfo
```  
Build and install LIBJIT:
```shell  
$ git clone https://git.savannah.gnu.org/git/libjit.git  
$ pushd libjit
$ ./bootstrap
$ mkdir build
$ pushd build
$ ../configure --with-pic
$ make -j`nproc` all
$ sudo make install
$ popd
$ popd
```  
Build and install Cash using 'JIT=LIBJIT' configuration option:
```shell  
$ mkdir build && cd build
$ cmake .. -DJIT=LIBJIT
$ make -j`nproc` all
$ sudo make install
```
# QuickStart Example

#### Implementing a Generic Adder using Cash.

1. Create demo folder
```shell
$ mkdir demo
$ cd demo
```
2. Copy Makefile template
```shell
$ cp /path_to_project/scripts/Makefile .
```
3. Create a file 'demo.cpp' that contains the code listing below.

```cpp
#include <cash/core.h>
using namespace ch::core;

// hardware description
template <unsigned N>
struct Adder {
  __io (
    __in (ch_uint<N>)  lhs,
    __in (ch_uint<N>)  rhs,
    __out (ch_uint<N>) out
  );

  void describe() {
    io.out = io.lhs + io.rhs;
  }
};

int main() {
  // instantiate a 4-bit adder
  ch_device<Adder<4>> my_adder;

  // assign input values
  my_adder.io.lhs = 1;
  my_adder.io.rhs = 3;

  // run simulation
  ch_simulator sim(my_adder);
  sim.run();
  
  // get result
  std::cout << "result = "  << my_adder.io.out << std::endl;

  return 0;
}
```

4. Build the Adder program
```shell
    $ make
```
5. Run the program
```shell
    $ demo.out
```
# Documentation

### Data Types

### Built-in Operators

### Control Flow

### Sequential Logic

### User-Defined Function

### High-Level Synthesis

### Simulation

### HDL Codegen

### Examples

### Test Suite

Cash documentation can be found in the [wiki](https://github.com/gtcasl/cash/wiki).

# Contributions

Contributions are welcome, just email me at blaise.tine@gmail.com.

# License

Release under the BSD license, see LICENSE for details.
