/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : matAdj.cpp
OBJET            : matrice adjacente
--------------------------------------------------------------------------------
DATE DE CREATION : 12/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../h/matAdj.h"

int temps;

void printMat (int** M) { // Affiche la matrice adjacente
    int i, j;
    printf("  1 2 3 4 5 6 7 8\n");
    for (i = 0; i < tailleMat; i++) {
        printf("%d ", i+1);
        for (j = 0; j < tailleMat; j++) {
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void PProfG (int** M, int i, sommet* s) { // Parcours en profondeur du graphe
    int j;
    s[i].etat = 0; // Etat atteint
    temps++;
    s[i].deb = temps;
    for (j = 0; j < tailleMat; j++) {
        if ((M[i][j] > 0) && (s[j].etat == -1)) { // Successeur non atteint
            PProfG(M, j, s);
        }
    }
    s[i].etat = 1; // Etat explore
    temps++;
    s[i].fin = temps;
}

void PProfGD (int** M, int i, sommet* s) { // Parcours en profondeur du graphe dual
    int j;
    s[i].etat = 0; // Etat atteint
    temps++;
    s[i].deb = temps;
    for (j = 0; j < tailleMat; j++) {
        if ((M[j][i] > 0) && (s[j].etat == -1)) { // Successeur non atteint
            PProfGD(M, j, s);
        }
    }
    s[i].etat = 1; // Etat explore
    temps++;
    s[i].fin = temps;
}

void PP (int** M, sommet* s, char mode) { // Parcours en profondeur
    int i;
    temps = 0;
    for (i = 0; i < tailleMat; i++) {
        s[i].num = i;
        s[i].etat = -1; // Etat non atteint
        s[i].deb = 0;
        s[i].fin = 0;
    }
    for (i = 0; i < tailleMat; i++) {
        if (s[s[i].num].etat == -1) {
            if (mode == 'g') {
                PProfG(M, i, s);
            } else {
                PProfGD(M, i, s);
            }
        }
    }
}

void triDecroissant (sommet* s) { // Renvoie l'ordre de parcours de la matrice duale (trié par ordre décroissant des temps d'accès finaux)
    int i, tmp = 0, continuer = 1;
    while (continuer) {
        continuer--;
        for (i = 0; i < tailleMat-1; i++) {
            if (s[i].fin < s[i+1].fin) {
                tmp = s[i+1].fin;
                s[i+1].fin = s[i].fin;
                s[i].fin = tmp;

                tmp = s[i+1].deb;
                s[i+1].deb = s[i].deb;
                s[i].deb = tmp;

                tmp = s[i+1].num;
                s[i+1].num = s[i].num;
                s[i].num = tmp;
                continuer++;
            }
        }
    }
}

void CFC (sommet* s) { // Renvoie les composantes fortement connexes du graphe
    int i;
    printf("Les composantes fortement connexes du graphe sont :\n{");
    for (i = 0; i < tailleMat; i++) {
        //printf("i= %d\n", i);
        if ((s[i].fin) < (s[i+1].deb)) {
            printf("%d}", s[i].num+1);
            //if (i < tailleMat)
            printf(", {");
        } else {
            if (i < tailleMat-1)
                printf("%d, ", s[i].num+1);
            else
                printf("%d}\n", s[i].num+1);
        }
    }
}

void printSommet (sommet* s) { // Affiche le tableau d'informations des sommets
    int i;
    for (i = 0; i < tailleMat; i++) {
        printf("Sommet %d = %d/%d\n", s[i].num+1, s[i].deb, s[i].fin);
    }
    printf("\n");
}
