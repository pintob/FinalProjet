CFLAGS = -Wall -Wfatal-errors -O2 -lm
STATICLIB = -L.//lib -lprofileur
EXE = RandomProgramme Optimus

all:
	make $(EXE)

RandomProgramme: RandomProgramme.o
	gcc -o RandomProgramme RandomProgramme.o $(CFLAGS) $(STATICLIB)

RandomProgramme.o: RandomProgramme.c
	gcc -c $< $(CFLAGS)

Optimus: Optimus.o
	gcc -o Optimus Optimus.o $(CFLAGS) $(STATICLIB)

Optimus.o: Optimus.c
	gcc -c $< $(CFLAGS)

clean:
	rm -f *.o *.log
	
mrproper: clean
	rm -f $(EXE)


