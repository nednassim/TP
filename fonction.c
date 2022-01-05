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
	memset(&personnel, 0, sizeof(Tenreg));
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
	(*i) = entete(F, 2);	// le numero du bloc tete
	(*j) = 0;				// positionnemt au debut du bloc
	(*trouve) = 0;

	// si le fichier est non-vide
	if (entete(F,1)) {
		LireDir(F, *i, &buf);	// lecture d'un buffer
		while (!(*trouve) && (*i) != -1) { 	// tant que non trouve et non fin de fichier
			for (int k = 0; k < buf.nb; k++) { 		// recherche dans le bloc
//				debug("%d %d %d", buf.tab[k].matricule, matricule, *i);	
				if (buf.tab[k].matricule == matricule) {	// le personnel est trouve et non efface 
					(*trouve) = 1;
					(*j) = k;
					break;
				}	
			}
			if (*trouve) break;
//			(*i)++;
			debug("%d", buf.suiv);
			(*i) = buf.suiv;
			LireDir(F, *i, &buf);
		}
	} else {
		perror("Fichier est vide!\n");	
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
			buf.suiv = -1;
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
				Aff_entete(F, 4, entete(F, 4) + 1);
			} else {
			// cas 2: dernier bloc plein
			// allocation d'un nouveau bloc vide
				Alloc_Bloc(F);	
				buf.tab[0] = personnel;
				buf.nb = 1;
				EcrireDir(F, entete(F, 3), buf);
				Aff_entete(F, 4, entete(F, 4) + 1);		
			}
		}
		continu = 1;
		LireDir(F, entete(F, 1), &buf);
	}
	Fermer(F);
}

// Module de suppression physique dans un fichier LObarreF
void Suppression(char *nom_fichier, int matricule) {
	int trouve;
	int i, j;
	Buffer buf1, buf2;
	Recherche(nom_fichier, matricule, &trouve, &i, &j);
	if (trouve) {
		F = Ouvrir(nom_fichier, 'A');
		// le bloc concerne est le bloc queue
		if (i == entete(F, 3)) {
			LireDir(F, i, &buf);
			buf.tab[j] = buf.tab[buf.nb - 1];		// ecrasement de l'enregistrement par le dernier enregistrement
			buf.nb--;									// decrementation du nombre d'enregistrements dans le bloc
			if (buf.nb > 0) {
				EcrireDir(F, i, buf);					
			} else {
				Aff_entete(F, 1, entete(F, 1) - 1);	
			}
			Aff_entete(F, 5, entete(F, 5) + 1);	 	// mise a jour du compteur de suppresssion	
		} else {
			// le bloc concerne n'est pas le bloc queue
			LireDir(F, i, &buf1);
			LireDir(F, entete(F, 3), &buf2);
			buf1.tab[j] = buf2.tab[buf2.nb - 1];
			buf2.nb--;
			EcrireDir(F, i, buf1);					
			if (buf2.nb > 0) {
			// cas 1: dernier bloc contient plusieurs personnel ( > 1)
				EcrireDir(F, entete(F, 3), buf2);
				Aff_entete(F, 3, entete(F, 3) - 1);		// mise a jour de la queue
				Aff_entete(F, 5, entete(F, 5) + 1);		// mise a jour du compteur de suppresssion	
			} else {
			// cas 2: dernier bloc contient un seul personnel
				Aff_entete(F, 1, entete(F, 1) - 1);		// mise a jour du nombre de bloc utilises
				Aff_entete(F, 5, entete(F, 5) + 1);	 	// mise a jour du compteur de suppresssion
			}
		}
		Fermer(F);
	}
}

