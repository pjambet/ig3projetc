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
#include <cstring>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <cassert>

using namespace std;


/* PROCEDURE : generateFile - Generation d'un fichier d'entree */
void generateFile(string source, string dest, int n, int d_rel, int d_quest);
/* COMPLEXITE : Lecture du fichier source -> Lineaire
                Choix des noms et id -> Quadratique
                Determination des relations -> Quadratique
                Determination des questions -> Quadratique
   ENTREE : source, la chaine de caracteres contenant l'emplacement d'un fichier de base de donnees
            dest, la chaine de caracteres contenant le nom du fichier ou stocker les donnees
            n, le nombre de sommets desires dans fichier a creer
            d_rel, le pourcentage de relations desirees entre les n personnes
            d_quest, le pourcentage de questions desirees entre les n personnes
   ALGORITHME :
     Ouverture du fichier source
       Lire et stocker les noms et id contenus dans le fichier
     Fermer le fichier source

     Ouvrir le fichier de destination dest, s'il n'existe pas, il est automatiquement cree
       Inscrire le nombre de personne n dans le fichier
       Choisir aleatoirement n personnes et les inscrire dans le fichier sous le format "nom, id, frequence"

       Creer une matrice virtuelle n*n

       Placer aleatoirement les relations selon le pourcentage d_rel dans la matrice n*n
       Inscrire le nombre de relations obtenu dans le fichier
       Lire la matrice et inscrire les relations dans le fichier sous le format "id1, id2"

       Placer aleatoirement les questions selon le pourcentage d_quest dans la matrice n*n
       Inscrire le nombre de questions obtenu dans le fichier
       Lire la matrice et inscrire les relations dans le fichier sous le format "id1 -> id2"
     Fermer le fichier dest
*/


/* FONCTION : generateMatrix - Generation une matrice de 0 et de 1 aleatoirement et renvoie le nombre de 1 */
int generateMatrix(int nb, int** m, int r);
/* COMPLEXITE : o(nb²)
   ENTREE : nb, la taille de la matrice
            m, la matrice d'entier
            r, le ratio de remplissage
   ALGORITHME :
     Pour toutes les cases de m
       Tirer un nombre entre 0 et 10 000
       Si ce nombre est inferieur a r
         on met 1 dans la matrice, et on incremente le compteur
       Sinon 0

     Renvoyer le compteur
*/


/* FONCTION : convertNumToRatio - Convertit le nombre donne en ratio par rapport a nbSum */
float convertNumToRatio(int n, int nbSum);
#endif // GENERATOR_H_INCLUDED
