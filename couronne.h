#include <stdio.h>
#include "structure.h"


//condition d'arrêts du jeu. Cette fonction sert a baisser de 1 les pv de la couronne a chaque crabe l'attegnant
int pv_couronne(Couronne couronne,Crabe crabe ){

    if(Crabe.x == Couronne.x && Crabe.y == Couronne.y){
        Couronne.pv = Couronne.pv --;
        printf("La couronne a perdu %d points de vie\n", pv_couronne);
    }



    if (pv_couronne <= 0){
        printf("La couronne est détruite !\n");
        return 0;
    }
    else{
        printf("La couronne a encore %d points de vie\n", couronne);
        return 1;   
    }   

}