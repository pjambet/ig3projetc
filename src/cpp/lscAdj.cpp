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
#include <iostream>
#include "../h/sommet.h"
#include "../h/lscAdj.h"

using namespace std;

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

void DepthFirstSearch (liste* l, sommet* s, int n) { // Parcours en profondeur du graphe
    int i, child = 0, temps = 0;
    int* t = &temps;
    if (s[0].etat == -1) { // Premier DFS
        for (i = 0; i < n; i++) {
            if (s[s[i].num].etat == -1) {
                DepthFirstSearchVisit(l, s, n, s[i].num, t);
            }
        }
        for (i = 1; i < n; i++) { // root check
            if (s[i].parent == 0) {
                child++;
            }
        }
        if (child > 1) {
            s[0].important = 1;
        }
        triDecroissant(s, n);
    } else { // Second DFS avec L transposé
        iniEtatSommet(s, n);
        for (i = 0; i < n; i++) {
            if (s[s[i].num].etat == -1) {
                DepthFirstSearchVisit(l, s, n, s[i].num, t);
            }
        }
    }
}

void PProfG (liste* l, sommet* s, int i, int* t, int n) { // Parcours en profondeur du graphe (recursif)
    s[i].etat = 0; // Etat atteint
    (*t)++;
    s[i].deb = *t;


    s[i].etat = 1; // Etat explore
    (*t)++;
    s[i].fin = *t;
}

void DepthFirstSearchVisit (liste* l, sommet* s, int n, int i, int* t) { // Parcours en profondeur du graphe (récursif)
    int j;
    s[i].etat = 0; // Etat atteint
    (*t)++;
    s[i].deb = *t;
    s[i].low = *t;
    liste temp = l[i];
    while (temp != NULL) { // Successeur
        j = temp->val;
        if (s[j].etat == -1) { // forward edge
            s[j].parent = i;
            DepthFirstSearchVisit(l, s, n, j, t);
            if (s[j].low >= s[i].deb && i != 0) {
                s[i].important = 1;
            }
            if (s[j].low < s[i].low) {
                s[i].low = s[j].low;
            }
        } else if (s[i].parent != j) { // back edge
            if (s[j].deb < s[i].low) {
                s[i].low = s[j].deb;
            }
        }
        temp = temp->suiv;
    }
    (*t)++;
    s[i].fin = *t;
}

void ShortestPath (liste* l, sommet* s, int n, int x) { // Algorithme de Dijkstra : calcule les plus courts chemins à partir de x
    int i, y, z;
    iniEtatSommet(s, n); // F = X
    for (i = 0; i < n; i++) { // Source Unique Initialisation
        s[i].deb = INT_MAX;
        s[i].fin = -1;
    }
    x = getIndice(s, n, x);
    z = x;
    s[x].deb = 0;
    liste temp = l[x];
    while (nonExplore(s, n)) { // F != null
        x = getIndiceMinDeb(s, n); // x = ExtraireMin(F)
        s[x].etat = 0; // F = F - x
        while (temp != NULL) { // Successeur
            y = temp->val;
            if (s[y].deb > s[x].deb + s[y].freq) { // Relacher
                s[y].deb = s[x].deb + s[y].freq;
                x = getIndice(s, n, s[x].id);
                s[y].fin = x;
            }
            temp = temp->suiv;
        }
    }
}
