#include <stdio.h>
#include <stdlib.h>
#include "structure.h"
#include "menu.h"
#include "couronne.h"
#include "sauvegarde.h"

int main(int argc, char* argv[]){
    Couronne couronne;
    Crabe crabe;
    Singe singe;


    int choix = menu();
    sauvegarderPartie(couronne);


    return 0;
}   


