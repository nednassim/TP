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


typedef struct Tenreg {
   int matricule;              // la matricule (4 bytes)
   char nom[31];               // le nom (31 bytes)
   char prenom[34];            // le prenom (34 bytes)
   char date_naissance[11];    // la date de naissance (11 bytes)
   int wilaya_naissance;       // la wilaya de naissance (4 bytes)
   int groupe_sanguin;         // le groupe sanguin (4 bytes)
   int grade;                  // le grade (4 bytes)
   int force_armee;            // la force armee (4 bytes)
   int region_militaire;       // la region militaire (4 bytes)
   // la taille de l'enregistrement est :  100 bytes
} Tenreg;



int rand_matricule() {return (rand() % 999999 +  111111);}

char *rand_nom() {
   static const char lettres[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

	char *nom = (char*) malloc (31 * sizeof(char));
   int taille = rand() % 28 + 3;
	for (int i = 0; i < taille; i++) {
      nom[i] = lettres[(int) (rand() % (sizeof(lettres) - 1))];
   }
   nom[taille] = '\0';
   return nom;
}
// fonction pour generer le prenom
char *rand_prenom() {
   static const char lettres[] = "abcdefghijklmnopqrstuvwxyz";

   char *prenom = (char*) malloc (34 * sizeof(char));
   int taille = rand() % 30 + 4;
   for (int i = 0; i < taille; i++) {
      prenom[i] = lettres[(int) (rand() % (sizeof(lettres) - 1))];
   }
   prenom[taille] = '\0';
   return prenom;
}

char *rand_date() {
	char *date = (char*) malloc (11 * sizeof(char));
	date[0] = rand() % 2 + 1 + '0';
	if (date[0] == 2 + '0') {
		date[1] = 0 + '0';
		date[2] = 0 + '0';
		date[3] = rand() % 4 + '0';
	} else if (date[0] ==  1 + '0') {
		date[1] = 9 + '0';
		date[2] = rand() % 6 + 4 + '0';
		date[3] = rand() % 10 + '0';
	}
	date[4] = '/';
	date[5] = rand() % 2 + '0';
	if (date[5] == 1 + '0') {
		date[6] = rand() % 2 + 1 + '0';
	} else if (date[5] == 0 + '0') {
		date[6] = rand() % 9 + 1 + '0';
	}
	date[7] = '/';
	char *annee = (char*) malloc (5 * sizeof(char));
	strncpy(annee, date, 4);
	annee[4] = '\0';
	if (atoi(annee) % 4 == 0) {	// une annee bissextile
		if ((date[5] == 0 + '0') && (date[6] == 2 + '0')) {	// mois de fevrier
			date[8] =  rand() % 3 + '0';
			if (date[8] ==  3 + '0') {
				date[9] = rand() % 2 + '0';
			} else {
				date[9] = rand() % 9 + 1 + '0';
			}
		} else {
			date[8] =  rand() % 4 + '0';
			if (date[8] ==  3 + '0') {
				date[9] = rand() % 2 + '0';
			} else {
				date[9] = rand() % 9 + 1 + '0';
			}
		}
	} else {		// une annee non-bissextile
		date[8] =  rand() % 4 + '0';
		if (date[8] ==  3 + '0') {
			date[9] = rand() % 2 + '0';
		} else {
			date[9] = rand() % 9 + 1 + '0';
		}
	}
	free(annee);
	date[10] = '\0';
	return date;
}
int rand_wilaya() { return (rand() % 58 + 1);}
// fonction pour generer le groupe sanguin
int rand_groupe_sanguin() { return (rand() % 8 + 1);}
// fonction pour generer le grade
int rand_grade() { return (rand() % 17 + 1);}
// fonction pour genererla force armee
int rand_force_armee() { return (rand() % 8 + 1);}
// fonction pour generer la region militaire
int rand_region_militaire () { return (rand() % 6 + 1);}


Tenreg creer_personne() {
	Tenreg personne;
	personne.matricule = rand_matricule();
	strcpy(personne.nom, rand_nom());
	strcpy(personne.prenom, rand_prenom());
	strcpy(personne.date_naissance, rand_date());
	personne.wilaya_naissance = rand_wilaya();
	personne.groupe_sanguin = rand_groupe_sanguin();
	personne.grade = rand_grade();
	personne.force_armee = rand_force_armee();
	personne.region_militaire = rand_region_militaire();
	return personne;
}

void afficher_pers(Tenreg personne, int i) {
	printf("Le personnel : %d\n", i);
	printf("Matricule : %d\n", personne.matricule);
	printf("Nom : %s\n", personne.nom);
	printf("Prenom : %s\n", personne.prenom);
	printf("Date de naissance : %s\n", personne.date_naissance);
	printf("Wilaya de naissance : %d\n", personne.wilaya_naissance);
	printf("Groupe sanguin: %d\n", personne.groupe_sanguin);
	printf("Grade : %d\n", personne.grade);
	printf("Force armee : %d\n", personne.force_armee);
	printf("Region militaire : %d\n", personne.region_militaire);
}


int main () {
	srand(time(NULL));
	for (int i = 0; i < 10; i ++) {
		Tenreg pers = creer_personne(); 
		afficher_pers(pers, i + 1);
		printf("#************************#\n");
	}
	printf("\nTime elapsed : %.3f s.\n",1.0 * clock() /CLOCKS_PER_SEC);
	return 0;
}
