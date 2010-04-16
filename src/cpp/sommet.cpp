/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : sommet.cpp
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

void printS (sommet* s, int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("s%d.nom = %s, s%d.id = %d, s%d.freq = %d\n", i, s[i].nom, i, s[i].id, i, s[i].freq);
    }
}

void printCFC (sommet* s, int n) {
    int d, f, i = 0;
    printf("Les composantes fortement connexes du graphe sont :\n{%d", s[i].id);
    d = s[i].deb;
    f = s[i].fin;
    while (i < n-1) {
        if ((d < (s[i+1].deb)) && (f > (s[i+1].fin))) {
            printf(", %d", s[i+1].id);
            i++;
        } else {
            i++;
            d = s[i].deb;
            f = s[i].fin;
            if (i < n)
                printf("}, {%d", s[i].id);
        }
    }
    printf("}.\n");
}

sommet* iniSommet (int n) { // // Initialise les valeurs de la structure sommet
    int i;
    sommet* s = (sommet*) malloc(n*sizeof(sommet));
}

void triDecroissant (sommet* s, int n) { // Renvoie l'ordre de parcours de la matrice duale (trié par ordre décroissant des temps d'accès finaux)
    int i, tmp = 0, continuer = 1;
    while (continuer) {
        continuer--;
        for (i = 0; i < n-1; i++) {
            if (s[i].fin < s[i+1].fin) {
                tmp = s[i+1].fin;
                s[i+1].fin = s[i].fin;
                s[i].fin = tmp;

                tmp = s[i+1].deb;
                s[i+1].deb = s[i].deb;
                s[i].deb = tmp;

                tmp = s[i+1].num;
                s[i+1].num = s[i].num;
                s[i].num = tmp;
                continuer++;
            }
        }
    }
}

int getIndice (sommet* s, int n, int x) { // Renvoie l'indice du tableau correspondant a l'id x
    int i;
    for (i = 0; i < n; i++) {
        if (s[i].id == x) {
            return i;
        }
    }
    return 0;
}
