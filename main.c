/*#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> //pour le bool
#include <unistd.h> // Pour sleep()
#include <time.h>
#include "structure.h"
#include "menu.h"
#include "couronne.h"
#include "sauvegarde.h"
#include "terrain.h"
#include "crabe.h"
//#include "terrain.c" //il faut l'inclure si on ne le compile pas
//#include "crabe.c" //il faut l'inclure si on ne le compile pas

int main(int argc, char** argv)
{
    srand(time(NULL)); // Initialiser le générateur de nombres aléatoires

    // Générer des dimensions aléatoires
    int LARGEUR = (rand() % (32 - 22 + 1)) + 22; // Largeur entre 22 et 32
    int HAUTEUR = (rand() % (21 - 16 + 1)) + 16; // Hauteur entre 16 et 21

    bool joue = true;
    char action;
    Couronne couronne;
    Chemin chemin_enregistre;
    Crabe crabe[MAX_CRABES];//liste de crabes
    int nb_crabes = 0;
    
    //pour gérer les vagues
    int compteur = 0;
    int intervalle_crabe = 5;
    
    for(int i = 0; i<MAX_CRABES; i++)
    {
    initialiserCrabe(&crabe[i]);
    }
    
    //int choix = menu();

   //terrain
   int tab[HAUTEUR][LARGEUR];
   char affichage[HAUTEUR][LARGEUR];
   EmplacementsSinges emp;
   emp.nb_positions = 0;
    initialisation(HAUTEUR, LARGEUR, tab);
    chemin(HAUTEUR, LARGEUR, tab, &chemin_enregistre);
    generer_emplacement(HAUTEUR, LARGEUR, tab, &emp);
    

    while ( joue )
    {

        system("clear"); // Efface la console



         // Faire avancer tous les crabes actifs
         for(int i = 0; i < nb_crabes; i++)
         {
             if(crabe[i].actif)
             {
                 deplacerCrabe(&crabe[i], &chemin_enregistre);
             }
         }
 
         // Ajouter un nouveau crabe à intervalle régulier
         compteur++;
         if(compteur >= intervalle_crabe && nb_crabes < MAX_CRABES)
         {
             crabe[nb_crabes].position = 0;
             crabe[nb_crabes].actif = true;
 
             nb_crabes++;
             compteur = 0;
 
             // Rendre la vague plus rapide
             if(intervalle_crabe > 1)
             {
                 intervalle_crabe--;
             }
         }

        // Copier le terrain original dans le tableau d'affichage
        for (int i = 0; i < HAUTEUR; i++) 
        {
            for (int j = 0; j < LARGEUR; j++)
             {
                affichage[i][j] = tab[i][j];
             }
        }

        for (int i = 0; i < nb_crabes; i++)
         {
            if (crabe[i].actif && crabe[i].position >= 0 && crabe[i].position < chemin_enregistre.taille)
             {
                int x = chemin_enregistre.cases[crabe[i].position].x;
                int y = chemin_enregistre.cases[crabe[i].position].y;
                affichage[x][y] = 'C';  // Afficher un crabe
            }
        }

        //On affiche le terrain 
        afficher(HAUTEUR, LARGEUR, affichage);

        

        //On affiche les emplacements de singes
        printf("\n--- Emplacements disponibles pour les singes ---\n");
        for (int i = 0; i < emp.nb_positions; i++)
        {
            if (emp.positions[i].disponible)
            {
                printf("%c ", emp.positions[i].id);
            }
        }

        printf("\n Appuyez sur 's' pour placer un singe, 'q' pour quitter : \n");
        //scanf(" %c", &action);
        //menu_singe(&emp);
        
        

        if(action == 's')
        {
            placer_singe(&emp, HAUTEUR, LARGEUR, tab);
        }else if (action == 'q')
        {
            joue = false;
        }

        sleep(1); //pause de 1 sec
    }

   return 0;
}*/
/*#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include "structure.h"
#include "menu.h"
#include "couronne.h"
#include "sauvegarde.h"
#include "terrain.h"
#include "crabe.h"

//#define MAX_CRABES 5  // Temporairement pour affichage

void afficher_heure_formatee() {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    printf("%02d:%02d:%02d", t->tm_hour, t->tm_min, t->tm_sec);
}

int main(int argc, char** argv)
{
    srand(time(NULL));

    int LARGEUR = 25;
    int HAUTEUR = 18;

    bool joue = true;
    char action;
    Chemin chemin_enregistre;
    Crabe crabe[MAX_CRABES];
    int nb_crabes = 0;
    int compteur = 0;
    int intervalle_crabe = 3;

    for (int i = 0; i < MAX_CRABES; i++) {
        initialiserCrabe(&crabe[i]);
    }

    int tab[HAUTEUR][LARGEUR];
    EmplacementsSinges emp;
    emp.nb_positions = 0;
    initialisation(HAUTEUR, LARGEUR, tab);
    chemin(HAUTEUR, LARGEUR, tab, &chemin_enregistre);
    generer_emplacement(HAUTEUR, LARGEUR, tab, &emp);

    while (joue) {
        // 1. Mise à jour positions crabes
        for (int i = 0; i < nb_crabes; i++) {
            if (crabe[i].actif) {
                crabe[i].position++;
                if (crabe[i].position >= chemin_enregistre.taille) {
                    crabe[i].actif = false;
                }
            }
        }

        // 2. Nouveau crabe
        compteur++;
        if (compteur >= intervalle_crabe && nb_crabes < MAX_CRABES) {
            bool libre = true;
            for (int i = 0; i < nb_crabes; i++) {
                if (crabe[i].actif && crabe[i].position == 0) {
                    libre = false;
                    break;
                }
            }
            if (libre) {
                crabe[nb_crabes].position = 0;
                crabe[nb_crabes].actif = true;
                nb_crabes++;
                compteur = 0;
            }
        }

        // 3. Affichage tableau
        printf("========================================================\n");
        printf("| Heure     | Crabe | Position | Coord (x,y) | Actif  |\n");
        printf("--------------------------------------------------------\n");

        for (int i = 0; i < MAX_CRABES; i++) {
            printf("| ");
            afficher_heure_formatee();
            printf(" |   %2d   |    %3d    |", i, crabe[i].position);

            if (crabe[i].actif && crabe[i].position < chemin_enregistre.taille) {
                int x = chemin_enregistre.cases[crabe[i].position].x;
                int y = chemin_enregistre.cases[crabe[i].position].y;
                printf("  (%2d,%2d)   |   Oui  |\n", x, y);
            } else {
                printf("    --      |   Non  |\n");
            }
        }

        printf("========================================================\n\n");

        sleep(1);
    }

    return 0;
}
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "structure.h"
#include "terrain.h"
#include "couronne.h"

int main() {
    srand(time(NULL));

    int LARGEUR = (rand() % (32 - 22 + 1)) + 22;
    int HAUTEUR = (rand() % (21 - 16 + 1)) + 16;

    int tab[HAUTEUR][LARGEUR];
    Chemin chemin_enregistre;

    // Initialisation du terrain et génération du chemin
    initialisation(HAUTEUR, LARGEUR, tab);
    chemin(HAUTEUR, LARGEUR, tab, &chemin_enregistre);

    // Affichage du chemin enregistré
    printf("======= Chemin Enregistré (%d cases) =======\n", chemin_enregistre.taille);
    for (int i = 0; i < chemin_enregistre.taille; i++) {
        printf("Position %3d : (%2d, %2d)\n",
               i,
               chemin_enregistre.cases[i].x,
               chemin_enregistre.cases[i].y);

        // Optionnel : détecter doublons consécutifs
        if (i > 0 &&
            chemin_enregistre.cases[i].x == chemin_enregistre.cases[i - 1].x &&
            chemin_enregistre.cases[i].y == chemin_enregistre.cases[i - 1].y) {
            printf("    Doublon avec la position précédente !\n");
        }
    }
    printf("===========================================\n");

    return 0;
}
