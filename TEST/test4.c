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

// la structure d'une case de la table d'index
typedef struct index {
	int cle;
	int adr;
	int age;
	int grade;
	int force_armee;
	int region_militaire;
} index;

 
void creer_table(int N) {
// Module pour chargement initial du fichier LObarreF 
void Chargement_Initial(char *nom_fichier, int N) {
   Tenreg personnel;
   int i, j;
   i = 1;
   j = 0;
   F = Ouvrir(nom_fichier, 'N');
	
	index *table = (index*) malloc (N * sizeof(index));	// declaration de la table d'index;
   for (int k = 0; k < N; k++) {
      personnel = creer_perso();
		table[k]->cle = personnel.matricule;
		table[k]->adr = k;
      char *annee = (char*) malloc (5 * sizeof(char));
      strncpy(annee, personnel.date_naissance, 4);
      annee[4] = '\0';
		table[k]->age = 2022 - atoi(annee);
		free(annee);

		table[k]->grade = personnel.grade;
	   table[k]->force_armee = personnel.force_armee; 
		table[k]->region_militaire = region_militaire;



	   if (j < b) {   // espace suffisant dans ce bloc 
         buf.tab[j] = personnel;
         j++;
      } else {       //espace insuffisant dans ce bloc
         buf.nb = j;
         buf.suiv = i + 1;
         EcrireDir(F, i, buf);
         buf.tab[0] = personnel;
         i++;
         j = 1;
      }
   }

   buf.nb = j;    // le dernier bloc
   buf.suiv = -1;
   EcrireDir(F, i, buf);
   Aff_entete(F, 1, i);    // mise a jour du nombre de blocs
   Aff_entete(F, 3, i);    // mise a jour du dernier bloc
   Aff_entete(F, 4, N);    // mise a jour du compteur d'insertion

   Fermer(F);
}




}


	printf("\nTime elapsed : %.3f s.\n",1.0 * clock() /CLOCKS_PER_SEC);
	return 0;
}
