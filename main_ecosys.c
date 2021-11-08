#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <strings.h>
#include "ecosys.h"

#define NB_PROIES 20
#define NB_PREDATEURS 0
#define T_WAIT 40000

float p_ch_dir = 0.01;
float p_reproduce_proie = 0.4;
float p_reproduce_predateur = 0.5;
int temps_repousse_herbe = -15;

int main(void)
{
  srand(time(NULL));
  int tab_herbe[SIZE_X][SIZE_Y];
  init_tab(tab_herbe, 0);

  Animal *liste_proie = NULL;
  Animal *liste_predateur = NULL;

  for (int i = 0; i < NB_PROIES; i++)
  {
    int x = rand() % SIZE_X;
    int y = rand() % SIZE_Y;
    int energie = rand() % 5;
    ajouter_animal(x, y, energie, &liste_proie);
  }
  for (int j = 0; j < NB_PREDATEURS; j++)
  {
    int x = rand() % SIZE_X;
    int y = rand() % SIZE_Y;
    int energie = rand() % 5;
    ajouter_animal(x, y, energie, &liste_predateur);
  }
  int i = 0;

  while (i < 5)
  {
    rafraichir_proies(&liste_proie, tab_herbe);
    afficher_ecosys(liste_proie, liste_predateur);
    i++;
  }
  printf("%d\n", compte_animal_it(liste_proie));
  printf("%d\n", i);
  return 0;
}
