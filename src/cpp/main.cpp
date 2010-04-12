/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : main.cpp
OBJET            : programme principal
--------------------------------------------------------------------------------
DATE DE CREATION : 12/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#include <stdio.h>
#include <stdlib.h>
#include "../h/matAdj.h"
#include "../h/lsc.h"

int main(int argc, char* argv[]) {
    int i = 0, j = 0, k;
    int** Mat = (int**) malloc(tailleMat*sizeof(int));
    for (k = 0; k < tailleMat; k++) {
        Mat[k] = (int*) malloc(tailleMat*sizeof(int));
    }
    sommet* S = (sommet*) malloc(tailleMat*sizeof(int));
    char c;
    FILE* fichier;
    fichier = fopen(argv[1], "r");
    if (fichier != NULL) {
        while (!feof(fichier)) {
            c = fgetc(fichier);
            if (i == tailleMat) {
                j++;
                i = 0;
            } else {
                Mat[j][i] = atoi(&c);
                i++;
            }
        }
        fclose(fichier);

        PP(Mat, S);
        triDecroissant(S);
        PP(matDuale(Mat), S);
        printf("Les composantes fortement connexes du graphe sont :\n");
        CFC(S);

    } else {
        printf("Lecture du fichier impossible\n");
    }
    system("PAUSE");
    return 0;
}
