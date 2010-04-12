/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : matAdj.h
OBJET            : matrice adjacente
--------------------------------------------------------------------------------
DATE DE CREATION : 12/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#ifndef MATADJ_H_INCLUDED
#define MATADJ_H_INCLUDED
#define tailleMat 8

typedef struct sommet sommet;

struct sommet {
    int etat; // -1 = Non atteint, 0 = Atteint, 1 = Exploré
    int num;
    int deb;
    int fin;
};

void matAdjCFC (char* a); // Renvoie les composantes fortement connexes du graphe
void printMat (int** M); // Affiche la matrice adjacente
void iniSommet (sommet* s); // Initialise les valeurs de la structure sommet
void PP (int** M, sommet* s, int mode); // Parcours en profondeur
void PProfG (int** M, int i, sommet* s); // Parcours en profondeur du graphe
void PProfGD (int** M, int i, sommet* s); // Parcours en profondeur du graphe dual
void triDecroissant (sommet* s); // Renvoie l'ordre de parcours de la matrice duale (trié par ordre décroissant des temps d'accès finaux)

#endif // MATADJ_H_INCLUDED
