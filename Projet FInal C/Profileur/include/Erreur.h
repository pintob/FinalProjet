#ifndef __ERREUR__
#define __ERREUR__

/*		### BIBLIOTHEQUE ###		*/

#include <stdio.h>
#include <stdlib.h>

/*		### MACRO ###		*/
#define ERROR(STR) fprintf(stderr, "%s ligne: %d dans %s\n", STR, __LINE__, __FILE__);
#define FATAL_ERROR(STR) {fprintf(stderr, "%s ligne: %d dans %s\n", STR, __LINE__, __FILE__); \
								exit(EXIT_FAILURE);}

#endif
