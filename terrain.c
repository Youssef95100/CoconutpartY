#include "terrain.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


void initialisation(int HAUTEUR, int LARGEUR, int tab[HAUTEUR][LARGEUR])
{
    // Setup des valeur a espace
    for (int i = 0; i < HAUTEUR; i++) 
    {
        for (int j = 0; j < LARGEUR; j++) 
        {
            tab[i][j] = 32;
        }
    }
    
    //setup des bordures en haut et en bas
    for(int i = 0; i < LARGEUR; i++)
    {
        tab[0][i] = 151;
        tab[HAUTEUR - 1][i] = 151;
    }

    //setup des bordures a gauche et a droite
    for(int i = 0; i < HAUTEUR; i++)
    {
        tab[i][0] = 124;
        tab[i][LARGEUR - 1] = 124;
    }
}

void chemin(int HAUTEUR, int LARGEUR, int tab[HAUTEUR][LARGEUR])
{
    srand(time(NULL)); // Initialiser le générateur de nombres aléatoires

    //Point de départ
    int pdp_valeur = ( rand() % (HAUTEUR -1) ) ;
    tab[pdp_valeur][LARGEUR -2] = 35;

    //Point d'arrivé théorique
    int pda_valeur = ( rand() % (HAUTEUR -1) ) +1 ;


    int hauteur_actuelle = pdp_valeur;
    int largeur_actuelle = LARGEUR -1;

    // Générer le chemin jusqu'à la colonne 0
    while (largeur_actuelle > 0)
    {
        // Déplacer vers la gauche
        largeur_actuelle--;

        // Déterminer si on monte, descend ou reste sur la même ligne
        int direction = rand() % 3; // 0 = monter, 1 = descendre, 2 = avancer

        if (direction == 0 && hauteur_actuelle > 1 && hauteur_actuelle > pda_valeur)
        {
            hauteur_actuelle--; // Monter
        }
        else if(direction == 1 && hauteur_actuelle < HAUTEUR - 2 && hauteur_actuelle < pda_valeur)
        {
            hauteur_actuelle++; // Descendre
        }
        else if(direction == 2 && largeur_actuelle > 1)
        {
            largeur_actuelle--; // Avancer
        }

        // Marquer le chemin avec '.'
        if (tab[hauteur_actuelle][largeur_actuelle] != 'X'
            && tab[hauteur_actuelle][largeur_actuelle] != '#'
            && largeur_actuelle > 0) 
        {
            tab[hauteur_actuelle][largeur_actuelle] = '.';
        }

        // Vérifier que le chemin reste adjacent
        if (largeur_actuelle > 1 && tab[hauteur_actuelle][largeur_actuelle - 1] != '.' &&
        tab[hauteur_actuelle][largeur_actuelle - 1] != 'X')
        {
            tab[hauteur_actuelle][largeur_actuelle - 1] = '.';
        }

    }

        //Point d'arrivé réel
        tab[hauteur_actuelle][1] = 88;
}

void afficher(int HAUTEUR, int LARGEUR, int tab[HAUTEUR][LARGEUR])
{    

    // Affichage du tableau
    for (int i = 0; i < HAUTEUR; i++) 
    {
        for (int j = 0; j < LARGEUR; j++) 
        {
            printf("%c ", tab[i][j]);
        }
        printf("\n");
    }

}