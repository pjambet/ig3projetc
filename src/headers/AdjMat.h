/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : AdjMat.h
OBJET            : matrice d'adjacence
--------------------------------------------------------------------------------
DATE DE CREATION : 30/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------
DETAILS 		     : SCC (Strongly Connected Component) = CFC (Composante Fortement Connexe)
                 : DFS (Depth First Search) = PPG(Parcours en Profondeur du Graphe)

============================================================================= */

#ifndef MATADJ_H_INCLUDED
#define MATADJ_H_INCLUDED

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


class AdjMat {
private:

    /* ATTRIBUTS */
    int m_size;
    int** m_graph;

    vector < s_summit > m_tabSummit;

    /* EXPLICATIONS DES ATTRIBUTS :

       Structure de representation d'une matrice d'adjacence.
       Les donnees conservees sont :
       - m_size : La taille de la matrice et le nombre de sommet dans le graphe
       - m_graph : Une matrice de 0 et de 1, pour i et j quelconques,
                   m_graph[i][j] = 1 si j est le descendant de i,
                   0 sinon
       - m_tabSummit : Tableau contenant les donnees des sommets, pour i quelconque,
                       si (i < m_size), alors m_tabSummit[i] correspond a i-eme ligne et colonne de m_graph */


    /* ****************************************************** */
    /* ****************************************************** */

public:

    /* CONSTRUCTEURS ET DESCTRUCTEURS : */
    AdjMat ();
    ~AdjMat ();

    /* Methode d'initialisation de la classe */

    /* PROCEDURE : initData - Initialisation des donnees */
    void initData (vector< s_summit >& v, int** m);
    /* COMPLEXITE : Copie du vecteur v -> Lineaire
                    Copie de la matrice m -> Quadratique
       ENTREE : v, le tableau contenant les donnees sur les sommets
                m, la matrice de relation correspondant aux donnees
       ALGORITHME :
         Deduit la taille m_size de la taille du vecteur v
         Copie v dans m_tabSummit
         Copie la matrice m dans m_tabSummit */


    /* Methodes de recherche de Composantes Fortement Connexes (Strongly Connected Component) */

    /* FONCTION : initSCC - Initialise les donnees pour trouver plus facilement les CFC */
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


    /* PROCEDURE : DFS - Parcours en profondeur du graphe (Depth First Search) */
    void DFS ();
    void DFSHidden (int i, int& t);
    /* COMPLEXITE : Quadratique
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
    /* COMPLEXITE : Quadratique
       ENTREE : -
       ALGORITHME :
         Initialiser le temps a 0
           Pour chaque sommet non explore, on fait un appel sur DFSDHidden
             Noter le temps de rencontre du sommet
               Pour chaque parent non explore, appel recursif DFSDHidden
             Noter le temps de fin d'exploration */



    /* Methodes de recherche des plus courts chemins (Dijkstra) */

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
    int extractMin(int x, map<int, int>& m);
    /* COMPLEXITE : Lineaire
       ENTREE : x, un sommet du graphe, le point de depart
       ALGORITHME :
         Initialiser l'indice du minimum a x et la distance minimum a l'infini

         Pour tous les sommets du graphe
           Si on trouve un point non explore avec une distance plus courte
           On la sauvegarde

         Renvoyer l'indice du minimum */


    /* Methodes de tri du tableau de sommets */

    /* FONCTION : sortDescEnd - Trie les ordres finaux en decroissant tout en conservant les id */
    void sortDescEnd();
    void sortAscBeg();
    /* COMPLEXITE : Quasi-lineaire
       ENTREE : -
       ALGORITHME :
         Initialiser l'indice du minimum a x et la distance minimum a l'infini

         Pour tous les sommets du graphe
           Si on trouve un point non explore avec une distance plus courte
           On la sauvegarde

         Renvoyer l'indice du minimum */




    bool isImportant(int x); // Renvoie vrai si le point x est important, x le rang d'un sommet dans m_tabSummit

    void nbNeighborhood(int x, int& nbF, int& nbC); // Trouve le nombre de voisin de x (nombre de pere nbF et nombre de fils nbC)
    // 0 si il n'y en a pas
    // 1 si il y en a qu'un
    // 2 si il y en a deux ou plus

    bool areInTheSameSCC(int x, int y); // Renvoie vrai si x et y sont dans la meme CFC


    void printMat (); // Affiche la matrice adjacente
};


#endif // MATADJ_H_INCLUDED
