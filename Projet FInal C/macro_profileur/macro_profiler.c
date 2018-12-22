#include <stdio.h>
#include <time.h>

#define MILLIARD 1000000000.

void ecrit_log(const char* nom, int i){
	static int ouverture = 0;
	static FILE* out = NULL;
	struct timespec start;
	clock_gettime(CLOCK_REALTIME, &start);
	
	ouverture += i;
	
	if(out == NULL){
		out = fopen("profile.log", "w+");
	}
	fprintf(out, "%s -- time : %fs\n", nom, start.tv_sec + (start.tv_nsec / MILLIARD));
	
	if(!ouverture){
		fclose(out);
	}
	
	
}
