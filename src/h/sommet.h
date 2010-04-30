/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : lscAdj.cpp
OBJET            : liste simplement chaînée d'adjacence
--------------------------------------------------------------------------------
DATE DE CREATION : 13/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <numeric>

#include "struct_sommet.h"
#include "UserData.h"

using namespace std;


class Sommet{
    /* Attributs */
    private :
    int m_tailleGraph;
    vector<s_sommet> m_tabSommet;

    public :
    /* Constructeurs & Destructeurs */
    Sommet();
    Sommet(int taille);
    ~Sommet();



    /* Methodes */
    void print (); // Affiche les informations des sommets
    void printCFC (); // Affiche les CFC

    void iniDataSommet(UserData* u, char s); // Initialise les sommets
    void iniEtatSommet (); // Initialise les etats des sommets

    void triDecroissant (); // Renvoie l'ordre de parcours de la matrice duale (trié par ordre décroissant des temps d'accès finaux)
    void triCroissant (); // Trie m_tabSommet par ordre croissant des debuts
    void triId(); // Trie m_tabSommet par ordre croissant des id

    int getIndice (int x); // Renvoie l'indice du tableau correspondant a l'id x
    int getIndiceMinDeb (); // Renvoie l'indice du plus petit d(x)
    s_sommet getStructSommet (int x); // Renvoie la struct_sommet(s_sommet) qui est a l'indice x du tableau m_tabSommet
    int getNbCFC (); // Renvoie le nombre de composantes fortement connexes
    string getCFC (); // Renvoie les CFC

    bool nonExplore (); // Renvoie vrai s'il reste un sommet non exploré
    char* getCheminMin (int y); // Renvoie le temps et le plus cours chemin jusqu'à y


    /* Accesseurs */
    vector<s_sommet>* getTabSommet ();
    //void setTabSommet (s_sommet* t);
    vector<s_sommet> copyTabSommet ();
    int getTaille ();
    void setTaille (int t);


    /* Accesseurs aux elements de la structure */
    /* Le parametre "i" correspond a l'indice du tableau m_tabSommet */
    void setEtat(int i, int e);
    int getEtat(int i);
    void setDeb(int i, int d);
    int getDeb(int i);
    void setFin(int i, int f);
    int getFin(int i);
    void setNum(int i, int n);
    int getNum(int i);
    void setNom(int i, string n);
    string getNom(int i);
    void setId(int i, int id);
    int getId(int i);
    void setFreq(int i, int f);
    int getFreq(int i);

    void printsommet();

};


#endif // SOMMET_H_INCLUDED
