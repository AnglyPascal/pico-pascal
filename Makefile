CXX   	?= g++
CXXDEBUG = -g -Wall
CXXSTD 	 = -std=c++17
CXXFLAGS = $(CXXDEBUG) $(CXXSTD)

EXE = ppc

SRC := src
TESTSRC := $(shell ls test/*.p)

MAIN = main 
COMP = consts check types dict tree keiko kgen driver \
			 simplify exceptions tree_print
SOBJ = parser scanner

CPPS = $(addprefix $(SRC)/, $(addsuffix .cpp, $(COMP) $(MAIN)))
OBJS = $(addprefix $(SRC)/, $(addsuffix .o, $(COMP) $(MAIN)))

PJUNK = parser.cpp location.hh position.hh   \
			  stack.hh parser.output parser.o      \
				scanner.o scanner.cpp 
CLEANLIST = $(OBJS) $(addprefix $(SRC)/, $(PJUNK)) $(EXE)        

.PHONY: all

all: ppc

parser: $(SRC)/parser.y 
	bison -o $(SRC)/parser.cpp --defines=$(SRC)/parser.h -v $(SRC)/parser.y
	$(CXX) $(CXXFLAGS) -c -o $(SRC)/parser.o $(SRC)/parser.cpp

scanner: $(SRC)/scanner.l
	flex --outfile=$(SRC)/scanner.cpp  $<
	$(CXX)  $(CXXFLAGS) -c $(SRC)/scanner.cpp -o $(SRC)/scanner.o

ppc: $(CPPS) $(SRC)/parser.y $(SRC)/scanner.l
	$(MAKE) $(SOBJ)
	$(MAKE) $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(OBJS) $(SRC)/parser.o $(SRC)/scanner.o $(LIBS)

.PHONY: test
# test0 -- compile tests and diff object code
test : $(TESTSRC:test/%.p=test-%)

test-%: force
	$(MAKE) ppc
	@echo "*** Test $*.p"
	./ppc $(OPT) test/$*.p # >b.s
	# -sed -n $(SCRIPT1) test/$*.p | diff -u -b - b.s
	@echo

force:

.PHONY: clean
clean:
	rm -rf $(CLEANLIST)

