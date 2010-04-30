/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : generate_mat.h
OBJET            : matrice adjacente
--------------------------------------------------------------------------------
DATE DE CREATION : 13/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#ifndef GENERATE_MAT_H_INCLUDED
#define GENERATE_MAT_H_INCLUDED

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

void generate_matrix(int x);
/*
Genere une matrice carre x*x de 0 et de 1
La stocke ensuite dans un fichier
*/

int number_nodes(char* fileName);
/* va renvoyer le nombre colonne, et donc le nombre de ligne du fichier soit le nombre de noeud du graphe */

#endif // GENERATE_MAT_H_INCLUDED
