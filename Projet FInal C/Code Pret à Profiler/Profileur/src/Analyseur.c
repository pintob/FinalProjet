/**
 * \file Analyseur.c
 * \brief Génére une liste chaînée à partir d'un arbre
 * \author PINTO Bruno
 *
 * Génére une liste chaînée à partir d'un arbre et traiter son contenu
 *
 */
 
/*		### BIBLIOTHEQUE ###		*/
#include "../include/Analyseur.h"
#include "../include/Erreur.h"
#include "../lib/macro_profiler.h"


/*		### DECLARATION FONCTION PRIVEE###	*/
static int ajoute_liste(Liste* lst, char* mot, double temps);
static Cellule* alloue_cellule(char* nom, double temps);
static void liberer_liste_aux(Liste lst);
static void insertion_generique(void* data, const Data* donne);
static int taille_liste(const Liste lst);
/*		### DEFINITION FONCTION ###		*/


int ajoute_liste(Liste* lst, char* mot, double temps){
	PROFILE
	/** retour 1:echec */
	Liste courant = *lst,temp = NULL;
	int i = 0;
	/*Liste VIDE*/
	if(*lst == NULL){
		*lst = alloue_cellule(mot, temps);
		return *lst == NULL;
	}
		
	/*Change entete*/
	
	i = strcmp(courant->nom, mot);
	if ( i == 0){
		courant->temps_total += temps;
		courant->occ += 1;
		return 0;
	}
	if ( i > 0){
		temp = alloue_cellule(mot, temps);
		if(temp == NULL){
			return 1;
		}
		else{
			temp->suivant = courant;
			*lst = temp;
			return 0;
		 }		
	}
	
	/*au milieu*/
	
	for(; courant->suivant != NULL; courant = courant->suivant){
		i = strcmp(courant->suivant->nom, mot);
		if( i == 0 ){
			courant->suivant->occ += 1;
			courant->suivant->temps_total += temps;
			return 0;
		}
		if ( i > 0){
			temp = alloue_cellule(mot, temps);
			
			if(temp == NULL){
				return 1;
			}
			else{
				temp->suivant = courant->suivant;
				courant->suivant = temp;
				return 0;
			 }		
		}		
	}
	
	/*à la fin*/
	
	temp = alloue_cellule(mot, temps);
	
	if(temp == NULL){
		return 1;
	}
	
	courant->suivant = temp;
	
	return 0;
}

Cellule* alloue_cellule(char* nom, double temps) {
	PROFILE
	Cellule* tmp;
	char* mot;
	
	mot = (char *) malloc(sizeof(char) * (strlen(nom) + 1));
	tmp = (Cellule *) malloc (sizeof(Cellule));
	if (tmp != NULL){
		strcpy(mot,nom);
		tmp->nom = mot;
		tmp->occ = 1;
		tmp->temps_total = temps;
		tmp->suivant = NULL;		
	}
	return tmp;
}

void liberer_liste(Liste* lst){
	PROFILE
	if(*lst == NULL)
		return;
	liberer_liste_aux(*lst);
	free((*lst)->nom);
	free(*lst);
	*lst = NULL;
	
	return;
}

void liberer_liste_aux(Liste lst){
	PROFILE
	
	Liste courant, backup;
	courant = lst;
	
	if(lst == NULL)
		return;
		
    for (courant = lst->suivant; courant != NULL; courant= backup){
        backup= courant->suivant;  
        free(courant->nom);
        free(courant);
	}

	return;
}

int affiche_liste(const Liste lst, double temps_total){
	PROFILE
	int res;
	
	res = faffiche_liste(stdout, lst, temps_total);
	return res;
}

int faffiche_liste(FILE* out, const Liste lst, double temps_total){
	PROFILE
	Liste copie;
	int cmp = 0;
	assert(lst != NULL);
	assert(out != NULL);
	
	/* time 9 seconds 9 seconds 9 calls 6 ms/call 7 ms/call 7*/
	printf("  %%         self           \n");
	printf("time      mseconds   calls     ms/calls    name\n");
	for(copie = lst; copie != NULL; copie = copie->suivant){
		cmp += printf("%7.4lf     %6.2lf %7d    %8.4lf     %s\n", 
			copie->temps_total / temps_total * 100,
			copie->temps_total * 1000,
			copie->occ,
			copie->temps_total * 1000 / copie->occ, 
			copie->nom);
	}
	return cmp;
}

void insertion_generique(void* data, const Data* donne){
	PROFILE
	
	assert(data != NULL);
	assert(donne != NULL);
	
	ajoute_liste(data, donne->nom, donne->temps_seul);
	return;
}

void cree_stat(const Arbre in, Liste* lst){
	PROFILE
	
	assert(in != NULL);
	assert(lst != NULL);
	
	ecriture_generique(in, lst, insertion_generique);
	return;
}

void fusion(Liste *un, Liste *deux, int compar(Liste, Liste)){
	PROFILE 

	Liste suivant = NULL, courant = NULL, temp = NULL;
	
	if( *un == NULL){
		*un = *deux;
		*deux = NULL;
		return;
	}
	if (*deux == NULL)
		return;
		
	if(compar(*un, *deux) < 0){ 
		temp = *un;
		*un = *deux;
		*deux = temp;
	}
	courant = *un;
	suivant = *deux;
	
	while( courant->suivant != NULL && suivant != NULL && courant->suivant != suivant){
		if(compar(courant->suivant, suivant) <0)
			courant = courant->suivant;
		else{
			temp = courant->suivant;
			courant->suivant = suivant;
			courant = courant->suivant;
			suivant = temp;
		}
	}
	if(courant->suivant == NULL)
			courant->suivant = suivant;
	
	return;
}

void tri_fusion(Liste *lst, int compar(Liste, Liste)){
	PROFILE
	/**
	 * Effectue un trie fusion sur un liste simplement chainée
	 */ 
	
	int taille = 0, i = 0;
	Liste copie = *lst, deux = NULL; 
	
	taille = taille_liste(*lst);
	
	if(taille <= 1)
		return;
	
	for( i = 0; i < taille/2 - 1; i++)
		copie = copie->suivant;
	
	deux = copie->suivant;
	copie->suivant = NULL;
	
	tri_fusion(lst, compar);
	tri_fusion(&deux, compar);
	
	fusion(lst, &deux, compar);
	return;
}

int taille_liste(const Liste lst){
	PROFILE
	int i;
	Liste tmp = (Liste)lst;
	for(i = 0; tmp != NULL; i++, tmp=tmp->suivant);
	
	return i;
	
}
