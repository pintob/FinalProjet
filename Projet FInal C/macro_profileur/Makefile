CFLAGS = -Wall -Wfatal-errors -O2 -lrt

libprofileur.a: macro_profiler.o
	ar rs libprofileur.a macro_profiler.o
	
macro_profiler.o: macro_profiler.c
	gcc -c $< $(CFLAGS)

clean:
	rm -f *.o *.a
