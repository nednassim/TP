#include "fonction.c"


void debut() {
   printf("\t\t*********************************************************************************\n");
	printf("\t\t*\t\t\t\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\tEcole Nationale Superieure d'Informatique (ESI)\t\t\t*\n");
	printf("\t\t*\t\t\t\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\t\t\t  TP SFSD\t\t\t\t\t*\n");
	printf("\t\t*\t\tStructure simple de fichiers - Methode: LObarreF\t\t*\n");
	printf("\t\t*\t\t\t\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\t\tSupervise par : Dr Kermi Adel\t\t\t\t*\n");
	printf("\t\t*\t\t\t\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\t\t  NEDJAR Nassim	groupe 4\t\t\t\t*\n");
	printf("\t\t*\t\t\tAnnee Universitaire : 2021/2022\t\t\t\t*\n");
	printf("\t\t*\t\t\t\t\t\t\t\t\t\t*\n");
	printf("\t\t*\t\t\t\t\t\t\t\t\t\t*\n");
	printf("\t\t*********************************************************************************\n\n\n\n");
}
int main () {
	system("clear");
	debut();
	printf("\n\t\t\t\t\t Soyez les bienvenues !\n\n\n\n ");
   for (int each = 0; each < 4; ++each) {
	   printf ( "\r\t\t\tChargement du programme de gestion du corps militaire %.*s   \b\b\b", each, "...");
      fflush ( stdout);//force printing as no newline in output
      system("sleep 1");
  	}
	srand(time(NULL));
	while (1) {
		system("clear");
		debut();
		printf("Les options disponibles sont : \n\n");
		printf("\t1) Creation du fichier de donnees PERSONNEL-ANP_DZ.bin\n");
		printf("\t2) Epuration du fichier de donnees PERSONNEL-ANP_DZ.bin des dupliques (deduplication)\n");
		printf("\t3) Insertion d'un nouvel personnel au fichier de donnees PERSONNEL-ANP_DZ.bin\n");
		printf("\t4) Modification de la region militaire d'un personnel\n");
		printf("\t5) Suppression d'un ou plusieurs personnels selon un critere donne\n");
		printf("\t6) Consultation d'un ou plusieurs personnels selon un critere donne \n");
		printf("\t7) Fragmentation du fichier de donnees PERSONNEL-ANP_DZ.bin en 6 fichiers selon la region militaire \n");
		printf("\t8) Manipulation des fichiers de la structure du corps militaire \n");
		printf("\n\n\tPour quitter, veuillez faire entrer CTRL+C \n");
		printf("\t\t \n");
		printf("Veuillez choisir une option : ");
		int opt;
		scanf("%d", &opt);
		switch(opt) {
			case 1: {
				system("clear");
				debut();
				printf("Veuillez entrer le nombre de personnels : ");
				int N;
				scanf("%d", &N);
				Chargement_Initial("PERSONNEL-ANP_DZ.bin", N);
				printf("Operation de creation terminee avec succes!\n");
				printf("Voulez vous afficher le fichier de donnees PERSONNEL-ANP_DZ.bin? (O/N) ");
				char opt1;
				scanf(" %c", &opt1);
				if ((opt1 == 'O') || (opt1 == 'o')) {
					F = Ouvrir("PERSONNEL-ANP_DZ.bin", 'A');
					Afficher_Fichier(F);
					Fermer(F);
				} 
				break;			 
			}
			case 2: {
				system("clear");
				debut();
				F = Ouvrir("PERSONNEL-ANP_DZ.bin", 'A');
				Epuration(F);
				printf("Operation d'epuration terminee avec succes!\n");
				printf("Voulez vous afficher le fichier de donnees PERSONNEL-ANP_DZ.bin? (O/N) ");
				char opt1;
				scanf(" %c", &opt1);
				if ((opt1 == 'O') || (opt1 == 'o')) {
					Afficher_Fichier(F);
				} 
				Fermer(F);
				break;			 
			}
			case 3: {
				system("clear");
				debut();
				F = Ouvrir("PERSONNEL-ANP_DZ.bin", 'A');
				Insertion(F);
				printf("Operation d'insertion du nouvel personnel erminee avec succes!\n");
				printf("Voulez vous afficher le fichier de donnees PERSONNEL-ANP_DZ.bin? (O/N) ");
				char opt1;
				scanf(" %c", &opt1);
				if ((opt1 == 'O') || (opt1 == 'o')) {
					Afficher_Fichier(F);
				} 
				Fermer(F);	  
				break;			 
			}
			case 4: {
				system("clear");
				debut();
				F = Ouvrir("PERSONNEL-ANP_DZ.bin", 'A');
				Afficher_Fichier(F);
				printf("Veuillez entrer la matricule du personnel voulu : ");
				int matricule;
				scanf("%d", &matricule);
				printf("Veuillez entrer la nouvelle region militaire : ");
				int region_militaire;
				scanf("%d", &region_militaire);
				int pos;
				Tenreg personnel = Modifier_Region_Militaire(F, matricule , region_militaire, &pos);
				printf("*+--------------------------------------------+*\n");
				Afficher_Perso(personnel, pos);
				printf("*+--------------------------------------------+*\n");
				printf("Operation de modification de region terminee avec succes!\n");
				Fermer(F);
				break;			 
			}
			case 5: {
				system("clear");
				debut();
				printf("\nLes options disponibles : \n\n");
				printf("\t1) Suppression d'un personnel donne par le matricule\n");
				printf("\t2) Suppression de tous les personnels relatif a une force armee donnee\n");
				printf("\nVeuillez choisir une option : ");
				int opt1;
				scanf("%d", &opt1);
				F = Ouvrir("PERSONNEL-ANP_DZ.bin", 'A');
				Afficher_Fichier(F);
				switch(opt1) {
					case 1: {
						Afficher_Fichier(F);
						printf("Veuillez entrer la matricule du personnel voulu : ");
						int matricule;
						scanf("%d", &matricule);
						Suppression(F, matricule);
						printf("Operation de supression du personnel terminee avec succes!\n");
						break;			 
					}
					case 2: {
						Afficher_Fichier(F);
						printf("Veuillez entrer la force armme voulu : ");
						int force_armee;
						scanf("%d", &force_armee);
						Suppression_Force_Armee(F, force_armee);
						printf("Operation de supressino de la force armee  terminee avec succes!\n");
						break;			 
					}
					default : {
						printf("Option indisponible !\n");
						break;
					}
				}
				printf("Voulez vous afficher le fichier de donnees PERSONNEL-ANP_DZ.bin? (O/N) ");
				char opt2;
				scanf(" %c", &opt2);
				if ((opt2 == 'O') || (opt2 == 'o')) {
					Afficher_Fichier(F);
				} 
				Fermer(F);
				break;			 
			}
			case 6: {
				system("clear");
				debut();
				printf("\nLes options disponibles : \n\n");
				printf("\t1) Consultation de tous les personnels du fichier de donnees \n");
				printf("\t2) Consultation de tous les personnels relatifs a une region militaire donnee ayant un age entre deux valeurs \n");
				printf("\t3) Consultation de tous les personnels appartenant a une categorie de grade donnee \n");
				printf("\t4) Consultation des personnels appartenant a une region militaire donnee \n");
				printf("\t5) Consultation de la table d'index \n");
				printf("\nVeuillez choisir une option : ");
				int opt1;
				scanf("%d", &opt1);
				F = Ouvrir("PERSONNEL-ANP_DZ.bin", 'A');
				switch(opt1) {
					case 1: {
						Afficher_Fichier(F);
						break;
					}
					case 2: {
						printf("Veuillez entrer la region militaire voulu : ");
						int region_militaire;
						scanf("%d", &region_militaire);
						printf("Veuillez entrer l'age minimum est l'age maximum tels que l'age du personnel appartient a [age_min, age_max] : ");
						int age_min, age_max;
						scanf("%d %d", &age_min, &age_max);
						int n;
						Tenreg *personnels = Recherche_Intervale(F, region_militaire, age_min, age_max, &n);
						printf("*+--------------------------------------------+*\n");
						for (int i = 0; i < n; i++) {
							Afficher_Perso(personnels[i], i + 1);
							printf("*+--------------------------------------------+*\n");
						}
						free(personnels);
						break;			 
					}
					case 3: {
						printf("Veuillez entrer la categorie de grade voulue : ");
						int categorie_grade;
						scanf("%d", &categorie_grade);
						int n;
						Tenreg *personnels = Recherche_Categorie_Grade(F, categorie_grade, &n);
						printf("*+--------------------------------------------+*\n");
						for (int i = 0; i < n; i++) {
							Afficher_Perso(personnels[i], i + 1);
							printf("*+--------------------------------------------+*\n");
						}
						free(personnels);
						break;			 
					}
					case 4: {
						system("./F/controle");
						break;
					}
					case 5 : {
						printf("La table d'index correspondante au fichier de donnees PERSONNEL-ANP_DZ.bin : \n");
						Afficher_Table_Index();
						break;
					}
					default : {
						printf("Option indisponible !\n");
						break;
					}
				}
				Fermer(F);
				break;			 
			}
			case 7: {
				F = Ouvrir("PERSONNEL-ANP_DZ.bin", 'A');
				Fragmentation(F);
				printf("Operation de fragmentation du fichier de donnees terminee avec succes!\n");
				Fermer(F);
				break;			 
			}
			case 8: {
				char mot_de_passe[10];
				printf("Entrer votre mot de passe : ");
				scanf("%s", mot_de_passe);
				if (!strcmp(mot_de_passe, "Chengriha") || !strcmp(mot_de_passe, "Tebboune"))  {
					system("BDD/controle");
				} else {
					printf("Vous n'avez pas le previlege a manipuler ces fichiers \n");	
				}				
				break;
			}
			default: {
				printf("Cette option est indisponible, veuillez reessayer!\n");						
			}
		}
		printf("Voullez vous continuer ? (O/N) : ");
		char opt1;
		scanf(" %c", &opt1);
		if ((opt1 == 'O') || (opt1 == 'o')) {
			continue;
		}
		if ((opt1 == 'N') || (opt1 == 'n')) {
			printf("Etes vous sur de quitter ? (O/N) : ");
			char opt2;
			scanf(" %c", &opt2);
			if ((opt2 == 'O') || (opt2 == 'o')) {
				system("clear");
				debut();
				printf("\n\t\t\t\t\t Merci pour votre confiance !\n\n\n\n ");
			   for (int each = 0; each < 4; ++each) {
				   printf ( "\r\t\t\t Fermeture du programme de gestion du corps militaire %.*s   \b\b\b", each, "...");
			      fflush ( stdout);//force printing as no newline in output
			      system("sleep 1");
			  	}
				break;
			}
			if ((opt2 == 'N') || (opt2 == 'n')) {
				continue;
			}
		}
	}
	printf("\nTime elapsed : %.3f s.\n",1.0 * clock() /CLOCKS_PER_SEC);
	return 0;
}
