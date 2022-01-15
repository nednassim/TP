#include "../affichage.c"


int main () {
	printf("La lecture des fichiers issues de la fragmentation du fichier de donnees  :\n");
	FILE *F1 = fopen("F1", "rb");
	FILE *F2 = fopen("F2", "rb");
	FILE *F3 = fopen("F3", "rb");
	FILE *F4 = fopen("F4", "rb");
	FILE *F5 = fopen("F5", "rb");
	FILE *F6 = fopen("F6", "rb");

	Tenreg personnel;
	memset(&personnel, 0, sizeof(Tenreg));
	char str[] = "+----------------------------------------------+";
	if (F1 != NULL) {
		printf("Les personnels de la region militaire 1: \n");
		int i = 1;
		while (fread(&personnel, sizeof(Tenreg), 1, F1) == 1) {
			printf("%s\n", str);
			Afficher_Perso(personnel, i++);
		}
		printf("%s\n", str);
	}
	if (F2 != NULL) {
		printf("Les personnels de la region militaire 2: \n");
		int i = 1;
		while (fread(&personnel, sizeof(Tenreg), 1, F2) == 1) {	
			printf("%s\n", str);
			Afficher_Perso(personnel, i++);
		}
		printf("%s\n", str);
	}
	if (F3 != NULL) {
		printf("Les personnels de la region militaire 3: \n");
		int i = 1;
		while (fread(&personnel, sizeof(Tenreg), 1, F3) == 1) {			
			printf("%s\n", str);
			Afficher_Perso(personnel, i++);
		}	
		printf("%s\n", str);
	}
	if (F4 != NULL) {
		printf("Les personnels de la region militaire 4: \n");
		int i = 1;
		while (fread(&personnel, sizeof(Tenreg), 1, F4) == 1) {	
			printf("%s\n", str);
			Afficher_Perso(personnel, i++);
		}	
		printf("%s\n", str);
	}
	if (F5 != NULL) {
		printf("Les personnels de la region militaire 5: \n");
		int i = 1;
		while (fread(&personnel, sizeof(Tenreg), 1, F5) == 1) {	
			printf("%s\n", str);
			Afficher_Perso(personnel, i++);
		}	
		printf("%s\n", str);
	}
	if (F6 != NULL) {
		printf("Les personnels de la region militaire 6: \n");
		int i = 1;
		while (fread(&personnel, sizeof(Tenreg), 1, F6) == 1) { 			
			printf("%s\n", str);
			Afficher_Perso(personnel, i++);
		}	
		printf("%s\n", str);
	}

   fclose(F1);
   fclose(F2);
   fclose(F3);
   fclose(F4);
   fclose(F5);
   fclose(F6);

   return 0;
}


