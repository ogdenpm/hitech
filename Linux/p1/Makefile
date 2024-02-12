TARGET = p1
OBJS =	 cclass.o emit.o expr.o lex.o main.o memchk.o op.o program.o stmt.o sym.o type.o
include ../hi.mk

main.o: showVersion.h
class.o: cclass.h
emit.o expr.o lex.o main.o op.o program.o stmt.o sym.o type.o: p1.h cclass.h tok.h
