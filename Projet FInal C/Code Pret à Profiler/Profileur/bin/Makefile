CFLAGS = -Wall -Wfatal-errors -O2 -g -L..//lib -lprofileur
CFLAGSMLV = `pkg-config --cflags MLV`
LDLIBS = `pkg-config --libs MLV`
OBJ = Analyseur.o Arbre.o ComparListe.o Data.o Dot.o main.o Parseur.o API.o

all:
	make doc
	make myprofiler
	

myprofiler: $(OBJ)
	gcc -o myprofiler $(OBJ) $(CFLAGS) $(CFLAGSMLV) $(LDLIBS)

doc: Doxyfile
	doxygen Doxyfile

Analyseur.o: ../src/Analyseur.c ../include/Analyseur.h ../include/Data.h ../include/Arbre.h 
	gcc -c $< $(CFLAGS)

Arbre.o: ../src/Arbre.c ../include/Arbre.h ../include/Data.h ../include/Dot.h ../include/Parseur.h
	gcc -c $< $(CFLAGS)

ComparListe.o: ../src/ComparListe.c ../include/ComparListe.h ../include/Analyseur.h
	gcc -c $< $(CFLAGS)
	
API.o: ../src/API.c ../include/API.h ../include/Arbre.h
	gcc -c $< $(CFLAGS)

Data.o: ../src/Data.c ../include/Data.h
	gcc -c $< $(CFLAGS)
	
Dot.o: ../src/Dot.c ../include/Dot.h ../include/Arbre.h
	gcc -c $< $(CFLAGS)

main.o: ../src/main.c ../include/Arbre.h ../include/Analyseur.h ../include/ComparListe.h ../include/API.h
	gcc -c $< $(CFLAGS)

Parseur.o: ../src/Parseur.c ../include/Parseur.h ../include/Data.h
	gcc -c $< $(CFLAGS)

clean:
	rm -f *.o 
	
mrproper: clean
	rm -rf ../html
	rm -f myprofiler 
	
