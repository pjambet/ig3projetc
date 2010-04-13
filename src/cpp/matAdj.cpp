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

void matAdjCFC (char* a) { // Renvoie les composantes fortement connexes du graphe
    int i = 0, j = 0, k;
    int** M = (int**) malloc(tailleMat*sizeof(int));
    for (k = 0; k < tailleMat; k++) {
        M[k] = (int*) malloc(tailleMat*sizeof(int));
    }
    sommet* s = (sommet*) malloc(tailleMat*sizeof(int));
    char c;
    FILE* fichier;
    fichier = fopen(a, "r"); //fichier = fopen("./test/graph.txt", "r");
    if (fichier != NULL) {
        while (!feof(fichier)) {
            c = fgetc(fichier);
            if (i == tailleMat) {
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
    for (i = 0; i < tailleMat; i++) {
        if (i <= 9)
            printf("  %d", i+1);
        else
            printf(" %d", i+1);
    }
    printf("\n");
    for (i = 0; i < tailleMat; i++) {
        if (i < 9)
            printf("%d  ", i+1);
        else
            printf("%d ", i+1);
        for (j = 0; j < tailleMat; j++) {
            printf("%d  ", M[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void printCFC (sommet* s) {
    int d, f, i = 0;
    printf("Les composantes fortement connexes du graphe sont :\n{%d", (s[i].num)+1);
    d = s[i].deb;
    f = s[i].fin;
    while (i < tailleMat) {
        if ((d < (s[i+1].deb)) && (f > (s[i+1].fin))) {
            printf(", %d", (s[i+1].num)+1);
            i++;
        } else {
            i++;
            d = s[i].deb;
            f = s[i].fin;
            if (i < tailleMat)
                printf("}, {%d", (s[i].num)+1);
            else
                printf("}.");
        }
    }
    printf("\n");
}

void iniSommet (sommet* s) { // // Initialise les valeurs de la structure sommet
    int i;
    for (i = 0; i < tailleMat; i++) {
        s[i].num = i;
    }
}

void PPG (int** M, sommet* s) { // Parcours en profondeur du graphe (appel sur PProfG)
    int i;
    int temps = 0;
    int* t = &temps;
    for (i = 0; i < tailleMat; i++) {
        s[i].etat = -1; // Etat non atteint
        s[i].deb = 0;
        s[i].fin = 0;
    }
    for (i = 0; i < tailleMat; i++) {
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
    for (j = 0; j < tailleMat; j++) {
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
    for (i = 0; i < tailleMat; i++) {
        s[i].etat = -1; // Etat non atteint
        s[i].deb = 0;
        s[i].fin = 0;
    }
    for (i = 0; i < tailleMat; i++) {
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
    for (j = 0; j < tailleMat; j++) {
        if ((M[j][i] > 0) && (s[j].etat == -1)) { // Successeur non atteint
            PProfGD(M, s, j, t);
        }
    }
    s[i].etat = 1; // Etat explore
    (*t)++;
    s[i].fin = *t;
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
