#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "ecosys.h"

/* PARTIE 1*/
/* Fourni: Part 1, exercice 3, question 2 */
Animal *creer_animal(int x, int y, float energie)
{
  Animal *na = (Animal *)malloc(sizeof(Animal));
  assert(na);
  na->x = x;
  na->y = y;
  na->energie = energie;
  na->dir[0] = rand() % 3 - 1;
  na->dir[1] = rand() % 3 - 1;
  na->suivant = NULL;
  return na;
}

/* Fourni: Part 1, exercice 3, question 3 */
Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal)
{
  assert(animal);
  assert(!animal->suivant);
  animal->suivant = liste;
  return animal;
}

/* A faire. Part 1, exercice 5, question 1 */
void ajouter_animal(int x, int y, float energie, Animal **liste_animal)
{
  Animal *tmp_animal = creer_animal(x, y, energie);
  *liste_animal = ajouter_en_tete_animal(*liste_animal, tmp_animal);
}

/* A Faire. Part 1, exercice 5, question 5 */
void enlever_animal(Animal **liste, Animal *animal)
{
  Animal *prev;
  Animal *to_find;
  if (*liste != NULL)
  {
    if ((*liste)->x == animal->x && (*liste)->y == animal->y && (*liste)->energie == animal->energie)
    {
      to_find = *liste;
      *liste = (*liste)->suivant;
      free(to_find);
    }
    else
    {
      prev = *liste;
      to_find = (*liste)->suivant;
      while (to_find)
      {
        if ((to_find->x = animal->x && to_find->y == animal->y) && (*liste)->energie == animal->energie)
        {
          prev->suivant = to_find->suivant;
          free(to_find);
          break;
        }
        prev = to_find;
        to_find = to_find->suivant;
      }
    }
  }
}

void enlever_animal_plus_energie(Animal **liste)
{
  Animal *aSupprimer;
  Animal *precedent;
  Animal *n;
  while (*liste != NULL && (*liste)->energie <= 0)
  {
    aSupprimer = *liste;
    *liste = (*liste)->suivant;
    free(aSupprimer);
  }
  if (*liste != NULL)
  {
    precedent = *liste;
    n = precedent->suivant;
    while (n != NULL)
    {
      while (n != NULL && n->energie <= 0)
      {
        aSupprimer = n;
        n = n->suivant;
        precedent->suivant = n;
        free(aSupprimer);
      }
      if (n != NULL)
      {
        precedent = n;
        n = n->suivant;
      }
    }
  }
}
/* A Faire. Part 1, exercice 5, question 2 */
Animal *liberer_liste_animaux(Animal *liste)
{
  Animal *tmp = NULL;
  while (liste)
  {
    tmp = liste->suivant;
    free(liste);
    liste = tmp;
  }
  return NULL;
}

/* Fourni: part 1, exercice 3, question 4 */
unsigned int compte_animal_rec(Animal *la)
{
  if (!la)
    return 0;
  return 1 + compte_animal_rec(la->suivant);
}

/* Fourni: part 1, exercice 3, question 4 */
unsigned int compte_animal_it(Animal *la)
{
  int cpt = 0;
  while (la)
  {
    ++cpt;
    la = la->suivant;
  }
  return cpt;
}

/* Part 1. Exercice 4, question 1 */
void afficher_ecosys(Animal *liste_proie, Animal *liste_predateur)
{
  unsigned int i, j;
  char ecosys[SIZE_X][SIZE_Y];

  /* on initialise le tableau */
  for (i = 0; i < SIZE_X; i++)
  {
    for (j = 0; j < SIZE_Y; j++)
    {
      ecosys[i][j] = ' ';
    }
  }

  /* on ajoute les proies */
  if (liste_proie == NULL)
    printf("Liste proie vide \n");
  else
  {
    while (liste_proie != NULL)
    {
      ecosys[liste_proie->x][liste_proie->y] = 'H';
      liste_proie = liste_proie->suivant;
    }
  }

  /* on ajoute les predateurs */
  if (liste_predateur == NULL)
    printf("Liste predateur vide \n");
  else
  {
    while (liste_predateur != NULL)
    {
      ecosys[liste_predateur->x][liste_predateur->y] = 'C';
      liste_predateur = liste_predateur->suivant;
    }
  }

  /* on affiche le tableau */
  for (j = 0; j <= SIZE_Y + 1; j++)
  {
    for (i = 0; i <= SIZE_X + 1; i++)
    {
      if ((i == 0 && j == 0) || (i == 0 && j == SIZE_Y + 1) || (i == SIZE_X + 1 && j == SIZE_Y + 1) || (i == SIZE_X + 1 && j == 0))
        printf("+");
      else if ((i == 0 && j < SIZE_Y + 2) || (i == SIZE_X + 1 && j < SIZE_Y + 2))
        printf("|");
      else if ((i != 0 && j == 0) || (i != 0 && j == SIZE_Y + 1))
        printf("-");
      else
        printf("%c", ecosys[i - 1][j - 1]);
    }
    printf("\n");
  }
}

