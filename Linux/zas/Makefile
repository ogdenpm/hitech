TARGET = zas
OBJS =	 code.o cclass.o expr.o lex.o macro.o main.o kwd.o\
		 parse.o sym.o tlab.o fname.o 
include ../hi.mk

cclass.o code.o kwd.o lex.o: cclass.h
main.o : showVersion.h
code.o expr.o kwd.o lex.o macro.o main.o parse.o sym.o tlab.o: zas.h kwd.h
