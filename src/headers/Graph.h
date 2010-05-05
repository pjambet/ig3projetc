/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : Graph.h
OBJET            : Structure de graphe
--------------------------------------------------------------------------------
DATE DE CREATION : 30/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

/*=================================
Includes
===================================*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <numeric>
#include <cstdio>

#include "Summit.h"
#include "AdjList.h"
#include "AdjMat.h"

#define TEST_STRUCT 'm'

using namespace std;


class Graph{

  /* Attributs */
  /* ********* */
  /* Dans tout ce qui est vecteur et map (sauf m_idToRank, on ne stocke que le rang de l'id
     Le rang est sa place dans m_tabSummit */
  private:
    int unsigned m_sizeGraph;                             /* Taille du graphe = nombre de personne */
    vector< s_summit > m_tabSummit;                  /* Tableau de personnes */


    map< string, int > m_idToRank;                      /* Trouve le rang dans m_tabSummit a partir de son id */


    char m_structGraph;                              /* Structure du graphe : 'l' pour liste, 'm' pour matrice */


    vector< vector< int > > m_listFriends;         /* Pour une id, on associe une liste de gens a qui il fait confiance */
    vector< vector< int > > m_listDualFriends;     /* Pour une id, on associe une liste de gens qui lui font confiance */

    int** m_matFriends;                                 /* Matrice d'adjacence */

    int unsigned m_nbSCC;                                     /* Nombre de CFC */
    vector< vector < int > > m_listSCC;              /* Vecteur de CFC
                                                        Chaque CFC est represente par un vecteur d'id (entier) */

    int unsigned m_nbDist;                                      /* Nombre de distance a determiner */
    map< int, vector< int > > m_listQuestion;        /* Stocke les questions dans un map */
    map< int, vector< s_summit > > m_listDist;       /* Structure de stockage des distances
                                                        A chaque id est associe le tableau de sommet trouve avec Disjktra */
    multimap< int, vector< int > > m_listPath;          /* Stocke les chemins = chemin a suivre dans m_tabSummit pour arriver */

  /* Methodes */
  /* ******** */
  public:

    /* Constructeurs et Destructeurs */
    Graph ();
    ~Graph ();


    /* Initialisation */
    void initGraph (string& fileNameIn);            /* Initialisation du graphe a partir d'un fichier */
    void clearGraph ();                             /* Remise a zero du graphe */


    /* Accesseurs */
    bool isAnalysable();                            /* Renvoie vrai si on peu analyser = ( taille du graffe != 0 )*/


    /* Recherche */
    void searchSCC ();                             /* Cherche et stocke les listes des CFC a partir de m_tabSummit */
    void searchDistances ();                       /* Utilise Djis */


    /* Autres et optionnels */
    char chooseStruct ();                           /* Choisit la structure la mieux adaptee pour analyser le graphe */
    void saveGraph (string& fileNameOut);            /* Sauvegarde les resultats dans un fichier */


    /* Affichage */
    void printGraph ();                             /* Procedure d'affichage du graphe
                                                      Affiche
                                                        - les personnes
                                                        - les composantes fortements connexes
                                                        - les distances demandees */

};

#endif // GRAPHE_H_INCLUDED
