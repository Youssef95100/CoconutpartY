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
    if ((crabe->x - singe.x <= singe.rayon || crabe->x - singe.x >= - singe.rayon) && (crabe->y - singe.y <= singe.rayon || crabe->y - singe.y >= -singe.rayon)){ // le big if il veut dire "si le crabe est dans le rayon du singe"


        printf("Le singe attaque le crabe ! Il lui a fait %d dégats !\n", singe.degat);
        crabe->pv -= singe.degat;

    }
    return crabe->pv;
}