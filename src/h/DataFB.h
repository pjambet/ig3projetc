/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : DataFB.h
OBJET            : Classe pour les donnees Facebook
--------------------------------------------------------------------------------
DATE DE CREATION : 17/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#ifndef DATAFB_H_INCLUDED
#define DATAFB_H_INCLUDED


// Include
#include <iostream>
#include <string>
using namespace std;


class DataFB {
  /* Attributs */
  private:
  string name;
  int id_number;
  int frequency;


  public:
  /* Methodes */

    /* Constructeurs et Desctructeurs */
  DataFB();
  DataFB(string n, int i, int f);

  ~DataFB();

    /* Accesseur en ecriture */
  void set_name (string n);
  void set_id (int i);
  void set_freq (int f);

    /* Accesseur en lecture */
  string get_name ();
  int get_id ();
  int get_freq ();

    /* Autres (optionnels) */
  void affiche();

};
#endif // DATAFB_H_INCLUDED

