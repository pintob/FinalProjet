#include <stdio.h>

#include "lib/macro_profiler.h"



int fibo(int n){
	PROFILE
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
	
	printf("%d\n", fibo(20));
	return 0;
}

