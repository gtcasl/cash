CXXFLAGS += -std=c++14 -O0 -g -fmax-errors=5 -DCHDL_DEBUG
LDFLAGS += -lchdl

PROJECT = test.out

all: $(PROJECT)

$(PROJECT) : main.o dogfood.o basics.o mem.o aggregates.o sim.o miscs.o
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

view: $(PROJECT).vcd
	gtkwave $^ &

clean:
	rm -f *.out *.vcd *.o simv *~ *\#
