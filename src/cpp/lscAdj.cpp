/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : lscAdj.cpp
OBJET            : liste simplement chaînée d'adjacence
--------------------------------------------------------------------------------
DATE DE CREATION : 13/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../h/sommet.h"
#include "../h/lscAdj.h"

void lscAdjCFC (char* a, int n) { // Renvoie les composantes fortement connexes du graphe
    int i = 0, j = 0, k;
    liste* l = (liste*) malloc(n*sizeof(liste));
    for (k = 0; k < n; k++) {
        l[k] = NULL;
    }
    liste* ld = (liste*) malloc(n*sizeof(liste));
    for (k = 0; k < n; k++) {
        ld[k] = NULL;
    }
    sommet* s = (sommet*) malloc(n*sizeof(sommet));
    char c;
    FILE* fichier;
    fichier = fopen(a, "r");
    if (fichier != NULL) {
        while (!feof(fichier)) {
            c = fgetc(fichier);
            if (i == n) {
                j++;
                i = 0;
            } else {
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
                i++;
            }
        }
        fclose(fichier);

        //printListeAdj(l);
        iniSommet(s, n);
        PPG(l, s, n);
        triDecroissant(s, n);
        PPGD(ld, s, n);
        iniSommet(s, n);
        printCFC(s, n);

    } else {
        printf("Lecture du fichier impossible\n");
    }
}

void printListeAdj (liste* l, int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d ", i+1);
        liste temp = l[i];
        while (temp != NULL) {
            printf("-> %d ", (temp->val)+1);
            temp = temp->suiv;
        }
        printf("\n");
    }
    printf("\n");
}

void PPG (liste* l, sommet* s, int n) { // Parcours en profondeur du graphe (appel sur PProfG)
    int i;
    int temps = 0;
    int* t = &temps;
    for (i = 0; i < n; i++) {
        s[i].etat = -1; // Etat non atteint
        s[i].deb = 0;
        s[i].fin = 0;
    }
    for (i = 0; i < n; i++) {
        if (s[s[i].num].etat == -1) {
            PProfG(l, s, s[i].num, t, n);
        }
    }
}

void PProfG (liste* l, sommet* s, int i, int* t, int n) { // Parcours en profondeur du graphe (recursif)
    s[i].etat = 0; // Etat atteint
    (*t)++;
    s[i].deb = *t;
    liste temp = l[i];
    while (temp != NULL) {
        if (s[temp->val].etat == -1) {
            PProfG(l, s, temp->val, t, n);
        }
        temp = temp->suiv;
    }
    s[i].etat = 1; // Etat explore
    (*t)++;
    s[i].fin = *t;
}

void PPGD (liste* l, sommet* s, int n) { // Parcours en profondeur du graphe dual (appel sur PProfGD)
    int i;
    int temps = 0;
    int* t = &temps;
    for (i = 0; i < n; i++) {
        s[i].etat = -1; // Etat non atteint
        s[i].deb = 0;
        s[i].fin = 0;
    }
    for (i = 0; i < n; i++) {
        if (s[s[i].num].etat == -1) {
            PProfGD(l, s, s[i].num, t, n);
        }
    }
}
void PProfGD (liste* l, sommet* s, int i, int* t, int n) { // Parcours en profondeur du graphe dual (recursif)
    s[i].etat = 0; // Etat atteint
    (*t)++;
    s[i].deb = *t;
    liste temp = l[i];
    while (temp != NULL) {
        if (s[temp->val].etat == -1) {
            PProfG(l, s, temp->val, t, n);
        }
        temp = temp->suiv;
    }
    s[i].etat = 1; // Etat explore
    (*t)++;
    s[i].fin = *t;
}
