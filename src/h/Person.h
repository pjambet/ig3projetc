/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : Person.cpp
OBJET            : Classe pour les donnees d'une personne (Nom, Id, Frequence, Liste d'amis)
--------------------------------------------------------------------------------
DATE DE CREATION : 19/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#ifndef PERSON_H_INCLUDED
#define PERSON_H_INCLUDED


/*=================================
Includes
===================================*/
#include <iostream>
#include <string>
#include <vector>
#include <numeric>
/*=================================*/

using namespace std;


class Person {
  /* Attributs */
  /* Le nom, l'id de la personne, la frequence de ses visites
     ainsi que la liste des id des personnes a qui il fait confiance */
  private:
  string name;
  int id_number;
  int frequency;
  vector <int> listLink;


  public:
  /* Methodes */

    /* Constructeurs et Desctructeurs */
    Person();
    Person(string n, int i, int f);
    ~Person();


    /* Accesseur en ecriture */
    void set_name(string n);
    void set_id(int i);
    void set_freq(int f);

    void addFriend(int i);
      /* Ajoute un ami en entrant son id */

    /* Accesseur en lecture */
    string get_name();
    int get_id();
    int get_freq();
    vector <int> get_listLink();


    /* Autres et optionnels  */
    void sortFriends();
      /* Trie le vecteur d'ami dans l'ordre croissant */

    void display();
      /* Affichage d'une personne */

};

#endif // PERSON_H_INCLUDED
