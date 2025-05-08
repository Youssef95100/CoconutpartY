#ifndef terrain_h
#define terrain_h

#include "structure.h"

void initialisation(int HAUTEUR, int LARGEUR, int tab[HAUTEUR][LARGEUR]);
void chemin(int HAUTEUR, int LARGEUR, int tab[HAUTEUR][LARGEUR]);
void afficher(int HAUTEUR, int LARGEUR, int tab[HAUTEUR][LARGEUR]);
void generer_emplacement(int HAUTEUR, int LARGEUR, int tab[HAUTEUR][LARGEUR], EmplacementsSinges* emp );
void menu_singe(EmplacementsSinges* emp);
void placer_singe(EmplacementsSinges* emp, int HAUTEUR, int LARGEUR, int tab[HAUTEUR][LARGEUR]);


#endif