#ifndef terrain_h
#define terrain_h

#include "structure.h"
#include <sys/select.h>
#include <unistd.h>

#define DELAI_DEPLOIEMENT 10// nombre de frames avant de sortir un nouveau crabe 
#define TIMEOUT 1 // Timeout pour select (en secondes)

void initialisation(int HAUTEUR, int LARGEUR, int tab[HAUTEUR][LARGEUR]);
void chemin(int HAUTEUR, int LARGEUR, int tab[HAUTEUR][LARGEUR], Chemin* chemin);
void afficher(int HAUTEUR, int LARGEUR, char affichage[HAUTEUR][LARGEUR]);
void generer_emplacement(int HAUTEUR, int LARGEUR, int tab[HAUTEUR][LARGEUR], EmplacementsSinges* emp );
void menu_singe(EmplacementsSinges* emp);
void placer_singe(EmplacementsSinges* emp, int HAUTEUR, int LARGEUR, int tab[HAUTEUR][LARGEUR]);
void lire_action(char* action);



#endif