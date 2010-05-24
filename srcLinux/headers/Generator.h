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
#include <map>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <cassert>

#include "fbfriends.h"
/*=================================
Constantes
===================================*/
#define FREQ_MAX 100
#define RATIO 10000
#define REPERTORY_TEST "../test/"

using namespace std;


class Generator {
private :

    /* ATTRIBUTS */
    string m_database;
    string m_destination;
    int m_nbPerson;
    int m_nbPersonMax;
    int m_nbRelation;
    int m_nbQuestion;

    bool m_connected;

    /* EXPLICATIONS DES ATTRIBUTS :

       Structure de generation de fichier d'entree
       Les donnees conservees sont :
       - database : L'entree source de tous les noms et leurs id respectifs
       - destination : Le fichier ou sera cree le fichier genere

       - nbPerson : Le nombre de personne desire
       - nbPersonMax : Le nombre de personne maximum disponible avec le fichier database
       - nbRelation : Le nombre de relation desire
       - nbQuestion : Le nombre de question desire

       - connected : indique si on s'est deja connecte sur facebook (et donc, qu'on possede un cookie valide) */


    /* ****************************************************** */
    /* ****************************************************** */

public :

    /* CONSTRUCTEURS ET DESCTRUCTEURS : */
    Generator();
    ~Generator();


    /* ACCESSEURS */
    string getDestination();


    /* METHODE D'INITIALISATION DE LA CLASSE */

    /* PROCEDURE : changeOptionAutomatic - Initialisation des donnees sans passer par un menu */
    void changeOptionAutomatic(string db, string dest, int nP, int nR, int nQ);
    /* COMPLEXITE : Constant
       ENTREE : db, la chaine de caracteres contenant la nouvelle database
                dest, la chaine de caracteres contenant le nom du fichier ou stocker les donnees
                nP, le nombre de sommets desires dans fichier a creer
                nR, le nombre de relations desirees entre les n personnes
                nQ, le nombre de questions desirees entre les n personnes
       ALGORITHME :
           Affecter chaque variable a leurs attributs respectifs */


    /* PROCEDURE : changeOptionManual - Initialisation des donnees via un menu */
    void changeOptionManual();
    /* COMPLEXITE : Constant
       ENTREE : -
       ALGORITHME :
           Demander a l'utilisateur les nouvelles valeurs pour les attributs */


    /* PROCEDURE : generateFile - Generation d'un fichier d'entree */
    void generateFile();
    /* COMPLEXITE : Lecture du fichier source -> Lineaire
                    Choix des noms et id -> Quadratique
                    Determination des relations -> Quadratique
                    Determination des questions -> Quadratique
       ENTREE : -
       ALGORITHME :
         Ouverture du fichier source
           Lire et stocker les noms et id contenus dans le fichier
         Fermer le fichier source

         Ouvrir le fichier de destination destination, s'il n'existe pas, il est automatiquement cree
           Inscrire le nombre de personne n dans le fichier
           Choisir aleatoirement n personnes et les inscrire dans le fichier sous le format "nom, id, frequence"

           Creer une matrice virtuelle n*n

           Placer aleatoirement les relations selon le pourcentage d_rel dans la matrice n*n
           Inscrire le nombre de relations obtenu dans le fichier
           Lire la matrice et inscrire les relations dans le fichier sous le format "id1, id2"

           Placer aleatoirement les questions selon le pourcentage d_quest dans la matrice n*n
           Inscrire le nombre de questions obtenu dans le fichier
           Lire la matrice et inscrire les relations dans le fichier sous le format "id1 -> id2"
         Fermer le fichier destination */


    /* PROCEDURE : generateDatabase - Generation une database de nom et d'id */
    void generateDatabase();
    /* COMPLEXITE :
       ENTREE : -
       ALGORITHME :
    */


    /* FONCTION : generateMatrix - Generation une matrice de 0 et de 1 aleatoirement et renvoie le nombre de 1 */
    int generateMatrix(int n, int** m, int r);
    /* COMPLEXITE : o(nb²)
       ENTREE : n, la taille de la matrice
                m, la matrice d'entier
                r, le ratio de remplissage
       ALGORITHME :
         Pour toutes les cases de m
           Tirer un nombre entre 0 et 10 000
           Si ce nombre est inferieur a r
             on met 1 dans la matrice, et on incremente le compteur
           Sinon 0

         Renvoyer le compteur */


    /* FONCTION : convertNumToRatio - Convertit le nombre donne en ratio par rapport a nbSum */
    float convertNumToRatio(int n, unsigned long long nbSum);
    /* COMPLEXITE : Constant o(1)
       ENTREE : n, le nombre de personne
                nbSum, le nombre de liens desire
       ALGORITHME :
          (nbSum) pour (n*n-n) possibles
          x pour 10 000

          Renvoyer x par produit en croix */

};


#endif // GENERATOR_H_INCLUDED
