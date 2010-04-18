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

int** iniMat (int n); // Renvoie la matrice d'adjacence
void printMat (int** M, int n); // Affiche la matrice adjacente
void PPG (int** M, sommet* s, int n); // Parcours en profondeur du graphe (appel sur PProfG)
void PProfG (int** M, sommet*, int n, int i, int* t); // Parcours en profondeur du graphe (recursif)
void PPGD (int** M, sommet* s, int n); // Parcours en profondeur du graphe dual (appel sur PProfGD)
void PProfGD (int** M, sommet* s, int n, int i, int* t); // Parcours en profondeur du graphe dual (recursif)
int getTMin (int** M, sommet* s, int n, int x, int y); // Renvoie le temps min pour aller de x à y
void getTMinProf (int** M, sommet* s, int n, int x, int y, int* t, int temp); // Parcours en profondeur
void algoDijkstra (int** M, sommet*s, int n, int x); // Calcule les plus courts chemins à partir de x

#endif // MATADJ_H_INCLUDED
