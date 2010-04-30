/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : liste_voisins.cpp
OBJET            : representation de graphes sous forme de liste de voisins
--------------------------------------------------------------------------------
DATE DE CREATION : 13/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#include "../h/ListeVoisins.h"

/*=================================
Constructeurs et Desctructeurs
===================================*/
ListeVoisins::ListeVoisins () : m_tailleGraph(0){
    m_summit = new Sommet();
}

ListeVoisins::~ListeVoisins(){
    delete m_summit;
}


/*=================================
Methodes
===================================*/
ListeVoisins ListeVoisins::toDual(){

 return *(this);
}

void ListeVoisins::iniList(UserData* u){
    map < int, Friends >::iterator it_UserData;
    map < int, Friends > maptemp;
    int i;

    maptemp = (*u).get_listFriends();
/*
    //On recopie dans le map (m_graph) la liste de voisins que l'on obtient a partir du userData
    for (it_UserData = u.get_listPerson().begin(); it_UserData != u.get_listPerson().end(); it_UserData++){
        m_graph[it_UserData->first] = it_UserData->second.get_listLink() ;
        m_tailleGraph++;
    }*/

    i = 0;
    for (it_UserData = maptemp.begin(); it_UserData != maptemp.end(); it_UserData++){
      idPosition[it_UserData->first] = i;
      m_graph[it_UserData->first] = it_UserData->second.get_listLink();
      m_graphDual[it_UserData->first] = it_UserData->second.get_listDualLink();
      m_tailleGraph++; i++;

    }

    m_summit->setTaille(m_tailleGraph);
}


void ListeVoisins::addSummit(int i, int x){
    m_graph[i].push_back(x); // On rajoute le sommet x dans les voisins de i
    m_graphDual[x].push_back(i); // On fait l'inverse pour obtenir le graphe dual
}


/*=================================
Affichage
===================================*/
void ListeVoisins::printListeAdj () {
    int i;
    vector <int>::iterator it;
    for (i = 0; i < m_tailleGraph; i++) {
        printf("%d ", i+1);
        for(it = m_graph[i].begin(); it < m_graph[i].end(); it++){
            cout << "-> " << ( (*it) + 1 );
        }
        cout << endl;
    }
    printf("\n");
}

void ListeVoisins::printListeAdjD () {
    int i;
    vector <int>::iterator it;
    for (i = 0; i < m_tailleGraph; i++) {
        printf("%d ", i+1);
        for(it = m_graphDual[i].begin(); it < m_graphDual[i].end(); it++){
            cout << "-> " << ( (*it) + 1 );
        }
        cout << endl;
    }
    printf("\n");
}

void ListeVoisins::printSummits () {
    m_summit->print();
}


/*=================================
Resolution
===================================*/
void ListeVoisins::PPG (UserData* u) { // Parcours en profondeur du graphe (appel sur PProfG)
    int i;
    int temps;
    map < int, vector <int> >::iterator it;
    vector <s_sommet> newOrderTab;


    temps = 0;
    m_summit->iniDataSommet(u, 'l');
    // m_summit->iniEtatSommet();

/*
    for (it = m_graph.begin(); it != m_graph.end(); it++) {
        if (m_summit->getEtat(getIndice(it->first)) == -1) { // ancienne version : s->getStructSommet(s->getStructSommet(i).num).etat
            PProfG(it->first, &temps);
        }
    }*/

    i = 0;
    for (it = m_graph.begin(); it != m_graph.end(); it++) {
        if (m_summit->getEtat(i) == -1) { // ancienne version : s->getStructSommet(s->getStructSommet(i).num).etat
            PProfG(it->first, &temps);
        }
        i++;
    }
/*
    m_summit->triDecroissant();*/

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
    //m_summit->printsommet(); cout << endl ;

    PPGD(u, &newOrderTab);

}


void ListeVoisins::PProfG (int i, int* t) { // Parcours en profondeur du graphe (recursif)
    int j;
    int pointActuel;

    pointActuel = idPosition[i]; // La case où se trouve le nombre i

    m_summit->setEtat(pointActuel, 0); // Etat atteint
    (*t)++;
    m_summit->setDeb(pointActuel, *t);

/*
    for ( j = 0; j != m_graph[x].size(); j++){
        if (m_summit->getEtat(getIndice(m_graph[x][j])) == -1) {
            PProfG(m_graph[i][j], , t);
        }
    }*/

    for ( j = 0; j != m_graph[i].size(); j++){
        if (m_summit->getEtat(idPosition[(m_graph[i][j])]) == -1) {
            PProfG(m_graph[i][j], t);
        }
    }

    m_summit->setEtat(pointActuel,1); // Etat explore
    (*t)++;
    m_summit->setFin(pointActuel,*t);
}


