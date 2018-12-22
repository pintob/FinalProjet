#ifndef __DOT__
#define __DOT__

/*		### BIBLIOTHEQUE ###		*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Arbre.h"
/*		### MACRO ###		*/

/*		### STRUCTURE ###		*/

/*		### DECLARATION FONCTION ###	*/
void cree_dot(const Arbre a, FILE* out);
/**
 * Prend en paramètre un Arbre et un fichier
 * Ecrit dans le fichier les informations contenu dans l'arbre
 * au format dot
 */ 
 
#endif
