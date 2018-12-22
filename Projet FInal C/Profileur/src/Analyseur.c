
/*		### BIBLIOTHEQUE ###		*/
#include "../include/Analyseur.h"
#include "../include/Erreur.h"
/*		### STRUCT FONCTION PRIVEE###	*/


/*		### DECLARATION FONCTION PRIVEE###	*/
static int ajoute_liste(Liste* lst, char* mot, double temps);
static Cellule* alloue_cellule(char* nom, double temps);
static void liberer_liste(Liste* lst);
static void liberer_liste_aux(Liste lst);
static void tri_fusion(Liste *lst, int compar(Liste, Liste));
static void insertion_generique(void* data, const Data* donne);
static void affiche_liste(const Liste lst, double temps_total, FILE* out);
static int taille_liste(const Liste lst);
/*		### DEFINITION FONCTION ###		*/


int ajoute_liste(Liste* lst, char* mot, double temps){
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
		if(temp == NULL)
			return 1;
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
			
			if(temp == NULL)
				return 1;
			else{
				temp->suivant = courant->suivant;
				courant->suivant = temp;
				return 0;
			 }		
		}		
	}
	
	/*à la fin*/
	
	temp = alloue_cellule(mot, temps);
	
	if(temp == NULL)
		return 1;
	
	courant->suivant = temp;
	
	return 0;
}

Cellule* alloue_cellule(char* nom, double temps) {
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
	if(*lst == NULL)
		return;
	liberer_liste_aux(*lst);
	free((*lst)->nom);
	free(*lst);
	*lst = NULL;
	
}

void liberer_liste_aux(Liste lst){
	
	Liste courant, backup;
	courant = lst;
	
	if(lst == NULL)
		return;
		
    for (courant = lst->suivant; courant != NULL; courant= backup){
        backup= courant->suivant;  
        free(courant->nom);
        free(courant);
	}

}

void affiche_liste(const Liste lst, double temps_total, FILE* out){
	Liste copie;
	
	assert(lst != NULL);
	assert(out != NULL);
	
	/* time 9 seconds 9 seconds 9 calls 6 ms/call 7 ms/call 7*/
	printf("  %%         self           \n");
	printf("time      mseconds   calls     ms/calls    name\n");
	for(copie = lst; copie != NULL; copie = copie->suivant){
		printf("%7.4lf     %6.2lf %7d    %8.4lf     %s\n", 
			copie->temps_total / temps_total * 100,
			copie->temps_total * 1000,
			copie->occ,
			copie->temps_total * 1000 / copie->occ, 
			copie->nom);
	}
}

void insertion_generique(void* data, const Data* donne){
	
	assert(data != NULL);
	assert(donne != NULL);
	
	ajoute_liste(data, donne->nom, donne->temps_seul);
}

void cree_stat(const Arbre in, FILE* out, int compar(const Liste lst1, const Liste lst2), Liste* lst){
	Liste _lst = NULL;
	
	assert(in != NULL);
	
	ecriture_generique(in, &_lst, insertion_generique);
	if(compar != NULL){
		tri_fusion(lst, compar);
	}
	
	if(out != NULL)
		affiche_liste(_lst, in->info.temps_total, out);
	
	if(lst != NULL)
		*lst = _lst;
	else
		liberer_liste(&_lst);
}

void fusion(Liste *un, Liste *deux, int compar(Liste, Liste)){ 

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
	
}

void tri_fusion(Liste *lst, int compar(Liste, Liste)){
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
}

int taille_liste(const Liste lst){
	int i;
	Liste tmp = (Liste)lst;
	for(i = 0; tmp != NULL; i++, tmp=tmp->suivant);
	
	return i;
	
}
