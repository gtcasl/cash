CXXFLAGS += -std=c++14 -O0 -g --coverage -fmax-errors=5
LDFLAGS += -lcash

PROJECT = test.out

SRCS = common.cpp basic.cpp literals.cpp proxies.cpp aggregates.cpp select.cpp arithm.cpp reg.cpp mem.cpp module.cpp sim.cpp misc.cpp float.cpp main.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(PROJECT) dogfood.out

$(PROJECT) : $(OBJS)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

dogfood.out : dogfood.o
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

.depend: $(SRCS) dogfood.cpp
	$(CXX) $(CXXFLAGS) -MM $^ > .depend;

clean:
	rm -f *.out *.o *.vcd *.gcda *.gcno .depend *~ *\#

run: $(PROJECT)
	./$(PROJECT)

cov: $(PROJECT)
	./covgen.sh
	gnome-open lcov_html/index.html

ifneq ($(MAKECMDGOALS),clean)
    -include .depend
endif
