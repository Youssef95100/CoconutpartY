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
    Crabe crabe;
    initialiserCrabe(&crabe);
    
    //&int choix = menu();

   //terrain
   int tab[HAUTEUR][LARGEUR];
   EmplacementsSinges emp;
   emp.nb_positions = 0;
    initialisation(HAUTEUR, LARGEUR, tab);
    chemin(HAUTEUR, LARGEUR, tab, &chemin_enregistre);
    generer_emplacement(HAUTEUR, LARGEUR, tab, &emp);

    while ( joue )
    {

        system("clear"); // Efface la console

        if(crabe.actif = 1)
        {
        deplacerCrabe(&crabe, &chemin_enregistre, HAUTEUR, LARGEUR, tab);
        }

        afficher(HAUTEUR, LARGEUR, tab);


        printf("\n--- Emplacements disponibles pour les singes ---\n");
        for (int i = 0; i < emp.nb_positions; i++)
        {
            if (emp.positions[i].disponible)
            {
                printf("%c ", emp.positions[i].id);
            }
        }

        printf("\n Appuyez sur 's' pour placer un singe, 'q' pour quitter : ");
        scanf(" %c", &action);
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
