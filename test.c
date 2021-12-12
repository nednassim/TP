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

const char wilaya_naissance[58][32] = {
"Adrar","Chlef","Laghouat","Oum El Bouaghi","Batna","Béjaïa","Biskra","Béchar","Blida","Bouïra","Tamanrasset","    Tébessa","Tlemcen","Tiaret","Tizi Ouzou","Alger","Djelfa","Jijel","Sétif","Saïda","Skikda","Sidi Bel Abbès","Annab    a","Guelma","Constantine","Médéa","Mostaganem","M'Sila","Mascara","Ouargla","Oran","El Bayadh","Illizi","Bordj Bou     Arréridj","Boumerdès","El Tarf","Tindouf","Tissemsilt","El Oued","Khenchela","Souk Ahras","Tipaza","Mila","Aïn De    fla","Naâma","Aïn Témouchent","Ghardaïa","Relizane","El M'Ghair","El Menia","Ouled Djellal","Bordj Baji Mokhtar","    Béni Abbès","Timimoun","Touggourt","Djanet","In Salah","In Guezzam"

};



const char groupe_sanguin[8][3] = {"O+","A+","B+","O-","A-","AB+","B-","AB-"};

const char grade[17][30] = {"Général de corps d’armée"," Général-Major","Général","Colonel","Lieutenant-colonel","Commandant","Capitaine","Lieutenant","Sous-lieutenant","Aspirant","Adjudant-chef","Adjudant","Sergent-chef","Sergent","Caporal-chef","Caporal","Djoundi"
};

const char force_armee[8][50] = {
	"Armée de terre","Armée de l’air","Marine nationale","Défense aérienne du territoire","Gendarmerie nationale","Garde républicaine","Département du renseignement et de la sécurité","Santé militaire"
};

const char region_militaire[6][16] = {
	"1RM-Blida","2RM-Oran","3RM-Béchar","4RM-Ouargla","5RM-Constantine","6RM-Tamanrasset"
};

 // structure d'un enregistrement                                                                                 
typedef struct Tenreg {     
	char  matricule[7];  // 7 * 1 = 7 bytes                                                                        
	char nom[20];     // 20 * 1 = 20 bytes      
	char prenom[20];  // 20 * 1 = 20 bytes                                                                         
	char date_naissance[12];   // 12 * 1 = 12 bytes                                                                
	char wilaya_naissance[32];   // 33 * 1 = 33 bytes                                                              
	char groupe_sanguin[3];  // 3 * 1 = 3 bytes                                                                    
	char grade[30];   // 30 * 1 = 30 bytes                    
	char force_armee[50];   // 50 * 1 = 50 bytes     
	char region_militaire[16];  // 16 * 1 = 16 bytes                                                               
  // la taille de l'enregistrement est :  bytes                                                                  
} Tenreg;   

                                                                                                              
#ifdef LOCAL
#define debug(format, ...) { printf("[%s",#__VA_ARGS__);printf("] : ") ; printf(format"\n",__VA_ARGS__);}
#else
#define debug(...) 42
#endif

int main () {
	printf("%d", (int) sizeof(Tenreg));

	printf("\nTime elapsed : %.3f s.\n",1.0 * clock() /CLOCKS_PER_SEC);
	return 0;
}
