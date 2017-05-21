#CXX = clang-3.8
#CXXFLAGS += -std=c++14 -O2 -DNDEBUG
CXXFLAGS += -std=c++14 -O0 -g -fmax-errors=5 -DCASH_DEBUG
LDFLAGS += -lcash

VCS_OPT = -I $(VCS_HOME)/include -full64
VCS_OPT+= -nc -V -debug_all -work work +librescan +v2k
VCS_OPT+= -override_timescale=10ps/10ps -l debug.log
VCS_OPT+= -LDFLAGS="-m64"
VCS_OPT+= +vcs+lic+wait

all: adder.out counter.out fastmul.out fifo.out

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.out: %.o
	$(CXX) $^ $(LDFLAGS) -o $@

iverilog: testbench.v counter.v
	iverilog -o testbench.vvp $^
	vvp testbench.vvp

vcs:    testbench.v counter.v
	vcs $(VCS_OPT) $^
	./simv

view: testbench.vcd
	gtkwave $^ &

clean:
	rm -f *.out *.o *.v *.vcd simv *~ *\#
