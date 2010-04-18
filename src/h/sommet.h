/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : lscAdj.cpp
OBJET            : liste simplement chaînée d'adjacence
--------------------------------------------------------------------------------
DATE DE CREATION : 13/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

typedef struct sommet sommet;
struct sommet {
    int etat; // -1 = Non atteint, 0 = Atteint, 1 = Exploré
    int deb;
    int fin;
    int num;
    char nom[32];
    int id;
    int freq;
};

void printS (sommet* s, int n); // Affiche les informations des sommets
void printCFC (sommet* s, int n); // Affiche les CFC
sommet* iniSommet (int n); // Initialise les valeurs de la structure sommet
void iniEtatSommet (sommet* s, int n); // Initialise les etats des sommets
void triDecroissant (sommet* s, int n); // Renvoie l'ordre de parcours de la matrice duale (trié par ordre décroissant des temps d'accès finaux)
int getIndice (sommet* s, int n, int x); // Renvoie l'indice du tableau correspondant a l'id x
int getNbCFC (sommet* s, int n); // Renvoie le nombre de composantes fortement connexes
char* getCFC (sommet* s, int n); // Renvoie les CFC

#endif // SOMMET_H_INCLUDED
