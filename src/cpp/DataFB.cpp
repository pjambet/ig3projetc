/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : DataFB.cpp
OBJET            : Classe pour les donnees Facebook
--------------------------------------------------------------------------------
DATE DE CREATION : 17/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#include "DataFB.h"

    /* Constructeurs et Desctructeurs */
DataFB::DataFB(){
  id_number = 0;
  frequency = 0;
}

DataFB::DataFB(string n, int i, int f){
  name = n;
  id_number = 0;
  frequency = 0;
}

DataFB::~DataFB() {
}


    /* Accesseur en ecriture */
void DataFB::set_name (string n) {
  name = n;
}

void DataFB::set_id (int i) {
  id_number = i;
}

void DataFB::set_freq (int f) {
  frequency = f;
}


    /* Accesseur en lecture */
string DataFB::get_name () {
  return name;
}

int DataFB::get_id () {
  return id_number;
}

int DataFB::get_freq () {
  return frequency;
}

    /* Autres (optionnels) */
void DataFB::affiche() {
  cout << name << " " << id_number << " " << frequency << endl;
}

