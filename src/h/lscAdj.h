/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : lscAdj.h
OBJET            : liste simplement chaînée d'adjacence
--------------------------------------------------------------------------------
DATE DE CREATION : 13/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#ifndef LSCADJ_H_INCLUDED
#define LSCADJ_H_INCLUDED
#include "../h/sommet.h"

typedef struct cell cell;
struct cell {
    struct cell* suiv;
    int val;
};

typedef cell* LSC;

void lscAdjCFC (char* a); // Renvoie les composantes fortement connexes du graphe
void printLSC (int** M); // Affiche la liste adjacente
void PPG (int* M, sommet* s); // Parcours en profondeur du graphe (appel sur PProfG)
void PProfG (int* M, sommet*, int i, int* t); // Parcours en profondeur du graphe (recursif)
void PPGD (int* M, sommet* s); // Parcours en profondeur du graphe dual (appel sur PProfGD)
void PProfGD (int* M, sommet* s, int i, int* t); // Parcours en profondeur du graphe dual (recursif)

#endif // LSCADJ_H_INCLUDED
