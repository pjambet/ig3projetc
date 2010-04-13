/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : matAdj.h
OBJET            : matrice d'adjacence
--------------------------------------------------------------------------------
DATE DE CREATION : 12/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#ifndef MATADJ_H_INCLUDED
#define MATADJ_H_INCLUDED
#include "../h/sommet.h"

void matAdjCFC (char* a); // Renvoie les composantes fortement connexes du graphe
void printMat (int** M); // Affiche la matrice adjacente
void PPG (int** M, sommet* s); // Parcours en profondeur du graphe (appel sur PProfG)
void PProfG (int** M, sommet*, int i, int* t); // Parcours en profondeur du graphe (recursif)
void PPGD (int** M, sommet* s); // Parcours en profondeur du graphe dual (appel sur PProfGD)
void PProfGD (int** M, sommet* s, int i, int* t); // Parcours en profondeur du graphe dual (recursif)

#endif // MATADJ_H_INCLUDED
