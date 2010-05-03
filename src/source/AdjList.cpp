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
        m_tabSummit[m_idToRank[it->first]].important = isImportant(it->first);

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

    for (it = m_graph.begin(); it != m_graph.end(); it++) {
      /* Recherche des importances des points */
      m_tabSummit[m_idToRank[it->first]].important = isImportant(it->first);
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
      n = extractMin(x); // x = ExtraireMin(F)

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


int AdjList::extractMin(int x) {
    int i, imin;
    int valmin;

    valmin = INT_MAX;
    imin = x;
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

bool AdjList::isImportant(int x) {
  bool important;
  bool sameCFC;
  int i, y;
  int nbFather, nbChild; /* Respectivement nombre de pere, nombre de fils */

  /* Initialisation, on suppose le point important */
  important = true;
  nbFather = 0;
  nbChild = 0;



  /* On regarde s'il a au moins un père et un fils distinct
     Si non, il n'est pas important
     On compte donc le nombre de pere et de fils de x */
    nbChild = m_graph[x].size();
    nbFather = m_graphDual[x].size();


    /* Si, en sortant de la boucle, on trouve
       - qu'il n'a pas de pere, ou pas de fils
       - qu'il a un seul pere et un seul fils, mais qu'il s'agit du meme point
       Alors, le point n'est pas important */

    if ((nbFather == 0) || (nbChild == 0)) {
      /* Cas pas de pere ou pas de fils, il s'agit d'un point isole */
      important = false;

    } else if ((nbFather == 1) && (nbChild == 1)) {
      /* Cas pere et fils unique, mais le meme point, il s'agit d'un point accessible que via son pere
         L'enlever ne changera donc pas le reste de la composante */
        if (m_graph[x][0] == m_graphDual[x][0]) {
          important = false;
        }
    }

    if (important) {
    /* A ce point, le point est toujours suppose important s'il n'a pas remplit les conditions ci dessus
       Il peut conserver ce status d'important si l'enlever implique que
       - un de ses fils ne se retrouve pas sans pere => le point deviendrait non accessible
       - un de ses peres ne se retrouve pas sans fils => le point deviendrait non co-accessible

       Il faut cependant comme condition que son fils ou pere a qui on enleve le lien
       ait lui aussi au moins un pere et un fils
       Sinon, il est forcement isole dans une CFC */

    /* L'idee est donc de regarder si,
       - pour tous ses fils qui ont au moins un pere ET un fils, il ne soit pas le seul pere
       - pour tous ses peres qui ont au moins un pere ET un fils, il ne soit pas le seul fils */

      important = false;
        /* On le met a pas important, et il va essayer de regagner ce rang en remplissant une des conditions */

      i = 0;
      /* Pour tous les fils de x */
      while ((i < (int) m_graph[x].size()) && !important) {
        y = m_graph[x][i]; /* y fils de x */

        nbChild = m_graph[y].size();
        nbFather = m_graphDual[y].size();
            /* On va compter le nombre de ses peres et fils */

          if ((nbFather > 0 ) && (nbChild > 0 )) {
            if (nbFather == 1) {
              /* Si le fils a qu'un pere, alors le pere est important */
              important = true;

            } else {
              sameCFC = false; /* Indique si on a rencontre un pere de la meme CFC */

              /* S'il y a plusieurs pere, si aucun d'eux n'est dans la CFC, alors le point est important */
              for (int j = 0; j < (int) m_graphDual[y].size(); j++) {
                if (m_graph[y][j] != x) {

                  /* Parcours des peres de i */
                  if ( (m_tabSummit[m_idToRank[m_graphDual[y][j]]].beg < m_tabSummit[m_idToRank[y]].beg && m_tabSummit[m_idToRank[m_graphDual[y][j]]].end > m_tabSummit[m_idToRank[y]].end)
                        || (m_tabSummit[m_idToRank[m_graphDual[y][j]]].beg > m_tabSummit[m_idToRank[y]].beg && m_tabSummit[m_idToRank[m_graphDual[y][j]]].end < m_tabSummit[m_idToRank[y]].end) ) {
                        /* On regarde si j est dans la meme CFC */
                    sameCFC = true; /* On dit qu'on a vu un pere dans la meme CFC */

                  }
                }
              }

              if (!sameCFC) {
                /* Si, au final, on a pas rencontre un frere de x de la meme CFC, alors le point est important */
                important = true;
              }
            }
          }

        i++;
      }

      i = 0;
      /* (S'il est toujours pas important) Pour tous les peres de x */
      while ((i < (int) m_graphDual[x].size()) && !important) {
        y = m_graphDual[x][i]; /* y pere de x */

        nbChild = m_graph[y].size();
        nbFather = m_graphDual[y].size();
            /* On va compter le nombre de ses peres et fils */

          if ((nbFather > 0 ) && (nbChild > 0 )) {
            if (nbChild == 1) {
              /* Si le pere a fils, alors le pere est important */
              important = true;

            } else {
              sameCFC = false; /* Indique si on a rencontre un fils de la meme CFC */

              /* S'il y a plusieurs fils, si aucun d'eux n'est dans la CFC, alors le point est important */
              for (int j = 0; j < (int) m_graph[y].size(); j++) {
                if (m_graph[y][j] != x) {
                  /* Parcours des fils de i != x */
                  if ( (m_tabSummit[m_idToRank[m_graph[y][j]]].beg < m_tabSummit[m_idToRank[y]].beg && m_tabSummit[m_idToRank[m_graph[y][j]]].end > m_tabSummit[m_idToRank[y]].end)
                        || (m_tabSummit[m_idToRank[m_graph[y][j]]].beg > m_tabSummit[m_idToRank[y]].beg && m_tabSummit[m_idToRank[m_graph[y][j]]].end < m_tabSummit[m_idToRank[y]].end) ) {
                        /* On regarde si j est dans la meme CFC */
                    sameCFC = true; /* On dit qu'on a vu un fils dans la meme CFC */

                  }
                }
              }

              if (!sameCFC) {
                /* Si, au final, on a pas rencontre un frere de x de la meme CFC, alors le point est important */
                important = true;
              }
            }
          }

        i++;
      }
    }

    return important;
}
