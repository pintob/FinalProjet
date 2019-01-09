/**
 * \file main.c
 * \author PINTO Bruno
 */

 
#include <stdio.h>
#include <getopt.h>

#include "../include/Arbre.h"
#include "../include/Dot.h"
#include "../include/Parseur.h"
#include "../include/Analyseur.h"
#include "../include/Data.h"
#include "../include/Erreur.h"
#include "../include/API.h"
#include "../lib/macro_profiler.h"

#define NDEBUG

/**
 * \fn int main (int argc, char **argv)
 * \brief Entrée du programme.
 *
 * \return 0 - Arrêt normal du programme.
 * \return EXIT_FAILURE - erreur
 */

int main(int argc, char **argv){
	PROFILE
	FILE* in , *out;
	Arbre a = NULL;
	int dot, opt, api;
	char *fichier;
	Liste lst = NULL;
	dot = 0;
	api = 0;
	if(argc < 2){
		fprintf(stderr, "Erreur le fichier .log doit etre passer en arguments\n");
		exit(EXIT_FAILURE);
	}
	
	fichier = argv[1];
	while ((opt = getopt(argc, argv, "hdg")) != -1){
		switch(opt){
		case('d'):{
			dot = 1;
			break;
		}
		case('g'):{
			api = 1;
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
	
	cree_stat(a, &lst);
	affiche_liste(lst, a->info.temps_total);
	fclose(in);
	if(api){
		affiche_arbre(a);
	}
	libere_arbre(a);
	liberer_liste(&lst);
	return 0;
}

