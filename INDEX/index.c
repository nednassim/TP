/*	fichier pour la manipulation de la table et le fichier d'index */

#include "../machine.c"
#include "../fonction.c"


typedef struct index {
   int cle;
   int adr;
   int age;
   int grade;
   int force_armee;
   int region_militaire;
} index;



index creer_index();
void ajout_index();
void supp_index();
int index_plein();
int index_vide();
int taille_index();





int main () {

	printf("\nTime elapsed : %.3f s.\n",1.0 * clock() /CLOCKS_PER_SEC);
   return 0;
}
       


