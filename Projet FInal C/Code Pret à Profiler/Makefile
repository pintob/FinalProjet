CFLAGS = -Wall -Wfatal-errors -O2 
STATICLIB = -L.//lib -lprofileur
EXE = RandomProgramme

all:
	make $(EXE)

RandomProgramme: RandomProgramme.o
	gcc -o RandomProgramme RandomProgramme.o $(CFLAGS) $(STATICLIB)

RandomProgramme.o: RandomProgramme.c
	gcc -c $< $(CFLAGS)
	

clean:
	rm -f *.o *.log
	
mrproper: clean
	rm -f $(EXE)


