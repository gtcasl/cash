CASH_HOME ?= /usr/local

CXXFLAGS += -std=c++17 -g -I$(CASH_HOME)/include -Wall -Wextra -pedantic

# Use Clang plugin if available
ifneq ("$(wildcard $(CASH_HOME)/lib/libcashpp.so)","")
	CXX = clang++-9
	CXXFLAGS += -Xclang -load -Xclang $(CASH_HOME)/lib/libcashpp.so -Xclang -add-plugin -Xclang cash-pp
endif

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