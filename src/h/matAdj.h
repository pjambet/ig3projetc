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
void DepthFirstSearch (int** M, sommet* s, int n); // Parcours en profondeur du graphe
void DepthFirstSearchVisit (int** M, sommet* s, int n, int i, int* t, int numDFS); // Parcours en profondeur du graphe (récursif)
void ShortestPath (int** M, sommet* s, int n, int x); // Algorithme de Dijkstra : calcule les plus courts chemins à partir de x

#endif // MATADJ_H_INCLUDED
