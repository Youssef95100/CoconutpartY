#ifndef structure_h
#define structure_h

#define MAX_SINGES 100
#define MAX_POSITIONS 26

#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>

typedef struct
{
    int x;
    int y;
    int pv;
    int position; // L’indice de sa position dans le tableau de chemin
    bool actif; //pour savoir si il est en vie ou arrivé
}Crabe;

//structure pour stocker le chemin

typedef struct
{
    int x;
    int y;
}CaseChemin;

typedef struct
{
    CaseChemin cases[100];
    int taille;
}Chemin;

typedef struct
{
    int x;
    int y;
    int degat;
    int rayon;
    int niveau;
}Singe;

typedef struct
{
 Singe singe[MAX_SINGES];
 int nb_singes;
}ListeSinges;

typedef struct
{
    char id; //pour les lettres 'a', 'b'...
    int x;
    int y;
    int disponible; //1 = libre et 0 = occupé
}PositionSinge;

typedef struct
{
    PositionSinge positions[MAX_POSITIONS];
    int nb_positions;
}EmplacementsSinges;

typedef struct{
    int x;
    int y;
    int pv;
}Couronne;





#endif