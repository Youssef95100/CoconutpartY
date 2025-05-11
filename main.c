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

    int vague_actuelle = 1;
    int nb_crabes_dans_vague = 3;
    int crabes_deployes = 0;
    int compteur_deploiement = 0;
    int delai_deploiement = 10;
    int delais_crabes[MAX_CRABES];

    
    
    //pour gérer les vagues
    //int compteur = 0;
    //int intervalle_crabe = 5;
    
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
        

          // Déploiement progressif des crabes
          //if (crabes_deployes < nb_crabes_dans_vague && compteur_deploiement >= delai_deploiement)
          if (crabes_deployes < nb_crabes_dans_vague &&
            compteur_deploiement >= delais_crabes[crabes_deployes])
          {
              crabe[nb_crabes].position = 0;
              crabe[nb_crabes].actif = true;
              nb_crabes++;
              crabes_deployes++;
              compteur_deploiement = 0;
          }
          compteur_deploiement++;
  
          // Avancer les crabes
          for (int i = 0; i < nb_crabes; i++)
          {
              if (crabe[i].actif)
              {
                  deplacerCrabe(&crabe[i], &chemin_enregistre);
  
                  if (crabe[i].position >= chemin_enregistre.taille - 1)
                  {
                      crabe[i].actif = false;
                      couronne.pv--;
                      printf("💥 Un crabe a atteint la couronne ! PV restants : %d\n", couronne.pv);
                      sleep(1);
                  }
              }
          }
  
          // Vérifier fin de vague
          bool vague_terminee = true;
          for (int i = nb_crabes - crabes_deployes; i < nb_crabes; i++)
          {
              if (crabe[i].actif)
              {
                  vague_terminee = false;
                  break;
              }
          }
  
          // Si la vague est terminée
          if (vague_terminee && crabes_deployes == nb_crabes_dans_vague)
          {
            printf("\n✅ Vague %d terminée !\n", vague_actuelle);
            vague_actuelle++;
            crabes_deployes = 0;
            nb_crabes_dans_vague += 2; // Vague suivante avec +2 crabes

              // Générer les délais aléatoires pour la prochaine vague
            for (int i = 0; i < nb_crabes_dans_vague; i++) {
                delais_crabes[i] = rand() % 8 + 1; // Déploiement entre 1 et 8 ticks après le début de la vague
                }
                
            // Afficher le terrain pour bien voir où placer le singe
printf("\n--- Terrain après la vague %d ---\n", vague_actuelle - 1);
afficher(HAUTEUR, LARGEUR, affichage);

printf("\n--- Emplacements disponibles pour les singes ---\n");
for (int i = 0; i < emp.nb_positions; i++)
    if (emp.positions[i].disponible)
        printf("%c ", emp.positions[i].id);
printf("\n");

// Placer un singe
printf("🧠 Place un singe avant la prochaine vague (appuie sur 's') :\n");
while (1)
{
    lire_action(&action);
    if (action == 's')
    {
        menu_singe(&emp);
        placer_singe(&emp, HAUTEUR, LARGEUR, tab);
        break;
    }
}
                            
              // Attente et placement d’un singe avant de continuer
              /*printf("🧠 Place un singe avant la prochaine vague (appuie sur 's') :\n");
              while (1)
              {
                  lire_action(&action);
                  if (action == 's')
                  {
                      menu_singe(&emp);
                      placer_singe(&emp, HAUTEUR, LARGEUR, tab);
                      break;
                  }
              }
  
              printf("🌊 Appuie sur entrée pour lancer la vague suivante...\n");
              getchar(); getchar();
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
/*
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

#define MAX_DELAY_BETWEEN_CRABES 8

int main(int argc, char** argv) {
    srand(time(NULL));

    int LARGEUR = (rand() % (32 - 22 + 1)) + 22;
    int HAUTEUR = (rand() % (21 - 16 + 1)) + 16;

    bool joue = true;
    char action;

    Couronne couronne = {.pv = 5};
    Chemin chemin_enregistre;
    Crabe crabe[MAX_CRABES];
    int nb_crabes = 0;

    int vague_actuelle = 1;
    int nb_crabes_dans_vague = 3;
    int crabes_deployes = 0;
    int compteur_temps = 0;
    int delais_crabes[MAX_CRABES];

    for (int i = 0; i < MAX_CRABES; i++) {
        initialiserCrabe(&crabe[i]);
        delais_crabes[i] = -1;
    }

    int tab[HAUTEUR][LARGEUR];
    char affichage[HAUTEUR][LARGEUR];
    EmplacementsSinges emp;
    emp.nb_positions = 0;

    initialisation(HAUTEUR, LARGEUR, tab);
    chemin(HAUTEUR, LARGEUR, tab, &chemin_enregistre);
    generer_emplacement(HAUTEUR, LARGEUR, tab, &emp);

    // Initialisation des delais de la première vague
    for (int i = 0; i < nb_crabes_dans_vague; i++) {
        delais_crabes[i] = rand() % MAX_DELAY_BETWEEN_CRABES + (i == 0 ? 0 : 3); // éviter crabes collés
    }

    while (joue && couronne.pv > 0) {
        lire_action(&action);

        if (action == 'q') {
            printf("\nVous avez quitté le jeu.\n");
            break;
        } else if (action == 's') {
            menu_singe(&emp);
            placer_singe(&emp, HAUTEUR, LARGEUR, tab);
        }

        system("clear");

        // Déployer les crabes à intervalle aléatoire
        if (crabes_deployes < nb_crabes_dans_vague && compteur_temps >= delais_crabes[crabes_deployes]) {
            crabe[nb_crabes].position = 0;
            crabe[nb_crabes].actif = true;
            nb_crabes++;
            crabes_deployes++;
        }
        compteur_temps++;

        // Avancer crabes
        for (int i = 0; i < nb_crabes; i++) {
            if (crabe[i].actif) {
                deplacerCrabe(&crabe[i], &chemin_enregistre);
                if (crabe[i].position >= chemin_enregistre.taille - 1) {
                    crabe[i].actif = false;
                    couronne.pv--;
                    printf("\n💥 Un crabe a atteint la couronne ! PV restants : %d\n", couronne.pv);
                    sleep(1);
                }
            }
        }

        // Vérifie si la vague est terminée
        bool vague_terminee = true;
        for (int i = nb_crabes - crabes_deployes; i < nb_crabes; i++) {
            if (crabe[i].actif) {
                vague_terminee = false;
                break;
            }
        }

        if (vague_terminee && crabes_deployes == nb_crabes_dans_vague) {
            printf("\n✅ Vague %d terminée !\n", vague_actuelle);
            vague_actuelle++;
            crabes_deployes = 0;
            nb_crabes_dans_vague += 2;
            compteur_temps = 0;

            // Génère des délais écartés aléatoirement pour éviter crabes collés
            for (int i = 0; i < nb_crabes_dans_vague; i++) {
                delais_crabes[i] = i * 2 + (rand() % 3); // ex: 0, 2-4, 4-6...
            }

            // Afficher terrain pour choix placement
            for (int i = 0; i < HAUTEUR; i++) {
                for (int j = 0; j < LARGEUR; j++) {
                    affichage[i][j] = tab[i][j];
                }
            }
            for (int i = 0; i < emp.nb_positions; i++) {
                if (emp.positions[i].disponible) {
                    affichage[emp.positions[i].x][emp.positions[i].y] = emp.positions[i].id;
                }
            }
            afficher(HAUTEUR, LARGEUR, affichage);

            printf("\n--- Emplacements disponibles ---\n");
            for (int i = 0; i < emp.nb_positions; i++) {
                if (emp.positions[i].disponible) {
                    printf("%c ", emp.positions[i].id);
                }
            }

            printf("\n🧠 Place un singe (tape 's') : ");
            while (1) {
                lire_action(&action);
                if (action == 's') {
                    menu_singe(&emp);
                    placer_singe(&emp, HAUTEUR, LARGEUR, tab);
                    break;
                }
            }
            printf("\n🌊 Appuie sur entrée pour lancer la prochaine vague...\n");
            getchar(); getchar();
        }

        // Affichage à jour
        for (int i = 0; i < HAUTEUR; i++) {
            for (int j = 0; j < LARGEUR; j++) {
                affichage[i][j] = tab[i][j];
            }
        }


        for (int i = 0; i < emp.nb_positions; i++) {
            if (emp.positions[i].disponible) {
                affichage[emp.positions[i].x][emp.positions[i].y] = emp.positions[i].id;
            }
        }
        for (int i = 0; i < nb_crabes; i++) {
            if (crabe[i].actif && crabe[i].position >= 0 && crabe[i].position < chemin_enregistre.taille) {
                int x = chemin_enregistre.cases[crabe[i].position].x;
                int y = chemin_enregistre.cases[crabe[i].position].y;
                affichage[x][y] = 'C';
            }
        }

        for (int i = 0; i < emp.nb_positions; i++) {
            int x = emp.positions[i].x;
            int y = emp.positions[i].y;
        
            if (emp.positions[i].disponible)
                affichage[x][y] = emp.positions[i].id; // emplacement libre
            else
                affichage[x][y] = '@'; // singe placé
        }
        

        afficher(HAUTEUR, LARGEUR, affichage);

        printf("\n--- Emplacements disponibles ---\n");
        for (int i = 0; i < emp.nb_positions; i++) {
            if (emp.positions[i].disponible) {
                printf("%c ", emp.positions[i].id);
            }
        }

        printf("\nAppuie sur 's' pour placer un singe ou 'q' pour quitter.\n");
        usleep(100000);
    }

    if (couronne.pv <= 0) {
        printf("\n💀 La couronne a été détruite. Game Over.\n");
    }

    return 0;
}
*/
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

#define MAX_DELAY_BETWEEN_CRABES 8

int main(int argc, char** argv) {
    srand(time(NULL));

    int LARGEUR = (rand() % (32 - 22 + 1)) + 22;
    int HAUTEUR = (rand() % (21 - 16 + 1)) + 16;

    bool joue = true;
    char action;

    Couronne couronne = {.pv = 50};
    Chemin chemin_enregistre;
    Crabe crabe[MAX_CRABES];
    int nb_crabes = 0;

    int vague_actuelle = 1;
    int nb_crabes_dans_vague = 3;
    int crabes_deployes = 0;
    int compteur_temps = 0;
    int delais_crabes[MAX_CRABES];

    for (int i = 0; i < MAX_CRABES; i++) {
        initialiserCrabe(&crabe[i]);
        delais_crabes[i] = -1;
    }

    int tab[HAUTEUR][LARGEUR];
    char affichage[HAUTEUR][LARGEUR];
    EmplacementsSinges emp;
    emp.nb_positions = 0;

    initialisation(HAUTEUR, LARGEUR, tab);
    chemin(HAUTEUR, LARGEUR, tab, &chemin_enregistre);
    generer_emplacement(HAUTEUR, LARGEUR, tab, &emp);

    for (int i = 0; i < nb_crabes_dans_vague; i++) {
        delais_crabes[i] = rand() % MAX_DELAY_BETWEEN_CRABES + (i == 0 ? 0 : 3);
    }

    while (joue && couronne.pv > 0) {
        lire_action(&action);

        if (action == 'q') break;
        if (action == 's') {
            menu_singe(&emp);
            placer_singe(&emp, HAUTEUR, LARGEUR, tab);
        }

        system("clear");

        if (crabes_deployes < nb_crabes_dans_vague && compteur_temps >= delais_crabes[crabes_deployes]) {
            crabe[nb_crabes].position = 0;
            crabe[nb_crabes].actif = true;
            nb_crabes++;
            crabes_deployes++;
        }
        compteur_temps++;

        for (int i = 0; i < nb_crabes; i++) {
            if (crabe[i].actif) {
                deplacerCrabe(&crabe[i], &chemin_enregistre);
                if (crabe[i].position >= chemin_enregistre.taille - 1) {
                    crabe[i].actif = false;
                    couronne.pv--;
                    printf("\n💥 Un crabe a atteint la couronne ! PV restants : %d\n", couronne.pv);
                    sleep(1);
                }
            }
        }

        bool vague_terminee = true;
        for (int i = nb_crabes - crabes_deployes; i < nb_crabes; i++) {
            if (crabe[i].actif) {
                vague_terminee = false;
                break;
            }
        }

        if (vague_terminee && crabes_deployes == nb_crabes_dans_vague) {
            printf("\n✅ Vague %d terminée !\n", vague_actuelle);
            vague_actuelle++;
            crabes_deployes = 0;
            nb_crabes_dans_vague += 2;
            compteur_temps = 0;

            for (int i = 0; i < nb_crabes_dans_vague; i++) {
                delais_crabes[i] = i * 2 + (rand() % 3);
            }

            // Mise à jour de l'affichage proprement à chaque tour
for (int i = 0; i < HAUTEUR; i++) {
    for (int j = 0; j < LARGEUR; j++) {
        affichage[i][j] = tab[i][j]; // base terrain (bordures, chemin, etc.)
    }
}

// Réafficher les crabes
for (int i = 0; i < nb_crabes; i++) {
    if (crabe[i].actif && crabe[i].position >= 0 && crabe[i].position < chemin_enregistre.taille) {
        int x = chemin_enregistre.cases[crabe[i].position].x;
        int y = chemin_enregistre.cases[crabe[i].position].y;
        affichage[x][y] = 'C';
    }
}

// Affichage des emplacements (lettres ou @ si singe)
for (int i = 0; i < emp.nb_positions; i++) {
    int x = emp.positions[i].x;
    int y = emp.positions[i].y;
    
    if (emp.positions[i].disponible)
        affichage[x][y] = emp.positions[i].id;
    else
        affichage[x][y] = '@';
}

            for (int i = 0; i < emp.nb_positions; i++) {
                if (emp.positions[i].disponible)
                    affichage[emp.positions[i].x][emp.positions[i].y] = emp.positions[i].id;
                else
                    affichage[emp.positions[i].x][emp.positions[i].y] = '@';
            }

            afficher(HAUTEUR, LARGEUR, affichage);
            

            printf("\n--- Emplacements disponibles ---\n");
            for (int i = 0; i < emp.nb_positions; i++) {
                if (emp.positions[i].disponible)
                    printf("%c ", emp.positions[i].id);
            }

            printf("\n🧠 Place un singe (tape 's') : ");
            while (1) {
                lire_action(&action);
                if (action == 's') {
                    menu_singe(&emp);
                    placer_singe(&emp, HAUTEUR, LARGEUR, tab);
                    break;
                }
            }
            
            printf("\n🌊 Appuie sur entrée pour lancer la prochaine vague...\n");
            getchar(); getchar();
        }

        for (int i = 0; i < HAUTEUR; i++)
            for (int j = 0; j < LARGEUR; j++)
                affichage[i][j] = tab[i][j];

        for (int i = 0; i < emp.nb_positions; i++) {
            int x = emp.positions[i].x;
            int y = emp.positions[i].y;
            if (emp.positions[i].disponible)
                affichage[x][y] = emp.positions[i].id;
            else
                affichage[x][y] = '@';
        }

        for (int i = 0; i < nb_crabes; i++) {
            if (crabe[i].actif && crabe[i].position >= 0 && crabe[i].position < chemin_enregistre.taille) {
                int x = chemin_enregistre.cases[crabe[i].position].x;
                int y = chemin_enregistre.cases[crabe[i].position].y;
                affichage[x][y] = 'C';
            }
        }

        afficher(HAUTEUR, LARGEUR, affichage);

        printf("\n--- Emplacements disponibles ---\n");
        for (int i = 0; i < emp.nb_positions; i++) {
            if (emp.positions[i].disponible)
                printf("%c ", emp.positions[i].id);
        }

        printf("\nAppuie sur 's' pour placer un singe ou 'q' pour quitter.\n");
        usleep(100000);
    }

    if (couronne.pv <= 0) {
        printf("\n💀 La couronne a été détruite. Game Over.\n");
    }

    return 0;
}
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

//#define MAX_CRABES 100 // Ajuste cette valeur si nécessaire

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
    Crabe crabe[MAX_CRABES]; // tableau de crabes
    int nb_crabes = 0;

    // Pour gérer les vagues
    int compteur = 0;
    int intervalle_crabe = 5; // Intervalle initial entre les crabes
    int vagues_passées = 0;   // Nombre de vagues passées

    for (int i = 0; i < MAX_CRABES; i++)
    {
        initialiserCrabe(&crabe[i]);
    }

    // Terrain
    int tab[HAUTEUR][LARGEUR];
    char affichage[HAUTEUR][LARGEUR];
    EmplacementsSinges emp;
    emp.nb_positions = 0;

    initialisation(HAUTEUR, LARGEUR, tab);
    chemin(HAUTEUR, LARGEUR, tab, &chemin_enregistre);
    generer_emplacement(HAUTEUR, LARGEUR, tab, &emp);

    while (joue)
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
        for (int i = 0; i < nb_crabes; i++)
        {
            if (crabe[i].actif)
            {
                deplacerCrabe(&crabe[i], &chemin_enregistre);
            }
        }

        // Ajouter un nouveau crabe à intervalle régulier
        compteur++;
        if (compteur >= intervalle_crabe && nb_crabes < MAX_CRABES)
        {
            // Ajouter un crabe à la vague
            crabe[nb_crabes].position = 0;
            crabe[nb_crabes].actif = true;

            nb_crabes++;
            compteur = 0;

            // Si on a ajouté assez de crabes pour cette vague, passer à la suivante
            if (nb_crabes >= (vagues_passées + 1) * 5) // Ajouter 5 crabes à chaque vague
            {
                vagues_passées++;
                intervalle_crabe = intervalle_crabe > 2 ? intervalle_crabe - 1 : intervalle_crabe; // Rendre les vagues plus rapides
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

        // Afficher les crabes sur le terrain
        for (int i = 0; i < nb_crabes; i++)
        {
            if (crabe[i].actif && crabe[i].position >= 0 && crabe[i].position < chemin_enregistre.taille)
            {
                int x = chemin_enregistre.cases[crabe[i].position].x;
                int y = chemin_enregistre.cases[crabe[i].position].y;
                affichage[x][y] = 'C';  // Afficher un crabe
            }
        }

        // Afficher le terrain
        afficher(HAUTEUR, LARGEUR, affichage);

        // Afficher les emplacements de singes
        printf("\n--- Emplacements disponibles pour les singes ---\n");
        for (int i = 0; i < emp.nb_positions; i++)
        {
            if (emp.positions[i].disponible)
            {
                printf("%c ", emp.positions[i].id);
            }
        }

        printf("\nAppuyez sur 's' puis 'entrer' pour placer un singe, 'q' puis 'entrer' pour quitter : \n");

        sleep(1); // Pause de 0.1 seconde pour simuler un gameplay fluide
    }

    return 0;
}*/
