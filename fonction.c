#include "affichage.c"


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

void Fusion(Index *arr, int p, int q, int r) {
	// Create L ← A[p..q] and M ← A[q+1..r]
   int n1 = q - p + 1;
   int n2 = r - q;
   Index L[n1], M[n2];

   for (int i = 0; i < n1; i++)  L[i] = arr[p + i];
   for (int j = 0; j < n2; j++)  M[j] = arr[q + 1 + j];
	
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
void Tri(Index *arr, int l, int r) {
	 if (l < r) {
    // m is the point where the array is divided into two subarrays
    int m = l + (r - l) / 2;
    Tri(arr, l, m);
    Tri(arr, m + 1, r);
    // Merge the sorted subarrays
    Fusion(arr, l, m, r);
   }
}

// Module pour chargement initial du fichier LObarreF 
void Chargement_Initial(char *nom_fichier, int N) {
	Tenreg personnel;
	Index index[N];
	int i, j;
	i = 1;
	j = 0;
	F = Ouvrir(nom_fichier, 'N');
	FILE *G = fopen("index.bin", "wb+");
   char *annee = (char*) malloc (5 * sizeof(char));
	for (int k = 0; k < N; k++) {
		memset(&personnel, 0, sizeof(Tenreg));
		memset(&index[k], 0, sizeof(Index));
		personnel = creer_perso();
		index[k].cle = personnel.matricule;
		index[k].adr = k;
		index[k].grade = personnel.grade;
		index[k].force_armee = personnel.force_armee;
		index[k].region_militaire = personnel.region_militaire;
      strncpy(annee, personnel.date_naissance, 4);
      annee[4] = '\0';
		index[k].age = 2022 - atoi(annee);

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
	free(annee);
	buf.nb = j;		// le dernier bloc
	buf.suiv = -1;
	EcrireDir(F, i, buf);
	Aff_entete(F, 1, i);		//	mise a jour du nombre de blocs
	Aff_entete(F, 3, i);		//	mise a jour du dernier bloc
	Aff_entete(F, 4, N);		//	mise a jour du compteur d'insertion

	Tri(index, 0, N - 1);  
	fwrite(&index, sizeof(Index), N, G);
	Fermer(F);
	rewind(G);
	fclose(G);
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
				if (buf.tab[k].matricule == matricule) {	// le personnel est trouve et non efface 
					(*trouve) = 1;
					(*j) = k;
					break;
				}	
			}
			if (*trouve) break;
			(*i) = buf.suiv;
			LireDir(F, *i, &buf);
		}
	} else {
		perror("Fichier est vide!\n");	
	}
	Fermer(F);
}

// La recherche dichotomique en utilisant la table d'index
void Recherche1(char *nom_fichier, int matricule, int *trouve, int *i, int *j) {
	F = Ouvrir(nom_fichier, 'A');
	FILE *G = fopen("index.bin", "rb+");
	int N = entete(F, 4) - entete(F, 5);
	Index index[N];
	fread(&index, sizeof(Index), N, G);

	int inf = 0, sup = N - 1, pos = 0, mid = 0;
	*trouve = 0;
	while (inf <= sup) {
      mid = (inf + sup) / 2;
 
      if (index[mid].cle == matricule) {
         *trouve = 1;
         pos = mid;
         break;
      }
      if (index[mid].cle > matricule) {
         sup = mid - 1;
		}
		if (index[mid].cle < matricule) {
         inf = mid + 1;
      }
	}
	if (*trouve) {
		*i = index[pos].adr / 85 + 1;
		*j = index[pos].adr % 85;
	} else {
		*i = entete(F, 3);		// le bloc queue
		*j = entete(F, 4) % 85;	// la derniere position
	}

	Fermer(F);
	fclose(G);
}

