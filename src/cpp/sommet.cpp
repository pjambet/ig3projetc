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
        printf("sommet %d :\n  nom = %s, freq = %d, d(%d), f(%d), l(%d)\n", s[i].id, s[i].nom, s[i].freq, s[i].deb, s[i].fin, s[i].low);
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
    char* buffer = (char*) malloc(6*n*sizeof(char));
    char* cfc = (char*) malloc(6*n*sizeof(char));
    if (s[0].important == 1)
        sprintf(buffer, "*%d", s[0].id);
    else
        sprintf(buffer, "%d", s[0].id);
    strcpy(cfc, buffer);
    for (i = 0; i < n-1; i++) {
        if ((d < (s[i+1].deb)) && (f > (s[i+1].fin))) {
            if (s[i+1].important == 1)
                sprintf(buffer, "*%d", s[i+1].id);
            else
                sprintf(buffer, "%d", s[i+1].id);
            strcat(cfc, ", ");
            strcat(cfc, buffer);
        } else {
            d = s[i+1].deb;
            f = s[i+1].fin;
            if (i+1 < n) {
                if (s[i+1].important == 1)
                    sprintf(buffer, "*%d", s[i+1].id);
                else
                    sprintf(buffer, "%d", s[i+1].id);
                strcat(cfc, "\n");
                strcat(cfc, buffer);
            }
        }
    }
    free(buffer);
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
    int i, j, k, p, l, m;
    char* buffer = (char*) malloc(1000*sizeof(char));
    char* chemin = (char*) malloc(1000*sizeof(char));
    sprintf(chemin, "%d : ", d[y].deb);
    strcpy(buffer, chemin);
    m = strlen(buffer);
    while (y != -1) {
        sprintf(chemin, "%d, ", d[y].id);
        strcat(buffer, chemin);
        y = d[y].fin;
    }
    p = strlen(buffer);
    strcpy(chemin, buffer);
    i = m;
    while (i < p) { // inversion de l'ordre (fonction super bordelique!)
        l = 0;
        while (buffer[i] != ' ') {
            i++;
            l++;
        }
        i = i-l;
        l++;
        k = 0;
        j = p-l-i;
        while (k < l) {
            //printf("Var : (l=%d p=%d i=%d), chemin[%d] = %c\n", l, p, i, j+m, buffer[i]);
            chemin[j+m] = buffer[i];
            i++;
            k++;
            j++;
        }
    }
    chemin[p-2] = '\0'; // on elève la dernière virgule et le dernier espace
    strcat(chemin, "\n");
    free(buffer);
    return chemin;
}
