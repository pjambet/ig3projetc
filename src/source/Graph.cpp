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
Graph::Graph (): m_sizeGraph(0), m_nbSCC(0), m_nbDist(0) {
  m_matFriends = new int*;
}

Graph::~Graph () {
  int i;

  if ((m_structGraph == 'm') && (m_sizeGraph)) {
    for (i = 0; i < (int) m_sizeGraph; i++) {
      delete[] m_matFriends[i];
    }
  }

  delete[] m_matFriends;
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
      char idTemp[30];

    /* Etape 3 */
    int unsigned nbConnections;

    /* Etape 4 */
    char x[30], y[30];
    int xRank, yRank;
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
      fscanf(f_in, "%[^,], %[^,], %d\n", nameTemp, idTemp, &s.freq);

      s.name = nameTemp;
      s.id = idTemp;
      s.num = i;
      m_tabSummit.push_back(s);

      m_idToRank[s.id] = i; // Stocke la relation entre l'id et son emplacement dans m_tabSummit
    }


    /* Etape 3 - Lecture du nombre de relation */
    fscanf(f_in, "%d\n", &nbConnections);


    /* Etape intermediaire : Definition de la structure a adopter */
    m_structGraph = chooseStruct();


    /* Etape 4 - Stocker les amis en fonction de la structure choisie */
    if (m_structGraph == 'm') {
      /* Structure de matrice */
      /* Initialisation de la matrice */

      m_matFriends = new int*[m_sizeGraph];
        for (i = 0; i < (int) m_sizeGraph; i++) {
          m_matFriends[i]= new int[m_sizeGraph];

          for (j = 0; j < (int) m_sizeGraph; j++) {
            m_matFriends[i][j] = 0;
          }
        }

      /* Lecture des donnees et stockage */
      for (i = 0; i < (int) nbConnections; i++){
        fscanf(f_in, "%[^,], %[^\n]\n", x, y);
        m_matFriends[m_idToRank[x]][m_idToRank[y]] = 1;
      }

    } else {

      m_listFriends.resize(m_sizeGraph);
      m_listDualFriends.resize(m_sizeGraph);

      /* Structure de liste */
      for (i = 0; i < (int) nbConnections; i++){
        fscanf(f_in, "%[^,], %[^\n]\n", x, y);

        xRank = m_idToRank[x];
        yRank = m_idToRank[y];

        /* On ajoute a x un ami */
        m_listFriends[xRank].push_back(yRank);

        /* On ajoute a y quelqu'un qui lui fait confiance */
        m_listDualFriends[yRank].push_back(xRank);
      }
    }


    /* Etape 5 - Lecture du nombre de question */
    fscanf(f_in, "%d\n", &m_nbDist);


    /* Etape 6 - Stockage des questions */
    for (i = 0; i < (int) m_nbDist; i++){
      fscanf(f_in, "%[^ ] -> %[^\n]\n", x, y);
        xRank = m_idToRank[x];
        yRank = m_idToRank[y];

      m_listQuestion[xRank].push_back(yRank);
    }
  }

  fclose(f_in);
}

void Graph::clearGraph () {
  int i;

  m_sizeGraph = 0;
  m_tabSummit.clear();

  m_idToRank.clear();


  m_listFriends.clear();
  m_listDualFriends.clear();


  if ((m_structGraph == 'm') && (m_sizeGraph)) {
    for (i = 0; i < (int) m_sizeGraph; i++) {
      delete[] m_matFriends[i];
    }
  }
  delete[] m_matFriends;


  m_nbSCC = 0;
  m_listSCC.clear();

  m_nbDist = 0;
  m_listQuestion.clear();
  m_listDist.clear();
  m_listPath.clear();

  m_structGraph = 'x';

}


char Graph::chooseStruct () {
  return TEST_STRUCT;
}


/*=================================
Recherche
===================================*/
bool Graph::isAnalysable() {
  return (m_sizeGraph != 0);
}


