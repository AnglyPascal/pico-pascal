CXX   	?= g++
CXXDEBUG = -g -Wall
CXXSTD 	 = -std=c++17
CXXFLAGS = $(CXXDEBUG) $(CXXSTD)

EXE = ppc

SRC_DIR := src

CPPOBJ = main driver dict tree
SOBJ = parser scanner

FILES = $(addsuffix .cpp, $(CPPOBJ))
OBJS = $(addsuffix .o, $(CPPOBJ))

CLEANLIST =  $(addsuffix .o, $(SOBJ)) $(OBJS) \
				 parser.cpp location.hh position.hh   \
			   stack.hh parser.output parser.o      \
				 scanner.o scanner.cpp $(EXE)         \

.PHONY: all

all: ppc

ppc: $(FILES)
	$(MAKE) $(SOBJ)
	$(MAKE) $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(OBJS) $(ASTOBJS) parser.o scanner.o $(LIBS)

parser: parser.y 
	bison -o parser.cpp --defines=parser.h -v parser.y
	$(CXX) $(CXXFLAGS) -c -o parser.o parser.cpp

scanner: scanner.l
	flex --outfile=scanner.cpp  $<
	$(CXX)  $(CXXFLAGS) -c scanner.cpp -o scanner.o

.PHONY: test
test:
	cd test && ./test0.pl

.PHONY: clean
clean:
	rm -rf $(CLEANLIST)
