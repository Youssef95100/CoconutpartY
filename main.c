#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> //pour le bool
#include <unistd.h> // Pour sleep()
#include <time.h>
#include "structure.h"
#include "menu.h"
#include "couronne.h"
#include "sauvegarde.h"
#include "terrain.h"
//#include "terrain.c" //il faut l'inclure si on ne le compile pas


int main(int argc, char** argv)
{
    srand(time(NULL)); // Initialiser le générateur de nombres aléatoires

    // Générer des dimensions aléatoires
    int LARGEUR = (rand() % (32 - 22 + 1)) + 22; // Largeur entre 22 et 32
    int HAUTEUR = (rand() % (21 - 16 + 1)) + 16; // Hauteur entre 16 et 21

    bool joue = true;
    Couronne couronne;
    //int choix = menu();

   //terrain
   int tab[HAUTEUR][LARGEUR];
    initialisation(HAUTEUR, LARGEUR, tab);
    chemin(HAUTEUR, LARGEUR, tab);

    while ( joue )
    {

        system("clear"); // Efface la console
        afficher(HAUTEUR, LARGEUR, tab);
        sleep(1); //pause de 1 sec
    }
   
}
