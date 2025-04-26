#include "terrain.h"

void afficher()
{
    int tab[3][4] = {
                            { 0,  0,  0,  0  },
                            { 0,  0,  0,  0  },
                            { 0,  0,  0,  0  }
                    };

    // Affichage du tableau
    for (int i = 0; i < 3; i++) 
    {
        for (int j = 0; j < 4; j++) 
        {
            printf("%d ", tab[i][j]);
        }
        printf("\n");
    }


}