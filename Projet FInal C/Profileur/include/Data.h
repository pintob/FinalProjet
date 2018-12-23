/**
 * \file Data.h
 * \brief Stock les informations relative à un noeud
 * \author PINTO Bruno
 *
 * Stock les informations relative à un noeud
 *
 */

#ifndef __DATA__
#define __DATA__

/*		### BIBLIOTHEQUE ###		*/
#include <stdio.h>
#include <assert.h>

/*		### MACRO ###		*/

/*		### STRUCTURE ###		*/
/**
 * \struct Data
 * \brief Stockage de donnée
 * 
 * Data contient des informations relative à un appel de fonction
 */ 
	 
typedef struct{
	double temps_total; /*!< Temps total passé dans la fonction */
	double temps_seul; /*!< Temps passé dans la fonction sans compter les appels fils */
	char* nom; /*!< nom de la fonction */
}Data;
/*		### DECLARATION FONCTION ###	*/

void affiche_data(const Data* data);
/**
 * \fn void affiche_data(const Data* data)
 * \brief affiche data sur la sortie standard
 * \param data: donnée à afficher
 * \return void
 */

#endif
