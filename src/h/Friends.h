/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : Friends.h
OBJET            : Classe pour les donnees d'une personne (Nom, Id, Frequence, Liste d'amis)
--------------------------------------------------------------------------------
DATE DE CREATION : 29/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#ifndef FRIENDS_H_INCLUDED
#define FRIENDS_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <numeric>

using namespace std;


class Friends {
  private :
  int id;
  vector<int> listLink;
  vector<int> listDualLink;

  public :
    /* Constructeur et Destructeur */
    Friends();
    ~Friends();


    /* Accesseur ecriture */
    void addFriend(int i);
      /* Ajoute un ami en entrant son id */
    void addDualFriend(int i);
      /* Ajoute un "ami dual", quelqu'un qui lui fait confiance */
    void set_id(int i);


    /* Accesseur lecture */
    int get_id();
    vector <int> get_listLink();
    vector <int> get_listDualLink();


    /* Autres et optionnels  */
    void sortFriends();
      /* Trie le vecteur d'ami et le vecteur d'"amis dual" dans l'ordre croissant */
    void print();
      /* Affichage d'un id et de tous ses amis */

};

#endif // FRIENDS_H_INCLUDED