void Suppression1(char *nom_fichier, int i, int j) {
	F = Ouvrir(nom_fichier, 'A');
	Buffer buf1;
	LireDir(F, i, &buf);
	// le bloc concerne est le bloc queue
	if (i == entete(F, 3)) {		
		if (j == buf.nb - 1) {	// le dernier enregistrement
			buf.nb--;
			EcrireDir(F, i, buf);
			Aff_entete(F, 5, entete(F, 5) + 1);	 	// mise a jour du compteur de suppresssion
		} else {
			buf.tab[j] = buf.tab[buf.nb - 1];		// ecrasement de l'enregistrement par le dernier enregistrement
			buf.nb--;									// decrementation du nombre d'enregistrements dans le bloc
			EcrireDir(F, i, buf);					
			Aff_entete(F, 5, entete(F, 5) + 1);	 	// mise a jour du compteur de suppresssion	
		}
	} else {
	// le bloc concerne n'est pas le bloc queue
		LireDir(F, entete(F, 3), &buf1);
		// cas 1: dernier bloc contient un seul personnel
		if (buf1.nb == 1) {
			buf.tab[j] = buf1.tab[0];
			EcrireDir(F, i, buf);					
			Aff_entete(F, 1, entete(F, 1) - 1);		// mise a jour du nombre de bloc utilises
			Aff_entete(F, 3, entete(F, 3) - 1);		// mise a jour de la queue
			Aff_entete(F, 5, entete(F, 5) + 1);		// mise a jour du compteur de suppresssion	
		} else if (buf1.nb > 1) {
		// cas 2: dernier bloc contient plusieurs personnel ( > 1)
			buf.tab[j] = buf1.tab[buf1.nb - 1];		// ecrasement de l'enregistrement par le dernier enregistrement
			buf.nb--;									// decrementation du nombre d'enregistrements dans le bloc
			EcrireDir(F, i, buf);					
			EcrireDir(F, entete(F, 3), buf1);
			Aff_entete(F, 5, entete(F, 5) + 1);	 	// mise a jour du compteur de suppresssion
		}
	}
	Fermer(F);
}

// Module pour chargement initial du fichier LObarreF 
void Chargement_Initial(char *nom_fichier, int N) {
	Tenreg personnel;
	int i, j;
	i = 1;
	j = 0;
	F = Ouvrir(nom_fichier, 'N');
	Index table_index[N];
	FILE *G = fopen("index.bin", "wb+");
	for (int k = 0; k < N; k++) {
		memset(&personnel, 0, sizeof(Tenreg));
		memset(&table_index[k], 0, sizeof(Index));
		personnel = creer_perso();
		table_index[k].cle = personnel.matricule;
		table_index[k].adr = k;
		table_index[k].grade = personnel.grade;
		table_index[k].force_armee = personnel.force_armee;
		table_index[k].region_militaire = personnel.region_militaire;
      char *annee = (char*) malloc (5 * sizeof(char));
      strncpy(annee, personnel.date_naissance, 4);
      annee[4] = '\0';
		table_index[k].age = 2022 - atoi(annee);
		free(annee);
		fwrite(&table_index[k], sizeof(Index), 1, G);

		if (j < b) {	// espace suffisant dans ce bloc 
			buf.tab[j] = personnel;
			j++;
		} else {			//espace insuffisant dans ce bloc
			buf.nb = j;
			buf.suiv = i + 1;
			EcrireDir(F, i, buf);
			buf.tab[0] = personnel;
		  	i++;
			j = 1;	
		}
	}

	buf.nb = j;		// le dernier bloc
	buf.suiv = -1;
	EcrireDir(F, i, buf);
	Aff_entete(F, 1, i);		//	mise a jour du nombre de blocs
	Aff_entete(F, 3, i);		//	mise a jour du dernier bloc
	Aff_entete(F, 4, N);		//	mise a jour du compteur d'insertion
	
	fclose(G);
	Fermer(F);
}

// Module pour extraire la table d'index secondaire du fichier d'index principale
void Index_Index1(char *nom_fichier, char *nom_fichier1) {
	FILE *G = fopen(nom_fichier, "rb");
	FILE *H = fopen(nom_fichier1, "wb+");

	Index index;
	Index1 index1;
	memset(&index, 0, sizeof(Index));
	memset(&index1, 0, sizeof(Index1));

	while (fread(&index, sizeof(Index), 1, G) == 1) {
		index1.cle = index.cle;
		index1.adr = index.adr; 
		fwrite(&index1, 1, sizeof(index1), H);
	}
	fclose(G);
	fclose(H);
}

