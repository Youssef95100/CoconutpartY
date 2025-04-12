#ifndef menu_h
#define menu_h


#include <stdio.h>
#include <stdlib.h>
#include "structure.h"
#include "couronne.h"

int menu(){
    int choix = 0;
    Couronne couronne;
    int vie_couronne = 0;  
    printf("\nBienvenue dans CoconutpartY !\n\n");
    printf("1. Jouer\n");
    printf("2. Reprendre une ancienne partie\n");
    printf("3. Quitter le jeu\n");
    printf("\nVeuillez entrer votre choix : ");
    
    if (scanf("%d", &choix) != 1) {
        printf("Erreur de saisie\n");
        return 1;
    }
    
    switch (choix) {
        case 1:
            printf("\nVous avez choisi de jouer !\n\n");
            vie_couronne = ini_couronne(couronne);
            // Appeler la fonction de jeu ici
            break;
        case 2:
            printf("\nVous avez choisi de reprendre une ancienne partie !\n");
            // Appeler la fonction de reprise de partie ici
            break;
        case 3:
            printf("\nAu revoir !\n");
            break;
        default:
            printf("\nChoix invalide. ");//ajouter boucle pour réessayer

            do { // si on met une bonne valeur (1,2,3) ca fais affiche pas jouer, sauvegarder, etc..
                printf("Veuillez entrer votre choix : "); 
                if (scanf("%d", &choix) != 1) {
                    printf("Erreur de saisie\n");
                    return 1;
                }
            } while (choix < 1 || choix > 3);
            break;
    }
    
    return 0;
}



#endif