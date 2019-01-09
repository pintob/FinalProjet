/**
 * \file Arbre.h
 * \brief Génére et effectue des opération sur un arbre 
 * \author PINTO Bruno
 *
 * Permet de crée un arbre à partir d'un fichier à parser.
 * Permet aussi d'en lire le contenu
 *
 */

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


/**
 * \struct Arbre
 * \brief Arbre Fils-Gauche Frère-Droit
 * 
 * Arbre reproduit l'arbre d'appel des fonctions d'un code
 * profiler
 */ 
 
typedef struct _noeud{
		unsigned char id[3]; /*!< identifiant (unique) du noeud */
		struct _noeud *frd; /*!< Frère droit  */
		struct _noeud *fg; /*!< Fils Gauche */
		struct _noeud *pere; /*!< Noeud Père (NULL = Racine) */
		Data info;	 /*!< Information relative au noeud */
}Noeud, *Arbre;
 
 
/**
 * \enum CodeErreurArbre
 * \brief Constantes d'erreurs.
 *
 * CodeErreurArbre est une série de constantes prédéfinie pour la fonction cree_arbre
 */
 
typedef enum{
	NoTreeError, /*!< Pas d'erreur. */
	MemoryError, /*!< Plus de mémoire. */
	ParsingError /*!< Erreur dans le parsing. */
}CodeErreurArbre;
/*		### DECLARATION FONCTION ###	*/

int cree_arbre(Arbre* a, FILE* in);
/**
 * \fn int cree_arbre(Arbre* a, FILE* in)
 * \brief  Crée un Arbre en initialisant tous les champs
 * \param  a est l'adresse de l'arbre où seront écrite les informations
 * \param  in est un fichier ouvert en lecture au format .log
 * \return ParsingError en cas d'erreur de parsing
 * \return MemoryError en cas d'erreur d'allocation
 * \return  NoTreeError en cas de bon déroulement du programme
 */

void libere_arbre(Arbre a);
/**
 * \fn void libere_arbre(Arbre a)
 * \brief libère tous les éléments d'un arbre
 * \param a arbre à libérer
 * \return void
 */
 
 
Noeud* cherche_noeud(const Arbre a, unsigned char id[3]);
/**
 * \fn Noeud* cherche_noeud(const Arbre a, Id id)
 * \brief Recherche un noeud en fonction de son id
 * \param a Arbre cible
 * \param id est l'identifiant du noeud rechercher
 * \return le Noeud de l'arbre a ayant pour Id id
 * \return NULL si aucun élément n'as pour Id id
 */

void ecriture_generique(const Arbre a, void* out, void(fct_ecriture)(void* out, const Data* donne));
/**
 * \fn void ecriture_generique(const Arbre a, void* out, void(fct_ecriture)(void* out, const Data* donne))
 * \brief écrit les données stockées dans un arbre
 * \param a arbre que l'on va parcourir
 * \param out pointeur vers une structure de donnée `out` 
 * \param fct_ecriture fonction fct_ecriture qui prend en paramètre un pointeur générique et une Data.
 * \return void
 * 
 * ecriture_generique appele fct_ecriture(out, Data) pour toutes les Data 
 * présent dans l'arbre en effectuant un parcours préfixe
 */
 
void ecriture_generique_frere(const Noeud* noeud, void* out, void(fct_ecriture)(void* out, const Data* donne));
/**
 * \fn void ecriture_generique_frere(const Noeud* noeud, void* out, void(fct_ecriture)(void* out, const Data* donne));
 * \brief écrit les données stockées dans les frères d'un noeud
 * \param noeud est le noeud dont on va parcourir les frères
 * \param out pointeur vers une structure de donnée `out` 
 * \param fct_ecriture fonction fct_ecriture qui prend en paramètre un pointeur générique et une Data.
 * \return void
 * ecriture_generique appele fct_ecriture(out, donne) pour toutes les Data 
 * présent dans les frères du noeud
 */
#endif
