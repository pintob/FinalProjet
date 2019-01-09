/**
 * \file Arbre.c
 * \brief Génére et effectue des opération sur un arbre 
 * \author PINTO Bruno
 *
 * Permet de crée un arbre à partir d'un fichier à parser.
 * Permet aussi d'en lire le contenu
 *
 */
 
/*		### BIBLIOTHEQUE ###		*/
#include "../include/Arbre.h"
#include "../include/Dot.h"
#include "../lib/macro_profiler.h"

/*		### DECLARATION FONCTION PRIVEE###	*/
static Noeud* alloue_noeud(const Data* d, unsigned char id[3], Noeud* pere);
static double cree_arbre_aux(Arbre* a, FILE* in, Noeud* pere, unsigned char id[3], int *err);
static void inc_id(unsigned char id[3]);
static int compar_id(unsigned char id[3], unsigned char id2[3]);
/*		### DEFINITION FONCTION ###		*/


void libere_arbre(Arbre a){
	PROFILE
	if(NULL == a){
		return;
	}
	libere_arbre(a->fg);
	libere_arbre(a->frd);
	free(a->info.nom);
	free(a);
	return;
}

Noeud* alloue_noeud(const Data* d, unsigned char id[3], Noeud* pere){
	PROFILE
	Noeud *tmp;
	
	assert(d != NULL);
	
	tmp = (Noeud *) malloc (sizeof(Noeud));
	if (tmp == NULL){
		return NULL;
	}
	tmp->id[0] = id[0];
	tmp->id[1] = id[1];
	tmp->id[2] = id[2];
	tmp->fg = NULL;
	tmp->frd = NULL; 
	tmp->pere = pere; 
	tmp->info.temps_total = d->temps_total;
	tmp->info.temps_seul = d->temps_total;
	tmp->info.nom = d->nom;
	return tmp;
	
}

int cree_arbre(Arbre* a, FILE* in){
	PROFILE
	unsigned char id[3] = {};
	int err = NoTreeError;
	cree_arbre_aux(a, in, NULL, id, &err);
	return err;
}

double cree_arbre_aux(Arbre* a, FILE* in, Noeud* pere, unsigned char id[3], int* err){
	PROFILE
	Data d;
	static double temps = 0;
	double temps_enfant;
	
	switch (parseur(in, &d)){
		case(InvalidLine):{
			*err = ParsingError;
			return 0;
		}
		case(EOF):{
			
			return 0;
		}
	}
	

	if(strcmp(d.nom, "END") == 0){
		temps = d.temps_total;
		free(d.nom);
		return 0;
	}
	inc_id(id);
	
	*a = alloue_noeud(&d, id, pere);
	if(NULL == a){
		free(d.nom);
		*err = MemoryError;
		return 0;
	}
	
	temps_enfant = cree_arbre_aux(&((*a)->fg), in, *a, id, err);
	if(*err != NoTreeError){
		free(d.nom);
		return 0;
	}
	(*a)->info.temps_total = temps - (*a)->info.temps_total;
	(*a)->info.temps_seul = temps - (*a)->info.temps_seul - temps_enfant;

	temps_enfant = cree_arbre_aux(&((*a)->frd), in, pere, id, err);
	
	if(*err != NoTreeError){
		free(d.nom);
		return 0;
	}
	return (*a)->info.temps_total + temps_enfant;
}

void ecriture_generique(const Arbre a, void* out, void(fct_ecriture)(void* out, const Data* donne)){
	PROFILE
	
	if(a == NULL){
		return;
	}
	
	fct_ecriture(out, &a->info);
	
	ecriture_generique(a->fg, out, fct_ecriture);
	ecriture_generique(a->frd, out, fct_ecriture);
	
	return;
}

void ecriture_generique_frere(const Noeud* noeud, void* out, void(fct_ecriture)(void* out, const Data* donne)){
	PROFILE
	Noeud* copie;
	
	for(copie = (Noeud*)noeud; copie != NULL; copie = copie->frd){
		fct_ecriture(out, &(copie->info));
	}
	return;
}

Noeud* cherche_noeud(const Arbre a, unsigned char id[3]){
	PROFILE
	Noeud* res;
	
	if(NULL == a)
		return NULL;
	if(compar_id(id, a->id) == 0)
		return a;
	if(a->frd == NULL){
		res = cherche_noeud(a->fg, id);
		return res;
	}
	if(compar_id(id, a->frd->id) > 0){
		res = cherche_noeud(a->fg, id);
		return res;
	}
	res = cherche_noeud(a->frd, id);
	return res;
}

int compar_id(unsigned char id[3], unsigned char id2[3]){
	PROFILE
	if(id[2] != id2[2]){
		return id2[2] - id[2];
	}
	if(id[1] != id2[1]){
		return id2[1] - id[1];
	}
	if(id[0] != id2[0]){
		return id2[0] - id[0];
	}
	
	return 0;
}

void inc_id(unsigned char id[3]){
	PROFILE
	id[0] += 1;
	if(id[0] == 0){
		id[1] += 1;
		if(id[1] == 0)
			id[2] += 1;
	}
	return;
}
