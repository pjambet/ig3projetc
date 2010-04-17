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

liste* iniListe (int n) { // Renvoie la liste d'adjacence
    int i;
    liste* l = (liste*) malloc(n*sizeof(liste));
    for (i = 0; i < n; i++) {
        l[i] = NULL;
    }
    return l;
}

liste* ajoutFin (liste* l, int i, int x) { // Ajoute à la fin de la liste* l la valeur x
    liste t = (liste) malloc(sizeof(cell));
    t->val = x;
    t->suiv = NULL;
    if (l[i] == NULL) {
        l[i] = t;
        return l;
    } else {
        liste temp = l[i];
        while (temp->suiv != NULL) {
            temp = temp->suiv;
        }
        temp->suiv = t;
        return l;
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
    triDecroissant(s, n);
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
