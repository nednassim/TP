#include "machine.c"

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
   

