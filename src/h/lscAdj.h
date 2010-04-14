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
    int val;
    struct cell* suiv;
};

typedef cell* liste;

void lscAdjCFC (char* a); // Renvoie les composantes fortement connexes du graphe
void printListeAdj (liste* l); // Affiche la liste adjacente
void PPG (liste* l, sommet* s); // Parcours en profondeur du graphe (appel sur PProfG)
void PProfG (liste* l, sommet* s, int i, int* t); // Parcours en profondeur du graphe (recursif)
void PPGD (liste* l, sommet* s); // Parcours en profondeur du graphe dual (appel sur PProfGD)
void PProfGD (liste* l, sommet* s, int i, int* t); // Parcours en profondeur du graphe dual (recursif)

#endif // LSCADJ_H_INCLUDED
