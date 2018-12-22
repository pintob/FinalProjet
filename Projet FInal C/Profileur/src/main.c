
#include <stdio.h>
#include "../include/Arbre.h"
#include "../include/Dot.h"
#include "../include/Parseur.h"
#include "../include/Analyseur.h"
#include "../include/Data.h"



int main(int argc, char **argv){
	FILE* in , *out;
	Arbre a;
	in = fopen("profile.log", "r");
	out = fopen("visualise.dot","w");
	
	cree_arbre(&a, in);
	cree_dot(a, out);
	fclose(out);
	
	/*system("dot -Tpdf visualise.dot -o visualise.pdf"); 
	system(" evince visualise.pdf &");*/
	
	/*printf("%lf\n", cherche_noeud(a, 4)->info.temps_seul); */
	
	cree_stat(a, stdout, NULL, NULL),
	fclose(in);
	libere_arbre(a);
	return 0;
}

