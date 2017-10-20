#CXX = clang-3.8
PREFIX ?= /usr/local
#CXXFLAGS += -fPIC -std=c++14 -O3 -DNDEBUG -Wall -Wextra
CXXFLAGS += -fPIC -std=c++14 -O0 -g --coverage -Wall -Wextra -Werror -fmax-errors=5
LDFLAGS += -shared --coverage -lbfd

PROJECT = libcash

SRCS = utils.cpp platform.cpp bitvector.cpp scalar.cpp \
       lnodeimpl.cpp proxyimpl.cpp litimpl.cpp selectimpl.cpp regimpl.cpp \
       aluimpl.cpp ioimpl.cpp memimpl.cpp callimpl.cpp assertimpl.cpp tickimpl.cpp printimpl.cpp \
       bit.cpp cdomain.cpp context.cpp compile.cpp moduleimpl.cpp \
       simulatorimpl.cpp tracerimpl.cpp vcdtracerimpl.cpp \
       verilogwriter.cpp \
       cash.cpp

OBJS := $(SRCS:.cpp=.o)

all : $(PROJECT).so

libcash.so : $(OBJS)
	$(CXX) $^ $(LDFLAGS) -o $@

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.depend: $(SRCS)
	$(CXX) $(CXXFLAGS) -MM $^ > .depend;

install: $(PROJECT).so
	if [ ! -e $(PREFIX)/lib ]; then mkdir -p $(PREFIX)/lib; fi
	cp libcash.so $(PREFIX)/lib
	if [ ! -e $(PREFIX)/include/cash ]; then mkdir -p $(PREFIX)/include/cash; fi
	cp *.h $(PREFIX)/include/cash

uninstall:
	rm -rf $(PREFIX)/lib/$(PROJECT).so $(PREFIX)/include/cash

clean:
	rm -f $(PROJECT).so $(OBJS) *.gcda *.gcno .depend *~ *\#

ifneq ($(MAKECMDGOALS),clean)
    -include .depend
endif
