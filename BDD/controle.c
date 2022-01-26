#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <float.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <setjmp.h>
#include <signal.h>
#include <stdarg.h>
#include <stddef.h>
#include <time.h>


#ifdef LOCAL
#define debug(format, ...) { printf("[%s",#__VA_ARGS__);printf("] : ") ; printf(format"\n",__VA_ARGS__);}
#else
#define debug(...) 42
#endif


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


int main () {

	// le menu
	while (1) {
		system("clear");
		printf("Les champs d'information disponible a manipuler :  \n");
		printf("			1) La force armee \n");
		printf("			2) Le grade \n");
		printf("			3) Le groupe sanguin \n");
		printf("			4) La region militaire \n");
		printf("			5) La wilaya de naissance \n");
		printf("Choisissez une option : ");
		int option;	
		scanf("%d", &option);
		switch(option) {
			case 1: {	// force armee
				printf("Les options disponibles : \n");
				printf("			1) Lister les forces armees \n");
				printf("			2) Ajout une force armee \n");
				printf("			3) Suppression d'une force armee \n");
				printf("Choisissez une option : ");
				int opt;
				scanf("%d", &opt);
				switch(opt) { 
					case 1: {	// liste des forces armees disponibles
						FILE *F1 = fopen("force_armee.bin", "rb"); // ouverture du fichier des forces armees binaire
						int n;
						fread(&n, sizeof(int), 1, F1);
						Force_armee force_armee;
						while (fread(&force_armee, sizeof(Force_armee), 1, F1) == 1) {
							printf("%d %s\n", force_armee.num, force_armee.nom);	
						}
						fclose(F1);
						break;
					}
					case 2: {	// ajout d'une force armee
						FILE *F1 = fopen("force_armee.bin", "rb+"); // ouverture du fichier des forces armees binaire
						int n;
						fread(&n, sizeof(int), 1, F1); 
						n += 1;
						Force_armee force_armee;
						printf("Veuillez entrer la nouvelle force armee : ");
						char nom[52];
						scanf(" %[^\n]s", nom);		
						force_armee.num = n;
						strcpy(force_armee.nom, nom);
						fseek(F1, sizeof(int) + (n - 1) * sizeof(Force_armee), SEEK_SET);
						fwrite(&force_armee, sizeof(Force_armee), 1, F1);
						rewind(F1);
						fwrite(&n, sizeof(int), 1, F1);
						fclose(F1);
						break;
					}
					case 3: {	// suppression d'une force armee
						FILE *F1 = fopen("force_armee.bin", "rb"); // ouverture du fichier des forces armees binaire
						FILE *F = fopen("force_armee_temp.bin", "wb+"); // ouverture du fichier des forces armees binaire
						int n;
						fread(&n, sizeof(int), 1, F1); 
						n -= 1;
						fwrite(&n, sizeof(int), 1, F);			
						Force_armee force_armee;
						int num;
						printf("Veuillez entrer le numero de la force armee a supprimer : ");
						scanf("%d", &num);
						while (fread(&force_armee, sizeof(Force_armee), 1, F1) == 1) {
							if (force_armee.num == num) {
								continue;
							}
							fwrite(&force_armee, sizeof(Force_armee), 1, F);
						}
						fclose(F1);
						fclose(F);
						system("rm force_armee.bin && mv force_armee_temp.bin force_armee.bin");
						break;
					}
				}
   	  	   break;
			}

			case 2: {	// grade
				printf("Les options disponibles : \n");
				printf("			1) Liste des grades disponibles \n");
				printf("			2) Ajout un grade \n");
				printf("			3) Suppression un grade \n");
				printf("Choisissez une option : ");
				int opt;
				scanf("%d", &opt);
				switch(opt) {
					case 1: { 	// liste des grades 				  
						FILE *F2 = fopen("grade.bin", "rb");	// ouverture du fichier des grades binaire
						fseek(F2, sizeof(int), SEEK_SET);
						Grade grade;
						while (fread(&grade, sizeof(Grade), 1, F2) == 1) {
							printf("%d %s\n", grade.num, grade.nom);	
						}
						fclose(F2);
						break;
					}
					case 2: {	// ajout d'un grade 
						FILE *F2 = fopen("grade.bin", "rb+"); // ouverture du fichier des grades binaire
						int n;
						fread(&n, sizeof(int), 1, F2); 
						n += 1;
						Grade grade;
						printf("Veuillez entrer le nouveau grade : ");
						char nom[32];
						scanf(" %[^\n]s", nom);		
						grade.num = n;
						strcpy(grade.nom, nom);
						fseek(F2, sizeof(int) + (n - 1) * sizeof(Grade), SEEK_SET);
						fwrite(&grade, sizeof(Grade), 1, F2);
						rewind(F2);
						fwrite(&n, sizeof(int), 1, F2);
						fclose(F2);
						break;					
					}
					case 3: {	// suppression d'un grade
						FILE *F2 = fopen("grade.bin", "rb"); // ouverture du fichier des grades binaire
						FILE *F = fopen("grade_temp.bin", "wb+"); // ouverture du fichier des grades binaire
						int n;
						fread(&n, sizeof(int), 1, F2); 
						n -= 1;
						fwrite(&n, sizeof(int), 1, F);			
						Grade grade;
						int num;
						printf("Veuillez entrer le numero du grade a supprimer : ");
						scanf("%d", &num);
						while (fread(&grade, sizeof(Grade), 1, F2) == 1) {
							if (grade.num == num) {
								continue;
							}
							fwrite(&grade, sizeof(Grade), 1, F);
						}
						fclose(F2);
						fclose(F);
						system("rm grade.bin && mv grade_temp.bin grade.bin");  
						break;
					}
				}
				break;		  
			}	  
			case 3: {	// groupe sanguin
				FILE *F3 = fopen("groupe_sanguin.bin", "rb");		// ouverture du fichier des groupes sanguins binaire
				Groupe_sanguin groupe_sanguin;
				while (fread(&groupe_sanguin, sizeof(Groupe_sanguin), 1, F3)) {
					printf("%d %s\n", groupe_sanguin.num, groupe_sanguin.nom);	
				}
				fclose(F3);
				break;		  
			}	
			case 4: {	// region militaire
				printf("Les options disponibles : \n");
				printf("			1) Liste des regions militaires disponibles \n");
				printf("			2) Ajout d'une region militaire \n");
				printf("			3) Suppression d'une region militaire \n");
				printf("Choisissez une option : ");
				int opt;
				scanf("%d", &opt);
				switch(opt) {
					case 1: { 	// Liste des regions militaires
						FILE *F4 = fopen("region_militaire.bin", "rb"); // ouverture du fichier des regions militaire binaire
						fseek(F4, sizeof(int), SEEK_SET);
						Region_militaire region_militaire;
						while (fread(&region_militaire, sizeof(Region_militaire), 1, F4) == 1) {
							printf("%d %s\n", region_militaire.num, region_militaire.nom);	
						}
						fclose(F4);
						break;
					}
					case 2: {	// Ajout d'un region militaire
						FILE *F4 = fopen("region_militaire.bin", "rb+"); // ouverture du fichier des regions militaire binaire
						int n;
						fread(&n, sizeof(int), 1, F4); 
						n += 1;
						Region_militaire region_militaire;
						printf("Veuillez entrer la nouvelle region militaire : ");
						char nom[20];
						scanf(" %[^\n]s", nom);		
						region_militaire.num = n;
						strcpy(region_militaire.nom, nom);
						fseek(F4, sizeof(int) + (n - 1) * sizeof(Region_militaire), SEEK_SET);
						fwrite(&region_militaire, sizeof(Region_militaire), 1, F4);
						rewind(F4);
						fwrite(&n, sizeof(int), 1, F4);
						fclose(F4);
 					   break;
					}
					case 3: {	// Suppression d'une region militaire
						FILE *F4 = fopen("region_militaire.bin", "rb"); // ouverture du fichier des regions militaires  binaire
						FILE *F = fopen("region_militaire_temp.bin", "wb+"); // ouverture du fichier des regions militaires binaire
						int n;
						fread(&n, sizeof(int), 1, F4); 
						n -= 1;
						fwrite(&n, sizeof(int), 1, F);			
						Region_militaire region_militaire;
						int num;
						printf("Veuillez entrer le numero du grade a supprimer : ");
						scanf("%d", &num);
						while (fread(&region_militaire, sizeof(Region_militaire), 1, F4) == 1) {
							if (region_militaire.num == num) {
								continue;
							}
							fwrite(&region_militaire, sizeof(Region_militaire), 1, F);
						}
						fclose(F4);
						fclose(F);
						system("rm region_militaire.bin && mv region_miliraire_temp.bin region_militaire.bin");  
						break;
					}
				}
				break;		  
			}	  
			case 5: {	// wilaya de naissance
				printf("Les options disponibles : \n");
				printf("			1) Liste des wilayas \n");
				printf("			2) Ajout d'une wilaya \n");
				printf("			3) Suppression d'une wilaya \n");
				printf("Choisissez une option : ");
				int opt;
				scanf("%d", &opt);
				switch(opt) {
					case 1: {  // Ajout d'une wilaya 
						FILE *F5 = fopen("wilaya.bin", "rb"); // ouverture du wilayas de naissance binaire
						fseek(F5, sizeof(int), SEEK_SET);
						Wilaya wilaya;
						while (fread(&wilaya, sizeof(Wilaya), 1, F5) == 1) {
							printf("%d %s\n", wilaya.num, wilaya.nom);	
						}
						fclose(F5);
						break;
					}
					case 2 : {	// Ajout d'une wilaya
						FILE *F5 = fopen("wilaya.bin", "rb+"); // ouverture du wilayas de naissance binaire
						int n;
						fread(&n, sizeof(int), 1, F5); 
						n += 1;
						Wilaya wilaya;
						printf("Veuillez entrer la nouvelle wilaya : ");
						char nom[25];
						scanf(" %[^\n]s", nom);		
						wilaya.num = n;
						strcpy(wilaya.nom, nom);
						fseek(F5, sizeof(int) + (n - 1) * sizeof(Wilaya), SEEK_SET);
						fwrite(&wilaya, sizeof(Wilaya), 1, F5);
						rewind(F5);
						fwrite(&n, sizeof(int), 1, F5);
						fclose(F5);
						break;
					}
					case 3: {  // Suppression d'une wilaya 
						FILE *F5 = fopen("wilaya.bin", "rb"); // ouverture du wilayas de naissance binaire
					   FILE *F = fopen("wilaya_temp.bin", "wb+");
						int n;
						fread(&n, sizeof(int), 1, F5); 
						n -= 1;
						fwrite(&n, sizeof(int), 1, F);			
						Wilaya wilaya;
						int num;
						printf("Veuillez entrer le numero de la wilaya a supprimer : ");
						scanf("%d", &num);
						while (fread(&wilaya, sizeof(Wilaya), 1, F5) == 1) {
							if (wilaya.num == num) {
								continue;
							}
							fwrite(&wilaya, sizeof(Wilaya), 1, F);
						}
						fclose(F5);
						fclose(F);
						system("rm wilaya.bin && mv wilaya_temp.bin wilaya.bin");  
						break;
					}
				}
				break;		  
			}	  
		}	
		printf("Voullez vous continuer ? (O/N) : ");
		char opt1;
		scanf(" %c", &opt1);
		if ((opt1 == 'O') || (opt1 == 'o')) {
			continue;
		} else {
			break;
		}
	}
	printf("\nTime elapsed : %.3f s.\n",1.0 * clock() /CLOCKS_PER_SEC);
	return 0;
}
