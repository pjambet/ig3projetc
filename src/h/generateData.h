/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : generate_data.h
OBJET            : Genere des fichiers de donnees (fait a l'arrache)
--------------------------------------------------------------------------------
DATE DE CREATION : 17/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#ifndef GENERATE_DATA_H_INCLUDED
#define GENERATE_DATA_H_INCLUDED

// Include
#include <iostream>
#include <string.h>
#include <time.h>
using namespace std;


void generate_data(int nb_person);
/* Genere des donnees contenant un nombre de personne defini */

void generer_nom_aleatoire(char n[20]);
/* Genere une chaine de caractere aleatoire pour faire genre un nom */


#endif // GENERATEDATA_H_INCLUDED
