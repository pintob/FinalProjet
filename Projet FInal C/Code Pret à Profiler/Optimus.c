/**
 * Programme fait en 1h30 pour être profiler
 * 
 * Factorise en élément premier les nombres passé en arguments
 * 
 * Génére un tableau de nombre premier en utilisant une version
 * bits à bits du crible d'Eratosthène 
 * 
 */
  
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "lib/macro_profiler.h"
typedef struct{
	uint64_t *array;
	unsigned int size;
}BArray;

typedef struct{
	int *array;
	unsigned int nb_elem;
	unsigned int size;
}IntArray;

void display_b(const BArray *bab){
	PROFILE
	int i;
	
	for(i = 0; i < sizeof(uint64_t) * sizeof(uint64_t) * bab->size; i++){
		if((bab->array[i/64] & (1ull << (i%64))) && 1)
			printf("%d ", i);
	}
	printf("\n");
	return;
}

void calcul_b(BArray* bab){
	PROFILE
	int i, j, sqrti;
	sqrti = sqrt(sizeof(uint64_t) * 8 * bab->size);
	if(bab->size == 0)
		return;
	bab->array[0] = (~(3ull));
	for(i = 1; i < bab->size; i++){
		bab->array[i] = (~(0ull));
	}
	for(i = 2; i < sqrti; i++){
		for(j = i * 2; j < sizeof(uint64_t) * 8 * bab->size; j += i){
			if((bab->array[j/64] & (1ull<< (j%64))))
				bab->array[j/64] = bab->array[j/64] & (~(1ull << (j%64)));
		}
	}
	return;
}

int create_barray(BArray* barray, unsigned int size){
	PROFILE
	barray->array = malloc(sizeof(uint64_t) * size);
	
	barray->size = size * (NULL != barray->array);
	
	return NULL == barray->array;
}

void free_intarray(IntArray* b){
	PROFILE
	free(b->array);
	return;
}

int create_intarray(IntArray* barray, unsigned int size){
	PROFILE
	barray->array = malloc(sizeof(int) * size);
	barray->nb_elem = 0;
	barray->size = size * (NULL != barray->array);
	
	return NULL == barray->array;
}

void display_initarray(const IntArray* array){
	PROFILE
	int i;
	
	for(i = 0; i < array->nb_elem; i++){
		printf("%d ", array->array[i]);
	}
	printf("\n");
	return;
}

void free_barray(BArray* b){
	PROFILE
	free(b->array);
	return;
}

void convert(const BArray* bab, IntArray* array){
	PROFILE
	int i;
	
	for(i = 0; i < sizeof(uint64_t) * sizeof(uint64_t) * bab->size; i++){
		if((bab->array[i/64] & (1ull << (i%64))) && 1)
			array->array[array->nb_elem++] = i;
	}
	return;
}

void analyse(const IntArray* array, int number){
	PROFILE
	int i;
	
	
	if(number <= 1){
		printf("%d is not valid\n", number);
		return;
	}
	printf("\t%d:\n", number);
	printf("List of factor:");

	for(i = 0; i < array->nb_elem && number != 1; i++){
		if(number % array->array[i] == 0){
			printf("%d ", array->array[i]);
			number /= array->array[i];
			i--;
		}
	}
	if(number != 1)
		printf("%d ", number);
	printf("\n============================================================\n");
	return;
}

int main(int argc, char **argv){
	PROFILE
	int max, i, temp;
	BArray bab;
	IntArray array;
	
	if(argc < 2){
		fprintf(stderr, "Error not enough arg\"n");
		exit(EXIT_FAILURE);
	} 
	for(i = 2, max = atoi(argv[1]); i < argc; i++){
		temp = atoi(argv[i]);
		if(temp > max){
			max = temp;
		}
	}
	
	if(create_barray(&bab, sqrt(max)/64 + 1)){
		fprintf(stderr, "Error not enough mémory\"n");
		exit(EXIT_FAILURE);
	}
	
	calcul_b(&bab);
	if(create_intarray(&array, sqrt(max))){
		fprintf(stderr, "Error not enough mémory\"n");
		exit(EXIT_FAILURE);
	}

	convert(&bab, &array);
	free_barray(&bab);
/*	display_initarray(&array);*/
	
	for(i = 1; i < argc; i++){
		temp = atoi(argv[i]);
		if(temp == 0){
			printf("\t%s is not valid\n", argv[i]);
		}
		else 
			analyse(&array, temp);
	}
	free_intarray(&array);
	
	return 0;
}

