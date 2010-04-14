/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : node.h
OBJET            : noeud de la liste
--------------------------------------------------------------------------------
DATE DE CREATION : 13/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include <iostream>

class Node{

  public :

  Node();
  ~Node();

  /*ACCESSEURS*/
  Node* getNext();
  void setNext(Node* n);
  int getVal();
  void setVal(int v);

  private :

  int m_val;
  Node* m_next;


};

#endif
