/**
 * \file Dot.h
 * \brief Permet de généré des fichier dot
 * \author PINTO Bruno
 *
 * Crée des fichiers dot à partir d'Arbres
 *
 */

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
 * \fn void cree_dot(const Arbre a, FILE* out)
 * \brief  Crée un fichier dot à partir d'un Arbre
 * \param Prend en paramètre un arbre ainsi qu'un fichier ouvert en écriture
 * \return ParsingError en cas d'erreur de parsing
 *         MemoryError en cas d'erreur d'allocation
 *         NoTreeError sinon
 * 
 * Cree un dot à partir de l'arbre a
 */

 
#endif
