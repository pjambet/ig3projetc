/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : AdjList.h
OBJET            : representation de graphes sous forme de liste de voisins
--------------------------------------------------------------------------------
DATE DE CREATION : 30/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------
DETAILS 		 : SCC (Strongly Connected Component) = CFC (Composante Fortement Connexe)
				 : DFS (Depth First Search) = PPG(Parcours en Profondeur du Graphe)
============================================================================= */

#ifndef ADJLIST_H_INCLUDED
#define ADJLIST_H_INCLUDED

// Include
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <climits>

#include "Summit.h"

using namespace std;


class AdjList {

private :
    /* Attributs */
    int m_size;
    vector < vector <int> > m_graph;
    vector < vector <int> > m_graphDual;

    vector < s_summit > m_tabSummit;

    /* EXPLICATIONS DES ATTRIBUTS :

    	Structure de representation d'une liste d'adjacence.
    	Les donnees conservees sont :
    	- m_size : La taille du tableau de listes
        - m_graph : Un vecteur de vecteur d'entiers,
        	        m_graph[i][j] = x si x est voisin, de i (x est le "j-ieme" voisin de i)
        - m_graphDual : Le graphe dual associe a m_graph
     	- m_tabSummit : Tableau contenant les donnees des sommets, pour i quelconque,
                        si (i < m_size), alors m_tabSummit[i] correspond a i-eme ligne et colonne de m_graph */

    /* ****************************************************** */
    /* ****************************************************** */

public:
    /* CONSTRUCTEURS ET DESCTRUCTEURS */
    AdjList ();
    ~AdjList ();

    /* Methode d'initialisation de la classe */
    void initData (vector< s_summit >& v, vector< vector< int > >& f, vector< vector< int > >& df); /* Remplit le la structure avec les donnees */

    /* Methodes de recherche de Composantes Fortement Connexes (Strongly Connected Component) */

    /* FONCTION : initSCC - Initialise les donnees pour trouver plus facilement les CFC (SCC) */
    vector< s_summit > initSCC ();
    /* COMPLEXITE : Premier parcours en profondeur ->
                    Tri decroissant ->
                    Second parcours en profondeur ->
                    Determination des importances ->
                    Tri croissant ->
       ENTREE : -
       ALGORITHME :
         Executer un premier parcours en profondeur du graphe
           Pour chaque sommet, on note le temps de rencontre et le temps de fin d'exploration
         Determiner le nouvel ordre d'exploration en fonction des temps de fin

         Executer le second parcours en profondeur du graphe
           Obtenir de nouveaux temps de rencontre et de fin d'exploration de chaque point
         Pour chaque sommet, on determine si ce point est important

         Trier les sommets par temps de rencontre */

    void DFS (); /* Parcours en profondeur du graphe (appel sur PProfG) */
    void DFSHidden (int i, int& t); /* Parcours en profondeur du graphe (recursif) */
    void DFSD (); /* Parcours en profondeur du graphe dual (appel sur PProfGD) */
    void DFSDHidden (int i, int& t); /* Parcours en profondeur du graphe dual (recursif) */


    vector< s_summit > initDist (int x); /* Calcule les plus courts chemins à partir de l'id au rang x */
    int extractMin(int x);

    bool isImportant(int x); /* Renvoie vrai si x est important, x est l'id */
    bool areInTheSameSCC(int x, int y);

    void sortDescEnd(); /* Trie les ordres finaux en decroissant */
    void sortAscBeg(); /* Trie les ordres de debut en croissant */


};

#endif
