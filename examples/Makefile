#CXX = clang-3.8
#CXXFLAGS += -std=c++14 -O2 -DNDEBUG
CXXFLAGS += -std=c++14 -O0 -g -fmax-errors=5
LDFLAGS += -lcash

SRCS = adder.cpp counter.cpp fastmult.cpp fifo.cpp

PROJECTS = $(SRCS:.cpp=.out)

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

ifneq ($(MAKECMDGOALS),clean)
    -include .depend
endif
