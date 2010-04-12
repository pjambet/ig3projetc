#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define tailleMat 8
typedef struct sommet sommet;

struct sommet {
    int etat; // -1 = Non atteint, 0 = Atteint, 1 = Exploré
    int deb;
    int fin;
};

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

void PProf (int** M, int i, sommet* s, int t) { // Parcours en profondeur
    int j;
    s[i].etat = 0; // Etat atteint
    t++;
    s[i].deb = t;
    printf("Sommet %d (%d / *)\n", i+1, s[i].deb, s[i].fin);
    for (j = 0; j < tailleMat; j++) {
        //printf("M[%d] = %d s[%d].etat = %d\n", j+1, M[i][j], j+1, s[j].etat);
        if ((M[i][j] > 0) && (s[j].etat == -1)) { // Successeur non atteint
            printf("M[%d][%d] = %d => Sommet %d\n", i+1, j+1, M[i][j], j+1);
            PProf(M, j, s, t);
        }
    }
    s[i].etat = 1; // Etat explore
    t++;
    s[i].fin = t;
    printf("Sommet %d (%d / %d)\n", i+1, s[i].deb, s[i].fin);
}

sommet* PP (int** M) { // Parcours en profondeur
    int i, t = 0;
    sommet* s = (sommet*) malloc(tailleMat*sizeof(int));
    for (i = 0; i < tailleMat; i++) {
        s[i].etat = -1; // Etat non atteint
        s[i].deb = 0;
        s[i].fin = 0;
    }
    for (i = 0; i < tailleMat; i++) {
        if (s[i].etat == -1)
            PProf(M, i, s, t);
    }
    return s;
}

void printSommet (sommet* s) { // Affiche le tableau d'informations des sommets
    int i;
    printf("\n");
    for (i = 0; i < tailleMat; i++) {
        printf("Sommet %d = %d / %d\n", i+1, s[i].deb, s[i].fin);
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

int main(int argc, char* argv[]) {
    int i = 0, j = 0;
    int** Mat = allocMat(Mat);
    sommet* s1 = (sommet*) malloc(tailleMat*sizeof(int));
    sommet* s2 = (sommet*) malloc(tailleMat*sizeof(int));
    char c;
    FILE* fichier;

    fichier = fopen(argv[1], "r");
    if (fichier != NULL) {
        while (!feof(fichier)) {
            c = fgetc(fichier);
            if (i == tailleMat) {
                j++;
                i = 0;
            } else {
                Mat[j][i] = atoi(&c);
                i++;
            }
        }
        fclose(fichier);
        printMat(Mat);
        s1 = PP(Mat);
        printSommet(s1);
    }
    return 0;
}
