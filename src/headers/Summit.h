/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : Summit.h
OBJET            : Structure de sommet
--------------------------------------------------------------------------------
DATE DE CREATION : 30/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------
DETAILS          : Ce fichier définit la structure "struct_summit" qui permet
				   de faire toutes les operations sur les graphes : parcours,
				   calcul de CFC ...
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
    /* Attributs */
    string name;
    string id;
    int freq;

    int status;
    int beg;
    int end;
    int num;

    bool important;

    /* EXPLICATIONS DES ATTRIBUTS :

       Structure de representation d'un sommet.
       Les donnees conservees d'une personne sont :
       - name : Le nom d'une personne
       - id : Son identifiant
       - freq : Sa frequence de connexion

       On stocke aussi les donnees necessaires aux calculs :
       - status : L'état du sommet.
                  -1 pour "NON ATTEINT"
                  0 pour "ATTEINT
                  1 pour "EXPLORE"
       - beg : Pour la recherche de CFC, cet attribut represente le temps qu'il a fallu pour "decouvrir" le sommet
               Pour la recherche de distance, il contient la distance minimale vers le point de depart du graphe
       - end : Pour CFC, il s'agit du temps final quand tous ses descendants non explore l'ont ete
               Pour les distances, il contient l'indice du pere a la plus courte distance
       - important : booleen indiquant si le point peut-etre considere comme important ou pas
    */

} s_summit;


/* PROCEDURE : printSummit - Affichage d'un element de type s_summit */
void printSummit (s_summit s);
/* COMPLEXITE : Constant o(1)
   ENTREE : s, un element de type s_summit a afficher
   ALGORITHME :
     Affiche les attributs name, id et freq de l'element s
*/

/* FONCTION : orderBeg - Donne une notion d'ordre entre deux elements de type s_summit, le critere est l'attribut beg */
bool orderBeg(s_summit a, s_summit b);
/* COMPLEXITE : Constant o(1)
   ENTREE : a et b, deux elements de type s_summit a comparer
   ALGORITHME :
     Renvoie le resultat de l'evalutation (a.beg < b.beg)
*/

/* FONCTION : orderEnd - Donne une notion d'ordre entre deux elements de type s_summit, le critere est l'attribut end */
bool orderEnd(s_summit a, s_summit b);
/* COMPLEXITE : Constant o(1)
   ENTREE : a et b, deux elements de type s_summit a comparer
   ALGORITHME :
     Renvoie le resultat de l'evalutation (a.end < b.end)
*/

#endif // SOMMET_H_INCLUDED

