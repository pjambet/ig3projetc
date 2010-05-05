/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : Summit.h
OBJET            : Structure de sommet
--------------------------------------------------------------------------------
DATE DE CREATION : 30/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
/*=================================
Includes
===================================*/
#include <iostream>
#include <string>

using namespace std;


typedef struct struct_summit {
  /* Structure de representation d'un sommet
     Il contient :
     - les donnees d'une personne (nom, id, frequence)
     - les donnees du graphe */

    string name;         /* Nom */
    string id;              /* ID */
    int freq;            /* Frequence */


    int status;          /* -1 = Non atteint, 0 = Atteint, 1 = Exploré*/

    int beg;             /* Indice de debut d'exploration */
    int end;             /* Indice de fin d'exploration */
    int num;             /* Numero repere */

    bool important;      /* Importance de la personne dans la composante */

} s_summit;

void printSummit (s_summit s);         /* Affiche le sommet s */
bool orderBeg(s_summit a, s_summit b); /* Ordre sur la structure par rapport a beg */
bool orderEnd(s_summit a, s_summit b); /* Ordre sur la structure par rapport a beg */


#endif // SOMMET_H_INCLUDED
