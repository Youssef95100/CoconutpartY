#include "couronne.h"


int ini_couronne(Couronne couronne){
    
    
    printf("Saisir le nombre de points de vie de la couronne : ");
    while(scanf("%d", &couronne.pv) != 1 || couronne.pv <= 0){
        printf("Erreur de saisie. Veuillez réessayer !\n");
        scanf("%d", &couronne.pv); // a revoir si on met un char 
    } 
    printf("\nLa couronne a %d points de vie\n", couronne.pv);
    
    return couronne.pv;
}






//condition d'arrêts du jeu. Cette fonction sert a baisser de 1 les pv de la couronne a chaque crabe l'attegnant
int pv_couronne(Couronne couronne,Crabe crabe ){

    if(crabe.x == couronne.x && crabe.y == couronne.y){
        couronne.pv --;
    }



    if (pv_couronne <= 0){
        printf("La couronne est détruite !\n");
        return 0;
    }
    else{
        printf("La couronne a encore %d points de vie\n", couronne.pv);
        return 1;   
    }   

}