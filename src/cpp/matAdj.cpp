/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : matAdj.cpp
OBJET            : matrice d'adjacence
--------------------------------------------------------------------------------
DATE DE CREATION : 12/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */
#include "../h/matAdj.h"

MatAdj::MatAdj () : m_size(0), m_Matrix(NULL){
    m_summit = new Sommet();
    m_Matrix = (int**) malloc (m_size*sizeof(int*));
}


MatAdj::MatAdj (int s) : m_size(s) {
    int i = 0, j = 0;
    m_Matrix = new int*[m_size];
    for (i = 0; i < m_size; i++){
        m_Matrix[i] = new int[m_size];
    }
    for (i = 0; i < m_size; i++) {
        for (j = 0; j < m_size; j++) {
            m_Matrix[j][i] = 0;
        }
    }
}



MatAdj::~MatAdj () {
    int i;

    for (i = 0; i < m_size; i++) {
      delete[] (m_Matrix[i]);
    }
    delete (m_Matrix);
}


void MatAdj::iniMat () { // Renvoie la matrice d'adjacence
    int i, j;
    m_Matrix = new int*[m_size];
    for (i = 0; i < m_size; i++){
        m_Matrix[i] = new int[m_size];
    }
    for (i = 0; i < m_size; i++) {
        for (j = 0; j < m_size; j++) {
            m_Matrix[j][i] = 0;
        }
    }
}

void MatAdj::iniMat (UserData* u) {
    //On recopie dans la matrice la liste de voisins que l'on obtient a partir du userData
    m_Matrix = (*u).get_matFriends();
    m_size = (*u).get_nbPerson();

    m_summit->setTaille(m_size);
}

void MatAdj::printMat () { // Affiche la matrice adjacente
    int i, j;
    cout << endl;
    for (i = 0; i < m_size; i++) {
        for (j = 0; j < m_size; j++) {
            cout << m_Matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}


void MatAdj::addSummit (int x, int y) {
    m_Matrix[x][y] = 1;
}





void MatAdj::PPG (UserData* u) { // Parcours en profondeur du graphe (appel sur PProfG)
    int i;
    int temps = 0;
    vector <s_sommet> newOrderTab;

    m_summit->iniDataSommet(u, 'm');
    for (i = 0; i < m_size; i++) {
        if ( m_summit->getEtat(m_summit->getNum(i)) == -1 ){ // version c de quentin : s[s[i].num].etat == -1)
        PProfG(i, &temps);
        }
    }

    newOrderTab = m_summit->copyTabSommet();
      /* On fait une copie du tableau */
/*
    for (int i = 0; i < newOrderTab.size(); i++) {
      newOrderTab[i].id = i;
    }*/

      /* On renote l'ordre des elements en ecrasant ces id inutiles */
    //m_summit->triDecroissant();
    sort(newOrderTab.rbegin(), newOrderTab.rend(), orderFin);
     /* On trie le tableau en decroissant par rapport aux finaux
        Le nouvel ordre a suivre sera donc donne par les id de ce vecteur */

    PPGD(u, &newOrderTab);
}

void MatAdj::PProfG (int i, int* t) { // Parcours en profondeur du graphe (recursif)
    int j;
    m_summit->setEtat(i, 0); // Etat atteint
    (*t)++;
    m_summit->setDeb(i, *t);
    for (j = 0; j < m_size; j++) {
        if ((m_Matrix[i][j]) && (m_summit->getEtat(j) == -1)) { // Successeur non atteint
            PProfG(j, t);
        }
    }
    m_summit->setEtat(i, 1); // Etat explore
    (*t)++;
    m_summit->setFin(i, *t);

}

void MatAdj::PPGD (UserData* u, vector <s_sommet>* V) { // Parcours en profondeur du graphe dual (appel sur PProfG)
//void MatAdj::PPGD () { // Parcours en profondeur du graphe dual (appel sur PProfG)
    int i;
    int temps;

    temps = 0;
    m_summit->iniEtatSommet();
    for (i = 0; i < m_size; i++) {
        if (m_summit->getEtat((*V)[i].num) == -1) {
          PProfGD((*V)[i].num, &temps);
        }
    }

//m_summit->printsommet();
    m_summit->triCroissant();
}

void MatAdj::PProfGD (int i, int* t) { // Parcours en profondeur du graphe dual (recursif)
    int j;

    m_summit->setEtat(i, 0); // Etat atteint
    (*t)++;
    m_summit->setDeb(i, *t);

    for (j = 0; j < m_size; j++) {
        if ((m_Matrix[j][i]) && (m_summit->getEtat(j) == -1)) { // Successeur non atteint
            PProfGD(j, t);
        }
    }

    m_summit->setEtat(i, 1); // Etat explore
    (*t)++;
    m_summit->setFin(i,*t);
}




int MatAdj::getTMin (int x, int y) { // Renvoie le temps min pour aller de x à y
    int t;
    int* tmin = &t;
    x = m_summit->getIndice(x);
    y = m_summit->getIndice(y);
    t = - m_summit->getFreq(x);
    m_summit->iniEtatSommet();
    getTMinProf(x, y, tmin, t);
    return *tmin;
}

void MatAdj::getTMinProf (int x, int y, int* t, int temp) { // Parcours en profondeur
    int j;
    m_summit->setEtat(x,0); // Etat atteint
    cout << "s = " << (x + 1) << " (" << m_summit->getId(x) << "), t = " << temp << endl;
    temp += m_summit->getFreq(x);
    if (x == y) {
        *t = temp;
    } else {
        for (j = 0; j < m_size; j++) {
            if ((m_Matrix[x][j] > 0) && (m_summit->getEtat(j) == -1)) { // Successeur non atteint
                getTMinProf(j, y, t, temp);
            }
        }
    }
    m_summit->setEtat(x, 1); // Etat explore
}

int MatAdj::getSize () {
    return m_size;
}

void MatAdj::setSize (int s) {
    m_size = s;
    int i = 0, j = 0;
    m_Matrix = new int*[m_size];
    for (i = 0; i < m_size; i++){
        m_Matrix[i] = new int[m_size];
    }
    for (i = 0; i < m_size; i++) {
        for (j = 0; j < m_size; j++) {
            m_Matrix[j][i] = 0;
        }
    }
}

vector <s_sommet>* MatAdj::recupTabSommet(){
  return m_summit->getTabSommet();
}

void MatAdj::setSummitEtat (int i, int e) {
    m_summit->setEtat(i, e);
}

void MatAdj::setSummitNom (int i, string s) {
    m_summit->setNom(i, s);
}

void MatAdj::setSummitNum (int i, int n) {
    m_summit->setNum(i, n);
}

void MatAdj::setSummitId (int i, int id) {
    m_summit->setId(i, id);
}

void MatAdj::setSummitFreq (int i, int f) {
    m_summit->setFreq(i, f);
}

void MatAdj::setSummitSize (int t) {
    m_summit->setTaille(t);
}

int MatAdj::getSummitSize () {
    return m_summit->getTaille();
}

int MatAdj::getIndice (int x) {
    return m_summit->getIndice(x);
}

int MatAdj::getNbCFC(){
    return m_summit->getNbCFC();
}

string MatAdj::getCFC(){
    return m_summit->getCFC();
}

void MatAdj::printCFC(){
  m_summit->printCFC();
}
