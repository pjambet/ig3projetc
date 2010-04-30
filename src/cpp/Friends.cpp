/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : Friends.h
OBJET            : Classe pour les donnees d'une personne (Nom, Id, Frequence, Liste d'amis)
--------------------------------------------------------------------------------
DATE DE CREATION : 29/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */
#include "../h/Friends.h"


/*=================================
Constructeur et Destructeur
===================================*/
Friends::Friends() {
  listLink.resize(0);
  listDualLink.resize(0);
}

Friends::~Friends() {
}




/*=================================
Accesseur en ecriture
===================================*/
void Friends::addFriend(int i) {
  listLink.push_back(i);
}

void Friends::addDualFriend(int i) {
  listDualLink.push_back(i);
}

void Friends::set_id(int i) {
  id = i;
}


/*=================================
Accesseur en lecture
===================================*/
vector <int> Friends::get_listLink() {
  return listLink;
}

vector <int> Friends::get_listDualLink() {
  return listDualLink;
}


/*=================================
Autres
===================================*/
void Friends::sortFriends() {
  sort(listLink.begin(), listLink.end());
  sort(listDualLink.begin(), listDualLink.end());
}

void Friends::print() {
  int i;

  cout << id << " : " << endl;

  cout << "   Friends : [ ";
  for (i = 0; i < listLink.size(); i++) {
    cout << listLink[i] << " ";
  }
  cout << "]" << endl;

  cout << "   Dual Friends : [ ";
  for (i = 0; i < listDualLink.size(); i++) {
    cout << listDualLink[i] << " ";
  }
  cout << "]" << endl;

  cout << endl;
}
