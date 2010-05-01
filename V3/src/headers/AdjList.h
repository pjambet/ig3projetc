/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : AdjList.h
OBJET            : representation de graphes sous forme de liste de voisins
--------------------------------------------------------------------------------
DATE DE CREATION : 30/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#ifndef ADJLIST_H_INCLUDED
#define ADJLIST_H_INCLUDED

// Include
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

#include "Summit.h"

using namespace std;


class AdjList {

    private :
    /* Attributs */
    int m_size;
    map < int, vector <int> > m_graph;
    map < int, vector <int> > m_graphDual;

    map< int, int > m_idToRank;
    vector < s_summit > m_tabSummit;


    public:
    /* Contructeurs et destructeurs*/
    AdjList ();
    ~AdjList ();

    /* Methodes */
    void initData (vector< s_summit >& v, map< int, vector< int > >& f, map< int, vector< int > >& df, map< int, int >& ItR); // Remplit le la structure avec les donnees


    vector< s_summit > initCFC ();

    void DFS (); // Parcours en profondeur du graphe (appel sur PProfG)
    void DFSHidden (int i, int& t); // Parcours en profondeur du graphe (recursif)
    void DFSD (); // Parcours en profondeur du graphe dual (appel sur PProfGD)
    void DFSDHidden (int i, int& t); // Parcours en profondeur du graphe dual (recursif)


    vector< s_summit > initDist (int x); // Calcule les plus courts chemins à partir de l'id au rang x
    int extractMin();


    void sortDescEnd(); // Trie les ordres finaux en decroissant
    void sortAscBeg(); // Trie les ordres de debut en croissant


};

#endif
