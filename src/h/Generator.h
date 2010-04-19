/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : Generator.h
OBJET            : Genere des fichiers de donnee
--------------------------------------------------------------------------------
DATE DE CREATION : 19/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#ifndef GENERATOR_H_INCLUDED
#define GENERATOR_H_INCLUDED

/*=================================
Includes
===================================*/
#include <iostream>
#include <string>
#include <vector>
#include "time.h"

/*=================================*/

using namespace std;


/*=================================
Constantes
===================================*/
#define FICHIER_DAT "../../test/noms.dat"

#define RATIO_MIN 10
#define RATIO_MAX 50

#define RATIO_QUESTION 100

/*=================================*/

void generateFile(string dest, int nb_person);
  /* Genere un fichier de donnees
     On indique en entree le nom du fichier destination et le nombre de personne */

int generateMatrix(int nb, int** m, int r);
  /* Genere une matrice m nb*nb avec des 0 et des 1
     r donne le pourcentage de remplissage
     renvoie le nombre de 1 */

string generateName(vector< string > database);
  /* Choisit un nom au hasard dans la database */


#endif // GENERATOR_H_INCLUDED
