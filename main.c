#include <stdio.h>
#include <stdlib.h>
#include "structure.h"



int main(int argc, char* argv[]){
    Couronne couronne;
    printf("Saisir le nombre de points de vie de la couronne\n");
    if (scanf("%d", &couronne.pv) != 1 || couronne.pv <= 0){
        printf("Erreur de saisie\n"); //a fixer (boucle)
        return 1;
    } 
    
}