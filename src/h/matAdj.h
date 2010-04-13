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

void matAdjCFC (char* a); // Renvoie les composantes fortement connexes du graphe
void printMat (int** M); // Affiche la matrice adjacente
void printCFC (sommet* s); // Affiche les CFC
void iniSommet (sommet* s); // Initialise les valeurs de la structure sommet
void PPG (int** M, sommet* s); // Parcours en profondeur du graphe (appel sur PProfG)
void PProfG (int** M, sommet*, int i, int* t); // Parcours en profondeur du graphe (recursif)
void PPGD (int** M, sommet* s); // Parcours en profondeur du graphe dual (appel sur PProfGD)
void PProfGD (int** M, sommet* s, int i, int* t); // Parcours en profondeur du graphe dual (recursif)
void triDecroissant (sommet* s); // Renvoie l'ordre de parcours de la matrice duale (trié par ordre décroissant des temps d'accès finaux)

#endif // MATADJ_H_INCLUDED
