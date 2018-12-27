#include <stdio.h>
#include <time.h>

void ecrit_log(const char* nom, int i){
	static int ouverture = 0;
	static FILE* out = NULL;
	struct timespec start;
	clock_gettime(CLOCK_REALTIME, &start);
	
	ouverture += i;
	
	if(out == NULL){
		remove("profile.log"); /* plus rapide de supprimer que d'écraser */
		out = fopen("profile.log", "w");
	}
	fprintf(out, "%s -- time : %ld.%lds\n", nom, start.tv_sec,start.tv_nsec / 1000);
	
	if(!ouverture){
		fclose(out);
	}
	
	
}

