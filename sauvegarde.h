#ifndef sauvegarde_h
#define sauvegarde_h

#include <stdio.h>
#include <stdlib.h>
#include "structure.h"

// Fonction pour sauvegarder la partie
void sauvegarderPartie(Couronne couronne){ // rajouter crabe et singe
    // Ouverture du fichier de sauvegarde
    FILE *fichier = fopen("sauvegarde.txt", "w");
    if (fichier == NULL) {
        printf("Erreur : Impossible de créer le fichier de sauvegarde.\n");
        return;
    }

    // Sauvegarde des données de la couronne
    fprintf(fichier, "PV de la couronne: %d\n", couronne.pv);
    fprintf(fichier, "Position de la couronne: (%d, %d)\n", couronne.x, couronne.y);



    fclose(fichier);
    printf("Partie sauvegardée avec succès !\n");
}

#endif