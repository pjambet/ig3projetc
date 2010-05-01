/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : Graph.h
OBJET            : Structure de graphe
--------------------------------------------------------------------------------
DATE DE CREATION : 27/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#include "../headers/Graph.h"

/*=================================
Constructeurs et Desctructeurs
===================================*/
Graph::Graph (): m_sizeGraph(0), m_nbCFC(0), m_nbDist(0) {
}

Graph::~Graph () {
}


/*=================================
Initialisation
===================================*/
void Graph::initGraph (string& fileNameIn) {
  clearGraph();

  /* Variables */
    /* Generales */
    int i, j;
    FILE* f_in;

    /* Etape 2 */
    s_summit s;
      char nameTemp[255];

    /* Etape 3 */
    int unsigned nbConnections;

    /* Etape 4 */
    int x, y;
    map< int, vector < int > >::iterator itFriends;

    /* Etape 6 */
    map< int, vector< int > >::iterator itDist;


  /* Corps de la fonction */
  f_in = fopen(fileNameIn.c_str(), "r");

  if (f_in == NULL) {
    cerr << "Erreur - Impossible d'ouvrir le fichier ou fichier inexistant." << endl;

  } else {
    /* Etape 1 - Lecture du nombre de personne*/
    fscanf(f_in, "%d\n", &m_sizeGraph);

    /* Etape 2 - Lecture des personnes*/
    s.status = -1;
    s.beg = 0;
    s.end = 0;
    s.important = false;

    for (i = 0; i < (int) m_sizeGraph; i++) {
      fscanf(f_in, "%[^,], %d, %d\n", nameTemp, &s.id, &s.freq);

      s.name = nameTemp;
      s.num = i;
      m_tabSummit.push_back(s);

      m_idToRank[s.id] = i;
    }

    /* Etape 3 - Lecture du nombre de relation */
    fscanf(f_in, "%d\n", &nbConnections);

    /* Etape intermediaire : Definition de la structure a adopter */
    m_structGraph = chooseStruct();

    /* Etape 4 - Stocker les amis en fonction de la structure choisie */
    if (m_structGraph == 'm') {
      /* Structure de matrice */
      /* Initialisation de la matrice */
      m_matFriends.resize(m_sizeGraph);
        for (i = 0; i < (int) m_sizeGraph; i++) {
          m_matFriends[i].resize(m_sizeGraph);
        }

      for (i = 0; i < (int) m_sizeGraph; i++) {
        for (j = 0; j < (int) m_sizeGraph; j++) {
          m_matFriends[i][j] = 0;
        }
      }

      /* Stocke les conversions entre rang et id */
      for (i = 0; i < (int) m_tabSummit.size(); i++) {
        m_idToRank[m_tabSummit[i].id] = i;
      }

      /* Lecture des donnees et stockage */
      for (i = 0; i < (int) nbConnections; i++){
        fscanf(f_in, "%d, %d\n", &x, &y);
        m_matFriends[m_idToRank[x]][m_idToRank[y]] = 1;
      }

    } else {
      /* Structure de liste */
      for (i = 0; i < (int) nbConnections; i++){
        fscanf(f_in, "%d, %d\n", &x, &y);

        /* On ajoute a x un ami */
        m_listFriends[x].push_back(y);

        /* On ajoute a y quelqu'un qui lui fait confiance */
        m_listDualFriends[y].push_back(x);
      }

        /* Tri de tous les amis
        for (itFriends = listFriends.begin() ; itFriends != listFriends.end(); itFriends++) {
          sort( m_listFriends[(*itFriends)].second.begin(), m_listFriends[(*itFriends)].second.end() );
          sort( m_listDualFriends[(*itFriends)].second.begin(), m_listDualFriends[(*itFriends)].second.end() );
        }*/


    }

    /* Etape 5 - Lecture du nombre de question */
    fscanf(f_in, "%d\n", &m_nbDist);

    /* Etape 6 - Stockage des questions */
    for (i = 0; i < (int) m_nbDist; i++){
      fscanf(f_in, "%d -> %d\n", &x, &y);
      m_listQuestion[x].push_back(y);
    }

      /* Tri des questions
      for (itQuest = m_listQuestion.begin() ; itQuest != m_listQuestion.end(); itQuest++) {
          sort( (*itQuest).second.begin(), (*itQuest).second.end() );
      }*/

  }

  fclose(f_in);
}

void Graph::clearGraph () {
  m_sizeGraph = 0;
  m_tabSummit.clear();

  m_structGraph = 'x';

  m_listFriends.clear();
  m_listDualFriends.clear();

  m_idToRank.clear();
  m_matFriends.clear();

  m_nbCFC = 0;
  m_listCFC.clear();

  m_nbDist = 0;
  m_listQuestion.clear();
  m_listDist.clear();
  m_listPath.clear();
}


/*=================================
Recherche
===================================*/
bool Graph::isAnalysable() {
  return (m_sizeGraph != 0);
}


