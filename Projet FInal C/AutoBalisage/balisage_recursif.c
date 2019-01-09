#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static char* cree_commande(const char* fpath){
	int taille;
	char* commande;
	
	taille = strlen(fpath);
	commande = malloc(sizeof(char) * (17 + 2 * taille));
	if(NULL == commande)
		return NULL;
	strcpy(commande, "./balisage <");
	strcat(commande, fpath);
	strcat(commande, "> ");
	strcat(commande, fpath);
	strcat(commande, "_");
	return commande;
	
}

static int parcours(const char *fpath, const struct stat *sb, int tflag){
	int size;
	struct stat statbuf;
	char* temp;
	stat(fpath, &statbuf);

	if((S_IFDIR & statbuf.st_mode) != S_IFDIR){ /*if fpath is not a repertory*/
		size = strlen(fpath);
		if(size >= 2 && strcmp(&fpath[size-2], ".c") == 0){
			temp = cree_commande(fpath);
			if(temp != NULL){
				system(temp);
				remove(fpath);
				strcpy(temp, fpath);
				strcat(temp, "_");
				rename(temp, fpath);
				free(temp);
				printf("Balisage de %s\n", fpath);
			}
			else
				return 1;
		}
	}
	
	return 0;        
}

int main(int argc, char **argv){
	
	if(argc < 2){
		printf("Pas assez d'arguments\n");
		return 1;
	}
	
	if(ftw(argv[1] , parcours, FTW_D) == -1){
		perror("Repertoire invalide\n");
		exit(EXIT_FAILURE);
	}
	
	printf("Ce programme ajoute uniquement les balises PROFILE + return pour les fonctions VOID\n");
	printf("Vous n'avez plus qu'a ajouté le fichier contenant les macros de profileur\n");
	printf("ainsi que modifier vôtre makefile avec les options de compilation \n-L{chemin de vos macro} -\n");
	return 0;
}

