/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : AdjMat.h
OBJET            : matrice d'adjacence
--------------------------------------------------------------------------------
DATE DE CREATION : 30/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#ifndef MATADJ_H_INCLUDED
#define MATADJ_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "Summit.h"

using namespace std;


class AdjMat {

  /* Attributs */
  /* ********* */
  private:
    int unsigned m_size;
    vector < vector < int > > m_graph;

    vector < s_summit > m_tabSummit;


  /* Methodes */
  /* ******** */
  public:
    AdjMat ();
    ~AdjMat ();

    void initData (vector< s_summit >& v, vector < vector < int > >& m); // Remplit la matrice


    vector< s_summit > initCFC (); /* Fait 2 parcours en prof pour trouver les CFC */
    void DFS (); // Parcours en profondeur du graphe (Depth First Search)
    void DFSHidden (int i, int& t); // Parcours en profondeur du graphe (recursif)
    void DFSD (); // Parcours en profondeur du graphe dual (Depth First Search Dual)
    void DFSDHidden (int i, int& t); // Parcours en profondeur du graphe dual (recursif)


    vector< s_summit > initDist (int x);// Calcule les plus courts chemins à partir de l'id x avec l'algo Dijkstra
    int extractMin(int x); // Extrait l'element de m_tabSummit non explore avec beg minimum, x valeur a renvoyer si on trouve pas de min


    void sortDescEnd(); // Trie les ordres finaux en decroissant
    void sortAscBeg(); // Trie les ordres de debut en croissant
    void printMat (); // Affiche la matrice adjacente


    bool isImportant(int x); // Renvoie vrai si le point x est important, x le rang d'un sommet dans m_tabSummit
};


#endif // MATADJ_H_INCLUDED
