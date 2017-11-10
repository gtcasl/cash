#CXX = clang-3.8
#CXXFLAGS += -std=c++17 -O2 -DNDEBUG
CXXFLAGS += -std=c++17 -O0 -g -fmax-errors=5
LDFLAGS += -lcash

SRCS = adder.cpp counter.cpp fastmult.cpp fifo.cpp gcd.cpp

PROJECTS = $(SRCS:.cpp=.out)
PROJECTS_NAMES = $(SRCS:.cpp=)

all: $(PROJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.out: %.o
	$(CXX) $^ $(LDFLAGS) -o $@

.depend: $(SRCS)
	$(CXX) $(CXXFLAGS) -MM $^ > .depend;

clean:
	rm -f *.out *.o *.vcd *.iv .depend *~ *\#

run: $(PROJECTS)
	$(foreach proj, $(PROJECTS), ./$(proj) || exit;)
	$(foreach proj, $(PROJECTS_NAMES), iverilog $(proj)_tb.v -I $(CASH_PATH)/verilog -o $(proj)_tb.iv || exit;)
	$(foreach proj, $(PROJECTS_NAMES), vvp $(proj)_tb.iv || exit;)

ifneq ($(MAKECMDGOALS),clean)
    -include .depend
endif
