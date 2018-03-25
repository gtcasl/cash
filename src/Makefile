#CXX = clang-5.0
PREFIX ?= /usr/local
#CXXFLAGS += -fPIC -std=c++17 -O3 -DNDEBUG -Wall -Wextra -pedantic
CXXFLAGS += -fPIC -std=c++17 -O0 -g --coverage -pedantic -Wall -Wextra -fmax-errors=5
LDFLAGS += -shared --coverage -lbfd

PROJECT = libcash

SRCS = utils.cpp platform.cpp bitvector.cpp scalar.cpp \
       lnodeimpl.cpp proxyimpl.cpp litimpl.cpp selectimpl.cpp regimpl.cpp \
       aluimpl.cpp ioimpl.cpp memimpl.cpp bindimpl.cpp assertimpl.cpp tickimpl.cpp printimpl.cpp \
       logic.cpp cdomain.cpp context.cpp compile.cpp deviceimpl.cpp \
       simulatorimpl.cpp tracerimpl.cpp vcdtracerimpl.cpp \
       verilogwriter.cpp firrtlwriter.cpp \
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
