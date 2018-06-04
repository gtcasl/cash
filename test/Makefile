#CXX = clang-5.0
CXXFLAGS += -std=c++17 -O0 -g --coverage -pedantic -Wall -Wextra -fmax-errors=1
LDFLAGS += -lcash -lstdc++

PROJECT = test.out

SRCS = common.cpp basic.cpp scalar.cpp literals.cpp proxies.cpp aggregates.cpp select.cpp arithm.cpp reg.cpp mem.cpp \
       module.cpp sim.cpp misc.cpp htl.cpp float.cpp main.cpp

OBJS = $(SRCS:.cpp=.o)

all: dogfood.out $(PROJECT)

$(PROJECT) : $(OBJS)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

dogfood.out : common.o dogfood.o
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

.depend: $(SRCS) dogfood.cpp
	$(CXX) $(CXXFLAGS) -MM $^ > .depend;

clean:
	rm -f *.out *.o *.vcd *.fir *.gcda *.gcno .depend *~ *\#

run: $(PROJECT)
	./$(PROJECT)

cov: $(PROJECT)
	./covgen.sh
	gnome-open lcov_html/index.html

ifneq ($(MAKECMDGOALS),clean)
    -include .depend
endif
