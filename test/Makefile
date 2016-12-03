CXXFLAGS += -std=c++14 -O0 -g -fmax-errors=5 -DCHDL_DEBUG
LDFLAGS += -lchdl

PROJECT = test.out

all: $(PROJECT)

$(PROJECT) : main.o dogfood.o literals.o proxies.o aggregates.o select.o arithm.o reg.o mem.o sim.o miscs.o float.o
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

view: $(PROJECT).vcd
	gtkwave $^ &

clean:
	rm -f *.out *.vcd *.o simv *~ *\#
