[![Linux Build Status](https://travis-ci.org/gtcasl/cash.png?branch=master)](https://travis-ci.org/gtcasl/cash) 
[![codecov.io](http://codecov.io/github/gtcasl/cash/coverage.svg?branch=master)](http://codecov.io/github/gtcasl/cash?branch=master)

# Cash

Cash is a C++ embedded domain specific library (EDSL) for hardware design and simulation. It uses template metaprogramming and macro-based reflection to extend the C++ language with hardware specific constructs. Cash enables developpers to describe and simulate their hardware modules from a single source program, leveraging the large C++ ecosystem.

The library documentation is available at:
https://gtcasl.github.io/cash/

Dependencies
------------
Cash requires a C++17 compiler to build and works best with clang 9.0 to leverage its custom plugin for code reflection.

Other dependencies include:

  - [LLVM] (https://www.llvm.org)
  - [LIBJIT] (https://www.gnu.org/software/libjit)
  - [Catch] (https://github.com/catchorg/Catch2)
  - [iVerilog] (http://iverilog.icarus.com)

Default Build Instructions (Ubuntu 18.04)
------------------------------------------

Build essentials Install:
    
    $ sudo build-essential zlib1g-dev

IVerilog Install:

    $ sudo apt-get install iverilog
    
Clang 9.0 Install:

    $ sudo apt-get install clang-9 libclang-9-dev

To install Cash you must clone the repository and create a build directory:

    $ git clone https://github.com/gtcasl/cash.git && cd cash
    $ mkdir build && cd build

Then run cmake to generate the makefile:

    $ cmake -DJIT=LLVM ..

Build and install Cash on your system:

    $ make -j`nproc` all
    $ sudo make install
    
Test your installation

    $ make test
        
That's all!

Alternative build using LIBJIT compiler
---------------------------------------

Install LIBJIT dependencies:
  
    $ sudo apt-get install libtool autoconf flex bison texinfo
  
Build and install LIBJIT:
  
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
  
Build and install Cash using 'JIT=LIBJIT' configuration option:
  
    $ mkdir build_lj && cd build_lj
    $ cmake .. -DJIT=LIBJIT
    $ make -j`nproc` all
    $ sudo make install

Using the Cash library
----------------------
You must link the Cash library from its install location to your project

    libcash.so

Example
-------
A generic adder.

```C++
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
Contributing
------------
Contributions are welcome, just email me at blaise.tine@gmail.com.

License
-------
Release under the BSD license, see LICENSE for details.
