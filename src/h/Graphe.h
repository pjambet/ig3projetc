/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : Graphe.h
OBJET            : Structure de graphe
--------------------------------------------------------------------------------
DATE DE CREATION : 27/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

/*=================================
Includes
===================================*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <numeric>

#include "UserData.h"
#include "sommet.h"
#include "ListeVoisins.h"
#include "matAdj.h"



class Graphe{
  /* Attributs */
  private:
  int nbCFC; /* Nombre de CFC */
  vector < vector <int> > listCFC;
    /* Vecteur de CFC
       Chaque CFC est represente par un vecteur d'id (entier) */

  int nbDist; /* Nombre de distance a determiner */
  multimap < int, vector < int > > listDist;
  /* Structure de stockage des questions
     L'entier en cle represente le point de depart
     Le vecteur d'entier represente le chemin jusqu'a l'avant dernier element du vecteur
     Le dernier element represente la distance
     */


  public:
  /* Methodes */

    /* Constructeurs et Desctructeurs */
    Graphe();
    ~Graphe();


    /* Resolution */
    void resolution(UserData* u);

    /* Autres et optionnels */
    void loadCFC(vector<s_sommet>* tabSommet);
      /* Cherche et stocke les listes des CFC a partir de tabSommet*/
    void saveGraphe(string fileName);
      /* Sauvegarde les resultats dans un fichier */


    /* Autres */
    void print();
      /* Procedure d'affichage */
    void clear();
      /* Remise a zero du graphe */
};

#endif // GRAPHE_H_INCLUDED
