
#include <stdio.h>
#include "../include/Arbre.h"
#include "../include/Dot.h"
#include "../include/Parseur.h"
#include "../include/Analyseur.h"
#include "../include/Data.h"
#include "../include/Erreur.h"



int main(int argc, char **argv){
	FILE* in , *out;
	Arbre a;
	
	in = fopen("profile.log", "r");
	cree_arbre(&a, in);
	
	
	#ifndef NDEBUG
		out = fopen("visualise.dot","w");
		cree_dot(a, out);
		fclose(out);
		system("dot -Tpdf visualise.dot -o visualise.pdf"); 
		system(" evince visualise.pdf &");
	#endif /*NDEBUG*/
	
	cree_stat(a, stdout, NULL, NULL),
	fclose(in);
	libere_arbre(a);
	return 0;
}

