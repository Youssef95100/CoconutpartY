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



int main(int argc, char** argv)
{
    srand(time(NULL)); // Initialiser le générateur de nombres aléatoires

    // Générer des dimensions aléatoires
    int LARGEUR = (rand() % (32 - 22 + 1)) + 22; // Largeur entre 22 et 32
    int HAUTEUR = (rand() % (21 - 16 + 1)) + 16; // Hauteur entre 16 et 21

    bool joue = true;
    char action;
    Couronne couronne = {.pv = 5};
    Chemin chemin_enregistre;
    Crabe crabe[MAX_CRABES];//tableau de crabes
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
        
        

        lire_action(&action);

        if (action == 'q') {
            printf("Vous avez quitté le jeu.\n");
            joue = false;
        } else if (action == 's') {
            menu_singe(&emp);
            placer_singe(&emp, HAUTEUR, LARGEUR, tab);
        }
         
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

        printf("\n Appuyez sur 's' puis 'entrer' pour placer un singe, 'q' puis 'entrer' pour quitter : \n");
        
        usleep(100000); //pause de 1 sec
    }

   return 0;
}