/*=================================
Recherche
===================================*/
void Graph::searchCFC () {
  int d, f; /* Reperes de debut et fin d'intervalle */
  int i;
  int unsigned cpt_CFC; /* Compteur de CFC*/
  vector <int > v;

  vector< s_summit > tabSummitTemp;
  AdjMat matrix;
  AdjList list;



  if (m_structGraph == 'm') {
    matrix.initData(m_tabSummit, m_matFriends);
    tabSummitTemp = matrix.initCFC();

  } else {
    list.initData(m_tabSummit, m_listFriends, m_listDualFriends, m_idToRank);
    tabSummitTemp = list.initCFC();

  }


  d = tabSummitTemp[0].beg;
  f = tabSummitTemp[0].end;
  cpt_CFC = 0;

  if (m_sizeGraph != 0) {
    cpt_CFC++;
    m_listCFC.push_back(v);
    m_listCFC[cpt_CFC-1].push_back(tabSummitTemp[0].id);

    for (i = 1; i < (int) m_sizeGraph; i++) {
      /* On regarde les autres sommets */
        if ((d < (tabSummitTemp[i].beg)) && (f > (tabSummitTemp[i].end))) {
          m_listCFC[cpt_CFC-1].push_back(tabSummitTemp[i].id);
        } else {
            d = tabSummitTemp[i].beg;
            f = tabSummitTemp[i].end;
            cpt_CFC++;

            m_listCFC.push_back(v);
            m_listCFC[cpt_CFC-1].push_back(tabSummitTemp[i].id);
        }
    }
  } else {
    cerr << "Erreur - Aucun graphe n'est ouvert !" << endl;
  }

  m_nbCFC = cpt_CFC;
}


void Graph::searchDistances () {
  int i;
  int token;

  map< int, vector< int > >::iterator it;
  vector < int > path;

  AdjMat matrix;
  AdjList list;


  /* Attention ! Delicat a comprendre */
  /* Etape 1 : Pour tous les points de depart distincts,
     on cherche et on stocke les plus courts chemins */
  if (m_structGraph == 'm') {
    matrix.initData(m_tabSummit, m_matFriends);
    for (it = m_listQuestion.begin(); it != m_listQuestion.end(); it++) {
      m_listDist[it->first] = matrix.initDist(m_idToRank[it->first]);
    }

  } else {
    list.initData(m_tabSummit, m_listFriends, m_listDualFriends, m_idToRank);
    for (it = m_listQuestion.begin(); it != m_listQuestion.end(); it++) {
      m_listDist[it->first] = list.initDist(m_idToRank[it->first]);
    }

  }

/* Etape 2 : A partir de la liste de question, pour chaque point de depart,
   On regarde les id des points où aller et on stocke le chemin inverse dans path
   On stockera ensuite ce chemin dans le multimap listPath avec le point de depart comme cle */
  for (it = m_listQuestion.begin(); it != m_listQuestion.end(); it++) {
    for (i = 0; i < (int) it->second.size(); i++) {
      /* i = l'id ou on veut aller a partir de it->first */
      path.clear();

      token = m_idToRank[it->second[i]];
      path.push_back(token);
      /* En meme temps, la distance de it->first a i est donnee par m_tabSummit[path[0]].beg */

    while (token != -1) {
      /* Tant qu'on n'est pas arrive a un pere "NULL", on remonte */
      token = m_listDist[it->first][token].end;
      path.push_back(token);
    }

    path.pop_back();
      /* On retire le dernier point qui est normalement -1 */

    m_listPath.insert(pair< int, vector< int > >(it->first, path));

    }
  }
}


/*=================================
Autres et optionnels
===================================*/
char Graph::chooseStruct () {
  return TEST;
}

void Graph::saveGraph (string& fileNameOut) {
  FILE* f_out;
  int i, j;
  multimap<int, vector< int > >::iterator itStart;


  f_out = fopen(fileNameOut.c_str(), "w+");

  /* Nombre de CFC */
  fprintf(f_out, "%d\n", m_nbCFC);

  /* CFC */
  for (i = 0; i < (int) m_listCFC.size(); i++) {
    for (j = 0; j < (int) m_listCFC[i].size()-1; j++) {
      fprintf(f_out, "%d, ", m_listCFC[i][j]);
    }
    fprintf(f_out, "%d\n", m_listCFC[i].back());
  }

  /* Chemins */
  fprintf(f_out, "%d\n", m_nbDist);

  for (itStart = m_listPath.begin(); itStart != m_listPath.end(); itStart++) {
    fprintf(f_out, "%d : ", m_listDist[itStart->first][itStart->second[0]].beg); /* = La distance */

    for (i = itStart->second.size()-1; i > 0; i--) {
      fprintf(f_out, "%d, ", m_listDist[itStart->first][itStart->second[i]].id);
    }
    fprintf(f_out, "%d\n", m_listDist[itStart->first][itStart->second[0]].id);
  }
  fclose(f_out);

}


/*=================================
Affichage
===================================*/
void Graph::printGraph () {
  int i, j;
  multimap<int, vector< int > >::iterator itStart;

  cout << "Rapport de graphe :" << endl << endl;
  cout << "Nombre de personnes : " << m_sizeGraph << endl;
  cout << "Personnes : " << endl;
  for (i = 0; i < (int) m_sizeGraph; i++) {
    printSummit(m_tabSummit[i]);
  }

  cout << endl;

  cout << "Nombre de CFC : " << m_nbCFC << endl;
  cout << "CFC : " << endl;

  for (i = 0; i < (int) m_listCFC.size(); i++) {
    cout << "{ ";
    for (j = 0; j < (int) m_listCFC[i].size(); j++) {
      cout << m_listCFC[i][j] << " ";
    }
    cout << "}" << endl;
  }

  cout << endl;

  cout << "Nombre de distances : " << m_nbDist << " " << endl;
  cout << "Distances : " << endl;

  for (itStart = m_listPath.begin(); itStart != m_listPath.end(); itStart++) {
    cout << m_listDist[itStart->first][itStart->second[0]].beg << " : "; /* = La distance */

    for (i = itStart->second.size()-1; i > 0; i--) {
      cout << m_listDist[itStart->first][itStart->second[i]].id << ", ";
    }
    cout << m_listDist[itStart->first][itStart->second[0]].id << endl;
  }
}
