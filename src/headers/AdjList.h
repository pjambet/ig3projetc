/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : AdjList.h
OBJET            : representation de graphes sous forme de liste de voisins
--------------------------------------------------------------------------------
DATE DE CREATION : 30/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------
DETAILS 		     : SCC (Strongly Connected Component) = CFC (Composante Fortement Connexe)
                 : DFS (Depth First Search) = PPG(Parcours en Profondeur du Graphe)

============================================================================= */

#ifndef ADJLIST_H_INCLUDED
#define ADJLIST_H_INCLUDED

/*=================================
Includes
===================================*/
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <climits>

#include "Summit.h"

using namespace std;


class AdjList {
private :

    /* ATTRIBUTS */
    int m_size;
    vector < vector <int> > m_graph;
    vector < vector <int> > m_graphDual;

    vector < s_summit > m_tabSummit;

    /* EXPLICATIONS DES ATTRIBUTS :

    	Structure de representation d'une liste d'adjacence.
    	Les donnees conservees sont :
    	- m_size : La taille du tableau de listes et le nombre de sommet dans le graphe
      - m_graph : Un vecteur associant a chaque sommet une liste de fils,
        	        m_graph[i][j] = x si m_tabSummit[x] est un fils de m_tabSummit[i]
      - m_graphDual : Un vecteur associant a chaque sommet une liste de pere,
                      m_graph[i][j] = x si m_tabSummit[x] est un pere de m_tabSummit[i]
     	- m_tabSummit : Tableau contenant les donnees des sommets */

    /* ****************************************************** */
    /* ****************************************************** */

public:

    /* CONSTRUCTEURS ET DESCTRUCTEURS */
    AdjList ();
    ~AdjList ();


    /* METHODES DE TRI DU TABLEAU DE SOMMETS */

    /* PROCEDURE : sortDescEnd - Trie les ordres finaux en decroissant tout en conservant les id */
    void sortDescEnd();
    /* COMPLEXITE : Quasi-lineaire
       ENTREE : -
       ALGORITHME :
           Sauvegarde les id
           Tri m_tabSummit
           Restaure les id */


    /* PROCEDURE : sortAscBeg - Trie les ordres de debut en croissant sans conservation des id */
    void sortAscBeg();
    /* COMPLEXITE : Quasi-lineaire
       ENTREE : -
       ALGORITHME :
         Utiliser un algorithme de tri sur m_tabSummit */


    /* Methode d'initialisation de la classe */

    /* PROCEDURE : initData - Initialisation des donnees */
    void initData (vector< s_summit >& v, vector< vector< int > >& f, vector< vector< int > >& df);
    /* COMPLEXITE : Copie du vecteur v -> Lineaire
                    Copie de du vecteur de vecteur f -> Quadratique
                    Copie de du vecteur de vecteur df -> Quadratique
       ENTREE : v, le tableau contenant les donnees sur les sommets
                f, la structure similaire a un tableau de liste de fils
                df, la structure similaire a un tableau de liste de pere
       ALGORITHME :
         Deduit la taille m_size de la taille du vecteur v
         Copie v dans m_tabSummit
         Copie f dans m_graph
         Copie df dans m_graphDual */

	/* ACCESSEURS */
	
	vector < s_summit > getTabSummit();
	s_summit getTabSummit(int i);
	int getSize();
	vector < vector <int> > getGraph();
	vector < vector <int> > getGraphDual();

    /* METHODES DE RECHERCHE DE COMPOSANTES FORTEMENT CONNEXES (STRONGLY CONNECTED COMPONENT) */

    /* FONCTION : initSCC - Initialise les donnees pour trouver plus facilement les CFC (SCC) */
    vector< s_summit > initSCC ();
    /* COMPLEXITE : Premier parcours en profondeur -> Lineaire
                    Tri decroissant -> Quasi-Lineaire
                    Second parcours en profondeur -> Lineaire
                    Determination des importances -> Polynomial
                    Tri croissant -> Quasi-Lineaire
       ENTREE : -
       ALGORITHME :
         Executer un premier parcours en profondeur du graphe
           Pour chaque sommet, on note le temps de rencontre et le temps de fin d'exploration
         Determiner le nouvel ordre d'exploration en fonction des temps de fin

         Executer le second parcours en profondeur du graphe
           Obtenir de nouveaux temps de rencontre et de fin d'exploration de chaque point
         Pour chaque sommet, on determine si ce point est important

         Trier les sommets par temps de rencontre */


