#include <stdio.h> 
#include <stdlib.h>
#include "crabe.h"


int pvCrabe(Crabe *crabe){
    if(crabe->pv <= 0){
        printf("Le crabe est mort !\n");
        crabe->x = 100; // pour le faire sortir de l'écran
        crabe->y = 100;
        return 0;
    }
    else{
        printf("Le crabe a encore %d points de vie\n", crabe->pv);
        return crabe->pv;   
    }   
}


int baissePvCrabe(Crabe *crabe, Singe singe){
    if ((crabe->x - singe.x <= singe.rayon || crabe->x - singe.x >= - singe.rayon) 
         && (crabe->y - singe.y <= singe.rayon || crabe->y - singe.y >= -singe.rayon)){ // le big if il veut dire "si le crabe est dans le rayon du singe"


        printf("Le singe attaque le crabe ! Il lui a fait %d dégats !\n", singe.degat);
        crabe->pv -= singe.degat;

    }
    return crabe->pv;
}

void initialiserCrabe(Crabe* crabe)
{
    (*crabe).position = 0;
    (*crabe).actif = true;
}

void deplacerCrabe(Crabe* crabe, Chemin* chemin, int hauteur, int largeur, int tab[hauteur][largeur])
{
    if ((*crabe).actif == false)
        return;

    // Ne pas dépasser la fin du chemin
    if ((*crabe).position >= (*chemin).taille - 1) 
    {
        (*crabe).actif = false;
        return;
    }

    // Effacer l'ancienne position uniquement si ce n'était pas le départ ni la couronne
    int ancienne_x = (*chemin).cases[(*crabe).position].x;
    int ancienne_y = (*chemin).cases[(*crabe).position].y;

    if (tab[ancienne_x][ancienne_y] == 'C') 
    {
        // On ne remet '.' que si ce n'était pas le départ ou la couronne
        if (tab[ancienne_x][ancienne_y] != '#' && tab[ancienne_x][ancienne_y] != 'X') 
        {
            tab[ancienne_x][ancienne_y] = '.';
        }
    }

    // Avancer le crabe
    (*crabe).position++;

    // Nouvelle position
    int nouvelle_x = (*chemin).cases[(*crabe).position].x;
    int nouvelle_y = (*chemin).cases[(*crabe).position].y;

    // Si c'est la couronne, on ne remplace pas 'X', on arrête le crabe
    if (tab[nouvelle_x][nouvelle_y] == 'X') {
        (*crabe).actif = false;
        return;
    }

    // Sinon, afficher le crabe
    tab[nouvelle_x][nouvelle_y] = 'C';
}