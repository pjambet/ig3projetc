/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : main.cpp
OBJET            : programme principal
--------------------------------------------------------------------------------
DATE DE CREATION : 12/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#include <stdio.h>
#include <stdlib.h>
#include "../h/matAdj.h"
#include "../h/lscAdj.h"
#include "../h/generate_mat.h"

int main(int argc, char* argv[]) {

    int i, n, m, x = 0, y = 0;
    int** M;
    liste* L;
    liste* P;
    sommet* s;
    char* NOM_IN;
    char* NOM_OUT;
    char DIR_IN[6] = "test/";
    char DIR_OUT[6] = "test/";
    char TYPE_STRUCT;
    char buffer[32], buffer2[32];
    FILE* fichier;

    if (argc > 2) {
        NOM_IN = argv[1];
        NOM_OUT = argv[2];
    } else if (argc > 1) {
        NOM_IN = argv[1];
        NOM_OUT = (char*) malloc(16*sizeof(char));
        strcpy(NOM_OUT, NOM_IN);
        strcat(NOM_OUT, ".res");
    } else {
        NOM_IN = (char*) malloc(16*sizeof(char));
        NOM_OUT = (char*) malloc(16*sizeof(char));
        printf("Entrez le nom du graphe.\n");
        scanf("%s", NOM_IN);
        printf("Entrez le nom du fichier resultat.\n");
        scanf("%s", NOM_OUT);
        printf("\n");
    }
    strcat(DIR_IN, NOM_IN);
    strcat(DIR_OUT, NOM_OUT);

    printf("Choix de la structure (m ou l) :\n");
    while ((TYPE_STRUCT != 'm') && (TYPE_STRUCT != 'l')) {
        scanf("%c", &TYPE_STRUCT);
    }

    fichier = fopen(DIR_IN, "r");
    if (fichier != NULL) {

        fgets(buffer, 8, fichier); // lecture du nombre de sommets du graphe
        i = 0;
        n = atoi(buffer);
        s = iniSommet(n);
        M = iniMat(n);

        while (i < n) { // lecture des id / nom / frequence
            fscanf(fichier, "%[^,], %d, %d\n", buffer, &x, &y);
            strcat(buffer, " ");
            strcat(buffer, buffer2);
            strcpy(s[i].nom, buffer);
            s[i].num = i;
            s[i].id = x;
            s[i].freq = y;
            i++;
        }

        fgets(buffer, 8, fichier); // lecture du nombre d'arretes du graphe
        i = 0;
        m = atoi(buffer);
        while (i < m) { // lecture les relations entre les sommets
            fscanf(fichier, "%d, %d", &x, &y);
            x = getIndice(s, n, x);
            y = getIndice(s, n, y);
            M[y][x] = 1;
            i++;
        }

        fgets(buffer, 8, fichier); // lecture du nombre de questions
        i = 0;
        m = atoi(buffer);
        fgetc(fichier);
        while (i < m) { // lecture des questions
            fscanf(fichier, "%d -> %d", &x, &y);
            // TODO : Traitement des questions
        }

        fclose(fichier);

        if (TYPE_STRUCT == 'm') { // Matrice


            PPG(M, s, n);
            triDecroissant(s, n);
            PPGD(M, s, n);

        } else { // Liste

            PPG(L, s, n);
            triDecroissant(s, n);
            PPGD(P, s, n);

        }

        m = getNbCFC(s, n);
        itoa(m, buffer, 10);
        fichier = fopen(DIR_OUT, "w+");
        fputc(buffer[0], fichier);
        fputc('\n', fichier);
        for (i = 0; i < m; i++) {

        }

        fclose(fichier);

    } else {
        printf("Lecture du fichier impossible\n");
    }

}

    /*L = (liste*) malloc(n*sizeof(liste));
    for (i = 0; i < n; i++) {
        L[i] = NULL;
    }

    P = (liste*) malloc(n*sizeof(liste));
    for (i = 0; i < n; i++) {
        P[i] = NULL;
    }

    if (atoi(&c)) { // Ajout à la fin de l[j] de i
        liste p = (liste) malloc(sizeof(cell));
        liste pd = (liste) malloc(sizeof(cell));
        p->val = i;
        pd->val = j;
        p->suiv = NULL;
        pd->suiv = NULL;
        if (l[j] == NULL) {
            l[j] = p;
        } else {
            liste temp = l[j];
            while (temp->suiv != NULL) {
                temp = temp->suiv;
            }
            temp->suiv = p;
        }
        if (ld[i] == NULL) {
            ld[i] = pd;
        } else {
            liste temp = ld[i];
            while (temp->suiv != NULL) {
                temp = temp->suiv;
            }
            temp->suiv = pd;
        }
    }
    i++;*/
