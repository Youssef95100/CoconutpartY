#ifndef CRABE_H
#define CRABE_H

#include <stdio.h>
#include <stdlib.h>
#include "structure.h"

#define MAX_CRABES 5



int pvCrabe(Crabe *crabe);
int baissePvCrabe(Crabe *crabe, Singe singe);
void initialiserCrabe(Crabe* crabe);
void deplacerCrabe(Crabe* crabe, Chemin* chemin);
void mettre_a_jour_liste_singes(ListeSinges * liste, EmplacementsSinges * emp);


#endif