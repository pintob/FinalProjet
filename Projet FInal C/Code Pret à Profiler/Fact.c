#include <stdio.h>

#include "lib/macro_profiler.h"



int fact(int n){
	PROFILE
	int res;
	if (n == 0) {
		return 1;
	} 
	if (n == 1) {
		return 1;
	}
	
	res = fact(n - 1) * n;
	
	return res;
	
}

int main(int argc, char **argv){
	PROFILE
	
	printf("%d\n", fact(10));
	return 0;
}