    /* PROCEDURE : DFS - Parcours en profondeur du graphe (Depth First Search) */
    void DFS ();
    void DFSHidden (int i, int& t);
    /* COMPLEXITE : Lineaire
       ENTREE : -
       ALGORITHME :
         Initialiser le temps a 0
         Pour chaque sommet non explore, on fait un appel sur DFSHidden
           Noter le temps de rencontre du sommet
             Pour chaque descendant non explore, appel recursif DFSHidden
           Noter le temps de fin d'exploration */


    /* PROCEDURE : DFSD - Parcours en profondeur du graphe dual */
    void DFSD ();
    void DFSDHidden (int i, int& t);
    /* COMPLEXITE : Lineaire
       ENTREE : -
       ALGORITHME :
         Initialiser le temps a 0
         Pour chaque sommet non explore, on fait un appel sur DFSDHidden
           Noter le temps de rencontre du sommet
             Pour chaque parent non explore, appel recursif DFSDHidden
           Noter le temps de fin d'exploration */



    /* METHODES DE RECHERCHE DES PLUS COURTS CHEMINS (DIJKSTRA) */

    /* FONCTION : initDist - Utilise l'algorithme de Dijkstra pour determiner les plus courts chemins */
    vector< s_summit > initDist (int x);
    /* COMPLEXITE : Polynomial
       ENTREE : x, un sommet du graphe
       ALGORITHME :
         Initialiser tous les points : Etat non explore, distance infinie, et pere null (-1)
         Initialiser x a une distance nulle

         Chercher le sommet n non explore qui possede la distance minimale
         Le passer a atteint
         Pour tous les descendants i de ce sommet
           Si leurs distances est inferieures à celle de (n + la frequence de i)
             Mettre a jour la distance et le pere le plus proche de i

         Retourner le tableau de sommets */


    /* FONCTION : extractMin - Chercher le sommet non explore avec la distance la plus courte du point de depart */
    int extractMin(int x);
    /* COMPLEXITE : Lineaire
       ENTREE : x, un sommet du graphe, le point de depart
       ALGORITHME :
         Initialiser l'indice du minimum a x et la distance minimum a l'infini

         Pour tous les sommets du graphe
           Si on trouve un point non explore avec une distance plus courte
           On la sauvegarde

         Renvoyer l'indice du minimum */


    /* METHODES DE DETERMINATION D'IMPORTANCE */

    /* FONCTION : isImportant - Determine l'importance d'un point */
    bool isImportant(int x);
    /* COMPLEXITE : Polynomial
       ENTREE : x, un sommet du graphe
       ALGORITHME :
         1 - Eliminer les cas simples ou le point n'est pas important
         Si le point est un puit (aucun fils) ou une source (aucun pere)
         Ou bien si le point n'est relie au reste du graphe que via un seul point (pere et fils unique et identique)
           Renvoyer faux

         2 - Tester les autres cas
         Pour tous les fils i de x de la meme CFC
           Si i ne possede qu'un seul pere (= x)
             Renvoyer vrai
           Sinon si aucun des autres peres de i n'est dans la meme CFC
             Renvoyer vrai

         Pour tous les pere i de x de la meme CFC
           Si i ne possede qu'un seul fils (= x)
             Renvoyer vrai
           Sinon si aucun des autres fils de i n'est dans la meme CFC
             Renvoyer vrai

         3 - Si la fonction n'a encore rien renvoye
         Renvoyer faux */


    /* FONCTION : areInTheSameSCC - Indique si deux sommets sont dans la meme CFC */
    bool areInTheSameSCC(int x, int y);
    /* COMPLEXITE : Lineaire
       ENTREE : x, un sommet du graphe
                y, un sommet du graphe
       ALGORITHME :
         Pour i de 0 a m_size
           Si on trouve un sommet dont temps beg et end encadre les beg et end de x et de y en meme temps
             Renvoyer vrai

         Renvoyer faux si on a pas trouve un sommet qui satisfait cette condition */

};


#endif // ADJLIST_H_INCLUDED
