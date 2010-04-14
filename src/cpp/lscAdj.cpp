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

void lscAdjCFC (char* a) { // Renvoie les composantes fortement connexes du graphe
    int i = 0, j = 0, k;
    liste* l = (liste*) malloc(TAILLE_MAT*sizeof(liste));
    for (k = 0; k < TAILLE_MAT; k++) {
        l[k] = NULL;
    }
    sommet* s = (sommet*) malloc(TAILLE_MAT*sizeof(int));
    char c;
    FILE* fichier;
    fichier = fopen(a, "r");
    if (fichier != NULL) {
        while (!feof(fichier)) {
            c = fgetc(fichier);
            if (i == TAILLE_MAT) {
                j++;
                i = 0;
            } else {
                if (atoi(&c)) { // Ajout à la fin de l[j] de i
                    liste p = (liste) malloc(sizeof(cell));
                    p->val = i;
                    p->suiv = NULL;
                    if (l[j] == NULL) {
                        l[j] = p;
                    } else {
                        liste temp = l[j];
                        while (temp->suiv != NULL) {
                            temp = temp->suiv;
                        }
                        temp->suiv = p;
                    }
                }
                i++;
            }
        }
        fclose(fichier);
        iniSommet(s);
        printListeAdj(l);
        PPG(l, s);
        printf("lala");
        triDecroissant(s);
        PPGD(l, s);
        iniSommet(s);
        printCFC(s);

    } else {
        printf("Lecture du fichier impossible\n");
    }
}

void printListeAdj (liste* l) {
    int i;
    for (i = 0; i < TAILLE_MAT; i++) {
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

void PPG (liste* l, sommet* s) { // Parcours en profondeur du graphe (appel sur PProfG)
    int i;
    int temps = 0;
    int* t = &temps;
    for (i = 0; i < TAILLE_MAT; i++) {
        s[i].etat = -1; // Etat non atteint
        s[i].deb = 0;
        s[i].fin = 0;
    }
    for (i = 0; i < TAILLE_MAT; i++) {
        if (s[s[i].num].etat == -1) {
            PProfG(l, s, s[i].num, t);
        }
    }
}

void PProfG (liste* l, sommet* s, int i, int* t) { // Parcours en profondeur du graphe (recursif)
    s[i].etat = 0; // Etat atteint
    (*t)++;
    s[i].deb = *t;
    printf("deb s(%d) = %d / xxx\n", i+1, s[i].deb);
    liste temp = l[i];
    while (temp != NULL) {
        if (s[temp->val].etat == -1) {
            PProfG(l, s, temp->val, t);
        }
        temp = temp->suiv;
    }
    s[i].etat = 1; // Etat explore
    (*t)++;
    s[i].fin = *t;
    printf("fin s(%d) = %d / %d\n", i+1, s[i].deb, s[i].fin);
}

void PPGD (liste* l, sommet* s) { // Parcours en profondeur du graphe dual (appel sur PProfGD)
    int i;
    int temps = 0;
    int* t = &temps;
    for (i = 0; i < TAILLE_MAT; i++) {
        s[i].etat = -1; // Etat non atteint
        s[i].deb = 0;
        s[i].fin = 0;
    }
    for (i = 0; i < TAILLE_MAT; i++) {
        if (s[s[i].num].etat == -1) {
            PProfGD(l, s, s[i].num, t);
        }
    }
}
void PProfGD (liste* l, sommet* s, int i, int* t) { // Parcours en profondeur du graphe dual (recursif)
    s[i].etat = 0; // Etat atteint
    (*t)++;
    s[i].deb = *t;
    s[i].etat = 1; // Etat explore
    (*t)++;
    s[i].fin = *t;
}
