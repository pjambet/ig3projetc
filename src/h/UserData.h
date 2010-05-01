/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : UserData.cpp
OBJET            : Classe pour stocker les donnees d'une fichier utilisateur
--------------------------------------------------------------------------------
DATE DE CREATION : 19/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------
  - Creation du fichier : (19/04/2010)
    Lit un fichier et stocke toutes les donnees qu'il contient en donnees reutilisables par une fonction externe

  - Modification : (20/04/2010)
    Traitement des relations duales dans le constructeur
    Ajout de la possibilite d'acces a une personne en particulier grace a son id

============================================================================= */

#ifndef USERDATA_H_INCLUDED
#define USERDATA_H_INCLUDED

/*=================================
Includes
===================================*/
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <numeric>
#include <cstdio>
#include <cstdlib>
#include "Person.h"
#include "Friends.h"



class UserData {
  /* Attributs */
  private:
  bool analysable; /* Indique si fichier a ete charge */
  int nbPerson; /* Nombre de personne */
  int nbLink; /* Nombre de relations */
  int nbQuestion; /* Nombre de questions */
  map < int, Person > listPerson; /* Liste des personnes (id, nom et frequence) */

  char structFriends; // 'm' pour matrice et 'l' pour liste
  /* Selon la structure de stockage des relations
     On choisira de remplir l'un des attributs suivants */
  map < int, Friends > listFriends;

  map <int, int> idToRank; // Associe une id a sa place dans la matrice
  map <int, int> rankToId; // Associe un rang a son id dans la matrice
  int** matFriends;

  map < int, vector <int> > listQuestion; /* Liste des questions */


  public:
  /* Methodes */

    /* Constructeurs et Desctructeurs */
    UserData();
    ~UserData();


    /* Accesseur en ecriture */
    void addPerson(Person p);
    void addQuestion(int id1, int id2);


    /* Accesseur en lecture */
    map < int, Person > get_listPerson();
    map < int, Friends > get_listFriends();
    int** get_matFriends();
    map < int, vector<int> > get_listQuestion();

    Person get_Person(int id);
    int get_nbPerson();
    int get_nbLink();
    int get_nbQuestion();
    char get_structFriends();

    int get_idToRank(int id);
    int get_rankToId(int rank);


    /* Autres et optionnels */
    void openData(string fileName);
      /* Ouvre le fichier indique par fileName */

    void clear();
      /* Reset la base de donnee */

    char defineStructFriends();
      /* Renvoie la structure la mieux adaptee pour stocker les donnees
         'm' pour matrice, 'l' pour liste */

    bool is_question(int id1, int id2);
      /* Renvoie vrai si on se demande le temps minimum entre id1 et id2 */

    bool is_analysable();
      /* Renvoie vrai si un fichier a ete charge */


    void print();
      /* Procedure d'affichage */
    void printMatFriends();
      /* Affichage de la matrice matFriends */
    void printListFriends();
      /* Affichage de la liste listFriends */

};

#endif // USERDATA_H_INCLUDED