// Module pour extraire la table d'index secondaire du fichier d'index principale
void Index_Index5(char *nom_fichier, char *nom_fichier1) {
	FILE *G = fopen(nom_fichier, "rb");
	FILE *H = fopen(nom_fichier1, "wb+");

	Index index;
	Index5 index5;
	memset(&index, 0, sizeof(Index));
	memset(&index5, 0, sizeof(Index5));

	while (fread(&index, sizeof(Index), 1, G) == 1) {
		index5.cle = index.cle;
		index5.adr = index.adr; 
		index5.region_militaire = index.region_militaire;
		index5.age = index.age;
		fwrite(&index5, 1, sizeof(index5), H);
	}
	fclose(G);
	fclose(H);
}

void Fusion(Index1 *arr, int p, int q, int r) {
	// Create L ← A[p..q] and M ← A[q+1..r]
   int n1 = q - p + 1;
   int n2 = r - q;
   Index1 L[n1], M[n2];

   for (int i = 0; i < n1; i++) {
      L[i] = arr[p + i];
	}
   for (int j = 0; j < n2; j++) {
      M[j] = arr[q + 1 + j];
	}
   int i = 0, j = 0, k = p;
   while (i < n1 && j < n2) {
      if (L[i].cle <= M[j].cle) {
         arr[k] = L[i];   i++;
      } else {
         arr[k] = M[j];   j++;
      }
      k++;
   }
   while (i < n1) {
      arr[k] = L[i];
      i++;  k++;
   }
   while (j < n2) {
      arr[k] = M[j];
      j++;	k++;
   }
}

// Module pour trier la table d'index par tri fusion
void Trier(Index1 *arr, int l, int r) {
	 if (l < r) {
    // m is the point where the array is divided into two subarrays
    int m = l + (r - l) / 2;
    Trier(arr, l, m);
    Trier(arr, m + 1, r);
    // Merge the sorted subarrays
    Fusion(arr, l, m, r);
   }
}
 
// Module d'epuration dans un fichier LObarreF
void Epuration(char *nom_fichier) {
	F = Ouvrir(nom_fichier, 'A');
	FILE *G = fopen("index1.bin", "rb");

	int N = entete(F, 4) - entete(F, 5);
	Index1 table_index1[N];	
	for (int i = 0; i < N; i++) {
		fread(&table_index1[i], sizeof(Index1), 1, G);
	}
	Trier(table_index1, 0, N - 1);  

	int j = 0;
	Index1 temp[N];
	for (int i  = 0; i < N - 1; i++) {
		if (table_index1[i].cle !=  table_index1[i + 1].cle) {
			temp[j++] = table_index1[i];
		} else {
			debug("%d %d", (table_index1[i + 1].adr / 85) + 1, table_index1[i + 1].adr % 85);
			Suppression1(nom_fichier, (table_index1[i + 1].adr / 85) + 1, table_index1[i + 1].adr % 85);
		}	
	}
	temp[j++] = table_index1[N - 1];
	for (int i = 0; i < j; i++) {
		table_index1[i] = temp[i];
	}
	for (int i = 0; i < j; i++) {
//		debug("%d %d", i, table_index1[i].cle);
	}
}

/*********************************************************************************/
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
void Afficher_Bloc(LObarreF *F, int i) {
	char str[] = "#**********************************************#"; 
	char str1[] = "*+--------------------------------------------+*";
	printf("%s\n", str);
	int len = 44 - ((i / 10) ? 2 : 1) - 9;
	printf("*| Bloc : %d | %*s\n", i, len, "|*");
	printf("%s\n", str1);
	LireDir(F, i, &buf);
	for (int i = 0; i < buf.nb; i++) {
		Afficher_Perso(buf.tab[i], i + 1);
		printf("%s\n", str1);
	}
	printf("%s\n", str);
	printf("\t\t *| Bloc : %d  |*\n", i );
	printf("\t\t *  * * * * * * *\n");
}

