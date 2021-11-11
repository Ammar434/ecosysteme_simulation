#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <strings.h>
#include "ecosys.h"

#define NB_PROIES 100
#define NB_PREDATEURS 100
#define T_WAIT 40000
//0.01  0.34  0.62   -0.1
float p_ch_dir = 0.01;
float p_reproduce_proie = 0.25;
float p_reproduce_predateur = 0.62;
int temps_repousse_herbe = -5;

int main(void)
{
  srand(time(NULL));

  FILE *fichier;
  fichier = fopen("Evol_Pop.txt", "w");
  if (!fichier)
  {
    fprintf(stderr, "Erreur durant l'ouverture du fichier");
    exit(-1);
  }
  int tab_herbe[SIZE_X][SIZE_Y];
  init_tab(tab_herbe, 0);

  Animal *liste_proie = NULL;
  Animal *liste_predateur = NULL;

  for (int i = 0; i < NB_PROIES; i++)
  {
    int x = rand() % SIZE_X;
    int y = rand() % SIZE_Y;
    int energie = rand() % 30;
    ajouter_animal(x, y, energie, &liste_proie);
  }
  for (int j = 0; j < NB_PREDATEURS; j++)
  {
    int x = rand() % SIZE_X;
    int y = rand() % SIZE_Y;
    int energie = rand() % 30;
    ajouter_animal(x, y, energie, &liste_predateur);
  }

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

    sleep(0.2);
    clear_screen();
    fprintf(fichier, "%d %d %d\n", k, i, j);
    printf("Proie %d\n", i);
    printf("Predateur %d\n", j);
    printf("Generation %d\n", k);
    k++;
  }

  liberer_liste_animaux(liste_proie);
  liberer_liste_animaux(liste_predateur);
  fclose(fichier);
  return 0;
}
