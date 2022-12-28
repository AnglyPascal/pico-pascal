CXX   	?= g++
CXXDEBUG = -g -Wall
CXXSTD 	 = -std=c++17
CXXFLAGS = $(CXXDEBUG) $(CXXSTD)

EXE = ppc

SRC_DIR := src

CPPOBJ = main 
COMP = check types dict tree keiko kgen driver
SOBJ = parser scanner

CPP_FILES = $(addsuffix .cpp, $(COMP) $(CPPOBJ))
OBJS = $(addsuffix .o, $(COMP) $(CPPOBJ))

CLEANLIST =  $(addsuffix .o, $(SOBJ)) $(OBJS) \
				 parser.cpp location.hh position.hh   \
			   stack.hh parser.output parser.o      \
				 scanner.o scanner.cpp $(EXE)         \

.PHONY: all

all: ppc

keiko: keiko.h keiko.cpp
	$(CXX) $(CXXFLAGS) -c -o keiko.o keiko.cpp

kgen: kgen.h kgen.cpp consts.h consts.cpp
	$(CXX) $(CXXFLAGS) -c -o consts.o consts.cpp
	$(CXX) $(CXXFLAGS) -c -o kgen.o kgen.cpp

dict: dict.h dict.cpp types
	$(CXX) $(CXXFLAGS) -c -o dict.o dict.cpp

tree: tree.h tree.cpp dict 
	$(CXX) $(CXXFLAGS) -c -o tree.o tree.cpp

types: types.h types.cpp
	$(CXX) $(CXXFLAGS) -c -o types.o types.cpp

driver: driver.h driver.cpp parser scanner
	$(CXX) $(CXXFLAGS) -c -o driver.o driver.cpp

check: check.h check.cpp tree dict types
	$(CXX) $(CXXFLAGS) -c -o check.o check.cpp

ppc: $(FILES) parser.y scanner.l
	$(MAKE) $(SOBJ)
	# $(MAKE) $(COMP)
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
