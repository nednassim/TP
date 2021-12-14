#pragma GCC optimize("-Ofast","-funroll-all-loops","-ffast-math")
#pragma GCC optimize("-fno-math-errno")
#pragma GCC optimize("-funsafe-math-optimizations")
#pragma GCC optimize("-freciprocal-math")
#pragma GCC optimize("-fno-trapping-math")
#pragma GCC optimize("-ffinite-math-only")
#pragma GCC optimize("-fno-stack-protector")
#pragma GCC target("sse4","avx2")
#include <immintrin.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <float.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <setjmp.h>
#include <signal.h>
#include <stdarg.h>
#include <stddef.h>
#include <time.h>

#ifdef LOCAL
#define debug(format, ...) { printf("[%s",#__VA_ARGS__);printf("] : ") ; printf(format"\n",__VA_ARGS__);} 
#else
#define debug(...) 42
#endif                                           


char *rand_nom() { 
	static const char lettres[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";          
	char *nom = (char*) malloc (32 * sizeof(char));
	for (int i = 0; i < 31; i++) {
		nom[i] = lettres[(int) (rand() % (sizeof(lettres) - 1))];
	}
	nom[31] = '\0';
	return nom;
}    

char *rand_date() {
	char *date = (char*) malloc (11 * sizeof(char));
	date[3] = rand() % 2 + 1;
	if (date[3] == 2 + '0') {
		date[2] = 0 + '0';
		date[1] = 0 + '0';
		date[0] = rand() % 4 + '0';
	} else if (date[3] ==  1 + '0') {
		date[2] = 9 + '0';
		date[1] = rand() % 6 + 4 + '0';
		date[0] = rand() % 10 + '0';
	}
	date[4] = '/';
	date[5] = rand() % 2 + '0';
	if (date[5] == 1 + '0') {
		date[6] = rand() % 2 + '0';
	} else if (date[4] == 0 + '0') {
		date[6] = rand() % 10 + '0';
	}
	date[7] = '/';
	date[8] =  rand() % 4 + '0';
	if (date[8] ==  3 + '0') {
		date[9] = rand() % 3 + '0';
	} else {
		date[9] = rand() % 10 + '0';
	}
	date[10] = '\0';
	return date;
}


int rand_wilaya() { return (rand() % 58 + 1);}     

int main () {
	static const char lettres[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";          
	for (int i = 0; i < 10; i++) {
		printf("%s\t", rand_nom());
		printf("%s\n", rand_date());
	}

	printf("\nTime elapsed : %.3f s.\n",1.0 * clock() /CLOCKS_PER_SEC);
	return 0;
}
