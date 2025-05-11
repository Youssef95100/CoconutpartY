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
        tab[0][i] = 95;
        tab[HAUTEUR - 1][i] = 95;
    }

    //setup des bordures a gauche et a droite
    for(int i = 0; i < HAUTEUR; i++)
    {
        tab[i][0] = 124;
        tab[i][LARGEUR - 1] = 124;
    }
}

void chemin(int HAUTEUR, int LARGEUR, int tab[HAUTEUR][LARGEUR], Chemin* chemin)
{
    srand(time(NULL)); // Initialiser le générateur de nombres aléatoires

    (*chemin).taille = 0;

    // Point de départ
    int pdp_valeur = rand() % (HAUTEUR - 2) + 1;
    tab[pdp_valeur][LARGEUR - 2] = 35;

    int hauteur_actuelle = pdp_valeur;
    int largeur_actuelle = LARGEUR - 2;

    // Enregistrer la case de départ
    (*chemin).cases[(*chemin).taille].x = hauteur_actuelle;
    (*chemin).cases[(*chemin).taille].y = largeur_actuelle;
    (*chemin).taille++;

    // Point d'arrivée théorique
    int pda_valeur = rand() % (HAUTEUR - 2) + 1;

    while (largeur_actuelle > 1)
    {
        int direction = rand() % 3; // 0 = haut, 1 = bas, 2 = gauche

        int prochaine_hauteur = hauteur_actuelle;
        int prochaine_largeur = largeur_actuelle;

        if (direction == 0 && hauteur_actuelle > 1 && hauteur_actuelle > pda_valeur) {
            prochaine_hauteur--;//Monter
        }
        else if (direction == 1 && hauteur_actuelle < HAUTEUR - 2 && hauteur_actuelle < pda_valeur) {
            prochaine_hauteur++;//Descendre
        }
        else if (direction == 2) {
            prochaine_largeur--;//Avancer
        }

        // Ne pas ajouter si même position que précédente
        if (prochaine_hauteur != hauteur_actuelle || prochaine_largeur != largeur_actuelle) {
            if (tab[prochaine_hauteur][prochaine_largeur] != 'X' &&
                tab[prochaine_hauteur][prochaine_largeur] != '#') {

                tab[prochaine_hauteur][prochaine_largeur] = '.';
                (*chemin).cases[(*chemin).taille].x = prochaine_hauteur;
                (*chemin).cases[(*chemin).taille].y = prochaine_largeur;
                (*chemin).taille++;

                hauteur_actuelle = prochaine_hauteur;
                largeur_actuelle = prochaine_largeur;
            }
        }
    }

    // Point d'arrivée réel
    tab[hauteur_actuelle][1] = 88;


    // Enregistrer l'arrivée uniquement si elle diffère de la dernière
    if ((*chemin).cases[(*chemin).taille - 1].x != hauteur_actuelle ||
        (*chemin).cases[(*chemin).taille - 1].y != 1) {
        (*chemin).cases[(*chemin).taille].x = hauteur_actuelle;
        (*chemin).cases[(*chemin).taille].y = 1;
        (*chemin).taille++;
    }
}




void afficher(int HAUTEUR, int LARGEUR, char affichage[HAUTEUR][LARGEUR])
{    

    // Affichage du tableau
    for (int i = 0; i < HAUTEUR; i++) 
    {
        for (int j = 0; j < LARGEUR; j++) 
        {
            printf("%c ", affichage[i][j]);
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

            bool placer = (rand() % 4 == 0); //pour que l'apparition des singes soit aléatoire
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

void lire_action(char* action) {
    fd_set fds;
    struct timeval timeout;

    // Réinitialiser les descripteurs de fichiers
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);

    timeout.tv_sec = TIMEOUT; // Timeout de 1 seconde
    timeout.tv_usec = 0;

    // Vérifie si une entrée est disponible
    int ret = select(STDIN_FILENO + 1, &fds, NULL, NULL, &timeout);

    if (ret > 0) { // Il y a une entrée disponible
        *action = getchar(); // Lire l'entrée de l'utilisateur
    } else {
        *action = '\0'; // Pas d'entrée, continue sans rien
    }
}



