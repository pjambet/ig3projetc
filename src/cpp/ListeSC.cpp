/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : ListeSC.cpp
OBJET            : liste simplement chainée
--------------------------------------------------------------------------------
DATE DE CREATION : 12/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#include "assert.h"

#include "../h/ListeSC.h"

ListeSC::ListeSC() : m_head(NULL), m_nbElem(0){

}

ListeSC::~ListeSC(){

}

bool ListeSC::isEmpty(){
  return (m_head == NULL);
}

int ListeSC::length(){
  return m_nbElem;
}

p_Node ListeSC::first(){
  return m_head;
}

p_Node ListeSC::getNext(p_Node c){
  return c->getNext();
}

void ListeSC::addAfter(p_Node c, int v){

}

void ListeSC::addBefore(p_Node c, int v){

}

void ListeSC::addFirst(p_Node c, int v){

}

void ListeSC::addLast(p_Node c, int v){

}

void ListeSC::setHead(p_Node c){
  m_head = c;
}

p_Node ListeSC::getHead(){
  return m_head;
}

void ListeSC::SetNbElem(int n){
  m_nbElem = n;
}

int ListeSC::getNbElem(){
  return m_nbElem;
}
