#CXX = clang-3.8
PREFIX ?= /usr/local
#CXXFLAGS += -fPIC -std=c++14 -O3 -DNDEBUG -Wall -Wextra
CXXFLAGS += -fPIC -std=c++14 -O0 -g --coverage -Wall -Wextra -Werror -fmax-errors=5
LDFLAGS += -shared --coverage -lbfd

SRCS = utils.cpp platform.cpp bitvector.cpp \
       lnodeimpl.cpp proxyimpl.cpp litimpl.cpp selectimpl.cpp regimpl.cpp \
	   memimpl.cpp aluimpl.cpp ioimpl.cpp assertimpl.cpp tickimpl.cpp printimpl.cpp \
       snodeimpl.cpp cdomain.cpp context.cpp device.cpp compile.cpp sim.cpp vcd.cpp

OBJS := $(SRCS:.cpp=.o)

all : libcash.so

libcash.so : $(OBJS)
	$(CXX) $^ $(LDFLAGS) -o $@

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

install: libcash.so
	if [ ! -e $(PREFIX)/lib ]; then mkdir -p $(PREFIX)/lib; fi
	cp libcash.so $(PREFIX)/lib
	if [ ! -e $(PREFIX)/include/cash ]; then mkdir -p $(PREFIX)/include/cash; fi
	cp *.h $(PREFIX)/include/cash

uninstall:
	rm -rf $(PREFIX)/lib/libcash.so $(PREFIX)/include/cash

.depend: $(SRCS)
	$(CXX) $(CXXFLAGS) -MM $^ > .depend;

clean:
	rm -f libcash.so $(OBJS) *.gcno .depend *~ *\#

ifneq ($(MAKECMDGOALS),clean)
	-include .depend
endif
