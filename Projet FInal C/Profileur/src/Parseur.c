
/*		### BIBLIOTHEQUE ###		*/
#include "../include/Parseur.h"
#include "../include/Erreur.h"

/*		### DECLARATION MACRO PRIVEE###	*/
#define MILLION 1000000.
/*		### DECLARATION FONCTION PRIVEE###	*/

/*		### DEFINITION FONCTION ###		*/

int parseur(FILE* in, Data* data){
	char *ligne = NULL;
	char nom_fonction[TAILLE_MAX_IDENT]; /*Taille max d'un ident*/
	char *endptr;
	long int t1, t2;
	int taille_fct;
	size_t t;
	
	assert(in != NULL);
	assert(data != NULL);
	if(getline(&ligne, &t, in) == EOF)
		return EOF;
		
	if(sscanf(ligne, "%[a-zA-Z_][a-zA-Z_0-9]", nom_fonction) == 0){
		return InvalidLine;
	}
	taille_fct = strlen(nom_fonction); 
	if(strncmp(&ligne[taille_fct], " -- time : ", 11)){
		return InvalidLine;
	}
	t1 = strtoll(&ligne[taille_fct + 11], &endptr, 10); 
	
	if(endptr[0] != '.'){
		return InvalidLine;
	}
	t2 = strtoll(endptr+1, &endptr, 10);

	data->nom = malloc(strlen(nom_fonction) + 1);
	if(NULL == data->nom)
		FATAL_ERROR("Erreur d'allocation mémoire\n");
	strcpy(data->nom, nom_fonction);
	data->temps_total = t1 + t2 / MILLION ;
	free(ligne);
	return NoParseError;
}
