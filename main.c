#include <stdio.h>
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
        //On fait avancer tous les crabes actifs


        /*for(int i=0; i < nb_crabes; i++)
        {
            if(crabe[i].actif)
            {
                deplacerCrabe(&crabe[i], &chemin_enregistre, HAUTEUR, LARGEUR, tab);
            }
        }

        //ajout d'un nouveau crabe a intervalle régulier
        compteur++;
        if(compteur >= intervalle_crabe && nb_crabes < MAX_CRABES)
        {
            crabe[nb_crabes].position = 0;
            crabe[nb_crabes].actif = true;

            // Placer immédiatement le crabe sur la grille
            int x_depart = chemin_enregistre.cases[0].x;
            int y_depart = chemin_enregistre.cases[0].y;
            tab[x_depart][y_depart] = 'C';


            nb_crabes++;
            compteur = 0;

            //on réduit l'intervalle pour que ce soit plus dur
            if(intervalle_crabe > 1)
            {
                intervalle_crabe--;
            }
        }*/

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
            if (crabe[i].actif && crabe[i].position < chemin_enregistre.taille)
             {
                int x = chemin_enregistre.cases[crabe[i].position].x;
                int y = chemin_enregistre.cases[crabe[i].position].y;
                affichage[x][y] = 'C';  // Afficher un crabe
            }
        }

        //On affiche le terrain 
        afficher(HAUTEUR, LARGEUR, affichage);//tab);

        

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
}
