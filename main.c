#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include "structure.h"
#include "sauvegarde.h"
#include "terrain.h"
#include "crabe.h"

int main(int argc, char** argv)
{
    system("clear");
    srand(time(NULL));

    int LARGEUR = (rand() % (32 - 22 + 1)) + 22;
    int HAUTEUR = (rand() % (21 - 16 + 1)) + 16;

    Couronne couronne;
    Chemin chemin_enregistre;
    Crabe crabe[MAX_CRABES];
    EmplacementsSinges emp;
    emp.nb_positions = 0;
    ListeSinges liste_singes;
    liste_singes.nb_singes = 0;
    int tab[HAUTEUR][LARGEUR];

    int nb_crabes = 0;
    int compteur = 0;
    int intervalle_crabe = 5;
    int num_vague = 1;
    int crabes_par_vague = 5;
    bool vague_active = false;
    bool attente_vague = true;
    bool joue = true;
    char action;

    // --- MENU MANUEL ---
    int choix = 0;
    printf("\n=== CoconutpartY ===\n");
    printf("1. Nouvelle partie\n");
    printf("2. Reprendre partie\n");
    printf("3. Quitter\n");
    printf("Votre choix : ");

    while (scanf("%d", &choix) != 1 || choix < 1 || choix > 3) {
        printf("Choix invalide. Réessayez : ");
        while (getchar() != '\n'); // vider le buffer
    }

    if (choix == 3) {
        printf("À bientôt !\n");
        return 0;
    }

    if (choix == 2) {
         {
            printf("Erreur lors du chargement de la partie.\n");
        }
            choix = 1;
    }
    

    if (choix == 1) {
        printf("Entrez les PV de la couronne : ");
        while (scanf("%d", &couronne.pv) != 1 || couronne.pv <= 0) {
            printf("Valeur invalide. Réessayez : ");
            while (getchar() != '\n');
        }
        system("clear)");

        initialisation(HAUTEUR, LARGEUR, tab);
        chemin(HAUTEUR, LARGEUR, tab, &chemin_enregistre);
        generer_emplacement(HAUTEUR, LARGEUR, tab, &emp);

        for (int i = 0; i < MAX_CRABES; i++)
            initialiserCrabe(&crabe[i]);
    }

    // --- Placement initial obligatoire d’un singe si aucun singe chargé ---
    if (liste_singes.nb_singes == 0) {
        printf("Avant de commencer, vous devez placer un singe !\n");
        afficher_jeu(HAUTEUR, LARGEUR, tab, &chemin_enregistre, crabe, nb_crabes, &emp, num_vague);
        menu_singe(&emp);
        placer_singe(&emp, HAUTEUR, LARGEUR, tab);
        mettre_a_jour_liste_singes(&liste_singes, &emp);
    }

    printf("Préparez-vous ! Vague %d va commencer...\n", num_vague);
    sleep(2);
    vague_active = true;
    attente_vague = false;

    // --- BOUCLE PRINCIPALE ---
    while (joue)
    {
        lire_action(&action);
        if (action == 'q') {
            printf("Vous avez quitté le jeu. Sauvegarde en cours...\n");
            sauvegarder_partie(&couronne, &chemin_enregistre, crabe, nb_crabes, &liste_singes, &emp, num_vague);

            break;
        }

        system("clear");

        // Déplacement des crabes
        for (int i = 0; i < nb_crabes; i++) {
            if (crabe[i].actif) {
                deplacerCrabe(&crabe[i], &chemin_enregistre);
                if (crabe[i].position >= chemin_enregistre.taille - 1) {
                    crabe[i].actif = false;
                    couronne.pv--;
                    printf(" Un crabe a atteint la couronne ! PV restants : %d\n", couronne.pv);

                    if (couronne.pv <= 0) {
                        printf("\n GAME OVER ! Vague atteinte : %d.\n", num_vague);
                        joue = false;
                        break;
                    }
                }
            }
        }

        // Attaque des singes
        for (int i = 0; i < liste_singes.nb_singes; i++) {
            Singe* s = &liste_singes.singe[i];
            for (int j = 0; j < nb_crabes; j++) {
                if (!crabe[j].actif) continue;
                int pos = crabe[j].position;
                if (pos >= 0 && pos < chemin_enregistre.taille) {
                    int cx = chemin_enregistre.cases[pos].x;
                    int cy = chemin_enregistre.cases[pos].y;
                    if (abs(s->x - cx) <= 1 && abs(s->y - cy) <= 1) {
                        crabe[j].pv -= s->degat;
                        if (crabe[j].pv <= 0) {
                            crabe[j].actif = false;
                            printf("Un crabe a été éliminé !\n");
                        }
                        break;
                    }
                }
            }
        }

        // Vague de crabes
        if (vague_active) {
            compteur++;
            if (compteur >= intervalle_crabe && nb_crabes < crabes_par_vague) {
                crabe[nb_crabes].position = 0;
                crabe[nb_crabes].actif = true;
                crabe[nb_crabes].pv = 3;
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

            if (nb_crabes == crabes_par_vague && tous_inactifs) {
                vague_active = false;
                attente_vague = true;
                num_vague++;
                crabes_par_vague += 2;
                nb_crabes = 0;
                intervalle_crabe = 5;

                printf("\n--- Vague %d terminée. Préparez-vous pour la suivante ! ---\n", num_vague - 1);
                sleep(2);
            }
        }
        else if (attente_vague) {
            printf("\nPlacez un nouveau singe avant la vague %d.\n", num_vague);
            afficher_jeu(HAUTEUR, LARGEUR, tab, &chemin_enregistre, crabe, nb_crabes, &emp, num_vague);
            menu_singe(&emp);
            placer_singe(&emp, HAUTEUR, LARGEUR, tab);
            mettre_a_jour_liste_singes(&liste_singes, &emp);
            printf("\nLa vague %d commence !\n", num_vague);
            sleep(2);
            vague_active = true;
            attente_vague = false;
        }

        afficher_jeu(HAUTEUR, LARGEUR, tab, &chemin_enregistre, crabe, nb_crabes, &emp, num_vague);
        printf(" PV Couronne : %d\n", couronne.pv);
        printf("\nAppuyez sur Entrée pour continuer ou 'q' + Entrée pour quitter.\n");
        usleep(100000);
    }

    return 0;
}
