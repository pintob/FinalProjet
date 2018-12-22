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
/*		### STRUCTURE ###		*/
typedef enum{
	NoParseError,
	InvalidLine
}CodeErreurParseur;
/*		### DECLARATION FONCTION ###	*/
int parseur(FILE* in, Data* data);
/**
 * Prend en paramètre un fichier au format
 * profileur fornit par la documentation.
 * 
 * Ecrit dans data les données contenu dans un ligne de log
 * 
 * Renvoie EOF si le fichier est vide
 * Renvoie InvalidLine en cas d'erreur de Parsing
 * Renvoie NoParseError si tout c'est bien passé.
 */ 
#endif