// Module d'insertion dans un fichier LObarreF
void Insertion(char *nom_fichier, Tenreg personnel) {
	int trouve, continu;
	int i, j, k;

	Recherche1(nom_fichier, personnel.matricule, &trouve, &i, &j);
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
				buf.suiv = -1;
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
	Recherche1(nom_fichier, matricule, &trouve, &i, &j);
	if (trouve) {
		F = Ouvrir(nom_fichier, 'A');
		// le bloc concerne est le bloc queue
		if (i == entete(F, 3)) {
			LireDir(F, i, &buf);
			buf.tab[j] = buf.tab[buf.nb - 1];		// ecrasement de l'enregistrement par le dernier enregistrement
			buf.nb--;									   // decrementation du nombre d'enregistrements dans le bloc
			if (buf.nb > 0) {
				EcrireDir(F, i, buf);					
			} else {
				if (entete(F, 3) == 1) {
					EcrireDir(F, i, buf);						
				} else {
					Aff_entete(F, 1, entete(F, 1) - 1);		// mise a jour du nombre de bloc utilises
					Aff_entete(F, 3, entete(F, 3) - 1);		// mise a jour de la queue
				}
			}
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
			} else {
			// cas 2: dernier bloc contient un seul personnel
				Aff_entete(F, 1, entete(F, 1) - 1);		// mise a jour du nombre de bloc utilises
				Aff_entete(F, 3, entete(F, 3) - 1);		// mise a jour de la queue
			}
		}
		Aff_entete(F, 5, entete(F, 5) + 1);	 	// mise a jour du compteur de suppresssion
		Fermer(F);
	}
}

void Suppression1(char *nom_fichier, int i, int j) {
	F = Ouvrir(nom_fichier, 'A');
	Buffer buf1, buf2;
	LireDir(F, i, &buf);
	if (i == entete(F, 3)) {
		LireDir(F, i, &buf);
		buf.tab[j] = buf.tab[buf.nb - 1];		// ecrasement de l'enregistrement par le dernier enregistrement
		buf.nb--;									   // decrementation du nombre d'enregistrements dans le bloc
		if (buf.nb > 0) {
			EcrireDir(F, i, buf);					
		} else {
			if (entete(F, 3) == 1) {
				EcrireDir(F, i, buf);						
			} else {
				Aff_entete(F, 1, entete(F, 1) - 1);		// mise a jour du nombre de bloc utilises
				Aff_entete(F, 3, entete(F, 3) - 1);		// mise a jour de la queue
			}
		}
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
		} else {
		// cas 2: dernier bloc contient un seul personnel
			Aff_entete(F, 1, entete(F, 1) - 1);		// mise a jour du nombre de bloc utilises
			Aff_entete(F, 3, entete(F, 3) - 1);		// mise a jour de la queue
		}
	}
	Aff_entete(F, 5, entete(F, 5) + 1);	 	// mise a jour du compteur de suppresssion
	Fermer(F);
}

// Module d'epuration dans un fichier LObarreF
void Epuration(char *nom_fichier) {
	F = Ouvrir(nom_fichier, 'A');
	FILE *G = fopen("index.bin", "rb+");

	int N = entete(F, 4) - entete(F, 5);
	Index index[N];
	Index *temp = (Index*) calloc (N, sizeof(Index));	
	fread(&index, sizeof(Index), N, G);

	Tri(index, 0, N - 1);  

	int j = 0;
	for (int i = 0; i < N - 1; i++) {
		if (index[i].cle !=  index[i + 1].cle) {
			temp[j++] = index[i];
		} else {
			Suppression1(nom_fichier, (index[i + 1].adr / 85) + 1, index[i + 1].adr % 85);
		}	
	}
	temp[j++] = index[N - 1];
	for (int i = 0; i < j; i++) {
		index[i] = temp[i];
		debug("%d", index[i].cle);
	}
	rewind(G);
	fwrite(&index, sizeof(Index), j, G);
	free(temp);
	fclose(G);
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

	Afficher_Table_Index(300000);
	Epuration("in");

	Afficher_Fichier("in");
//	Afficher_Table_Index(10000);
	printf("\nTime elapsed : %.3f s.\n",1.0 * clock() /CLOCKS_PER_SEC);
   return 0;
}
       


