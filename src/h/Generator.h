/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : Generator.h
OBJET            : Genere des fichiers de donnee
--------------------------------------------------------------------------------
DATE DE CREATION : 19/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------
  - Creation du fichier : (19/04/2010)
    Genere un autre fichier a partir d'une liste de nom externe

  - Modification : (19/04/2010)
    Possibilite de mettre la liste de nom externe en parametre
    La liste de nom contient en plus des nom, les id lie a chaque nom

============================================================================= */

#ifndef GENERATOR_H_INCLUDED
#define GENERATOR_H_INCLUDED

/*=================================
Includes
===================================*/
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <cassert>
#include <ctime>

using namespace std;


void generateFile(string source, string dest, int n, int d_rel, int d_quest);
  /* Genere un fichier d'entree
     Les noms et id des personnes sont determines par le fichier indique par source
     On indique ensuite le nom du fichier destination
     n represente le nombre de personne
     d_rel est la densite de relation, c'est-a-dire le pourcentage de relation a creer sur le nombre de relation possible
     d_quest est la densite de question, le pourcentage de question a creer sur le nombre de question possible */

int generateMatrix(int nb, int** m, int r);
  /* Genere une matrice m nb*nb avec des 0 et des 1
     r donne le pourcentage de remplissage
     renvoie le nombre de 1 */

#endif // GENERATOR_H_INCLUDED
