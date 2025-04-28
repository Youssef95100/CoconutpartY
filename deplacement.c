// Déplacer un personnage (crabe ou singe) uniquement sur les 'P'
void Deplacer_Personnage(char *Terrain, int longueur, int largeur, int *x, int *y, char direction) {
    int nouveau_x = *x;
    int nouveau_y = *y;

    if (direction == 'z' && *x > 0)              nouveau_x--; // haut
    else if (direction == 's' && *x < longueur-1) nouveau_x++; // bas
    else if (direction == 'q' && *y > 0)           nouveau_y--; // gauche
    else if (direction == 'd' && *y < largeur-1)   nouveau_y++; // droite

    if (Terrain[nouveau_x * largeur + nouveau_y] == 'P') {
        *x = nouveau_x;
        *y = nouveau_y;
    } else {
        printf("Déplacement impossible : pas de chemin ici !\n");
    }
}
