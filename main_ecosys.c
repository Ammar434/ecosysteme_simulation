#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <strings.h>
#include "ecosys.h"

#define NB_PROIES 1500
#define NB_PREDATEURS 1500
#define T_WAIT 40000

float p_ch_dir = 0.01;
float p_reproduce_proie = 0.5;
float p_reproduce_predateur = 0.4;
int temps_repousse_herbe = -10;

int main(void)
{
  // srand(time(NULL));
  FILE *fichier;
  fichier = fopen("Evol_Pop.txt", "w");
  int tab_herbe[SIZE_X][SIZE_Y];
  init_tab(tab_herbe, 0);

  Animal *liste_proie = NULL;
  Animal *liste_predateur = NULL;

  for (int i = 0; i < NB_PROIES; i++)
  {
    int x = rand() % SIZE_X;
    int y = rand() % SIZE_Y;
    int energie = 10;
    ajouter_animal(x, y, energie, &liste_proie);
  }
  for (int j = 0; j < NB_PREDATEURS; j++)
  {
    int x = rand() % SIZE_X;
    int y = rand() % SIZE_Y;
    int energie = 10;
    ajouter_animal(x, y, energie, &liste_predateur);
  }
  // liste_proie->x = 0;
  // liste_proie->y = 2;
  // liste_predateur->x = 0;
  // liste_predateur->y = 1;
  // liste_predateur->dir[0] = -1;
  // liste_predateur->dir[1] = 0;
  // liste_proie->dir[0] = 0;
  // liste_proie->dir[1] = 0;
  // printf("Predateur %f\n", liste_predateur->energie);
  // printf("Proie %f\n", liste_proie->energie);
  // afficher_ecosys(liste_proie, liste_predateur);
  // rafraichir_predateurs(&liste_predateur, &liste_proie);
  // rafraichir_proies(&liste_proie, tab_herbe);
  // printf("Proie %f\n", liste_proie->energie);
  // printf("Proie %d\n", compte_animal_it(liste_proie));
  // printf("Predateur %d\n", compte_animal_it(liste_predateur));

  // printf("Predateur %f\n", liste_predateur->energie);
  // afficher_ecosys(liste_proie, liste_predateur);
  int i = compte_animal_it(liste_proie);
  int j = compte_animal_it(liste_predateur);
  int k = 0;
  while (i > 0 && j > 0)
  {
    i = compte_animal_it(liste_proie);
    j = compte_animal_it(liste_predateur);
    afficher_ecosys(liste_proie, liste_predateur);
    rafraichir_monde(tab_herbe);
    rafraichir_predateurs(&liste_predateur, &liste_proie);
    rafraichir_proies(&liste_proie, tab_herbe);

    // sleep(1);
    clear_screen();
    fprintf(fichier, "%d %d %d\n", k, i, j);
    printf("Proie %d\n", compte_animal_it(liste_proie));
    printf("Predateur %d\n", compte_animal_it(liste_predateur));
    k++;
  }

  liberer_liste_animaux(liste_proie);
  liberer_liste_animaux(liste_predateur);
  return 0;
}
