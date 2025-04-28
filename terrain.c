#include "terrain.h"




void afficher()
{    
    int tab[HAUTEUR][LARGEUR];

    // Setup des valeur a O
    for (int i = 0; i < HAUTEUR; i++) 
    {
        for (int j = 0; j < LARGEUR; j++) 
        {
            tab[i][j] = 79;
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