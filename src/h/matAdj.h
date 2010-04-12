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
#define tailleMat 10

typedef struct sommet sommet;

struct sommet {
    int etat; // -1 = Non atteint, 0 = Atteint, 1 = Exploré
    int num;
    int deb;
    int fin;
};

void printMat (int** M); // Affiche la matrice adjacente
void PProfG (int** M, int i, sommet* s); // Parcours en profondeur du graphe
void PProfGD (int** M, int i, sommet* s); // Parcours en profondeur du graphe dual
void PP (int** M, sommet* s, char mode); // Parcours en profondeur
void triDecroissant (sommet* s); // Renvoie l'ordre de parcours de la matrice duale (trié par ordre décroissant des temps d'accès finaux)
void CFC (sommet* s); // Renvoie les composantes fortement connexes du graphe
void printSommet (sommet* s); // Affiche le tableau d'informations des sommets

#endif // MATADJ_H_INCLUDED
