#ifndef __COMPARLISTE__
#define __COMPARLISTE__

/*		### BIBLIOTHEQUE ###		*/
#include <assert.h>

#include "Analyseur.h"
/*		### MACRO ###		*/

/*		### STRUCTURE ###		*/

/*		### DECLARATION FONCTION ###	*/
int compar_antilexico(Liste un , Liste deux);
int compar_minocc(Liste un, Liste deux);
int compar_maxocc(Liste un, Liste deux);
int compar_tempsmax(Liste un , Liste deux);
int compar_tempsmin(Liste un , Liste deux);
int compar_tempsmoymax(Liste un, Liste deux);
int compar_tempsmoymin(Liste un, Liste deux);


#endif
