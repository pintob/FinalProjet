/**
 * \file Parseur.h
 * \brief Permet de parser des fichier.log
 * \author PINTO Bruno
 *
 * Permet de parser des fichier.log
 *
 */

#ifndef __PARSEUR__
#define __PARSEUR__

/*		### BIBLIOTHEQUE ###		*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "Data.h"
/*		### MACRO ###		*/
#define TAILLE_MAX_IDENT 256
/**
 * \def TAILLE_MAX_IDENT
 * Taille maximal d'un identificateur dans les fichiers à parser
 */ 
/*		### STRUCTURE ###		*/
/**
 * \enum CodeErreurParseur
 * \brief Constantes d'erreurs.
 *
 * CodeErreurParseur est une série de constantes prédéfinie la fonction parseur
 */
 
typedef enum{
	NoParseError, /*!< Pas d'erreur. */
	InvalidLine /*!< Ligne invalide */
}CodeErreurParseur;
/*		### DECLARATION FONCTION ###	*/
int parseur(FILE* in, Data* data);

/**
 * \fn int parseur(FILE* in, Data* data)
 * \brief  Prend en paramètre un fichier au format profileur fornit par la documentation.
 * \param in est le fichier au format .log ouvert en lecture
 * \param data à la fin de la fonction, si possible data contient les informations d'une ligne du fichier
 * \return EOF si le fichier a été entièrement lu
 *		   InvalidLine en cas d'erreur de Parsing
 *         NoParseError si tout c'est bien passé.
 */

#endif
