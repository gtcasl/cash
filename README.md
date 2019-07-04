[![Linux Build Status](https://travis-ci.org/gtcasl/cash.png?branch=master)](https://travis-ci.org/gtcasl/cash) 
[![codecov.io](http://codecov.io/github/gtcasl/cash/coverage.svg?branch=master)](http://codecov.io/github/gtcasl/cash?branch=master)

# Cash

Cash is a C++ embedded domain specific library (EDSL) for hardware design and simulation. It uses template metaprogramming and macro-based reflection to extend the C++ language with hardware specific constructs. Cash enables developpers to describe and simulate their hardware modules from a single source program, leveraging the large C++ ecosystem.

The library documentation is available at:
https://gtcasl.github.io/cash/

Dependencies
------------
Cash requires C++17 compiler to build with support for inline variables.

It has been tested with GCC 7 and Clang 5.

Other dependencies include:

  - [LLVM] (https://www.llvm.org)
  - [LIJIT] (https://www.gnu.org/software/libjit/)
  - [Catch] (https://github.com/catchorg/Catch2)
  - [iVerilog] (http://iverilog.icarus.com/)
  - [lcov] (http://ltp.sourceforge.net/coverage/lcov.php)
  - [binutils-dev] (https://www.gnu.org/software/binutils/)

Default Build Instructions (Ubuntu Trusty)
------------------------------------------

IVerilog Install:

    $ sudo apt-get install iverilog
    
Binutils Install:

    $ sudo apt-get install binutils-dev

GCC 7.1 Install:

    $ sudo add-apt-repository --yes ppa:ubuntu-toolchain-r/test
    $ sudo apt-get update
    $ sudo apt-get install gcc-7 g++-7
    $ sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-7 60 --slave /usr/bin/g++ g++ /usr/bin/g++-7
    
LLVM 8.0 Install:

    $ wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | sudo apt-key add -
    $ sudo apt-add-repository "deb http://apt.llvm.org/trusty/ llvm-toolchain-trusty-8 main"
    $ sudo apt-get update
    $ sudo apt-get install llvm-8-dev

To install Cash you must clone the repository and create a build directory:

    $ git clone https://github.com/gtcasl/cash.git && cd cash
    $ mkdir build && cd build

Then use run cmake to generate the makefile and export the package informations:

    $ cmake .. -DJIT=LLVM

Optionally, you can also install Cash on your system:

    $ make install
    
That's all!

Alternative build using LIBJIT compiler
---------------------------------------

Install LIBJIT dependencies:
  
  $ sudo apt-get install libtool flex bison texinfo
  
Building and Installing LIBJIT:
  
  $ git clone https://git.savannah.gnu.org/git/libjit.git
  $ pushd libjit
  $ git apply ${CASH_HOME}/scripts/libjit.patch
  $ ./bootstrap
  $ mkdir build
  $ pushd build
  $ ../configure --with-pic
  $ make -j8 all
  $ sudo make install
  $ popd
  $ popd
  
Build Cash using the JIT=LIBJIT configuration option
  
  $ mkdir build_lj && cd build_lj
  $ cmake .. -DJIT=LIBJIT

Using the Cash library
----------------------
You must link the Cash library from its install location to your project

    libcash.so

Example
-------
A generic binary adder.

```C++
#include <cash.h>

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
