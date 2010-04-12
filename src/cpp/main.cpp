#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define tailleMat 5
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
    for (i = 0; i < tailleMat; i++) {
        for (j = 0; j < tailleMat; j++) {
            printf("%d ", M[j][i]);
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

void PProf (int* M, int i, sommet* s, int t) { // Parcours en profondeur
    s[i].etat = 0; // Etat atteint
    t++;
    s[i].deb = t;
    for (i = 0; i < tailleMat; i++) {
        if ((M[i] > 0) && (s[i].etat == -1)) // Successeur non atteint
            PProf(M, i, s, t);
    }
    s[i].etat = 1; // Etat explore
    t++;
    s[i].fin = t;
}

sommet* PP (int** M) { // Parcours en profondeur
    int i, t = 0;
    sommet* s = (sommet*) malloc(tailleMat*sizeof(int));
    for (i = 0; i < tailleMat; i++) {
        s[i].etat = -1; // Etat non atteint
    }
    for (i = 0; i < tailleMat; i++) {
        PProf(M[i], i, s, t);
    }
    return s;
}

void CFCx (int** M, int x) { // Composante Forcement Connexe d'un sommet

}

void CFC (int** M) { // Ensemble des Composantes Fortement Connexe d'un graphe
    PP(M);
    PP(matDuale(M));
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
                Mat[i][j] = atoi(&c);
                i++;
            }
        }
        fclose(fichier);
        printMat(Mat);
    }
    return 0;
}
