
/*		### BIBLIOTHEQUE ###		*/
#include "../include/Arbre.h"
#include "../include/Dot.h"
/*		### DECLARATION FONCTION PRIVEE###	*/
Noeud* alloue_noeud(const Data* d, Id id, Noeud* pere);
double cree_arbre_aux(Arbre* a, FILE* in, Noeud* pere, Id* id, int *err);
/*		### DEFINITION FONCTION ###		*/


void libere_arbre(Arbre a){
	if(NULL == a){
		return;
	}
	libere_arbre(a->fg);
	libere_arbre(a->frd);
	free(a);
}

Noeud* alloue_noeud(const Data* d, Id id, Noeud* pere){
	Noeud *tmp;
	
	assert(d != NULL);
	
	tmp = (Noeud *) malloc (sizeof(Noeud));
	if (tmp == NULL){
		return NULL;
	}
	tmp->id = id;
	tmp->fg = NULL;
	tmp->frd = NULL; 
	tmp->pere = pere; 
	tmp->info.temps_total = d->temps_total;
	tmp->info.temps_seul = d->temps_total;
	tmp->info.nom = malloc(strlen(d->nom) + 1);
	if(NULL == tmp->info.nom){
		free(tmp);
		return NULL;
	}
	strcpy(tmp->info.nom, d->nom);
	return tmp;
	
}

int cree_arbre(Arbre* a, FILE* in){
	Id i = 0;
	int err = NoTreeError;
	cree_arbre_aux(a, in, NULL, &i, &err);
	return err;
}

double cree_arbre_aux(Arbre* a, FILE* in, Noeud* pere, Id* id, int* err){
	Data d;
	static double temps = 0;
	double temps_enfant;
	
	switch (parseur(in, &d)){
		case(InvalidLine):{
			*err = ParsingError;
			return 0;
		}
		case(EOF):
			return 0;
	}
	

	if(strcmp(d.nom, "END") == 0){
		temps = d.temps_total;
		free(d.nom);
		return 0;
	}
	
	*id = *id + 1;
	
	*a = alloue_noeud(&d, *id, pere);
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
	
	free(d.nom);
	return (*a)->info.temps_total + temps_enfant;
}

void ecriture_generique(const Arbre a, void* out, void(fct_ecriture)(void* out, const Data* donne)){
	
	if(a == NULL)
		return;
	
	fct_ecriture(out, &a->info);
	
	ecriture_generique(a->fg, out, fct_ecriture);
	ecriture_generique(a->frd, out, fct_ecriture);
	
}

void ecriture_generique_frere(const Noeud* noeud, void* out, void(fct_ecriture)(void* out, const Data* donne)){
	Noeud* copie;
	
	for(copie = (Noeud*)noeud; copie != NULL; copie = copie->frd){
		fct_ecriture(out, &(copie->info));
	}
}

Noeud* cherche_noeud(const Arbre a, Id id){
	if(NULL == a)
		return NULL;
	if(a->id == id)
		return a;
	if(a->frd == NULL)
		return cherche_noeud(a->fg, id);
	if(id < a->frd->id)
		return cherche_noeud(a->fg, id); /*on va dans fg et pas frd (voir doc)*/
	return cherche_noeud(a->frd, id);
}
