/**
 * \file main.c
 * \author PINTO Bruno
 *
 * 
 *
 */
#include <stdio.h>
#include <getopt.h>
 
#include "../include/Arbre.h"
#include "../include/Dot.h"
#include "../include/Parseur.h"
#include "../include/Analyseur.h"
#include "../include/Data.h"
#include "../include/Erreur.h"

/**
 * \fn int main (void)
 * \brief Entrée du programme.
 *
 * \return 0 - Arrêt normal du programme.
 * EXIT_FAILURE - erreur
 */

int main(int argc, char **argv){
	FILE* in , *out;
	Arbre a;
	int dot, opt;
	char *fichier;
	dot = 0;
	
	if(argc < 2){
		fprintf(stderr, "Erreur le fichier .log doit etre passer en arguments\n");
		exit(EXIT_FAILURE);
	}
	
	fichier = argv[1];
	while ((opt = getopt(argc, argv, "hd")) != -1){
		switch(opt){
		case('d'):{
			dot = 1;
			break;
		}
		case('h'):{
			system("man ./../fichier/man");
			return 0;
		}
		}
	}
	in = fopen(fichier, "r");
	if(in == NULL){
		fprintf(stderr, "Erreur le fichier %s ne peut pas être ouvert en lecture\n", fichier);
		exit(EXIT_FAILURE);
	}
	
	switch(cree_arbre(&a, in)){
		case(MemoryError):{
			fprintf(stderr, "Erreur plus de mémoire disponible\n");
			libere_arbre(a);
			fclose(in);
			exit(EXIT_FAILURE);
		}
		case(ParsingError):{
			fprintf(stderr, "Erreur le fichier %s n'est pas au mon format\n", argv[1]);
			libere_arbre(a);
			fclose(in);
			exit(EXIT_FAILURE);
		}
	}

	if(dot){
		out = fopen("visualise.dot","w");
		cree_dot(a, out);
		fclose(out);
	}
	
	#ifndef NDEBUG
		system("dot -Tpdf visualise.dot -o visualise.pdf"); 
		system(" evince visualise.pdf &");
	#endif /*NDEBUG*/
	
	cree_stat(a, stdout, NULL, NULL),
	fclose(in);
	libere_arbre(a);
	return 0;
}

