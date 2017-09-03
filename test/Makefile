CXXFLAGS += -std=c++14 -O0 -g --coverage -fmax-errors=5
LDFLAGS += -lcash

SRCS = main.cpp dogfood.cpp smoke.cpp literals.cpp proxies.cpp aggregates.cpp select.cpp arithm.cpp reg.cpp mem.cpp sim.cpp miscs.cpp float.cpp

OBJS = $(SRCS:.cpp=.o)

PROJECT = test

all: $(PROJECT).out

$(PROJECT).out : $(OBJS)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

.depend: $(SRCS)
	$(CXX) $(CXXFLAGS) -MM $^ > .depend;

view: $(PROJECT).vcd
	gtkwave $^ &

clean:
	rm -f *.out *.o *.v *.vcd *.gcda *.gcno .depend *~ *\#

ifneq ($(MAKECMDGOALS),clean)
    -include .depend
endif
