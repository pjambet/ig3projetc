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

void printCFC (sommet* s) {
    int d, f, i = 0;
    printf("Les composantes fortement connexes du graphe sont :\n{%d", (s[i].num)+1);
    d = s[i].deb;
    f = s[i].fin;
    while (i < TAILLE_MAT) {
        if ((d < (s[i+1].deb)) && (f > (s[i+1].fin))) {
            printf(", %d", (s[i+1].num)+1);
            i++;
        } else {
            i++;
            d = s[i].deb;
            f = s[i].fin;
            if (i < TAILLE_MAT)
                printf("}, {%d", (s[i].num)+1);
            else
                printf("}.");
        }
    }
    printf("\n");
}

void iniSommet (sommet* s) { // // Initialise les valeurs de la structure sommet
    int i;
    for (i = 0; i < TAILLE_MAT; i++) {
        s[i].num = i;
    }
}

void triDecroissant (sommet* s) { // Renvoie l'ordre de parcours de la matrice duale (trié par ordre décroissant des temps d'accès finaux)
    int i, tmp = 0, continuer = 1;
    while (continuer) {
        continuer--;
        for (i = 0; i < TAILLE_MAT-1; i++) {
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
