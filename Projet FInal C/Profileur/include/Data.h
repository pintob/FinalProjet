#ifndef __DATA__
#define __DATA__

/*		### BIBLIOTHEQUE ###		*/
#include <stdio.h>
#include <assert.h>

/*		### MACRO ###		*/

/*		### STRUCTURE ###		*/
typedef struct{
	double temps_total;
	double temps_seul;
	char* nom;
}Data;
/*		### DECLARATION FONCTION ###	*/

void affiche_data(const Data* data);
/**
 * Affiche data sur la sorti standard 
 */ 

#endif
