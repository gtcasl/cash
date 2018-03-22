#CXX = clang-5.0
#CXXFLAGS += -std=c++17 -O3 -DNDEBUG -Wall -Wextra -pedantic
CXXFLAGS += -std=c++17 -O0 -g -Wall -Wextra -pedantic -fmax-errors=1
LDFLAGS += -lcash -lstdc++

SRCS = adder.cpp counter.cpp fastmult.cpp fifo.cpp gcd.cpp vending.cpp

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
	rm -f *.out *.o *.vcd *.iv *.fir .depend *~ *\#

run: $(PROJECTS)
	$(foreach proj, $(PROJECTS), ./$(proj) || exit;)
	$(foreach proj, $(PROJECTS_NAMES), iverilog $(proj)_tb.v -g2012 -o $(proj)_tb.iv || exit;)
	$(foreach proj, $(PROJECTS_NAMES), vvp $(proj)_tb.iv || exit;)

ifneq ($(MAKECMDGOALS),clean)
    -include .depend
endif
