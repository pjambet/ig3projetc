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
#include <limits.h>
#include "../h/sommet.h"

void printS (sommet* s, int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("sommet %d :\n  nom = %s, freq = %d, d(%d), f(%d)\n", s[i].id, s[i].nom, s[i].freq, s[i].deb, s[i].fin);
    }
}

void printCFC (sommet* s, int n) {
    int d = s[0].deb, f = s[0].fin, i;
    printf("Les composantes fortement connexes du graphe sont :\n{%d", s[0].id);
    for (i = 0; i < n-1; i++) {
        if ((d < (s[i+1].deb)) && (f > (s[i+1].fin))) {
            printf(", %d", s[i+1].id);
        } else {
            d = s[i+1].deb;
            f = s[i+1].fin;
            if (i+1 < n)
                printf("}, {%d", s[i+1].id);
        }
    }
    printf("}.\n");
}

sommet* iniSommet (int n) { // // Initialise les valeurs de la structure sommet
    sommet* s;
    s = (sommet*) malloc(n*sizeof(sommet));
    return s;
}

void iniEtatSommet (sommet* s, int n) { // Initialise les etats des sommets
    int i;
    for (i = 0; i < n; i++) {
        s[i].etat = -1; // Etat non atteint
        s[i].deb = 0;
        s[i].fin = 0;
    }
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

int getIndiceMinDeb (sommet* s, int n) { // Renvoie l'indice du plus petit d(x)
    int i, imin, min = INT_MAX;
    for (i = 0; i < n; i++) {
        if ((s[i].deb < min) && (s[i].etat == -1)) {
            min = s[i].deb;
            imin = i;
        }
    }
    if (imin != INT_MAX)
        return imin;
    else
        return 0;
}

int getNbCFC (sommet* s, int n) { // Renvoie le nombre de composantes fortement connexes
    int d = s[0].deb, f = s[0].fin, i, r = 1;
    for (i = 0; i < n-1; i++) {
        if (!((d < (s[i+1].deb)) && (f > (s[i+1].fin)))) {
            r++;
            d = s[i+1].deb;
            f = s[i+1].fin;
        }
    }
    return r;
}

char* getCFC (sommet* s, int n) { // Renvoie les CFC
    int d = s[0].deb, f = s[0].fin, i;
    char* buffer = (char*) malloc(5*n*sizeof(char));
    char* cfc = (char*) malloc(5*n*sizeof(char));
    sprintf(buffer, "%d", s[0].id);
    strcpy(cfc, buffer);
    for (i = 0; i < n-1; i++) {
        if ((d < (s[i+1].deb)) && (f > (s[i+1].fin))) {
            sprintf(buffer, "%d", s[i+1].id);
            strcat(cfc, ", ");
            strcat(cfc, buffer);
        } else {
            d = s[i+1].deb;
            f = s[i+1].fin;
            if (i+1 < n) {
                sprintf(buffer, "%d", s[i+1].id);
                strcat(cfc, "\n");
                strcat(cfc, buffer);
            }
        }
    }
    return cfc;
}

int nonExplore (sommet* s, int n) { // Renvoie vrai s'il reste un sommet non exploré
    int i;
    for (i = 0; i < n; i++) {
        if ((s[i].etat == -1) && (s[i].deb != INT_MAX))
            return 1;
    }
    return 0;
}

char* getCheminMin (sommet* d, int n, int y) {
    int i;
    char* buffer = (char*) malloc(5*n*sizeof(char));
    char* buffer2 = (char*) malloc(5*n*sizeof(char));
    char* chemin = (char*) malloc(5*n*sizeof(char));
    sprintf(buffer, "%d :", d[y].deb);
    strcpy(chemin, buffer);
    while (y != -1) {
        sprintf(buffer, ",%d ", d[y].id);
        strcat(buffer2, buffer);
        y = d[y].fin;
    }
    for (i = 0; i < strlen(buffer2)-1; i++) {
        buffer[i] = buffer2[strlen(buffer2)-i-1];
    }
    strcat(chemin, buffer);
    strcat(chemin, "\n");
    return chemin;
}
