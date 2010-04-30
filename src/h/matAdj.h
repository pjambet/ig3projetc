/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : matAdj.h
OBJET            : matrice d'adjacence
--------------------------------------------------------------------------------
DATE DE CREATION : 12/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#ifndef MATADJ_H_INCLUDED
#define MATADJ_H_INCLUDED

#include <iostream>
#include <string>
#include "sommet.h"
#include "UserData.h"

class MatAdj{

    private:

    int m_size;
    int** m_Matrix;
    Sommet* m_summit;

    public:

    MatAdj();
    MatAdj(int s);
    ~MatAdj();

    void iniMat (); // Renvoie la matrice d'adjacence
    void iniMat (UserData* u); // Renvoie la matrice d'adjacence
    void printMat (); // Affiche la matrice adjacente

    void addSummit(int x, int y); // Ajoute le sommet de coordonnées x:y dans la matrice

    void PPG (UserData* u); // Parcours en profondeur du graphe (appel sur PProfG)
    void PProfG (int i, int* t); // Parcours en profondeur du graphe (recursif)

    void PPGD (UserData* u, vector <s_sommet>* V); // Parcours en profondeur du graphe dual (appel sur PProfGD)
    //void PPGD (); // Parcours en profondeur du graphe dual (appel sur PProfGD)
    void PProfGD (int i, int* t); // Parcours en profondeur du graphe dual (recursif)

    int getTMin (int x, int y); // Renvoie le temps min pour aller de x à y
    void getTMinProf (int x, int y, int* t, int temp); // Parcours en profondeur

    // Accesseurs
    int getSize();
    void setSize(int s);
    vector <s_sommet>* recupTabSommet();

    // Accesseurs sur Sommet
    void setSummitEtat (int i, int e);
    void setSummitNom (int i, string s);
    void setSummitNum (int i, int n);
    void setSummitId (int i, int id);
    void setSummitFreq (int i, int f);
    void setSummitSize(int t);
    int getSummitSize();

    int getIndice (int x); // Renvoie l'indice du tableau correspondant a l'id x
    int getNbCFC (); // Renvoie le nombre de composantes fortement connexes
    string getCFC (); // Renvoie les CFC
    void printCFC();

};


#endif // MATADJ_H_INCLUDED
