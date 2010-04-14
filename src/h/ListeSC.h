/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : ListeSC.h
OBJET            : Representation de la liste des voisins
--------------------------------------------------------------------------------
DATE DE CREATION : 12/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#ifndef LISTESC_H_INCLUDED
#define LISTESC_H_INCLUDED

#include "node.h"

/*Redefinition du type Node* */
typedef Node* p_Node;

class ListeSC{

  public :

  /*Methodes */
  ListeSC();
  ~ListeSC();
  bool isEmpty();
  int length();
  p_Node first();

  p_Node getNext(p_Node c);

  void addAfter(p_Node c, int v);
  void addBefore(p_Node c, int v);
  void addFirst(p_Node c, int v);
  void addLast(p_Node c, int v);

  /*Accesseurs*/
  void setHead(p_Node c);
  p_Node getHead();
  void SetNbElem(int n);
  int getNbElem();

  private :

  /*Methodes privées permettant de modifier le contenu de la liste*/
  /*Ces methodes sont privées car on n'en a besoin uniquement pour les methodes de la classe ListeSC*/
  void setNext(p_Node c, p_Node next);
  void setPrev(p_Node c, p_Node prev);

  /*Attributs*/
  p_Node m_head;
  int m_nbElem;

};


#endif
