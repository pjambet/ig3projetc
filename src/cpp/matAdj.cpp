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

int** copieMat (int** M) { // Renvoie la copie de la matrice M
    int i, j, k;
    int** Mp = (int**) malloc(tailleMat*sizeof(int));
    for (k = 0; k < tailleMat; k++) {
        Mp[k] = (int*) malloc(tailleMat*sizeof(int));
    }
    for (i = 0; i < tailleMat; i++) {
        for (j = 0; j < tailleMat; j++) {
            Mp[i][j] = M[i][j];
        }
    }
    return Mp;
}

int** matDuale (int** M) { // Renvoie la matrice duale de M
    int i, j, k;
    int** Mp = (int**) malloc(tailleMat*sizeof(int));
    for (k = 0; k < tailleMat; k++) {
        Mp[k] = (int*) malloc(tailleMat*sizeof(int));
    }
    for (i = 0; i < tailleMat; i++) {
        for (j = 0; j < tailleMat; j++) {
            Mp[i][j] = M[j][i];
        }
    }
    return Mp;
}

void PProf (int** M, int i, sommet* s) { // Parcours en profondeur
    int j;
    s[i].etat = 0; // Etat atteint
    temps++;
    s[i].deb = temps;
    for (j = 0; j < tailleMat; j++) {
        if ((M[i][j] > 0) && (s[j].etat == -1)) { // Successeur non atteint
            PProf(M, j, s);
        }
    }
    s[i].etat = 1; // Etat explore
    temps++;
    s[i].fin = temps;
}

void PP (int** M, sommet* s) { // Parcours en profondeur
    int i;
    temps = 0;
    for (i = 0; i < tailleMat; i++) {
        s[i].num = i;
        s[i].etat = -1; // Etat non atteint
        s[i].deb = 0;
        s[i].fin = 0;
    }
    for (i = 0; i < tailleMat; i++) {
        if (s[s[i].num].etat == -1)
            PProf(M, i, s);
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
    printf("{");
    for (i = 0; i < tailleMat-1; i++) {
        //printf("i= %d\n", i);
        if ((s[i].fin) < (s[i+1].deb)) {
            printf("%d}", s[i].num+1);
            if (i < tailleMat-2)
                printf(", {");
        } else {
            if (i < tailleMat-2)
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
