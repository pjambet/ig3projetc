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
#include <limits.h>
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
    iniEtatSommet(s, n);
    for (i = 0; i < n; i++) {
        if (s[s[i].num].etat == -1) {
            PProfG(M, s, n, s[i].num, t);
        }
    }
    triDecroissant(s, n);
}

void PProfG (int** M, sommet* s, int n, int i, int* t) { // Parcours en profondeur du graphe (recursif)
    int j;
    s[i].etat = 0; // Etat atteint
    (*t)++;
    s[i].deb = *t;
    for (j = 0; j < n; j++) {
        if ((M[i][j] > 0) && (s[j].etat == -1)) { // Successeur non atteint
            PProfG(M, s, n, j, t);
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
    iniEtatSommet(s, n);
    for (i = 0; i < n; i++) {
        if (s[s[i].num].etat == -1) {
            PProfGD(M, s, n, s[i].num, t);
        }
    }
}

void PProfGD (int** M, sommet* s, int n, int i, int* t) { // Parcours en profondeur du graphe dual (recursif)
    int j;
    s[i].etat = 0; // Etat atteint
    (*t)++;
    s[i].deb = *t;
    for (j = 0; j < n; j++) {
        if ((M[j][i] > 0) && (s[j].etat == -1)) { // Successeur non atteint
            PProfGD(M, s, n, j, t);
        }
    }
    s[i].etat = 1; // Etat explore
    (*t)++;
    s[i].fin = *t;
}

void algoDijkstra (int** M, sommet* d, int n, int x) { // Calcule les plus courts chemins à partir de x
    int i, y, z;
    iniEtatSommet(d, n); // F = X
    for (i = 0; i < n; i++) { // Source Unique Initialisation
        d[i].deb = INT_MAX;
        d[i].fin = -1;
    }
    x = getIndice(d, n, x);
    z = x;
    d[x].deb = 0;
    while (nonExplore(d, n)) { // F != null
        x = getIndiceMinDeb(d, n); // x = ExtraireMin(F)
        d[x].etat = 0; // F = F - x
        for (y = 0; y < n; y++) {
            if (M[x][y] > 0) { // Successeur
                if (d[y].deb > d[x].deb + d[y].freq) { // Relacher
                    printf("relacher(%d, %d) : %d > %d + %d => d(%d) = %d\n", d[x].id, d[y].id, d[y].deb, d[x].deb, d[y].freq, d[y].id, d[x].deb+d[y].freq);
                    d[y].deb = d[x].deb + d[y].freq;
                    x = getIndice(d, n, d[x].id);
                    d[y].fin = x;
                }
            }
        }
    }
}
