CXXFLAGS += -std=c++14 -O0 -g --coverage -fmax-errors=5
LDFLAGS += -lcash

PROJECT = test.out

SRCS = main.cpp dogfood.cpp smoke.cpp literals.cpp proxies.cpp aggregates.cpp select.cpp arithm.cpp reg.cpp mem.cpp sim.cpp miscs.cpp float.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(PROJECT)

$(PROJECT) : $(OBJS)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

.depend: $(SRCS)
	$(CXX) $(CXXFLAGS) -MM $^ > .depend;

clean:
	rm -f *.out *.o *.v *.vcd *.gcda *.gcno .depend *~ *\#

run: $(PROJECT)
	./$(PROJECT)

cov: $(PROJECT)
	./covgen.sh

ifneq ($(MAKECMDGOALS),clean)
    -include .depend
endif
