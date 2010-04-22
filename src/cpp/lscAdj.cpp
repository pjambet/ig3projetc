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
    iniEtatSommet(s, n);
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

void algoDijkstra (liste* l, sommet* d, int n, int x) { // Calcule les plus courts chemins à partir de x
    int i, z;
    iniEtatSommet(d, n); // F = X
    for (i = 0; i < n; i++) { // Source Unique Initialisation
        d[i].deb = INT_MAX;
        d[i].fin = -1;
    }
    x = getIndice(d, n, x);
    z = x;
    d[x].deb = 0;
    while (nonExplore(d, n)) { // F != null
        x = getIndiceMinDeb(d, n); // x = ExtraireMin(F)
        d[x].etat = 0; // F = F - x
        liste temp = l[x];
        while (temp != NULL) {
            if (d[temp->val].deb > d[x].deb + d[temp->val].freq) { // Relacher
                //printf("relacher(%d, %d) : %d > %d + %d => d(%d) = %d\n", d[x].id, d[y].id, d[y].deb, d[x].deb, d[y].freq, d[y].id, d[x].deb+d[y].freq);
                d[temp->val].deb = d[x].deb + d[temp->val].freq;
                x = getIndice(d, n, d[x].id);
                d[temp->val].fin = x;
            }
            temp = temp->suiv;
        }
    }
}
