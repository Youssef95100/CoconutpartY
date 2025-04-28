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

    while ( joue )
    {

        system("clear"); // Efface la console
        afficher();
        sleep(1); //pause de 1 sec
    }
   
}
