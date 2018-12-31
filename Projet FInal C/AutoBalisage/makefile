# Makefile TP Flex

# $@ : the current target
# $^ : the current prerequisites
# $< : the first current prerequisite

CFLAGS=-Wall -lfl -O2
EXEC=balisage

all:  balisage
	 make balisage_recursif

balisage: lex.yy.o
	gcc -o $@ $^ $(CFLAGS)

balisage_recursif: balisage_recursif.o
	gcc -o $@ $^ $(CFLAGS)

lex.yy.c: balisage.lex
	  flex balisage.lex

%.o: %.c
	gcc -o $@ -c $< $(CFLAGS)

clean:
	rm -f lex.yy.* *.o
	
mrproper: clean
	rm -f balisage
	rm -f balisage_recursif
