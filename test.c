#include <stdio.h>
#include <stdlib.h>
#include "structure.h"
// #include "menu.h"
#include "couronne.h"
#include "sauvegarde.h"
#include "crabe.h"


int main(){
    Couronne couronne;
    int vie_couronne = 0;
    Crabe *crabe = malloc(sizeof(Crabe));
    Singe singe; 
    int choix = 0;

    couronne.x = 0;
    couronne.y = 0;

    crabe->x = 10;
    crabe->y = 0;
    crabe->pv = 5;

    singe.x = 8;
    singe.y = 0;
    singe.rayon = 2;
    singe.degat = 1;
    
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
            break;
        case 2:
            printf("\nVous avez choisi de reprendre une ancienne partie !\n");
            // Appeler la fonction de reprise de partie ici
            break;
        case 3:
            printf("\nAu revoir !\n");
            break;
        default:
            printf("\nChoix invalide. ");
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







    
    // int pv_du_crabe = crabe->pv;
    // printf("Le crabe à %d PV\n", pv_du_crabe);
    // pv_du_crabe = baissePvCrabe(crabe, singe);
    // pv_du_crabe = pvCrabe(crabe);
    // crabe->x ++;
    // printf("%d\n", crabe->pv);
    // pv_du_crabe = baissePvCrabe(crabe, singe);
    // pv_du_crabe = pvCrabe(crabe);
    // crabe->x ++;
    // printf("%d\n", crabe->pv);
    // pv_du_crabe = baissePvCrabe(crabe, singe);
    // pv_du_crabe = pvCrabe(crabe);




