CC    ?= clang
CXX   ?= clang++

EXE = my_wc

CDEBUG = -g -Wall

CXXDEBUG = -g -Wall

CSTD = -std=c99
CXXSTD = -std=c++17

CFLAGS = -Wno-deprecated-register -O0  $(CDEBUG) $(CSTD) 
CXXFLAGS = -Wno-deprecated-register -O0  $(CXXDEBUG) $(CXXSTD)


CPPOBJ = main driver dict tree
SOBJ =  parser scanner

FILES = $(addsuffix .cpp, $(CPPOBJ))

OBJS  = $(addsuffix .o, $(CPPOBJ))

CLEANLIST =  $(addsuffix .o, $(OBJ)) $(OBJS) \
				 parser.tab.cc parser.tab.hh \
				 location.hh position.hh \
			   stack.hh parser.output parser.o \
				 scanner.o scanner.yy.cc $(EXE)\

.PHONY: all
all: wc

wc: $(FILES)
	$(MAKE) $(SOBJ)
	$(MAKE) $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(OBJS) parser.o scanner.o $(LIBS)


parser: parser.y 
	bison -d -v parser.y
	$(CXX) $(CXXFLAGS) -c -o parser.o parser.tab.cc

scanner: scanner.l
	flex --outfile=scanner.yy.cc  $<
	$(CXX)  $(CXXFLAGS) -c scanner.yy.cc -o scanner.o

.PHONY: test
test:
	cd test && ./test0.pl

.PHONY: clean
clean:
	rm -rf $(CLEANLIST)
