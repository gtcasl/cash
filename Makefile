PREFIX ?= /usr/local
#CXXFLAGS += -fPIC -std=c++11 -O2 -DNDEBUG
CXXFLAGS += -fPIC -std=c++11 -O0 -g -fmax-errors=5
LDFLAGS += -shared

SRCS = utils.cpp nodeimpl.cpp proxyimpl.cpp litimpl.cpp aluimpl.cpp regimpl.cpp memimpl.cpp \
       ioimpl.cpp busimpl.cpp cdomain.cpp context.cpp device.cpp assertimpl.cpp \
       opt.cpp sim.cpp vcd.cpp

OBJS := $(SRCS:.cpp=.o)

all : libchdl.so

libchdl.so : $(OBJS)
	$(CXX) $^ $(LDFLAGS) -o $@

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

install: libchdl.so
	if [ ! -e $(PREFIX)/lib ]; then mkdir -p $(PREFIX)/lib; fi
	cp libchdl.so $(PREFIX)/lib
	if [ ! -e $(PREFIX)/include/chdl ]; then mkdir -p $(PREFIX)/include/chdl; fi
	cp *.h $(PREFIX)/include/chdl

uninstall:
	rm -rf $(PREFIX)/lib/libchdl.so $(PREFIX)/include/chdl

.depend: $(SRCS)
	$(CXX) $(CXXFLAGS) -MM $^ > .depend;

clean:
	rm -f libchdl.so $(OBJS) .depend *~ *\#

ifneq ($(MAKECMDGOALS),clean)
    -include .depend
endif
