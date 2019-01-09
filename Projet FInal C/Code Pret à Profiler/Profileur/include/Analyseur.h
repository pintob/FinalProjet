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

void cree_stat(const Arbre in, Liste* lst);
/**
 * \fn void cree_stat(const Arbre in, Liste* lst)
 * \brief Ecrit dans une liste les informations relative à un arbre
 * \param in est un Arbre
 * \param lst est une liste
 * \return void
 * 
 * Replis aussi le contenu de lst avec le contenu de l'arbre a
 */
 
void liberer_liste(Liste* lst);
/**
 * \fn void liberer_liste(Liste* lst)
 * \brief libère tous les éléments d'une lsite
 * \param lst liste à libérer
 * \return void
 */

int affiche_liste(const Liste lst, double temps_total);
/**
 * \fn int affiche_liste(const Liste lst, double temps_total)
 * \brief affiche le contenu d'une liste sur la sorti standard
 * \param lst liste contenant les informations
 * \param temps_total le temps total de la liste (normalement contenu dans l'arbre)
 * \return le nombre d'élément afficher
 */ 

int faffiche_liste(FILE* out, const Liste lst, double temps_total);
/**
 * \fn int faffiche_liste(FILE* out, const Liste lst, double temps_total)
 * \brief ecrit le contenu d'une liste sur un fichier
 * \param lst liste contenant les informations
 * \param temps_total est le temps total de la liste (normalement contenu dans l'arbre)
 * \param out est le ficher de sortiouvert en écriture
 * \return le nombre d'élément écrit
 */ 

void tri_fusion(Liste *lst, int compar(Liste, Liste));
/**
 * \fn void tri_fusion(Liste *lst, int compar(Liste, Liste))
 * \brief tri une liste chaîné par adresse
 * \param lst la liste à trié
 * \param compar la fonction de comparaison entre deux elem, ComparListe en fourni déjà plusieurs
 * \return void
 */ 

/*
 * void tri_liste(Liste* lst, int compar(const Liste lst1, const Liste lst2));
 * 
 */ 

#endif
