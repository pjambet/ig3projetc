/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : ListeVoisins.cpp
OBJET            : representation de graphes sous forme de liste de voisins
--------------------------------------------------------------------------------
DATE DE CREATION : 13/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#ifndef LISTEVOISINS_H_INCLUDED
#define LISTEVOISINS_H_INCLUDED

#define TAILLE_GRAPH 10

#include "ListeSC.h"

class ListeVoisins{

  private :

  ListeSC graph[TAILLE_GRAPH];

  public:

  ListeVoisins();
  ~ListeVoisins();

};

#endif
