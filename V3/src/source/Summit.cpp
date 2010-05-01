/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : Summit.cpp
OBJET            : Structure de sommet
--------------------------------------------------------------------------------
DATE DE CREATION : 30/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#include "../headers/Summit.h"

void printSummit (s_summit s) {
  cout << "Nom : " << s.name << endl;
  cout << "    id( " << s.id << " ) frequence( " << s.freq << " ) " << endl;
  cout << "debut( " << s.beg << " ) fin( " << s.end << " ) numero( " << s.num << " )" << endl;
}

bool orderBeg(s_summit a, s_summit b) {
  return (a.beg < b.beg);
}
