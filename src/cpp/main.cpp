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
#include <string.h>
#include "../h/matAdj.h"
#include "../h/lsc.h"

int main(int argc, char* argv[]) {
    int i = 0, j = 0;
    int** Mat = allocMat(Mat);
    sommet* s = (sommet*) malloc(tailleMat*sizeof(int));
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
        s = PP(Mat);
        printSommet(s);
        //ordreDual(s);
    } else {
        printf("Lecture du fichier impossible\n");
    }
    return 0;
}
