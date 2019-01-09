#ifndef __MACRO__PROFILAGE__
#define __MACRO__PROFILAGE__

/*		### BIBLIOTHEQUE ###		*/
#include <stdio.h>
#include <time.h>

/*		### MACRO ###		*/
/**
 * La fonction ecrit_log ne doit pas être utilise en dehors des macros 
 * défini ci-dessous.
 * 
 * 
 * Le premier appel de PROFILE est extrement long (temps d'ouvrir le
 * fichier .log ainsi que quelque autre utilisation)
 * 
 * Il est donc conseillé de modifier son code distiné a été profiler
 * en ayant comme main:
 * 
 * int main(int argc, char** argv){
 * 		PROFILE
 * 		int valeur;
 * 		valeur = main2(argc, argv); 
 * 		return valeur;
 * } 
 * int main2(int argc, char** argv) étant vôtre ancien main
 */ 

void ecrit_log(const char* nom, int i);

#define PROFILE ecrit_log(__FUNCTION__, 1);
#define return ecrit_log("END", -1);\
			   return 



#endif

