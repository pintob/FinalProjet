#ifndef __MACRO__PROFILAGE__
#define __MACRO__PROFILAGE__

/*		### BIBLIOTHEQUE ###		*/
#include <stdio.h>
#include <time.h>

/*		### MACRO ###		*/


extern void ecrit_log(const char* nom, int i);

#define PROFILE ecrit_log(__FUNCTION__, 1);
#define return ecrit_log("END", -1);\
			   return 



#endif

