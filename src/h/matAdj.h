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

void printMat (int** M); // Affiche la matrice adjacente
int** copieMat (int** M); // Renvoie la copie de la matrice M
int** matDuale (int** M); // Renvoie la matrice duale de M
void PProf (int** M, int i, sommet* s); // Parcours en profondeur
void PP (int** M, sommet* s); // Parcours en profondeur
void triDecroissant (sommet* s); // Renvoie l'ordre de parcours de la matrice duale (trié par ordre décroissant des temps d'accès finaux)
void CFC (sommet* s); // Renvoie les composantes fortement connexes du graphe
void printSommet (sommet* s); // Affiche le tableau d'informations des sommets


#endif // MATADJ_H_INCLUDED
