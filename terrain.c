#include "terrain.h"
#include "structure.h"
#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>




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
    int pdp_valeur = (( rand() % (HAUTEUR -2)) + 1 ) ;
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

void generer_emplacement(int HAUTEUR, int LARGEUR, int tab[HAUTEUR][LARGEUR], EmplacementsSinges* emp )
{
    
    (*emp).nb_positions = 0;
    char lettre = 'a';

    for(int i=1; i < HAUTEUR - 1; i++)
    {
        for(int j=1; j < LARGEUR - 1; j++)
        {   

            bool placer =(rand() % 4 == 0); //pour que l'apparition des singes soit aléatoire
            if(placer)
            {
                if(tab[i][j] == 32)//si la case est vide
                {
                    if(tab[i-1][j] == '.' || tab[i+1][j] == '.' || tab[i][j+1] == '.' || tab[i][j-1] == '.')
                    {
                        if((*emp).nb_positions < MAX_POSITIONS)
                        {
                            tab[i][j] = lettre;
                            (*emp).positions[(*emp).nb_positions].id = lettre;
                            (*emp).positions[(*emp).nb_positions].x = i;
                            (*emp).positions[(*emp).nb_positions].y = j;
                            (*emp).positions[(*emp).nb_positions].disponible = 1;
                            (*emp).nb_positions++;
                            lettre++;

                        }
                    }
                }
            }
        }
    }
}


void menu_singe(EmplacementsSinges* emp)
{
    printf("\n MENU DE POSITIONNEMENT DES SINGES \n");
    for(int i = 0; i < (*emp).nb_positions; i++)
    {
        if((*emp).positions[i].disponible == 1)
        {
            printf("%c : case (%d, %d)\n", (*emp).positions[i].id, (*emp).positions[i].x, 
            (*emp).positions[i].y);

        }
    }
    printf("Choisir la lettre correspondant à l'emplacement voulu :");
}


void placer_singe(EmplacementsSinges* emp, int HAUTEUR, int LARGEUR, int tab[HAUTEUR][LARGEUR])
{
    char choix;
    scanf(" %c", &choix);

    for(int i = 0; i < (*emp).nb_positions; i++)
    {
        if((*emp).positions[i].id == choix && (*emp).positions[i].disponible == 1)
        {
            int x = (*emp).positions[i].x;
            int y = (*emp).positions[i].y;

            if(x >= 0 && x < HAUTEUR && y >= 0 && y < LARGEUR)
            {
            tab[x][y] = 64;
            (*emp).positions[i].disponible = 0;//on rend indisponible la case
            printf("Singe placé en (%d, %d)\n", x, y);
            }
            
            else
            {
                printf("Erreur, position hors limite\n");
            }

            return; //pour finir la boucle
        }
    }

    printf("Choix invalide ou emplacement déjà utilisé\n");
}