void Graph::searchSCC () {
  int d, f; /* Reperes de debut et fin d'intervalle */
  int i;
  int unsigned cpt_SCC; /* Compteur de CFC*/
  vector < int > v;

  vector< s_summit > tabSummitTemp;
  AdjMat matrix;
  AdjList list;



  if (m_structGraph == 'm') {
    matrix.initData(m_tabSummit, m_matFriends);
    tabSummitTemp = matrix.initSCC();

  } else {
    list.initData(m_tabSummit, m_listFriends, m_listDualFriends);
    tabSummitTemp = list.initSCC();
  }


  d = tabSummitTemp[0].beg;
  f = tabSummitTemp[0].end;
  cpt_SCC = 0;



  if (m_sizeGraph != 0) {
    cpt_SCC++;
    m_listSCC.push_back(v);
    m_listSCC[cpt_SCC-1].push_back(m_idToRank[tabSummitTemp[0].id]);

    m_tabSummit[m_idToRank[tabSummitTemp[0].id]].important = tabSummitTemp[0].important;

    for (i = 1; i < (int) m_sizeGraph; i++) {
      /* On regarde les autres sommets */
      m_tabSummit[m_idToRank[tabSummitTemp[i].id]].important = tabSummitTemp[i].important;

        if ((d < (tabSummitTemp[i].beg)) && (f > (tabSummitTemp[i].end))) {
          m_listSCC[cpt_SCC-1].push_back(m_idToRank[tabSummitTemp[i].id]);
        } else {
            d = tabSummitTemp[i].beg;
            f = tabSummitTemp[i].end;
            cpt_SCC++;

            m_listSCC.push_back(v);
            m_listSCC[cpt_SCC-1].push_back(m_idToRank[tabSummitTemp[i].id]);
        }

    }

  } else {
    cerr << "Erreur - Aucun graphe n'est ouvert !" << endl;
  }

  m_nbSCC = cpt_SCC;

	for (i = 0; i < (int) m_nbSCC; i++) {
		sort(m_listSCC[i].begin(), m_listSCC[i].end());
	}
}


/*=================================
Recherche
===================================*/

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
      m_listDist[it->first] = matrix.initDist(it->first);
    }

  } else {
    list.initData(m_tabSummit, m_listFriends, m_listDualFriends);

    for (it = m_listQuestion.begin(); it != m_listQuestion.end(); it++) {
      m_listDist[it->first] = list.initDist(it->first);
    }
  }


