/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : AdjList.cpp
OBJET            : representation de graphes sous forme de liste de voisins
--------------------------------------------------------------------------------
DATE DE CREATION : 30/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#include "../headers/AdjList.h"

/*=================================
Constructeurs et Desctructeurs
===================================*/
AdjList::AdjList () : m_size(0){
}

AdjList::~AdjList(){
}


/*=================================
Initialisation
===================================*/
void AdjList::initData (vector< s_summit >& v, map< int, vector< int > >& f, map< int, vector< int > >& df, map< int, int >& ItR){
  m_size = v.size();
  m_graph = f;
  m_graphDual = df;
  m_idToRank = ItR;
  m_tabSummit = v;
}

vector< s_summit > AdjList::initCFC () {
  DFS();
  sortDescEnd();
  DFSD();
  sortAscBeg();

  return m_tabSummit;
}



/*=================================
Resolution
===================================*/
void AdjList::DFS () { // Parcours en profondeur du graphe (appel sur PProfG)
    int temps;
    map < int, vector <int> >::iterator it;

    temps = 0;


    for (it = m_graph.begin(); it != m_graph.end(); it++) {

        if (m_tabSummit[m_tabSummit[m_idToRank[it->first]].num].status == -1 ) { // ancienne version : s->getStructSommet(s->getStructSommet(i).num).etat
            DFSHidden(it->first, temps);
        }
    }
}


void AdjList::DFSHidden (int i, int& t) { // Parcours en profondeur du graphe (recursif)
    int j;
    int token;

    token = m_idToRank[i]; // La case de m_tabSummit où se trouve le nombre i

    m_tabSummit[token].status = 0;
      /* On marque l'etat atteint */
    t++;
    m_tabSummit[token].beg = t;
      /* On le marque comme le t-ieme rencontre */


    for ( j = 0; j < (int) m_graph[i].size(); j++){
        if (m_tabSummit[ m_idToRank[ m_graph[i][j] ] ].status == -1) {
          /* Si le voisin avec l'id m_graph[i][j] n'a pas ete explore */
            DFSHidden(m_graph[i][j], t);
        }
    }

    m_tabSummit[token].status = 1;
      /* Une fois termine, on marque l'etat comme explore */
    t++;
    m_tabSummit[token].end = t;
      /* On marque le temps qu'il a fallu pour l'explorer */
}


void AdjList::DFSD () { // Parcours en profondeur du graphe dual (appel sur PProfGD)
    int i;
    int temps;
    map < int, vector <int> >::iterator it;

    temps = 0;

    for (i = 0; i < (int) m_size; i++) {
      /* Reinitialisation des donnees */
      m_tabSummit[i].status = -1;
      m_tabSummit[i].beg = 0;
      m_tabSummit[i].end = 0;
    }

    for (i = 0; i < (int) m_size; i++) {
        if (m_tabSummit[ m_tabSummit[i].num ].status == -1) {
            DFSDHidden(m_tabSummit[ m_tabSummit[i].num ].id, temps);
        }
    }
}

void AdjList::DFSDHidden (int i, int& t) { // Parcours en profondeur du graphe dual (recursif)
    int j;
    int token;

    token = m_idToRank[i]; // La case de m_tabSummit où se trouve le nombre i

    m_tabSummit[token].status = 0;
      /* On marque l'etat atteint */
    t++;
    m_tabSummit[token].beg = t;
      /* On le marque comme le t-ieme rencontre */


    for ( j = 0; j < (int) m_graphDual[i].size(); j++){
        if (m_tabSummit[ m_idToRank[ m_graphDual[i][j] ] ].status == -1) {
            DFSDHidden(m_graphDual[i][j], t);
        }
    }

    m_tabSummit[token].status = 1;
      /* Une fois termine, on marque l'etat comme explore */
    t++;
    m_tabSummit[token].end = t;
      /* On marque le temps qu'il a fallu pour l'explorer */

}