// procedure pour afficher l'entete d'un fichier LObarreF
void Afficher_Entete(LObarreF *F) {
	char nb[5];
	char tete[4];
	char queue[6];
	char cpt_inser[8];
	char cpt_supp[8];
	sprintf(nb, "%d", F->entete.nb);
	sprintf(tete, "% 3d", F->entete.tete);
	sprintf(queue, "% 5d", F->entete.queue);
	sprintf(cpt_inser, "% 7d", F->entete.cpt_inser);
	sprintf(cpt_supp, "% 7d", F->entete.cpt_supp);
	char str[] = "+-----------------+------+---------+----------------------+-------------------------+";
	printf("+-----------------+\n");
	printf("|     Entete	  |\n");
	printf("%s\n", str);
	printf("| Nombre de Blocs | Tete |  Queue  | Compteur d'insertion | Compteur de suppression |\n");
	printf("%s\n", str);
	printf("|      		  |      | 	   |		 	  |  	 		    |\n");
	printf("| 	%s 	  | %s  |  %s  |     %s	  | 	  %s 	    |\n", nb, tete, queue, cpt_inser, cpt_supp);
	printf("|      		  |      | 	   |		 	  |   	 		    |\n");
	printf("%s\n", str);
}

// procedure pour afficher un fichier LObarreF
void Afficher_Fichier(char *nom_fichier) {
	F = Ouvrir(nom_fichier, 'A');
	Afficher_Entete(F);
	Afficher_Bloc(F, 1);
/*
	for (int i = 0; i < F->entete.nb; i++) {
		Afficher_Bloc(F, i + 1);
		printf("\t\t      *\n");
		printf("\t\t      *\n");
		printf("\t\t    * * *\n");
		printf("\t\t     ***\n");
		printf("\t\t      *\n");
	}

	Afficher_Bloc(F, 3);
	*/
	Afficher_Entete(F);
	Fermer(F);
}

void Afficher_Table_Index() {
	FILE *F = fopen("index.bin", "rb");
	Index id;
	memset(&id, 0, sizeof(Index));
	while(fread(&id, sizeof(Index), 1, F) == 1) {
		debug("%d %d %d %d %d %d", id.cle, id.adr, id.age, id.grade, id.force_armee, id.region_militaire);
	}
}

void Afficher_Table_Index1() {
	FILE *F = fopen("index1.bin", "rb");
	Index1 id;
	int count = 1;
	memset(&id, 0, sizeof(Index1));
	while(fread(&id, sizeof(Index1), 1, F) == 1) {
		debug("%d %d", id.cle, id.adr);
	}
}

void Afficher_Table_Index5() {
	FILE *F = fopen("index5.bin", "rb");
	Index5 id;
	int count = 1;
	memset(&id, 0, sizeof(Index5));
	while(fread(&id, sizeof(Index5), 1, F) == 1) {
		debug("%d %d %d %d", id.cle, id.adr, id.region_militaire, id.age);
	}
}

int main () {
   srand(time(0));
/*
	for (int i = 0; i < 1000; i ++) {
      Tenreg pers = creer_perso();
		Afficher_Perso(pers, i + 1);
   }	
	Entete E;
	E.nb = 5;
	E.tete = 1;
	E.queue = 5;
	E.cpt_inser = 854;
	E.cpt_supp = 10403;

	Afficher_Fichier("in");

	int i, j, trouve;
	Recherche("in", 273126, &trouve, &i, &j);
	debug("%d %d %d", i, j, trouve);

	Tenreg personnel = creer_perso();
	Insertion("in", personnel);
	Suppression("in", 411382);

*/
	Chargement_Initial("in", 300000);		//	Afficher_Fichier("in");
	Afficher_Fichier("in");
	Afficher_Table_Index();
//	Index_Index1("index.bin", "index1.bin");
//	Epuration("in");
//	Afficher_Fichier("in");
	printf("\nTime elapsed : %.3f s.\n",1.0 * clock() /CLOCKS_PER_SEC);
   return 0;
}
       


