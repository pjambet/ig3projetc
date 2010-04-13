/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : node.h
OBJET            : noeud de la liste
--------------------------------------------------------------------------------
DATE DE CREATION : 13/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#ifndef DEF_NODE
#define DEF_NODE
#include <iostream>

class Node{

  private :

  Node();
  ~Node();



  public :

  /*ACCESSEURS*/
  Node* getNext();
  void setNext(Node* n);
  int getVal();
  void setVal(int v);

};

#endif
