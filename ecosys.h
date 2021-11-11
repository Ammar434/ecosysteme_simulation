#ifndef _ECOSYS_H_
#define _ECOSYS_H_

#define SIZE_X 1000
#define SIZE_Y 1000

typedef struct _animal
{
  int x;
  int y;
  int dir[2]; /* direction courante sous la forme (dx, dy) */
  float energie;
  struct _animal *suivant;
} Animal;

Animal *creer_animal(int x, int y, float energie);
Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal);
unsigned int compte_animal_rec(Animal *la);
unsigned int compte_animal_it(Animal *la);

void ajouter_animal(int x, int y, float energie, Animal **liste_animal);
void enlever_animal(Animal **liste, Animal *animal);
Animal *liberer_liste_animaux(Animal *liste);
void afficher_ecosys(Animal *liste_proie, Animal *liste_predateur);

void bouger_animaux(Animal *la);
Animal *animal_en_XY(Animal *l, int x, int y);
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie);
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]);
void rafraichir_monde(int monde[SIZE_X][SIZE_Y]);

void clear_screen();

void move(Animal *la);
void change_direction(Animal *la);
void reproduce(Animal **liste_animal, float p_reproduce);
void init_tab(int tab[SIZE_X][SIZE_Y], int value);

extern float p_ch_dir; //probabilte de changer de direction de dsplacement
extern float p_reproduce_proie;
extern float p_reproduce_predateur;
extern int temps_repousse_herbe;

#endif
