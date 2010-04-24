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
#include <iostream>
#include <string>
#include "../h/sommet.h"
#include "../h/matAdj.h"

using namespace std;

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

void DepthFirstSearch (int** M, sommet* s, int n) { // Parcours en profondeur du graphe
    int i, child = 0, temps = 0;
    int* t = &temps;
    if (s[0].etat == -1) { // Premier DFS
        for (i = 0; i < n; i++) {
            if (s[s[i].num].etat == -1) {
                DepthFirstSearchVisit(M, s, n, s[i].num, t, 1);
            }
        }
        for (i = 1; i < n; i++) { // root check
            if (s[i].parent == 0) {
                child++;
            }
        }
        if (child > 1) {
            s[0].important = 1;
        }
        triDecroissant(s, n);
    } else { // Second DFS avec M transposé
        iniEtatSommet(s, n);
        for (i = 0; i < n; i++) {
            if (s[s[i].num].etat == -1) {
                DepthFirstSearchVisit(M, s, n, s[i].num, t, 2);
            }
        }
    }
}

void DepthFirstSearchVisit (int** M, sommet* s, int n, int i, int* t, int numDFS) { // Parcours en profondeur du graphe (recursif)
    int j;
    s[i].etat = 0; // Etat atteint
    (*t)++;
    s[i].deb = *t;
    s[i].low = *t;
    for (j = 0; j < n; j++) {
        if (numDFS == 1) {
            if (M[i][j] > 0) { // Successeur
                if (s[j].etat == -1) { // forward edge
                    s[j].parent = i;
                    DepthFirstSearchVisit(M, s, n, j, t, numDFS);
                    if (s[j].low >= s[i].deb && i != 0) {
                        s[i].important = 1;
                    }
                    if (s[j].low < s[i].low) {
                        s[i].low = s[j].low;
                    }
                } else if (s[i].parent != j) { // back edge
                    if (s[j].deb < s[i].low) {
                        s[i].low = s[j].deb;
                    }
                }
            }
        } else if (numDFS == 2) {
            if (M[j][i] > 0) { // Successeur
                if (s[j].etat == -1) { // forward edge
                    s[j].parent = i;
                    DepthFirstSearchVisit(M, s, n, j, t, numDFS);
                    if (s[j].low >= s[i].deb && i != 0) {
                        s[i].important = 1;
                    }
                    if (s[j].low < s[i].low) {
                        s[i].low = s[j].low;
                    }
                } else if (s[i].parent != j) { // back edge
                    if (s[j].deb < s[i].low) {
                        s[i].low = s[j].deb;
                    }
                }
            }
        }
    }
    (*t)++;
    s[i].fin = *t;
}

void ShortestPath (int** M, sommet* s, int n, int x) { // Algorithme de Dijkstra : calcule les plus courts chemins à partir de x
    int i, y, z;
    iniEtatSommet(s, n); // F = X
    for (i = 0; i < n; i++) { // Source Unique Initialisation
        s[i].deb = INT_MAX;
        s[i].fin = -1;
    }
    x = getIndice(s, n, x);
    z = x;
    s[x].deb = 0;
    while (nonExplore(s, n)) { // F != null
        x = getIndiceMinDeb(s, n); // x = ExtraireMin(F)
        s[x].etat = 0; // F = F - x
        for (y = 0; y < n; y++) {
            if (M[x][y] > 0) { // Successeur
                if (s[y].deb > s[x].deb + s[y].freq) { // Relacher
                    s[y].deb = s[x].deb + s[y].freq;
                    x = getIndice(s, n, s[x].id);
                    s[y].fin = x;
                }
            }
        }
    }
}
