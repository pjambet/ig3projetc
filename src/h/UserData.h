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

#include "../h/Person.h"

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
    Person get_Person(int id);


    /* Autres et optionnels */
    bool is_link(int id1, int id2);
      /* Renvoie vrai s'il existe une relation de id1 vers id2 */
    bool is_dualLink(int id1, int id2);
      /* Renvoie vrai s'il existe une relation de id1 vers id2 dans les relations duales */

    bool is_question(int id1, int id2);
      /* Renvoie vrai si on se demande le temps minimum entre id1 et id2 */

    void display();
      /* Procedure d'affichage */

};

#endif // USERDATA_H_INCLUDED
