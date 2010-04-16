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

    int i = 0, j = 0, k, n, m, q, x, y;
    int** M;
    liste* L;
    liste* P;
    sommet* s;
    char* NOM_GRAPH;
    char NOM_DIR[6] = "test/";
    char TYPE_STRUCT;
    char c;
    char buffer[32];
    FILE* fichier;

    if (argc > 1) {
        NOM_GRAPH = argv[1];
    } else {
        NOM_GRAPH = (char*) malloc(10*sizeof(char));
        printf("Entrez le nom du graphe.\n");
        scanf("%s", NOM_GRAPH);
        printf("\n");
    }
    strcat(NOM_DIR, NOM_GRAPH);
    strcpy(NOM_GRAPH, NOM_DIR);

    while ((TYPE_STRUCT != 'm') && (TYPE_STRUCT != 'l')) {
        printf("Choix de la structure (m ou l)\n");
        scanf("%c", &TYPE_STRUCT);
    }

    fichier = fopen(NOM_GRAPH, "r");
    if (fichier != NULL) {

        c = fgetc(fichier);
        n = atoi(&c); // nombre de sommets du graphe
        fgetc(fichier);

        s = iniSommet(n);
        M = iniMat(n);

        L = (liste*) malloc(n*sizeof(liste));
        for (k = 0; k < n; k++) {
            L[k] = NULL;
        }

        P = (liste*) malloc(n*sizeof(liste));
        for (k = 0; k < n; k++) {
            P[k] = NULL;
        }

        k = 0;
        while (i < n) {
            c = fgetc(fichier);
            if (c != '\n') {
                if (c != ',') {
                    buffer[j] = c;
                    j++;
                } else {
                    buffer[j] = '\0';
                    j = 0;
                    if (k == 0) {
                        strcpy(s[i].nom, buffer);
                    } else {
                        s[i].id = atoi(buffer);
                    }
                    fgetc(fichier);
                    k++;
                }
            } else {
                buffer[j] = '\0';
                j = 0;
                k = 0;
                s[i].freq = atoi(buffer);
                s[i].num = i;
                i++;
            }
        }

        i = 0;
        c = fgetc(fichier);
        m = atoi(&c); // nombre d'arrêtes
        fgetc(fichier);
        while (i < m) {
            c = fgetc(fichier);
            if (c != '\n') {
                if (c != ',') {
                    buffer[j] = c;
                    j++;
                } else {
                    buffer[j] = '\0';
                    j = 0;
                    x = getIndice(s, n, atoi(buffer));
                    fgetc(fichier);
                }
            } else {
                buffer[j] = '\0';
                j = 0;
                y = getIndice(s, n, atoi(buffer));
                M[y][x] = 1;
                i++;
            }
        }

        i = 0;
        c = fgetc(fichier);
        q = atoi(&c); // nombre de questions
        fgetc(fichier);
        while (i < q) {
            c = fgetc(fichier);
            if (c != '\n') {
                if (c != ' ') {
                    buffer[j] = c;
                    j++;
                } else {
                    buffer[j] = '\0';
                    j = 0;
                    fgetc(fichier);
                    fgetc(fichier);
                    fgetc(fichier);
                }
            } else {
                buffer[j] = '\0';
                j = 0;
                i++;
            }
        }

        if (TYPE_STRUCT == 'm') { // Matrice

            printf("Matrice d'adjacence :\n");
            PPG(M, s, n);
            triDecroissant(s, n);
            PPGD(M, s, n);
            printCFC(s, n);

        } else { // Liste

            printf("\nListe d'adjacence :\n");
            PPG(L, s, n);
            triDecroissant(s, n);
            PPGD(P, s, n);
            printCFC(s, n);

        }

        fclose(fichier);

    } else {
        printf("Lecture du fichier impossible\n");
    }

                    /*if (atoi(&c)) { // Ajout à la fin de l[j] de i
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
}
