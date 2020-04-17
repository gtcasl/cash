CASH_HOME ?= /usr/local

CXXFLAGS += -std=c++17 -g -I$(CASH_HOME)/include -Wall -Wextra -pedantic

# Use Clang plugin if available
ifneq ("$(wildcard $(CASH_HOME)/lib/libcashpp.so)","")
	CXX = clang++
	CXXFLAGS += -Xclang -load -Xclang $(CASH_HOME)/lib/libcashpp.so -Xclang -add-plugin -Xclang cash-pp #-Xclang -plugin-arg-cash-pp -Xclang debug -Xclang -plugin-arg-cash-pp -Xclang dump-ast
endif

LDFLAGS  += -lcash -L$(CASH_HOME)/lib -Wl, -rpath /usr/local/lib

PROJECT = demo.out

SRCS = demo.cpp

OBJS := $(SRCS:.cpp=.o)

.PHONY: all
all: $(PROJECT)

$(PROJECT): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(LDFLAGS) -o $@

.depend: $(SRCS)
	$(CXX) $(CXXFLAGS) -MM $^ > .depend;

.PHONY: clean
clean:
	rm -rf *.out *.o *.v

ifneq ($(MAKECMDGOALS),clean)
    -include .depend
endif
