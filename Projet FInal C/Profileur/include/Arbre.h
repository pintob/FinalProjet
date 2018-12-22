#ifndef __ARBRE__
#define __ARBRE__

/*		### BIBLIOTHEQUE ###		*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "Data.h"
#include "Parseur.h"

/*		### MACRO ###		*/

/*		### STRUCTURE ###		*/

typedef unsigned int Id;

typedef struct _noeud{
		Id id;
		struct _noeud *frd, *fg, *pere;
		Data info;
}Noeud, *Arbre;

typedef enum{
	NoTreeError,
	MemoryError,
	ParsingError
}CodeErreurArbre;
/*		### DECLARATION FONCTION ###	*/

int cree_arbre(Arbre* a, FILE* in);
/**
 * Prend en paramètre un arbre ainsi qu'un fichier log au format
 * profileur fornit par la documentation.
 * 
 * Crée un Arbre en initialisant tous les champs
 * 
 * Renvoie ParsingError en cas d'erreur de parsing
 * Renvoie MemoryError en cas d'erreur d'allocation
 * Renvoie NoTreeError sinon
 */ 

void libere_arbre(Arbre a);
/**
 * Prend en paramètre un arbre et libère tout les emplacements mémoire
 * liée à l'arbre.
 */ 
 
Noeud* cherche_noeud(const Arbre a, Id id);
/**
 * Renvoie le Noeud de l'arber a qui a pour Id id
 * Renvoie NULL si aucun élément n'as pour Id id
 */ 

void ecriture_generique(const Arbre a, void* out, void(fct_ecriture)(void* out, const Data* donne));
/**
 * Prend en parametre un arbre, ainsi qu'un pointeur vers une structure
 * de donné `out` et une fonction qui prend en paramètre un point générique 
 * et un Data.
 * 
 * ecriture_generique appele fct_ecriture(out, donne) pour toutes les Data 
 * présent dans l'arbre en effectuant un parcourt prefixe
 */ 
 
void ecriture_generique_frere(const Noeud* noeud, void* out, void(fct_ecriture)(void* out, const Data* donne));
/**
 * Prend en parametre l'adresse d'un Noeud, ainsi qu'un pointeur vers une structure
 * de donné `out` et une fonction qui prend en paramètre un point générique 
 * et un Data.
 * 
 * ecriture_generique appele fct_ecriture(out, donne) pour toutes les Data 
 * présent dans les frères de noeud
 */ 
#endif
