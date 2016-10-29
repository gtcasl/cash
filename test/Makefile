CXXFLAGS += -std=c++11 -O0 -g -fmax-errors=5 -DCHDL_DEBUG
LDFLAGS += -lchdl

PROJECT = test.out

all: $(PROJECT)

$(PROJECT) : main.o dogfood.o basics.o aggregates.o sim.o
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

view: $(PROJECT).vcd
	gtkwave $^ &

clean:
	rm -f *.out *.vcd *.o simv *~ *\#
