#CXX = clang-5.0
#CXXFLAGS += -std=c++17 -O3 -DNDEBUG -Wall -Wextra -pedantic
CXXFLAGS += -std=c++17 -O0 -g -I/usr/lib/llvm-5.0/include -Wall -Wextra -pedantic
LDFLAGS += -L/usr/lib/llvm-5.0/lib -lclang -lstdc++

SRCS = parser.cpp

PROJECTS = $(SRCS:.cpp=.out)
PROJECTS_NAMES = $(SRCS:.cpp=)

all: $(PROJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.out: %.o
	$(CXX) $^ $(LDFLAGS) -o $@

.depend: $(SRCS)
	$(CXX) $(CXXFLAGS) -MM $^ > .depend;

clean:
	rm -f *.out *.o *.vcd *.iv .depend *~ *\#

run: $(PROJECTS)
	$(foreach proj, $(PROJECTS), ./$(proj) || exit;)

ifneq ($(MAKECMDGOALS),clean)
    -include .depend
endif
