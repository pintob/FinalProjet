/**
 * \file Analyseur.h
 * \brief Génére une liste chaînée à partir d'un arbre
 * \author PINTO Bruno
 *
 * Génére une liste chaînée à partir d'un arbre et traiter son contenu
 *
 */

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
/**
 * \struct Liste
 * \brief liste chainé 
 * 
 * Liste est une structure qui contient toutes les informations
 * relative au temps d'utilisation/nombre d'appel d'une fonction
 * profiler
 */ 
	 
typedef struct _cel{
	struct _cel* suivant; /*!<  Element suivant */
	char* nom; /*!< Nom de la fonction */
	double temps_total /*!< Temps passé dans la fonction sans compter les appels fils */;
	unsigned int occ /*!< Nombre d'occurence */;
}Cellule, *Liste;

/*		### DECLARATION FONCTION ###	*/

void cree_stat(const Arbre in, FILE* out, int compar(const Liste lst1, const Liste lst2), Liste* lst);
/**
 * \fn void cree_stat(const Arbre in, FILE* out, int compar(const Liste lst1, const Liste lst2), Liste* lst);
 * \brief Ecrit dans un fichier et/ou Liste les informations relative à un arbre
 * \param in est un Arbre
 * out est le fichier sur lequelle sera écrit les informations
 * compar est une fonction de comparation entre deux Liste
 * lst est une liste chaîné par adresse
 * \return void
 * 
 * Ecrit sur le fichier out au format .log les informations
 * contenu dans in .
 * Replis aussi le contenu de lst avec le contenu de l'arbre a
 * Si out ou lst est NULL alors le paramètre est ignoré.
 * La Liste lst est trié par en respectant la fonction compar, si compar est 
 * égal à null la liste sera trié par ordre lexicographique.
 */
/*
 * TODO
 * void cree_stat(const Arbre in, Liste* lst);
 * int affiche_liste(const Liste lst);
 * int faffiche_liste(FILE* out, const Liste lst);
 * void tri_liste(Liste* lst, int compar(const Liste lst1, const Liste lst2));
 * 
 */ 

#endif
