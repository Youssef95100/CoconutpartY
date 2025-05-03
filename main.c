#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> //pour le bool
#include <unistd.h> // Pour sleep()
#include "structure.h"
#include "menu.h"
#include "couronne.h"
#include "sauvegarde.h"
#include "terrain.h"


int main(int argc, char** argv)
{
    
    bool joue = true;
    Couronne couronne;
    int choix = menu();

    printf("%d;%d",HAUTEUR, LARGEUR);
   //terrain
    int tab[HAUTEUR][LARGEUR];
    initialisation(&tab);
    chemin(&tab);

    while ( joue )
    {

        system("clear"); // Efface la console
        afficher(tab);
        sleep(1); //pause de 1 sec
    }
   
}