//void ListeVoisins::PPGD () { // Parcours en profondeur du graphe dual (appel sur PProfGD)
void ListeVoisins::PPGD (UserData* u, vector <s_sommet>* V) { // Parcours en profondeur du graphe dual (appel sur PProfGD)
    int i;
    int temps;
    map < int, vector <int> >::iterator it;

    temps = 0;
    m_summit->iniEtatSommet();
/*
    for (it = m_graphDual.begin(); it != m_graphDual.end(); it++) {
        if (m_summit->getEtat(getIndice(it->first)) == -1) {
            PProfGD(it->first, &temps);
        }
    }*/

    for (i = 0; i != m_tailleGraph; i++) {
        if (m_summit->getEtat((*V)[i].num) == -1) {

            PProfGD((*V)[i].id, &temps);
        }
    }

    m_summit->triCroissant();

}

void ListeVoisins::PProfGD (int i, int* t) { // Parcours en profondeur du graphe dual (recursif)
    int j;
    int pointActuel;

    pointActuel = idPosition[i]; // La case où se trouve le nombre i

    m_summit->setEtat(pointActuel, 0); // Etat atteint
    (*t)++;
    m_summit->setDeb(pointActuel ,*t);
/*
    for ( j = 0; j < m_graphDual[i].size(); j++){
        if (m_summit->getEtat(getIndice(m_graphDual[i][j])) == -1) {
            PProfGD(m_graphDual[i][j], t);
        }
    }*/

    for ( j = 0; j < m_graphDual[i].size(); j++){
        if (m_summit->getEtat(idPosition[(m_graphDual[i][j])]) == -1) {
            PProfGD(m_graphDual[i][j], t);
        }
    }

    m_summit->setEtat(pointActuel, 1); // Etat explore
    (*t)++;
    m_summit->setFin(pointActuel, *t);

}


/*=================================
Dijkstra
===================================*/
void ListeVoisins::algoDijkstra (int x) { // Calcule les plus courts chemins à partir de l'id x
    int i;
    int n;
    int nbExplore; // nombre de sommet explore
    vector <int>::iterator it;


    //m_summit->iniEtatSommet(); // F = X
    for (i = 0; i < m_tailleGraph; i++) { // Source Unique Initialisation
        m_summit->setEtat(i, -1);
        m_summit->setDeb(i, INT_MAX);
        m_summit->setFin(i, -1);
    }
    m_summit->triId();


    nbExplore = 0;

    x = idPosition[x];
    // z = x;
    m_summit->setDeb(x, 0);

    //while (m_summit->nonExplore() == true) { // F != null
    while (nbExplore < m_tailleGraph) { // F != null
        x = m_summit->getIndiceMinDeb(); // x = ExtraireMin(F)
        m_summit->setEtat(x, 0); nbExplore++; // F = F - x

        for ( it = m_graph[x].begin(); it < m_graph[x].end(); it++){
            if (m_summit->getDeb(*it) > m_summit->getDeb(x) + m_summit->getFreq(*it)) { // Relacher
                //printf("relacher(%d, %d) : %d > %d + %d => d(%d) = %d\n", d[x].id, d[y].id, d[y].deb, d[x].deb, d[y].freq, d[y].id, d[x].deb+d[y].freq);
                m_summit->setDeb(*it, m_summit->getDeb(x) + m_summit->getFreq(*it));

                x = getIndice(m_summit->getId(x));
                m_summit->setFin(*it, x);
            }
        }

    }
}


/*=================================
Accesseurs
===================================*/
int ListeVoisins::getTaille(){
    return m_tailleGraph;
}


void ListeVoisins::setTaille(int t){
    m_tailleGraph = t;
    setSummitSize(t);
}

void ListeVoisins::setSummitEtat (int i, int e) {
    m_summit->setEtat(i, e);
}

void ListeVoisins::setSummitNom (int i, string s) {
    m_summit->setNom(i, s);
}

void ListeVoisins::setSummitNum (int i, int n) {
    m_summit->setNum(i, n);
}

void ListeVoisins::setSummitId (int i, int id) {
    m_summit->setId(i, id);
}

void ListeVoisins::setSummitFreq (int i, int f) {
    m_summit->setFreq(i, f);
}

void ListeVoisins::setSummitSize (int t) {
    m_summit->setTaille(t);
}

int ListeVoisins::getSummitSize () {
    return m_summit->getTaille();
}



vector <s_sommet>* ListeVoisins::recupTabSommet(){
  return m_summit->getTabSommet();
}




int ListeVoisins::getIndice (int x) {
    return m_summit->getIndice(x);
}

int ListeVoisins::getNbCFC (){
    return m_summit->getNbCFC();
}

string ListeVoisins::getCFC (){
    return m_summit->getCFC();
}

char* ListeVoisins::getCheminMin (int y) {
    return m_summit->getCheminMin(y);
}
