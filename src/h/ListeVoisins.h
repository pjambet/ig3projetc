/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : ListeVoisins.cpp
OBJET            : representation de graphes sous forme de liste de voisins
--------------------------------------------------------------------------------
DATE DE CREATION : 13/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#ifndef LISTEVOISINS_H_INCLUDED
#define LISTEVOISINS_H_INCLUDED

// Include
#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "sommet.h"
#include "UserData.h"
#include "Friends.h"

using namespace std;

class ListeVoisins{

    private :
    /* Attributs */
    /* Le graph est représenté par un tableau de vecteur d'entier
       on stocke aussi la taille du graphe*/
    map < int, vector <int> > m_graph;
    map < int, vector <int> > m_graphDual;
    /////////////////////////////////
    map < int, int > idPosition; // relation entre l'id et la position
    /////////////////////////////////

    multimap < int, vector <int> > m_distances;

    int m_tailleGraph;
    Sommet* m_summit;

    public:
    /* Contructeurs et destructeurs*/
    ListeVoisins();
    ~ListeVoisins();

    /* Methodes */
    ListeVoisins toDual(); // Renvoie le graphe dual du graphe actuel
    void iniList(UserData* u); // Remplit le map(m_graph) avec les données contenu dans u (UserData)
    void addSummit(int i, int x); // Ajoute l'element x dans la liste(vecteur) graph[i]
    void lscAdjCFC (char* a, int n); // Renvoie les composantes fortement connexes du graphe
    void printListeAdj (); // Affiche la liste adjacente
    void printListeAdjD ();// Affiche la liste adjacente duale
    void printSummits(); // Affiche les infos des sommets


    void PPG (UserData* u); // Parcours en profondeur du graphe (appel sur PProfG)
    void PProfG (int i, int* t); // Parcours en profondeur du graphe (recursif)
    //void PPGD (); // Parcours en profondeur du graphe dual (appel sur PProfGD)
    void PPGD (UserData* u, vector <s_sommet>* V); // Parcours en profondeur du graphe dual (appel sur PProfGD)
    void PProfGD (int i, int* t); // Parcours en profondeur du graphe dual (recursif)


    void algoDijkstra (int x); // Calcule les plus courts chemins à partir de x


    /* Accesseurs */
    int getTaille();
    void setTaille (int t);
    void setSummitEtat (int i, int e);
    void setSummitNom (int i, string s);
    void setSummitNum (int i, int n);
    void setSummitId (int i, int id);
    void setSummitFreq (int i, int f);
    void setSummitSize(int t);
    int getSummitSize();

    vector <s_sommet>* recupTabSommet();

    int getIndice (int x); // Renvoie l'indice du tableau correspondant a l'id x
    int getNbCFC (); // Renvoie le nombre de composantes fortement connexes
    string getCFC (); // Renvoie les CFC
    char* getCheminMin(int y);

};

#endif
