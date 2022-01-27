#include "machine.c"


typedef struct Force_armee {
   int num;
   char nom[52];
} Force_armee;

typedef struct Grade {
   int num;
   char nom[32];
} Grade;

typedef struct Groupe_sanguin {
   int num;
   char nom[8];
} Groupe_sanguin;

typedef struct Region_militaire {
   int num;
   char nom[20];
} Region_militaire;

typedef struct Wilaya {
   int num;
   char nom[25];
} Wilaya;



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
   printf("\t\t * * * * * * * *\n");
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
   printf("+-------------+\n");
   printf("|    Entete   |\n");
   printf("%s\n", str);
   printf("| Nombre de Blocs | Tete |  Queue  | Compteur d'insertion | Compteur de suppression |\n");
   printf("%s\n", str);
   printf("|          	  |      |         |                	  |		            |\n");
  	printf("|       %s  	  | %s  | %s   |     %s 	  |     %s  	    |\n", nb, tete, queue, cpt_inser, cpt_supp);
   printf("|                 |      |  	   |    		  |                         |\n");
   printf("%s\n", str);
}
 
// procedure pour afficher un fichier LObarreF
void Afficher_Fichier(LObarreF *F) {
	FILE *F1 = fopen("BDD/force_armee.bin", "rb");
	FILE *F2 = fopen("BDD/grade.bin", "rb");
	FILE *F3 = fopen("BDD/groupe_sanguin.bin", "rb");
	FILE *F4 = fopen("BDD/region_militaire.bin", "rb");
	FILE *F5 = fopen("BDD/wilaya.bin", "rb");

	int force_armee, grade, region_militaire, wilaya;
	fread(&force_armee, sizeof(int), 1, F1);
	fread(&grade, sizeof(int), 1, F2);
	fread(&region_militaire, sizeof(int), 1, F4);
	fread(&wilaya, sizeof(int), 1, F5);

	char force_armees[force_armee][52];
	char grades[grade][32];
	char groupe_sanguins[8][8];
	char region_militaires[region_militaire][20];
	char wilayas[wilaya][25];

	Force_armee force_armee1;
	for (int i = 0; i < force_armee; i++) {
		fread(&force_armee1, sizeof(Force_armee), 1, F1);
		strcpy(force_armees[i], force_armee1.nom);
	}
	Grade grade1;
	for (int i = 0; i < grade; i++) {
		fread(&grade1, sizeof(Grade), 1, F2);
		strcpy(grades[i], grade1.nom);
	}
	Groupe_sanguin groupe_sanguin1;
	for (int i = 0; i < 8; i++) {
		fread(&groupe_sanguin1, sizeof(Groupe_sanguin), 1, F3);
		strcpy(groupe_sanguins[i], groupe_sanguin1.nom);
	}
	Region_militaire region_militaire1;
	for (int i = 0; i < region_militaire; i++) {
		fread(&region_militaire1, sizeof(Region_militaire), 1, F4);
		strcpy(region_militaires[i], region_militaire1.nom);
	}
	Wilaya wilaya1;
	for (int i = 0; i < wilaya; i++) {
		fread(&wilaya1, sizeof(Wilaya), 1, F5);
		strcpy(wilayas[i], wilaya1.nom);
	}

	fclose(F1);
	fclose(F2);
	fclose(F3);
	fclose(F4);
	fclose(F5);

   Afficher_Entete(F);
	int i = 1;
   char str[] = "#****************************************************************#";
   char str1[] = "*+--------------------------------------------------------------+*";
   printf("%s\n", str);
   int len = 62 - ((i / 10) ? 2 : 1) - 9;
   printf("*| Bloc : %d | %*s\n", i, len, "|*");
   printf("%s\n", str1);
   LireDir(F, i, &buf);
	int j = 1;
   for (int i = 0; i < buf.nb; i++) {
	 	int len = 62 - ((i / 10) ? 2 : 1) - 14;
		printf("*| Personnel : %d  |%*s\n", j++, len, "|*");
		printf("*| ---------------%*s\n", 48, "|*");
		printf("*| Matricule : %d %*s \n", buf.tab[i].matricule, 44, "|*");
		int len1 = 62 - strlen(buf.tab[i].nom) - 6;
		printf("*| Nom : %s %*s\n", buf.tab[i].nom, len1, "|*");
		int len2 = 62 - strlen(buf.tab[i].prenom) - 9;
		printf("*| Prenom : %s %*s\n", buf.tab[i].prenom, len2, "|*");
		printf("*| Date de naissance : %s %*s\n", buf.tab[i].date_naissance, 32, "|*");
		int len3 = 62 - strlen(wilayas[buf.tab[i].wilaya_naissance - 1]) - 22;
		printf("*| Wilaya de naissance : %s %*s\n", wilayas[buf.tab[i].wilaya_naissance - 1], len3, "|*");
		int len4 = 62 - strlen(groupe_sanguins[buf.tab[i].groupe_sanguin - 1]) - 17;
		printf("*| Groupe sanguin : %s %*s\n", groupe_sanguins[buf.tab[i].groupe_sanguin - 1], len4, "|*");
		int len5 = 62 - strlen(grades[buf.tab[i].grade - 1]) - 8;
		printf("*| Grade : %s %*s\n", grades[buf.tab[i].grade - 1], len5, "|*");
		int len6 = 62 - strlen(force_armees[buf.tab[i].force_armee - 1]) - 14;
		printf("*| Force armee : %s %*s\n", force_armees[buf.tab[i].force_armee - 1], len6, "|*");
		int len7 = 62 - strlen(region_militaires[buf.tab[i].region_militaire - 1]) - 19;
		printf("*| Region militaire : %s %*s\n", region_militaires[buf.tab[i].region_militaire - 1], len7, "|*");
		printf("%s\n", str1);
   }
   printf("%s\n", str);
   printf("\t\t\t *| Bloc : %d  |*\n", i );
   printf("\t\t\t * * * * * * * *\n");

//	Afficher_Bloc(F, 1);
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
}  
   
// procedure pour afficher la table d'index
void Afficher_Table_Index() {
   FILE *G = fopen("index.bin", "rb");
		if (G != NULL) {
		int N;
		memset(&N, 0, sizeof(int));
		fread(&N, sizeof(int), 1, G);
		Index index[N];
		fread(&index, sizeof(Index), N, G);
		for (int i = 0; i < N; i++) {
			printf("%d %d %d %d %d %d\n", index[i].cle, index[i].adr, index[i].age, index[i].grade, index[i].force_armee    , index[i].region_militaire); 
		}
	}
   fclose(G); 
}  
   

