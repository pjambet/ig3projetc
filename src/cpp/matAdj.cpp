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

int** iniMat (int n) { // Renvoie la matrice d'adjacence
    int i, j;
    int** M = (int**) malloc(n*sizeof(int));
    for (i = 0; i < n; i++) {
        M[i] = (int*) malloc(n*sizeof(int));
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            M[j][i] = 0;
        }
    }
    return M;
}

void printMat (int** M, int n) { // Affiche la matrice adjacente
    int i, j;
    printf("\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%d  ", M[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void PPG (int** M, sommet* s, int n) { // Parcours en profondeur du graphe (appel sur PProfG)
    int i;
    int temps = 0;
    int* t = &temps;
    for (i = 0; i < n; i++) {
        s[i].etat = -1; // Etat non atteint
        s[i].deb = 0;
        s[i].fin = 0;
    }
    for (i = 0; i < n; i++) {
        if (s[s[i].num].etat == -1) {
            PProfG(M, s, s[i].num, t, n);
        }
    }
    triDecroissant(s, n);
}

void PProfG (int** M, sommet* s, int i, int* t, int n) { // Parcours en profondeur du graphe (recursif)
    int j;
    s[i].etat = 0; // Etat atteint
    (*t)++;
    s[i].deb = *t;
    for (j = 0; j < n; j++) {
        if ((M[i][j] > 0) && (s[j].etat == -1)) { // Successeur non atteint
            PProfG(M, s, j, t, n);
        }
    }
    s[i].etat = 1; // Etat explore
    (*t)++;
    s[i].fin = *t;
}

void PPGD (int** M, sommet* s, int n) { // Parcours en profondeur du graphe dual (appel sur PProfG)
    int i;
    int temps = 0;
    int* t = &temps;
    for (i = 0; i < n; i++) {
        s[i].etat = -1; // Etat non atteint
        s[i].deb = 0;
        s[i].fin = 0;
    }
    for (i = 0; i < n; i++) {
        if (s[s[i].num].etat == -1) {
            PProfGD(M, s, s[i].num, t, n);
        }
    }
}

void PProfGD (int** M, sommet* s, int i, int* t, int n) { // Parcours en profondeur du graphe dual (recursif)
    int j;
    s[i].etat = 0; // Etat atteint
    (*t)++;
    s[i].deb = *t;
    for (j = 0; j < n; j++) {
        if ((M[j][i] > 0) && (s[j].etat == -1)) { // Successeur non atteint
            PProfGD(M, s, j, t, n);
        }
    }
    s[i].etat = 1; // Etat explore
    (*t)++;
    s[i].fin = *t;
}
