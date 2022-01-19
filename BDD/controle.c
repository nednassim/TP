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


typedef struct force_armee {
	int num;
	char nom[46];
} force_armee;

typedef struct grade {
	int num;
	char nom[24];
} grade;

typedef struct groupe_sanguin {
	int num;
	char nom[3];
} groupe_sanguin;

typedef struct region_militaire {
	int num;
	char nom[15];
} region_militaire;

typedef struct wilaya_naissance {
	int num;
	char nom[18];
} wilaya_naissance;


int main () {
	// Les fichiers textes
	FILE *F1 = fopen("force_armee", "r");			// ouverture du fichier des forces armees
	FILE *F2 = fopen("grade", "r");					// ouverture du fichier des grades
	FILE *F3 = fopen("groupe_sanguin", "r");		// ouverture du fichier des groupes sanguins
	FILE *F4 = fopen("region_militaire", "r");	// ouverture du fichier des regions militaire
	FILE *F5 = fopen("wilaya_naissance", "r");	// ouverture du wilayas de naissance
	// Les fichiers binaires
	FILE *F6 = fopen("force_armee.bin", "rb+");			// ouverture du fichier des forces armees binaire
	FILE *F7 = fopen("grade.bin", "rb+");					// ouverture du fichier des grades binaire
	FILE *F8 = fopen("groupe_sanguin.bin", "rb+");		// ouverture du fichier des groupes sanguins binaire
	FILE *F9 = fopen("region_militaire.bin", "rb+");	// ouverture du fichier des regions militaire binaire
	FILE *F10 = fopen("wilaya_naissance.bin", "rb+");	// ouverture du wilayas de naissance binaire

	// le menu
	printf("Les champs d'information disponible a manipuler :  \n");
	printf("			1) La force armee \n");
	printf("			2) Le grade \n");
	printf("			3) Le groupe sanguin \n");
	printf("			4) La region militaire \n");
	printf("			5) La wilaya de naissance \n");
	printf("Choisissez une option : ");
	int option;	
	scanf("%d", &option);
	switch(option) {
		case 1: {	// force armee
			printf("Les options disponibles : \n");
			printf("			1) Ajout une force armee \n");
			printf("			2) Suppression d'une force armee \n");
			printf("Choisissez une option : ");
			int opt;
			scanf("%d", &opt);
			switch(opt) {	// la modification est synchronisee dans le fichier texte et binaire
				case 1: {	// ajout d'une force armee
					break;
				}
				case 2: {	// suppression d'une force armee
					break;
				}
			}
			 break;		  
		}	  
		case 2: {	// grade
			printf("Les options disponibles : \n");
			printf("			1) Ajout un grade \n");
			printf("			2) Suppression un grade \n");
			printf("Choisissez une option : ");
			int opt;
			scanf("%d", &opt);
			switch(opt) {
				case 1: { 	// ajout un grade 
					break;
				}
					case 2: {	// suppression un grade 
					break;
				
				}
			}
   		break;		  
		}	  
		case 3: {	// groupe sanguin
			int opt;
			scanf("%d", &opt);
			switch(opt) {
				case 1: {
					break;
				}
				case 2: {
					break;
				}
			}
		   break;		  
		}	  
		case 4: {	// region militaire
   		printf("Les options disponibles : \n");
			printf("			1) Ajout d'une region militaire \n");
			printf("			2) Suppression d'une region militaire \n");
			printf("Choisissez une option : ");
			int opt;
			scanf("%d", &opt);
			switch(opt) {
				case 1: { 	// ajout d'une region militaire
					break;
				}
				case 2: {	// suppression d'une region militaire
					break;
				}
			}
			break;		  
		}	  
		case 5: {	// wilaya de naissance
   		printf("Les options disponibles : \n");
			printf("			1) Ajout d'une wilaya \n");
			printf("			2) Suppression d'une wilaya \n");
			printf("Choisissez une option : ");
			int opt;
			scanf("%d", &opt);
			switch(opt) {
				case 1: {  // ajout d'une wilaya 
					break;
				}
				case 2: {  // suppression d'une wilaya 
					break;
				}
			}
			break;		  
		}	  
	}

	fclose(F1);
	fclose(F2);
	fclose(F3);
	fclose(F4);
	fclose(F5);
	fclose(F6);
	fclose(F7);
	fclose(F8);	
	fclose(F9);
	fclose(F10);
	printf("\nTime elapsed : %.3f s.\n",1.0 * clock() /CLOCKS_PER_SEC);
	return 0;
}
