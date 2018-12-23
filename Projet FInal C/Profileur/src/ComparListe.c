/**
 * \file ComparListe.c
 * \brief Fourni des Fonctions de comparaison entre Liste
 * \author PINTO Bruno
 *
 * Fourni des Fonctions de comparaison entre Liste
 *
 */
 
/*		### BIBLIOTHEQUE ###		*/
#include "../include/ComparListe.h"
/*		### DECLARATION FONCTION PRIVEE###	*/

/*		### DEFINITION FONCTION ###		*/


int compar_tempsmax(Liste un , Liste deux){
	return (un->temps_total < deux->temps_total)?-1:1;
}

int compar_tempsmin(Liste un , Liste deux){
	return (un->temps_total > deux->temps_total)?-1:1;
}

int compar_antilexico(Liste un , Liste deux){
	return -strcmp(un->nom, deux->nom);
}

int compar_maxocc(Liste un, Liste deux){
	return un - deux;
}

int compar_minocc(Liste un, Liste deux){
	return deux - un;
}

int compar_tempsmoymax(Liste un, Liste deux){
	return ((un->temps_total/un->occ) > (deux->temps_total/un->occ))?-1:1;
}

int compar_tempsmoymin(Liste un, Liste deux){
	return ((un->temps_total/un->occ) < (deux->temps_total/un->occ))?-1:1;
}
