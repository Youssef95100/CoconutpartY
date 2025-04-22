#include "sauvegarde.h"

// Fonction pour sauvegarder la partie
void sauvegarderPartie(Couronne couronne, Crabe *crabe, Singe singe){ 
    // Ouverture du fichier de sauvegarde
    FILE *fichier = fopen("sauvegarde.txt", "w");
    if (fichier == NULL) {
        printf("Erreur : Impossible de créer le fichier de sauvegarde.\n");
        return;
    }

    // Sauvegarde des données de la couronne
    fprintf(fichier, "PV de la couronne: %d\n", couronne.pv);
    fprintf(fichier, "Position de la couronne: (%d, %d)\n", couronne.x, couronne.y);

    // Sauvegarde des données du crabe
    fprintf(fichier, "PV du crabe: %d\n", crabe->pv);
    fprintf(fichier, "Position du crabe: (%d, %d)\n", crabe->x, crabe->y);

    // Sauvegarde des données du singe
    fprintf(fichier, "Position du singe: (%d, %d)\n", singe.x, singe.y);
    fprintf(fichier, "Rayon du singe: %d\n", singe.rayon);
    fprintf(fichier, "Dégâts du singe: %d\n", singe.degat);




    fclose(fichier);
    printf("Partie sauvegardée avec succès !\n");
}