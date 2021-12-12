#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>


#ifdef LOCAL
#define debug(format, ...) { printf("[%s",#__VA_ARGS__);printf("] : ") ; printf(format"\n",__VA_ARGS__);}
#else
#define debuf(...) 42
#endif

const char wilaya_naissance[58][32] = {
	"Adrar","Chlef","Laghouat","Oum El Bouaghi","Batna","Béjaïa","Biskra","Béchar","Blida","Bouïra","Tamanrasset","Tébessa","Tlemcen","Tiaret","Tizi Ouzou","Alger","Djelfa","Jijel","Sétif","Saïda","Skikda","Sidi Bel Abbès","Annaba","Guelma","Constantine","Médéa","Mostaganem","M'Sila","Mascara","Ouargla","Oran","El Bayadh","Illizi","Bordj Bou Arréridj","Boumerdès","El Tarf","Tindouf","Tissemsilt","El Oued","Khenchela","Souk Ahras","Tipaza","Mila","Aïn Defla","Naâma","Aïn Témouchent","Ghardaïa","Relizane","El M'Ghair","El Menia","Ouled Djellal","Bordj Baji Mokhtar","Béni Abbès","Timimoun","Touggourt","Djanet","In Salah","In Guezzam"
};

const char groupe_sanguin[8][3] = {"O+","A+","B+","O-","A-","AB+","B-","AB-"};

const char grade[17][30] = {"Général de corps d’armée"," Général-Major","Général","Colonel","Lieutenant-colonel","    Commandant","Capitaine","Lieutenant","Sous-lieutenant","Aspirant","Adjudant-chef","Adjudant","Sergent-chef","Serge    nt","Caporal-chef","Caporal","Djoundi"
};

const char force_armee[8][50] = {
   "Armée de terre","Armée de l’air","Marine nationale","Défense aérienne du territoire","Gendarmerie nationale","    Garde républicaine","Département du renseignement et de la sécurité","Santé militaire"
};

const char region_militaire[6][16] = {
   "1RM-Blida","2RM-Oran","3RM-Béchar","4RM-Ouargla","5RM-Constantine","6RM-Tamanrasset"
};

#define b 1024	// la taille maximal d'un bloc

 // structure d'un enregistrement
typedef struct Tenreg { 
   char	matricule[7];	  		 // la matricule (7 bytes)
	char nom[20];    		 		 // le nom (20 bytes)
   char prenom[20]; 				 // le prenom (20 bytes)
	char date_naissance[12];	 // la date de naissance (12 bytes)
	char wilaya_naissance[32];  // la wilaya de naissance (32 bytes)
	char groupe_sanguin[3];	    // le groupe sanguin (3 bytes)
	char grade[30];				 // le grade (30 bytes)
	char force_armee[50];		 // la force armee (50 bytes)
	char region_militaire[16];	 // la region militaire (16 bytes)
   // la taille de l'enregistrement est :  190 bytes
} Tenreg;

// structure d'un bloc
typedef struct Tbloc {
   Tenreg tab[b];  // un tableau d'enregistrements d'une capacite b (1024 * 190 = 194560 bytes)
   int nb;         // nombre d'enregistrements dans tab (<= b)  (4 bytes)
	int suiv;		 // bloc suivant  (4 bytes)
   // la taille du bloc est : 194568 bytes
} Tbloc;

typedef struct Tbloc Buffer;	 // declaraion du tampon
// structure de l'entete
typedef struct Entete {
   int nb;     	 // nombre de bloc utilises (4 bytes)
	int tete; 		 // le pointeur tete	(4 bytes)
	int queue; 		 // le pointeur queue	(4 bytes)
	int libre;	 	 // la position libre du bloc queue (4 bytes)
   int cpt_inser;  // compteur d'insertions (4 bytes) 
   int cpt_supp;   // compteur d'insertions (4 bytes) 
  	// la taille de l'entete est : 24 bytes
} Entete;

// structure du fichier LObarreF (fichier cu comme tableau, non ordonne avec enregistrements de taille fixe)
typedef struct LObarreF {
   FILE *fichier;  // 12 bytes (8 bytes + 4 bytes du padding)
   Entete entete;  // 24 bytes
   // la taille de la structure du fichier est : 36 bytes
} LObarreF;


/* La machine abstraite d'un fichier LObarreF */
void LireDir(LObarreF *fichier, int i , Buffer *buf);   // procedure pour lire un buffer du fichier LObarreF
void EcrireDir(LObarreF *fichier, int i, Buffer *buf);  // procedure pour ecrire un buffer dans fichier LObarreF
int entete(LObarreF *fichier, int i);    					  // fonction retourne un champ de l'entete
void Aff_entete(LObarreF *fichier,int i , int valeur);  // procedure pour modifier l'entete
LObarreF *Ouvrir(char nom_physique[20], char mode);     // fonction pour ouvrir un fichier LObarreF
void Fermer(LObarreF *fichier);   							  // fonction pour fermer un fichier LObarreF
void Alloc_Bloc(LObarreF *fichier); 						  // procedure pour allouer un bloc dans un fichier LObarreF
void Creation_Fichier(LObarreF *fichier,int n);  		  // procedure pour creer un fichier LObarreF

/* Les modules d'affichage */

void Afficher_Bloc(LObarreF *fichier,int i);    // procedure pour afficher un bloc dans un fichier LObarreF
void Afficher_entete(LObarreF *fichier);    		// procedure pour afficher l'entete d'un fichier LObarreF
void Afficher_Fichier(LObarreF *fichier);   		// procedure pour afficher un fichier LObarreF


