.PHONY: clean distclean default

CC=g++
CFLAGS=-Wall

default: gracecomp

lexer.cpp: lexer.l
	flex -s -o lexer.cpp lexer.l

lexer.o: lexer.cpp lexer.hpp parser.hpp

parser.hpp parser.cpp: parser.y
	bison -dv --debug -o parser.cpp parser.y

parser.o: parser.cpp lexer.hpp

gracecomp: lexer.o parser.o
	$(CC) $(CFLAGS) -o gracecomp lexer.o parser.o

clean:
	$(RM) lexer.cpp parser.cpp parser.hpp parser.output *.o

distclean: clean
	$(RM) gracecomp