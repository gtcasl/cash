# use Clang-9 compiler
CXX ?= clang++-9

CASH_HOME ?= /usr/local

CXXFLAGS += -std=c++17 -g -I$(CASH_HOME)/include -Wall -Wextra -pedantic

# Clang plugin flags
CXXFLAGS += -Xclang -load -Xclang $(CASH_HOME)/lib/libcashpp.so -Xclang -add-plugin -Xclang cash-pp

LDFLAGS  += -lcash -L$(CASH_HOME)/lib

PROJECT = demo.out

SRCS = demo.cpp

OBJS := $(SRCS:.cpp=.o)

all: $(PROJECT)

$(PROJECT): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

.depend: $(SRCS)
	$(CXX) $(CXXFLAGS) -MM $^ > .depend;

clean:
	rm -rf *.out *.o *.v

ifneq ($(MAKECMDGOALS),clean)
    -include .depend
endif