/* Etape 2 : A partir de la liste de question, pour chaque point de depart,
   On regarde les id des points où aller et on stocke le chemin inverse dans path
   On stockera ensuite ce chemin dans le multimap listPath avec le point de depart comme cle */
  for (it = m_listQuestion.begin(); it != m_listQuestion.end(); it++) {
    /* Pour tous les points de departs distincts */

    for (i = 0; i < (int) it->second.size(); i++) {
      /* it->second[i] = l'id ou on veut aller a partir de it->first */
      path.clear();

      token = it->second[i];
      path.push_back(it->second[i]);
      /* En meme temps, la distance de it->first a i est donnee par m_tabSummit[path[0]].beg */


    if ( (m_listDist[it->first][token].end == -1) && (token != it->first)) {
      /* Si il n'existe pas de chemin entre les 2 points
         On stocke directement le point de depart (rang) */
      path.push_back(it->first);
    }

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
void Graph::saveGraph (string& fileNameOut) {
  FILE* f_out;
  int i, j;
  multimap<int, vector< int > >::iterator itStart;


  f_out = fopen(fileNameOut.c_str(), "w+");

  /* Nombre de CFC */
  fprintf(f_out, "%d\n", m_nbSCC);
  /* CFC */
  for (i = 0; i < (int) m_listSCC.size(); i++) {
    for (j = 0; j < (int) m_listSCC[i].size()-1; j++) {
      if (m_tabSummit[ m_listSCC[i][j] ].important) {
        fprintf(f_out, "*");
      }
      fprintf(f_out, "%s, ", m_tabSummit[m_listSCC[i][j]].id.c_str());
    }

    if (m_tabSummit[ m_listSCC[i].back() ].important) {
        fprintf(f_out, "*");
    }
    fprintf(f_out, "%s\n", m_tabSummit[ m_listSCC[i].back() ].id.c_str());

  }

   /*Chemins*/
  fprintf(f_out, "%d\n", m_nbDist);

  for (itStart = m_listPath.begin(); itStart != m_listPath.end(); itStart++) {
    fprintf(f_out, "%d : ", m_listDist[itStart->first][itStart->second.front()].beg); // = La distance

    for (i = itStart->second.size()-1; i > 0; i--) {
      fprintf(f_out, "%d, ", m_listDist[itStart->first][itStart->second[i]].id.c_str());
    }
    fprintf(f_out, "%d\n", m_listDist[itStart->first][itStart->second[0]].id.c_str());
  }

  fclose(f_out);

}

/*=================================
Affichage
===================================*/
void Graph::printGraph () {
  int i, j;
  int start, finish;
  multimap<int, vector< int > >::iterator itStart;

  cout << "Rapport de graphe :" << endl << endl;
  cout << "Nombre de personnes : " << m_sizeGraph << endl;
  cout << "Personnes : " << endl;

if (m_structGraph == 'm') {
  for (i = 0; i < (int) m_sizeGraph; i++) {
    printSummit(m_tabSummit[i]);

    cout << "   Amis : [ ";
    for (j = 0; j < (int) m_sizeGraph; j++) {
      if (m_matFriends[i][j]) {
        cout << m_tabSummit[j].id << " ";
      }
    }

    cout << "]" << endl << "   Amis (Dual) : [ ";
    for (j = 0; j < (int) m_sizeGraph; j++) {
      if (m_matFriends[j][i]) {
        cout << m_tabSummit[j].id << " ";
      }
    }
    cout << "]" << endl;
  }
} else {
    for (i = 0; i < (int) m_sizeGraph; i++) {
    printSummit(m_tabSummit[i]);

    cout << "   Amis : [ ";
    for (j = 0; j < (int) m_listFriends[i].size(); j++) {
        cout << m_tabSummit[m_listFriends[i][j]].id << " ";
    }

    cout << "]" << endl << "   Amis (Dual) : [ ";
    for (j = 0; j < (int) m_listDualFriends[i].size(); j++) {
        cout << m_tabSummit[m_listDualFriends[i][j]].id << " ";
    }
    cout << "]" << endl;
    }
}

  cout << endl;

  cout << "Nombre de CFC : " << m_nbSCC << endl;
  cout << "CFC : " << endl;

  for (i = 0; i < (int) m_listSCC.size(); i++) {
    cout << "{ ";
    for (j = 0; j < (int) m_listSCC[i].size(); j++) {
      if (m_tabSummit[m_listSCC[i][j]].important) {
        cout << "*";
      }
      cout << m_tabSummit[m_listSCC[i][j]].id << " ";
    }
    cout << "}" << endl;
  }

  cout << endl;



  cout << "Nombre de distances : " << m_nbDist << " " << endl;
  cout << "Distances : " << endl;

  for (itStart = m_listPath.begin(); itStart != m_listPath.end(); itStart++) {
    start = itStart->first;
    finish = itStart->second.front();

    if (m_listDist[start][finish].beg == INT_MAX) {
      /* Si la distance entre les 2 est infinie */
      cout << "Pas de chemin entre " << m_listDist[start][itStart->second.back()].id;
      cout << " et " << m_listDist[start][finish].id << endl;

    } else {
      cout << m_listDist[start][finish].beg << " : "; /* = La distance */

      for (i = itStart->second.size()-1; i > 0; i--) {
        cout << m_listDist[start][itStart->second[i]].id << ", ";
      }
      cout << m_listDist[start][finish].id << endl;
    }
  }


}
