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

int getTMin (int** M, sommet* s, int n, int x, int y) { // Renvoie le temps min pour aller de x à y
    int t;
    int* tmin = &t;
    x = getIndice(s, n, x);
    y = getIndice(s, n, y);
    t = - s[x].freq;
    iniEtatSommet(s, n);
    getTMinProf(M, s, n, x, y, tmin, t);
    return *tmin;
}

void getTMinProf (int** M, sommet* s, int n, int x, int y, int* t, int temp) { // Parcours en profondeur
    int j;
    s[x].etat = 0; // Etat atteint
    temp += s[x].freq;
    if (x == y) {
        *t = temp;
    } else {
        for (j = 0; j < n; j++) {
            if ((M[x][j] > 0) && (s[j].etat == -1)) { // Successeur non atteint
                getTMinProf(M, s, n, j, y, t, temp);
            }
        }
    }
    s[x].etat = 1; // Etat explore
}

void algoDijkstra (int** M, sommet* s, int n, int x) { // Calcule les plus courts chemins à partir de x
    int i, y, z;
    iniEtatSommet(s, n); // F = X
    for (i = 0; i < n; i++) { // Source Unique Initialisation
        s[i].deb = INT_MAX;
    }
    x = getIndice(s, n, x);
    z = x;
    s[x].deb = 0;
    while (nonExplore(s, n)) { // F != null
        x = getIndiceMinDeb(s, n); // x = ExtraireMin(F)
        s[x].etat = 0; // F = F - x
        for (y = 0; y < n; y++) {
            //printf("M[%d][%d] = %d\n", x+1, y+1, M[x][y]);
            if (M[x][y] > 0) { // Successeur
                if (s[y].deb > s[x].deb + s[y].freq) { // Relacher
                    s[y].deb = s[x].deb + s[y].freq;
                }
            }
        }
    }
    for (i = 0; i < n; i++) {
        printf("%d -> %d = %d\n", s[z].id, s[i].id, s[i].deb);
    }
}
