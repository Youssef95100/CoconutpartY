#include <stdio.h>
#include <stdbool.h>
#include "sauvegarde.h"

void sauvegarder_partie(Couronne* couronne, Chemin* chemin, Crabe* crabes, int nb_crabes,
                        ListeSinges* liste_singes, EmplacementsSinges* emp, int num_vague) {
    FILE* fichier = fopen("save.dat", "w");
    if (!fichier) {
        printf("Erreur lors de l'ouverture du fichier de sauvegarde.\n");
        return;
    }

    fprintf(fichier, "Couronne: x=%d y=%d pv=%d\n", couronne->x, couronne->y, couronne->pv);

    fprintf(fichier, "NbCrabes: %d\n", nb_crabes);
    for (int i = 0; i < nb_crabes; i++) {
        fprintf(fichier, "Crabe %d: x=%d y=%d pv=%d position=%d actif=%d\n",
                i,
                crabes[i].x, crabes[i].y, crabes[i].pv,
                crabes[i].position, crabes[i].actif);
    }

    fprintf(fichier, "NbSinges: %d\n", liste_singes->nb_singes);
    for (int i = 0; i < liste_singes->nb_singes; i++) {
        fprintf(fichier, "Singe %d: x=%d y=%d degat=%d rayon=%d niveau=%d\n",
                i,
                liste_singes->singe[i].x,
                liste_singes->singe[i].y,
                liste_singes->singe[i].degat,
                liste_singes->singe[i].rayon,
                liste_singes->singe[i].niveau);
    }

    fprintf(fichier, "NbPositions: %d\n", emp->nb_positions);
    for (int i = 0; i < emp->nb_positions; i++) {
        fprintf(fichier, "Position %d: id=%c x=%d y=%d disponible=%d\n",
                i,
                emp->positions[i].id,
                emp->positions[i].x,
                emp->positions[i].y,
                emp->positions[i].disponible);
    }

    fprintf(fichier, "CheminTaille: %d\n", chemin->taille);
    for (int i = 0; i < chemin->taille; i++) {
        fprintf(fichier, "Case %d: x=%d y=%d\n",
                i,
                chemin->cases[i].x,
                chemin->cases[i].y);
    }

    fprintf(fichier, "NumVague: %d\n", num_vague);

    fclose(fichier);
}

