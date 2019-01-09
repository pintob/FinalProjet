CFLAGS = -Wall -Wfatal-errors -lm
STATICLIB = -L.//lib -lprofileur
EXE = RandomProgramme Optimus Fact

all:
	make $(EXE)

RandomProgramme: RandomProgramme.o
	gcc -o RandomProgramme RandomProgramme.o $(CFLAGS) $(STATICLIB)

RandomProgramme.o: RandomProgramme.c
	gcc -c $< $(CFLAGS)

Optimus: Optimus.o
	gcc -o Optimus Optimus.o $(CFLAGS) $(STATICLIB)

Fact.o: Fact.c
	gcc -c $< $(CFLAGS)
	
Fact: Fact.o
	gcc -o Fact Fact.o $(CFLAGS) $(STATICLIB)

Optimus.o: Optimus.c
	gcc -c $< $(CFLAGS)

clean:
	rm -f *.o *.log
	
mrproper: clean
	rm -f $(EXE)