void AdjList::sortDescEnd() {
  int i;
  int tmp, continuer;

  tmp = 0;
  continuer = 1;


  while (continuer) {
      continuer--;
      for (i = 0; i < (int) m_size-1; i++) {
          if (m_tabSummit[i].end < m_tabSummit[i+1].end) {
              tmp = m_tabSummit[i+1].end;
              m_tabSummit[i+1].end = m_tabSummit[i].end;
              m_tabSummit[i].end = tmp;

              tmp = m_tabSummit[i+1].beg;
              m_tabSummit[i+1].beg = m_tabSummit[i].beg;
              m_tabSummit[i].beg = tmp;

              tmp = m_tabSummit[i+1].num;
              m_tabSummit[i+1].num = m_tabSummit[i].num;
              m_tabSummit[i].num = tmp;

              continuer++;
          }
      }
  }
}

void AdjList::sortAscBeg() {
  sort(m_tabSummit.begin(), m_tabSummit.end(), orderBeg);
}

/*=================================
Dijkstra
===================================*/

vector< s_summit > AdjList::initDist (int x) {
  /* Variables */
    int i;
    int token;
    int n; // id temporaire
    int nbExplore; // nombre de sommet explore
    vector< int >::iterator it;


  /* Source Unique Initialisation */
    for (i = 0; i < (int) m_size; i++) {
        m_tabSummit[i].status = -1;
        m_tabSummit[i].beg = INT_MAX;
        m_tabSummit[i].end = -1;
    }

    m_tabSummit[x].beg = 0;
    nbExplore = 0;


    while (nbExplore < (int) m_size) { // F != null
      n = extractMin(); // x = ExtraireMin(F)

      if (m_tabSummit[m_idToRank[n]].status == -1) {
        // Si l'etat n'a pas encore ete explore
        m_tabSummit[m_idToRank[n]].status = 0;  // F = F - x
        nbExplore++;

        for ( i = 0; i < (int) m_graph[n].size(); i++){ // Pour tous les amis de n
          token = m_idToRank[m_graph[n][i]];
            if (m_tabSummit[token].beg > m_tabSummit[m_idToRank[n]].beg + m_tabSummit[token].freq) { // Relacher
                m_tabSummit[token].beg = m_tabSummit[m_idToRank[n]].beg + m_tabSummit[token].freq;

                m_tabSummit[token].end = m_idToRank[n]; // On indique que le pere le plus proche de i est n
            }

        }

      } else {
        nbExplore++;
      }

    }

    return m_tabSummit;
}


int AdjList::extractMin() {
    int i, imin;
    int valmin;

    valmin = INT_MAX;
    imin = 0;
    for (i = 0; i < (int) m_size; i++) {
        if ((m_tabSummit[i].beg < valmin) && (m_tabSummit[i].status == -1)) {
            valmin = m_tabSummit[i].beg;
            imin = m_tabSummit[i].id;
        }
    }
/*
    if (valmin != INT_MAX)
        return imin;
    else
        return 0;*/
    return imin;
}


/*
void AdjList::algoDijkstra (int x) { // Calcule les plus courts chemins à partir de l'id x
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
*/

/*=================================
Affichage
===================================
void AdjList::printListeAdj () {
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

void AdjList::printListeAdjD () {
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

void AdjList::printSummits () {
    m_summit->print();
}
*/
/*=================================
Accesseurs
===================================*//*
int AdjList::getTaille(){
    return m_tailleGraph;
}


void AdjList::setTaille(int t){
    m_tailleGraph = t;
    setSummitSize(t);
}

void AdjList::setSummitEtat (int i, int e) {
    m_summit->setEtat(i, e);
}

void AdjList::setSummitNom (int i, string s) {
    m_summit->setNom(i, s);
}

void AdjList::setSummitNum (int i, int n) {
    m_summit->setNum(i, n);
}

void AdjList::setSummitId (int i, int id) {
    m_summit->setId(i, id);
}

void AdjList::setSummitFreq (int i, int f) {
    m_summit->setFreq(i, f);
}

void AdjList::setSummitSize (int t) {
    m_summit->setTaille(t);
}

int AdjList::getSummitSize () {
    return m_summit->getTaille();
}



vector <s_sommet>* AdjList::recupTabSommet(){
  return m_summit->getTabSommet();
}




int AdjList::getIndice (int x) {
    return m_summit->getIndice(x);
}

int AdjList::getNbCFC (){
    return m_summit->getNbCFC();
}

string AdjList::getCFC (){
    return m_summit->getCFC();
}

char* AdjList::getCheminMin (int y) {
    return m_summit->getCheminMin(y);
}
*/
