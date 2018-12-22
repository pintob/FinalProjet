#include <stdio.h>

#include "lib/macro_profiler.h"

void fct(){
	PROFILE
	return;
}

int fibo(int n){
	PROFILE
	fct();
	int res;
	if (n == 0) {
		return 0;
	} 
	if (n == 1) {
		return 1;
	}
	
	res = fibo(n - 1) + fibo(n - 2);
	
	return res;
	
}

int main(int argc, char **argv){
	PROFILE
	
	fibo(4);
	return 0;
}

