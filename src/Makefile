all:
	flex -o scanner.cpp scanner.l
	bison -o parser.cpp --defines=parser.h -v parser.y
	g++ -g main.cpp scanner.cpp parser.cpp driver.cpp tree.cpp dict.cpp -o ppc

clean:
	rm -rf scanner.cpp
	rm -rf parser.cpp parser.h location.hh position.hh stack.hh
	rm -rf a.out
