/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : AdjMat.cpp
OBJET            : matrice d'adjacence
--------------------------------------------------------------------------------
DATE DE CREATION : 30/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#include "../headers/AdjMat.h"


/*=================================
Constructeurs et Desctructeurs
===================================*/
AdjMat::AdjMat () : m_size(0) {
}

AdjMat::~AdjMat () {
}


/*=================================
Initialisation
===================================*/
void AdjMat::initData (vector< s_summit >& v, vector < vector < int > >& m) {
  m_size = v.size();
  m_tabSummit = v;
  m_graph = m;
}

vector< s_summit > AdjMat::initCFC () {
  DFS();
  sortDescEnd();
  DFSD();
  sortAscBeg();

  return m_tabSummit;
}



/*=================================
Parcours en profondeur
===================================*/
void AdjMat::DFS () {
    int i;
    int temps;

    temps = 0;


    for (i = 0; i < (int) m_size; i++) {
      /* Pour tous les points */
        if ( m_tabSummit[m_tabSummit[i].num].status == -1 ){
          /* Si l'etat est marque comme non atteint, on fait un appel recursif */
          DFSHidden(m_tabSummit[i].num, temps);
        }
    }
}

void AdjMat::DFSHidden (int i, int& t) { // Parcours en profondeur du graphe (recursif)
    int j;


    m_tabSummit[i].status = 0;
      /* On marque l'etat atteint */
    t++;
    m_tabSummit[i].beg = t;
      /* On le marque comme le t-ieme rencontre */

    for (j = 0; j < (int) m_size; j++) {
        if ((m_graph[i][j]) && (m_tabSummit[j].status == -1)) {
          /* Si on trouve un successeur non atteint, on fait un appel recursif */
            DFSHidden(j, t);
        }
    }

    m_tabSummit[i].status = 1;
      /* Une fois termine, on marque l'etat comme explore */
    t++;
    m_tabSummit[i].end = t;
      /* On marque le temps qu'il a fallu pour l'explorer */
}

void AdjMat::DFSD () {
    int i;
    int temps;

    temps = 0;

    for (i = 0; i < (int) m_size; i++) {
      /* Reinitialisation des donnees */
      m_tabSummit[i].status = -1;
      m_tabSummit[i].beg = 0;
      m_tabSummit[i].end = 0;
    }

    for (i = 0; i < (int) m_size; i++) {
      /* Parcours dans le nouvel ordre */
        if (m_tabSummit[m_tabSummit[i].num].status == -1) {
          DFSDHidden(m_tabSummit[i].num, temps);
        }
    }
}

void AdjMat::DFSDHidden (int i, int& t) { // Parcours en profondeur du graphe dual (recursif)
    int j;

    m_tabSummit[i].status = 0;
      /* On marque l'etat atteint */
    t++;
    m_tabSummit[i].beg = t;
      /* On le marque comme le t-ieme rencontre */

    for (j = 0; j < (int) m_size; j++) {
        if ((m_graph[j][i]) && (m_tabSummit[j].status == -1)) { // Successeur non atteint
            DFSDHidden(j, t);
        }
    }

    m_tabSummit[i].status = 1;
      /* Une fois termine, on marque l'etat comme explore */
    t++;
    m_tabSummit[i].end = t;
      /* On marque le temps qu'il a fallu pour l'explorer */
}


void AdjMat::sortDescEnd() {
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

void AdjMat::sortAscBeg() {
  sort(m_tabSummit.begin(), m_tabSummit.end(), orderBeg);
}


void AdjMat::printMat () { // Affiche la matrice adjacente
    int i, j;


    cout << endl;
    for (i = 0; i < (int) m_size; i++) {
        for (j = 0; j < (int) m_size; j++) {
            cout << m_graph[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}







vector< s_summit > AdjMat::initDist (int x) {
  /* Variables */
    int i;
    int n, nbExplore; // nombre de sommet explore
    vector <int>::iterator it;

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

      if (m_tabSummit[n].status == -1) {
        m_tabSummit[n].status = 0;  // F = F - x
        nbExplore++;

        for ( i = 0; i < (int) m_size; i++){
          if (m_graph[n][i]) {
            if (m_tabSummit[i].beg > m_tabSummit[n].beg + m_tabSummit[i].freq) { // Relacher
                m_tabSummit[i].beg = m_tabSummit[n].beg + m_tabSummit[i].freq;

                m_tabSummit[i].end = n; // On indique que le pere le plus proche de i est n
            }
          }
        }
      } else {
        nbExplore++;
      }
    }

    return m_tabSummit;
}

int AdjMat::extractMin() {
    int i, imin;
    int valmin;

    valmin = INT_MAX;
    imin = 0;
    for (i = 0; i < (int) m_size; i++) {
        if ((m_tabSummit[i].beg < valmin) && (m_tabSummit[i].status == -1)) {
            valmin = m_tabSummit[i].beg;
            imin = i;
        }
    }

/*
    if (valmin != INT_MAX)
        return imin;
    else
        return 0;*/
    return imin;
}
