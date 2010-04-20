/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : Person.cpp
OBJET            : Classe pour les donnees d'une personne (Nom, Id, Frequence, Liste d'amis)
--------------------------------------------------------------------------------
DATE DE CREATION : 19/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

/*=================================
Includes
===================================*/
#include "../h/Person.h"

/*=================================*/


/*=================================
Constructeurs et Desctructeurs
===================================*/
Person::Person(){
  id_number = 0;
  frequency = 0;
  listLink.resize(0);
  listDualLink.resize(0);
}

Person::Person(string n, int i, int f){
  name = n;
  id_number = i;
  frequency = f;
  listLink.resize(0);
  listDualLink.resize(0);
}

Person::~Person() {
}

/*=================================*/


/*=================================
Accesseurs en ecriture
===================================*/
void Person::set_name(string n) {
  name = n;
}

void Person::set_id(int i) {
  id_number = i;
}

void Person::set_freq(int f) {
  frequency = f;
}

void Person::addFriend(int i) {
  listLink.push_back(i);
}

void Person::addDualFriend(int i) {
  listDualLink.push_back(i);
}

/*=================================*/


/*=================================
Accesseurs en lecture
===================================*/
string Person::get_name() {
  return name;
}

int Person::get_id() {
  return id_number;
}

int Person::get_freq() {
  return frequency;
}

vector <int> Person::get_listLink() {
  return listLink;
}

vector <int> Person::get_listDualLink() {
  return listDualLink;
}

/*=================================*/


/*=================================
Autres et optionnels
===================================*/
void Person::sortFriends() {
  sort(listLink.begin(), listLink.end());
  sort(listDualLink.begin(), listDualLink.end());
}

void Person::display() {
  cout << name << " " << id_number << " " << frequency << endl;
  cout << "   Friends : [ ";
  for (int i = 0; i < listLink.size(); i++) {
    cout << listLink[i] << " ";
  }
  cout << "]" << endl;

  cout << "   Dual Friends : [ ";
  for (int i = 0; i < listDualLink.size(); i++) {
    cout << listDualLink[i] << " ";
  }
  cout << "]" << endl;

  cout << endl;
}

/*=================================*/
