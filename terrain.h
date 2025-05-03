#ifndef terrain_h
#define terrain_h
#include <stdlib.h>

#define HAUTEUR (int)16
#define LARGEUR (int)22

#include "terrain.c"


void initialisation(int (*tab)[HAUTEUR][LARGEUR]);
void chemin(int (*tab)[HAUTEUR][LARGEUR]);

void afficher(int tab[HAUTEUR][LARGEUR]);


#endif