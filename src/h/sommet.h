/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : lscAdj.cpp
OBJET            : liste simplement chaînée d'adjacence
--------------------------------------------------------------------------------
DATE DE CREATION : 13/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
#define TAILLE_MAT 8

typedef struct sommet sommet;
struct sommet {
    int etat; // -1 = Non atteint, 0 = Atteint, 1 = Exploré
    int num;
    int deb;
    int fin;
};

void printCFC (sommet* s); // Affiche les CFC
void iniSommet (sommet* s); // Initialise les valeurs de la structure sommet
void triDecroissant (sommet* s); // Renvoie l'ordre de parcours de la matrice duale (trié par ordre décroissant des temps d'accès finaux)

#endif // SOMMET_H_INCLUDED
