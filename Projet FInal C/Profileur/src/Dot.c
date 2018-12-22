
/*		### BIBLIOTHEQUE ###		*/
#include "../include/Dot.h"
/*		### DECLARATION FONCTION PRIVEE###	*/
void ecrire_debut(FILE *out);
void ecrit_arbre_dot(const Arbre a, FILE *out);
void ecrire_fin(FILE *out);
/*		### DEFINITION FONCTION ###		*/

void cree_dot(const Arbre a, FILE* out){
	
	assert(a != NULL);
	assert(out != NULL);
	
	ecrire_debut(out);
	ecrit_arbre_dot(a,out);
	ecrire_fin(out);
}


void ecrire_debut(FILE *out){
	assert(out != NULL);
	fprintf(out, "digraph arbre {\nnode [shape=record,height=.1]\nedge [tailclip=false, arrowtail=dot, dir=both];\n");
}

void ecrit_arbre_dot(const Arbre a, FILE *out){
	
	assert(a != NULL);
	assert(out != NULL);
	fprintf(out,"n%p [label=\"<gauche> | <valeur> %s | <temps> %lf - %lf | <droit>\"];\n",a , a->info.nom, a->info.temps_total, a->info.temps_seul);


	if( NULL != a->fg){
		ecrit_arbre_dot(a->fg, out);
		fprintf(out, "n%p:gauche:c -> n%p:valeur;\n",a ,a->fg );
	}
	if( NULL != a->frd){
		ecrit_arbre_dot(a->frd,out);
		fprintf(out, "n%p:droit:c -> n%p:valeur;\n",a ,a->frd );
	}
	
}

void ecrire_fin(FILE *out){
	assert(out != NULL);
	fprintf(out, "}");
}
