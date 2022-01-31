#include "../affichage.c"


int main () {
	printf("Veuillez choisir la region militaire a consulter : ");
	int opt;
	scanf("%d", &opt);
	Tenreg personnel;
	memset(&personnel, 0, sizeof(Tenreg));
	char str[] = "*+--------------------------------------------------------------+*";
	switch(opt) {
		case 1: {
			FILE *F1 = fopen("F/F1", "rb");
			if (F1 != NULL) {
				printf("Les personnels de la region militaire 1: \n");
				int i = 1;
				while (fread(&personnel, sizeof(Tenreg), 1, F1) == 1) {
					printf("%s\n", str);
					Afficher_Perso(personnel, i++);
				}
				printf("%s\n", str);
			}
		   fclose(F1);
			break;
		}
		case 2: {
			FILE *F2 = fopen("F/F2", "rb");
			if (F2 != NULL) {
				printf("Les personnels de la region militaire 2: \n");
				int i = 1;
				while (fread(&personnel, sizeof(Tenreg), 1, F2) == 1) {	
					printf("%s\n", str);
					Afficher_Perso(personnel, i++);
				}
				printf("%s\n", str);
			}
			fclose(F2);
			break;
		}
		case 3: {
			FILE *F3 = fopen("F/F3", "rb");
			if (F3 != NULL) {
				printf("Les personnels de la region militaire 3: \n");
				int i = 1;
				while (fread(&personnel, sizeof(Tenreg), 1, F3) == 1) {			
					printf("%s\n", str);
					Afficher_Perso(personnel, i++);
				}	
				printf("%s\n", str);
			}
   		fclose(F3);
			break;
		}
		case 4: {
			FILE *F4 = fopen("F/F4", "rb");
			if (F4 != NULL) {
				printf("Les personnels de la region militaire 4: \n");
				int i = 1;
				while (fread(&personnel, sizeof(Tenreg), 1, F4) == 1) {	
					printf("%s\n", str);
					Afficher_Perso(personnel, i++);
				}	
				printf("%s\n", str);
			} 
   		fclose(F4);
			break;
		}
		case 5: {
			FILE *F5 = fopen("F/F5", "rb");
			if (F5 != NULL) {
				printf("Les personnels de la region militaire 5: \n");
				int i = 1;
				while (fread(&personnel, sizeof(Tenreg), 1, F5) == 1) {	
					printf("%s\n", str);
					Afficher_Perso(personnel, i++);
				}	
				printf("%s\n", str);
			}
   		fclose(F5);
			break;
		}
		case 6: {
			FILE *F6 = fopen("F/F6", "rb");
			if (F6 != NULL) {
				printf("Les personnels de la region militaire 6: \n");
				int i = 1;
				while (fread(&personnel, sizeof(Tenreg), 1, F6) == 1) { 			
					printf("%s\n", str);
					Afficher_Perso(personnel, i++);
				}	
				printf("%s\n", str);
			}
			fclose(F6);
			break;
		}
		default: {
			FILE *F1 = fopen("F/F1", "rb");
			FILE *F2 = fopen("F/F2", "rb");
			FILE *F3 = fopen("F/F3", "rb");
			FILE *F4 = fopen("F/F4", "rb");
			FILE *F5 = fopen("F/F5", "rb");
			FILE *F6 = fopen("F/F6", "rb");
			
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
 
			break;						
		}
	}

   return 0;
}

