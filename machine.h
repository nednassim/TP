#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>


#ifdef LOCAL
#define debug(format, ...) { printf("[%s",#__VA_ARGS__);printf("] : ") ; printf(format"\n",__VA_ARGS__);}
#else
#define debuf(...) 42
#endif

#define b 85	// le nombre maximal d'enregistrements dans un bloc

 // structure d'un enregistrement
typedef struct Tenreg { 
   int matricule;			  		 // la matricule (4 bytes)
	char nom[31];    		 		 // le nom (31 bytes)
   char prenom[34]; 				 // le prenom (34 bytes)
	char date_naissance[11];	 // la date de naissance (11 bytes)
	int wilaya_naissance; 		 // la wilaya de naissance (4 bytes)
	int groupe_sanguin;	    	 // le groupe sanguin (4 bytes)
	int grade;				 		 // le grade (4 bytes)
	int force_armee;				 // la force armee (4 bytes)
	int region_militaire;		 // la region militaire (4 bytes)
   // la taille de l'enregistrement est :  100 bytes
} Tenreg;

// structure d'un bloc
typedef struct Tbloc {
   Tenreg tab[b];  // un tableau d'enregistrements d'une capacite b (8500 bytes)
	int nb;         // nombre d'enregistrements dans tab (<= b)  (4 bytes)
	int suiv;		 // bloc suivant  (4 bytes)
   // la taille du bloc est : 8508 bytes
} Tbloc;

typedef struct Tbloc Buffer;	 // declaraion du tampon

// structure de l'entete
typedef struct Entete {
   int nb;     	 // nombre de blocs utilises (4 bytes)
	int tete; 		 // le pointeur tete	(4 bytes)
	int queue; 		 // le pointeur queue	(4 bytes)
   int cpt_inser;  // compteur d'insertions (4 bytes) 
   int cpt_supp;   // compteur de suppression (4 bytes) 
  	// la taille de l'entete est : 20 bytes
} Entete;

// structure du fichier LObarreF (fichier cu comme tableau, non ordonne avec enregistrements de taille fixe)
typedef struct LObarreF {
   FILE *fich;  // 12 bytes (8 bytes + 4 bytes du padding)
   Entete entete;  // 24 bytes
   // la taille de la structure du fichier est : 36 bytes
} LObarreF;


/* La machine abstraite d'un fichier LObarreF */
void LireDir(LObarreF *F, int i , Buffer *buf);   	 // procedure pour lire un buffer du fichier LObarreF
void EcrireDir(LObarreF *F, int i, Buffer buf);  	 // procedure pour ecrire un buffer dans fichier LObarreF
int entete(LObarreF *F, int i);    					    // fonction retourne un champ de l'entete
void Aff_entete(LObarreF *F,int i , int valeur);  	 // procedure pour modifier l'entete
LObarreF *Ouvrir(char nom_physique[20], char mode); // fonction pour ouvrir un fichier LObarreF
void Fermer(LObarreF *F);   							  	 // fonction pour fermer un fichier LObarreF
Buffer  *Alloc_Bloc(LObarreF *F); 					  	 // procedure pour allouer un bloc dans un fichier LObarreF
//void Chargement_Initial(char *nom_fichier, LObarreF *F, int N); 	 // procedure pour creer un fichier LObarreF

/* Les modules d'affichage */
void Afficher_Bloc(LObarreF *F,int i);    // procedure pour afficher un bloc dans un fichier LObarreF
void Afficher_Entete(LObarreF *F);    		// procedure pour afficher l'entete d'un fichier LObarreF
void Afficher_Fichier(char *nom_fichier);   		// procedure pour afficher un fichier LObarreF

