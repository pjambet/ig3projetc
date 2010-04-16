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
    int i = 0, j = 0, k, n, m, q, ind = 0;
    char* NOM_GRAPH;
    char NOM_DIR[6] = "test/";
    char TYPE_STRUCT;
    char c;
    char buffer[32];
    char* num = (char*) malloc(16*sizeof(char));
    char* freq = (char*) malloc(16*sizeof(char));
    //sommet* s = (sommet*) malloc(n*sizeof(sommet));

    /*int** M = (int**) malloc(n*sizeof(int));
    for (k = 0; k < n; k++) {
        M[k] = (int*) malloc(n*sizeof(int));
    }

    liste* l = (liste*) malloc(n*sizeof(liste));
    for (k = 0; k < n; k++) {
        l[k] = NULL;
    }

    liste* ld = (liste*) malloc(n*sizeof(liste));
    for (k = 0; k < n; k++) {
        ld[k] = NULL;
    }*/

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

    FILE* fichier;
    fichier = fopen(NOM_GRAPH, "r");
    if (fichier != NULL) {
        c = fgetc(fichier);
        n = atoi(&c); // nombre de sommets du graphe
        fgetc(fichier);

        while (i < n) {
            c = fgetc(fichier);
            if (c != '\n') {
                if (c != ',') {
                    buffer[j] = c;
                    j++;
                } else {
                    buffer[j] = '\0';
                    j = 0;
                    printf("\"%s\" ", buffer);
                    fgetc(fichier);
                }
            } else {
                buffer[j] = '\0';
                j = 0;
                printf("\"%s\"\n", buffer);
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
                    printf("\"%s\" ", buffer);
                    fgetc(fichier);
                }
            } else {
                buffer[j] = '\0';
                j = 0;
                printf("\"%s\"\n", buffer);
                i++;
            }
        }

        i = 0;
        c = fgetc(fichier);
        q = atoi(&c); // nombre d'arrêtes
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
                    printf("\"%s\" ", buffer);
                    fgetc(fichier);
                    fgetc(fichier);
                    fgetc(fichier);
                }
            } else {
                buffer[j] = '\0';
                j = 0;
                printf("\"%s\"\n", buffer);
                i++;
            }
        }
            /*i = 0;
            c = fgetc(fichier);
            q = atoi(&c); // nombre de questions
            while (i < q) {
                i++;
            }*/

        /*if (TYPE_STRUCT != 'm') { // Matrice

            printf("Matrice d'adjacence :\n");
            iniSommet(s, n);
            PPG(M, s, n);
            triDecroissant(s, n);
            PPGD(M, s, n);
            iniSommet(s, n);
            printCFC(s, n);

        } else { // Liste

            printf("\nListe d'adjacence :\n");
            iniSommet(s, n);
            PPG(l, s, n);
            triDecroissant(s, n);
            PPGD(ld, s, n);
            iniSommet(s, n);
            printCFC(s, n);

        }*/

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
