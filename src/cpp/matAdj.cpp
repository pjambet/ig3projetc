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

static int t = 0;

int** allocMat (int** M) { // Alloue une matrice adjacente
    int i;
    M = (int**) malloc(tailleMat*sizeof(int));
    for (i = 0; i < tailleMat; i++) {
        M[i] = (int*) malloc(tailleMat*sizeof(int));
    }
    return M;
}

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
    int i, j;
    int** Mp = allocMat(Mp);
    for (i = 0; i < tailleMat; i++) {
        for (j = 0; j < tailleMat; j++) {
            Mp[i][j] = M[i][j];
        }
    }
    return Mp;
}

int** matDuale (int** M) { // Renvoie la matrice duale de M
    int i, j;
    int** Mp = allocMat(Mp);
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
    t++;
    s[i].deb = t;
    for (j = 0; j < tailleMat; j++) {
        if ((M[i][j] > 0) && (s[j].etat == -1)) { // Successeur non atteint
            PProf(M, j, s);
        }
    }
    s[i].etat = 1; // Etat explore
    t++;
    s[i].fin = t;
}

sommet* PP (int** M) { // Parcours en profondeur
    int i;
    sommet* s = (sommet*) malloc(tailleMat*sizeof(int));
    for (i = 0; i < tailleMat; i++) {
        s[i].num = i+1;
        s[i].etat = -1; // Etat non atteint
        s[i].deb = 0;
        s[i].fin = 0;
    }
    for (i = 0; i < tailleMat; i++) {
        if (s[i].etat == -1)
            PProf(M, i, s);
    }
    return s;
}

void ordreDual (sommet* s) { // Renvoie l'ordre de parcours de G^D (trié par ordre décroissant des temps d'accès finaux)
    int i, tmp = 0, continuer = 1;
    int* o = (int*) malloc(tailleMat*sizeof(int));
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
    for (i = 0; i < tailleMat; i++) {
        o[i] = s[i].num;
        printf("%d ", o[i]);
    }
    printf("\n");
    //return o;
}

void printSommet (sommet* s) { // Affiche le tableau d'informations des sommets
    int i;
    for (i = 0; i < tailleMat; i++) {
        printf("Sommet %d = %d/%d\n", s[i].num, s[i].deb, s[i].fin);
    }
    printf("\n");
}

/*int** addiMat (int** M1, int** M2) {
    int i, j;
    int** M = allocMat(M);
    for (i = 0; i < tailleMat; i++) {
        for (j = 0; j < tailleMat; j++) {
            if ((M1[i][j] == 1) || (M2[i][j] == 1))
                M[i][j] = 1;
            else
                M[i][j] = 0; // M[i][j] = (M1[i][j] == 1) || (M2[i][j] == 1);
        }
    }
    return M;
}

int** prodMat (int** M1, int** M2) {
    int i, j, k;
    int** M = allocMat(M);
    for (i = 0; i < tailleMat; i++) {
        for (j = 0; j < tailleMat; j++) {
            for (k = 0; k < tailleMat; k++) {
                M[i][j] += M1[i][k]*M2[k][j];
            }
        }
    }
    return M;
}

int** fermetureTrans (int** M) {
    int** G = copieMat(M);
    int** Gk = copieMat(M);
    int i;
    for (i = 1; i < tailleMat; i++) {
        Gk = prodMat(Gk, M);
        G = addiMat(Gk, G);
    }
    return G;
}
*/
