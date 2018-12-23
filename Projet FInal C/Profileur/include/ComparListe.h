/**
 * \file ComparListe.h
 * \brief Fourni des Fonctions de comparaison entre Liste
 * \author PINTO Bruno
 *
 * Fourni des Fonctions de comparaison entre Liste
 *
 */

#ifndef __COMPARLISTE__
#define __COMPARLISTE__

/*		### BIBLIOTHEQUE ###		*/
#include <assert.h>

#include "Analyseur.h"
/*		### MACRO ###		*/

/*		### STRUCTURE ###		*/

/*		### DECLARATION FONCTION ###	*/
int compar_antilexico(Liste un , Liste deux);
/**
 * \fn int compar_antilexico(Liste un , Liste deux)
 * \brief Fonction de comparaion entre deux Liste
 */
int compar_minocc(Liste un, Liste deux);
/**
 * \fn int compar_minocc(Liste un, Liste deux)
 * \brief Fonction de comparaion entre deux Liste
 */
int compar_maxocc(Liste un, Liste deux);
/**
 * \fn int compar_maxocc(Liste un, Liste deux)
 * \brief Fonction de comparaion entre deux Liste
 */
int compar_tempsmax(Liste un , Liste deux);
/**
 * \fn int compar_tempsmax(Liste un , Liste deux)
 * \brief Fonction de comparaion entre deux Liste
 */
int compar_tempsmin(Liste un , Liste deux);
/**
 * \fn int compar_tempsmin(Liste un , Liste deux)
 * \brief CFonction de comparaion entre deux Liste
 */
int compar_tempsmoymax(Liste un, Liste deux);
/**
 * \fn int compar_tempsmoymax(Liste un, Liste deux)
 * \brief CFonction de comparaion entre deux Liste
 */
int compar_tempsmoymin(Liste un, Liste deux);
/**
 * \fn int compar_tempsmoymin(Liste un, Liste deux)
 * \brief Fonction de comparaion entre deux Liste
 */


#endif
