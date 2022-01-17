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
#include <openssl/sha.h>
#include "machine.h"

#ifdef LOCAL
#define debug(format, ...) { printf("[%s",#__VA_ARGS__);printf("] : ") ; printf(format"\n",__VA_ARGS__);}
#else
#define debug(...) 42
#endif

int main () {
	system("clear");
	printf("\t\t*********************************************************************************\n");
	printf("\t\t*\t\t\t\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\tEcole Nationale Superieure d'Informatique (ESI)\t\t\t*\n");
	printf("\t\t*\t\t\t\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\t\t\t  TP SFSD\t\t\t\t\t*\n");
	printf("\t\t*\t\tStructure simple de fichiers - Methode: LObarreF\t\t*\n");
	printf("\t\t*\t\t\t\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\t\tSupervise par : Dr Kermi Adel\t\t\t\t*\n");
	printf("\t\t*\t\t\t\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\t\t  NEDJAR Nassim	groupe 4\t\t\t\t*\n");
	printf("\t\t*\t\t\t\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\t\t\t\t\t\t\t\t\t*\n");
	printf("\t\t*********************************************************************************\n");

	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");


	printf("\nTime elapsed : %.3f s.\n",1.0 * clock() /CLOCKS_PER_SEC);
	return 0;
}
