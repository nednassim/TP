#include "machine.c"

// variables generales
LObarreF *F;	// fichier de structure LObarreF
Buffer buf;		// region tampon dans la MC

/*Les fonction pour generer les champs aleatoirement*/
// fonction pour generer la matricule
int rand_matricule() {return (rand() % 888889 +  111111);}

// fonction pour generer le nom
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
// fonction pour generer la date de naissance
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
   if (atoi(annee) % 4 == 0) {   // une annee bissextile
      if ((date[5] == 0 + '0') && (date[6] == 2 + '0')) {   // mois de fevrier
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
   } else {    // une annee non-bissextile
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
// fonction pour generer la wilaya de naissance
int rand_wilaya() { return (rand() % 58 + 1);}
// fonction pour generer le groupe sanguin
int rand_groupe_sanguin() { return (rand() % 8 + 1);}
// fonction pour generer le grade
int rand_grade() { return (rand() % 17 + 1);}
// fonction pour genererla force armee
int rand_force_armee() { return (rand() % 8 + 1);}
// fonction pour generer la region militaire
int rand_region_militaire () { return (rand() % 6 + 1);}

// fonction pour creer un personnel militaire
Tenreg creer_perso() {
   Tenreg personnel;
   personnel.matricule = rand_matricule();
   strcpy(personnel.nom, rand_nom());
   strcpy(personnel.prenom, rand_prenom());
   strcpy(personnel.date_naissance, rand_date());
   personnel.wilaya_naissance = rand_wilaya();
   personnel.groupe_sanguin = rand_groupe_sanguin();
   personnel.grade = rand_grade();
   personnel.force_armee = rand_force_armee();
   personnel.region_militaire = rand_region_militaire();
   return personnel;
}

/* Module de recherche dans un fichier LObarreF */
// La recherche est sequentielle 
void Recherche(char *nom_fichier, int matricule, int *trouve, int *i, int *j) {
	F = Ouvrir(nom_fichier, 'A');
	(*trouve) = 0;
	(*i) = entete(F, 2);	// le numero du bloc tete
	(*j) = 0;				// positionnemt au debut du bloc

	// si le fichier est non-vide
	if (entete(F,1)) {
		LireDir(F, *i, &buf);	// lecture d'un buffer
		while (!trouve && (*i) != -1) { 	// tant que non trouve et non fin de fichier
			for (int k = 0; k < buf.nb; k++) { 		// recherche dans le bloc
				if (buf.tab[k].matricule == matricule) {	// le personnel est trouve
					(*trouve) = 1;
					(*j) = k;
				}	
			}
			(*i) = buf.suiv;
			LireDir(F, *i, &buf);
		}
	}
	Fermer(F);
}

// Module d'insertion dans un fichier LObarreF
void Insertion(char *nom_fichier, Tenreg personnel) {
	int trouve, continu;
	int i, j, k;

	Recherche(nom_fichier, personnel.matricule, &trouve, &i, &j);
	if (!trouve) {		// le personnel est inexistant
		F = Ouvrir(nom_fichier, 'A');
		if (!entete(F, 1)) {		// fichier vide
			// insertion en premier bloc en premiere position
			buf.tab[0] = personnel;
			buf.nb = 1;
			EcrireDir(F, 0, buf);
			Aff_entete(F, 5, entete(F, 5) + 1);
		} else {						// fichier non-vide
			// insertion en dernier bloc en derniere position
			LireDir(F, entete(F, 3), &buf);
			// cas 1: dernier bloc pas plein
			if (buf.nb < b) {
				buf.tab[buf.nb] = personnel;
				buf.nb++;
				EcrireDir(F, entete(F, 3), buf);
				Aff_entete(F, 5, entete(F, 5) + 1);
			} else {
			// cas 2: dernier bloc plein
			// allocation d'un nouveau bloc vide
				Alloc_Bloc(F);	
				buf.tab[0] = personnel;
				buf.nb = 1;
				EcrireDir(F, entete(F, 3), buf);
				Aff_entete(F, 5, entete(F, 5) + 1);		
			}
		}
		continu = 1;
		LireDir(F, entete(F, 1), &buf);
	}
	Fermer(F);
}

// Module de suppression physique dans un fichierLObarreF
void Suppression(char *nom_fichier, int matricule) {
	int trouve;
	int i, j;
	Buffer buf1;
	Recherche(nom_fichier, matricule, &trouve, &i, &j);
	if (trouve) {
		F = Ouvrir(nom_fichier, 'A');
		LireDir(F, i, &buf);
		LireDir(F, entete(F, 3), &buf1);
		// cas 1: dernier bloc contient un seul personnel
		if (buf1.nb == 1) {
			buf.tab[j] = buf1.tab[buf1.nb];
			EcrireDir(F, i, buf);					
			Aff_entete(F, 1, entete(F, 1) - 1);		// mise a jour du nombre de bloc utilises
			Aff_entete(F, 3, entete(F, 3) - 1);		// mise a jour de la queue
			Aff_entete(F, 5, entete(F, 5) - 1);		// mise a jour du compteur d'insertions
			Aff_entete(F, 6, entete(F, 6) + 1);		// mise a jour du compteur de suppresssion	
		} else {
		// cas 2: dernier bloc contient plusieurs personnel ( > 1)
			buf.tab[j] = buf1.tab[buf1.nb];		// ecrasement de l'enregistrement par le dernier enregistrement
			EcrireDir(F, i, buf);					
			EcrireDir(F, entete(F, 3), buf1);
			Aff_entete(F, 5, entete(F, 5) - 1);	 	// mise a jour du compteur d'insertions
			Aff_entete(F, 6, entete(F, 6) + 1);	 	// mise a jour du compteur de suppresssion
		}
		Fermer(F);
	}
}


/* Module pour chargement initial du fichier LObarreF */
void chargement_initial(char *nom_fichier, int N) {
	Tenreg personnel;
	int i, j;
	i = 1;
	j = 1;
	F = Ouvrir(nom_fichier, 'N');

	for (int k = 0; k < N; k++) {
		personnel = creer_perso();
		if (j <= b) {	// espace suffisant dans ce bloc 
			buf.tab[j] = personnel;
			j++;
		} else {			//espace insuffisant dans ce bloc
			buf.nb = j;
			EcrireDir(F, i, buf);
			buf.tab[0] = personnel;
		  	i++;
			j = 1;	
		}
	}

	buf.nb = j;		// le dernier bloc
	EcrireDir(F, i, buf);
	Aff_entete(F, 1, i);		//	mise a jour du nombre de blocs
	Aff_entete(F, 3, i);		//	mise a jour du dernier bloc
	Aff_entete(F, 5, N);		//	mise a jour du compteur d'insertion
}


/* Les modules d'affichage */
// procedure pour afficher les informations d'un personnel militaire
void Afficher_Perso(Tenreg personnel, int i) {
	int len = 44 - ((i / 10) ? 2 : 1) - 14;
   printf("*| Personnel : %d  |%*s\n", i, len, "|*");
	printf("*| ---------------%*s\n", 30, "|*");
   printf("*| Matricule : %d %*s \n", personnel.matricule, 26, "|*");
	int len1 = 44 - strlen(personnel.nom) - 6;
   printf("*| Nom : %s %*s\n", personnel.nom, len1, "|*");
	int len2 = 44 - strlen(personnel.prenom) - 9;
   printf("*| Prenom : %s %*s\n", personnel.prenom, len2, "|*");
   printf("*| Date de naissance : %s %*s\n", personnel.date_naissance, 14, "|*");
  	int len3 = 44 - ((personnel.wilaya_naissance / 10) ? 2 : 1) - 22;
   printf("*| Wilaya de naissance : %d %*s\n", personnel.wilaya_naissance, len3, "|*");
   printf("*| Groupe sanguin: %d %*s\n", personnel.groupe_sanguin, 27, "|*");
  	int len4 = 44 - ((personnel.grade / 10) ? 2 : 1) - 8;
	printf("*| Grade : %d %*s\n", personnel.grade, len4, "|*");
   printf("*| Force armee : %d %*s\n", personnel.force_armee, 29, "|*");
   printf("*| Region militaire : %d %*s\n", personnel.region_militaire, 24, "|*");
}


// procedure pour afficher un bloc dans un fichier LObarreF
//void Afficher_Bloc(LObarreF *F, int i) {
void Afficher_Bloc(Tbloc B, int i) {
	char str[] = "#**********************************************#"; 
	char str1[] = "*+--------------------------------------------+*";
	printf("%s\n", str);
	int len = 44 - ((i / 10) ? 2 : 1) - 9;
	printf("*| Bloc : %d | %*s\n", i, len, "|*");
	printf("%s\n", str1);
	for (int i = 0; i < B.nb; i++) {
		Afficher_Perso(B.tab[i], i);
		printf("%s\n", str1);
	}
	printf("%s\n", str);
}

// procedure pour afficher l'entete d'un fichier LObarreF
//void Afficher_Entete(LObarreF F) {
void Afficher_Entete(Entete E) {
	char nb[3];
	char tete[4];
	char queue[4];
	char cpt_inser[8];
	char cpt_supp[8];
	sprintf(nb, "%d", E.nb);
	sprintf(tete, "% 3d", E.tete);
	sprintf(queue, "% 3d", E.queue);
	sprintf(cpt_inser, "% 7d", E.cpt_inser);
	sprintf(cpt_supp, "% 7d", E.cpt_supp);
	char str[] = "+-----------------+------+-------+----------------------+-------------------------+";
	printf("+-----------------+\n");
	printf("|     Entete	  |\n");
	printf("%s\n", str);
	printf("| Nombre de Blocs | Tete | Queue | Compteur d'insertion | Compteur de suppression |\n");
	printf("%s\n", str);
	printf("|      		  |      | 	 |		 	|  	 		  |\n");
	printf("| 	%s 	  | %s  | %s   |     %s		| 	 %s	  |\n", nb, tete, queue, cpt_inser, cpt_supp);
	printf("|      		  |      | 	 |		 	|  	 		  |\n");
	printf("%s\n", str);
}


// procedure pour afficher un fichier LObarreF
void Afficher_Fichier(LObarreF *F) {
//	Afficher_Entete(F.entete);
	for (int i = 0; i < F->entete.nb; i++) {
//		Afficher_Bloc(F, i);
	}
}



int main () {
   srand(time(NULL));
   for (int i = 0; i < 3; i ++) {
      Tenreg pers = creer_perso();
		buf.tab[i] = pers;
		buf.nb++;
   }
	Entete E;
	E.nb = 5;
	E.tete = 1;
	E.queue = 5;
	E.cpt_inser = 854;
	E.cpt_supp = 10403;
	Afficher_Entete(E);
	Afficher_Bloc(buf, 1);
   printf("\nTime elapsed : %.3f s.\n",1.0 * clock() /CLOCKS_PER_SEC);
   return 0;
}
       


