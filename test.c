#include <stdio.h>
#include <stdlib.h>
#include "structure.h"
#include "menu.h"

int main(int argc, char* argv[]){
    Couronne couronne;
    Crabe crabe;
    int choix = menu();

    printf("Saisir le nombre de points de vie de la couronne\n");
    if (scanf("%d", &couronne.pv) != 1 || couronne.pv <= 0){
        printf("Erreur de saisie\n");
        return 1;
    }   
    return 0;
}   