/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : ListeSC.h
OBJET            : Representation de la liste des voisins
--------------------------------------------------------------------------------
DATE DE CREATION : 12/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#ifndef DEF_LISTESC
#define DEF_LISTESC

#include "node.h"

class ListeSC{

  public :

  typedef Node* Cell;

  ListeSC();
  ~ListeSC();
  bool isEmpty();
  int length();
  Cell first();

  Cell getNext(Cell c);
  Cell getPrev(Cell c);

  void addAfter(Cell c, int v);
  void addBefore(Cell c, int v);
  void addFirst(Cell c, int v);
  void addLast(Cell c, int v);

  private :

  void setNext(Cell c, Cell next);
  void setPrev(Cell c, Cell prev);

  Cell head;
  int nbElem;

};


#endif
