#ifndef structure_h
#define structure_h

#define MAX_SINGES 100
#define MAX_POSITIONS 26

#include <stdio.h>
#include <stdlib.h> 

typedef struct{
    int x;
    int y;
    int pv;
}Crabe;

typedef struct{
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