void clear_screen()
{
  printf("\x1b[2J\x1b[1;1H"); /* code ANSI X3.4 pour effacer l'ecran */
}

/* PARTIE 2*/
/* Part 2. Exercice 4, question 1 */

void move(Animal *la)
{
  //Mouvement sur x
  if (la->dir[1] >= 0) //Mouvement vers la gauche
  {
    if (la->x - la->dir[1] % SIZE_X < 0)
      la->x = SIZE_X - la->dir[1] % SIZE_X;
    else
      la->x = la->x - la->dir[1] % SIZE_X;
  }
  else //mouvement vers la droite
  {
    if (la->x - la->dir[1] % SIZE_X >= SIZE_X)
      la->x = -la->dir[1] % SIZE_X - 1;
    else
      la->x = la->x - la->dir[1] % SIZE_X;
  }

  //Mouvement sur y
  if (la->dir[0] >= 0) // Mouvement vers le haut
  {
    if (la->y - la->dir[0] % SIZE_Y < 0)
      la->y = SIZE_Y - la->dir[0] % SIZE_Y;
    else
      la->y = la->y - la->dir[0] % SIZE_Y;
  }
  else //Mouvement vers le bas
  {
    if (la->y - la->dir[0] % SIZE_Y >= SIZE_Y)
      la->y = -la->dir[0] % SIZE_Y - 1;
    else
      la->y = la->y - la->dir[0] % SIZE_Y;
  }
}

void change_direction(Animal *la)
{
  if ((float)rand() / (float)RAND_MAX < p_ch_dir)
  {
    la->dir[0] = rand() % 3 - 1;
    la->dir[1] = rand() % 3 - 1;
  }
}

void bouger_animaux(Animal *la)
{
  while (la)
  {
    change_direction(la);
    move(la);
    la = la->suivant;
  }
}

/* Part 2. Exercice 4, question 3 */
void reproduce(Animal **liste_animal, float p_reproduce)
{
  Animal *liste_debut = *liste_animal;
  while (liste_debut)
  {
    if ((float)rand() / (float)RAND_MAX < p_reproduce)
    {
      ajouter_animal(liste_debut->x, liste_debut->y, liste_debut->energie / 2, liste_animal);
      liste_debut->energie = liste_debut->energie / 2;
    }
    liste_debut = liste_debut->suivant;
  }
}

/* Part 2. Exercice 6, question 1 */
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y])
{
  Animal *liste_debut = *liste_proie;

  if ((*liste_proie) != NULL)
  {
    bouger_animaux(liste_debut);

    while (liste_debut)
    {
      liste_debut->energie = liste_debut->energie - 1.0;

      // Manger
      if (monde[liste_debut->x][liste_debut->y] > 0)
      {
        liste_debut->energie = liste_debut->energie + monde[liste_debut->x][liste_debut->y];
        monde[liste_debut->x][liste_debut->y] = temps_repousse_herbe;
      }

      liste_debut = liste_debut->suivant;
    }
    // A optimiser - Pas efficace
    enlever_animal_plus_energie(liste_proie);

    reproduce(liste_proie, p_reproduce_proie);
  }
}

/* Part 2. Exercice 7, question 1 */
Animal *animal_en_XY(Animal *l, int x, int y)
{
  while (l)
  {
    if (l->x == x && l->y == y)
      return l;
    l = l->suivant;
  }
  return NULL;
}

/* Part 2. Exercice 7, question 2 */
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie)
{
  Animal *liste_debut = *liste_predateur;

  if ((*liste_predateur) != NULL)
  {
    bouger_animaux(liste_debut);
    while (liste_debut)
    {
      liste_debut->energie = liste_debut->energie - 1.0;
      // Manger
      Animal *animalAManger = animal_en_XY(*liste_proie, liste_debut->x, liste_debut->y);
      if (animalAManger != NULL)
      {
        liste_debut->energie = liste_debut->energie + animalAManger->energie;
        animalAManger->energie = 0;
      }

      liste_debut = liste_debut->suivant;
    }
    enlever_animal_plus_energie(liste_predateur);
    reproduce(liste_predateur, p_reproduce_predateur);
  }
}

/* Part 2. Exercice 5, question 2 */
void rafraichir_monde(int monde[SIZE_X][SIZE_Y])
{
  for (int i = 0; i < SIZE_X; i++)
  {
    for (int j = 0; j < SIZE_Y; j++)
    {
      monde[i][j] = monde[i][j] + 1;
      // printf("herbe dispo %d\n", monde[i][j]);
    }
  }
}

//On initialise un tableau !!!Fonction non obligatoire!!!
void init_tab(int tab[SIZE_X][SIZE_Y], int value)
{
  for (int i = 0; i < SIZE_X; i++)
  {
    for (int j = 0; j < SIZE_Y; j++)
    {
      tab[i][j] = 0;
    }
  }
}
