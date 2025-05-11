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
}*/
#include <stdio.h>
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

int main(int argc, char** argv)
{
    srand(time(NULL));

    int LARGEUR = (rand() % (32 - 22 + 1)) + 22;
    int HAUTEUR = (rand() % (21 - 16 + 1)) + 16;

    bool joue = true;
    char action;
    Couronne couronne = {.pv = 5};
    Chemin chemin_enregistre;
    Crabe crabe[MAX_CRABES];
    int nb_crabes = 0;

    int compteur = 0;
    int intervalle_crabe = 5;

    int num_vague = 1;
    int crabes_par_vague = 5;
    bool vague_active = false;
    bool attente_vague = true;

    for (int i = 0; i < MAX_CRABES; i++) {
        initialiserCrabe(&crabe[i]);
    }

    int tab[HAUTEUR][LARGEUR];
    EmplacementsSinges emp;
    emp.nb_positions = 0;

    initialisation(HAUTEUR, LARGEUR, tab);
    chemin(HAUTEUR, LARGEUR, tab, &chemin_enregistre);
    generer_emplacement(HAUTEUR, LARGEUR, tab, &emp);

    printf("Avant de commencer, vous devez placer un singe !\n");
    afficher_jeu(HAUTEUR, LARGEUR, tab, &chemin_enregistre, crabe, nb_crabes, &emp, num_vague);
    menu_singe(&emp);
    placer_singe(&emp, HAUTEUR, LARGEUR, tab);

    printf("Préparez-vous ! Vague %d va commencer...\n", num_vague);
    sleep(2);
    vague_active = true;
    attente_vague = false;

    while (joue)
    {
        lire_action(&action);

        if (action == 'q') {
            printf("Vous avez quitté le jeu.\n");
            break;
        }

        system("clear");

        for (int i = 0; i < nb_crabes; i++) {
            if (crabe[i].actif) {
                deplacerCrabe(&crabe[i], &chemin_enregistre);

                // Vérifie si le crabe est à la fin du chemin
                if (crabe[i].position >= chemin_enregistre.taille - 1) {
                    crabe[i].actif = false;
                    couronne.pv--;
                    printf(" Un crabe a atteint la couronne ! PV restants : %d\n", couronne.pv);

                    if (couronne.pv <= 0) {
                        printf("\n GAME OVER \nVous avez tenu jusqu’à la vague %d.\n", num_vague);
                        joue = false;
                        break;
                    }
                }
            }
        }

        if (!joue) break;

        if (vague_active)
        {
            compteur++;
            if (compteur >= intervalle_crabe && nb_crabes < crabes_par_vague)
            {
                crabe[nb_crabes].position = 0;
                crabe[nb_crabes].actif = true;
                nb_crabes++;
                compteur = 0;
                if (intervalle_crabe > 1) intervalle_crabe--;
            }

            bool tous_inactifs = true;
            for (int i = 0; i < nb_crabes; i++) {
                if (crabe[i].actif) {
                    tous_inactifs = false;
                    break;
                }
            }

            if (nb_crabes == crabes_par_vague && tous_inactifs)
            {
                vague_active = false;
                attente_vague = true;
                num_vague++;
                crabes_par_vague += 2;
                nb_crabes = 0;
                intervalle_crabe = 5;

                printf("\n--- VAGUE %d terminée ! Préparez-vous pour la vague %d ---\n", num_vague - 1, num_vague);
                sleep(2);
            }
        }
        else if (attente_vague)
        {
            printf("\nVous pouvez placer un nouveau singe avant la vague %d.\n", num_vague);
            afficher_jeu(HAUTEUR, LARGEUR, tab, &chemin_enregistre, crabe, nb_crabes, &emp, num_vague);
            menu_singe(&emp);
            placer_singe(&emp, HAUTEUR, LARGEUR, tab);

            printf("\nLa vague %d commence !\n", num_vague);
            sleep(2);
            vague_active = true;
            attente_vague = false;
        }

        // Affichage du jeu
        afficher_jeu(HAUTEUR, LARGEUR, tab, &chemin_enregistre, crabe, nb_crabes, &emp, num_vague);
        printf(" PV Couronne : %d\n", couronne.pv);
        printf("\nAppuyez sur 'Entrée' pour accélérer, 'q' puis 'Entrée' pour quitter : \n");

        usleep(100000);
    }

    return 0;
}
