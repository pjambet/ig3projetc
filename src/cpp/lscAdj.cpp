/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : lscAdj.cpp
OBJET            : liste simplement chaînée d'adjacence
--------------------------------------------------------------------------------
DATE DE CREATION : 13/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../h/sommet.h"
#include "../h/lscAdj.h"

void lscAdjCFC (char* a) { // Renvoie les composantes fortement connexes du graphe
    int i = 0, j = 0, k;
    int** M = (int**) malloc(TAILLE_MAT*sizeof(int));
    for (k = 0; k < TAILLE_MAT; k++) {
        M[k] = (int*) malloc(TAILLE_MAT*sizeof(int));
    }
    sommet* s = (sommet*) malloc(TAILLE_MAT*sizeof(int));
    char c;
    FILE* fichier;
    fichier = fopen(a, "r");
    if (fichier != NULL) {
        while (!feof(fichier)) {
            c = fgetc(fichier);
            if (i == TAILLE_MAT) {
                j++;
                i = 0;
            } else {
                M[j][i] = atoi(&c);
                i++;
            }
        }
        fclose(fichier);

    } else {
        printf("Lecture du fichier impossible\n");
    }
}

void printLSC (int** M) { // Affiche la liste adjacente

}

void PPG (int* M, sommet* s) { // Parcours en profondeur du graphe (appel sur PProfG)

}

void PProfG (int* M, sommet*, int i, int* t) { // Parcours en profondeur du graphe (recursif)

}

void PPGD (int* M, sommet* s) { // Parcours en profondeur du graphe dual (appel sur PProfGD)

}

void PProfGD (int* M, sommet* s, int i, int* t) { // Parcours en profondeur du graphe dual (recursif)

}
