#ifndef __ANALYSEUR__
#define __ANALYSEUR__

/*		### BIBLIOTHEQUE ###		*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
 
#include "Data.h"
#include "Arbre.h"
/*		### MACRO ###		*/

/*		### STRUCTURE ###		*/

typedef struct _cel{
	struct _cel* suivant;
	char* nom;
	double temps_total;
	unsigned int occ;
}Cellule, *Liste;

/*		### DECLARATION FONCTION ###	*/

void cree_stat(const Arbre in, FILE* out, int compar(const Liste lst1, const Liste lst2), Liste* lst);
/**
 * Ecrit sur le fichier out au format .log les informations
 * contenu dans in ainsi que dans la Liste lst.
 * 
 * Si out ou lst est NULL alors le paramètre est ignoré.
 * La Liste lst est trié par en respectant la fonction compar, si compar est 
 * égal à null la liste sera trié par ordre lexicographique
 * 
 */ 
#endif
