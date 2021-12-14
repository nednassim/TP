#include "machine.h"

// variables generales
LObarreF *F;
Buffer buf;

/*Le modele*/
// fonction retourne un champ de l'entete
int entete(LObarreF *F, int i) {
	switch (i) {
		case 1: {
			return(F->entete.nb);
			break;
		}
		case 2: {
			return(F->entete.tete);
			break;
		}
		case 3: {
			return (F->entete.queue);
			break;
		}
		case 4: {
			return (F->entete.cpt_libre);
			break;
		}
		case 5: {
			return (F->entete.cpt_inser);
			break;
		}
		case 6: {
			return (F->entete.cpt_supp);
			break;
		}
	}
}
 
// procedure pour  modifier l'entete
void Aff_entete(LObarreF *F,int i , int val) {
	switch (i) {
      case 1: {
         F->entete.nb = val;
         break;
      }
      case 2: {
         F->entete.tete = val;
         break;
      }
      case 3: {
         F->entete.cpt_queue= val;
         break;
      }
      case 4: {
         F->entete.cpt_libre = val;
         break;
      case 5: {
         F->entete.cpt_inser= val;
         break;
      }
  	   case 6: {
         F->entete.cpt_supp = val;
         break;
      }
   }
}

// procedure pour lire un buffer du fichier
void LireDir(LObarreF *F, int i , Buffer *buf) {
   fseek(F->fich, sizeof(Entete) + (i - 1) * sizeof(Buffer), SEEK_SET);
   fread(buf, sizeof(Buffer), 1, F->fich);
}

// procedure pour ecrire un buffer dans fichier
void EcrireDir(LObarreF *F, int i, Buffer buf) {
   fseek(F->fich, sizeof(Entete) + (i - 1) * sizeof(Buffer), SEEK_SET);
   fwrite(&buf, sizeof(Buffer), 1, F->fich);
}

// fonction pour ouvrir un fichier LObarreF
LObarreF *Ouvri(char *nom_fichier, char mode) {
	F = (LObarreF*) malloc(sizeof(LObarreF));
	if ((mode == 'a') || (mode == 'A')) {
		F->fich = fopen(nom_fichier, "rb+");
		if (F->fich != NULL) {
			rewind(F->fich);
			fread(&(F->entete), sizeof(Entete), 1, F->fich);
		} else {
			perror("Fichier mal ouvert \n");
			exit(1);
		}
	} else if ((mode == 'n') || (mode == 'N')) {
		F->fich = fopen(nom_fichier, "wb+");
		if (F->fich != NULL) {
			Aff_entete(F, 1, 0);
			Aff_entete(F, 2, 1);
			Aff_entete(F, 3, 1);
			Aff_entete(F, 4, 0);
			Aff_entete(F, 5, 0);
			Aff_entete(F, 6, 0);
			rewind(F->fich);
			fwrite(&(F->entete), sizeof(Entete), 1, F->fich);
		} else {
			perror("Fichier mal cree \n");
			exit(1);
		}
	} else {
		perror("Format d'ouverture non disponible\n");
		exit(1);
	}
	return (F);
}

// fonction pour fermer un fichier LObarreF
void Fermer(LObarreF *F) {
   rewind(F->fich);												   //	repositionnement en debut du fichier
   fwrite(&(F->entete), sizeof(Entete), 1, F->fich);		// eenregistrement de l'entete
   rewind(F->fich);													//	repositionnement den debut du fichier
	fclose(F->fich);													// fermeture du fichier
   free(F);																// liberation du pointeur fichier
}

// procedure pour allouer un bloc dans un fichier LObarreF
void Alloc_Bloc(TOVC *F) {
	Buffer *buf = malloc(sizeof(Buffer));	// allocation d'un buffer
	LireDir(F, entete(F, 3), buf);			// lecture du bloc queue
	buf->suiv = entete(F, 1) + 1;				// mise a jour du bloc queue au nouveau bloc queue
	EcrireDir(F, entete(F, 3), buf);			// ecriture du bloc dans le fichier
	Aff_entete(F, 3, entete(F, 1) + 1);		// mise a jour de la queue dans l'entete
	buf->suiv = -1;								//	mise a NIL du suivant de la queue
	buf->nb = 0;									// initialisation du nouveau bloc queue
	EcrireDir(F, entete(F, 3), buf);			// ecriture du nouveau bloc queueu
	Aff_entete(F, 1, entete(F, 1) + 1);		// mise a jour du nombre de bloc dans l'entete
}

/*Les fonction pour generer les champs aleatoirement*/

// fonction pour generer la matricule
int rand_matricule() {return (rand() % 999999 +  111111);}
// fonction pour generer le nom
char *rand_nom() { 
   static const char lettres[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
   char *nom = (char*) malloc (32 * sizeof(char));  
   for (int i = 0; i < 31; i++) {
      nom[i] = lettres[(int) (rand() % (sizeof(lettres) - 1))]; 
   } 
   nom[31] = '\0';                                                                                               
	return nom;          
}
// fonction pour generer le prenom
char *rand_prenom() {
   static const char lettres[] = "abcdefghijklmnopqrstuvwxyz";
   char *prenom = (char*) malloc (35 * sizeof(char));  
   for (int i = 0; i < 34; i++) {
      prenoom[i] = lettres[(int) (rand() % (sizeof(lettres) - 1))]; 
   } 
   prenom[34] = '\0';
	return prenom;
}
// fonction pour generer la date de naissance
char *date_naissance() {

}
// fonction pour generer la wilaya de naissance
int rand_wilaya() { return (rand() % 58 + 1);}
// fonction pour generer le groupe sanguin
int rand_groupe_sanguin() { return (rand() % 8 + 1);}
// fonction pour generer le grade
int rand_grade() { return (rand() % 17 + 1);}
// fonction pour genererla force armee
int rand_force_armeee() { return (rand() % 8 + 1);}
// fonction pour generer la region militaire
int region_militaire () { return (rand() % 6 + 1);}




/* Module pour chargement initial du fichier LObarreF */
void chargement_initial(char *nom_fichier, ) {




}
