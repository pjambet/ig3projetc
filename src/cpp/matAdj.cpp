/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : matAdj.cpp
OBJET            : matrice d'adjacence
--------------------------------------------------------------------------------
DATE DE CREATION : 12/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../h/sommet.h"
#include "../h/matAdj.h"

void matAdjCFC (char* a) { // Renvoie les composantes fortement connexes du graphe
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

        printMat(M);
        iniSommet(s);
        PPG(M, s);
        triDecroissant(s);
        PPGD(M, s);
        iniSommet(s);
        printCFC(s);

    } else {
        printf("Lecture du fichier impossible\n");
    }
}

void printMat (int** M) { // Affiche la matrice adjacente
    int i, j;
    printf(" ");
    for (i = 0; i < TAILLE_MAT; i++) {
        if (i <= 9)
            printf("  %d", i+1);
        else
            printf(" %d", i+1);
    }
    printf("\n");
    for (i = 0; i < TAILLE_MAT; i++) {
        if (i < 9)
            printf("%d  ", i+1);
        else
            printf("%d ", i+1);
        for (j = 0; j < TAILLE_MAT; j++) {
            printf("%d  ", M[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void PPG (int** M, sommet* s) { // Parcours en profondeur du graphe (appel sur PProfG)
    int i;
    int temps = 0;
    int* t = &temps;
    for (i = 0; i < TAILLE_MAT; i++) {
        s[i].etat = -1; // Etat non atteint
        s[i].deb = 0;
        s[i].fin = 0;
    }
    for (i = 0; i < TAILLE_MAT; i++) {
        if (s[s[i].num].etat == -1) {
            PProfG(M, s, s[i].num, t);
        }
    }
}

void PProfG (int** M, sommet* s, int i, int* t) { // Parcours en profondeur du graphe (recursif)
    int j;
    s[i].etat = 0; // Etat atteint
    (*t)++;
    s[i].deb = *t;
    for (j = 0; j < TAILLE_MAT; j++) {
        if ((M[i][j] > 0) && (s[j].etat == -1)) { // Successeur non atteint
            PProfG(M, s, j, t);
        }
    }
    s[i].etat = 1; // Etat explore
    (*t)++;
    s[i].fin = *t;
}

void PPGD (int** M, sommet* s) { // Parcours en profondeur du graphe dual (appel sur PProfG)
    int i;
    int temps = 0;
    int* t = &temps;
    for (i = 0; i < TAILLE_MAT; i++) {
        s[i].etat = -1; // Etat non atteint
        s[i].deb = 0;
        s[i].fin = 0;
    }
    for (i = 0; i < TAILLE_MAT; i++) {
        if (s[s[i].num].etat == -1) {
            PProfGD(M, s, s[i].num, t);
        }
    }
}

void PProfGD (int** M, sommet* s, int i, int* t) { // Parcours en profondeur du graphe dual (recursif)
    int j;
    s[i].etat = 0; // Etat atteint
    (*t)++;
    s[i].deb = *t;
    for (j = 0; j < TAILLE_MAT; j++) {
        if ((M[j][i] > 0) && (s[j].etat == -1)) { // Successeur non atteint
            PProfGD(M, s, j, t);
        }
    }
    s[i].etat = 1; // Etat explore
    (*t)++;
    s[i].fin = *t;
}
