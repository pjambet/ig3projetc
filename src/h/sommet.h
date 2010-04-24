/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : lscAdj.cpp
OBJET            : liste simplement cha�n�e d'adjacence
--------------------------------------------------------------------------------
DATE DE CREATION : 13/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#include <iostream>
#include <string>
#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

typedef struct sommet sommet;
struct sommet {
    int etat; // -1 = Non atteint, 0 = Atteint, 1 = Explor�
    int deb;
    int fin;
    int low;
    int parent;
    int num; // position
    char nom[32];
    int id;
    int freq;
    int important;
};

void printS (sommet* s, int n); // Affiche les informations des sommets
void printCFC (sommet* s, int n); // Affiche les CFC
sommet* iniSommet (int n); // Initialise les valeurs de la structure sommet
void iniEtatSommet (sommet* s, int n); // Initialise les etats des sommets
void triDecroissant (sommet* s, int n); // Renvoie l'ordre de parcours de la matrice duale (tri� par ordre d�croissant des temps d'acc�s finaux)
int getIndice (sommet* s, int n, int x); // Renvoie l'indice du tableau correspondant a l'id x
int getIndiceMinDeb (sommet* s, int n); // Renvoie l'indice du plus petit d(x)
int getNbCFC (sommet* s, int n); // Renvoie le nombre de composantes fortement connexes
char* getCFC (sommet* s, int n); // Renvoie les CFC
int nonExplore (sommet* s, int n); // Renvoie vrai s'il reste un sommet non explor�
char* getCheminMin (sommet* d, int n, int y); // Renvoie le temps et le plus cours chemin jusqu'� y

#endif // SOMMET_H_INCLUDED
