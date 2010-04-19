/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : UserData.cpp
OBJET            : Classe pour stocker les donnees d'une fichier utilisateur
--------------------------------------------------------------------------------
DATE DE CREATION : 19/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

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

#include "Person.h"

class UserData {
  /* Attributs */
  /* Le nombre de personne, de relation et de question au total
     La liste des personnes
     La liste des questions */
  private:
  int nb_person;
  int nb_link;
  int nb_question;
  map < int, Person > listPerson;
  map < int, vector <int> > listQuestion;


  public:
  /* Methodes */

    /* Constructeurs et Desctructeurs */
    UserData(string fileName);

    ~UserData();


    /* Accesseur en ecriture */
    void addPerson(Person p);
    void addQuestion(int id1, int id2);


    /* Accesseur en lecture */
    map < int, Person > get_listPerson();
    map < int, vector<int> > get_listQuestion();


    /* Autres et optionnels */
    bool is_link(int id1, int id2);
      /* Renvoie vrai s'il existe une relation entre id1 et id2 */

    bool is_question(int id1, int id2);
      /* Renvoie vrai si on se demande le temps minimum entre id1 et id2 */

    void display();
      /* Procedure d'affichage */

};

#endif // USERDATA_H_INCLUDED
